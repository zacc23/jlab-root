#include <TCanvas.h>
#include <TFrame.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TMath.h>

#include <iostream>
#include <math.h>

#include "alpha.h"
#include "leading.h"

using namespace std;

int main() {
	TCanvas *c1 = new TCanvas("c1", "Plot of leading twist versus Q2", 200, 10, 700, 500);
	c1->SetGrid();
	c1->GetFrame()->SetBorderSize(12);
	c1->SetLogx();

	double q2[10000], lead[10000];

	for (int i = 0; i < 9900; i++) // Q2: 0 to 10^2 (i < 200) [8]pg.20
	{
		q2[i] = 0.6 + i * 0.1; // get more data points
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
*/
