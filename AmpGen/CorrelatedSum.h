#include "AmpGen/CoherentSum.h"
#ifndef CORRELATEDSUM
#define CORRELATEDSUM

using namespace std;
using namespace AmpGen;

/* 
CorrelatedSum is the Quantum Correlated sum, designed as an input for the QcFitter program. 
This object is designed to take the correlated decays:
P --> D1 D2
D1 --> X1 and D2 --> X2 or D2 --> X1 and D1 --> X2
which will give an amplitude in the X1 phasespace (x1) and the X2 phasespace (x2)

A(x1, x2) = A(x1) B(x2) - C(x1) D(x2) [*]

where A = Amp(D1-->X1), B = Amp(D2 --> X2), C = Amp(D2 --> X1) and D = Amp(D1 --> X2)
the corresponding probability density is thus

P(x1,x2) = |A(x1)|^2 |B(x2)|^2 + |C(x1)|^2 |D(x2)|^2 - 2 Re(A(x1) B*(x2) C(x1) D*(x2))
Therefore to normalise this distribution we need to integrate P(x1, x2):

N = int_x1 int_x2 P(x1, x2) dx1 dx2 
  = NA NB + NC ND - 2 Re(NAC NBD)

where N{FG} = int_x F(x) G*(x) dx
and N{FF} = N{F} = int_x |F(x)|^2 dx

These "N" factors are calculated by summing individual components of the amplitude so 
N{F} = sum_i sum_j g_i g*_j NA_ij
where the indicies are for each amplitude A_i(x) and g_i is the coupling to that component



 */


class CorrelatedSum{
    public:
        //Takes amplitudes - 
        CorrelatedSum();
        
        
        virtual ~CorrelatedSum()=default;
        //real_t operator()( const Event& event1, const Event& event2) const { return prob(event1, event2); }
        //real_t prob(const Event& event1, const Event& event2) const {return std::norm(getVal(event1, event2)/m_norm);}
        void prepare();
        complex_t getVal(const Event& event1, const Event& event2) const;
        complex_t getValNoCache(const Event& event1, const Event& event2) const;
        complex_t getValNoCache(const Event& event1, const Event& event2, const size_t& offset) const;
        real_t norm()  const;
        real_t norm(const Bilinears& norms) const; 
    protected:
        double  m_norm  =    {0};
};

#endif
