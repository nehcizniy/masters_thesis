// Macro myfunc.C
/*Double_t myfunction(Double_t *x, Double_t *par)
{
   Float_t xx =x[0];
   Double_t f = TMath::Abs(par[0]*sin(par[1]*xx)/xx);
   return f;
}*/
// bin distribution
Double_t xbin[23] = {0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.2,2.4,2.6,2.8,3.0,3.5,4.0};

void myfunc()
{  
   //fit function
    TF1* fHagedorn = new TF1("fHagedorn","[0]/pow((exp(-[1]*x -[2]*x*x) + x/[3]),[4])", 0.5, 4.0);// fit function
    fHagedorn->SetParameters(5.26451e+01, 7.19392e-01, 5.42228e-02, 1.02260e+00, 7.88555e+00);
   //auto f1 = new TF1("myfunc",myfunction,0,10,2);
   //f1->SetParameters(2,1);
   //f1->SetParNames("constant","coefficient");
   fHagedorn->Draw();
//}
//void myfit()
//{
   auto h1 = new TH1D("fHagedorn","test",22,xbin);
   h1->FillRandom("fHagedorn",1000000);
   
   TF1 *f1 = (TF1 *)gROOT->GetFunction("fHagedorn");
   f1->SetParameters(5.26451e+01, 7.19392e-01, 5.42228e-02, 1.02260e+00, 7.88555e+00);
   h1->Scale(1.0/1000000);
   h1->Fit("fHagedorn");
}
void linear_func()
   {
      TF1* test1 = new TF1("test1","[0]*x",0.5,4.);
      Double_t params[] = {1.0};
      test1->SetParameters(params);
      test1->Draw();
      auto t1 = new TH1D("linear","test1",22,xbin);
      t1->FillRandom("test1",1000000);
      for (int j = 1; j <= t1->GetNbinsX(); j++) 
        {
            double content = t1->GetBinContent(j);
            double binWidth = t1->GetBinWidth(j);
            double dividedContent = content / binWidth;
            t1->SetBinContent(j, dividedContent);
        }
      double integral = test1->Integral(0.5,4.);
      double integral2 = t1->Integral();
      t1->Scale(integral/1000000);
      t1->Fit("test1");
      t1->Draw("same");
   }
void non_linear_func()
   {
      TF1* test1 = new TF1("test1","pow(x,[0])",0.5,4.);
      Double_t params[] = {2.0};
      test1->SetParameters(params);
      test1->Draw();
      auto t1 = new TH1D("non_linear","test1",22,xbin);
      t1->FillRandom("test1",1000000);
      for (int j = 1; j <= t1->GetNbinsX(); j++) 
        {
            double content = t1->GetBinContent(j);
            double binWidth = t1->GetBinWidth(j);
            double dividedContent = content / binWidth;
            t1->SetBinContent(j, dividedContent);
        }
      double integral = test1->Integral(0.5,4.);
      double integral2 = t1->Integral();
      t1->Scale(integral/1000000);
      t1->Fit("test1");
      t1->Draw("same");
   }
void expo()
   {
      TF1* test1 = new TF1("test1","pow([0],x)",0.5,4.);
      Double_t params[] = {2.0};
      test1->SetParameters(params);
      test1->Draw();
      auto t1 = new TH1D("non_linear","test1",22,xbin);
      t1->FillRandom("test1",1000000);
      for (int j = 1; j <= t1->GetNbinsX(); j++) 
        {
            double content = t1->GetBinContent(j);
            double binWidth = t1->GetBinWidth(j);
            double dividedContent = content / binWidth;
            t1->SetBinContent(j, dividedContent);
        }
      double integral = test1->Integral(0.5,4.);
      double integral2 = t1->Integral();
      t1->Scale(integral/1000000);
      t1->Fit("test1");
      t1->Draw("same");
   }