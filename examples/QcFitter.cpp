#include "AmpGen/CoherentSum.h"
#include "AmpGen/Generator.h"
#include "AmpGen/EventType.h"
#include "AmpGen/NamedParameter.h"
#include "AmpGen/Kinematics.h"
#include "AmpGen/OptionsParser.h"
#include "AmpGen/ProfileClock.h"
#include "AmpGen/ParticlePropertiesList.h"
#include "AmpGen/MinuitParameterSet.h"
#include <chrono>
#include <ctime>
#include <iostream>
#include <map>
#include <ratio>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "AmpGen/Chi2Estimator.h"
#include "AmpGen/EventList.h"
#include "AmpGen/EventType.h"
#include "AmpGen/IncoherentSum.h"
#include "AmpGen/FitResult.h"
#include "AmpGen/Minimiser.h"
#include "AmpGen/MsgService.h"
#include "AmpGen/SumPDF.h"
#include "AmpGen/Utilities.h"
#include "AmpGen/ErrorPropagator.h"

#include <TFile.h>
#include <TGraph2D.h>
#include <TRandom3.h>
#include <TRandom.h>
#ifdef _OPENMP
#include <omp.h>
#include <thread>
#endif
//#include <boost/algorithm/string.hpp>
using namespace AmpGen;
using namespace std::complex_literals;

std::vector<std::string> makeBranches(EventType Type, std::string prefix);
template <typename PDF>
FitResult* doFit( PDF&& pdf, EventList& data, EventList& mc, MinuitParameterSet& MPS );


/*template <class Container>
void split5(const std::string& str, Container& cont,
              const std::string& delims = " ")
{
    boost::split(cont, str, boost::is_any_of(delims));
}
*/

class FixedLibPdf 
{
  public: 
    FixedLibPdf() = default; 
    FixedLibPdf(const EventType& type, MinuitParameterSet& mps) : 
      FixedLibPdf(NamedParameter<std::string>(type.decayDescriptor()+"::lib").getVal()) 
    {
      INFO("Constructing: " << type << " flib = " <<type.decayDescriptor()+"::lib" );
    }
    FixedLibPdf(const std::string& lib)
    {
      void* handle = dlopen( lib.c_str(), RTLD_NOW );
      if ( handle == nullptr ) ERROR( dlerror() );
      INFO("Constructing from " << lib );
      amp = AmpGen::DynamicFCN<complex_t( const double*, const int& )>( handle, "AMP" );
    }
    void prepare(){};
    void setEvents( AmpGen::EventList& evts ){};
    double prob_unnormalised( const AmpGen::Event& evt ) const { return std::norm(getValNoCache(evt)); }
    complex_t getValNoCache( const AmpGen::Event& evt ) const { return amp(evt,+1); }
    size_t size() { return 0; }
    void reset( const bool& flag = false ){};
  private:
    AmpGen::DynamicFCN<complex_t( const double*, const int& )> amp;
};

struct DTEvent 
{
  AmpGen::Event signal;
  AmpGen::Event    tag;
  double prob;
  DTEvent() : signal(0,0,0), tag(0,0,0) {};
  DTEvent( const AmpGen::Event& signal, const AmpGen::Event& tag ) : signal(signal), tag(tag) {};
  void set( const AmpGen::Event& s1, const AmpGen::Event& s2 ) { signal.set(s1); tag.set(s2); };
  void invertParity(){
    for( size_t i = 0 ; i < signal.size(); ++i ) if( i % 4 != 3 ) signal[i] *= -1;
    for( size_t i = 0 ; i < tag.size(); ++i )    if( i % 4 != 3 ) tag[i] *= -1;
  }
};

struct DTEventList : public std::vector<DTEvent> 
{
  AmpGen::EventType m_sigType; 
  AmpGen::EventType m_tagType;
  DTEventList( const AmpGen::EventType& signal, const AmpGen::EventType& tag ) : m_sigType(signal), m_tagType(tag) {}
  std::string particleName(const AmpGen::EventType& type, const size_t& j);
  TTree* tree(const std::string& name);
};
class DTYieldCalculator {
  public:
    DTYieldCalculator(const double& productionCrossSection = 3260) : 
      productionCrossSection(productionCrossSection){}

    double operator()(const double& lumi, 
        const AmpGen::EventType& t_signal, 
        const AmpGen::EventType& t_tag, 
        const bool& print = false);
    double bf( const AmpGen::EventType& type ) const;
  private: 
    double productionCrossSection;
    std::map<std::string, double> getKeyed( const std::string& name );
    std::map<std::string, double> branchingRatios = {getKeyed("BranchingRatios")};
    std::map<std::string, double> efficiencies    = {getKeyed("Efficiencies")};
};
void add_CP_conjugate( MinuitParameterSet& mps );

template <class PDF> struct normalised_pdf {
  PDF       pdf; 
  complex_t norm;
  normalised_pdf() = default; 
  normalised_pdf(const EventType& type, MinuitParameterSet& mps, const DTYieldCalculator& yc) : pdf(type, mps)
  {
    ProfileClock pc; 
    auto normEvents = Generator<PhaseSpace>(type).generate(1e6);
    double n =0;
    pdf.prepare();
    #pragma omp parallel for reduction(+:n)
    for(size_t i =0; i<normEvents.size(); ++i) 
      n += std::norm(pdf.getValNoCache(normEvents[i]));
    auto it = mps.find( type.decayDescriptor() + "::strongPhase");
    norm = sqrt(yc.bf(type)/n);
    if( it != nullptr ) norm *= exp( 1i * it->mean() * M_PI/180. );
    pc.stop();
    INFO(type << " Time to construct: " << pc << "[ms], norm = " << norm  << " " << typeof<PDF>() );
  }
  complex_t operator()(const Event& event){ return norm * pdf.getValNoCache(event); }
};

struct ModelStore {
  MinuitParameterSet*                                 mps;
  DTYieldCalculator                                   yieldCalculator;
  std::map<std::string, normalised_pdf<CoherentSum>>  genericModels;
  std::map<std::string, normalised_pdf<FixedLibPdf>>  flibModels;
  ModelStore(MinuitParameterSet* mps, const DTYieldCalculator& yc) : mps(mps), yieldCalculator(yc) {}
  template <class T> normalised_pdf<T>& get(const EventType& type, std::map<std::string, normalised_pdf<T>>& container)
  {
    auto key = type.decayDescriptor();
    if( container.count(key) == 0 ) 
      container[key] = normalised_pdf<T>(type, *mps, yieldCalculator);
    return container[key]; 
  }
  template <class T>    normalised_pdf<T>& find(const EventType& type);
};
template <class T1, class T2> class Psi3770 {
  private:
    EventType           m_signalType;
    EventType           m_tagType;
    normalised_pdf<T1>& m_signal; 
    normalised_pdf<T1>& m_signalBar; 
    normalised_pdf<T2>& m_tag; 
    normalised_pdf<T2>& m_tagBar; 
    PhaseSpace          m_signalPhsp;
    PhaseSpace          m_tagPhsp;
    PhaseSpace          m_headPhsp;
    bool                m_printed     = {false};
    bool                m_ignoreQc    = {NamedParameter<bool>("IgnoreQC",false)};
    size_t              m_blockSize   = {1000000};
};
int main( int argc, char* argv[] )
{
  /* The user specified options must be loaded at the beginning of the programme, 
     and these can be specified either at the command line or in an options file. */   
  OptionsParser::setArgs( argc, argv );
  OptionsParser::setArgs( argc, argv, "Toy simulation for Quantum Correlated Ψ(3770) decays");
  auto time_wall = std::chrono::high_resolution_clock::now();
  auto time      = std::clock();
  size_t hwt = std::thread::hardware_concurrency();
  size_t nThreads     = NamedParameter<size_t>("nCores"      , hwt         , "Number of threads to use");
  double luminosity   = NamedParameter<double>("Luminosity"  , 818.3       , "Luminosity to generate. Defaults to CLEO-c integrated luminosity.");
  size_t nEvents      = NamedParameter<size_t>("nEvents"     , 0           , "Can also generate a fixed number of events per tag, if unspecified use the CLEO-c integrated luminosity.");
  size_t seed         = NamedParameter<size_t>("Seed"        , 0           , "Random seed to use.");
  bool   poissonYield = NamedParameter<bool  >("PoissonYield", true        , "Flag to include Poisson fluctuations in expected yields (only if nEvents is not specified)");
  bool   noQCFit      = NamedParameter<bool  >("noQCFit"     , false       , "Treat Signal and Tag as uncorrelated and fit the data individually");
  double crossSection = NamedParameter<double>("CrossSection", 3.26 * 1000 , "Cross section for e⁺e⁻ → Ψ(3770) → DD'");
  std::string output  = NamedParameter<std::string>("Output" , "ToyMC.root", "File containing output events"); 
  auto pNames = NamedParameter<std::string>("EventType" , ""    
      , "EventType to generate, in the format: \033[3m parent daughter1 daughter2 ... \033[0m" ).getVector(); 
  auto tags           = NamedParameter<std::string>("TagTypes" , std::string(), "Vector of opposite side tags to generate, in the format \033[3m outputTreeName decayDescriptor \033[0m.").getVector();


  /* Parameters that have been parsed can be accessed anywhere in the program 
     using the NamedParameter<T> class. The name of the parameter is the first option,
     then the default value, and then the help string that will be printed if --h is specified 
     as an option. */
  std::string dataFile = NamedParameter<std::string>("DataSample", ""          , "Name of file containing data sample to fit." );
  std::string intFile  = NamedParameter<std::string>("IntegrationSample",""    , "Name of file containing events to use for MC integration.");
  std::string logFile  = NamedParameter<std::string>("LogFile"   , "Fitter.log", "Name of the output log file");
  std::string plotFile = NamedParameter<std::string>("Plots"     , "plots.root", "Name of the output plot file");
  
  if( dataFile == "" ) FATAL("Must specify input with option " << italic_on << "DataSample" << italic_off );
  if( pNames.size() == 0 ) FATAL("Must specify event type with option " << italic_on << " EventType" << italic_off);

  TRandom3 rndm;
  rndm.SetSeed( seed );
  gRandom = &rndm;

  INFO("LogFile: " << logFile << "; Plots: " << plotFile );
   #ifdef _OPENMP
  omp_set_num_threads( nThreads );
  INFO( "Setting " << nThreads << " fixed threads for OpenMP" );
  omp_set_dynamic( 0 );
#endif


  TFile * data = TFile::Open(dataFile.c_str());
  TFile * mc = TFile::Open(intFile.c_str());
  std::vector<std::string> varNames = {"E", "PX", "PY", "PZ"};
  auto yc = DTYieldCalculator(crossSection);
  MinuitParameterSet MPS;
  MPS.loadFromStream();
  ModelStore models(&MPS, yc);
 for( auto& tag : tags ){

    EventType signalType( pNames );

    auto tokens       = split(tag, ' ');
    auto tagParticle  = Particle(tokens[1], {}, false);
    EventType    tagType = tagParticle.eventType();
    INFO("Tag is "<<tagType<<"\n");
    CoherentSum sigPDF(signalType, MPS);
    CoherentSum tagPDF(tagType, MPS);
    INFO("Tokens are "<<tokens[0]<<"\n");
 

    TTree * dataTree = (TTree*)data->Get(tokens[0].c_str());
    TTree * mcTree = (TTree*)mc->Get(tokens[0].c_str());

    
    
    auto sigBranches = makeBranches(signalType, "");
    auto tagBranches = makeBranches(tagType, "Tag_");
    EventList sigEvents(signalType);
    EventList sigMCEvents(signalType);
    EventList tagEvents(tagType);
    EventList tagMCEvents(tagType);
    tagEvents.loadFromTree(dataTree, Branches(tagBranches));
    tagMCEvents.loadFromTree(mcTree, Branches(tagBranches));
    sigEvents.loadFromTree(dataTree, Branches(sigBranches));
    sigMCEvents.loadFromTree(mcTree, Branches(sigBranches));
    tagPDF.setEvents(tagEvents);
    sigPDF.setEvents(sigEvents);
    sigPDF.setMC(sigMCEvents);
    tagPDF.setMC(tagMCEvents);
    //FitResult * fr = doFit(make_pdf(tagPDF), tagEvents, MPS);
    FitResult * frSig = doFit(make_pdf(sigPDF), sigEvents, sigMCEvents, MPS);
    //FitResult * frTag = doFit(make_pdf(tagPDF), tagEvents, tagMCEvents , MPS);
    std::ostringstream stringStream;
    stringStream<<logFile<<tokens[0];
    frSig->writeToFile(stringStream.str());

   }
  
  return 0;
}


std::vector<std::string> makeBranches(EventType Type, std::string prefix){
  auto n = Type.finalStates().size();
  std::vector<std::string> branches;
  std::vector<std::string> varNames = {"E", "PX", "PY", "PZ"};
  for (int i=0; i<n; i++){
    auto part = replaceAll(Type.finalStates()[i], "+", "p");
    part = replaceAll(part, "-", "m");
    for (int j=0; j<varNames.size(); j++){
      std::ostringstream stringStream;
      stringStream<<prefix<<part<<"_"<<varNames[j];
      branches.push_back(stringStream.str());
    }
  }
  return branches;
}

template <typename PDF>
FitResult* doFit( PDF&& pdf, EventList& data, EventList& mc, MinuitParameterSet& MPS )
{
  auto time_wall = std::chrono::high_resolution_clock::now();
  auto time      = std::clock();

  pdf.setEvents( data );

  /* Minimiser is a general interface to Minuit1/Minuit2, 
     that is constructed from an object that defines an operator() that returns a double 
     (i.e. the likielihood, and a set of MinuitParameters. */
  Minimiser mini( pdf, &MPS );
  INFO("Starting Fit");
  mini.doFit();
  FitResult* fr = new FitResult(mini);

  /* Make the plots for the different components in the PDF, i.e. the signal and backgrounds. 
     The structure assumed the PDF is some SumPDF<T1,T2,...>. */
  unsigned int counter = 1;
 /* 
  for_each(pdf.m_pdfs, [&]( auto& f ){
    std::function<double(const Event&)> FCN_sig = [&](const Event& evt){ return f.prob_unnormalised(evt) ; };
    auto mc_plot3 = mc.makeDefaultProjections(WeightFunction(f), Prefix("Model_cat"+std::to_string(counter)));
    for( auto& plot : mc_plot3 )
    {
      plot->Scale( ( data.integral() * f.getWeight() ) / plot->Integral() );
      plot->Write();
    }
    counter++;
  } );
  */
  /* Estimate the chi2 using an adaptive / decision tree based binning, 
     down to a minimum bin population of 15, and add it to the output. */
  
  Chi2Estimator chi2( data, mc, pdf, 15 );
  chi2.writeBinningToFile("chi2_binning.txt");
  fr->addChi2( chi2.chi2(), chi2.nBins() );
  
  auto twall_end  = std::chrono::high_resolution_clock::now();
  double time_cpu = ( std::clock() - time ) / (double)CLOCKS_PER_SEC;
  double tWall    = std::chrono::duration<double, std::milli>( twall_end - time_wall ).count();
  INFO( "Wall time = " << tWall / 1000. );
  INFO( "CPU  time = " << time_cpu );
  
  fr->print();
  return fr;
}
