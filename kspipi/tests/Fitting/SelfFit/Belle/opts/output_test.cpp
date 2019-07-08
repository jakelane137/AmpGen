#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE amp
#include <boost/test/included/unit_test.hpp>
#include "AmpGen/Particle.h"
#include "AmpGen/CompiledExpression.h"
#include "AmpGen/EventType.h"
#include "AmpGen/MinuitParameterSet.h"
#include "AmpGen/OptionsParser.h"
using namespace AmpGen;
void setupOptions(){
 OptionsParser::setArg( "CouplingConstant::Coordinates cartesian");
 OptionsParser::setArg( "D0{K(0)*(1430)+[GLASS]{K0S0,pi+},pi-} 0 -.10 .01 0 0.03 0.01");
 OptionsParser::setArg( "D0{K(0)*(1430)bar-[GLASS]{K0S0,pi-},pi+} 0 -.39 .07 0 2.33 0.06");
 OptionsParser::setArg( "D0{K(2)*(1430)+{K0S0,pi+},pi-} 0 .00 .01 0 -0.10 0.01");
 OptionsParser::setArg( "D0{K(2)*(1430)bar-{K0S0,pi-},pi+} 0 .91 .02 0 -0.88 0.02");
 OptionsParser::setArg( "D0{K*(1410)+{K0S0,pi+},pi-} 0 -.18 .02 0 0.10 0.02");
 OptionsParser::setArg( "D0{K*(1410)bar-{K0S0,pi-},pi+} 0 -.05 .03 0 0.29 0.03");
 OptionsParser::setArg( "D0{K*(1680)bar-{K0S0,pi-},pi+} 0 -1.56 .18 0 -2.92 0.20");
 OptionsParser::setArg( "D0{K*(892)+{K0S0,pi+},pi-} 0 .12 .00 0 -0.11 0.00");
 OptionsParser::setArg( "D0{K*(892)bar-{K0S0,pi-},pi+} 0 -1.25 .01 0 1.18 0.01");
 OptionsParser::setArg( "D0{K0S0,PiPi00} 0 1.00 .00 0 0.00 0.00");
 OptionsParser::setArg( "D0{K0S0,f(2)(1270)0{pi+,pi-}} 0 1.15 .03 0 -0.85 0.03");
 OptionsParser::setArg( "D0{K0S0,omega(782)0{pi+,pi-}} 0 -.02 .00 0 0.03 0.00");
 OptionsParser::setArg( "D0{K0S0,rho(1450)0{pi+,pi-}} 0 -.60 .09 0 2.79 0.10");
 OptionsParser::setArg( "D0{K0S0,rho(770)0{pi+,pi-}} 2 1.00 .00 2 0.00 0.00");
 OptionsParser::setArg( "Dbar0{K(0)*(1430)+[GLASS]{K0S0,pi+},pi-} 0 -.39 .07 0 2.33 0.06");
 OptionsParser::setArg( "Dbar0{K(0)*(1430)bar-[GLASS]{K0S0,pi-},pi+} 0 -.10 .01 0 0.03 0.01");
 OptionsParser::setArg( "Dbar0{K(2)*(1430)+{K0S0,pi+},pi-} 0 .91 .02 0 -0.88 0.02");
 OptionsParser::setArg( "Dbar0{K(2)*(1430)bar-{K0S0,pi-},pi+} 0 .00 .01 0 -0.10 0.01");
 OptionsParser::setArg( "Dbar0{K*(1410)+{K0S0,pi+},pi-} 0 -.05 .03 0 0.29 0.03");
 OptionsParser::setArg( "Dbar0{K*(1410)bar-{K0S0,pi-},pi+} 0 -.18 .02 0 0.10 0.02");
 OptionsParser::setArg( "Dbar0{K*(1680)+{K0S0,pi+},pi-} 0 -1.56 .18 0 -2.92 0.20");
 OptionsParser::setArg( "Dbar0{K*(892)+{K0S0,pi+},pi-} 0 -1.25 .01 0 1.18 0.01");
 OptionsParser::setArg( "Dbar0{K*(892)bar-{K0S0,pi-},pi+} 0 .12 .00 0 -0.11 0.00");
 OptionsParser::setArg( "Dbar0{K0S0,PiPi00} 0 1.00 .00 0 0.00 0.00");
 OptionsParser::setArg( "Dbar0{K0S0,f(2)(1270)0{pi+,pi-}} 0 1.15 .03 0 -0.85 0.03");
 OptionsParser::setArg( "Dbar0{K0S0,omega(782)0{pi+,pi-}} 0 -.02 .00 0 0.03 0.00");
 OptionsParser::setArg( "Dbar0{K0S0,rho(1450)0{pi+,pi-}} 0 -.60 .09 0 2.79 0.10");
 OptionsParser::setArg( "Dbar0{K0S0,rho(770)0{pi+,pi-}} 2 1.00 .00 2 0.00 0.00");
 OptionsParser::setArg( "EventType D0 K0S0 pi+ pi-");
 OptionsParser::setArg( "IS_p1_4pi 3 0 0");
 OptionsParser::setArg( "IS_p1_EtaEta 3 -0.39899 0");
 OptionsParser::setArg( "IS_p1_EtapEta 3 -0.34639 0");
 OptionsParser::setArg( "IS_p1_KK 3 -0.55377 0");
 OptionsParser::setArg( "IS_p1_mass 3 0.651 0");
 OptionsParser::setArg( "IS_p1_pipi 3 0.22889 0");
 OptionsParser::setArg( "IS_p2_4pi 3 0 0");
 OptionsParser::setArg( "IS_p2_EtaEta 3 0.39065 0");
 OptionsParser::setArg( "IS_p2_EtapEta 3 0.31503 0");
 OptionsParser::setArg( "IS_p2_KK 3 0.55095 0");
 OptionsParser::setArg( "IS_p2_mass 3 1.2036 0");
 OptionsParser::setArg( "IS_p2_pipi 3 0.94128 0");
 OptionsParser::setArg( "IS_p3_4pi 3 0.55639 0");
 OptionsParser::setArg( "IS_p3_EtaEta 3 0.1834 0");
 OptionsParser::setArg( "IS_p3_EtapEta 3 0.18681 0");
 OptionsParser::setArg( "IS_p3_KK 3 0.23888 0");
 OptionsParser::setArg( "IS_p3_mass 3 1.55817 0");
 OptionsParser::setArg( "IS_p3_pipi 3 0.36856 0");
 OptionsParser::setArg( "IS_p4_4pi 3 0.85679 0");
 OptionsParser::setArg( "IS_p4_EtaEta 3 0.19906 0");
 OptionsParser::setArg( "IS_p4_EtapEta 3 -0.00984 0");
 OptionsParser::setArg( "IS_p4_KK 3 0.40907 0");
 OptionsParser::setArg( "IS_p4_mass 3 1.21 0");
 OptionsParser::setArg( "IS_p4_pipi 3 0.3365 0");
 OptionsParser::setArg( "IS_p5_4pi 3 -0.79658 0");
 OptionsParser::setArg( "IS_p5_EtaEta 3 -0.00355 0");
 OptionsParser::setArg( "IS_p5_EtapEta 3 0.22358 0");
 OptionsParser::setArg( "IS_p5_KK 3 -0.17558 0");
 OptionsParser::setArg( "IS_p5_mass 3 1.82206 0");
 OptionsParser::setArg( "IS_p5_pipi 3 0.18171 0");
 OptionsParser::setArg( "Particle::DefaultModifier BL");
 OptionsParser::setArg( "Particle::SpinFormalism Canonical");
 OptionsParser::setArg( "PiPi00[kMatrix.pole.0]{pi+,pi-} 0 3.12 .50 0 7.91 0.50");
 OptionsParser::setArg( "PiPi00[kMatrix.pole.1]{pi+,pi-} 0 11.15 .30 0 4.96 0.30");
 OptionsParser::setArg( "PiPi00[kMatrix.pole.2]{pi+,pi-} 0 29.20 1.60 0 -0.05 1.27");
 OptionsParser::setArg( "PiPi00[kMatrix.pole.3]{pi+,pi-} 0 6.66 .47 0 -8.50 0.48");
 OptionsParser::setArg( "PiPi00[kMatrix.prod.0]{pi+,pi-} 0 -4.70 .37 0 -6.47 0.38");
 OptionsParser::setArg( "PiPi00[kMatrix.prod.1]{pi+,pi-} 0 -23.29 1.55 0 -12.23 1.43");
 OptionsParser::setArg( "PiPi00[kMatrix.prod.2]{pi+,pi-} 0 -1.84 1.79 0 -32.95 1.80");
 OptionsParser::setArg( "PiPi00[kMatrix.prod.3]{pi+,pi-} 0 -13.65 1.25 0 -22.36 1.28");
 OptionsParser::setArg( "f_scatt0 3 0.23399 0");
 OptionsParser::setArg( "f_scatt1 3 0.15044 0");
 OptionsParser::setArg( "f_scatt2 3 -0.20545 0");
 OptionsParser::setArg( "f_scatt3 3 0.32825 0");
 OptionsParser::setArg( "f_scatt4 3 0.35412 0");
 OptionsParser::setArg( "s0_prod 3 -1 0");
 OptionsParser::setArg( "s0_scatt 3 -3.92637 0");
 OptionsParser::setArg( "sA 3 1 0");

}

BOOST_AUTO_TEST_CASE( D0_K_0_s_1430_p_GLASS_BL__K0S0_pip__pim__test){
  EventType type({"D0", "K0S0", "pi+", "pi-"});
  Particle p("D0{K(0)*(1430)+[GLASS.BL]{K0S0,pi+},pi-}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {-0.632680761611367, -0.317287909488989, 0.180580700476102, 0.883847071614469, 0.679919904250768, 0.268382414427232, -0.281704232040771, 0.795711823504639, -0.0472391426394016, 0.0489054950617566, 0.10112353156467, 0.185281104880893};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == 0.0359725565394843, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == 0.000584703354055873, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_K_0_s_1430_barm_GLASS_BL__K0S0_pim__pip__test){
  EventType type({"D0", "K0S0", "pi+", "pi-"});
  Particle p("D0{K(0)*(1430)bar-[GLASS.BL]{K0S0,pi-},pi+}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {-0.632680761611367, -0.317287909488989, 0.180580700476102, 0.883847071614469, 0.679919904250768, 0.268382414427232, -0.281704232040771, 0.795711823504639, -0.0472391426394016, 0.0489054950617566, 0.10112353156467, 0.185281104880893};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == 1.7385331052736, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == 0.754778108968434, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_K_2_s_1430_p_K0S0_pip__pim__test){
  EventType type({"D0", "K0S0", "pi+", "pi-"});
  Particle p("D0{K(2)*(1430)+{K0S0,pi+},pi-}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {-0.632680761611367, -0.317287909488989, 0.180580700476102, 0.883847071614469, 0.679919904250768, 0.268382414427232, -0.281704232040771, 0.795711823504639, -0.0472391426394016, 0.0489054950617566, 0.10112353156467, 0.185281104880893};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == 0.043651893410477, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == -0.0158233993486357, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_K_2_s_1430_barm_K0S0_pim__pip__test){
  EventType type({"D0", "K0S0", "pi+", "pi-"});
  Particle p("D0{K(2)*(1430)bar-{K0S0,pi-},pi+}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {-0.632680761611367, -0.317287909488989, 0.180580700476102, 0.883847071614469, 0.679919904250768, 0.268382414427232, -0.281704232040771, 0.795711823504639, -0.0472391426394016, 0.0489054950617566, 0.10112353156467, 0.185281104880893};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == 0.0136658407693519, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == 3.1331520023933e-06, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_Ks_1410_p_K0S0_pip__pim__test){
  EventType type({"D0", "K0S0", "pi+", "pi-"});
  Particle p("D0{K*(1410)+{K0S0,pi+},pi-}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {-0.632680761611367, -0.317287909488989, 0.180580700476102, 0.883847071614469, 0.679919904250768, 0.268382414427232, -0.281704232040771, 0.795711823504639, -0.0472391426394016, 0.0489054950617566, 0.10112353156467, 0.185281104880893};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == -0.182238489136295, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == 0.0956862591927359, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_Ks_1410_barm_K0S0_pim__pip__test){
  EventType type({"D0", "K0S0", "pi+", "pi-"});
  Particle p("D0{K*(1410)bar-{K0S0,pi-},pi+}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {-0.632680761611367, -0.317287909488989, 0.180580700476102, 0.883847071614469, 0.679919904250768, 0.268382414427232, -0.281704232040771, 0.795711823504639, -0.0472391426394016, 0.0489054950617566, 0.10112353156467, 0.185281104880893};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == -0.116217977326228, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == -0.00138203204588872, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_Ks_1680_barm_K0S0_pim__pip__test){
  EventType type({"D0", "K0S0", "pi+", "pi-"});
  Particle p("D0{K*(1680)bar-{K0S0,pi-},pi+}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {-0.632680761611367, -0.317287909488989, 0.180580700476102, 0.883847071614469, 0.679919904250768, 0.268382414427232, -0.281704232040771, 0.795711823504639, -0.0472391426394016, 0.0489054950617566, 0.10112353156467, 0.185281104880893};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == -0.100880524586751, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == -0.000917035654961705, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_Ks_892_p_K0S0_pip__pim__test){
  EventType type({"D0", "K0S0", "pi+", "pi-"});
  Particle p("D0{K*(892)+{K0S0,pi+},pi-}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {-0.632680761611367, -0.317287909488989, 0.180580700476102, 0.883847071614469, 0.679919904250768, 0.268382414427232, -0.281704232040771, 0.795711823504639, -0.0472391426394016, 0.0489054950617566, 0.10112353156467, 0.185281104880893};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == -0.0270378698198936, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == 0.00311771422789058, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_Ks_892_barm_K0S0_pim__pip__test){
  EventType type({"D0", "K0S0", "pi+", "pi-"});
  Particle p("D0{K*(892)bar-{K0S0,pi-},pi+}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {-0.632680761611367, -0.317287909488989, 0.180580700476102, 0.883847071614469, 0.679919904250768, 0.268382414427232, -0.281704232040771, 0.795711823504639, -0.0472391426394016, 0.0489054950617566, 0.10112353156467, 0.185281104880893};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == -0.188691090406239, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == -0.0067968280627042, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_PiPi00_kMatrix_pole_0__pip_pim__K0S0__test){
  EventType type({"D0", "K0S0", "pi+", "pi-"});
  Particle p("D0{PiPi00[kMatrix.pole.0]{pi+,pi-},K0S0}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {-0.632680761611367, -0.317287909488989, 0.180580700476102, 0.883847071614469, 0.679919904250768, 0.268382414427232, -0.281704232040771, 0.795711823504639, -0.0472391426394016, 0.0489054950617566, 0.10112353156467, 0.185281104880893};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == 0.630485472441833, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == 1.0932378327331, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_PiPi00_kMatrix_pole_1__pip_pim__K0S0__test){
  EventType type({"D0", "K0S0", "pi+", "pi-"});
  Particle p("D0{PiPi00[kMatrix.pole.1]{pi+,pi-},K0S0}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {-0.632680761611367, -0.317287909488989, 0.180580700476102, 0.883847071614469, 0.679919904250768, 0.268382414427232, -0.281704232040771, 0.795711823504639, -0.0472391426394016, 0.0489054950617566, 0.10112353156467, 0.185281104880893};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == 0.288313912313402, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == 0.499930460274807, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_PiPi00_kMatrix_pole_2__pip_pim__K0S0__test){
  EventType type({"D0", "K0S0", "pi+", "pi-"});
  Particle p("D0{PiPi00[kMatrix.pole.2]{pi+,pi-},K0S0}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {-0.632680761611367, -0.317287909488989, 0.180580700476102, 0.883847071614469, 0.679919904250768, 0.268382414427232, -0.281704232040771, 0.795711823504639, -0.0472391426394016, 0.0489054950617566, 0.10112353156467, 0.185281104880893};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == 0.0595790843125637, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == 0.103302028878853, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_PiPi00_kMatrix_pole_3__pip_pim__K0S0__test){
  EventType type({"D0", "K0S0", "pi+", "pi-"});
  Particle p("D0{PiPi00[kMatrix.pole.3]{pi+,pi-},K0S0}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {-0.632680761611367, -0.317287909488989, 0.180580700476102, 0.883847071614469, 0.679919904250768, 0.268382414427232, -0.281704232040771, 0.795711823504639, -0.0472391426394016, 0.0489054950617566, 0.10112353156467, 0.185281104880893};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == 0.116272718917695, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == 0.201596176711339, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_PiPi00_kMatrix_prod_0__pip_pim__K0S0__test){
  EventType type({"D0", "K0S0", "pi+", "pi-"});
  Particle p("D0{PiPi00[kMatrix.prod.0]{pi+,pi-},K0S0}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {-0.632680761611367, -0.317287909488989, 0.180580700476102, 0.883847071614469, 0.679919904250768, 0.268382414427232, -0.281704232040771, 0.795711823504639, -0.0472391426394016, 0.0489054950617566, 0.10112353156467, 0.185281104880893};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == 0.535414066216762, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == 0.928396830558508, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_PiPi00_kMatrix_prod_1__pip_pim__K0S0__test){
  EventType type({"D0", "K0S0", "pi+", "pi-"});
  Particle p("D0{PiPi00[kMatrix.prod.1]{pi+,pi-},K0S0}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {-0.632680761611367, -0.317287909488989, 0.180580700476102, 0.883847071614469, 0.679919904250768, 0.268382414427232, -0.281704232040771, 0.795711823504639, -0.0472391426394016, 0.0489054950617566, 0.10112353156467, 0.185281104880893};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == 0.177874959451026, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == 0.308439686649509, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_PiPi00_kMatrix_prod_2__pip_pim__K0S0__test){
  EventType type({"D0", "K0S0", "pi+", "pi-"});
  Particle p("D0{PiPi00[kMatrix.prod.2]{pi+,pi-},K0S0}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {-0.632680761611367, -0.317287909488989, 0.180580700476102, 0.883847071614469, 0.679919904250768, 0.268382414427232, -0.281704232040771, 0.795711823504639, -0.0472391426394016, 0.0489054950617566, 0.10112353156467, 0.185281104880893};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == 2.24241098732402e-05, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == -1.29349550167178e-05, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_PiPi00_kMatrix_prod_3__pip_pim__K0S0__test){
  EventType type({"D0", "K0S0", "pi+", "pi-"});
  Particle p("D0{PiPi00[kMatrix.prod.3]{pi+,pi-},K0S0}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {-0.632680761611367, -0.317287909488989, 0.180580700476102, 0.883847071614469, 0.679919904250768, 0.268382414427232, -0.281704232040771, 0.795711823504639, -0.0472391426394016, 0.0489054950617566, 0.10112353156467, 0.185281104880893};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == 0.0293052592775151, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == 0.0508160052588401, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_f_2__1270_0_pip_pim__K0S0__test){
  EventType type({"D0", "K0S0", "pi+", "pi-"});
  Particle p("D0{f(2)(1270)0{pi+,pi-},K0S0}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {-0.632680761611367, -0.317287909488989, 0.180580700476102, 0.883847071614469, 0.679919904250768, 0.268382414427232, -0.281704232040771, 0.795711823504639, -0.0472391426394016, 0.0489054950617566, 0.10112353156467, 0.185281104880893};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == 0.209557566192474, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == 0.00252619562952199, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_omega_782_0_pip_pim__K0S0__test){
  EventType type({"D0", "K0S0", "pi+", "pi-"});
  Particle p("D0{omega(782)0{pi+,pi-},K0S0}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {-0.632680761611367, -0.317287909488989, 0.180580700476102, 0.883847071614469, 0.679919904250768, 0.268382414427232, -0.281704232040771, 0.795711823504639, -0.0472391426394016, 0.0489054950617566, 0.10112353156467, 0.185281104880893};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == -0.226409239151879, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == -0.0056515419803771, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_rho_1450_0_pip_pim__K0S0__test){
  EventType type({"D0", "K0S0", "pi+", "pi-"});
  Particle p("D0{rho(1450)0{pi+,pi-},K0S0}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {-0.632680761611367, -0.317287909488989, 0.180580700476102, 0.883847071614469, 0.679919904250768, 0.268382414427232, -0.281704232040771, 0.795711823504639, -0.0472391426394016, 0.0489054950617566, 0.10112353156467, 0.185281104880893};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == -0.312744646553665, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == -0.0301386607979306, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_rho_770_0_pip_pim__K0S0__test){
  EventType type({"D0", "K0S0", "pi+", "pi-"});
  Particle p("D0{rho(770)0{pi+,pi-},K0S0}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {-0.632680761611367, -0.317287909488989, 0.180580700476102, 0.883847071614469, 0.679919904250768, 0.268382414427232, -0.281704232040771, 0.795711823504639, -0.0472391426394016, 0.0489054950617566, 0.10112353156467, 0.185281104880893};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == -0.82572296446812, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == -0.389408909580126, boost::test_tools::tolerance(1e-6)) ;
}

