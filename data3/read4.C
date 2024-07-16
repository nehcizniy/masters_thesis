#include <iostream>
#include <fstream>
#include <TGraph.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TGraphMultiErrors.h>
#include <TAttFill.h>
#include <TAxis.h>
#include <TSystemDirectory.h>
#include <TSystemFile.h>
using namespace std;

//add legend names
TString pi0[] = {"Phenix-3HeAu-200","Phenix-AuAu-200","Phenix-CuAu-200","Phenix-dAu-200","Phenix-pAl-200","Phenix-pAu-200","Phenix-pp-200"};
TString phi[] = {"Phenix-3HeAu-200","Phenix-CuAu-200","Phenix-pAl-200","Phenix-pAu-200","phenix-UU-193"};
TString pbar[] = {"Phenix-AuAu-130","Phenix-AuAu-200","Phenix-dAu-200","Phenix-pp-200","star-AUAu-62.4","star-CuCu-200","star-UU-193"};
TString p[] = {"Phenix-AuAu-130","Phenix-AuAu-200","Phenix-dAu-200","Phenix-pp-200","star-AuAu-62.4","star-CuCu-200","star-UU-193"};
TString kp[] = {"Phenix-AuAu-130","Phenix-AuAu-200","Phenix-dAu-200","Phenix-pp-200","star-UU-193"};
TString km[] = {"Phenix-AuAu-130","Phenix-AuAu-200","Phenix-dAu-200","Phenix-pp-200","star-UU-193"};
TString pip[] = {"Phenix-AuAu-130","Phenix-AuAu-200","Phenix-dAu-200","Phenix-pp-200","star-AUAu-62.4","star-CuCu-200","star-UU-193"};
TString pim[] = {"Phenix-AuAu-130","Phenix-AuAu-200","Phenix-dAu-200","Phenix-pp-200","star-AUAu-62.4","star-CuCu-200","star-UU-193"};
Double_t parameter0[9];
Double_t parameter1[9];
Double_t error_parameter0[9];
Double_t error_parameter1[9];
const int color[] = {kRed, kBlue, kMagenta, kCyan, kGreen+2, kYellow+4, kBlack};

void read4()
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

    int style_index = 2;
    int color_index = 0;
    int file_index = 0;
    int total_num_of_files = 1;
    if(Num_collab != 0){total_num_of_files = total_num_of_files*Num_collab;}
    if(Num_sys != 0){total_num_of_files = total_num_of_files*Num_sys;}
    if(Num_part != 0){total_num_of_files = total_num_of_files*Num_part;}
    if(Num_energy != 0){total_num_of_files = total_num_of_files*Num_energy;}
    TString raw_legend_names[total_num_of_files];
    TCanvas* c1 = new TCanvas("c1","Pt vs Yield",800,600);
    c1->SetLogy();
    c1->SetLogx();
    gStyle->SetOptStat(0);
    gStyle->SetLegendBorderSize(0);

    TLegend* leg = new TLegend(0.15,0.55,0.3,0.89);

    TGraphMultiErrors* g[total_num_of_files][15];
    auto mg = new TMultiGraph();
    mg->SetTitle("k-; #frac{dN_{ch}}{d#eta}; int.Yield");

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
    /*ifstream inputfile; 
    inputfile.open("phenix-k+-AuAu-200.txt");
    if(!inputfile){
        cout << "Unable to open input file";
        return;
    }
    */

        char line[100];
        char cent[15];
        int centlow[15];
        int centhigh[15];
        Float_t Nch[15];
        float Ncher[15];
        int NumCentIndex = 0;
        int CurrentCentIndex = -1;
        int CurrentPtIndex = 0;
        float pt[15][100];
        float ptlow[15][100];
        float pthigh[15][100];
        float yield[15][100];
        Float_t integrated_yield[15]={0};
        Float_t stat_integrated_yield[15]={0};
        Double_t sys_integrated_yield[15]={0};
        float dn_deta[15][100]={0};
        float errdn_deta[15][100]={0};
        float statp[15][100];
        float statm[15][100];
        Double_t sysp[15][100];
        Double_t sysm[15][100];

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
                sscanf(line, "%f %f %f %f %f %f %lf %lf", 
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

                //cout << pt[CurrentCentIndex][CurrentPtIndex] << endl;

                if(pt[CurrentCentIndex][CurrentPtIndex] > 2 && pt[CurrentCentIndex][CurrentPtIndex] < 3)
                {
                    integrated_yield[CurrentCentIndex] += 2*TMath::Pi() * pt[CurrentCentIndex][CurrentPtIndex] * yield[CurrentCentIndex][CurrentPtIndex] * (pthigh[CurrentCentIndex][CurrentPtIndex] - ptlow[CurrentCentIndex][CurrentPtIndex]);
                    stat_integrated_yield[CurrentCentIndex] += pow(2*TMath::Pi() * pt[CurrentCentIndex][CurrentPtIndex] * statp[CurrentCentIndex][CurrentPtIndex] * (pthigh[CurrentCentIndex][CurrentPtIndex] - ptlow[CurrentCentIndex][CurrentPtIndex]),2);
                    sys_integrated_yield[CurrentCentIndex] += pow(2*TMath::Pi() * pt[CurrentCentIndex][CurrentPtIndex] * sysp[CurrentCentIndex][CurrentPtIndex] * (pthigh[CurrentCentIndex][CurrentPtIndex] - ptlow[CurrentCentIndex][CurrentPtIndex]),2);
                //cout<< integrated_yield[CurrentCentIndex] <<endl;
                }

                ++CurrentPtIndex;
            }
        }

    inputfile.close();
    
    for (int i = 0; i < NumCentIndex; ++i) 
    {   stat_integrated_yield[i] = sqrt(stat_integrated_yield[i]);
        sys_integrated_yield[i] = sqrt(sys_integrated_yield[i]);
        cout << Nch[i] << "\t" << integrated_yield[i]<< "\t"<<  stat_integrated_yield[i]<<endl;
        int k = file_index;

        g[k][i] = new TGraphMultiErrors(NumCentIndex,Nch,integrated_yield,Ncher,Ncher,stat_integrated_yield,stat_integrated_yield);
        //g[k][i]->SetTitle("pi0 at 200GeV"); // set the title of the graph
        g[k][i]->AddYError(NumCentIndex,sys_integrated_yield, sys_integrated_yield);
        g[k][i]->SetMinimum(0.00000000001);
        g[k][i]->SetMaximum(100.);
        g[k][i]->GetAttLine(0)->SetLineColor(kRed);
        //g[k][i]->GetAttLine(1)->SetLineColor(kBlue);
        g[k][i]->GetAttFill(1)->SetFillStyle(0);
        g[k][i]->SetMarkerStyle(20+color_index); 
        g[k][i]->SetMarkerSize(.7); 
        g[k][i]->SetMarkerColor(color[color_index]);
        g[k][i]->SetLineColor(color[color_index]); 
        g[k][i]->SetLineWidth(1); 
        g[k][i]->SetFillStyle(0);
        //g[k][i]->GetXaxis()->SetTitle("frac{dN_{ch}}{d#eta}"); 
        //g[k][i]->GetYaxis()->SetTitle("int.yield");
        //leg->AddEntry(g[k][i],Form("%d - %d",centlow[i],centhigh[i]),"lep"); // add the graph to the legend
        //if(i==0) gr->Draw("APL"); // draw the first graph with axes
        //else gr->Draw("PLSAME");
        if(i==0) leg->AddEntry(g[k][i], filename, "p");
        mg->Add(g[k][i], "APE ; Z ; 5 s = 0.5");
        mg->Draw("APE");
    }
    leg->Draw("p");
    style_index++;
    color_index++;
    file_index++;
}
gPad->Modified();
   mg->GetXaxis()->SetLimits(.5,1000.);
   //mg->GetXaxis()->SetRangeUser(2,10);
   mg->SetMinimum(0.0001);
   mg->SetMaximum(100.);
gPad->Modified();
}