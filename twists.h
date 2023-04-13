const int n = 8; // "The presence of two distinct higher twist terms for n ≥ 4 is motivated by the Q2-behaviour of the total higher twist contribution in the moments" [8]pg.13
	
/* Leading Twist Key:
	A_n : twist-2 parameter: T2para
	alpha_s(Q^2) : RCConstant --> Running Coupling Constant
	alpha_s(mu^2) : ASM2
	gamma_n^NS : NSADimen ---> one-loop NS anamalous dimensions [1]pg.?
	C_DIS^(NLO) : QCFunction ---> Quark Coefficient Function [1]pg.3
	G_n(Q^2) : SoftGluonR ---> key quantity of Soft Gluon Resummation [1]pg.4
	R_n^NS : RNNS ---> [1]pg.3
	
	
   Higher Twist Key:
	a_n^(4) : HTPA4 = 1.7 * 10^(-3) ---> Higher Twist Parameter
   	a_n^(6) : HTPA6 = -6.6 * 10^(-3) ---> Higher Twist Parameter
   	gamma_n^(4) : HTPG4 = 6.4 ---> Higher Twist Parameter
   	gamma_n^(6) : HTPG6 = 4.7 ---> Higher Twist Parameter
   	alpha_s(Q^2) : RCConstant ---> Running Coupling Constant
   	alpha_s(mu^2) : ASM2
   	Q^2 : HTQ2 = Q^2 values from graph
   	mu^2 : Mu2 = 10 (GeV/c)^2 ---> reference scale
   
   
   RCConstant Key:
   	mu^2 : Mu2 = 10 (GeV/c)^2---> Reference Scale
   	beta_0 : Beta0 = 11-2/3*Flavors ---> ???
   	n_f : Flavors = ??? ---> Number of Quark Flavors
   	alpha_s(mu^2) : ASM2
   	Q^2 : HTQ2 = Q^2 values from graph
   ﻿
   Notes:
   	[RCConstant/ASM2]^NSADimen corresponds to Wilson Coefficient E_ntau [2]pg.4 Eq.2
   	tau = twist, ex. in twist 4 a_n(tau) = a_n(8) = HTPA8 (not used)
   	Ref [2] mentions a value alpha_s(M_Z^2) = 0.118 from [3], but in [3] various versions of an alpha_s(M_Z) are given, none of which are squared. Ref [1] specifies this to be = 0.118 (pg.4), but states it was originally 0.113 from another source [4]
   
References:
	[1] https://arxiv.org/pdf/hep-ph/0005315.pdf
	[2] Base Paper: Measurement of the Deuteron Structure Function F_2 in the Resonance Region and Evaluation of Its Moments
	[3] https://pdg.lbl.gov/2000/qcdrppbook.pdf
	[4] https://www.sciencedirect.com/science/article/abs/pii/037026939391530Z (no access)
	[5] https://arxiv.org/pdf/hep-ph/9901360.pdf
	[6] https://lss.fnal.gov/archive/thesis/2000/fermilab-thesis-2000-51.pdf#:~:text=The%20strong%20coupling%20constant%20has,189%20GeV%20at%20LEP%2D2.
	[7] Euler-Mascheroni constant found pg. 27 https://arxiv.org/pdf/1303.1856.pdf
 	[8] https://arxiv.org/pdf/hep-ex/0506004.pdf	
	[9] http://arxiv.org/pdf/hep-ph/9601294.pdf
*/
