#include <iostream>


void test(){

  TFile *f = new TFile("muons105.root");
  TFile *f2 = new TFile("electrons105.root");

  TTree *t3 = (TTree*) f->Get("SHD/shdiag");
  TH1F *h3 = new TH1F("h3","h3",50,-0.001,0.005);
  t3->Project("h3","mcedep/sqrt(pow(2.5,2)-pow(mcshd,2))","mcpdg==13 && mcproc ==56 && mcom<110 && mcom>80");
  TCanvas *c1 = new TCanvas("c1","response");
  h3->Scale(1.0/h3->Integral());
  h3->Draw("HIST");
 
  TTree *t4 = (TTree*) f2->Get("SHD/shdiag");
  TH1F *h4 = new TH1F("h4","h4",50,-0.001,0.005);
  t4->Project("h4","mcedep/sqrt(pow(2.5,2)-pow(mcshd,2))","mcpdg==11 && mcproc ==56 && mcom<110 && mcom>80");
  h4->Scale(1.0/h4->Integral());
  h4->Draw("HIST Same");

  h3->SetLineColor(kRed);
  TLegend *legend2 = new TLegend(0.6,0.7,0.9,0.9);
  legend2->SetHeader("muon v electron response","C");
  legend2->AddEntry("h3","muon dE/dX","l");
  legend2->AddEntry("h4","electron dE/dX","l");
  legend2->Draw();
  
 }
