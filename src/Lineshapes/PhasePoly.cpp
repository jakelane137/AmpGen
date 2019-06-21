#include <stddef.h>
#include <string>
#include <vector>

#include "AmpGen/Expression.h"
#include "AmpGen/Factory.h"
#include "AmpGen/Lineshapes.h"
#include "AmpGen/Tensor.h"
#include "AmpGen/NamedParameter.h"

#include <cmath>

using namespace AmpGen;
using namespace AmpGen::fcn;

DEFINE_GENERIC_SHAPE( PhasePoly )
{
    INFO("2D exponential Polynomial of the form e^(iP(x,y)), used to correct the fitted phase of D->KsPiPi decays ");
    //Degree for our 2D polynomial - N
    std::cout<<"Starting to make Phase Poly\n";
    unsigned int degree = NamedParameter<unsigned int>( lineshapeModifier + "::Degree" );
    //vector of vectors 
    std::vector<std::vector<Expression> > param;
    auto i=0;
    while (i!= degree){
        auto param_i = parameterVector(lineshapeModifier + "_c" + std::to_string(i), degree + 1 - i);
        i++;
        param.push_back(param_i);
    }

    //4D momentum tensor for 

    Tensor P (Tensor::dim(4));
    for ( auto& ip : p ) P = P + ip;
    //For simplicity we will use x and y as the input for the polynomial not m^2_+, m^2_-!
    Expression x = dot(p[0] + p[1], p[0] + p[1]);
    Expression y = dot(p[0] + p[2], p[0] + p[2]);
   
    Expression sum;
    //For a 2D polynomial we take the x projections so V_i = (c_i0, ci1,.., c_im), where m = N+1 - i
    //Then we do the y polynomial for each x^i, then sum all of the y polynomials.
    //i.e. sum_0 = c_00 + c_01 y + c_02 y^2 ...
    //     sum_1 = c_10 x + c_11 xy + c12 x y^2 + ...
    //     sum_2 = c_20 x^2 + c_21 x^2 y + c_22 x^2 y^2 + ...
    i=0;
    while (i!=degree){
        Expression sum_i;
        for (int j=0; j<param[i].size(); j++){
            sum_i += param[i][j] * pow(x, i) * pow(y, j);
        }
        i++;
        sum += sum_i;
    }
    Expression amp = exp(std::complex<double>(0,1) * sum);
    return amp;
}