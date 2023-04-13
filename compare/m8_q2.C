#include <TAxis.h>
#include <TFrame.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TMath.h>

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void m8_q2() {
	TCanvas *c1 = new TCanvas("c1", "Plot of M8 moments versus Q2 with error bars", 200, 10, 700, 500);
	c1->SetGrid();
	c1->GetFrame()->SetBorderSize(12);
	
	ifstream NaData;
        NaData.open("m8_q2.tsv", ios::in);

	const int lines = 120; // for no whitespace, 132 total
	Float_t Q2[lines], M8[lines], M8err1[lines], M8err2[lines], M8errT[lines], Q2err[lines];
	for (int i=0; i<lines; i++)
	{		
		NaData >> Q2[i] >> M8[i] >> M8err1[i] >> M8err2[i];
		//cout << Q2[i] << ' ' << M8[i] << ' ' << M8err1[i] << ' ' << M8err2[i] << endl;
		Q2err[i] = 0;
		M8errT[i] = TMath::Sqrt(TMath::Power(M8err1[i], 2) + TMath::Power(M8err2[i], 2));
	}	

        TGraphErrors *gr = new TGraphErrors(lines, Q2, M8, Q2err, M8errT);
        gr->SetTitle("M8 moments versus Q2");
	gr->GetXaxis()->SetTitle("Q2");
	gr->GetXaxis()->CenterTitle(true);
	gr->GetYaxis()->SetTitle("M8");
	gr->GetYaxis()->CenterTitle(true);
	gr->SetMarkerSize(4);
	gr->SetMarkerColor(2);
	gr->SetMarkerStyle(33);
        gr->Draw("AP");
        c1->Update();
	c1->Print("m8.png");
}
