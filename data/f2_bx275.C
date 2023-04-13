#include <TAxis.h>
#include <TFrame.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TMath.h>

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void f2_bx275() {
	TCanvas *c1 = new TCanvas("c1", "Plot of F2 functions for 2.75 versus Bjorken x with error bars", 200, 10, 700, 500);
	c1->SetGrid();
	c1->GetFrame()->SetBorderSize(12);
	
	ifstream NaData;
	NaData.open("F2_275.dat", ios::in);

	const int lines = 34;
	Float_t F2[lines], F2err[lines], BX[lines], BXerr[lines], tmp;
	for (int i=0; i<lines; i++)
	{		
		NaData >> tmp >> tmp >> BX[i] >> tmp >> tmp >> tmp >> tmp >> tmp >> F2[i] >> F2err[i] >> tmp;
		BXerr[i] = 0;
	}	

        TGraphErrors *gr = new TGraphErrors(lines, BX, F2, BXerr, F2err);
        gr->SetTitle("F2 functions for 2.75 versus Bjorken x");
	gr->GetXaxis()->SetTitle("BX");
	gr->GetXaxis()->CenterTitle(true);
	gr->GetYaxis()->SetTitle("F2");
	gr->GetYaxis()->CenterTitle(true);
	gr->SetMarkerSize(2);
	gr->SetMarkerColor(2);
	gr->SetMarkerStyle(33);
        gr->Draw("AP");
        c1->Update();
	c1->Print("275.pdf");
}
