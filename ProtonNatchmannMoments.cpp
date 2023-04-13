{
#include <iostream>
#include <fstream>
using namespace std;

double Q2[6], M2[6], M2err[6], tmp;
ifstream NaData;
NaData.open("ProtonNatchmannData.txt", ios::in); 

	for (int i=0; i<6; i++)
	{
		NaData >> Q2[i] >> tmp >> M2[i] >> M2err[i] >> tmp >> tmp;
		cout << Q2[i] << " " << tmp << M2[i] << " " << M2err[i] << " " << tmp << " " << tmp << " " << endl;
	}

	return 0;
}

// pass to graph (plot)
