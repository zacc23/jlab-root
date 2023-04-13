#include <TAxis.h>
#include <TFrame.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TMath.h>

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void moments() {
	TCanvas *c1 = new TCanvas("c1", "Plot of M8 moments versus Q2 with error bars", 200, 10, 700, 500);
	c1->SetGrid();
	c1->GetFrame()->SetBorderSize(12);

	ifstream MData;
        MData.open("moments.tsv", ios::in);

	const int lines = 32; // for no whitespace, 132 total
        Float_t Q2[lines], M2[lines], M4[lines], M6[lines], M8[lines];
        for (int i=0; i<lines; i++)
        {
                MData >> Q2[i] >> M2[i] >> M4[i] >> M6[i] >> M8[i];
        }
	
	TGraph *gr = new TGraph(lines, Q2, M2);
	TGraph *m4 = new TGraph(lines, Q2, M4);
	TGraph *m6 = new TGraph(lines, Q2, M6);
	TGraph *m8 = new TGraph(lines, Q2, M8);
        gr->SetTitle("Moments versus Q2");
	gr->GetXaxis()->SetTitle("Q2");
	gr->GetXaxis()->CenterTitle(true);
	gr->GetYaxis()->SetTitle("Moments");
	gr->GetYaxis()->CenterTitle(true);
	gr->SetMarkerSize(4);
	gr->SetMarkerColor(2);
	gr->SetMarkerStyle(33);
        gr->Draw("AP");
	
	m4->SetMarkerSize(2);
        m4->SetMarkerColor(2);
        m4->SetMarkerStyle(34);
        m4->SetLineWidth(3);
        m4->SetLineColor(1);
        m4->Draw("CSame");

	m6->SetMarkerSize(2);
        m6->SetMarkerColor(2);
        m6->SetMarkerStyle(33);
        m6->SetLineWidth(3);
        m6->SetLineColor(2);
        m6->Draw("CSame");

	m8->SetMarkerSize(2);
        m8->SetMarkerColor(2);
        m8->SetMarkerStyle(34);
        m8->SetLineWidth(3);
        m8->SetLineColor(3);
        m8->Draw("CSame");

	c1->Update();
}
