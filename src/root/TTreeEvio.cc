/**
* Autogenerated Source File for TTreeEvio
* \\file TTreeEvio.cc
* \\author G.Gavalian
* \\date 2014-09-25
*/
#include "TTreeEvio.h"

ClassImp(TTreeEvio)

TTreeEvio::TTreeEvio() : TTree("CLAS12Tree","CLAS 12 Evio Tree")
{
  //variable = 2.5;
  //TBranch *branchPCAL =  Branch("PCAL",&variable,"time:path:energy");
  //TBranch *branchFTOF =  Branch("FTOF",&variable,"energy");
  //TBasket *energy  = new TBasket("energy","PCAL energy",branchFTOF);
  //branchPCAL->AddBasket(*energy,false,0);
}

TTreeEvio::TTreeEvio(const char *filename) : TTree("CLAS12Tree","CLAS 12 Evio Tree")
{
    evioReader = new EvioFileReader();
    evioReader->open(filename);
    InitDescriptors();
    InitBranches();
}
/* 
TTreeEvio::TTreeEvio(const TTreeEvio &obj)
{
}
*/
TTreeEvio::~TTreeEvio()
{
}

Long64_t    TTreeEvio::GetEntries() const
{
  if(evioReader!=NULL){
    return evioReader->getEntries();
  }
  return 0;
}
Long64_t    TTreeEvio::GetEntries(const char* selection)
{
  if(evioReader!=NULL){
    return evioReader->getEntries();
  }
  return 0;
}
Long64_t    TTreeEvio::GetEntriesFast() const
{
  if(evioReader!=NULL){
    return evioReader->getEntries();
  }
  return 0;
}

Long64_t  TTreeEvio::GetEntriesFriend() const {
  if(evioReader!=NULL){
    return evioReader->getEntries();
  }
  return 0;
}

Long64_t    TTreeEvio::LoadTree(Long64_t entry)
{
  //cout << "-----> load tree function called" << endl;
  TBranch  *EVHB = GetBranch("EVNTHB::particle");
  TLeafI   *entLeaf = (TLeafI *) EVHB->GetLeaf("entries");
  entLeaf->SetMinimum(0);
  entLeaf->SetMaximum(100);
  TLeafF   *pxLeaf = (TLeafF *)  EVHB->GetLeaf("px");
  int *counter = new int[1];
  evioReader->readEvent(entry);
  int len;
  float *bufferPx = evioReader->getEvent().getf(4601,7,&len);
  if(len==0){
    counter[0] = 0;
    valueI = 0;
    entLeaf->SetLen(1);
    entLeaf->SetAddress(&counter[0]);
  } else {
    counter[0] = len;
    entLeaf->SetLen(1);
    entLeaf->SetAddress(&counter[0]);
    valueI = len;
    pxLeaf->SetLen(len);
    pxLeaf->SetAddress(bufferPx);
  }
  //cout << " Reading PX LENGTH = " << len << "  counter = " << entLeaf->GetValue() 
  //<< "  " << entLeaf->GetNdata() << "  " << entLeaf->GetMinimum() << "  " << entLeaf->GetMaximum()
  // << endl; 
}

void        TTreeEvio::InitBranches()
{
  //Branch("entries",&valueI,"entries[10]/I");
  Branch("EVNTHB::particle",&variableD,"entries/I:status[entries]/I:charge[entries]/I:pid[entries]/I:mass[entries]/F:beta[entries]/F:px[entries]/F:pz[entries]/F:py[entries]/F");
  //InitBranch(bankEvnt);
}


void        TTreeEvio::InitBranch(TBankDescriptor &desc)
{
  TBranch  *branch = Branch(desc.GetName(),&variableI,desc.GetFormatString().c_str());
  TLeafI   *counterLeaf = (TLeafI *) branch->GetLeaf("entries");
  counterLeaf->SetMaximum(20);
}

void        TTreeEvio::InitDescriptors()
{
  bankEvnt.SetName("EVNT");
  bankEvnt.AddEntry("status"  ,"I", 4601, 1  );
  bankEvnt.AddEntry("charge"  ,"I", 4601, 2  ); 
  bankEvnt.AddEntry("pid"     ,"I", 4601, 3  );
  bankEvnt.AddEntry("chi2pid" ,"F", 4601, 4  );
  bankEvnt.AddEntry("mass"    ,"F", 4601, 5  );
  bankEvnt.AddEntry("beta"    ,"F", 4601, 6  ); 
  bankEvnt.AddEntry("px"      ,"F", 4601, 7  ); 
  bankEvnt.AddEntry("py"      ,"F", 4601, 8  ); 
  bankEvnt.AddEntry("pz"      ,"F", 4601, 9  );
  bankEvnt.AddEntry("vx"      ,"F", 4601, 10 ); 
  bankEvnt.AddEntry("vy"      ,"F", 4601, 11 ); 
  bankEvnt.AddEntry("vz"      ,"F", 4601, 12 ); 
  cout << " EVNT : " << bankEvnt.GetFormatString().c_str();
}
/*
Long64_t TTreeEvio::Draw(const char* varexp, const char* selection, Option_t* option, Long64_t nentries, Long64_t firstentry){
  cout << "  Tree Drawing is called variable [" << varexp << "]  selection [" << selection << "]" <<  endl;

  //TH1D *tmp = (TH1D *) gDirectory->Get();
  //if(tmp!=NULL){
  //  cout << " Deleting histogram " << endl;
  //}
  if(gDirectory->FindObject(varexp)!=NULL){
    cout << " Deleting histogram " << varexp << endl;
    gDirectory->Delete(varexp);
  }
  
  TH1D *H = new TH1D(varexp,varexp,100,0.0,1.0);
  H->Draw();
}
*/
/* const TTreeEvio &TTreeEvio::operator=(const TTreeEvio &obj){} */
