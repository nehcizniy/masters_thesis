#include <iostream>
#include <fstream>
#include <string>
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
//#include "fit_parameters_p.h"
using namespace std;

//add legend names
TString pi0[] = {"Phenix-3HeAu-200","Phenix-AuAu-200","Phenix-CuAu-200","Phenix-dAu-200","Phenix-pAl-200","Phenix-pAu-200","Phenix-pp-200"};
TString phi[] = {"Phenix-3HeAu-200","Phenix-CuAu-200","Phenix-pAl-200","Phenix-pAu-200","phenix-UU-193"};
TString pbar[] = {"Phenix-AuAu-130","Phenix-AuAu-200","Phenix-dAu-200","Phenix-pp-200","star-AUAu-62.4","star-CuCu-200","star-UU-193"};
TString proton[] = {"Phenix-AuAu-130","Phenix-AuAu-200","Phenix-dAu-200","Phenix-pp-200","star-AuAu-62.4","star-CuCu-200","star-UU-193"};
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
TString parameter_index_particle[] = {"k+","k-","-p-","pbar","pi+","pi-","pi0","phi","kaon","pion","proton"};
Double_t parameter_index_mass[] = {493.677, 493.677, 938.272, 938.272, 139.570, 139.570, 134.9768, 1019.461, 493.677, 139.570, 938.272};
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
void p()
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
double mt_int_low;
double mt_int_high;
string raw_text;
cout << "integration_range: " << endl;
cin >> int_low;
cin >> int_high;
cin >> raw_text;
const char *true_text = raw_text.c_str();

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
    c1->SetLogy();
    c1->SetLogx();
    gStyle->SetOptStat(0);
    gStyle->SetLegendBorderSize(0);

    TLegend* leg = new TLegend(0.12,0.70,0.70,0.88);
    leg->SetFillStyle(0);
    TGraphMultiErrors* g_point[100][100];
    TGraphMultiErrors* g_flat[100][100];
    TGraphMultiErrors* g_steeper[100][100];
    TMultiGraph* ratio_mass_parameters0 = new TMultiGraph();
    TMultiGraph* ratio_mass_parameters1 = new TMultiGraph();
    TMultiGraph* ratio_mass_parameters2 = new TMultiGraph();
    TMultiGraph* ratio_mass_parameters3 = new TMultiGraph();
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
        float yield_steeper[100][100];
        float yield_flat[100][100];
        Float_t width_error_bar[100][100];
        int bin_num[100];
        int fill_num[100]={0};
        float dn_deta[100][100]={0};
        float errdn_deta[100][100]={0};
        float statp[100][100];
        float statm[100][100];
        float Rstat[100][100];
        float stat_flat[100][100];
        float stat_steeper[100][100];
        Double_t sysp[100][100];
        Double_t sysm[100][100];
        Double_t Rsys[100][100];
        Double_t sys_flat[100][100];
        Double_t sys_steeper[100][100];


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
                Rstat[CurrentCentIndex][CurrentPtIndex] = statp[CurrentCentIndex][CurrentPtIndex] / yield[CurrentCentIndex][CurrentPtIndex];
                Rsys[CurrentCentIndex][CurrentPtIndex] = sysp[CurrentCentIndex][CurrentPtIndex] / yield[CurrentCentIndex][CurrentPtIndex];
                yield_steeper[CurrentCentIndex][CurrentPtIndex] = yield[CurrentCentIndex][CurrentPtIndex] + 0.08 * yield[CurrentCentIndex][CurrentPtIndex] * (2*pt[CurrentCentIndex][CurrentPtIndex]/(int_low-int_high) + (int_high + int_low)/(int_high - int_low));
                yield_flat[CurrentCentIndex][CurrentPtIndex] = yield[CurrentCentIndex][CurrentPtIndex] + 0.08 * yield[CurrentCentIndex][CurrentPtIndex] * (2*pt[CurrentCentIndex][CurrentPtIndex]/(int_high-int_low) + (int_high + int_low)/(int_low - int_high));
                stat_flat[CurrentCentIndex][CurrentPtIndex] = yield_flat[CurrentCentIndex][CurrentPtIndex]*Rstat[CurrentCentIndex][CurrentPtIndex];
                stat_steeper[CurrentCentIndex][CurrentPtIndex] = yield_steeper[CurrentCentIndex][CurrentPtIndex]*Rsys[CurrentCentIndex][CurrentPtIndex];
                //cout<< yield_flat[CurrentCentIndex][CurrentPtIndex]<<"\t"<<yield[CurrentCentIndex][CurrentPtIndex]<<"\t"<<yield_steeper[CurrentCentIndex][CurrentPtIndex]<<endl;
                for(int i=0;i<11;++i)
        {
            if(filename.Contains(parameter_index_particle[i]))
            {
                mt[CurrentCentIndex][CurrentPtIndex] = sqrt(pt[CurrentCentIndex][CurrentPtIndex]*pt[CurrentCentIndex][CurrentPtIndex]+0.000001*parameter_index_mass[i]*parameter_index_mass[i]) - 0.001*parameter_index_mass[i];
                mt_int_low = sqrt(int_low*int_low + 0.000001*parameter_index_mass[i]*parameter_index_mass[i]) - 0.001*parameter_index_mass[i];
                mt_int_high = sqrt(int_high*int_high + 0.000001*parameter_index_mass[i]*parameter_index_mass[i]) - 0.001*parameter_index_mass[i];
                //cout<<pt[CurrentCentIndex][CurrentPtIndex]<<"    "<<mt[CurrentCentIndex][CurrentPtIndex]<<"    "<<yield[CurrentCentIndex][CurrentPtIndex]<<endl;
            }
        }
                width_error_bar[CurrentCentIndex][CurrentPtIndex] = 0.01 * mt[CurrentCentIndex][CurrentPtIndex];
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
    cout<<NumCentIndex<<endl;
    // Float_t width_error_bar[50];
    // for (int i = 0; i < 50; ++i) 
    // {   
    //     width_error_bar[i] = 0.01;
    // }

    for (int i = 0; i < NumCentIndex; ++i) 
    {
    //cout << k << "\t" << integrated_yield[i] << "\t" << integrated_yield_corrected[i]<< "\t"<<  stat_integrated_yield[i]<< "\t"<<  sys_integrated_yield[i]<<endl;
        g_point[k][i] = new TGraphMultiErrors(bin_num[i],mt[i],yield[i],width_error_bar[i],width_error_bar[i],statp[i], statp[i]);
        g_flat[k][i] = new TGraphMultiErrors(bin_num[i],mt[i],yield_flat[i],width_error_bar[i],width_error_bar[i],statp[i], statp[i]);
        g_steeper[k][i] = new TGraphMultiErrors(bin_num[i],mt[i],yield_steeper[i],width_error_bar[i],width_error_bar[i],statp[i], statp[i]);
        //g[k][i]->SetTitle("pi0 at 200GeV"); // set the title of the graph
        
        //g[k][i]->AddYError(bin_num[i],sysp[i], sysp[i]);
        //g[k][i]->SetMinimum(0.00000000001);
        //g[k][i]->SetMaximum(100.);
        //g[k]->GetAttLine(0)->SetLineColorAlpha(kRed, 1);
        //g[k][i]->GetAttLine(1)->SetLineColor(kBlue);
        //g[k]->GetAttFill(1)->SetFillStyle(0);
        //g[k]->SetMarkerStyle(20+color_index); 
        //g[k]->SetMarkerSize(.7); 
        //g[k][i]->SetMarkerColorAlpha(color[color_index],1);//color[color_index]
        //g[k][i]->SetLineColor(color[color_index]); 
        //g[k]->SetLineWidth(1); 
        //g[k][i]->SetFillStyle(0);

         TF1* fit_int_yield_index = new TF1("fit_int_yieldx","exp(-x/[0])*[1]", mt_int_low, mt_int_high);
        Double_t params_point[] = {0.4,0.01};
        Double_t params_flat[] = {0.5,0.02};
        Double_t params_steeper[] = {0.2,0.05};
        fit_int_yield_index->SetParameters(params_point);
    //    fit_int_yield_index->SetParameter(0.9991, 0.0018);
    //    fit_int_yield_index->SetParLimits(0,0.,1);
    //    fit_int_yield_index->SetParLimits(1,0.5,2.5);
        for(int j=0;j<10;++j)
        {
            fit_int_yield_index->SetParameters(fit_int_yield_index->GetParameter(0),fit_int_yield_index->GetParameter(1));
            g_point[k][i]->Fit(fit_int_yield_index, "QR");
        }
        parameter0[k][i] = fit_int_yield_index->GetParameter(0);
        parameter1[k][i] = fit_int_yield_index->GetParameter(1);
        double y0 = parameter1[k][i];
        fit_int_yield_index->SetParameters(params_flat);
        for(int j=0;j<10;++j)
        {
            fit_int_yield_index->SetParameters(fit_int_yield_index->GetParameter(0),fit_int_yield_index->GetParameter(1));
            g_flat[k][i]->Fit(fit_int_yield_index, "QR");
        }
        error_parameter0[k][i] = fit_int_yield_index->GetParameter(0);
        error_parameter1[k][i] = fit_int_yield_index->GetParameter(1);
        double x0 = error_parameter0[k][i];
        
        fit_int_yield_index->SetParameters(params_steeper);
        for(int j=0;j<10;++j)
        {
            fit_int_yield_index->SetParameters(fit_int_yield_index->GetParameter(0),fit_int_yield_index->GetParameter(1));
            g_steeper[k][i]->Fit(fit_int_yield_index, "QR");
        }
        error_parameter0[k][i] = -0.5*(fit_int_yield_index->GetParameter(0) - error_parameter0[k][i]);
        error_parameter1[k][i] = -0.5*(fit_int_yield_index->GetParameter(1) - error_parameter1[k][i]);
        cout<<parameter0[k][i]<<"\t"<<x0<<"\t"<< fit_int_yield_index->GetParameter(0) << "\t" <<error_parameter0[k][i]<< "\t"<<y0<< endl;
        // g[k][i]->GetFunction("fit_int_yieldx")->SetLineColor(kBlack);
        // g[k][i]->GetFunction("fit_int_yieldx")->SetLineWidth(1); 
        // g[k][i]->GetFunction("fit_int_yieldx")->SetLineStyle(2); 

        p0[k][i] = new TGraphErrors();
        p1[k][i] = new TGraphErrors();
        p2[k][i] = new TGraphErrors();
        p3[k][i] = new TGraphErrors();
        p2[k][i]->SetPoint(0,Nch[i],parameter0[k][i]);
        p3[k][i]->SetPoint(0,Nch[i],parameter1[k][i]);
        p2[k][i]->SetPointError(0,0,error_parameter0[k][i]);
        p3[k][i]->SetPointError(0,0,error_parameter1[k][i]);

        for(int j=0;j<11;++j)
        {
            if(filename_array[k].Contains(parameter_index_particle[j]))
            {   
                p0[k][i]->SetPoint(0,parameter_index_mass[j],parameter0[k][i]);
                p1[k][i]->SetPoint(0,parameter_index_mass[j],parameter1[k][i]);
                p0[k][i]->SetPointError(0,0,error_parameter0[k][i]);
                p1[k][i]->SetPointError(0,0,error_parameter1[k][i]);
                //p0[k][i]->SetMarkerColor(color[j]);
                //p1[k][i]->SetMarkerColor(color[j]);
                //p2[k][i]->SetMarkerColor(color[j]);
                p3[k][i]->SetMarkerColor(color[j]);
                g_point[k][i]->SetMarkerColor(color[j]);
            }
        }
        for(int j=0;j<2;++j)
        {
            if(filename_array[k].Contains(parameter_index_collab[j]))
            {
                //p0[k][i]->SetMarkerSize(1.*(1+0.5*j));
                //p1[k][i]->SetMarkerSize(1.*(1+0.5*j));
                //p2[k][i]->SetMarkerSize(1.*(1+0.5*j));
                p3[k][i]->SetMarkerSize(1.*(1+0.5*j));
                g_point[k][i]->SetMarkerSize(1.*(1+0.5*j));
            }
        }
        for(int j=0;j<8;++j)
        {
            if(filename_array[k].Contains(parameter_index_system[j]))
            {
                //p0[k][i]->SetMarkerStyle(20+j);
                //p1[k][i]->SetMarkerStyle(20+j);
                //p2[k][i]->SetMarkerStyle(20+j);
                p3[k][i]->SetMarkerStyle(20+j);
                g_point[k][i]->SetMarkerStyle(20+j);
            }
        }

        p0[k][i]->SetMarkerStyle(21+color_index); 
        //g[k]->SetMarkerSize(.7); 
        p0[k][i]->SetMarkerColorAlpha(20+color_index,1);//color[color_index]
        p0[k][i]->SetLineColor(20+color_index); 

        p2[k][i]->SetMarkerStyle(21+color_index); 
        //g[k]->SetMarkerSize(.7); 
        p2[k][i]->SetMarkerColorAlpha(20+color_index,1);//color[color_index]
        p2[k][i]->SetLineColor(20+color_index); 

        //fit_int_yield_index->Draw();
        //g[k][i]->GetXaxis()->SetTitle("frac{dN_{ch}}{d#eta}"); 
        //g[k][i]->GetYaxis()->SetTitle("int.yield");
        //leg->AddEntry(g[k][i],Form("%d - %d",centlow[i],centhigh[i]),"lep"); // add the graph to the legend
        //if(i==0) gr->Draw("APL"); // draw the first graph with axes
        //else gr->Draw("PLSAME");
        //leg->AddEntry(g[k][i], filename, "p");
        //g[k][i]->Draw("APE ; Z ; 5 s = 0.5");
        mg->Add(g_point[k][i], "APE ; Z ; 5 s = 0.5");
        mg->Add(g_flat[k][i], "APE ; Z ; 5 s = 0.5");
        mg->Add(g_steeper[k][i], "APE ; Z ; 5 s = 0.5");
        ratio_mass_parameters0->Add(p0[k][i]);
        ratio_mass_parameters1->Add(p1[k][i]);
        ratio_mass_parameters2->Add(p2[k][i]);
        ratio_mass_parameters3->Add(p3[k][i]);

        mg->Draw("APE");
        //fit_int_yield_index->Draw("same");
    }
    //leg->Draw("p");

//cout<< "ggggggg"<<endl;
    style_index++;
    color_index++;
    file_index++;

}

leg->SetNColumns(3);
// Add entries for particle labels in the first row
leg->AddEntry(new TNamed(), " ","");
leg->AddEntry(new TNamed(), "#pi+","");
leg->AddEntry(new TNamed(), "#pi-","");
// Add entries for AuAu
leg->AddEntry(new TNamed(), "Au+Au 2013","");
leg->AddEntry(p2[6][0], " ", "p");
leg->AddEntry(p2[1][0], " ", "p");

leg->AddEntry(new TNamed(), "Au+Au 2004","");
leg->AddEntry(p2[5][0], " ", "p");
leg->AddEntry(p2[0][0], " ", "p");

leg->AddEntry(new TNamed(), "Cu+Au","");
leg->AddEntry(p2[11][0], "#pi++#pi-", "p");
leg->AddEntry((TObject*)0, " ", "");

leg->AddEntry(new TNamed(), "3He+Au","");
leg->AddEntry(p2[10][0], "#pi++#pi-", "p");
leg->AddEntry((TObject*)0, " ", "");

// Add entries for dAu
leg->AddEntry(new TNamed(), "d+Au","");
leg->AddEntry(p2[7][0], " ", "p");
leg->AddEntry(p2[2][0], " ", "p");

leg->AddEntry(new TNamed(), "p+Au","");
leg->AddEntry(p2[8][0], " ", "p");
leg->AddEntry(p2[3][0], " ", "p");

leg->AddEntry(new TNamed(), "p+Al","");
leg->AddEntry(p2[12][0], "#pi++#pi-", "p");
leg->AddEntry((TObject*)0, " ", "");

// Add entries for pp
leg->AddEntry(new TNamed(), "p+p","");
leg->AddEntry(p2[9][0], " ", "p");
leg->AddEntry(p2[4][0], " ", "p");
leg->SetTextSize(0.025);


   mg->GetXaxis()->SetLimits(.1,20.);
   //mg->GetYaxis()->SetRangeUser(0.001,200);
   mg->SetMinimum(0.0001);
   mg->SetMaximum(1000.);
gPad->Modified();
// for(int i=0;i<file_index;i++){
//     cout<< i << "    "<< filename_array[i]<<"    "<< parameter0[i][0]<<"    "<<error_parameter0[i][0]<<"    "<<parameter1[i][0]<<"    "<<error_parameter1[i][0]<<endl;
// }
// Double_t ex[] = {0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5};
TCanvas* c2 = new TCanvas("c2","parameter0 vs mass",800,800);;
//auto ratio_mass_parameters0 = new TGraphErrors(file_index, particle_mass3, parameter0, 0, error_parameter0);
//ratio_mass_parameters0->SetTitle("parameter0 vs mass");
//ratio_mass_parameters0->SetMarkerStyle(25);
//ratio_mass_parameters0->SetMarkerSize(.7); 
//ratio_mass_parameters0->SetMarkerColor(kRed);
//ratio_mass_parameters0->SetLineColor(kBlack); // Set the line color to 0 (disable line drawing)
ratio_mass_parameters0->GetXaxis()->SetTitle("Mass(MeV)"); 
ratio_mass_parameters0->GetYaxis()->SetTitle("inverse slope");
ratio_mass_parameters0->SetMinimum(0.01);
ratio_mass_parameters0->SetMaximum(2.);
ratio_mass_parameters0->GetXaxis()->SetLimits(100.,1100.);

    

 ratio_mass_parameters0->Draw("APE1");
 gPad->Modified();
 c2->Draw();
// TCanvas* c3 = new TCanvas("c3","parameter1 vs mass",800,600);;
// //auto ratio_mass_parameters1 = new TGraphErrors(file_index, particle_mass3, parameter1, 0, error_parameter1);

// ratio_mass_parameters1->SetTitle("parameter1 vs mass");
// //ratio_mass_parameters1->SetMarkerStyle(25);
// //ratio_mass_parameters1->SetMarkerSize(.7); 
// //ratio_mass_parameters1->SetMarkerColor(kRed);
// //ratio_mass_parameters1->SetLineColor(kBlack); // Set the line color to 0 (disable line drawing)
// ratio_mass_parameters1->GetXaxis()->SetTitle("Mass(MeV)"); 
// ratio_mass_parameters1->GetYaxis()->SetTitle("parameter1");
// ratio_mass_parameters1->SetMinimum(0.);
// ratio_mass_parameters1->SetMaximum(330.);
// ratio_mass_parameters1->GetXaxis()->SetLimits(100.,1100.);
// //for(int i=0;i<file_index;i++)
// //{
//  //   ratio_mass_parameters1->Add(p1[i]);
// //}
// ratio_mass_parameters1->Draw("APE1");
// gPad->Modified();
// c3->Draw();

TCanvas* c4 = new TCanvas("c4","parameter0 vs #frac{dN_{ch}}{d#eta}",800,800);;
c4->SetLogy(0);
c4->SetLogx();
gStyle->SetOptStat(0);
gStyle->SetLegendBorderSize(0);
//auto ratio_mass_parameters1 = new TGraphErrors(file_index, particle_mass3, parameter1, 0, error_parameter1);

//ratio_mass_parameters2->SetTitle("parameter0 vs #frac{dN_{ch}}{d#eta}");
//ratio_mass_parameters1->SetMarkerStyle(25);
//ratio_mass_parameters1->SetMarkerSize(.7); 
//ratio_mass_parameters1->SetMarkerColor(kRed);
//ratio_mass_parameters1->SetLineColor(kBlack); // Set the line color to 0 (disable line drawing)
//ratio_mass_parameters2->GetXaxis()->SetTitle("#frac{dN_{ch}}{d#eta}"); 
//ratio_mass_parameters2->GetYaxis()->SetTitle("parameter0");
//for(int i=0;i<file_index;i++)
//{
 //   ratio_mass_parameters1->Add(p1[i]);
//}
ratio_mass_parameters2->GetXaxis()->SetTitle("dN_{ch}/d#eta");
        ratio_mass_parameters2->GetXaxis()->SetTitleSize(.025);
        ratio_mass_parameters2->GetYaxis()->SetTitle("inverse slope");
        ratio_mass_parameters2->GetYaxis()->SetTitleSize(.02);
        ratio_mass_parameters2->GetXaxis()->CenterTitle(true);
        ratio_mass_parameters2->GetYaxis()->CenterTitle(true);
        ratio_mass_parameters2->GetXaxis()->SetTitleOffset(1.2);
        ratio_mass_parameters2->GetYaxis()->SetTitleOffset(1.8);
        ratio_mass_parameters2->GetXaxis()->SetLabelSize(.020);
        ratio_mass_parameters2->GetYaxis()->SetLabelSize(.020);
        ratio_mass_parameters2->SetMinimum(0.);
        ratio_mass_parameters2->SetMaximum(2.0);
        ratio_mass_parameters2->GetXaxis()->SetLimits(0.5,1000.);
        gPad->SetTickx(1);
        gPad->SetTicky(1); 
        gPad->SetFixedAspectRatio();
        TGaxis::SetMaxDigits(0);
ratio_mass_parameters2->Draw("APE1");
gPad->Modified();
leg->Draw();
TLatex latex;
latex.SetNDC();  // Use normalized coordinates
latex.SetTextSize(0.03);
latex.SetTextAlign(13);  // align at top

double x = 0.7;  // X position in NDC coordinates
double y = 0.2;  // Y position in NDC coordinates

latex.DrawLatex(x, y, true_text);  // Draw the text
c4->Draw();
TString outputfilename = TString::Format("p-%f-%f.pdf", int_low, int_high);
c4->Print(outputfilename.Data());

// TCanvas* c5 = new TCanvas("c5","parameter1 vs #frac{dN_{ch}}{d#eta}",800,600);;
// //auto ratio_mass_parameters1 = new TGraphErrors(file_index, particle_mass3, parameter1, 0, error_parameter1);

// ratio_mass_parameters3->SetTitle("parameter1 vs #frac{dN_{ch}}{d#eta}");
// //ratio_mass_parameters1->SetMarkerStyle(25);
// //ratio_mass_parameters1->SetMarkerSize(.7); 
// //ratio_mass_parameters1->SetMarkerColor(kRed);
// //ratio_mass_parameters1->SetLineColor(kBlack); // Set the line color to 0 (disable line drawing)
// ratio_mass_parameters3->GetXaxis()->SetTitle("#frac{dN_{ch}}{d#eta}"); 
// ratio_mass_parameters3->GetYaxis()->SetTitle("parameter1");
// ratio_mass_parameters3->SetMinimum(0.01);
// ratio_mass_parameters3->SetMaximum(100.);
// ratio_mass_parameters3->GetXaxis()->SetLimits(0.01,1100.);
// //for(int i=0;i<file_index;i++)
// //{
//  //   ratio_mass_parameters1->Add(p1[i]);
// //}
// ratio_mass_parameters3->Draw("APE1");
// gPad->Modified();
// c5->Draw();



    
}