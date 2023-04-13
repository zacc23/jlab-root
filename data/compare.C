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

void compare() {
	TCanvas *c1 = new TCanvas("c1", "Plot of F2 functions versus Bjorken x with error bars", 200, 10, 700, 500);
	c1->SetGrid();
	c1->GetFrame()->SetBorderSize(12);
	
	char name[50];
        double qval = 1.75;
	sprintf(name,"F2_%1.2f.dat",qval);
        cout << name << endl;

	ifstream NaData;
        NaData.open(name, ios::in);
	
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

        sprintf(name,"whitlow_%1.2f.dat",qval);
	cout << name << endl;

	ifstream WSData;
	WSData.open(name, ios::in);
	
	int wlines = 0;
        Float_t wF2[100], wF2err1[100], wF2err2[100], wF2errT[100], wBX[100], wBXerr[100];
	for (int i=0; i<100; i++)
	{		
        	if(!WSData.eof())
		{
	                WSData >> wBX[i] >> tmp >> wF2[i] >> wF2err1[i] >> wF2err2[i];
			wF2errT[i] = TMath::Sqrt(TMath::Power(wF2err1[i], 2) + TMath::Power(wF2err2[i], 2));
			wBXerr[i] = 0;
			wlines++;
		}
	}	

	sprintf(name,"nm1992_%1.2f.dat",qval);
        cout << name << endl;
	
	ifstream NM92Data;
        NM92Data.open(name, ios::in);
	
	int nm92lines = 0;
	Float_t nm92F2[100], nm92F2err1[100], nm92F2err2[100], nm92F2errT[100], nm92BX[100], nm92BXerr[100];
	for (int i=0; i<100; i++)
        {
                if(!NM92Data.eof())
                {
                        NM92Data >> nm92BX[i] >> tmp >> nm92F2[i] >> nm92F2err1[i] >> nm92F2err2[i];
                        nm92F2errT[i] = TMath::Sqrt(TMath::Power(nm92F2err1[i], 2) + TMath::Power(nm92F2err2[i], 2));
                        nm92BXerr[i] = 0;
                        nm92lines++;
                }
        }

	sprintf(name,"nm1995_%1.2f.dat",qval);
        cout << name << endl;

        ifstream NM95Data;
        NM95Data.open(name, ios::in);

        int nm95lines = 0;
        Float_t nm95F2[100], nm95F2err1[100], nm95F2err2[100], nm95F2errT[100], nm95BX[100], nm95BXerr[100];
        for (int i=0; i<100; i++)
        {
                if(!NM95Data.eof())
                {
                        NM95Data >> nm95BX[i] >> tmp >> nm95F2[i] >> nm95F2err1[i] >> nm95F2err2[i];
                        nm95F2errT[i] = TMath::Sqrt(TMath::Power(nm95F2err1[i], 2) + TMath::Power(nm95F2err2[i], 2));
                        nm95BXerr[i] = 0;
                        nm95lines++;
                }
        }
	
        TGraphErrors *jl = new TGraphErrors(lines-1, BX, F2, BXerr, F2err);
	TGraphErrors *ws = new TGraphErrors(wlines-1, wBX, wF2, wBXerr, wF2errT);
	TGraphErrors *nm92 = new TGraphErrors(nm92lines-1, nm92BX, nm92F2, nm92BXerr, nm92F2errT);
	TGraphErrors *nm95 = new TGraphErrors(nm95lines-1, nm95BX, nm95F2, nm95BXerr, nm95F2errT);
	sprintf(name,"F_{2} versus Bjorken x at Q^{2} = %1.2f GeV^{2}",qval);
	jl->SetTitle(name);
	jl->GetXaxis()->SetTitle("X_{B}");
	jl->GetXaxis()->CenterTitle(true);
	jl->GetYaxis()->SetTitle("F_{2}");
	jl->GetYaxis()->CenterTitle(true);
	jl->SetMarkerSize(2);
	jl->SetMarkerColor(2);
	jl->SetMarkerStyle(33);
	jl->GetXaxis()->SetRangeUser(0,1.3);
	jl->GetXaxis()->SetLimits(0,1.3);
	jl->GetYaxis()->SetRangeUser(0,0.4);
        jl->Draw("AP");

	ws->SetMarkerSize(2);
        ws->SetMarkerColor(4);
        ws->SetMarkerStyle(33);
        ws->Draw("PSame");

	nm92->SetMarkerSize(2);
        nm92->SetMarkerColor(3);
        nm92->SetMarkerStyle(33);
        nm92->Draw("PSame");

	nm95->SetMarkerSize(2);
        nm95->SetMarkerColor(1);
        nm95->SetMarkerStyle(33);
        nm95->Draw("PSame");

        c1->Update();
	sprintf(name,"compare_%1.2f.pdf",qval);
	c1->Print(name);
	sprintf(name,"compare_%1.2f.png",qval);
	c1->Print(name);
}
