#include "integrate.h"
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

int main() {
	TCanvas *c1 = new TCanvas("c1", "Plot of F2 functions versus Bjorken x with error bars", 200, 10, 700, 500);
	c1->Divide(1,3);
	c1->SetGrid();
	c1->GetFrame()->SetBorderSize(12);
	
	char name[50];
        double qval = .5;
	sprintf(name,"F2_%1.2f.dat",qval);

	int lines = 0,
                cnt_all = 0;
        Float_t F2[100], F2err[100], BX[100], BXerr[100], tmp,
                F2_all[1000], F2_allErr[1000], BX_all[1000], BX_allErr[1000];
	ifstream NaData;
        NaData.open(name, ios::in);
	if(NaData.good()) {
        	for (int i=0; i<100; i++)
        	{
                	if(!NaData.eof())
                	{
                       		NaData >> tmp >> tmp >> BX[i] >> tmp >> tmp >> tmp >> 
					tmp >> tmp >> F2[i] >> F2err[i] >> tmp;
				F2_all[cnt_all] = F2[i];
				F2_allErr[cnt_all] = F2err[i];
				BX_all[cnt_all] = BX[i];
				BX_allErr[cnt_all] = 0;
                        	BXerr[cnt_all] = 0;
				cnt_all++;
                       		lines++;
                	}
        	}
	}

        sprintf(name,"whitlow_%1.2f.dat",qval);
	cout << name << endl;

	ifstream WSData;
	WSData.open(name, ios::in);

	int wlines = 0;
        Float_t wF2[100], wF2err1[100], wF2err2[100], wF2errT[100], wBX[100], wBXerr[100];
        if(WSData.good()) {
		cnt_all--;
		for (int i=0; i<100; i++)
		{		
        		if(!WSData.eof())
			{
	                	WSData >> wBX[i] >> tmp >> wF2[i] >> wF2err1[i] >> wF2err2[i];
				wF2errT[i] = TMath::Sqrt(TMath::Power(wF2err1[i], 2) + TMath::Power(wF2err2[i], 2));
				wBXerr[i] = 0;
				F2_all[cnt_all] = wF2[i];
                        	F2_allErr[cnt_all] = wF2errT[i];
                        	BX_all[cnt_all] = wBX[i];
                        	BX_allErr[cnt_all] = 0;
                       		cnt_all++;	
				wlines++;
			}
		}	
	}

	sprintf(name,"nm1992_%1.2f.dat",qval);
        cout << name << endl;
	
	ifstream NM92Data;
        NM92Data.open(name, ios::in);
	
	int nm92lines = 0;
	Float_t nm92F2[100], nm92F2err1[100], nm92F2err2[100], nm92F2errT[100], nm92BX[100], nm92BXerr[100];
	if(NM92Data.good()) {
		cnt_all--;
		for (int i=0; i<100; i++)
        	{
                	if(!NM92Data.eof())
                	{
                        	NM92Data >> nm92BX[i] >> tmp >> nm92F2[i] >> nm92F2err1[i] >> nm92F2err2[i];
                        	nm92F2errT[i] = TMath::Sqrt(TMath::Power(nm92F2err1[i], 2) + 
					TMath::Power(nm92F2err2[i], 2));
                        	nm92BXerr[i] = 0;
				F2_all[cnt_all] = nm92F2[i];
                        	F2_allErr[cnt_all] = nm92F2errT[i];
                        	BX_all[cnt_all] = nm92BX[i];
                        	BX_allErr[cnt_all] = 0;
                        	cnt_all++;
                        	nm92lines++;
                	}
        	 }
	}

	sprintf(name,"nm1995_%1.2f.dat",qval);
        cout << name << endl;

        ifstream NM95Data;
        NM95Data.open(name, ios::in);

        int nm95lines = 0;
        Float_t nm95F2[100], nm95F2err1[100], nm95F2err2[100], nm95F2errT[100], nm95BX[100], nm95BXerr[100];
	if(NM95Data.good()) {
		cnt_all--;
        	for (int i=0; i<100; i++)
        	{
                	if(!NM95Data.eof())
                	{
                        	NM95Data >> nm95BX[i] >> tmp >> nm95F2[i] >> nm95F2err1[i] >> nm95F2err2[i];
                        	nm95F2errT[i] = TMath::Sqrt(TMath::Power(nm95F2err1[i], 2) + 
					TMath::Power(nm95F2err2[i], 2));
                        	nm95BXerr[i] = 0;
				F2_all[cnt_all] = nm95F2[i];
                        	F2_allErr[cnt_all] = nm95F2errT[i];
                        	BX_all[cnt_all] = nm95BX[i];
                        	BX_allErr[cnt_all] = 0;
                        	cnt_all++;
                        	nm95lines++;
                	}
        	}
	}

	/*
	for (int i=0; i<cnt_all-1; i++) {
                cout << i << " " << BX_all[i] << " " << F2_all[i] << ' ' << F2_allErr[i] << endl;
        }
	*/

	// SORT (bubble)
	double tmpF2, tmpF2err, tmpBX, tmpBXerr;
	for (int i=0; i<cnt_all-2; i++)
	{
		for (int j=0; j<cnt_all-2; j++)
		{
			if (BX_all[j] > BX_all[j+1])
			{
				tmpBX = BX_all[j];
				BX_all[j] = BX_all[j+1];
				BX_all[j+1] = tmpBX;

				tmpF2 = F2_all[j];
				F2_all[j] = F2_all[j+1];
				F2_all[j+1] = tmpF2;

				tmpBXerr = BX_allErr[j];
				BX_allErr[j] = BX_allErr[j+1];
				BX_allErr[j+1] = tmpBXerr;

				tmpF2err = F2_allErr[j];
				F2_allErr[j] = F2_allErr[j+1];
				F2_allErr[j+1] = tmpF2err;
			}
		}
	}
	 
	/*
	for (int i=0; i<cnt_all-1; i++) {
                cout << i << " " << BX_all[i] << " " << F2_all[i] << ' ' << F2_allErr[i] << endl;
        }
	*/

	int cnt_avg = 0;
        Float_t F2all_avg[1000], F2all_avgErr[1000], BXall_avg[1000], BXall_avgErr[1000];
        for (int i=0; i<cnt_all; i++)
        {
                BXall_avg[cnt_avg] = BX_all[i];
                BXall_avgErr[cnt_avg] = 0;
                // check if Bjorken x is equal at i, if so then average F2 and increment i to avoid it showing up next (i=i+2)
		// also track amount of equal values, as j, and add up all then divide by j for average
                int j = 1;
		// sum is single value by default, then added to by following equal values and divided by amount of equal values
                Float_t sum = F2_all[i];
                while (BX_all[i] == BX_all[i+j])
		{
                        sum += F2_all[i+j];
                        j++;
                }
		F2all_avg[cnt_avg] = sum / j;
		// weighted error (http://ned.ipac.caltech.edu/level5/Leo/Stats4_5.html)
		if (j == 1)	
			F2all_avgErr[cnt_avg] = sqrt(1.0 / (1.0 / pow(F2_allErr[i], 2)));
		else if (j == 2)
			F2all_avgErr[cnt_avg] = sqrt(1.0 / (1.0 / pow(F2_allErr[i], 2) + 1.0 / pow(F2_allErr[i+1], 2)));
		else if (j == 3)
			F2all_avgErr[cnt_avg] = sqrt(1.0 / (1.0 / pow(F2_allErr[i], 2) + 1.0 / pow(F2_allErr[i+1], 2)
				+ 1.0 / pow(F2_allErr[i+2], 2)));
		//cout << j << ' ' << cnt_avg << ' ' << F2all_avg[cnt_avg] << ' ' << F2all_avgErr[cnt_avg] << endl;
		//cout << cnt_avg << " " << BXall_avg[cnt_avg] << " " << F2all_avg[cnt_avg] << endl;
                i = i+j - 1;
                cnt_avg++;	
        }

	/*
	for (int i=0; i<cnt_avg-1; i++) {
                cout << i << " " << BXall_avg[i] << " " << F2all_avg[i] << ' ' << F2all_avgErr[i] << endl;
        }
	*/
	
	TGraphErrors *jl = new TGraphErrors(lines-1, BX, F2, BXerr, F2err);
	TGraphErrors *ws = new TGraphErrors(wlines-1, wBX, wF2, wBXerr, wF2errT);
	TGraphErrors *nm92 = new TGraphErrors(nm92lines-1, nm92BX, nm92F2, nm92BXerr, nm92F2errT);
	TGraphErrors *nm95 = new TGraphErrors(nm95lines-1, nm95BX, nm95F2, nm95BXerr, nm95F2errT);
	TGraphErrors *all = new TGraphErrors(cnt_all-1, BX_all, F2_all, BX_allErr, F2_allErr);
        TGraphErrors *avg = new TGraphErrors(cnt_avg-1, BXall_avg, F2all_avg, BXall_avgErr, F2all_avgErr);

	c1->cd(1);
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
	
	c1->cd(2);
	sprintf(name,"F_{2} versus Bjorken x at Q^{2} = %1.2f GeV^{2}",qval);
        all->SetTitle(name);
        all->GetXaxis()->SetTitle("X_{B}");
        all->GetXaxis()->CenterTitle(true);
        all->GetYaxis()->SetTitle("F_{2}");
        all->GetYaxis()->CenterTitle(true);
	all->SetMarkerSize(2);
        all->SetMarkerColor(1);
        all->SetMarkerStyle(33);
        all->Draw("AP");

	c1->cd(3);	
	sprintf(name,"F_{2} versus Bjorken x at Q^{2} = %1.2f GeV^{2}",qval);
	avg->SetTitle(name);
        avg->GetXaxis()->SetTitle("X_{B}");
        avg->GetXaxis()->CenterTitle(true);
        avg->GetYaxis()->SetTitle("F_{2}");
        avg->GetYaxis()->CenterTitle(true);
        avg->SetMarkerSize(2);
        avg->SetMarkerColor(1);
        avg->SetMarkerStyle(33);
        avg->Draw("AP");

	// TODO: add integration error (https://narkive.com/ngne6MEq.2)
        cout << "Moment of avg: " << integrate(cnt_avg, BXall_avg, F2all_avg) << endl;
	//cout << "Moment of avg: " << avg->Integral(0,1) << endl;

        c1->Update();
	sprintf(name,"integral_%1.2f.pdf",qval);
	c1->Print(name);
	sprintf(name,"integral_%1.2f.png",qval);
	c1->Print(name);

	return 0;
}
