#include <TCanvas.h>
#include <TFrame.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TMath.h>

#include <iostream>
#include <math.h>

using namespace std;

double alpha(double q2) { // alpha_s(Q^2): Running Coupling Constant [10]pg.5
        double pi = 3.141592653589793238,
                nf, lambda, b0, b1;
	//double psi, b2, b3;

	// lambda2
        double lambda2, mu2, ln;
        nf = 5.0; // N_f: number of quark flavors ("N_f being the number of active flavors") [8]pg.13
        lambda = 0.23; // lambda_n: [8]pg.13
        //mu = 91.1876; //Z boson mass
        mu2 = q2; // mu^2 = 10 (GeV/c)^2 (Reference Scale) [8]pg.13
        lambda2 = lambda*lambda;
        //psi = 1.20206; // Apery const
        b0 = 11.0 - 2.0*nf/3.0; // [10]pg.5
        b1 = 102.0 - (38.0*nf) / 3.0; // [10]pg.5
        //b2 = 2857.0 / 2.0 - 5033.0 / 18.0*nf + 325.0 / 54.0*nf*nf;
        //b3 = (149753.0 / 6.0 + 3564.0*psi) - (1078361.0 / 162.0 + 6508.0 / 27.0*psi)*nf + (50065.0 / 162.0 + 6475.0 / 81.0 * psi)*nf*nf + 1093.0 / 729.0*nf*nf*nf;
        ln = log(mu2 / lambda2); // L: [10]pg.5

        return 4.0*pi / (b0*ln) * (1.0 - b1 / (b0*b0) * log(ln) / ln);
}

/* unnecessary when using summation
double polygamma(double n) { // [9]pg.24 to the power of one, so no "m"
	return gammafunc(n) / n; // derivative of gamma function with respect to n 
}
*/
double s1(double n) { // [9]pg.23
	// -> gammaE + polygamma(n + 1); 
	// summation of 1/j
	double sum = 0;
	for (int j=1; j<=n; j++) {
		sum += 1.0/j;
	}
	return sum;
}

double s2(double n) { // [9]pg.23
	double sum = 0;
	for (int j=1; j<=n; j++) {
                sum += 1.0/(j*j);
        }
        return sum;
}

double sp2(double n) { // sp2: l=2, s'_2 (prime) [9]pg.23 
	double sum, l;
	sum = 0;
	l = 2.0;	

	for (int j=1; j<=n; j++) 
	{
		sum += pow(2.0, l - 1.0) * (1.0 + pow(-1.0, j))/pow(j, l);
	}
	return sum;	
}

double sp3(double n) { // sp3: l=3, s'_3 (prime) [9]pg.23
	double sum, l;
	sum = 0;
	l = 3.0;

        for (int j=1; j<=n; j++) 
	{
                sum += pow(2.0, l - 1.0) * (1.0 + pow(-1.0, j))/pow(j, l);
        }
	return sum;
}

double st(double n) { // st: s (tilde) [9]pg.23 
	double sum = 0;

	for (int j=1; j<=n; j++) 
	{
		sum += pow(-1.0, j)/(j*j) * s1(j);
	}
	return sum;	
}

double leading(double q2) { // leading twist: eta_n(Q^2) [8]pg.13
	double n, an, mu2, pi = 3.141592653589793238, e = 2.7182818284590452354,
		cn, cdis, cnlog, g1, g2, gn, tf, rn, k, b0, b1, cf, ca, nc, nf, 
		gammaE, gammaN, gammaN0, gammaN1, eta, lambdaN; 
	mu2 = 10.0; // mu^2 = 10 (GeV/c)^2 (Reference Scale) [8]pg.13 
	n = 4.0; // "The presence of two distinct higher twist terms for n ≥ 4 is motivated by the Q2-behaviour of the total higher twist contribution in the moments" [8]pg.13 
	nf = 3.0; // N_f: number of quark flavors ("N_f being the number of active flavors") [8]pg.13
	tf = nf / 2.0; // [9]pg.21
	b0 = 11.0 - 2.0*nf/3.0;
	b1 = 102.0 - (38.0*nf) / 3.0;

	an = .01215; // m_4: eta_4(mu^2) = A_4 = (1.215±0.03±0.01)×10−2 (n = 4); A_n: twist-2 parameter [8]pg.17 
        nc = 3.0; // C_A = N_c -> 3 (substitute for C_A) [1]pg.4
	ca = nc; // C_A: [1]pg.4
        cf = (nc*nc - 1.0) / (2.0*nc); // [8]pg.13 (C_F -> 4/3 [1]pg.3)
        k = nc * (67.0 / 18.0 - pi * pi/6.0) - 5.0*nf/9.0; // K: [8]pg.13 
        lambdaN = b0 * alpha(q2) * log(n) / (4*pi); // lambda_n: [8]pg.13 

	gammaE = 0.5772156649015328606065; // Euler-Mascheroni constant [7] (equivalent to TMath::EulerGamma())
	g1 = cf * 4.0/(b0 * lambdaN) * (lambdaN + (1.0 - lambdaN)*log(1.0 - lambdaN)); // G_1(lambda_n): [8]pg.13
	g2 = -cf * (4.0 * gammaE + 3.0)/b0 * log(1.0 - lambdaN) 
             -cf * (8.0*k/(b0*b0)) * (lambdaN + log(1.0 - lambdaN))
             +cf * (4.0*b1/pow(b0, 3)) * (lambdaN + log(1.0 - lambdaN) + .5*pow(log(1.0 - lambdaN), 2.0)); // // G_2(lambda_n): "divergent for lambda -> 1" [8]pg.13 
        gn = log(n) * g1 + g2; // (without O) G_n: "key quantity of the soft gluon resummation" [8]pg.13 
	// log(n) * g1 + g2 + O * (pow(alpha(q2), k) * pow(log(n), k - 1.0))
	eta = pow(-1.0, n); // [9]pg.25 
	gammaN0 = 2.0 * cf * (4.0 * s1(n) - 3.0 - 2.0/(n * (n - 1.0)) - 4.0 / ((n+1.0)*(n+2.0))) + 8.0/3.0 * tf ; // gamma_0,n: anomalous dimensions [9]pg.21 
	gammaN1 = cf*cf * (16.0 * s1(n) * (2.0*n + 1.0) / (n*n * pow(n + 1.0, 2)) + 16.0*(2.0*s1(n) - 1.0/(n*(n+1.0))) *
		  (s2(n) - sp2(n/2.0)) + 24.0*s2(n) + 64.0*st(n) - 8.0*sp3(n/2.0) - 3.0 - 8.0 * (3*(n*n*n) + n*n - 1.0) / 
		  (n*n*n * pow(n + 1.0, 3.0)) - 16.0*eta * (2.0*(n*n) + 2.0*n + 1.0) / ((n*n*n) * pow(n + 1.0, 3))) + 
		  ca*cf * (536.0/9.0 * s1(n) - 8.0*(2.0*s1(n) - 1/(n*(n + 1.0))) * (2.0*s2(n) - sp2(n/2)) - 
		  88.0/3.0 * s2(n) - 32.0*st(n) + 4.0*sp3(n/2) - 17.0/3.0 - 4.0/9.0 * 
		  (151.0*n*n*n*n + 236.0*n*n*n + 88.0*n*n + 3.0*n + 18.0)/(n*n*n * pow(n + 1.0, 3.0) +
		  8.0*eta * (2.0*n*n + 2*n + 1.0)/(n*n*n * pow(n + 1.0, 3)))) + cf*tf * 
		  (-160.0/9.0 * s1(n) + 32.0/3.0 * s2(n) + 4.0/3.0 + 16.0/9.0 * (11.0*n*n + 5.0*n - 3.0) / 
		  (n*n * pow(n + 1.0, 2))); // gamma_1,n: [9]pg.21,22
	gammaN = alpha(q2)/(4.0*pi) * gammaN0 + pow(alpha(q2)/(4.0*pi), 2) * gammaN1; // gamma_n: anomalous dimensions [9]pg.21
	cdis = cf * (gammaE*gammaE + (3.0/2.0)*gammaE - 9.0/2.0 - pi*pi/6.0); // C_DIS^(NLO): [1]pg.3
	cnlog = cf * log(n) * (log(n) + 2.0*gammaE + 3.0/2.0); // C_n,LOG^(NLO): [1]pg.3
	cn = cdis + cnlog; // (without O(1/n)) C_n^(NLO): "NLO part of the quark coefficient function" [1]pg.3
	rn = (1.0 + alpha(q2)/(2.0*pi) * cdis) * pow(e, gn) + alpha(q2)/(2.0*pi) * (cn - cdis - cnlog) /
	     (1.0 + alpha(q2)/(2.0*pi) * cn); // r_n(Q^2): "ratio of the quark coefficient function" [1]pg.4

	return an * pow(alpha(q2) / alpha(mu2), gammaN) *
	       ((1.0 + alpha(q2) / (2*pi) * cdis) * pow(e, gn) +
	       alpha(q2)/(4.0*pi) * rn);
} 

double higher(double q2) { 
	// example of M8 (no error consideration yet):
	double an4 = 1.7, an6 = -6.6, mu2 = 10.0, gammaN4 = 6.4, gammaN6 = 4.7;
	return an4 * pow(alpha(q2) / alpha(mu2), gammaN4) * (mu2 / q2) +
	       an6 * pow(alpha(q2) / alpha(mu2), gammaN6) * (mu2*mu2 / (q2*q2)); 
}
	
int main() {
	TCanvas *c1 = new TCanvas("c1", "Plot of leading twist versus Q2", 200, 10, 700, 500);
	c1->SetGrid();
	c1->GetFrame()->SetBorderSize(12);
	c1->SetLogx();

	double q2[10000], lead[10000];

	for (int i = 0; i < 9900; i++) // Q2: 0 to 10^2 (i < 200) [8]pg.20
	{
		q2[i] = 0.5 + i * 0.1; // get more data points
		lead[i] = leading(q2[i]);
		cout << i << " " << q2[i] << " " << lead[i] << endl;
	}

	TGraph *gr = new TGraph(9000, q2, lead);
	gr->SetTitle("#eta versus Q^{2}");
	gr->GetXaxis()->SetTitle("Q^{2}");
	gr->GetXaxis()->CenterTitle(true);
	gr->GetYaxis()->SetTitle("#eta");
	gr->GetYaxis()->CenterTitle(true);
	gr->SetMarkerSize(2);
	gr->SetMarkerColor(2);
	gr->SetMarkerStyle(33);
	gr->SetLineWidth(3);
	gr->SetLineColor(2);
	gr->Draw("AC");
	c1->Update();

	c1->Print("leading.pdf");
	c1->Print("leading.png");

	return 0;
}

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
	[10] Determination of alpha-s from the scaling violation in the fragmentation functions in e+e- annihilation. DELPHI Collaboration.
*/
