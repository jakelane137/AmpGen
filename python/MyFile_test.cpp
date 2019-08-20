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
 OptionsParser::setArg( "CoherentSum::Verbosity 0");
 OptionsParser::setArg( "CouplingConstant::AngularUnits deg");
 OptionsParser::setArg( "CouplingConstant::Coordinates polar");
 OptionsParser::setArg( "D0[D]{K*(892)bar0{K-,pi+},rho(770)0{pi+,pi-}} 2 1.000 0.000 2 0.0 0.0");
 OptionsParser::setArg( "D0[D]{rho(1450)0{pi+,pi-},K*(892)bar0{K-,pi+}} 0 0.649 0.021 0 -15.6 2.0");
 OptionsParser::setArg( "D0[P]{K*(892)bar0{K-,pi+},rho(770)0{pi+,pi-}} 0 0.362 0.002 0 -102.9 0.4");
 OptionsParser::setArg( "D0[P]{rho(1450)0{pi+,pi-},K*(892)bar0{K-,pi+}} 0 0.643 0.006 0 97.3 0.5");
 OptionsParser::setArg( "D0_radius 2 3.7559 0");
 OptionsParser::setArg( "D0{K(1)(1270)bar-,pi+} 0 0.362 0.004 0 114.2 0.8");
 OptionsParser::setArg( "D0{K(1)(1400)bar-{K*(892)bar0{K-,pi+},pi-},pi+} 0 0.127 0.002 0 -169.8 1.1");
 OptionsParser::setArg( "D0{K(1460)bar-,pi+} 0 0.122 0.002 0 172.7 2.2");
 OptionsParser::setArg( "D0{K(2)*(1430)bar-{K*(892)bar0{K-,pi+},pi-},pi+} 0 0.302 0.004 0 -77.7 0.7");
 OptionsParser::setArg( "D0{K*(892)bar0{K-,pi+},PiPi10} 2 1.000 0.000 2 0.0 0.0");
 OptionsParser::setArg( "D0{K*(892)bar0{K-,pi+},rho(770)0{pi+,pi-}} 0 0.196 0.001 0 -22.4 0.4");
 OptionsParser::setArg( "D0{KPi0bar0,PiPi00} 2 1.000 0.000 2 0.0 0.0");
 OptionsParser::setArg( "D0{a(1)(1260)+,K-} 0 0.813 0.006 0 -149.2 0.5");
 OptionsParser::setArg( "D0{rho(1450)0{pi+,pi-},K*(892)bar0{K-,pi+}} 0 0.162 0.005 0 -86.1 1.9");
 OptionsParser::setArg( "D0{rho(770)0{pi+,pi-},KPi1bar0} 0 0.338 0.006 0 73.0 0.8");
 OptionsParser::setArg( "EventType D0 K- pi+ pi+ pi-");
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
 OptionsParser::setArg( "IncludePythonBindings 1");
 OptionsParser::setArg( "K(1)(1270)+::Spline 40 0.6 3.0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline 40 0.6 3.0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::0 2 6.62044e-09 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::1 2 8.1034e-05 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::10 2 0.142193 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::11 2 0.182565 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::12 2 0.231309 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::13 2 0.295139 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::14 2 0.383415 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::15 2 0.507206 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::16 2 0.673751 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::17 2 0.918665 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::18 2 1.18142 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::19 2 1.41125 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::2 2 0.000601093 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::20 2 1.61709 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::21 2 1.80236 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::22 2 1.97044 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::23 2 2.12449 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::24 2 2.26729 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::25 2 2.40124 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::26 2 2.52841 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::27 2 2.65063 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::28 2 2.76952 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::29 2 2.88658 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::3 2 0.00199416 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::30 2 3.0032 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::31 2 3.12073 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::32 2 3.24046 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::33 2 3.36373 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::34 2 3.49188 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::35 2 3.62634 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::36 2 3.76865 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::37 2 3.92048 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::38 2 4.08365 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::39 2 4.26015 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::4 2 0.00478532 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::5 2 0.0097556 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::6 2 0.0184164 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::7 2 0.0348721 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::8 2 0.0672518 0");
 OptionsParser::setArg( "K(1)(1270)bar-::Spline::Gamma::9 2 0.105115 0");
 OptionsParser::setArg( "K(1)(1270)bar-[D;GSpline.EFF]{K*(892)bar0{K-,pi+},pi-} 0 0.769 0.021 0 -19.3 1.6");
 OptionsParser::setArg( "K(1)(1270)bar-[GSpline.EFF]{K*(892)bar0{K-,pi+},pi-} 0 0.388 0.007 0 -172.6 1.1");
 OptionsParser::setArg( "K(1)(1270)bar-[GSpline.EFF]{KPi2bar0[FOCUS.Kpi]{K-,pi+},pi-} 0 0.554 0.010 0 53.2 1.1");
 OptionsParser::setArg( "K(1)(1270)bar-[GSpline.EFF]{omega(782)0{pi+,pi-},K-} 0 0.146 0.005 0 9.0 2.1");
 OptionsParser::setArg( "K(1)(1270)bar-[GSpline.EFF]{rho(1450)0{pi+,pi-},K-} 0 2.016 0.026 0 -119.5 0.9");
 OptionsParser::setArg( "K(1)(1270)bar-[GSpline.EFF]{rho(770)0{pi+,pi-},K-} 2 1.000 0.000 2 0.0 0.0");
 OptionsParser::setArg( "K(1)(1270)bar-_mass 0 1.28981 0.00056");
 OptionsParser::setArg( "K(1)(1270)bar-_radius 2 1.70000 0.00000");
 OptionsParser::setArg( "K(1)(1270)bar-_width 0 0.11611 0.00165");
 OptionsParser::setArg( "K(1460)+::Spline 40 0.6 3.0");
 OptionsParser::setArg( "K(1460)bar-::Spline 40 0.6 3.0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::0 2 8.29869e-06 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::1 2 0.00482634 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::10 2 0.162536 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::11 2 0.195329 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::12 2 0.232727 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::13 2 0.273932 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::14 2 0.318217 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::15 2 0.364931 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::16 2 0.413518 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::17 2 0.463526 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::18 2 0.514629 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::19 2 0.566657 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::2 2 0.0176071 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::20 2 0.619642 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::21 2 0.67389 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::22 2 0.730087 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::23 2 0.789463 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::24 2 0.853918 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::25 2 0.925529 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::26 2 0.999944 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::27 2 1.05939 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::28 2 1.11703 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::29 2 1.17704 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::3 2 0.0349086 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::30 2 1.2408 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::31 2 1.30884 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::32 2 1.37941 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::33 2 1.4487 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::34 2 1.51729 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::35 2 1.58528 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::36 2 1.6526 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::37 2 1.71901 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::38 2 1.78418 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::39 2 1.8476 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::4 2 0.0532389 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::5 2 0.0703992 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::6 2 0.0855373 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::7 2 0.0991271 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::8 2 0.114209 0");
 OptionsParser::setArg( "K(1460)bar-::Spline::Gamma::9 2 0.135205 0");
 OptionsParser::setArg( "K(1460)bar-[GSpline.EFF]{K*(892)bar0{K-,pi+},pi-} 2 1.000 0.000 2 0.0 0.0");
 OptionsParser::setArg( "K(1460)bar-[GSpline.EFF]{PiPi30,K-} 2 1.000 0.000 2 0.0 0.0");
 OptionsParser::setArg( "K(1460)bar-_mass 0 1.48240 0.00358");
 OptionsParser::setArg( "K(1460)bar-_radius 2 1.70000 0.00000");
 OptionsParser::setArg( "K(1460)bar-_width 0 0.33560 0.00620");
 OptionsParser::setArg( "KPi0bar0[FOCUS.I32]{K-,pi+} 0 0.870 0.010 0 -149.2 0.7");
 OptionsParser::setArg( "KPi0bar0[FOCUS.KEta]{K-,pi+} 0 2.614 0.141 0 -19.1 2.4");
 OptionsParser::setArg( "KPi0bar0[FOCUS.Kpi]{K-,pi+} 2 1.000 0.000 2 0.0 0.0");
 OptionsParser::setArg( "KPi1bar0[FOCUS.I32]{K-,pi+} 0 1.073 0.008 0 -130.9 0.5");
 OptionsParser::setArg( "KPi1bar0[FOCUS.Kpi]{K-,pi+} 2 1.000 0.000 2 0.0 0.0");
 OptionsParser::setArg( "Output MyFile.cpp");
 OptionsParser::setArg( "OutputEvents events.csv");
 OptionsParser::setArg( "PiPi00[kMatrix.pole.1]{pi+,pi-} 0 0.554 0.009 0 35.3 0.7");
 OptionsParser::setArg( "PiPi00[kMatrix.prod.0]{pi+,pi-} 0 0.082 0.001 0 -147.0 0.7");
 OptionsParser::setArg( "PiPi00_s0_prod 2 -0.196872 0");
 OptionsParser::setArg( "PiPi10[kMatrix.pole.1]{pi+,pi-} 0 0.305 0.011 0 65.6 1.5");
 OptionsParser::setArg( "PiPi10[kMatrix.prod.0]{pi+,pi-} 0 0.261 0.005 0 -149.0 0.9");
 OptionsParser::setArg( "PiPi10_s0_prod 2 -0.950027 0");
 OptionsParser::setArg( "PiPi20[kMatrix.pole.0]{pi+,pi-} 0 0.291 0.007 0 165.8 1.3");
 OptionsParser::setArg( "PiPi20[kMatrix.pole.1]{pi+,pi-} 0 0.991 0.018 0 -22.2 1.0");
 OptionsParser::setArg( "PiPi20[kMatrix.prod.0]{pi+,pi-} 0 0.117 0.002 0 170.5 1.2");
 OptionsParser::setArg( "PiPi20_s0_prod 2 -0.165753 0");
 OptionsParser::setArg( "PiPi30[kMatrix.pole.0]{pi+,pi-} 0 0.315 0.010 0 46.7 1.9");
 OptionsParser::setArg( "PiPi30[kMatrix.pole.1]{pi+,pi-} 0 0.813 0.032 0 112.9 2.6");
 OptionsParser::setArg( "PiPi30[kMatrix.prod.1]{pi+,pi-} 0 1.819 0.059 0 -80.8 2.2");
 OptionsParser::setArg( "PiPi30_s0_prod 2 -0.0676736 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline 40 0.18412 1.9");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::0 2 1.23936e-06 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::1 2 0.000223871 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::10 2 0.0832521 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::11 2 0.115406 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::12 2 0.159329 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::13 2 0.218726 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::14 2 0.295241 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::15 2 0.384295 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::16 2 0.475641 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::17 2 0.560491 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::18 2 0.635169 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::19 2 0.699435 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::2 2 0.00119329 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::20 2 0.754352 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::21 2 0.801255 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::22 2 0.841402 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::23 2 0.875894 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::24 2 0.905694 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::25 2 0.931693 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::26 2 0.954723 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::27 2 0.97539 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::28 2 0.994175 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::29 2 1.01148 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::3 2 0.00326416 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::30 2 1.02765 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::31 2 1.04297 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::32 2 1.05768 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::33 2 1.07198 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::34 2 1.08602 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::35 2 1.09995 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::36 2 1.11387 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::37 2 1.12789 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::38 2 1.14208 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::39 2 1.15651 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::4 2 0.00671647 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::5 2 0.0118496 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::6 2 0.0190462 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::7 2 0.0288353 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::8 2 0.0419745 0");
 OptionsParser::setArg( "a(1)(1260)+::Spline::Gamma::9 2 0.0595699 0");
 OptionsParser::setArg( "a(1)(1260)+[D;GSpline.EFF]{rho(770)0{pi+,pi-},pi+} 0 0.582 0.011 0 -152.8 1.2");
 OptionsParser::setArg( "a(1)(1260)+[GSpline.EFF]{PiPi20,pi+} 2 1.000 0.000 2 0.0 0.0");
 OptionsParser::setArg( "a(1)(1260)+[GSpline.EFF]{rho(770)0{pi+,pi-},pi+} 2 1.000 0.000 2 0.0 0.0");
 OptionsParser::setArg( "a(1)(1260)+_mass 0 1.19505 0.00105");
 OptionsParser::setArg( "a(1)(1260)+_radius 2 1.70000 0.00000");
 OptionsParser::setArg( "a(1)(1260)+_width 0 0.42201 0.00210");
 OptionsParser::setArg( "a(1)(1260)-::Spline 40 0.18412 1.9");
 OptionsParser::setArg( "f_scatt0 3 0.23399 0");
 OptionsParser::setArg( "f_scatt1 3 0.15044 0");
 OptionsParser::setArg( "f_scatt2 3 -0.20545 0");
 OptionsParser::setArg( "f_scatt3 3 0.32825 0");
 OptionsParser::setArg( "f_scatt4 3 0.35412 0");
 OptionsParser::setArg( "s0_prod 3 -1 0");
 OptionsParser::setArg( "s0_scatt 3 -3.92637 0");
 OptionsParser::setArg( "sA 3 1 0");

}

BOOST_AUTO_TEST_CASE( D0_D__Ks_892_bar0_Km_pip__rho_770_0_pip_pim___test){
  EventType type({"D0", "K-", "pi+", "pi+", "pi-"});
  Particle p("D0[D]{K*(892)bar0{K-,pi+},rho(770)0{pi+,pi-}}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {0.228270996790714, 0.235158203267673, -0.30579218343989, 0.666807969599825, 0.0865495211976492, 0.289201986936342, 0.278700481936464, 0.433915202135533, -0.043403693477507, -0.414060757164493, 0.0179885466205549, 0.439469696550143, -0.271416824510856, -0.110299433039523, 0.00910315488287075, 0.324647131714499};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == 0.0171995095647245, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == -0.000972693302244763, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_D__rho_1450_0_pip_pim__Ks_892_bar0_Km_pip___test){
  EventType type({"D0", "K-", "pi+", "pi+", "pi-"});
  Particle p("D0[D]{rho(1450)0{pi+,pi-},K*(892)bar0{K-,pi+}}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {0.228270996790714, 0.235158203267673, -0.30579218343989, 0.666807969599825, 0.0865495211976492, 0.289201986936342, 0.278700481936464, 0.433915202135533, -0.043403693477507, -0.414060757164493, 0.0179885466205549, 0.439469696550143, -0.271416824510856, -0.110299433039523, 0.00910315488287075, 0.324647131714499};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == 0.00654852846026193, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == -0.00302370335140033, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_P__Ks_892_bar0_Km_pip__rho_770_0_pip_pim___test){
  EventType type({"D0", "K-", "pi+", "pi+", "pi-"});
  Particle p("D0[P]{K*(892)bar0{K-,pi+},rho(770)0{pi+,pi-}}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {0.228270996790714, 0.235158203267673, -0.30579218343989, 0.666807969599825, 0.0865495211976492, 0.289201986936342, 0.278700481936464, 0.433915202135533, -0.043403693477507, -0.414060757164493, 0.0179885466205549, 0.439469696550143, -0.271416824510856, -0.110299433039523, 0.00910315488287075, 0.324647131714499};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == -0.0142706961605909, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == 0.162964412462887, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_P__rho_1450_0_pip_pim__Ks_892_bar0_Km_pip___test){
  EventType type({"D0", "K-", "pi+", "pi+", "pi-"});
  Particle p("D0[P]{rho(1450)0{pi+,pi-},K*(892)bar0{K-,pi+}}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {0.228270996790714, 0.235158203267673, -0.30579218343989, 0.666807969599825, 0.0865495211976492, 0.289201986936342, 0.278700481936464, 0.433915202135533, -0.043403693477507, -0.414060757164493, 0.0179885466205549, 0.439469696550143, -0.271416824510856, -0.110299433039523, 0.00910315488287075, 0.324647131714499};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == -0.0347257647629937, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == 0.0895887095558543, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_K_1__1270_barm_D_GSpline_EFF__Ks_892_bar0_Km_pip__pim__pip__test){
  EventType type({"D0", "K-", "pi+", "pi+", "pi-"});
  Particle p("D0{K(1)(1270)bar-[D;GSpline.EFF]{K*(892)bar0{K-,pi+},pi-},pi+}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {0.228270996790714, 0.235158203267673, -0.30579218343989, 0.666807969599825, 0.0865495211976492, 0.289201986936342, 0.278700481936464, 0.433915202135533, -0.043403693477507, -0.414060757164493, 0.0179885466205549, 0.439469696550143, -0.271416824510856, -0.110299433039523, 0.00910315488287075, 0.324647131714499};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == -0.00144167797282099, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == -0.01006009419213, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_K_1__1270_barm_GSpline_EFF__Ks_892_bar0_Km_pip__pim__pip__test){
  EventType type({"D0", "K-", "pi+", "pi+", "pi-"});
  Particle p("D0{K(1)(1270)bar-[GSpline.EFF]{K*(892)bar0{K-,pi+},pi-},pi+}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {0.228270996790714, 0.235158203267673, -0.30579218343989, 0.666807969599825, 0.0865495211976492, 0.289201986936342, 0.278700481936464, 0.433915202135533, -0.043403693477507, -0.414060757164493, 0.0179885466205549, 0.439469696550143, -0.271416824510856, -0.110299433039523, 0.00910315488287075, 0.324647131714499};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == -0.0138678844666404, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == -0.155691499469263, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_K_1__1270_barm_GSpline_EFF__KPi2bar0_FOCUS_Kpi__Km_pip__pim__pip__test){
  EventType type({"D0", "K-", "pi+", "pi+", "pi-"});
  Particle p("D0{K(1)(1270)bar-[GSpline.EFF]{KPi2bar0[FOCUS.Kpi]{K-,pi+},pi-},pi+}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {0.228270996790714, 0.235158203267673, -0.30579218343989, 0.666807969599825, 0.0865495211976492, 0.289201986936342, 0.278700481936464, 0.433915202135533, -0.043403693477507, -0.414060757164493, 0.0179885466205549, 0.439469696550143, -0.271416824510856, -0.110299433039523, 0.00910315488287075, 0.324647131714499};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == 0.122635575013061, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == -0.0274476181020119, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_K_1__1270_barm_GSpline_EFF__omega_782_0_pip_pim__Km__pip__test){
  EventType type({"D0", "K-", "pi+", "pi+", "pi-"});
  Particle p("D0{K(1)(1270)bar-[GSpline.EFF]{omega(782)0{pi+,pi-},K-},pi+}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {0.228270996790714, 0.235158203267673, -0.30579218343989, 0.666807969599825, 0.0865495211976492, 0.289201986936342, 0.278700481936464, 0.433915202135533, -0.043403693477507, -0.414060757164493, 0.0179885466205549, 0.439469696550143, -0.271416824510856, -0.110299433039523, 0.00910315488287075, 0.324647131714499};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == 0.0242482757531935, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == -0.030300005448681, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_K_1__1270_barm_GSpline_EFF__rho_1450_0_pip_pim__Km__pip__test){
  EventType type({"D0", "K-", "pi+", "pi+", "pi-"});
  Particle p("D0{K(1)(1270)bar-[GSpline.EFF]{rho(1450)0{pi+,pi-},K-},pi+}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {0.228270996790714, 0.235158203267673, -0.30579218343989, 0.666807969599825, 0.0865495211976492, 0.289201986936342, 0.278700481936464, 0.433915202135533, -0.043403693477507, -0.414060757164493, 0.0179885466205549, 0.439469696550143, -0.271416824510856, -0.110299433039523, 0.00910315488287075, 0.324647131714499};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == 0.0404685133876986, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == -0.0444853010151785, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_K_1__1270_barm_GSpline_EFF__rho_770_0_pip_pim__Km__pip__test){
  EventType type({"D0", "K-", "pi+", "pi+", "pi-"});
  Particle p("D0{K(1)(1270)bar-[GSpline.EFF]{rho(770)0{pi+,pi-},K-},pi+}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {0.228270996790714, 0.235158203267673, -0.30579218343989, 0.666807969599825, 0.0865495211976492, 0.289201986936342, 0.278700481936464, 0.433915202135533, -0.043403693477507, -0.414060757164493, 0.0179885466205549, 0.439469696550143, -0.271416824510856, -0.110299433039523, 0.00910315488287075, 0.324647131714499};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == 0.135800111537361, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == -0.0789536843011126, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_K_1__1400_barm_Ks_892_bar0_Km_pip__pim__pip__test){
  EventType type({"D0", "K-", "pi+", "pi+", "pi-"});
  Particle p("D0{K(1)(1400)bar-{K*(892)bar0{K-,pi+},pi-},pi+}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {0.228270996790714, 0.235158203267673, -0.30579218343989, 0.666807969599825, 0.0865495211976492, 0.289201986936342, 0.278700481936464, 0.433915202135533, -0.043403693477507, -0.414060757164493, 0.0179885466205549, 0.439469696550143, -0.271416824510856, -0.110299433039523, 0.00910315488287075, 0.324647131714499};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == -0.289694861442217, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == -0.124062978534655, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_K_1460_barm_GSpline_EFF__Ks_892_bar0_Km_pip__pim__pip__test){
  EventType type({"D0", "K-", "pi+", "pi+", "pi-"});
  Particle p("D0{K(1460)bar-[GSpline.EFF]{K*(892)bar0{K-,pi+},pi-},pi+}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {0.228270996790714, 0.235158203267673, -0.30579218343989, 0.666807969599825, 0.0865495211976492, 0.289201986936342, 0.278700481936464, 0.433915202135533, -0.043403693477507, -0.414060757164493, 0.0179885466205549, 0.439469696550143, -0.271416824510856, -0.110299433039523, 0.00910315488287075, 0.324647131714499};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == 0.0279412006322049, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == 0.0641363733157935, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_K_1460_barm_GSpline_EFF__PiPi30_kMatrix_pole_0__pip_pim__Km__pip__test){
  EventType type({"D0", "K-", "pi+", "pi+", "pi-"});
  Particle p("D0{K(1460)bar-[GSpline.EFF]{PiPi30[kMatrix.pole.0]{pi+,pi-},K-},pi+}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {0.228270996790714, 0.235158203267673, -0.30579218343989, 0.666807969599825, 0.0865495211976492, 0.289201986936342, 0.278700481936464, 0.433915202135533, -0.043403693477507, -0.414060757164493, 0.0179885466205549, 0.439469696550143, -0.271416824510856, -0.110299433039523, 0.00910315488287075, 0.324647131714499};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == -0.0560126423630965, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == 1.99529410054675, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_K_1460_barm_GSpline_EFF__PiPi30_kMatrix_pole_1__pip_pim__Km__pip__test){
  EventType type({"D0", "K-", "pi+", "pi+", "pi-"});
  Particle p("D0{K(1460)bar-[GSpline.EFF]{PiPi30[kMatrix.pole.1]{pi+,pi-},K-},pi+}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {0.228270996790714, 0.235158203267673, -0.30579218343989, 0.666807969599825, 0.0865495211976492, 0.289201986936342, 0.278700481936464, 0.433915202135533, -0.043403693477507, -0.414060757164493, 0.0179885466205549, 0.439469696550143, -0.271416824510856, -0.110299433039523, 0.00910315488287075, 0.324647131714499};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == -0.0255475385322314, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == 0.913467021179523, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_K_1460_barm_GSpline_EFF__PiPi30_kMatrix_prod_1__pip_pim__Km__pip__test){
  EventType type({"D0", "K-", "pi+", "pi+", "pi-"});
  Particle p("D0{K(1460)bar-[GSpline.EFF]{PiPi30[kMatrix.prod.1]{pi+,pi-},K-},pi+}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {0.228270996790714, 0.235158203267673, -0.30579218343989, 0.666807969599825, 0.0865495211976492, 0.289201986936342, 0.278700481936464, 0.433915202135533, -0.043403693477507, -0.414060757164493, 0.0179885466205549, 0.439469696550143, -0.271416824510856, -0.110299433039523, 0.00910315488287075, 0.324647131714499};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == 0.00652337857806248, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == 0.674779545252473, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_K_2_s_1430_barm_Ks_892_bar0_Km_pip__pim__pip__test){
  EventType type({"D0", "K-", "pi+", "pi+", "pi-"});
  Particle p("D0{K(2)*(1430)bar-{K*(892)bar0{K-,pi+},pi-},pi+}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {0.228270996790714, 0.235158203267673, -0.30579218343989, 0.666807969599825, 0.0865495211976492, 0.289201986936342, 0.278700481936464, 0.433915202135533, -0.043403693477507, -0.414060757164493, 0.0179885466205549, 0.439469696550143, -0.271416824510856, -0.110299433039523, 0.00910315488287075, 0.324647131714499};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == 0.255178100522318, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == -0.144428709208459, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_Ks_892_bar0_Km_pip__PiPi10_kMatrix_pole_1__pip_pim___test){
  EventType type({"D0", "K-", "pi+", "pi+", "pi-"});
  Particle p("D0{K*(892)bar0{K-,pi+},PiPi10[kMatrix.pole.1]{pi+,pi-}}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {0.228270996790714, 0.235158203267673, -0.30579218343989, 0.666807969599825, 0.0865495211976492, 0.289201986936342, 0.278700481936464, 0.433915202135533, -0.043403693477507, -0.414060757164493, 0.0179885466205549, 0.439469696550143, -0.271416824510856, -0.110299433039523, 0.00910315488287075, 0.324647131714499};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == -0.0507309585940436, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == 0.0209134852430491, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_Ks_892_bar0_Km_pip__PiPi10_kMatrix_prod_0__pip_pim___test){
  EventType type({"D0", "K-", "pi+", "pi+", "pi-"});
  Particle p("D0{K*(892)bar0{K-,pi+},PiPi10[kMatrix.prod.0]{pi+,pi-}}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {0.228270996790714, 0.235158203267673, -0.30579218343989, 0.666807969599825, 0.0865495211976492, 0.289201986936342, 0.278700481936464, 0.433915202135533, -0.043403693477507, -0.414060757164493, 0.0179885466205549, 0.439469696550143, -0.271416824510856, -0.110299433039523, 0.00910315488287075, 0.324647131714499};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == -0.122734162567721, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == 0.0516214570508781, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_Ks_892_bar0_Km_pip__rho_770_0_pip_pim___test){
  EventType type({"D0", "K-", "pi+", "pi+", "pi-"});
  Particle p("D0{K*(892)bar0{K-,pi+},rho(770)0{pi+,pi-}}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {0.228270996790714, 0.235158203267673, -0.30579218343989, 0.666807969599825, 0.0865495211976492, 0.289201986936342, 0.278700481936464, 0.433915202135533, -0.043403693477507, -0.414060757164493, 0.0179885466205549, 0.439469696550143, -0.271416824510856, -0.110299433039523, 0.00910315488287075, 0.324647131714499};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == 0.159206907266248, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == -0.0423246968415026, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_PiPi00_kMatrix_pole_1__pip_pim__KPi0bar0_FOCUS_I32__Km_pip___test){
  EventType type({"D0", "K-", "pi+", "pi+", "pi-"});
  Particle p("D0{PiPi00[kMatrix.pole.1]{pi+,pi-},KPi0bar0[FOCUS.I32]{K-,pi+}}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {0.228270996790714, 0.235158203267673, -0.30579218343989, 0.666807969599825, 0.0865495211976492, 0.289201986936342, 0.278700481936464, 0.433915202135533, -0.043403693477507, -0.414060757164493, 0.0179885466205549, 0.439469696550143, -0.271416824510856, -0.110299433039523, 0.00910315488287075, 0.324647131714499};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == 0.670983116424345, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == 0.384410961016162, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_PiPi00_kMatrix_pole_1__pip_pim__KPi0bar0_FOCUS_KEta__Km_pip___test){
  EventType type({"D0", "K-", "pi+", "pi+", "pi-"});
  Particle p("D0{PiPi00[kMatrix.pole.1]{pi+,pi-},KPi0bar0[FOCUS.KEta]{K-,pi+}}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {0.228270996790714, 0.235158203267673, -0.30579218343989, 0.666807969599825, 0.0865495211976492, 0.289201986936342, 0.278700481936464, 0.433915202135533, -0.043403693477507, -0.414060757164493, 0.0179885466205549, 0.439469696550143, -0.271416824510856, -0.110299433039523, 0.00910315488287075, 0.324647131714499};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == -7.85217419961927e-05, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == 0.0612916848492701, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_PiPi00_kMatrix_pole_1__pip_pim__KPi0bar0_FOCUS_Kpi__Km_pip___test){
  EventType type({"D0", "K-", "pi+", "pi+", "pi-"});
  Particle p("D0{PiPi00[kMatrix.pole.1]{pi+,pi-},KPi0bar0[FOCUS.Kpi]{K-,pi+}}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {0.228270996790714, 0.235158203267673, -0.30579218343989, 0.666807969599825, 0.0865495211976492, 0.289201986936342, 0.278700481936464, 0.433915202135533, -0.043403693477507, -0.414060757164493, 0.0179885466205549, 0.439469696550143, -0.271416824510856, -0.110299433039523, 0.00910315488287075, 0.324647131714499};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == -0.050113099649476, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == 0.804534174602086, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_PiPi00_kMatrix_prod_0__pip_pim__KPi0bar0_FOCUS_I32__Km_pip___test){
  EventType type({"D0", "K-", "pi+", "pi+", "pi-"});
  Particle p("D0{PiPi00[kMatrix.prod.0]{pi+,pi-},KPi0bar0[FOCUS.I32]{K-,pi+}}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {0.228270996790714, 0.235158203267673, -0.30579218343989, 0.666807969599825, 0.0865495211976492, 0.289201986936342, 0.278700481936464, 0.433915202135533, -0.043403693477507, -0.414060757164493, 0.0179885466205549, 0.439469696550143, -0.271416824510856, -0.110299433039523, 0.00910315488287075, 0.324647131714499};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == 2.10729135809801, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == 0.980127777437068, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_PiPi00_kMatrix_prod_0__pip_pim__KPi0bar0_FOCUS_KEta__Km_pip___test){
  EventType type({"D0", "K-", "pi+", "pi+", "pi-"});
  Particle p("D0{PiPi00[kMatrix.prod.0]{pi+,pi-},KPi0bar0[FOCUS.KEta]{K-,pi+}}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {0.228270996790714, 0.235158203267673, -0.30579218343989, 0.666807969599825, 0.0865495211976492, 0.289201986936342, 0.278700481936464, 0.433915202135533, -0.043403693477507, -0.414060757164493, 0.0179885466205549, 0.439469696550143, -0.271416824510856, -0.110299433039523, 0.00910315488287075, 0.324647131714499};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == 0.0254911165281341, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == 0.196659106735301, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_PiPi00_kMatrix_prod_0__pip_pim__KPi0bar0_FOCUS_Kpi__Km_pip___test){
  EventType type({"D0", "K-", "pi+", "pi+", "pi-"});
  Particle p("D0{PiPi00[kMatrix.prod.0]{pi+,pi-},KPi0bar0[FOCUS.Kpi]{K-,pi+}}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {0.228270996790714, 0.235158203267673, -0.30579218343989, 0.666807969599825, 0.0865495211976492, 0.289201986936342, 0.278700481936464, 0.433915202135533, -0.043403693477507, -0.414060757164493, 0.0179885466205549, 0.439469696550143, -0.271416824510856, -0.110299433039523, 0.00910315488287075, 0.324647131714499};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == 0.200758378154312, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == 2.3918268579923, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_a_1__1260_p_D_GSpline_EFF__rho_770_0_pip_pim__pip__Km__test){
  EventType type({"D0", "K-", "pi+", "pi+", "pi-"});
  Particle p("D0{a(1)(1260)+[D;GSpline.EFF]{rho(770)0{pi+,pi-},pi+},K-}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {0.228270996790714, 0.235158203267673, -0.30579218343989, 0.666807969599825, 0.0865495211976492, 0.289201986936342, 0.278700481936464, 0.433915202135533, -0.043403693477507, -0.414060757164493, 0.0179885466205549, 0.439469696550143, -0.271416824510856, -0.110299433039523, 0.00910315488287075, 0.324647131714499};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == 0.00311368321715661, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == 0.00292119799701798, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_a_1__1260_p_GSpline_EFF__rho_770_0_pip_pim__pip__Km__test){
  EventType type({"D0", "K-", "pi+", "pi+", "pi-"});
  Particle p("D0{a(1)(1260)+[GSpline.EFF]{rho(770)0{pi+,pi-},pi+},K-}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {0.228270996790714, 0.235158203267673, -0.30579218343989, 0.666807969599825, 0.0865495211976492, 0.289201986936342, 0.278700481936464, 0.433915202135533, -0.043403693477507, -0.414060757164493, 0.0179885466205549, 0.439469696550143, -0.271416824510856, -0.110299433039523, 0.00910315488287075, 0.324647131714499};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == -0.00396694983361761, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == 0.113898981345305, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_a_1__1260_p_GSpline_EFF__PiPi20_kMatrix_pole_0__pip_pim__pip__Km__test){
  EventType type({"D0", "K-", "pi+", "pi+", "pi-"});
  Particle p("D0{a(1)(1260)+[GSpline.EFF]{PiPi20[kMatrix.pole.0]{pi+,pi-},pi+},K-}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {0.228270996790714, 0.235158203267673, -0.30579218343989, 0.666807969599825, 0.0865495211976492, 0.289201986936342, 0.278700481936464, 0.433915202135533, -0.043403693477507, -0.414060757164493, 0.0179885466205549, 0.439469696550143, -0.271416824510856, -0.110299433039523, 0.00910315488287075, 0.324647131714499};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == -0.0283006182472249, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == -0.0805143901137985, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_a_1__1260_p_GSpline_EFF__PiPi20_kMatrix_pole_1__pip_pim__pip__Km__test){
  EventType type({"D0", "K-", "pi+", "pi+", "pi-"});
  Particle p("D0{a(1)(1260)+[GSpline.EFF]{PiPi20[kMatrix.pole.1]{pi+,pi-},pi+},K-}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {0.228270996790714, 0.235158203267673, -0.30579218343989, 0.666807969599825, 0.0865495211976492, 0.289201986936342, 0.278700481936464, 0.433915202135533, -0.043403693477507, -0.414060757164493, 0.0179885466205549, 0.439469696550143, -0.271416824510856, -0.110299433039523, 0.00910315488287075, 0.324647131714499};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == -0.0129395476019332, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == -0.0369114969939935, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_a_1__1260_p_GSpline_EFF__PiPi20_kMatrix_prod_0__pip_pim__pip__Km__test){
  EventType type({"D0", "K-", "pi+", "pi+", "pi-"});
  Particle p("D0{a(1)(1260)+[GSpline.EFF]{PiPi20[kMatrix.prod.0]{pi+,pi-},pi+},K-}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {0.228270996790714, 0.235158203267673, -0.30579218343989, 0.666807969599825, 0.0865495211976492, 0.289201986936342, 0.278700481936464, 0.433915202135533, -0.043403693477507, -0.414060757164493, 0.0179885466205549, 0.439469696550143, -0.271416824510856, -0.110299433039523, 0.00910315488287075, 0.324647131714499};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == 0.00969404653157287, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == -0.257181284776112, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_rho_1450_0_pip_pim__Ks_892_bar0_Km_pip___test){
  EventType type({"D0", "K-", "pi+", "pi+", "pi-"});
  Particle p("D0{rho(1450)0{pi+,pi-},K*(892)bar0{K-,pi+}}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {0.228270996790714, 0.235158203267673, -0.30579218343989, 0.666807969599825, 0.0865495211976492, 0.289201986936342, 0.278700481936464, 0.433915202135533, -0.043403693477507, -0.414060757164493, 0.0179885466205549, 0.439469696550143, -0.271416824510856, -0.110299433039523, 0.00910315488287075, 0.324647131714499};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == 0.0666354719114899, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == -0.0458825021231428, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_rho_770_0_pip_pim__KPi1bar0_FOCUS_I32__Km_pip___test){
  EventType type({"D0", "K-", "pi+", "pi+", "pi-"});
  Particle p("D0{rho(770)0{pi+,pi-},KPi1bar0[FOCUS.I32]{K-,pi+}}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {0.228270996790714, 0.235158203267673, -0.30579218343989, 0.666807969599825, 0.0865495211976492, 0.289201986936342, 0.278700481936464, 0.433915202135533, -0.043403693477507, -0.414060757164493, 0.0179885466205549, 0.439469696550143, -0.271416824510856, -0.110299433039523, 0.00910315488287075, 0.324647131714499};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == -0.0996713672879522, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == -0.00322508122977461, boost::test_tools::tolerance(1e-6)) ;
}

BOOST_AUTO_TEST_CASE( D0_rho_770_0_pip_pim__KPi1bar0_FOCUS_Kpi__Km_pip___test){
  EventType type({"D0", "K-", "pi+", "pi+", "pi-"});
  Particle p("D0{rho(770)0{pi+,pi-},KPi1bar0[FOCUS.Kpi]{K-,pi+}}", type.finalStates());
  setupOptions();
  MinuitParameterSet mps; mps.loadFromStream();
  double event[] = {0.228270996790714, 0.235158203267673, -0.30579218343989, 0.666807969599825, 0.0865495211976492, 0.289201986936342, 0.278700481936464, 0.433915202135533, -0.043403693477507, -0.414060757164493, 0.0179885466205549, 0.439469696550143, -0.271416824510856, -0.110299433039523, 0.00910315488287075, 0.324647131714499};
  auto expr = make_expression<complex_t>(p.getExpression(), p.decayDescriptor(), type.getEventFormat(), mps);
  auto eval = expr(event);
  BOOST_TEST( std::real(eval) == -0.0387165254085704, boost::test_tools::tolerance(1e-6)) ;
  BOOST_TEST( std::imag(eval) == -0.0998489672951287, boost::test_tools::tolerance(1e-6)) ;
}

