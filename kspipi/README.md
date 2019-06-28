Amplitude Analysis for D->KsPiPi
================================
The analysis in this folder is designed to model the phase space of the $D \to K_S^0 \pi^+\pi^-$ decay, where $D$ is either a $D^0$ or $\bar{D}^0$ meson.

 The phase space for this three body decay (or indeed any three body decay $X\to abc$) has two dimensions, which we will parameterize with the variables $m^2_+ = m^2_{K_S^0 \pi^+}$ and $m^2_- = m^2_{K_S^0 \pi^-}$ which are the invariant masses of the combination of $K_S^0 \pi^+$ and $K_S^0 \pi^-$ respectively. These variables are refered to as ''Dalitz'' variables, the probability distribution of the decay $D\to K_S^0 \pi^+ \pi^-$, $P(m_+^2, m_-^2)$ is referred to as a ''Dalitz Plot''. The variables $m^2_{K_S^0 \pi^+}$ and $m^2_{K_S^0 \pi^-}$ are chosen due to the property
 $P_{D^0}(m^2_-, m^2_+) = P_{\bar{D}^0}(m^2_+, m^2_-)$, assuming the decay obeys $CP$ symmetry.

  The coordinates $(x,y)$ and $(m^2_+,m^2_-)$ are sometimes used interchangeably, however these are not to be confused with the neutral charm mixing parameters $x=\frac{\Delta m}{\Gamma}$ and $y=\frac{\Delta \Gamma}{\Gamma}$ where $\Delta m$ is difference in mass between the two mass eigenstates, $D_1, D_2$ of neutral charm meson and $\Delta \Gamma$ is similarly the difference in decay width between the two mass eigenstates. In this project, the variables, $x$ and $y$ will refer to the neutral charm mixing parameters and the variables $(m^2_+,m^2_-)$ will refer to coordinates in the Dalitz plot.

  Amplitude for the $D\to K_S^0 \pi^+ \pi^-$ decay
  ------------------------------------------------
  The differential decay rate for $D \to K_S^0 \pi^+ \pi^-$, 
  
  $$\Gamma_{D\to K_S^0 \pi^+ \pi^-}(m^2_+, m^2_-) \propto\left |A_D(m^2_+, m^2_-)\right|^2dm^2_+ dm^2_-.$$ (1)
  
  In a three body decay one usually has $A(m^2_+, m^2_-) = C$ where $C$ is independent of the position in the phase space. This is the case when the $D$ meson decays directly to the final state $K_S^0 \pi^+ \pi^-$, however there exists several two-body intermediate states the $D$ meson can decay to before decaying into the final state.
  
  The possible intermediate states that the $D$ meson can decay into are either
  1. $\rho^0 \to \pi^+ \pi^-$ resonances 

  $$D \to K_S^0 \left(\rho^0 \to \pi^+ \pi^-\right).$$ (2)

  2. $K^{*\pm}\to K_S^0 \pi^\pm$ resonances

  $$D \to \left(K^{*\pm} \to K_S^0 \pi^\pm\right) \pi^\mp.$$ (3)
  
 These intermediate states contribute to $A(m^2_+, m^2_-)$ and occur when the combined mass of their daughter particles approaches the mass of the intermediate state. These intermediate states enhance the parts of the Dalitz plot where they occur. 

 The decay amplitude, $A_{D^0}(m^2_+, m^2_-)$, is calculated by the addition of sub-amplitudes, $A^n_{D^0}(m^2_+, m^2_-)$ which take the form

$$A^n_{D^0} (m^2_+, m^2_-) = A_n e^{i\phi_n} f_n(m^2_+, m^2_-), $$ (4)

where $A_n e^{i\phi_n$ make up the amplitude and phase of the individual amplitude. The phase space dependent $f_n(m^2_+, m^2_-)$ is called the ''lineshape''.
The sub amplitudes are arranged in the following categories
1. A single relativistic particle, of mass $m_r$ and width $\Gamma_r(s)$ decaying into the two final states of the resonance, note that the width is dependent on the invariant mass of the two final states. The lineshape for such a sub-amplitude is given as a ''Breit Wigner'' function

The function $f_r(m^2_+, m^2_-)$ can be factorized as

$$ f_r(m^2_+, m^2_-) = F_D \times F_r \times T_r \times W_r $$

where $F_{D,r}$ is the ''Blatt-Weisskopf'' barrier factor for the $D,r$ decay, $T_r$ is the ''resonance'' propagator, which is either a ''Breit-Wiger'' function or a Gounaris-Sakurai function and $W_r$ is the angular distribution of the decay, described by ''Zemach Tensors''.





 2. In the case of resonances of $\pi^+ \pi%-$ with spin zero, there are overlapping scalar resonances, therefore the previous approximation of a single resonance is no longer accurate. The use of the ''K-Matrix'' from nuclear physics is used instead. The value of $A_n e^{i\phi_n}$ are set to one in this case, for the $\pi^+ \pi^-$ case the function $f_n(m^2_+, m^2_-)$ is given by

 $$ f_n(m^2_+, m^2_-) = \sum_l (I - iK(s(m^2_+, m^2_-))\rho(s(m^2_+, m^2_-)))_{ij} 