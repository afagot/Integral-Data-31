#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <random>
#include <sstream>
#include <assert.h>

#include "TFile.h"
#include "TH2I.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TVirtualFitter.h"
#include "TList.h"

using namespace std;

string intTostring(int value){
	string word;
	stringstream ss;
	ss << setw(2) << setfill('0') << value;
	ss >> word;

	return word;
}

double ErrorMaximumX(TF1* function, double Xmax){
	double Af = function->GetParameter(0);
	double dAf = function->GetParError(0);

	double Xf = function->GetParameter(1);
	double dXf = function->GetParError(1);

	double Sf = function->GetParameter(2);
	double dSf = function->GetParError(2);

	double Lf = function->GetParameter(3);
	double dLf = function->GetParError(3);

	double If = function->GetParameter(4);
	double dIf = function->GetParError(4);

	double Ab = function->GetParameter(5);
	double dAb = function->GetParError(5);

	double Xb = function->GetParameter(6);
	double dXb = function->GetParError(6);

	double Sb = function->GetParameter(7);
	double dSb = function->GetParError(7);

	double Lb = function->GetParameter(8);
	double dLb = function->GetParError(8);

	double Ib = function->GetParameter(9);
	double dIb = function->GetParError(9);


	double F = Af * exp(-0.5*pow(Xmax-Xf,2));
}

#endif // FONCTIONS_H
