void ener(){
	ifstream ene;
	ene.open("ene");
	
	Double_t E[50];
	Double_t o[50];

	for(int i=0; i<11; i++){
		ene >> o[i];
		ene >> E[i];
	}

	TCanvas *cnv = new TCanvas("cnv", "E(o)", 1200, 900);

	TGraph *En = new TGraph(11, o, E);

	En->SetTitle("E_{max}(#omega/#omega_{0})");
	En->SetMarkerStyle(1);
	En->SetMarkerSize(3);
	En->SetLineColor(0);
	En->GetXaxis()->SetTitle("#omega/#omega_{0}");
	En->GetYaxis()->SetTitle("E_{max}");
	En->GetHistogram()->SetMaximum(25);
	En->GetHistogram()->SetMinimum(5);
	En->Draw("ACP*");

	cnv->SaveAs("E(o).gif");
	cnv->SetEditable(0);
}
