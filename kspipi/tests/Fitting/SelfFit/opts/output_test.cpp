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
 OptionsParser::setArg( "D0_radius 0 5 0.01");
 OptionsParser::setArg( "D0{K(0)*(1430)+[GLASS]{K0S0,pi+},pi-} 0 0.0095653 0.000827718 0 0.00601207 0.000843968");
 OptionsParser::setArg( "D0{K(0)*(1430)bar-[GLASS]{K0S0,pi-},pi+} 0 0.0255993 0.00122597 0 -0.194327 0.00105316");
 OptionsParser::setArg( "D0{K(2)*(1430)+{K0S0,pi+},pi-} 0 0.0133101 0.00135651 0 0.0170886 0.00123279");
 OptionsParser::setArg( "D0{K(2)*(1430)bar-{K0S0,pi-},pi+} 0 -0.107163 0.00146194 0 0.104979 0.00164431");
 OptionsParser::setArg( "D0{K*(1410)+{K0S0,pi+},pi-} 0 0.00296544 0.00225542 0 0.014186 0.00247679");
 OptionsParser::setArg( "D0{K*(1410)bar-{K0S0,pi-},pi+} 0 -0.0339155 0.00309512 0 0.0613357 0.0037167");
 OptionsParser::setArg( "D0{K*(1680)bar-{K0S0,pi-},pi+} 0 -0.0535469 0.00651378 0 0.0272353 0.0073212");
 OptionsParser::setArg( "D0{K*(892)+{K0S0,pi+},pi-} 0 0.126313 0.00245399 0 -0.140858 0.00235595");
 OptionsParser::setArg( "D0{K*(892)bar-{K0S0,pi-},pi+} 0 -1.37962 0.00769138 0 1.49371 0.00800201");
 OptionsParser::setArg( "D0{K0S0,PiPi00} 2 1 0 2 0 0");
 OptionsParser::setArg( "D0{K0S0,f(2)(1270)0{pi+,pi-}} 0 -0.125526 0.00221442 0 0.0943573 0.00286431");
 OptionsParser::setArg( "D0{K0S0,omega(782)0{pi+,pi-}} 0 -0.0640864 0.00196373 0 0.12832 0.00170606");
 OptionsParser::setArg( "D0{K0S0,rho(1450)0{pi+,pi-}} 0 0.160532 0.00460311 0 0.0886014 0.00646564");
 OptionsParser::setArg( "D0{K0S0,rho(770)0{pi+,pi-}} 2 1 0 2 0 0");
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
 OptionsParser::setArg( "K");
 OptionsParser::setArg( "K(0)*(1430)+::GLASS::F 0 0.95532 0.01");
 OptionsParser::setArg( "K(0)*(1430)+::GLASS::R 3 1 0");
 OptionsParser::setArg( "K(0)*(1430)+::GLASS::a 0 0.11267 0.01");
 OptionsParser::setArg( "K(0)*(1430)+::GLASS::phiF 0 0.00173 0.01");
 OptionsParser::setArg( "K(0)*(1430)+::GLASS::phiR 0 -1.9145 0.01");
 OptionsParser::setArg( "K(0)*(1430)+::GLASS::r 0 -33.799 0.01");
 OptionsParser::setArg( "K(0)*(1430)+_mass 2 1.44055 0.002");
 OptionsParser::setArg( "K(0)*(1430)+_width 2 0.19261 0.005");
 OptionsParser::setArg( "K(0)*(1430)bar-::GLASS::F 0 0.95532 0.01");
 OptionsParser::setArg( "K(0)*(1430)bar-::GLASS::R 3 1 0");
 OptionsParser::setArg( "K(0)*(1430)bar-::GLASS::a 0 0.11267 0.01");
 OptionsParser::setArg( "K(0)*(1430)bar-::GLASS::phiF 0 0.00173 0.01");
 OptionsParser::setArg( "K(0)*(1430)bar-::GLASS::phiR 0 -1.9145 0.01");
 OptionsParser::setArg( "K(0)*(1430)bar-::GLASS::r 0 -33.799 0.01");
 OptionsParser::setArg( "K(0)*(1430)bar-_mass 2 1.44055 0.002");
 OptionsParser::setArg( "K(0)*(1430)bar-_width 2 0.19261 0.005");
 OptionsParser::setArg( "K(2)*(1430)0_mass 2 1.4256 0");
 OptionsParser::setArg( "K(2)*(1430)0_width 2 0.0985 0");
 OptionsParser::setArg( "K*(1410)+_mass 2 1.414 0");
 OptionsParser::setArg( "K*(1410)+_width 2 0.232 0");
 OptionsParser::setArg( "K*(1410)bar-_mass 2 1.414 0");
 OptionsParser::setArg( "K*(1410)bar-_width 2 0.232 0");
 OptionsParser::setArg( "K*(1680)+_mass 2 1.717 0");
 OptionsParser::setArg( "K*(1680)+_width 2 0.322 0");
 OptionsParser::setArg( "K*(1680)bar-_mass 2 1.717 0");
 OptionsParser::setArg( "K*(1680)bar-_width 2 0.322 0");
 OptionsParser::setArg( "K*(892)+_mass 2 0.89371 5e-05");
 OptionsParser::setArg( "K*(892)bar-_mass 2 0.89371 5e-05");
 OptionsParser::setArg( "K*(892)bar-_width 2 0.04719 0.00011");
 OptionsParser::setArg( "Particle::DefaultModifier BL");
 OptionsParser::setArg( "Particle::SpinFormalism Canonical");
 OptionsParser::setArg( "PiPi00[kMatrix.pole.0]{pi+,pi-} 0 -0.696212 0.0249041 0 -0.564193 0.0150433");
 OptionsParser::setArg( "PiPi00[kMatrix.pole.1]{pi+,pi-} 0 -1.1781 0.0163188 0 -0.387498 0.0128765");
 OptionsParser::setArg( "PiPi00[kMatrix.pole.2]{pi+,pi-} 0 -3.56439 0.100848 0 -0.302991 0.0769034");
 OptionsParser::setArg( "PiPi00[kMatrix.pole.3]{pi+,pi-} 0 -0.654174 0.0322988 0 0.779454 0.0257366");
 OptionsParser::setArg( "PiPi00[kMatrix.prod.0]{pi+,pi-} 0 0.722348 0.0181052 0 0.555636 0.011945");
 OptionsParser::setArg( "PiPi00[kMatrix.prod.1]{pi+,pi-} 0 3.23771 0.0874993 0 0.614543 0.0497138");
 OptionsParser::setArg( "PiPi00[kMatrix.prod.2]{pi+,pi-} 0 1.67044 0.0909612 0 2.7479 0.0945962");
 OptionsParser::setArg( "PiPi00[kMatrix.prod.3]{pi+,pi-} 0 2.36804 0.0672284 0 1.81536 0.0420283");
 OptionsParser::setArg( "PiPi00_s0_prod 3 -0.07 0.03");
 OptionsParser::setArg( "f(2)(1270)_mass 2 1.2751 0");
 OptionsParser::setArg( "f(2)(1270)_width 2 0.1842 0");
 OptionsParser::setArg( "f_scatt0 3 0.23399 0");
 OptionsParser::setArg( "f_scatt1 3 0.15044 0");
 OptionsParser::setArg( "f_scatt2 3 -0.20545 0");
 OptionsParser::setArg( "f_scatt3 3 0.32825 0");
 OptionsParser::setArg( "f_scatt4 3 0.35412 0");
 OptionsParser::setArg( "omega(782)0_mass 2 0.78265 0");
 OptionsParser::setArg( "omega(782)0_width 2 0.00849 0");
 OptionsParser::setArg( "rho(1450)0_mass 2 1.465 0");
 OptionsParser::setArg( "rho(1450)0_width 2 0.4 0");
 OptionsParser::setArg( "rho(770)0_mass 0 0.769374 0.000335341");
 OptionsParser::setArg( "rho(770)0_width 0 0.141979 0.000700587");
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
  BOOST_TEST( std::real(eval) == -0.412796393273831, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == 0.495484947334305, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_K_0_s_1430_barm_GLASS_BL__K0S0_pim__pip__test){
  EventType type({"D0", "K0S0", "pi+", "pi-"});
  Particle p("D0{K(0)*(1430)bar-[GLASS.BL]{K0S0,pi-},pi+}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {-0.632680761611367, -0.317287909488989, 0.180580700476102, 0.883847071614469, 0.679919904250768, 0.268382414427232, -0.281704232040771, 0.795711823504639, -0.0472391426394016, 0.0489054950617566, 0.10112353156467, 0.185281104880893};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == 0.0009216875217859, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == -0.400207874995696, boost::test_tools::tolerance(1e-6)) ;
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
  BOOST_TEST( std::real(eval) == -0.101203142610442, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == -0.000925718156344368, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_Ks_892_p_K0S0_pip__pim__test){
  EventType type({"D0", "K0S0", "pi+", "pi-"});
  Particle p("D0{K*(892)+{K0S0,pi+},pi-}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {-0.632680761611367, -0.317287909488989, 0.180580700476102, 0.883847071614469, 0.679919904250768, 0.268382414427232, -0.281704232040771, 0.795711823504639, -0.0472391426394016, 0.0489054950617566, 0.10112353156467, 0.185281104880893};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == -0.0271545718079767, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == 0.00310822320671134, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_Ks_892_barm_K0S0_pim__pip__test){
  EventType type({"D0", "K0S0", "pi+", "pi-"});
  Particle p("D0{K*(892)bar-{K0S0,pi-},pi+}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {-0.632680761611367, -0.317287909488989, 0.180580700476102, 0.883847071614469, 0.679919904250768, 0.268382414427232, -0.281704232040771, 0.795711823504639, -0.0472391426394016, 0.0489054950617566, 0.10112353156467, 0.185281104880893};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == -0.179829926845627, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == -0.00588133352178236, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_PiPi00_kMatrix_pole_0__pip_pim__K0S0__test){
  EventType type({"D0", "K0S0", "pi+", "pi-"});
  Particle p("D0{PiPi00[kMatrix.pole.0]{pi+,pi-},K0S0}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {-0.632680761611367, -0.317287909488989, 0.180580700476102, 0.883847071614469, 0.679919904250768, 0.268382414427232, -0.281704232040771, 0.795711823504639, -0.0472391426394016, 0.0489054950617566, 0.10112353156467, 0.185281104880893};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == 0.630485472441834, boost::test_tools::tolerance(1e-6)) ;
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
  BOOST_TEST( std::real(eval) == 2.24241098732403e-05, boost::test_tools::tolerance(1e-6)) ;
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
  BOOST_TEST( std::real(eval) == 0.0293052592775153, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == 0.0508160052588403, boost::test_tools::tolerance(1e-6)) ;
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
  BOOST_TEST( std::real(eval) == -0.840447081619105, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == -0.401426499421178, boost::test_tools::tolerance(1e-6)) ;
}

