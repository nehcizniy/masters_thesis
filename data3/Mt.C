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
Double_t parameter0[40];
Double_t parameter1[40];
TString filename_array[40];
TString parameter_index_collab[] = {"phenix","star"};
TString parameter_index_system[] = {"AuAu","CuAu","dAu","3HeAu","UU","pAl","pAu","CuCu"};
TString parameter_index_particle[] = {"k+","k-","-p-","pbar","pi+","pi-","pi0","phi"};
Double_t parameter_index_mass[] = {493.677, 493.677, 938.272, 938.272, 139.570, 139.570, 134.9768, 1019.461};
Double_t error_parameter0[40];
Double_t error_parameter1[40];
const int color[] = {kRed, kBlue, kMagenta, kCyan, kGreen+2, kYellow+4, kBlack, kGray};
Double_t particle_mass[] = {493.677, 493.677, 938.272, 938.272, 139.570, 139.570, 134.9768, 134.9768, 1019.461};//k+, k-, p, pbar, pi+, pi-, pi0, pi0, phi
Double_t kaon_mass = 493.677;
Double_t proton_mass = 938.272;
Double_t pion_mass = 139.570;
Double_t pi0_mass = 134.9768;
Double_t phi_mass = 1019.461;
Double_t particle_mass2[] = {493.677, 493.677, 493.677, 493.677, 938.272, 938.272, 938.272, 938.272, 1019.461, 1019.461, 1019.461, 1019.461, 1019.461, 139.570, 139.570, 139.570, 139.570, 134.9768, 134.9768, 134.9768, 134.9768, 134.9768, 134.9768, 134.9768, 493.677, 493.677, 938.272, 938.272, 1019.461, 139.570, 139.570};
Double_t particle_mass3[] = {493.677, 493.677, 938.272, 938.272, 139.570, 139.570};
void Mt()
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

    TGraphErrors* p0[40];
    TGraphErrors* p1[40];
    //TCanvas* c0[40][40];
    TH1F *spectra_fill[40][40];
    TGraphMultiErrors* spectra_fit[40][40];
    TCanvas* c1 = new TCanvas("c1","Pt vs Yield",800,600);
    c1->SetLogy();
    c1->SetLogx();
    gStyle->SetOptStat(0);
    gStyle->SetLegendBorderSize(0);

    TLegend* leg = new TLegend(0.15,0.55,0.3,0.89);
    leg->SetFillStyle(0);
    TGraphMultiErrors* g[total_num_of_files][30];
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
        char cent[40];
        int centlow[40];
        int centhigh[40];
        Float_t Nch[40];
        float Ncher[40];
        int NumCentIndex = 0;
        int CurrentCentIndex = -1;
        int CurrentPtIndex = 0;
        float pt[40][100];
        float mt[40][100];
        Double_t ptlow[40][100];
        Double_t pthigh[40][100];
        float yield[40][100];
        int bin_num[40];
        int fill_num[40]={0};
        float ratio_binshift[40][100];
        float yield_corrected[40][100];
        Float_t integrated_yield[40]={0};
        Float_t integrated_yield_corrected[40]={0};
        Float_t stat_integrated_yield[40]={0};
        Float_t sys_integrated_yield[40]={0};
        float dn_deta[40][100]={0};
        float errdn_deta[40][100]={0};
        float statp[40][100];
        float statm[40][100];
        Double_t sysp[40][100];
        Double_t sysm[40][100];
        TString fit_int_yield[] = {"fit_int_yield1", "fit_int_yield2", "fit_int_yield3" "fit_int_yield4" "fit_int_yield5" "fit_int_yield6" "fit_int_yield7", "fit_int_yield8", "fit_int_yield9", "fit_int_yield10", "fit_int_yield11", "fit_int_yield12", "fit_int_yield13", "fit_int_yield14", "fit_int_yield15", "fit_int_yield16", "fit_int_yield17", "fit_int_yield18", "fit_int_yield19", "fit_int_yield20" };


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
                for(int i=0;i<8;++i)
        {
            if(filename.Contains(parameter_index_particle[i]))
            {
                mt[CurrentCentIndex][CurrentPtIndex] = sqrt(pt[CurrentCentIndex][CurrentPtIndex]*pt[CurrentCentIndex][CurrentPtIndex]+0.000001*parameter_index_mass[i]*parameter_index_mass[i])-0.001*parameter_index_mass[i];
                cout<<pt[CurrentCentIndex][CurrentPtIndex]<<"    "<<mt[CurrentCentIndex][CurrentPtIndex]<<endl;
            }
        }
                if (pt[CurrentCentIndex][CurrentPtIndex]<=5)
                {
                    fill_num[CurrentCentIndex] +=1;
                    //cout << "fill_num[" <<CurrentCentIndex <<"]= " << fill_num[CurrentCentIndex]<<endl;
                }
                //cout << pt[CurrentCentIndex][CurrentPtIndex] << endl;

                if(pt[CurrentCentIndex][CurrentPtIndex] > int_low && pt[CurrentCentIndex][CurrentPtIndex] < int_high)
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



    /*for (int i = 0; i < NumCentIndex; ++i) //get ratio_binshift and yield_corrected
    {   
        int k = file_index;
        cout << centlow[i] << "\t" << centhigh[i] << endl;
        //c0[k][i] = new TCanvas(Form("%d - %d - %d",k, centlow[i],centhigh[i]), Form("%s - %d - %d",AuAu200only[k], centlow[i],centhigh[i]), 800, 600);
        //c0[k][i]->SetLogy();
        //c0[k][i]->SetLogx(0);
        //gStyle->SetOptStat(0);
        //gStyle->SetLegendBorderSize(0);
        
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
        spectra_fit[k][i]->SetTitle(filename);

        //spectra_fit[k][i]->SetTitle(Form("%s cent_%d-%d", hdvi, i. i+1));
        //spectra_fit[k][i]->Draw("AP");
        //spectra_fill[k][i]->Draw("same");
    }
    */


    /*for (int i = 0; i < NumCentIndex; ++i)  //get integrated_yield_corrected
    {   
        int N = bin_num[i]-1;
        for(int j=0; j<N;j++)
        {
        
        if(pt[i][j] > int_low && pt[i][j] < int_high)
            {   //cout<< pt[i][j]<<"  "<< yield[i][j]<<"  "<< ratio_binshift[i][j]<<"  "<< yield_corrected[i][j]<<endl;
                integrated_yield_corrected[i] += 2*TMath::Pi() * pt[i][j] * yield_corrected[i][j] * (pthigh[i][j] - ptlow[i][j]);
            }
        }
    }*/


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
    for (int i = 0; i < 1; ++i) 
    {   //stat_integrated_yield[i] = sqrt(stat_integrated_yield[i]);
        //sys_integrated_yield[i] = sqrt(sys_integrated_yield[i]);
        
        cout << k << "\t" << integrated_yield[i] << "\t" << integrated_yield_corrected[i]<< "\t"<<  stat_integrated_yield[i]<< "\t"<<  sys_integrated_yield[i]<<endl;

    
        if(filename.Contains("phenix")){g[k][i] = new TGraphMultiErrors(bin_num[i],mt[i],yield[i],0,0,statp[i], statp[i]);}
        //if(filename.Contains("star")){g[k][i] = new TGraphMultiErrors(bin_num[i],mt[i],yield[i],0,0,statp[i], statp[i]);}
        //g[k][i]->SetTitle("pi0 at 200GeV"); // set the title of the graph
        
        //g[k]->AddYError(NumCentIndex,sys_integrated_yield, sys_integrated_yield);
        g[k][i]->SetMinimum(0.00000000001);
        g[k][i]->SetMaximum(100.);
        //g[k]->GetAttLine(0)->SetLineColorAlpha(kRed, 1);
        //g[k][i]->GetAttLine(1)->SetLineColor(kBlue);
        //g[k]->GetAttFill(1)->SetFillStyle(0);
        //g[k]->SetMarkerStyle(20+color_index); 
        //g[k]->SetMarkerSize(.7); 
        g[k][i]->SetMarkerColorAlpha(color[color_index],1);//color[color_index]
        g[k][i]->SetLineColor(color[color_index]); 
        //g[k]->SetLineWidth(1); 
        g[k][i]->SetFillStyle(0);

        TF1* fit_int_yield_index = new TF1("fit_int_yieldx","exp(-x/[0])*[1]", int_low, int_high);
        Double_t params[] = {0.3484,48.3};
        fit_int_yield_index->SetParameters(params);
       //fit_int_yield_index->SetParameter(0.9991, 0.0018);
       //fit_int_yield_index->SetParLimits(0,0.,1);
       //fit_int_yield_index->SetParLimits(1,0.5,2.5);
        for(int j=0;j<5;++j)
        {
            fit_int_yield_index->SetParameters(fit_int_yield_index->GetParameter(0),fit_int_yield_index->GetParameter(1));
            g[k][i]->Fit(fit_int_yield_index, "R");
        }
        parameter0[k] = fit_int_yield_index->GetParameter(0);
        parameter1[k] = fit_int_yield_index->GetParameter(1);
        error_parameter0[k] = fit_int_yield_index->GetParError(0);
        error_parameter1[k] = fit_int_yield_index->GetParError(1);
        g[k][i]->GetFunction("fit_int_yieldx")->SetLineColor(color[color_index]);
        g[k][i]->GetFunction("fit_int_yieldx")->SetLineWidth(1); 
        g[k][i]->GetFunction("fit_int_yieldx")->SetLineStyle(2); 

        p0[k] = new TGraphErrors();
        p1[k] = new TGraphErrors();
        for(int j=0;j<8;++j)
        {
            if(filename_array[k].Contains(parameter_index_particle[i]))
            {   
                p0[k]->SetPoint(0,parameter_index_mass[j],parameter0[k]);
                cout<< filename_array[k]<<endl;
                p1[k]->SetPoint(0,parameter_index_mass[j],parameter1[k]);
                p0[k]->SetPointError(0,0,error_parameter0[k]);
                p1[k]->SetPointError(0,0,error_parameter1[k]);
                p0[k]->SetMarkerColor(color[j]);
                p1[k]->SetMarkerColor(color[j]);
                g[k][i]->SetMarkerColor(color[j]);
            }
        }
        for(int j=0;j<2;++j)
        {
            if(filename.Contains(parameter_index_collab[j]))
            {
                p0[k]->SetMarkerSize(0.4*(1+j));
                p1[k]->SetMarkerSize(0.4*(1+j));
                g[k][i]->SetMarkerSize(0.4*(1+j));
            }
        }
        for(int j=0;j<8;++j)
        {
            if(filename.Contains(parameter_index_system[j]))
            {
                p0[k]->SetMarkerStyle(20+j);
                p1[k]->SetMarkerStyle(20+j);
                g[k][i]->SetMarkerStyle(20+j);
            }
        }

        //fit_int_yield_index->Draw();
        //g[k][i]->GetXaxis()->SetTitle("frac{dN_{ch}}{d#eta}"); 
        //g[k][i]->GetYaxis()->SetTitle("int.yield");
        //leg->AddEntry(g[k][i],Form("%d - %d",centlow[i],centhigh[i]),"lep"); // add the graph to the legend
        //if(i==0) gr->Draw("APL"); // draw the first graph with axes
        //else gr->Draw("PLSAME");
        {leg->AddEntry(g[k][i], filename, "p");}
        //g[k][i]->Draw("APE ; Z ; 5 s = 0.5");
        mg->Add(g[k][i], "APE ; Z ; 5 s = 0.5");
        mg->Draw("APE");
        //fit_int_yield_index->Draw("same");
    }
    leg->Draw("p");
    style_index++;
    color_index++;
    file_index++;
}


/*TF1* fit_int_yield = new TF1("fit_int_yield","pow(x,[0])*[1]", 1.5, 1000.);
Double_t params[] = {0.9991, 0.0018};
fit_int_yield->SetParameters(params);
mg->Fit(fit_int_yield,"R");
mg->GetFunction("fit_int_yield")->SetLineWidth(1); */
gPad->Modified();
   mg->GetXaxis()->SetLimits(.1,20.);
   //mg->GetYaxis()->SetRangeUser(0.001,200);
   mg->SetMinimum(0.0001);
   mg->SetMaximum(1000.);
gPad->Modified();
for(int i=0;i<file_index;i++){
    cout<< i << "    "<< filename_array[i]<<"    "<< parameter0[i]<<"    "<<error_parameter0[i]<<"    "<<parameter1[i]<<"    "<<error_parameter1[i]<<endl;
}
Double_t ex[] = {0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5};
TCanvas* c2 = new TCanvas("c2","parameter0 vs mass",800,600);;
auto ratio_mass_parameters0 = new TGraphErrors(file_index, particle_mass3, parameter0, 0, error_parameter0);
//auto ratio_mass_parameters0 = new TMultiGraph();
ratio_mass_parameters0->SetTitle("parameter0 vs mass");
ratio_mass_parameters0->SetMarkerStyle(25);
ratio_mass_parameters0->SetMarkerSize(.7); 
ratio_mass_parameters0->SetMarkerColor(kRed);
ratio_mass_parameters0->SetLineColor(kBlack); // Set the line color to 0 (disable line drawing)
ratio_mass_parameters0->GetXaxis()->SetTitle("Mass(MeV)"); 
ratio_mass_parameters0->GetYaxis()->SetTitle("parameter0");
ratio_mass_parameters0->SetMinimum(0.25);
ratio_mass_parameters0->SetMaximum(0.45);
ratio_mass_parameters0->GetXaxis()->SetLimits(100.,1100.);
//for(int i=0;i<file_index;i++)
//{
//    ratio_mass_parameters0->Add(p0[i]);
//}
ratio_mass_parameters0->Draw("APE1");
gPad->Modified();
c2->Draw();
TCanvas* c3 = new TCanvas("c3","parameter1 vs mass",800,600);;
auto ratio_mass_parameters1 = new TGraphErrors(file_index, particle_mass3, parameter1, 0, error_parameter1);
//auto ratio_mass_parameters1 = new TMultiGraph();
ratio_mass_parameters1->SetTitle("parameter1 vs mass");
ratio_mass_parameters1->SetMarkerStyle(25);
ratio_mass_parameters1->SetMarkerSize(.7); 
ratio_mass_parameters1->SetMarkerColor(kRed);
ratio_mass_parameters1->SetLineColor(kBlack); // Set the line color to 0 (disable line drawing)
ratio_mass_parameters1->GetXaxis()->SetTitle("Mass(MeV)"); 
ratio_mass_parameters1->GetYaxis()->SetTitle("parameter1");
ratio_mass_parameters1->SetMinimum(0.);
ratio_mass_parameters1->SetMaximum(330.);
ratio_mass_parameters1->GetXaxis()->SetLimits(100.,1100.);
//for(int i=0;i<file_index;i++)
//{
 //   ratio_mass_parameters1->Add(p1[i]);
//}
ratio_mass_parameters1->Draw("APE1");
gPad->Modified();
c3->Draw();



    
}