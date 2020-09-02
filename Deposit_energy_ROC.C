#include <iostream>

void test(){

  TFile *f = new TFile("electrons_protons.root");
  TTree *t3 = (TTree*) f->Get("SHD/shdiag");
  TH1F *h5 = new TH1F("h5","h5",40,0,0.006);
  t3->Project("h5","edep","mcpdg==2212");
  TH1F *h6 = new TH1F("h6","h6",40,0,0.006);
  t3->Project("h6","edep","mcpdg==11 && mcom>=100 && mcproc==56");
  float p = h5->Integral();
  float e = h6->Integral(); 
  float electron_ratio[101];
  float proton_ratio[101];
  for (int i=0; i<=100; i++){
    TH1F *h3 = new TH1F("h3","h3",40,0,0.006);
    double mycutval = i*0.00006;
    t3->Project("h3","edep",TString::Format("mcpdg==2212 && edep<=%f && edep>=0",mycutval));
    TH1F *h4 = new TH1F("h4","h4",40,0,0.006);
    t3->Project("h4","edep",TString::Format("mcpdg==11 && mcom >=100 && mcproc ==56 && edep<=%f && edep>=0",mycutval) );
    float pa = h3->Integral();
    float ea = h4->Integral();
    electron_ratio[i]=ea/e;
    proton_ratio[i]=1-(pa/p);
    std::cout<<"cutvalue = "<<i*0.0006<<" electrons accepted ratio = "<<ea/e<<" and proton acceptance ratio = "<<pa/p<<std::endl;
    electron_ratio[i]=ea/e;
    proton_ratio[i]=1-(pa/p);
  }
  //TH2F *h7 = new TH2F("h7","ROC",101,0,1,101,0,1);
  TGraph *g = new TGraph(101,proton_ratio,electron_ratio);
  g->SetLineColor(kRed);
  g->SetLineWidth(3);
  TMultiGraph *mg = new TMultiGraph();
  mg->Add(g);
  mg->SetTitle("ROC for Energy deposit cuts");
  mg->GetXaxis()->SetTitle("Electron Acceptance Efficiency");
  mg->GetYaxis()->SetTitle("Proton Rejection Efficiency");
  mg->Draw("ALP");
 
  }



  //TFile *f = new TFile("electrons_protons.root");
  //TTree *t3 = (TTree*) f->Get("SHD/shdiag");
  //TH1F *h3 = new TH1F("h3","h3",50,-0.001,0.005);
  //t3->Project("h3","mcedep/sqrt(pow(2.5,2)-pow(mcshd,2))","mcpdg==2212");
  //TCanvas *c1 = new TCanvas("c1","response");
  //h3->Scale(1.0/h3->Integral());
  //h3->Draw("HIST");
  //TH1F *h4 = new TH1F("h4","h4",50,-0.001,0.005);
  //t3->Project("h4","mcedep/sqrt(pow(2.5,2)-pow(mcshd,2))","mcpdg==11 && mcproc==56 && mcom>80 && mcom < 110");
  //h4->Scale(1.0/h4->Integral());
  //h4->Draw("HIST Same");
  //h3->SetLineColor(kRed);
  //h4->SetLineColor(100);
  //}




//TFile *f = new TFile("electrons_protons.root");
//TTree *t = (TTree*) f->Get("shdiag");
//TH1F *h1 = new TH1F("h1","h1",50,-0.001,0.03);
  //t->Draw("edep");
  //t->Project("h1","edep");





