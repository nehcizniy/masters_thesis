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
TString pi0[] = {"Phenix-3HeAu-200","Phenix-AuAu-200","Phenix-CuAu-200","Phenix-dAu-200","Phenix-pAl-200","Phenix-pAu-200","Phenix-pp-200"};
TString phi[] = {"Phenix-3HeAu-200","Phenix-CuAu-200","Phenix-pAl-200","Phenix-pAu-200","phenix-UU-193","star-AuAu-200","star-pp-200"};
TString pbar[] = {"Phenix-AuAu-130","Phenix-AuAu-200","Phenix-dAu-200","Phenix-pp-200","star-AUAu-62.4","star-CuCu-200","star-UU-193"};
TString p[] = {"Phenix-AuAu-130","Phenix-AuAu-200","Phenix-dAu-200","Phenix-pp-200","star-AuAu-62.4","star-CuCu-200","star-UU-193"};
TString kp[] = {"Phenix-AuAu-130","Phenix-AuAu-200","Phenix-dAu-200","Phenix-pp-200","star-UU-193"};
TString km[] = {"Phenix-AuAu-130","Phenix-AuAu-200","Phenix-dAu-200","Phenix-pp-200","star-UU-193"};
TString pip[] = {"Phenix-AuAu-130","Phenix-AuAu-200","Phenix-dAu-200","Phenix-pp-200","star-AuAu-62.4","star-CuCu-200","star-UU-193"};
TString pim[] = {"Phenix-AuAu-130","Phenix-AuAu-200","Phenix-dAu-200","Phenix-pp-200","star-AuAu-62.4","star-CuCu-200","star-UU-193"};
char* AuAu200only[] = {"k+ 2013","k-","p","#bar{p}","#pi+","#pi-","#pi^{0} 2003","#pi^{0} 2008","star-#phi 2004"};
char* AuAu200[] = {"k+","pp-k+","k-","pp-k-","p","pp-p","#bar{p}","pp-#bar{p}","#pi+","pp-#pi+","#pi-","pp-#pi-","#pi^{0}-2","#pi^{0}","pp-#pi^{0}","star-#phi","pp-star-#phi","pp"};
const int color[] = {kRed, kBlue, kMagenta, kCyan, kGreen+2, kYellow+4, kBlack, kOrange, kPink};
Double_t Nch2 = 2.38;
float Ncher2 = 0.09;
Double_t integrated_yield1_2[8]={0.0112681,0.0111776,0.00807284,0.00679928,0.0356458,0.0358609,0.0418221,0.0418221};
Double_t integrated_yield1_2_corrected[8]={0.0113596,0.0111917,0.00822862,0.00686195,0.0358591,0.0360479,0.0440541,0.0440541};
Double_t integrated_yield2_3[8]={};
Double_t integrated_yield2_3_corrected[8]={};
Double_t integrated_yield1_3[8]={};
Double_t integrated_yield1_3_corrected[8]={};
Double_t stat_integrated_yield2[8]={0.000133128,0.000133128,7.61375e-05,5.56e-05,0.000261685,0.000309277,0.000561956,0.000561956};
Double_t sys_integrated_yield2[8]={0.000304975,0.000304975,0.000419242,0.000372123,0.001015,0.00102828,0.00254404,0.00254404};
Double_t parameter0[9];
Double_t parameter1[9];
Double_t error_parameter0[9];
Double_t error_parameter1[9];
Double_t particle_mass[] = {493.677, 493.677, 938.272, 938.272, 139.570, 139.570, 134.9768, 134.9768, 1019.461};//k+, k-, p, pbar, pi+, pi-, pi0, pi0, phi


void binshift()
{   TSystemDirectory dir("data","./"); // assuming all data files are in the current directory
    TList *files = dir.GetListOfFiles();
    if (!files) {
        cout << "No files found in the directory!" << endl;
        return;
    }
    
    //fix bin shift
    
    
    TCanvas* c0[20][20];
    TH1F *spectra_fill[20][20];
    TGraphMultiErrors* spectra_fit[20][20];
    //TLegend* ptleg[20][20]
    TCanvas* c1 = new TCanvas("c1","Pt vs Yield",800,600);
    c1->SetLogy();
    c1->SetLogx();
    gStyle->SetOptStat(0);
    gStyle->SetLegendBorderSize(0);

    TLegend* leg = new TLegend(0.15,0.55,0.3,0.89);
    leg->SetFillStyle(0);
    TGraphMultiErrors* g[20];
    auto mg = new TMultiGraph();
    mg->SetTitle("Integrated Yield 3-4GeV AuAu200 (undo binshift);#frac{dN_{ch}}{d#eta}; int.Yield");
    
    int style_index = 2;
    int color_index = 0;
    int file_index = 0;


    for (int i = 0; i < files->GetSize(); ++i) 
    {
        TSystemFile *file = (TSystemFile*) files->At(i);
        if (!file) continue;

        TString filename = file->GetName();
        //if (!filename.Contains("star")) continue;
        if (!filename.EndsWith(".txt")) continue;
        //if (!filename.Contains("AuAu")) continue;
        //if (!filename.Contains("200")) continue;
        //if (!filename.Contains("p-")) continue;
        //if (!filename.Contains("2003")) continue;

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
        Double_t ptlow[20][100];
        Double_t pthigh[20][100];
        float yield[20][100];
        int bin_num[20];
        int fill_num[20]={0};
        float ratio_binshift[20][100];
        float yield_corrected[20][100];
        Float_t integrated_yield[20]={0};
        Float_t integrated_yield_corrected[20]={0};
        Float_t stat_integrated_yield[20]={0};
        Double_t sys_integrated_yield[20]={0};
        float dn_deta[20][100]={0};
        float errdn_deta[20][100]={0};
        float statp[20][100];
        float statm[20][100];
        Double_t sysp[20][100];
        Double_t sysm[20][100];
        TString fit_int_yield[20] = {"fit_int_yield1", "fit_int_yield2", "fit_int_yield3" "fit_int_yield4" "fit_int_yield5" "fit_int_yield6" "fit_int_yield7", "fit_int_yield8", "fit_int_yield9", "fit_int_yield10", "fit_int_yield11", "fit_int_yield12", "fit_int_yield13", "fit_int_yield14", "fit_int_yield15", "fit_int_yield16", "fit_int_yield17", "fit_int_yield18", "fit_int_yield19", "fit_int_yield20" };


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
                yield_corrected[CurrentCentIndex][CurrentPtIndex] = yield[CurrentCentIndex][CurrentPtIndex];
                dn_deta[CurrentCentIndex][CurrentPtIndex] = Nch[CurrentCentIndex];
                errdn_deta[CurrentCentIndex][CurrentPtIndex] = Ncher[CurrentCentIndex];
                if (pt[CurrentCentIndex][CurrentPtIndex]<=5)
                {
                    fill_num[CurrentCentIndex] +=1;
                    //cout << "fill_num[" <<CurrentCentIndex <<"]= " << fll_num[CurrentCentIndex]<<endl;
                }
                //cout << pt[CurrentCentIndex][CurrentPtIndex] << endl;

                if(pt[CurrentCentIndex][CurrentPtIndex] > 1 && pt[CurrentCentIndex][CurrentPtIndex] < 3)
                {
                    integrated_yield[CurrentCentIndex] += 2*TMath::Pi() * pt[CurrentCentIndex][CurrentPtIndex] * yield[CurrentCentIndex][CurrentPtIndex] * (pthigh[CurrentCentIndex][CurrentPtIndex] - ptlow[CurrentCentIndex][CurrentPtIndex]);
                    stat_integrated_yield[CurrentCentIndex] += pow(2*TMath::Pi() * pt[CurrentCentIndex][CurrentPtIndex] * statp[CurrentCentIndex][CurrentPtIndex] * (pthigh[CurrentCentIndex][CurrentPtIndex] - ptlow[CurrentCentIndex][CurrentPtIndex]),2);
                    sys_integrated_yield[CurrentCentIndex] += pow(2*TMath::Pi() * pt[CurrentCentIndex][CurrentPtIndex] * sysp[CurrentCentIndex][CurrentPtIndex] * (pthigh[CurrentCentIndex][CurrentPtIndex] - ptlow[CurrentCentIndex][CurrentPtIndex]),2);
                //cout<< integrated_yield[CurrentCentIndex] <<endl;
                }

                ++CurrentPtIndex;
            }
        bin_num[CurrentCentIndex] = CurrentPtIndex + 1;
        }

    inputfile.close();
    
    for (int i = 0; i < NumCentIndex; ++i) //get ratio_binshift and yield_corrected
    {   
        int k = file_index;
        cout << centlow[i] << "\t" << centhigh[i] << endl;
        /*c0[k][i] = new TCanvas(Form("%d - %d - %d",k, centlow[i],centhigh[i]), Form("%s - %d - %d",AuAu200only[k], centlow[i],centhigh[i]), 800, 600);
        c0[k][i]->SetLogy();
        c0[k][i]->SetLogx(0);
        gStyle->SetOptStat(0);
        gStyle->SetLegendBorderSize(0);*/
        
        spectra_fit[k][i] = new TGraphMultiErrors(bin_num[i]-1, pt[i], yield[i], 0,0, statp[i], statp[i]);
        spectra_fit[k][i]->AddYError(bin_num[i]-1, sysp[i],sysp[i]);
        int N = bin_num[i];
        int M = fill_num[i]+1;
        Double_t xbin[N];
        Double_t xbin_fill[M];
        for(int j=0;j<N-1;++j)
        {
            xbin[j]=ptlow[i][j];
        }
        xbin[N-1] = pthigh[i][N-2];
        for(int j=0;j<M-1;++j)
        {
            xbin_fill[j]=ptlow[i][j];
        }
        xbin_fill[M-1] = pthigh[i][M-2];
         ///for(int j=0;j<N;++j)
        //{   
           // cout<<N<<"   "<<M<<"   "<<xbin[j]<<"  "<< xbin_fill[j]<<"  "<< pthigh[i][M-2]<<endl;
            
        //}
        TF1* fHagedorn = new TF1("fHagedorn","[0]/pow((exp(-[1]*x -[2]*x*x) + x/[3]),[4])", xbin_fill[0], xbin_fill[M-1]);
    fHagedorn->SetParameters(5.26449e+01, 7.19390e-01, 5.42216e-02, 1.02260e+00, 7.88555e+00);
        for(int j=0;j<10;++j)
        {
            spectra_fit[k][i]->Fit(fHagedorn,"Q");
        }
        //fHagedorn->Draw();
        spectra_fill[k][i] = new TH1F("fHagedorn_fill",filename,M-1,xbin_fill);
        spectra_fill[k][i]->FillRandom("fHagedorn",10000000);
        for (int j = 1; j <= spectra_fill[k][i]->GetNbinsX(); j++) 
        {
            double content = spectra_fill[k][i]->GetBinContent(j);
            double binWidth = spectra_fill[k][i]->GetBinWidth(j);
            double dividedContent = content / binWidth;
            spectra_fill[k][i]->SetBinContent(j, dividedContent);
        }
        double integral_fHagedorn = fHagedorn->Integral(xbin_fill[0],xbin_fill[M-1]);
        spectra_fill[k][i]->Scale(integral_fHagedorn/10000000);

        for (int j = 1; j <= spectra_fill[k][i]->GetNbinsX(); j++) 
        {
            ratio_binshift[i][j-1] = spectra_fill[k][i]->GetBinContent(j)/spectra_fit[k][i]->Eval(pt[i][j-1]);
            yield_corrected[i][j-1] = yield[i][j-1] * ratio_binshift[i][j-1];
            //cout << ratio_binshift[i][j-1]<<endl;
        }
        //spectra_fill[k][i]->Fit("fHagedorn");
        //delete fHagedorn;
        spectra_fit[k][i]->SetTitle(AuAu200only[k]);

        //spectra_fit[k][i]->SetTitle(Form("%s cent_%d-%d", hdvi, i. i+1));
        //spectra_fit[k][i]->Draw("AP");
        //spectra_fill[k][i]->Draw("same");
    }

    for (int i = 0; i < NumCentIndex; ++i)  //get integrated_yield_corrected
    {   
        int N = bin_num[i]-1;
        for(int j=0; j<N;j++)
        {
        
        if(pt[i][j] > 1 && pt[i][j] < 3)
            {   //cout<< pt[i][j]<<"  "<< yield[i][j]<<"  "<< ratio_binshift[i][j]<<"  "<< yield_corrected[i][j]<<endl;
                integrated_yield_corrected[i] += 2*TMath::Pi() * pt[i][j] * yield_corrected[i][j] * (pthigh[i][j] - ptlow[i][j]);
            }
        }
    }
    for (int i = 0; i < NumCentIndex; ++i) //get stat and sys error; normalize data by pp data
    {
        stat_integrated_yield[i] = sqrt(stat_integrated_yield[i]);
        sys_integrated_yield[i] = sqrt(sys_integrated_yield[i]);
        /*int k = file_index;

        //cout << k << "\t" << Nch[i] << "\t" << integrated_yield[i]<< "\t"<<  stat_integrated_yield[i]<< "\t"<< stat_integrated_yield2[k]<< endl;

        Nch[i]=Nch[i]/2.38;
        Ncher[i]=Nch[i]*sqrt(pow(0.09/2.38,2)+pow(Ncher[i]/(2.38*Nch[i]),2));
        integrated_yield_corrected[i]=integrated_yield_corrected[i]/integrated_yield2_corrected[k];
        //cout << integrated_yield[i] << endl;
        stat_integrated_yield[i]=integrated_yield_corrected[i]*sqrt(pow(stat_integrated_yield[i]/(integrated_yield_corrected[i]*integrated_yield2_corrected[k]),2)+pow(stat_integrated_yield2[k]/integrated_yield2_corrected[k],2));
        sys_integrated_yield[i]=integrated_yield_corrected[i]*sqrt(pow(sys_integrated_yield[i]/(integrated_yield_corrected[i]*integrated_yield2_corrected[k]),2)+pow(sys_integrated_yield2[k]/integrated_yield2_corrected[k],2));

       // cout << k << "\t" << Nch[i] << "\t" << integrated_yield[i]<< "\t"<<  stat_integrated_yield[i] << "\t"<< stat_integrated_yield2[k] << "\t"<<  sys_integrated_yield[i]<<endl;
    */}
int k = file_index;

    for (int i = 0; i < NumCentIndex; ++i) 
    {   //stat_integrated_yield[i] = sqrt(stat_integrated_yield[i]);
        //sys_integrated_yield[i] = sqrt(sys_integrated_yield[i]);
        
        cout << k << "\t" << integrated_yield[i] << "\t" << integrated_yield_corrected[i]<< "\t"<<  stat_integrated_yield[i]<< "\t"<< stat_integrated_yield2[k]<< "\t"<<  sys_integrated_yield[i]<< "\t"<< sys_integrated_yield2[k]<<endl;

    }
        g[k] = new TGraphMultiErrors(NumCentIndex,Nch,integrated_yield_corrected,Ncher,Ncher,stat_integrated_yield,stat_integrated_yield);
        //g[k][i]->SetTitle("pi0 at 200GeV"); // set the title of the graph
        
        g[k]->AddYError(NumCentIndex,sys_integrated_yield, sys_integrated_yield);
        g[k]->SetMinimum(0.00000000001);
        g[k]->SetMaximum(100.);
        g[k]->GetAttLine(0)->SetLineColorAlpha(kRed, 1);
        //g[k][i]->GetAttLine(1)->SetLineColor(kBlue);
        g[k]->GetAttFill(1)->SetFillStyle(0);
        g[k]->SetMarkerStyle(20+color_index); 
        g[k]->SetMarkerSize(.7); 
        g[k]->SetMarkerColorAlpha(color[color_index],1);
        g[k]->SetLineColor(color[color_index]); 
        g[k]->SetLineWidth(1); 
        g[k]->SetFillStyle(0);

        TF1* fit_int_yield_index = new TF1(fit_int_yield[k],"pow(x,[0])*[1]", 5., 1000.);
        Double_t params[] = {0.9991, 0.0018};
        fit_int_yield_index->SetParameters(params);
       //fit_int_yield_index->SetParameter(0.9991, 0.0018);
       //fit_int_yield_index->SetParLimits(0,0.,1);
       //fit_int_yield_index->SetParLimits(1,0.5,2.5);
        for(int j=0;j<5;++j)
        {
            fit_int_yield_index->SetParameters(fit_int_yield_index->GetParameter(0), fit_int_yield_index->GetParameter(1));
            g[k]->Fit(fit_int_yield_index, "R");
        }
        parameter0[k] = fit_int_yield_index->GetParameter(0);
        parameter1[k] = fit_int_yield_index->GetParameter(1);
        error_parameter0[k] = fit_int_yield_index->GetParError(0);
        error_parameter1[k] = fit_int_yield_index->GetParError(1);
        g[k]->GetFunction(fit_int_yield[k])->SetLineColor(color[color_index]);
        g[k]->GetFunction(fit_int_yield[k])->SetLineWidth(1); 
        g[k]->GetFunction(fit_int_yield[k])->SetLineStyle(2); 
        //fit_int_yield_index->Draw();
        //g[k][i]->GetXaxis()->SetTitle("frac{dN_{ch}}{d#eta}"); 
        //g[k][i]->GetYaxis()->SetTitle("int.yield");
        //leg->AddEntry(g[k][i],Form("%d - %d",centlow[i],centhigh[i]),"lep"); // add the graph to the legend
        //if(i==0) gr->Draw("APL"); // draw the first graph with axes
        //else gr->Draw("PLSAME");
        {leg->AddEntry(g[k], AuAu200only[k], "p");}
        //g[k][i]->Draw("APE ; Z ; 5 s = 0.5");
        mg->Add(g[k], "APE ; Z ; 5 s = 0.5");
        mg->Draw("APE");
        fit_int_yield_index->Draw("same");
    
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
for(int i=0;i<9;i++){
    cout<< parameter0[i]<<"    "<<error_parameter0[i]<<"    "<<parameter1[i]<<"    "<<error_parameter1[i]<<endl;
}
Double_t ex[] = {0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5};
TCanvas* c2 = new TCanvas("c2","mass vs parameter0",800,600);;
auto ratio_mass_parameters0 = new TGraphErrors(9, particle_mass, parameter0, 0, error_parameter0);
ratio_mass_parameters0->SetTitle("mass vs parameter0");
ratio_mass_parameters0->SetMarkerStyle(25);
ratio_mass_parameters0->SetMarkerSize(.7); 
ratio_mass_parameters0->SetMarkerColor(kRed);
ratio_mass_parameters0->SetLineColor(kBlack); // Set the line color to 0 (disable line drawing)
ratio_mass_parameters0->GetXaxis()->SetTitle("Mass(MeV)"); 
ratio_mass_parameters0->GetYaxis()->SetTitle("parameter0");
ratio_mass_parameters0->Draw("APE1");
c2->Draw();
TCanvas* c3 = new TCanvas("c3","mass vs parameter1",800,600);;
auto ratio_mass_parameters1 = new TGraphErrors(9, particle_mass, parameter1, 0, error_parameter1);
ratio_mass_parameters1->SetTitle("mass vs parameter1");
ratio_mass_parameters1->SetMarkerStyle(25);
ratio_mass_parameters1->SetMarkerSize(.7); 
ratio_mass_parameters1->SetMarkerColor(kRed);
ratio_mass_parameters1->SetLineColor(kBlack); // Set the line color to 0 (disable line drawing)
ratio_mass_parameters1->GetXaxis()->SetTitle("Mass(MeV)"); 
ratio_mass_parameters1->GetYaxis()->SetTitle("parameter0");
ratio_mass_parameters1->Draw("APE1");
c3->Draw();
}