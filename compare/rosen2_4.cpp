#include <TAxis.h>
#include <TFrame.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TMath.h>

#include <string>
#include <iostream>

using namespace std;

void rosen2_4() {
	TCanvas *c1 = new TCanvas("c1", "Plot of Rosen07 moments versus Q2", 200, 10, 700, 500);
	c1->SetGrid();
	c1->GetFrame()->SetBorderSize(12);

	double Q2[] = { 2, 3, 4 };
	double M2_4[] = { 0.03368, 0.03295, 0.031355 };

        TGraph *gr = new TGraph(3, Q2, M2_4);
        gr->SetTitle("M2_4 moments versus Q2");
	gr->GetXaxis()->SetTitle("Q2");
	gr->GetXaxis()->CenterTitle(true);
	gr->GetYaxis()->SetTitle("M2_4");
	gr->GetYaxis()->CenterTitle(true);
	gr->SetMarkerSize(4);
	gr->SetMarkerColor(2);
	gr->SetMarkerStyle(33);
        gr->Draw("AC");
        c1->Update();
}
