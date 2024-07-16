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
TString phi[] = {"Phenix-3HeAu-200","Phenix-CuAu-200","Phenix-pAl-200","Phenix-pAu-200","phenix-UU-193","star-AuAu-200","star-pp-200"};
TString pbar[] = {"Phenix-AuAu-130","Phenix-AuAu-200","Phenix-dAu-200","Phenix-pp-200","star-AUAu-62.4","star-CuCu-200","star-UU-193"};
TString p[] = {"Phenix-AuAu-130","Phenix-AuAu-200","Phenix-dAu-200","Phenix-pp-200","star-AuAu-62.4","star-CuCu-200","star-UU-193"};
TString kp[] = {"Phenix-AuAu-130","Phenix-AuAu-200","Phenix-dAu-200","Phenix-pp-200","star-UU-193"};
TString km[] = {"Phenix-AuAu-130","Phenix-AuAu-200","Phenix-dAu-200","Phenix-pp-200","star-UU-193"};
TString pip[] = {"Phenix-AuAu-130","Phenix-AuAu-200","Phenix-dAu-200","Phenix-pp-200","star-AUAu-62.4","star-CuCu-200","star-UU-193"};
TString pim[] = {"Phenix-AuAu-130","Phenix-AuAu-200","Phenix-dAu-200","Phenix-pp-200","star-AUAu-62.4","star-CuCu-200","star-UU-193"};
TString AuAu200[] = {"k-","k+","p","#bar{p}","#pi-","#pi+","#pi^{0}","star-#phi"};
const int color[] = {kRed, kBlue, kMagenta, kCyan, kGreen+2, kYellow+4, kBlack};

void read2()
{   TSystemDirectory dir("data","./"); // assuming all data files are in the current directory
    TList *files = dir.GetListOfFiles();
    if (!files) {
        cout << "No files found in the directory!" << endl;
        return;
    }
    

    TCanvas* c1 = new TCanvas("c1","Pt vs Yield",800,600);
    c1->SetLogy();
    c1->SetLogx();
    gStyle->SetOptStat(0);
    gStyle->SetLegendBorderSize(0);

    TLegend* leg = new TLegend(0.15,0.55,0.3,0.89);

    TGraphMultiErrors* g[10][15];
    auto mg = new TMultiGraph();
    mg->SetTitle("phenix AuAu200;#frac{dN_{ch}}{d#eta}; int.Yield");
    
    int style_index = 2;
    int color_index = 0;
    int file_index = 0;
    for (int i = 0; i < files->GetSize(); ++i) 
    {
        TSystemFile *file = (TSystemFile*) files->At(i);
        if (!file) continue;

        TString filename = file->GetName();
        if (!filename.Contains("phenix")) continue;
        if (!filename.EndsWith(".txt")) continue;
        //if (!filename.Contains("AuAu")) continue;
        if (!filename.Contains("pp")) continue;
        if (!filename.Contains("200")) continue;
        //if (!filename.Contains("k+")) continue;

        ifstream inputfile(filename);
        if (!inputfile) {
            cout << "Unable to open input file: " << filename << endl;
            continue;
        }
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

                if(pt[CurrentCentIndex][CurrentPtIndex] > 1 && pt[CurrentCentIndex][CurrentPtIndex] < 2)
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
        cout << Nch[i]<< "\t"<< Ncher[i] << "\t" << integrated_yield[i]<< "\t"<<  stat_integrated_yield[i] << "\t" <<  sys_integrated_yield[i] <<endl;
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
        if(i==0) leg->AddEntry(g[k][i], AuAu200[k], "p");
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