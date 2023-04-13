#include <TAxis.h>
#include <TFrame.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TMath.h>

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void f2_bx() {
	TCanvas *c1 = new TCanvas("c1", "Plot of F2 functions versus Bjorken x with error bars", 200, 10, 700, 500);
	c1->SetGrid();
	c1->GetFrame()->SetBorderSize(12);
	
	char name[50];
        double qval = .8;
        sprintf(name,"F2_%1.2f.dat",qval);
	cout << name << endl;

	ifstream NaData;
	NaData.open(name, ios::in);
	
	// line numbers also differ between files

	int lines = 0;
	Float_t F2[100], F2err[100], BX[100], BXerr[100], tmp;
	for (int i=0; i<100; i++)
	{		
        	if(!NaData.eof())
		{
			NaData >> tmp >> tmp >> BX[i] >> tmp >> tmp >> tmp >> tmp >> tmp >> F2[i] >> F2err[i] >> tmp;
			BXerr[i] = 0;
			lines++;
		}
	}	

        TGraphErrors *gr = new TGraphErrors(lines-1, BX, F2, BXerr, F2err);
	sprintf(name,"F_{2} versus Bjorken x at Q^{2} = %1.2f GeV^{2}",qval);
	gr->SetTitle(name);
	gr->GetXaxis()->SetTitle("X_{B}");
	gr->GetXaxis()->CenterTitle(true);
	gr->GetYaxis()->SetTitle("F_{2}");
	gr->GetYaxis()->CenterTitle(true);
	gr->SetMarkerSize(2);
	gr->SetMarkerColor(2);
	gr->SetMarkerStyle(33);
	gr->GetXaxis()->SetLimits(0,1.4);
        gr->Draw("AP");
        c1->Update();
	sprintf(name,"F2_%1.2f.pdf",qval);
	c1->Print(name);
}
