/*This program calculates that the current energy deposit cut of 3 keV (no dE/dx cut) gives 92.7851% electron acceptance efficiency and 97.1324% proton rejection efficiency.
  Then this program finds an optimized combination of simultaneous energy and dE/dx cuts that maximizes proton rejection to 99.8249% without hurting the signal efficiency.
  From the commentary-style output during runtime, it is found that the required combination of cuts is 3.90 keV for Deposit energy and 1.75 keV for dE/dx.
*/


#include <iostream>
#include <cmath>
#include <cstdlib>

float minvalue(float arr[],int n){
  float temp = arr[0];
  for(int s=0;s<n;s++){
    if(temp>arr[s]){
    temp = arr[s];
    }}
  return temp;
}

float maxvalue(float arr[],int n){
  float temp = arr[0];
  for(int s=0;s<n;s++){
    if(temp<arr[s]){
      temp = arr[s];
    }}
  return temp;
}

void test(){
  TFile *f = new TFile("electrons_protons.root");
  TTree *t1 = (TTree*) f->Get("SHD/shdiag");
  TH1F *h1 = new TH1F("h1","h1",100,0,0.006);
  t1->Project("h1","edep","mcpdg==2212");
  TH1F *h2 = new TH1F("h2","h2",100,0,0.006);
  t1->Project("h2","edep","mcpdg==11 && mcom>=100 && mcproc==56");
  float p1 = h1->Integral();
  float e1 = h2->Integral();
  float electron_ratio_edep[101];
  float proton_ratio_edep[101];
  float proton_ratio_edep_rej[101];
  for(int i=0;i<=100;i++){
    TH1F *ht1 = new TH1F("ht1","ht1",100,0,0.006);
    float mycutval1 = i*0.00006;
    t1->Project("ht1","edep",TString::Format("mcpdg==2212 && edep<=%f && edep>=0",mycutval1));
    TH1F *ht2 = new TH1F("ht2","ht2",100,0,0.006);
    t1->Project("ht2","edep",TString::Format("mcpdg==11 && mcom>=100 && mcproc==56 && edep<=%f && edep>=0",mycutval1));
    float paccept1 = ht1->Integral();
    float eaccept1 = ht2->Integral();
    electron_ratio_edep[i]=eaccept1/e1;
    proton_ratio_edep[i]=paccept1/p1;
    proton_ratio_edep_rej[i]=1-(paccept1/p1);
    if(mycutval1-0.003<0.00003 && mycutval1-0.003>-0.00003){std::cout<<"The acceptance ratio corresponding to 3 keV cut is "<<electron_ratio_edep[i]<<" and "<<proton_ratio_edep_rej[i];
    }}
  // int cutoff_edep = 0;
  //for(int m=0;m<=100;m++){
  //  if(electron_ratio_edep[m]>=0.8){
  //    cutoff_edep = cutoff_edep + m;
  //	break;
  //  }}
  //int siz = 101-cutoff_edep;
  //float electron_edep_80[siz];
  //float proton_edep_80[siz];
  //for(int l=cutoff_edep;l<=100;l++){
  //  electron_edep_80[l-cutoff_edep]=electron_ratio_edep[l];
  //  proton_edep_80[l-cutoff_edep]=proton_ratio_edep_rej[l];
  //}   

  TH1F *h3 = new TH1F("h3","h3",100,0,0.007);
  t1->Project("h3","edep/sqrt(pow(2.5,2)-pow(mcshd,2))","mcpdg==2212");
  TH1F *h4 = new TH1F("h4","h4",100,0,0.007);
  t1->Project("h4","edep/sqrt(pow(2.5,2)-pow(mcshd,2))","mcpdg==11 && mcproc==56 && mcom<110 && mcom>80");
  float p2 = h3->Integral();
  float e2 = h4->Integral();
  float electron_ratio_ex[101];
  float proton_ratio_ex[101];
  float proton_ratio_ex_rej[101];
  for(int i=0;i<=100;i++){
    TH1F *ht3 = new TH1F("ht3","ht3",100,0,0.007);
    float mycutval2 = i*0.00007;
    t1->Project("ht3","edep/sqrt(pow(2.5,2)-pow(mcshd,2))",TString::Format("mcpdg==2212 && (edep/sqrt(pow(2.5,2)-pow(mcshd,2)))<=%f",mycutval2));
    TH1F *ht4 = new TH1F("ht4","ht4",100,0,0.007);
    t1->Project("ht4","edep/sqrt(pow(2.5,2)-pow(mcshd,2))",TString::Format("mcpdg==11 && mcproc==56 && mcom<110 && mcom>80 && (edep/sqrt(pow(2.5,2)-pow(mcshd,2)))<=%f",mycutval2));
    float paccept2 = ht3->Integral();
    float eaccept2 = ht4->Integral();
    electron_ratio_ex[i]= eaccept2/e2;
    proton_ratio_ex[i]= paccept2/p2;
    proton_ratio_ex_rej[i]=1-(paccept2/p2);
  }
  // int cutoff_ex = 0;
  // for(int p=0;p<=100;p++){
  //    if(electron_ratio_ex[p]>=0.8){
  //      cutoff_ex = cutoff_ex + p;
  //	break;
  //  }}
  // int siz2 = 101-cutoff_ex;
  // float electron_ex_80[siz2];
  // float proton_ex_80[siz2];
  // for(int q=cutoff_ex;q<=100;q++){
  // electron_ex_80[q-cutoff_ex]=electron_ratio_ex[q];
  //  proton_ex_80[q-cutoff_ex]=proton_ratio_ex_rej[q];
  //}   


  float  ROC_x[101];
  float  ROC_y[101];
  float dummy[101];
  bool bools = true;
  for(int e_percent=0; e_percent<=100; e_percent++){
    float x = (float(e_percent))/(float(100));
    ROC_x[e_percent] = x;
    std::cout<<"Net electron ratio = "<<x<<"\n";
    int cut = 0;
    for(int i=0; i<=100; i++){
      if(electron_ratio_edep[i]>=x){
	cut = cut + i;
	break;
      }}
    int count = 101 - cut;
    float allprotons_edep[count];
    float allprotons_ex[count];
    float productprotons[count];
    float cutvalues_edep[count];
    float cutvalues_ex[count];
    for(int i=cut;i<=100;i++){
      allprotons_edep[i-cut] = proton_ratio_edep[i];
      cutvalues_edep[i-cut]=i*0.00006;
      float y = electron_ratio_edep[i];
      float z = x/y;
      float ex_temp[101];
      for(int j=0;j<=100;j++){
	ex_temp[j] = sqrt(pow(z - electron_ratio_ex[j],2));
      }
      for(int j=0;j<=100;j++){
	if(ex_temp[j] == minvalue(ex_temp,101)){
	  allprotons_ex[i-cut] = proton_ratio_ex[j];
	  cutvalues_ex[i-cut]=j*0.00007;
	  break;
	}}
      productprotons[i-cut] = (allprotons_edep[i-cut])*(allprotons_ex[i-cut]);
      dummy[i-cut] = allprotons_edep[i-cut];
    }
    float final_proton_ratio = 0;
    if(bools){
      final_proton_ratio =final_proton_ratio + minvalue(productprotons,101-cut);
    }
    if(not bools){
      final_proton_ratio = final_proton_ratio + minvalue(dummy,101-cut);
    }
    std::cout<<"Maximum product of proton ratios = "<<final_proton_ratio<<"\n";
    for(int k=cut;k<=100;k++){
      if(productprotons[k-cut]== minvalue(productprotons,101-cut)){
	std::cout<<"The edep cut value is "<<cutvalues_edep[k-cut]<<" and the dE/dx cut value is "<<cutvalues_ex[k-cut]<<" \n";
	}}
    ROC_y[e_percent] = 1-final_proton_ratio;
  }

  TGraph *g1 = new TGraph(101,ROC_x,ROC_y);
  TGraph *g2 = new TGraph(101,electron_ratio_edep,proton_ratio_edep_rej);
  TGraph *g3 = new TGraph(101,electron_ratio_ex,proton_ratio_ex_rej);
  g1->SetLineColor(kRed);
  g2->SetLineColor(kBlue);
  g3->SetLineColor(kGreen);
  g1->SetLineWidth(3);
  g2->SetLineWidth(3);
  g3->SetLineWidth(3);
  TMultiGraph *mg = new TMultiGraph();
  mg->Add(g1);
  mg->Add(g2);
  mg->Add(g3);
  mg->SetTitle("ROC for Energy and(or) dE/dx cuts");
  mg->GetXaxis()->SetTitle("Electron Acceptance Efficiency");
  mg->GetYaxis()->SetTitle("Proton Rejection Efficiency");
  mg->Draw("ALP");
  TLegend *legend= new TLegend(0.1,0.7,0.48,0.9);
  legend->SetHeader("Header","C");
  legend->AddEntry(g1,"Energy + dE/dx","l");
  legend->AddEntry(g2,"Energy only","l");
  legend->AddEntry(g3,"dE/dx only","l");
  legend->Draw();

}



