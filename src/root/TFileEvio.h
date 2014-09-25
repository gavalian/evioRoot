/**
* Autogenerated Header File for TFileEvio
* \\file TFileEvio.h
* \\author G.Gavalian
* \\date 2014-09-24
*/
#ifndef __TFILEEVIO__
#define __TFILEEVIO__
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <TH1D.h>
#include <TROOT.h>
#include <TDirectory.h>
#include <TBrowser.h>
#include <TEvioFileReader.h>

using namespace std;
//! A Brief Description
/*
 * A detailed description
 */

class TFileEvio :  public TDirectory {

private:
  char  *GetNameFromArray(TArrayC &array);
public:

  /** Default Constructor */
  TFileEvio();
  TFileEvio(const char *filename);
  /** Default Destructor */
  ~TFileEvio();
  /** Copy Constructor if one is needed */
  /*TFileEvio( const TFileEvio &obj); */ 
  TBrowser  *Browse();
  /** An operator = if one is needed */
  /* const TFileEvio &operator=(const TFileEvio &obj); */

  void ReadFile(const char *filename);

  ClassDef(TFileEvio,1)

};
#endif