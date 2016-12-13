#include "../include/fonctions.h"

using namespace std;

int main(int argc ,char *argv[]){
	stringstream converter;
	converter << argv[0];
	string program;
	converter >> program;
	converter.clear();

	if(argc != 1){
			cout << "[Integrals] expects to have 1 parameter\n";
			cout << "[Offline] USAGE is : " << program << "\n";
			return -1;
	} else if(argc == 1){
		int HV[13] = {8500,8600,8700,8800,8900,9000,9100,9200,9300,9400,9500,9600,9700};

		TH1I* AllRuns = new TH1I("Cumul","Cumul",16,48.5,64.5);

		//output csv file with integrals results for cumulated data
		ofstream CSVCumulated("CumulData.csv", ios::out);

		for(int i=0; i< 13; i++){

			//intput ROOT file
			string ROOTName = "/home/alex/Desktop/RPCs/Lyon_Electronics/Alexis_DATA/Data/Gamma_off/Run310814/Processed/Run310814_nocuts/RootData_Run310814/ROOT_RE-2-BARC-161_HV_"
					+ intTostring(HV[i]) + "_source_off_B2_31_08_2014.root";
			TFile ROOTinput(ROOTName.c_str(),"READ");
			TH1I* Profile = (TH1I*)ROOTinput.Get("StripProfile");
			AllRuns->Add(Profile,1);

			//output csv file with integrals results
			ofstream CSVData("Data.csv", ios::out);

			//*****************************************************************************************************

			TF1* AllMuons = new TF1("fit","[0]*exp(-0.5*((x-[1])/[2])**2) / (1 + exp(-[3]*(x-[4])))+[5]*exp(-0.5*((x-[6])/[7])**2) / (1 + exp(-[8]*(x-[9])))",48.5,64.5);
			AllMuons->SetParLimits(0,1,2000);
			AllMuons->SetParameter(1,58);
			AllMuons->SetParLimits(1,48.5,64.5);
			AllMuons->SetParameter(2,6);
			AllMuons->SetParLimits(2,1,32);
			AllMuons->SetParameter(3,-1);
			AllMuons->SetParLimits(3,-10,-0.01);
			AllMuons->SetParameter(4,56);
			AllMuons->SetParLimits(4,48.5,64.5);
			AllMuons->SetParLimits(5,1,500);
			AllMuons->SetParameter(6,59);
			AllMuons->SetParLimits(6,48.5,64.5);
			AllMuons->SetParameter(7,2);
			AllMuons->SetParLimits(7,1,32);
			AllMuons->SetParameter(8,1);
			AllMuons->SetParLimits(8,0.01,10);
			AllMuons->SetParameter(9,56);
			AllMuons->SetParLimits(9,48.5,64.5);
			Profile->Fit(AllMuons,"QR");
			Profile->Draw();

			cout << "What to do?\n";
			cin.get();

			//*****************************************************************************************************

			TF1* ForwardMuons = new TF1("fit_f","[0]*exp(-0.5*((x-[1])/[2])**2) / (1 + exp(-[3]*(x-[4])))",33,64);
			ForwardMuons->FixParameter(0,AllMuons->GetParameter(0));
			ForwardMuons->FixParameter(1,AllMuons->GetParameter(1));
			ForwardMuons->FixParameter(2,AllMuons->GetParameter(2));
			ForwardMuons->FixParameter(3,AllMuons->GetParameter(3));
			ForwardMuons->FixParameter(4,AllMuons->GetParameter(4));

			CSVData << Profile->GetEntries() << '\t'
					<< ForwardMuons->Integral(33.,64.) << '\t'
					<< ForwardMuons->Integral(33.,48.) << '\t'
					<< Profile->GetMaximum() << '\t'
					<< Profile->GetMaximumBin()+48 << '\t'
					<< ForwardMuons->GetMaximum() << '\t'
					<< ForwardMuons->GetMaximumX() << '\t';

			//*****************************************************************************************************

			TF1* BackwardMuons = new TF1("fit_b","[0]*exp(-0.5*((x-[1])/[2])**2) / (1 + exp(-[3]*(x-[4])))",33,64);
			BackwardMuons->FixParameter(0,AllMuons->GetParameter(5));
			BackwardMuons->FixParameter(1,AllMuons->GetParameter(6));
			BackwardMuons->FixParameter(2,AllMuons->GetParameter(7));
			BackwardMuons->FixParameter(3,AllMuons->GetParameter(8));
			BackwardMuons->FixParameter(4,AllMuons->GetParameter(9));

			CSVData << BackwardMuons->Integral(33.,64.) << '\t';

			Profile->GetXaxis()->SetRange(9.5,16.5);

			CSVData << Profile->GetMaximum() << '\t'
					<< Profile->GetMaximumBin()+48 << '\t'
					<< BackwardMuons->GetMaximum(57.5,64) << '\t'
					<< BackwardMuons->GetMaximumX(57.5,64) << '\t';

			//*****************************************************************************************************

			CSVData << endl;

			CSVData.close();
			ROOTinput.Close();
		}

		//*****************************************************************************************************

		TF1* AllMuons = new TF1("fit","[0]*exp(-0.5*((x-[1])/[2])**2) / (1 + exp(-[3]*(x-[4])))+[5]*exp(-0.5*((x-[6])/[7])**2) / (1 + exp(-[8]*(x-[9])))",49,64);
		AllMuons->SetParLimits(0,1,2000);
		AllMuons->SetParameter(1,58);
		AllMuons->SetParLimits(1,48.5,64.5);
		AllMuons->SetParameter(2,6);
		AllMuons->SetParLimits(2,1,32);
		AllMuons->SetParameter(3,-1);
		AllMuons->SetParLimits(3,-10,-0.01);
		AllMuons->SetParameter(4,56);
		AllMuons->SetParLimits(4,48.5,64.5);
		AllMuons->SetParLimits(5,1,500);
		AllMuons->SetParameter(6,59);
		AllMuons->SetParLimits(6,48.5,64.5);
		AllMuons->SetParameter(7,2);
		AllMuons->SetParLimits(7,1,32);
		AllMuons->SetParameter(8,1);
		AllMuons->SetParLimits(8,0.01,10);
		AllMuons->SetParameter(9,56);
		AllMuons->SetParLimits(9,48.5,64.5);
		AllRuns->Fit(AllMuons,"QR");
		AllRuns->Draw();
		AllMuons->SetRange(33,64);

		cout << "What to do?\n";
		cin.get();

		//*****************************************************************************************************

		TF1* ForwardMuons = new TF1("fit_f","[0]*exp(-0.5*((x-[1])/[2])**2) / (1 + exp(-[3]*(x-[4])))",33,64);
		ForwardMuons->FixParameter(0,AllMuons->GetParameter(0));
		ForwardMuons->FixParameter(1,AllMuons->GetParameter(1));
		ForwardMuons->FixParameter(2,AllMuons->GetParameter(2));
		ForwardMuons->FixParameter(3,AllMuons->GetParameter(3));
		ForwardMuons->FixParameter(4,AllMuons->GetParameter(4));

		CSVCumulated << AllRuns->GetEntries() << '\t'
					 << ForwardMuons->Integral(33.,64.) << '\t'
					 << AllMuons->Integral(33.,48.) << '\t'
					 << AllRuns->GetMaximum() << '\t'
					 << AllRuns->GetMaximumBin()+48 << '\t'
					 << ForwardMuons->GetMaximum() << '\t'
					 << ForwardMuons->GetMaximumX() << '\t';

		//*****************************************************************************************************

		TF1* BackwardMuons = new TF1("fit_b","[0]*exp(-0.5*((x-[1])/[2])**2) / (1 + exp(-[3]*(x-[4])))",33,64);
		BackwardMuons->FixParameter(0,AllMuons->GetParameter(5));
		BackwardMuons->FixParameter(1,AllMuons->GetParameter(6));
		BackwardMuons->FixParameter(2,AllMuons->GetParameter(7));
		BackwardMuons->FixParameter(3,AllMuons->GetParameter(8));
		BackwardMuons->FixParameter(4,AllMuons->GetParameter(9));

		CSVCumulated << BackwardMuons->Integral(33.,64.) << '\t';

		AllRuns->GetXaxis()->SetRange(9.5,16.5);

		CSVCumulated << AllRuns->GetMaximum() << '\t'
					 << AllRuns->GetMaximumBin()+48 << '\t'
					 << BackwardMuons->GetMaximum(57.5,64) << '\t'
					 << BackwardMuons->GetMaximumX(57.5,64) << '\t';

		//*****************************************************************************************************

		CSVCumulated << endl;

		CSVCumulated.close();

		//*****************************************************************************************************

		TFile ROOToutput("Cumulated.root","RECREATE");
		AllMuons->Write();
		ForwardMuons->Write();
		BackwardMuons->Write();
		AllRuns->Write();
		ROOToutput.Close();

		return 0;
	}
}
