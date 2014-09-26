/**
* Autogenerated Header File for TTreeEvio
* \\file TTreeEvio.h
* \\author G.Gavalian
* \\date 2014-09-25
*/
#ifndef __TTREEEVIO__
#define __TTREEEVIO__
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "TTree.h"
#include "TROOT.h"
#include "TBasket.h"
#include "TLeafI.h"
#include "TLeafD.h"
#include "TLeafF.h"
#include "TH1D.h"
#include "TDirectory.h"
#include "EvioFileReader.h"
#include "TBankDescriptor.h"

using namespace std;
//! A Brief Description
/*
 * A detailed description
 */
class TTreeEvio  : public TTree {

private:
  
  Double_t  variableD;
  Int_t     variableI;
  Int_t     valueI;
  TBankDescriptor   bankEvnt;
  EvioFileReader *evioReader;

public:

/** Default Constructor */

TTreeEvio();
TTreeEvio(const char *filename);

/** Default Destructor */
~TTreeEvio();
/** Copy Constructor if one is needed */
/*TTreeEvio( const TTreeEvio &obj); */ 
 //Long64_t Draw(const char* varexp, const char* selection, Option_t* option = "", Long64_t nentries = 1000000000, Long64_t firstentry = 0);
/** An operator = if one is needed */
/* const TTreeEvio &operator=(const TTreeEvio &obj); */

Long64_t    GetEntries() const;
Long64_t    GetEntries(const char* selection);
Long64_t    GetEntriesFast() const;
Long64_t    GetEntriesFriend() const;
Long64_t    LoadTree(Long64_t entry);
void        InitBranches();

void        InitBranch(TBankDescriptor &desc);
void        InitDescriptors();

 ClassDef(TTreeEvio,1)

};
#endif
