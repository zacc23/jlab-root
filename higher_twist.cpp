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

double higher2(double q2) { // higher twist: HT_2(Q^2) [8]pg.13
	// example of M2 (no error consideration yet):
        double an4, mu2, gammaN4;
        an4 = 4.0 * pow(10.0, -4);
        gammaN4 = 3.4;
        mu2 = 10.0; // mu^2 = 10 (GeV/c)^2 (Reference Scale) [8]pg.13
        return an4 * pow(alpha(q2) / alpha(mu2), gammaN4) * (mu2 / q2); 
}

double higher4(double q2) { // higher twist: HT_4(Q^2) [8]pg.13
        // example of M4 (no error consideration yet):
        double an4, an6, mu2, mu4, q4,
		gammaN4, gammaN6;
	an4 = 7.4 * pow(10.0, -3);
	an6 = -1.5 * pow(10.0, -2);
	gammaN4 = 3.0;
	gammaN6 = 1.9;
	mu2 = 10.0; // mu^2 = 10 (GeV/c)^2 (Reference Scale) [8]pg.13
	mu4 = mu2*mu2;
	q4 = q2*q2;
	cout << alpha(q2) << ", " << alpha(mu2) << ": " << an4 * pow(alpha(q2) / alpha(mu2), gammaN4) * (mu2 / q2) << " + " << an6 * pow(alpha(q2) / alpha(mu2), gammaN6) * (mu4 / q4) << " = ";
        return an4 * pow(alpha(q2) / alpha(mu2), gammaN4) * (mu2 / q2);
	 //    + an6 * pow(alpha(q2) / alpha(mu2), gammaN6) * (mu4 / q4);
}

double higher6(double q2) { // higher twist: HT_6(Q^2) [8]pg.13
	// example of M6 (no error consideration yet):
        double an4, an6, mu2, mu4, q4,
                gammaN4, gammaN6;
        an4 = 2.7 * pow(10.0, -3);
        an6 = -9.2 * pow(10.0, -3);
        gammaN4 = 5.9;
        gammaN6 = 4.3;
        mu2 = 10.0; // mu^2 = 10 (GeV/c)^2 (Reference Scale) [8]pg.13
        mu4 = mu2*mu2;
        q4 = q2*q2;
        return an4 * pow(alpha(q2) / alpha(mu2), gammaN4) * (mu2 / q2) +
               an6 * pow(alpha(q2) / alpha(mu2), gammaN6) * (mu4 / q4);
}	

double higher8(double q2) { // higher twist: HT_8(Q^2) [8]pg.13
	// example of M8 (no error consideration yet):
	double an4 = .0017, an6 = -.0066, 
	       mu2, gammaN4 = 6.4, gammaN6 = 4.7;
	mu2 = 10.0; // mu^2 = 10 (GeV/c)^2 (Reference Scale) [8]pg.13
	return an4 * pow(alpha(q2) / alpha(mu2), gammaN4) * (mu2 / q2) +
	       an6 * pow(alpha(q2) / alpha(mu2), gammaN6) * (mu2*mu2 / (q2*q2)); 
}
	
int main() {
	TCanvas *c1 = new TCanvas("c1", "Plot of higher twist versus Q2", 200, 10, 700, 500);
	c1->SetGrid();
	c1->GetFrame()->SetBorderSize(12);
	c1->SetLogx();

	double q2[1000], high[1000];

	for (int i = 0; i < 990; i++) // Q2: 0 to 10^2 (i < 200) [8]pg.20
        {
                q2[i] = 0.5 + i * 0.1; // get more data points
		high[i] = higher4(q2[i]);
		cout << high[i] << endl;
		//cout << i << " " << alpha(q2[i]) << " " << high[i] << endl;
		//cout << alpha(0.475) << " " << higher4(0.475) << endl;
	}

	TGraph *gr = new TGraph(900, q2, high);
	gr->SetTitle("HT versus Q^{2}");
	gr->GetXaxis()->SetTitle("Q^{2}");
	gr->GetXaxis()->CenterTitle(true);
	gr->GetYaxis()->SetTitle("HT");
	gr->GetYaxis()->CenterTitle(true);
	gr->SetMarkerSize(2);
	gr->SetMarkerColor(2);
	gr->SetMarkerStyle(33);
	gr->SetLineWidth(3);
	gr->SetLineColor(2);
	gr->Draw("AC");
	c1->Update();

	//c1->Print("higher.pdf");
	//c1->Print("higher.png");

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
*/
