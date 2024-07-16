#include "TFile.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TSystemDirectory.h"
#include "TList.h"
#include "TRegexp.h"

void plotp() {
    TMultiGraph* mg = new TMultiGraph();
    TGraphErrors* g[30];
    // Get the current directory
    TString dir = gSystem->pwd();

    // Get a list of all files in the directory
    TSystemDirectory sysdir(dir, dir);
    TList *files = sysdir.GetListOfFiles();

    // Regular expression for text files
    TRegexp re("*.txt", kTRUE);
    int k = 0;
    if (files) {
        TIter next(files);
        TSystemFile *file;

        // Loop over all files
        while ((file = (TSystemFile*)next())) {
            TString filename = file->GetName();

            // If the file name matches the regular expression
            if (filename.Contains(re)) {

                cout<< filename << endl;
                g[k] = new TGraphErrors(filename.Data(), "%lg %lg %lg");
                g[k]->SetMarkerStyle(21+k); 
                g[k]->SetMarkerSize(1.5); 
                g[k]->SetMarkerColorAlpha(k+1,1);
                g[k]->SetLineColor(k+1); 
                g[k]->SetFillStyle(0);
TF1* fit_int_yield_index = new TF1("fit_int_yieldx","[1]*log(x)+[0]", 2., 1000.);
        Double_t params[] = {0.8013, 0.0327};
        fit_int_yield_index->SetParameters(params);
        for(int j=0;j<10;++j)
        {
            g[k]->Fit(fit_int_yield_index, "Q");
        }
        cout<<fit_int_yield_index->GetParameter(0)<< "  " << fit_int_yield_index->GetParameter(1)<<endl;
                mg->Add(g[k]);
                k++;
            }

        }
    }

    // Create a canvas
    TCanvas *c1 = new TCanvas("c1", "meanpt", 800,800);
    c1->SetLogy(0);
    c1->SetLogx();
    gStyle->SetOptStat(0);
    gStyle->SetLegendBorderSize(0);

    TLegend* leg = new TLegend(0.12,0.70,0.70,0.88);
    leg->SetFillStyle(0);

    mg->GetXaxis()->SetTitle("<N_{coll}>");
    mg->GetXaxis()->SetTitleSize(.025);
    mg->GetYaxis()->SetTitle("ratio to MB");
    mg->GetYaxis()->SetTitleSize(.025);
    mg->GetXaxis()->CenterTitle(true);
    mg->GetYaxis()->CenterTitle(true);
    mg->GetXaxis()->SetTitleOffset(1.2);
    mg->GetYaxis()->SetTitleOffset(1.2);
    mg->GetXaxis()->SetLabelSize(.020);
    mg->GetYaxis()->SetLabelSize(.020);

    mg->GetXaxis()->SetLimits(.5,1100.);
    mg->SetMinimum(0.85);
    mg->SetMaximum(1.1);
    gPad->SetTickx(1);
    gPad->SetTicky(1); 
    gPad->SetFixedAspectRatio();
    TGaxis::SetMaxDigits(0);
    gPad->Modified();

    mg->Draw("APX");

    leg->SetNColumns(4);
        // Add entries for particle labels in the first row

// Add entries for AuAu
leg->AddEntry(new TNamed(), "Au+Au 2004","");
leg->AddEntry(g[0], " ", "p");

leg->AddEntry(new TNamed(), "Cu+Au","");
leg->AddEntry(g[1], " ", "p");

leg->AddEntry(new TNamed(), "3He+Au","");
leg->AddEntry(g[2], " ", "p");

// Add entries for dAu
leg->AddEntry(new TNamed(), "d+Au","");
leg->AddEntry(g[3], " ", "p");

leg->AddEntry(new TNamed(), "p+Au","");
leg->AddEntry(g[4], "#bar{p}", "p");

leg->AddEntry(new TNamed(), "p+Al","");
leg->AddEntry(g[5], "#bar{p}", "p");



leg->SetTextSize(0.025);
leg->Draw();
c1->Draw();

}