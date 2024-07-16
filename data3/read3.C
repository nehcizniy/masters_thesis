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
char* AuAu200only[] = {"k+ 2013","k-","p","#bar{p}","#pi+","#pi-","#pi^{0} 2008","#pi^{0} 2003","star-#phi"};
char* AuAu200[] = {"k+","pp-k+","k-","pp-k-","p","pp-p","#bar{p}","pp-#bar{p}","#pi+","pp-#pi+","#pi-","pp-#pi-","#pi^{0}-2","#pi^{0}","pp-#pi^{0}","star-#phi","pp-star-#phi","pp"};
const int color[] = {kRed, kBlue, kMagenta, kCyan, kGreen+2, kYellow+4, kBlack, kOrange, kPink};
Double_t Nch2 = 2.38;
float Ncher2 = 0.09;
Double_t integrated_yield2[8]={0.0111776,0.0111776,0.00807284,0.00679928,0.0356458,0.0358609,0.0418221,0.0418221};
Double_t stat_integrated_yield2[8]={0.000133128,0.000133128,7.61375e-05,5.56e-05,0.000261685,0.000309277,0.000561956,0.000561956};
Double_t sys_integrated_yield2[8]={0.000304975,0.000304975,0.000419242,0.000372123,0.001015,0.00102828,0.00254404,0.00254404};



void read3()
{   TSystemDirectory dir("data","./"); // assuming all data files are in the current directory
    TList *files = dir.GetListOfFiles();
    if (!files) {
        cout << "No files found in the directory!" << endl;
        return;
    }
    
    //fix bin shift
    
    TF1* fHagedorn = new TF1("fHagedorn","[0]/pow((exp(-[1]*x -[2]*x*x) + x/[3]),[4])", 0.5, 5.0);
    fHagedorn->SetParameters(40.58, 0.214, 0.142, 0.559, 8.124);
    TCanvas* c0[20][20];
    
    TGraphMultiErrors* spectra_fit[20][20];
    //TLegend* ptleg[20][20]
    TCanvas* c1 = new TCanvas("c1","Pt vs Yield",800,600);
    c1->SetLogy();
    c1->SetLogx();
    gStyle->SetOptStat(0);
    gStyle->SetLegendBorderSize(0);

    TLegend* leg = new TLegend(0.15,0.55,0.3,0.89);
    leg->SetFillStyle(0);

    TGraphMultiErrors* g[20][20];
    auto mg = new TMultiGraph();
    mg->SetTitle("phenix AuAu200 scaled by pp200(1-2GeV);#frac{dN_{ch}}{d#eta}; int.Yield");
    
    int style_index = 2;
    int color_index = 0;
    int file_index = 0;


    for (int i = 0; i < files->GetSize(); ++i) 
    {
        TSystemFile *file = (TSystemFile*) files->At(i);
        if (!file) continue;

        TString filename = file->GetName();
        //if (!filename.Contains("phenix")) continue;
        if (!filename.EndsWith(".txt")) continue;
        if (!filename.Contains("AuAu")) continue;
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
        char cent[20];
        int centlow[20];
        int centhigh[20];
        Float_t Nch[20];
        float Ncher[20];
        int NumCentIndex = 0;
        int CurrentCentIndex = -1;
        int CurrentPtIndex = 0;
        float pt[20][100];
        float ptlow[20][100];
        float pthigh[20][100];
        float yield[20][100];
        Float_t integrated_yield[20]={0};
        Float_t stat_integrated_yield[20]={0};
        Double_t sys_integrated_yield[20]={0};
        float dn_deta[20][100]={0};
        float errdn_deta[20][100]={0};
        float statp[20][100];
        float statm[20][100];
        double sysp[20][100];
        double sysm[20][100];

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

    /*for (int i = 0; i < NumCentIndex; ++i) 
    {   
        int k = file_index;
        c0[k][i] = new TCanvas(Form("%d - %d - %d",k, centlow[i],centhigh[i]), Form("%s - %d - %d",AuAu200[k], centlow[i],centhigh[i]), 800, 600);
        c0[k][i]->SetLogy();
        c0[k][i]->SetLogx(0);
        gStyle->SetOptStat(0);
        gStyle->SetLegendBorderSize(0);
        spectra_fit[k][i] = new TGraphMultiErrors(CurrentPtIndex, pt[i], yield[i], 0,0, statp[i], statp[i]);
        spectra_fit[k][i]->AddYError(CurrentPtIndex, sysp[i],sysp[i]);
        spectra_fit[k][i]->Fit(fHagedorn);
        spectra_fit[k][i]->SetTitle(AuAu200[k]);

        //spectra_fit[k][i]->SetTitle(Form("%s cent_%d-%d", hdvi, i. i+1));
        spectra_fit[k][i]->Draw("APE");
    }*/

    for (int i = 0; i < NumCentIndex; ++i) 
    {
        stat_integrated_yield[i] = sqrt(stat_integrated_yield[i]);
        sys_integrated_yield[i] = sqrt(sys_integrated_yield[i]);
        int k = file_index;

        //cout << k << "\t" << Nch[i] << "\t" << integrated_yield[i]<< "\t"<<  stat_integrated_yield[i]<< "\t"<< stat_integrated_yield2[k]<< endl;

        Nch[i]=Nch[i]/2.38;
        Ncher[i]=Nch[i]*sqrt(pow(0.09/2.38,2)+pow(Ncher[i]/(2.38*Nch[i]),2));
        integrated_yield[i]=integrated_yield[i]/integrated_yield2[k];
        //cout << integrated_yield[i] << endl;
        stat_integrated_yield[i]=integrated_yield[i]*sqrt(pow(stat_integrated_yield[i]/(integrated_yield[i]*integrated_yield2[k]),2)+pow(stat_integrated_yield2[k]/integrated_yield2[k],2));
        sys_integrated_yield[i]=integrated_yield[i]*sqrt(pow(sys_integrated_yield[i]/(integrated_yield[i]*integrated_yield2[k]),2)+pow(sys_integrated_yield2[k]/integrated_yield2[k],2));

       // cout << k << "\t" << Nch[i] << "\t" << integrated_yield[i]<< "\t"<<  stat_integrated_yield[i] << "\t"<< stat_integrated_yield2[k] << "\t"<<  sys_integrated_yield[i]<<endl;
    }
    
    for (int i = 0; i < NumCentIndex; ++i) 
    {   //stat_integrated_yield[i] = sqrt(stat_integrated_yield[i]);
        //sys_integrated_yield[i] = sqrt(sys_integrated_yield[i]);
        int k = file_index;

        cout << k << "\t" << Nch[i] << "\t" << Ncher[i] << "\t" << integrated_yield[i]<< "\t"<<  stat_integrated_yield[i]<< "\t"<<  sys_integrated_yield[i]<<endl;
        
        g[k][i] = new TGraphMultiErrors(NumCentIndex,Nch,integrated_yield,Ncher,Ncher,stat_integrated_yield,stat_integrated_yield);
        //g[k][i]->SetTitle("pi0 at 200GeV"); // set the title of the graph
        g[k][i]->AddYError(NumCentIndex,sys_integrated_yield, sys_integrated_yield);
        g[k][i]->SetMinimum(0.00000000001);
        g[k][i]->SetMaximum(100.);
        g[k][i]->SetMarkerStyle(20+color_index); 
        g[k][i]->SetMarkerSize(.7); 
        g[k][i]->SetMarkerColorAlpha(color[color_index],0.8);
        g[k][i]->SetLineColor(color[color_index]); 
        g[k][i]->SetLineWidth(1);
        g[k][i]->GetAttLine(0)->SetLineColorAlpha(kRed, 0.8);
        g[k][i]->GetAttLine(0)->SetLineColor(kRed);
        g[k][i]->GetAttLine(1)->SetLineColor(kBlue);
        g[k][i]->GetAttFill(1)->SetFillStyle(0); 
        g[k][i]->SetFillStyle(0);
        //g[k][i]->GetXaxis()->SetTitle("frac{dN_{ch}}{d#eta}"); 
        //g[k][i]->GetYaxis()->SetTitle("int.yield");
        //leg->AddEntry(g[k][i],Form("%d - %d",centlow[i],centhigh[i]),"lep"); // add the graph to the legend
        //if(i==0) gr->Draw("APL"); // draw the first graph with axes
        //else gr->Draw("PLSAME");
        if(i==0) {leg->AddEntry(g[k][i], AuAu200only[k], "p");}
        //g[k][i]->Draw("APE ; Z ; 5 s = 0.5");
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
   //mg->SetMinimum(0.0001);
   //mg->SetMaximum(1000.);
gPad->Modified();
}