#include <TAxis.h>
#include <TFrame.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TMath.h>

#include <string>
#include <iostream>
#include <fstream>

#include "alpha.h"
#include "higher.h"
#include "leading.h"

using namespace std;

int main() {
	TCanvas *c1 = new TCanvas("c1", "Plot of M8 moments versus Q2 with error bars", 200, 10, 700, 500);
	c1->SetGrid();
	c1->GetFrame()->SetBorderSize(12);
	c1->SetLogx();
	
	ifstream NaData;
        NaData.open("m8_q2.tsv", ios::in);

	const int lines = 120; // for no whitespace, 132 total
	Float_t Q2[lines], M8[lines], M8err1[lines], M8err2[lines], M8errT[lines], Q2err[lines];
	for (int i=0; i<lines; i++)
	{		
		NaData >> Q2[i] >> M8[i] >> M8err1[i] >> M8err2[i];
		//cout << Q2[i] << ' ' << M8[i] << ' ' << M8err1[i] << ' ' << M8err2[i] << endl;
		M8[i] = M8[i] / 1000.0;
		Q2err[i] = 0;
		M8errT[i] = (TMath::Sqrt(TMath::Power(M8err1[i], 2) + TMath::Power(M8err2[i], 2))) / 1000.0;
	}	

        double q2[1000], tws4[1000], tws6[1000], high[1000], lead[1000];

	extern const double n;
	/*
	if (n == 4)
        {
        }
	else if (n == 5)
        {
        }
	else if (n == 7)
        {
        }
	else if (n == 7)
        {
	}
	else if (n == 8) 
	{
	*/
        	for (int i = 0; i < 990; i++) // Q2: 0 to 10^2 (i < 200) [8]pg.20
        	{
                	q2[i] = 0.5 + i * 0.1; // get more data points
                	tws4[i] = tw4(q2[i]);
                	tws6[i] = tw6(q2[i]);
                	high[i] = higher(q2[i]);
                	lead[i] = leading(q2[i]); 
		}
        //}

        TGraph *tw4 = new TGraph(900, q2, tws4);
        TGraph *tw6 = new TGraph(900, q2, tws6);
        TGraph *ld = new TGraph(900, q2, lead);
        TGraph *ht = new TGraph(900, q2, high);
	TGraphErrors *gr = new TGraphErrors(lines, Q2, M8, Q2err, M8errT);

        gr->SetTitle("M8 moments versus Q2");
        gr->GetXaxis()->SetTitle("Q2");
        gr->GetXaxis()->CenterTitle(true);
        gr->GetYaxis()->SetTitle("M8");
        gr->GetYaxis()->CenterTitle(true);
        gr->SetMarkerSize(4);
        gr->SetMarkerColor(2);
        gr->SetMarkerStyle(33);
	gr->SetMinimum(-.0025);
        //gr->SetMaximum(.005);
        gr->Draw("AP");

	ld->SetMarkerSize(2);
        ld->SetMarkerColor(2);
        ld->SetMarkerStyle(34);
        ld->SetLineWidth(3);
        ld->SetLineColor(1);
        ld->Draw("CSame");

        ht->SetMarkerSize(2);
        ht->SetMarkerColor(2);
        ht->SetMarkerStyle(33);
        ht->SetLineWidth(3);
        ht->SetLineColor(2);
        ht->Draw("CSame");

        tw4->SetMarkerSize(2);
        tw4->SetMarkerColor(2);
        tw4->SetMarkerStyle(34);
        tw4->SetLineWidth(3);
        tw4->SetLineColor(3);
        tw4->Draw("CSame");

	/*
        tw6->SetMarkerSize(2);
        tw6->SetMarkerColor(2);
        tw6->SetMarkerStyle(35);
        tw6->SetLineWidth(3);
        tw6->SetLineColor(4);
        tw6->Draw("CSame");
	*/

	c1->Update();

        c1->Print("all.pdf");
        c1->Print("all.png");

	return 0;
}
