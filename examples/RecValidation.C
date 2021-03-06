/**
 * Example script for reading Evio files from ROOT/CINT.
 * Author: G.Gavalian
 */
{
  /**
   * Loading shared library of evio-root package.
   */

  gSystem->Load("../lib/libEvioRoot.so");
  gStyle->SetLabelSize(0.045,"X");
  gStyle->SetLabelSize(0.045,"Y");
  gStyle->SetTitleSize(0.045,"X");
  gStyle->SetTitleSize(0.045,"Y");

  TTreeEvio  *tree = new TTreeEvio("input.evio");

  int nentries = tree->GetEntries();
  
  int icounter = 0;

  TH1F  *H1_PRES    = new TH1F("H1_PRES" ,"",100,  -0.5,  0.5);
  TH1F  *H1_TRES    = new TH1F("H1_TRES" ,"",100, -10.5, 10.5);
  TH1F  *H1_FRES    = new TH1F("H1_FRES" ,"",100, -10.5, 10.5);
  TH1F  *H1_GPIDE   = new TH1F("H1_GPIDE","", 40,   0.5,  5.5);
  TH1F  *H1_RPIDE   = new TH1F("H1_RPIDE","", 40,   0.5,  5.5);
  TH1F  *H1_RPIDO   = new TH1F("H1_RPIDO","", 40,   0.5,  5.5);
  TH1F  *H1_MASS    = new TH1F("H1_MASS" ,"",120,  -0.1,  1.3);
  TH2D  *H2_BETA_P  = new TH2D("H2_BETA_P","",200,0.5,5.5,200,0.5,1.15);

  TVector3 genPart, recPart;

  for(int eloop = 0; eloop < nentries; eloop++){

    tree.LoadTree(eloop);
    icounter++;
    if(icounter%2000==0) cout << "-------> processed " << icounter << endl;
    if(tree.GetNRows("GenPart::true")>0&&tree.GetNRows("EVENTHB::particle")>0){
      genPart.SetXYZ(
		     tree.GetValueD(0,"GenPart::true","px")/1000.0,
		     tree.GetValueD(0,"GenPart::true","py")/1000.0,
		     tree.GetValueD(0,"GenPart::true","pz")/1000.0
		     );
      recPart.SetXYZ(
		     tree.GetValueF(0,"EVENTHB::particle","px"),
		     tree.GetValueF(0,"EVENTHB::particle","py"),
		     tree.GetValueF(0,"EVENTHB::particle","pz")
		     );
      
      H1_PRES->Fill((genPart.Mag()-recPart.Mag())/genPart.Mag());
      H1_TRES->Fill((genPart.Theta()-recPart.Theta())*57.29);
      H1_FRES->Fill((genPart.Phi()-recPart.Phi())*57.29);
      
      int genPID = tree.GetValueI(0,"GenPart::true","pid");
      int recPID = tree.GetValueI(0,"EVENTHB::particle","pid");

      float beta = tree.GetValueF(0,"EVENTHB::particle","beta");
      float mass = tree.GetValueF(0,"EVENTHB::particle","mass");
      H1_MASS->Fill(mass);
      H2_BETA_P->Fill(genPart.Mag(),beta);
      //************************
      // PID 11 check
      if(genPID==11){
	H1_GPIDE->Fill(genPart.Mag());
	if(recPID==11){
	  H1_RPIDE->Fill(genPart.Mag());
	} else {
	  H1_RPIDO->Fill(genPart.Mag());
	}
      }
      //************************

    }
  }
  
  cout << " Events in the FILE = " << icounter << endl;

  /**
   * Draw histograms on ROOT canvas.
   */

  TCanvas *c1 = new TCanvas("c1","",800,700);
  c1->Divide(2,2);
  c1->cd(1);
  H1_PRES->Draw();
  c1->cd(2);
  H1_TRES->Draw();
  c1->cd(3);
  H1_FRES->Draw();
  c1->cd(4);

  H1_GPIDE->SetFillColor(kOrange+7);
  H1_RPIDE->SetFillColor(38);
  H1_RPIDO->SetFillColor(8);
  H1_GPIDE->Draw();
  H1_RPIDE->Draw("same");
  H1_RPIDO->Draw("same");

  TCanvas *c2 = new TCanvas("c2","",800,500);
  c2->Divide(2,1);
  c2->cd(1);
  H2_BETA_P->SetXTitle("P [GeV]");
  H2_BETA_P->SetYTitle("#beta");
  H2_BETA_P->Draw();
  c2->cd(2);
  H1_MASS->SetXTitle("M^{2} [GeV^{2}/c]");
  H1_MASS->Draw();
  H1_MASS->SetFillColor(11);
  gPad->SetLogy();
}
