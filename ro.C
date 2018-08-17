void ro(TString ifroP, TString par){
	TString name, tit	;
	ifstream fro, fpar;
	fro.open(ifroP.Data());
	fpar.open(par.Data());
	TCanvas *cnv = new TCanvas("cnv", "Gestosc prawd. znalezienia elektronu", 640, 480);

	int Nn, n, K, SNEx, SroP, S;
	double omega, dtau;
	fpar >> Nn >> n >> K >> omega >> dtau >> SNEx >> SroP >> S;

	int a=S/SroP;
	const int aa=a, nn=Nn;
	
	double x[nn]=.0, ro[aa][nn]=.0;
	for(int i=0; i<aa; i++){
		for(int j=0; j<nn; j++){
			x[j] = (double)j/nn;
			fro >> ro[i][j];
		}
		TGraph *grR = new TGraph(100, x, ro[i]);
		tit="ro(x)           ";
		tit += i;
		tit += "/";
		tit += aa;
		grR->SetTitle(tit.Data());
		grR->SetMarkerColor(0);
		grR->SetLineColor(9);
		grR->GetXaxis()->SetTitle("x");
		grR->GetYaxis()->SetTitle("ro(x)");
		grR->GetHistogram()->SetMaximum(3.55);
		grR->GetHistogram()->SetMinimum(0.);
		grR->Draw("AC");
		gSystem->ProcessEvents();
		name = "ro";
		name += (100 + i);
		name += ".png";

		cnv->SaveAs(name.Data());
	}
	
	fro.close();
	gSystem->Exec("convert -delay 10 ro*.png Ro_np1.gif");
	gSystem->Exec("rm *.png");
	cnv->SetEditable(0);
}
