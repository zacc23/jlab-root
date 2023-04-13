#include <TAxis.h>
#include <TFrame.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TMath.h>

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void m6_q2() {
	TCanvas *c1 = new TCanvas("c1", "Plot of M6 moments versus Q2 with error bars", 200, 10, 700, 500);
	c1->SetGrid();
	c1->GetFrame()->SetBorderSize(12);
	
	ifstream NaData;
        NaData.open("m6_q2.tsv", ios::in);

	const int lines = 114; 
	Float_t Q2[lines], M6[lines], M6err1[lines], M6err2[lines], M6errT[lines], Q2err[lines];
	for (int i=0; i<lines; i++)
	{		
		NaData >> Q2[i] >> M6[i] >> M6err1[i] >> M6err2[i];
		Q2err[i] = 0;
		M6errT[i] = TMath::Sqrt(TMath::Power(M6err1[i], 2) + TMath::Power(M6err2[i], 2));
	}	

        TGraphErrors *gr = new TGraphErrors(lines, Q2, M6, Q2err, M6errT);
        gr->SetTitle("M6 moments versus Q2");
	gr->GetXaxis()->SetTitle("Q2");
	gr->GetXaxis()->CenterTitle(true);
	gr->GetYaxis()->SetTitle("M6");
	gr->GetYaxis()->CenterTitle(true);
	gr->SetMarkerSize(4);
	gr->SetMarkerColor(2);
	gr->SetMarkerStyle(33);
        gr->Draw("AP");
        c1->Update();
	c1->Print("m6.png");
}
