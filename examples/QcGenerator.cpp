#include "AmpGen/Psi3770.h"
using namespace AmpGen;
using namespace std::complex_literals;
void add_CP_conjugate( MinuitParameterSet& mps );


int main( int argc, char** argv )
{
  OptionsParser::setArgs( argc, argv, "Toy simulation for Quantum Correlated Ψ(3770) decays");
  auto time_wall = std::chrono::high_resolution_clock::now();
  auto time      = std::clock();
  size_t hwt = std::thread::hardware_concurrency();
  size_t nThreads     = NamedParameter<size_t>("nCores"      , hwt         , "Number of threads to use");
  double luminosity   = NamedParameter<double>("Luminosity"  , 818.3       , "Luminosity to generate. Defaults to CLEO-c integrated luminosity.");
  size_t nEvents      = NamedParameter<size_t>("nEvents"     , 0           , "Can also generate a fixed number of events per tag, if unspecified use the CLEO-c integrated luminosity.");
  size_t seed         = NamedParameter<size_t>("Seed"        , 0           , "Random seed to use.");
  bool   poissonYield = NamedParameter<bool  >("PoissonYield", true        , "Flag to include Poisson fluctuations in expected yields (only if nEvents is not specified)");
  double crossSection = NamedParameter<double>("CrossSection", 3.26 * 1000 , "Cross section for e⁺e⁻ → Ψ(3770) → DD'");
  std::string output  = NamedParameter<std::string>("Output" , "ToyMC.root", "File containing output events"); 
  auto pNames = NamedParameter<std::string>("EventType" , ""    
      , "EventType to generate, in the format: \033[3m parent daughter1 daughter2 ... \033[0m" ).getVector(); 
  auto tags           = NamedParameter<std::string>("TagTypes" , std::string(), "Vector of opposite side tags to generate, in the format \033[3m outputTreeName decayDescriptor \033[0m.").getVector();



  gRandom = new TRandom3(seed);
#ifdef _OPENMP
  omp_set_num_threads( nThreads );
  INFO("Setting " << nThreads << " fixed threads for OpenMP");
  omp_set_dynamic(0);  
#endif
  MinuitParameterSet MPS; 
  MPS.loadFromStream();
  add_CP_conjugate( MPS );
  EventType signalType( pNames );
  TFile* f = TFile::Open( output.c_str() ,"RECREATE");
  auto yc = DTYieldCalculator(crossSection);
  if( nEvents == 0 ) 
    INFO("Generating events using PDG/efficiencies with luminosity = " << luminosity << " pb⁻¹; σ = " << crossSection << " pb" );
  else INFO("Generating " << nEvents << " per sample");
  ModelStore models(&MPS, yc); 
  for( auto& tag : tags ){
    auto tokens       = split(tag, ' ');
    auto tagParticle  = Particle(tokens[1], {}, false);
    EventType    type = tagParticle.eventType();
    double yield_noQC = yc(luminosity,signalType,type,true);
    auto generator    = Psi3770<CoherentSum,CoherentSum>(models, signalType, type) ; 
    double rho        = generator.rho();
//    std::complex<double> fSig = generator.fSig()
    double yield = nEvents; 
    if( nEvents == 0 && poissonYield  )  yield = gRandom->Poisson(yield_noQC*rho); 
    if( nEvents == 0 && !poissonYield ) yield = yield_noQC*rho;  
    INFO( "Tag = " << type << " Expected Yield [incoherent] = " << yield_noQC << " rho = " << rho << " requested = " << yield );
    DTEventList evtlist = generator.generate(yield);
    int n_evtList = evtlist.size();
    TFile * fsigVal = TFile::Open("sigVal.root", "RECREATE");
    TGraph2D * gSigMag = new TGraph2D(nEvents);
    TGraph2D * gSigPh = new TGraph2D(nEvents);
    TGraph2D * gSigCCMag = new TGraph2D(nEvents);
    TGraph2D * gSigCCPh = new TGraph2D(nEvents);
    TGraph2D * gSigDelta = new TGraph2D(nEvents);


    for (int i =0; i < n_evtList; i++){

      std::complex<double> sigVal = generator.fSig(evtlist[i]);
      std::complex<double> sigCCVal = generator.fSigCC(evtlist[i]);
      std::complex<double> tagVal = generator.fTag(evtlist[i]);
      std::complex<double> tagCCVal = generator.fTagCC(evtlist[i]);
      std::vector<size_t> xind = {0,1};
      std::vector<size_t> yind = {0,2};
      double sigx = generator.sigS(evtlist[i], xind);
      double sigy = generator.sigS(evtlist[i], yind);
      double sigMag = std::abs(sigVal);
      double sigPh = std::arg(sigVal); 
      double sigCCMag = std::abs(sigCCVal);
      double sigCCPh = std::arg(sigCCVal);
      double sigDelta = sigPh - sigCCPh;
      double tagMag = std::abs(tagVal);
      double tagPh = std::arg(tagVal); 
      double tagCCMag = std::abs(tagCCVal);
      double tagCCPh = std::arg(tagCCVal);
      double tagDelta = tagPh - tagCCPh;
      gSigMag->SetPoint(i, sigx, sigy, sigMag);
      gSigPh->SetPoint(i, sigx, sigy, sigPh);
      gSigCCMag->SetPoint(i, sigx, sigy, sigCCMag);
      gSigCCPh->SetPoint(i, sigx, sigy, sigCCPh);
      gSigDelta->SetPoint(i, sigx, sigy, sigDelta);
      if (i % (int)n_evtList/100 ){
        std::cout<<"Event "<<i<<"out of "<<n_evtList<<"\n";
        std::cout<<"Dalitz Coordinates = ("<<sigx<<","<<sigy<<")\n";
        std::cout<<"Signal |A| = "<<sigMag<<"\n";
        std::cout<<"SignalCC |A| = "<<sigCCMag<<"\n";
        std::cout<<"Signal ẟ = "<<sigPh<<"\n";
        std::cout<<"SignalCC ẟ = "<<sigCCPh<<"\n";
        std::cout<<"Signal Δẟ ="<<sigDelta<<"\n";
        std::cout<<"Tag |A| = "<<tagMag<<"\n";
        std::cout<<"TagCC |A| = "<<tagCCMag<<"\n";
        std::cout<<"Tag ẟ = "<<tagPh<<"\n";
        std::cout<<"TagCC ẟ = "<<tagCCPh<<"\n";
        std::cout<<"Tag Δẟ ="<<tagDelta<<"\n";
//        std::cout<<"Value of event "<<i<<" = "<<generator.fSig(evtlist[i])<<"\n";
      }
    }
    gSigMag->Write("mag");
    gSigPh->Write("phase");
    gSigDelta->Write("deltaPhase");
    gSigCCMag->Write("magCC");
    gSigCCPh->Write("phaseCC");
    fsigVal->Close();
    f->cd();
 generator.generate(yield).tree(tokens[0])->Write();
  }
  f->Close(); 
  auto twall_end  = std::chrono::high_resolution_clock::now();
  double time_cpu = ( std::clock() - time ) / (double)CLOCKS_PER_SEC;
  double tWall    = std::chrono::duration<double, std::milli>( twall_end - time_wall ).count();
  INFO( "Wall time = " << tWall / 1000. );
  INFO( "CPU  time = " << time_cpu );
}

void add_CP_conjugate( MinuitParameterSet& mps )
{
  std::vector<MinuitParameter*> tmp;
  for( auto& param : mps ){
    const std::string name = param->name();
    size_t pos=0;
    std::string new_name = name; 
    int sgn=1;
    if( name.find("::") != std::string::npos ){
      pos = name.find("::");
      auto props = AmpGen::ParticlePropertiesList::get( name.substr(0,pos), true );
      if( props != 0 ) new_name = props->anti().name() + name.substr(pos); 
    }
    else { 
      auto tokens=split(name,'_');
      std::string reOrIm = *tokens.rbegin();
      std::string name   = tokens[0];
      if ( reOrIm == "Re" || reOrIm == "Im" ){
        auto p = Particle( name ).conj();
        sgn = reOrIm == "Re" ? p.quasiCP() : 1; 
        new_name = p.uniqueString() +"_"+reOrIm;
      }
      else if( tokens.size() == 2 ) {
        auto props = AmpGen::ParticlePropertiesList::get( name );
        if( props != 0  ) new_name = props->anti().name() + "_" + tokens[1]; 
      }
    }
    if( mps.find( new_name ) == nullptr ){
      tmp.push_back( new MinuitParameter(new_name, Flag::Free, sgn * param->mean(), param->err(), 0, 0));
    }
  }
  for( auto& p : tmp ) mps.add( p );
}

template <> normalised_pdf<CoherentSum>& ModelStore::find(const EventType& type){ return get<CoherentSum>(type, genericModels); }
template <> normalised_pdf<FixedLibPdf>& ModelStore::find(const EventType& type){ return get<FixedLibPdf>(type, flibModels); }

