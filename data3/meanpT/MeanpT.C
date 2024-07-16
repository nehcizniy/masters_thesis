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
TString phi[] = {"Phenix-3HeAu-200","Phenix-CuAu-200","Phenix-pAl-200","Phenix-pAu-200","phenix-UU-193"};
TString pbar[] = {"Phenix-AuAu-130","Phenix-AuAu-200","Phenix-dAu-200","Phenix-pp-200","star-AUAu-62.4","star-CuCu-200","star-UU-193"};
TString p[] = {"Phenix-AuAu-130","Phenix-AuAu-200","Phenix-dAu-200","Phenix-pp-200","star-AuAu-62.4","star-CuCu-200","star-UU-193"};
TString kp[] = {"Phenix-AuAu-130","Phenix-AuAu-200","Phenix-dAu-200","Phenix-pp-200","star-UU-193"};
TString km[] = {"Phenix-AuAu-130","Phenix-AuAu-200","Phenix-dAu-200","Phenix-pp-200","star-UU-193"};
TString pip[] = {"Phenix-AuAu-130","Phenix-AuAu-200","Phenix-dAu-200","Phenix-pp-200","star-AUAu-62.4","star-CuCu-200","star-UU-193"};
TString pim[] = {"Phenix-AuAu-130","Phenix-AuAu-200","Phenix-dAu-200","Phenix-pp-200","star-AUAu-62.4","star-CuCu-200","star-UU-193"};
Double_t parameter0[100][100];
Double_t parameter1[100][100];
Double_t parameter2[100][100];
Double_t parameter3[100][100];
TString filename_array[100];
TString parameter_index_collab[] = {"phenix","star"};
TString parameter_index_system[] = {"AuAu","CuAu","dAu","3HeAu","UU","pAl","pAu","CuCu"};
TString parameter_index_particle[] = {"k+","k-","-p-","pbar","pi+","pi-","pi0","phi"};
Double_t parameter_index_mass[] = {493.677, 493.677, 938.272, 938.272, 139.570, 139.570, 134.9768, 1019.461};
Double_t error_parameter0[100][100];
Double_t error_parameter1[100][100];
Double_t error_parameter2[100][100];
Double_t error_parameter3[100][100];
const int color[] = {kRed, kBlue, kMagenta, kCyan, kGreen+2, kYellow+4, kBlack, kGray};
Double_t particle_mass[] = {493.677, 493.677, 938.272, 938.272, 139.570, 139.570, 134.9768, 134.9768, 1019.461};//k+, k-, p, pbar, pi+, pi-, pi0, pi0, phi
Double_t kaon_mass = 493.677;
Double_t proton_mass = 938.272;
Double_t pion_mass = 139.570;
Double_t pi0_mass = 134.9768;
Double_t phi_mass = 1019.461;
Double_t particle_mass2[] = {493.677, 493.677, 493.677, 493.677, 938.272, 938.272, 938.272, 938.272, 1019.461, 1019.461, 1019.461, 1019.461, 1019.461, 139.570, 139.570, 139.570, 139.570, 134.9768, 134.9768, 134.9768, 134.9768, 134.9768, 134.9768, 134.9768, 493.677, 493.677, 938.272, 938.272, 1019.461, 139.570, 139.570};
Double_t particle_mass3[] = {493.677, 493.677, 938.272, 938.272, 139.570, 139.570};
void MeanpT()
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
    TGraphErrors* p2[100][100];
    TGraphErrors* p3[100][100];
    //TCanvas* c0[100][100];
    TH1F *spectra_fill[100][100];
    TGraphMultiErrors* spectra_fit[100][100];
    TCanvas* c1 = new TCanvas("c1","Pt vs Yield",800,600);
    c1->SetLogy(0);
    c1->SetLogx();
    gStyle->SetOptStat(0);
    gStyle->SetLegendBorderSize(0);

    TLegend* leg = new TLegend(0.15,0.55,0.3,0.89);
    leg->SetFillStyle(0);
    TGraphMultiErrors* g[100];
    TMultiGraph* ratio_mass_parameters0 = new TMultiGraph();
    TMultiGraph* ratio_mass_parameters1 = new TMultiGraph();
    TMultiGraph* ratio_mass_parameters2 = new TMultiGraph();
    TMultiGraph* ratio_mass_parameters3 = new TMultiGraph();
    auto mg = new TMultiGraph();
    mg->SetTitle(Form("%f - %f",int_low,int_high));
    mg->GetXaxis()->SetTitle("#frac{dN_{ch}}{d#eta}");
    mg->GetYaxis()->SetTitle("<pT>");

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
        float ratio_binshift[100][100];
        float yield_corrected[100][100];
        int bin_num[100];
        int fill_num[100]={0};
        float dn_deta[100][100]={0};
        float errdn_deta[100][100]={0};
        float statp[100][100];
        float statm[100][100];
        Double_t sysp[100][100];
        Double_t sysm[100][100];
        float mean_pt[100][100];
        float mean_pt_error[100][100];
        float std_pt[100][100];
        float std_pt_error[100][100];
        


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

        for (int i = 0; i < NumCentIndex; ++i) //get ratio_binshift and yield_corrected
    {   
        int k = file_index;
        cout << centlow[i] << "\t" << centhigh[i] << endl;
        // c0[k][i] = new TCanvas(Form("%d - %d - %d",k, centlow[i],centhigh[i]), Form("%d - %d", centlow[i],centhigh[i]), 800, 600);
        // c0[k][i]->SetLogy();
        // c0[k][i]->SetLogx(0);
        // gStyle->SetOptStat(0);
        // gStyle->SetLegendBorderSize(0);
        
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

        double pt_low = 0;
        double pt_high = 0;

        for(int n = 0; n<8; ++n){
        if (filename.Contains(parameter_index_particle[n])){
        pt_low = sqrt(int_low*int_low-0.000001*parameter_index_mass[n]*parameter_index_mass[n]);
        pt_high = sqrt(int_high*int_high-0.000001*parameter_index_mass[n]*parameter_index_mass[n]);
        }
        }


        spectra_fill[k][i] = new TH1F("fHagedorn_fill",filename,10000,pt_low,pt_high);
        spectra_fill[k][i]->FillRandom("fHagedorn",1000000);
        for (int j = 1; j <= spectra_fill[k][i]->GetNbinsX(); j++) 
        {
            double content = spectra_fill[k][i]->GetBinContent(j);
            double binWidth = spectra_fill[k][i]->GetBinWidth(j);
            double dividedContent = content / binWidth;
            spectra_fill[k][i]->SetBinContent(j, dividedContent);
        }
        double integral_fHagedorn = fHagedorn->Integral(pt_low,pt_high);
        spectra_fill[k][i]->Scale(integral_fHagedorn/10000000);

        for (int j = 1; j <= spectra_fill[k][i]->GetNbinsX(); j++) 
        {
            ratio_binshift[i][j-1] = spectra_fill[k][i]->GetBinContent(j)/spectra_fit[k][i]->Eval(pt[i][j-1]);
            yield_corrected[i][j-1] = yield[i][j-1] * ratio_binshift[i][j-1];
            //cout << ratio_binshift[i][j-1]<<endl;
        }
        

        Double_t sumPT[NumCentIndex];
        Double_t sumWeights[NumCentIndex];
        Double_t sumDeviationSquared[NumCentIndex];

    for (Int_t bin = 1; bin <= spectra_fill[k][i]->GetNbinsX(); ++bin) {
        Double_t binCenter = spectra_fill[k][i]->GetBinCenter(bin);
        Double_t binContent = spectra_fill[k][i]->GetBinContent(bin);
        Double_t binError = spectra_fill[k][i]->GetBinError(bin);

        sumPT[i] += binCenter * binContent;
        sumWeights[i] += binContent;
    }

    mean_pt[k][i] = sumPT[i] / sumWeights[i];
    

    for (Int_t bin = 1; bin <= spectra_fill[k][i]->GetNbinsX(); ++bin) {
        Double_t binCenter = spectra_fill[k][i]->GetBinCenter(bin);
        Double_t binContent = spectra_fill[k][i]->GetBinContent(bin);

        Double_t deviation = binCenter - mean_pt[k][i];
        sumDeviationSquared[i] += binContent * deviation * deviation;
    }

    mean_pt_error[k][i] = TMath::Sqrt(sumDeviationSquared[i] / (sumWeights[i] * (sumWeights[i] - 1)));
    std_pt[k][i] = TMath::Sqrt(sumDeviationSquared[i] / sumWeights[i]);


        // mean_pt[k][i] = spectra_fill[k][i]->GetMean(2);
        // mean_pt_error[k][i] = spectra_fill[k][i]->GetMeanError(2);
        // std_pt[k][i] = spectra_fill[k][i]->GetStdDev(2);
        // std_pt_error[k][i] = spectra_fill[k][i]->GetStdDevError(2);
        cout <<
        mean_pt[k][i] <<"   "<<
        mean_pt_error[k][i]<<"   "<<
        std_pt[k][i]<<"   "<<
        std_pt_error[k][i]<<endl;
        //spectra_fill[k][i]->Fit("fHagedorn");
        //delete fHagedorn;
        // spectra_fit[k][i]->SetTitle(filename);

        // spectra_fit[k][i]->SetTitle(Form("cent_%d-%d", i, i+1));
        // spectra_fit[k][i]->Draw("AP");
        // spectra_fill[k][i]->Draw("same");
    }

    //cout << k << "\t" << integrated_yield[i] << "\t" << integrated_yield_corrected[i]<< "\t"<<  stat_integrated_yield[i]<< "\t"<<  sys_integrated_yield[i]<<endl;
        g[k] = new TGraphMultiErrors(NumCentIndex,Nch,mean_pt[k],0,0,mean_pt_error[k], mean_pt_error[k]);
        //if(filename.Contains("star")){g[k][i] = new TGraphMultiErrors(bin_num[i],pt[i],yield[i],0,0,statp[i], statp[i]);}
        //g[k][i]->SetTitle("pi0 at 200GeV"); // set the title of the graph
        
        //g[k]->AddYError(NumCentIndex,sys_integrated_yield, sys_integrated_yield);
        g[k]->SetMinimum(0.00000000001);
        g[k]->SetMaximum(100.);
        g[k]->GetAttLine(0)->SetLineColorAlpha(kRed, 1);
        //g[k][i]->GetAttLine(1)->SetLineColor(kBlue);
        //g[k]->GetAttFill(1)->SetFillStyle(0);
        g[k]->SetMarkerStyle(20); 
        g[k]->SetMarkerSize(.7); 
        g[k]->SetMarkerColorAlpha(color[color_index],1);//color[color_index]
        //g[k][i]->SetLineColor(color[color_index]); 
        g[k]->SetLineWidth(1); 
        g[k]->SetFillStyle(0);

        
        //fit_int_yield_index->Draw();
        //g[k][i]->GetXaxis()->SetTitle("frac{dN_{ch}}{d#eta}"); 
        //g[k][i]->GetYaxis()->SetTitle("int.yield");
        //leg->AddEntry(g[k][i],Form("%d - %d",centlow[i],centhigh[i]),"lep"); // add the graph to the legend
        //if(i==0) gr->Draw("APL"); // draw the first graph with axes
        //else gr->Draw("PLSAME");
        leg->AddEntry(g[k], filename, "p");
        //g[k][i]->Draw("APE ; Z ; 5 s = 0.5");
        mg->Add(g[k], "APE ; Z ; 5 s = 0.5");


        mg->Draw("APE");
        //fit_int_yield_index->Draw("same");
    
    leg->Draw("p");

//cout<< "ggggggg"<<endl;
    style_index++;
    color_index++;
    file_index++;

}

gPad->Modified();
   mg->GetXaxis()->SetLimits(1.,1000.);
   //mg->GetYaxis()->SetRangeUser(0.001,200);
   mg->SetMinimum(0.1);
   mg->SetMaximum(10.);
gPad->Modified();



    
}