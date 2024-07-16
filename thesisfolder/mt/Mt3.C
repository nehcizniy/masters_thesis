#include <iostream>
#include <fstream>
#include <TGraph.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TGraphMultiErrors.h>
#include <TGraphErrors.h>
#include <TMultiGraph.h>
#include <TAttFill.h>
#include <TAxis.h>
#include <TSystemDirectory.h>
#include <TSystemFile.h>
#include <TF1.h>
#include <TH1F.h>
using namespace std;

//add legend names
    auto ratio_mass_parameters0 = new TMultiGraph();
    auto ratio_mass_parameters1 = new TMultiGraph();
Double_t parameter0[100][100];
Double_t parameter1[100][100];
TString filename_array[100];
TString parameter_index_collab[] = {"phenix","star"};
TString parameter_index_system[] = {"AuAu","CuAu","dAu","3HeAu","UU","pAl","pAu","CuCu"};
TString parameter_index_particle[] = {"k+","k-","-p-","pbar","pi+","pi-","pi0","phi"};
Double_t parameter_index_mass[] = {493.677, 493.677, 938.272, 938.272, 139.570, 139.570, 134.9768, 1019.461};
Double_t error_parameter0[100][100];
Double_t error_parameter1[100][100];
const int color[] = {kRed, kBlue, kMagenta, kCyan, kGreen+2, kYellow+4, kBlack, kGray};
Double_t particle_mass[] = {493.677, 493.677, 938.272, 938.272, 139.570, 139.570, 134.9768, 134.9768, 1019.461};//k+, k-, p, pbar, pi+, pi-, pi0, pi0, phi
Double_t kaon_mass = 493.677;
Double_t proton_mass = 938.272;
Double_t pion_mass = 139.570;
Double_t pi0_mass = 134.9768;
Double_t phi_mass = 1019.461;
Double_t particle_mass2[] = {493.677, 493.677, 493.677, 493.677, 938.272, 938.272, 938.272, 938.272, 1019.461, 1019.461, 1019.461, 1019.461, 1019.461, 139.570, 139.570, 139.570, 139.570, 134.9768, 134.9768, 134.9768, 134.9768, 134.9768, 134.9768, 134.9768, 493.677, 493.677, 938.272, 938.272, 1019.461, 139.570, 139.570};
Double_t particle_mass3[] = {493.677, 493.677, 938.272, 938.272, 139.570, 139.570};

void Mt3()
{   TSystemDirectory dir("data","./"); // assuming all data files are in the current directory
    TList *files = dir.GetListOfFiles();
    if (!files) {
        cout << "No files found in the directory!" << endl;
        return;
    }
    
//decide what file is used
cout << "Number of collaboration(s)(type 0 if all are included): " <<endl;
int Num_collab = 0;
cin >> Num_collab;
std::vector<TString> collaboration(Num_collab);
if(Num_collab != 0)
{
    for(int i = 0; i< Num_collab; i++)
    {
        cout << "Input collaboration(phenix,star,alice,atlas) #" << i+1 << ": " << endl;
        cin >> collaboration[i];
    }
}
cout << "Number of systems(s)(type 0 if all are included): " <<endl;
int Num_sys = 0;
cin >> Num_sys;
std::vector<TString> collision(Num_sys);
if(Num_sys != 0)
{
    for(int i = 0; i< Num_sys; i++)
    {
        cout << "Input system(AuAu,CuAu,dAu,3HeAu,CuCu,UU,pAl,pAu,pp,etc.) #" << i+1 << ": " << endl;
        cin >> collision[i];
    }
}
cout << "Number of type(s) of particles(type 0 if all are included): " <<endl;
int Num_part = 0;
cin >> Num_part;
std::vector<TString> particle(Num_part);
if(Num_part != 0)
{
    for(int i = 0; i< Num_part; i++)
    {
        cout << "Input particle(k+,k-,pi+,pi-,-p-,pbar,pi0,phi) #" << i+1 << ": " << endl;
        cin >> particle[i];
    }
}
cout << "Number of energy(type 0 if all are included): " <<endl;
int Num_energy = 0;
cin >> Num_energy;
std::vector<TString> energy(Num_energy);
if(Num_energy != 0)
{
    for(int i = 0; i< Num_energy; i++)
    {
        cout << "Input energy #" << i+1 << ": " << endl;
        cin >> energy[i];
    }
}
double int_low;
double int_high;
cout << "integration_range: " << endl;
cin >> int_low;
cin >> int_high;


    int style_index = 2;
    int color_index = 0;
    int file_index = 0;
    int total_num_of_files = 1;
    if(Num_collab != 0){total_num_of_files = total_num_of_files*Num_collab;}
    if(Num_sys != 0){total_num_of_files = total_num_of_files*Num_sys;}
    if(Num_part != 0){total_num_of_files = total_num_of_files*Num_part;}
    if(Num_energy != 0){total_num_of_files = total_num_of_files*Num_energy;}
    TString raw_legend_names[total_num_of_files];
    
    TGraphErrors* p0[100][100];
    TGraphErrors* p1[100][100];
    TH1F *spectra_fill[100][100];
    TGraphMultiErrors* spectra_fit[100][100];
    TCanvas* c1 = new TCanvas("c1","Pt vs Yield",800,600);
    c1->SetLogy();
    c1->SetLogx();
    gStyle->SetOptStat(0);
    gStyle->SetLegendBorderSize(0);

    //TLegend* leg = new TLegend(0.15,0.55,0.3,0.89);
    //leg->SetFillStyle(0);
    TGraphMultiErrors* g[100][100];
    auto mg = new TMultiGraph();
    mg->SetTitle(Form("%f - %f",int_low,int_high));
    mg->GetXaxis()->SetTitle("mT");
    mg->GetYaxis()->SetTitle("inv.Yield");

    for (int i = 0; i < files->GetSize(); ++i) 
    {
        TSystemFile *file = (TSystemFile*) files->At(i);
        if (!file) continue;

        TString filename = file->GetName();

        bool pass_collab = (Num_collab == 0);
        for (int j = 0; j < Num_collab; j++) 
        {
            if (filename.Contains(collaboration[j])) 
            {
                pass_collab = true;
                break;
            }
        }
        if (!pass_collab) continue;

        bool pass_sys = (Num_sys == 0);
        for (int j = 0; j < Num_sys; j++) 
        {
            if (filename.Contains(collision[j])) 
            {
                pass_sys = true;
                break;
            }
        }
        if (!pass_sys) continue;

        bool pass_part = (Num_part == 0);
        for (int j = 0; j < Num_part; j++) 
        {
            if (filename.Contains(particle[j])) 
            {
                pass_part = true;
                break;
            }
        }
        if (!pass_part) continue;

        bool pass_energy = (Num_energy == 0);
        for (int j = 0; j < Num_energy; j++) 
        {
            if (filename.Contains(energy[j])) 
            {
                pass_energy = true;
                break;
            }
        }
        if (!pass_energy) continue;

        if (!filename.EndsWith(".txt")) continue;

        ifstream inputfile(filename);
        if (!inputfile) {
            cout << "Unable to open input file: " << filename << endl;
            continue;
        }
raw_legend_names[file_index] = filename;
cout<< "Following files are being used" << endl;
cout<< filename <<endl;
filename_array[file_index]=filename;


        char line[100];
        char cent[100];
        int centlow[100];
        int centhigh[100];
        Float_t Nch[100];
        float Ncher[100];
        int NumCentIndex = 0;
        int CurrentCentIndex = -1;
        int CurrentPtIndex = 0;
        float pt[100][100];
        float mt[100][100];
        Double_t ptlow[100][100];
        Double_t pthigh[100][100];
        float yield[100][100];
        int bin_num[100];
        int fill_num[100];
        float dn_deta[100][100];
        float errdn_deta[100][100];
        float statp[100][100];
        float statm[100][100];
        Double_t sysp[100][100];
        Double_t sysm[100][100];
        


        while(inputfile.getline(line, sizeof(line)))
        {
            if(line[0] == 'c')
            {
                ++NumCentIndex;
                CurrentCentIndex = NumCentIndex - 1;
                CurrentPtIndex = 0;
                sscanf(line, "%s %i %i %f %f",//add %f %f
                &cent[CurrentCentIndex],
                &centlow[CurrentCentIndex],
                &centhigh[CurrentCentIndex],
                &Nch[CurrentCentIndex],
                &Ncher[CurrentCentIndex]
                //add&Nch[CurrentCentIndex], &Ncher[CurrentCentIndex]
                );
            }
            else if(line[0] == 'p'||line[0] == '\n' ||line[0] == ' '||line[0] == '\t' ||line[0] == '\r')
            {
                //do nothing
            }
            else
            {
                sscanf(line, "%f %lf %lf %f %f %f %lf %lf", 
                &pt[CurrentCentIndex][CurrentPtIndex],
                &ptlow[CurrentCentIndex][CurrentPtIndex],
                &pthigh[CurrentCentIndex][CurrentPtIndex],
                &yield[CurrentCentIndex][CurrentPtIndex],
                &statp[CurrentCentIndex][CurrentPtIndex],
                &statm[CurrentCentIndex][CurrentPtIndex],
                &sysp[CurrentCentIndex][CurrentPtIndex],
                &sysm[CurrentCentIndex][CurrentPtIndex]);
                dn_deta[CurrentCentIndex][CurrentPtIndex] = Nch[CurrentCentIndex];
                errdn_deta[CurrentCentIndex][CurrentPtIndex] = Ncher[CurrentCentIndex];
                for(int i=0;i<8;++i)
        {
            if(filename.Contains(parameter_index_particle[i]))
            {
                mt[CurrentCentIndex][CurrentPtIndex] = sqrt(pt[CurrentCentIndex][CurrentPtIndex]*pt[CurrentCentIndex][CurrentPtIndex]+0.000001*parameter_index_mass[i]*parameter_index_mass[i])-0.001*parameter_index_mass[i];
                //cout<<pt[CurrentCentIndex][CurrentPtIndex]<<"    "<<mt[CurrentCentIndex][CurrentPtIndex]<<endl;
            }
        }
                if (pt[CurrentCentIndex][CurrentPtIndex]<=5)
                {
                    fill_num[CurrentCentIndex] +=1;
                    //cout << "fill_num[" <<CurrentCentIndex <<"]= " << fill_num[CurrentCentIndex]<<endl;
                }
                //cout << pt[CurrentCentIndex][CurrentPtIndex] << endl;


                ++CurrentPtIndex;
            }
        bin_num[CurrentCentIndex] = CurrentPtIndex + 1;
        }
    
    inputfile.close();


    int k = file_index;
    for (int i = 0; i < NumCentIndex; ++i) 
    {
    //cout << k << "\t" << integrated_yield[i] << "\t" << integrated_yield_corrected[i]<< "\t"<<  stat_integrated_yield[i]<< "\t"<<  sys_integrated_yield[i]<<endl;
        g[k][i] = new TGraphMultiErrors(bin_num[i],mt[i],yield[i],0,0,statp[i], statp[i]);

        //g[k][i]->SetTitle("pi0 at 200GeV"); // set the title of the graph
        
        //g[k]->AddYError(NumCentIndex,sys_integrated_yield, sys_integrated_yield);
        g[k][i]->SetMinimum(0.00000000001);
        g[k][i]->SetMaximum(100.);
        //g[k]->GetAttLine(0)->SetLineColorAlpha(kRed, 1);
        //g[k][i]->GetAttLine(1)->SetLineColor(kBlue);
        //g[k]->GetAttFill(1)->SetFillStyle(0);
        //g[k]->SetMarkerStyle(20+color_index); 
        //g[k]->SetMarkerSize(.7); 
        //g[k][i]->SetMarkerColorAlpha(color[color_index],1);//color[color_index]
        //g[k][i]->SetLineColor(color[color_index]); 
        //g[k]->SetLineWidth(1); 
        g[k][i]->SetFillStyle(0);

        //leg->AddEntry(g[k][i], filename, "p");
        //g[k][i]->Draw("APE ; Z ; 5 s = 0.5");
        mg->Add(g[k][i], "APE ; Z ; 5 s = 0.5");
        mg->Draw("APE");
        //fit_int_yield_index->Draw("same");
    }
    //leg->Draw("p");
 
    style_index++;
    color_index++;
    file_index++;

}

gPad->Modified();
   mg->GetXaxis()->SetLimits(.1,20.);
   //mg->GetYaxis()->SetRangeUser(0.001,200);
   mg->SetMinimum(0.0001);
   mg->SetMaximum(1000.);
gPad->Modified();

}