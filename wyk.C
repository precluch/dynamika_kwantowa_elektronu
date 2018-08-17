void wyk(TString ifroP, TString ifNEx, TString par){
	TString name, tit, cnv_name="Wykresy symulacji ";
	cnv_name += par;
	ifstream fro, fnex, fpar;
	fro.open(ifroP.Data());
	fnex.open(ifNEx.Data());
	fpar.open(par.Data());
	TCanvas *cnv2 = new TCanvas("cnv2", cnv_name, 1200, 900);

	int Nn, n, K, SNEx, SroP, S;
	double omega, dtau;
	fpar >> Nn >> n >> K >> omega >> dtau >> SNEx >> SroP >> S;

	int a=S/SroP, b=S/SNEx;
	const int aa=a, bb=b, nn=Nn;
	
	double x[nn]=.0, ro[aa][nn]=.0, tau[bb]=.0, N[bb]=.0, E[bb]=.0, X[bb]=.0, NN, EE, XX, tt;
	for(int i=0; i<aa; i++){
		for(int j=0; j<nn; j++){
			x[j] = (double)j/nn;
			fro >> ro[i][j];
		}
	}

	fro.close();

	int k=-1;
	for(int i=0; i<b; i++){
		k++;
		fnex >> tau[i];
		fnex >> N[i];
		fnex >> X[i];
		fnex >> E[i];
	}
	fnex.close();

	TGraph *grN = new TGraph(k, tau, N);
	TGraph *grE = new TGraph(k, tau, E);
	TGraph *grX = new TGraph(k, tau, X);
	TGraph *grR0 = new TGraph(Nn, x, ro[0]);
	TGraph *grR50 = new TGraph(Nn, x, ro[(int)(k/2)+5]);
	TGraph *grR100 = new TGraph(Nn, x, ro[k-5]);

	cnv2->Divide(2, 2);

	cnv2->cd(1);
	grN->SetTitle("N(tau)");
	grN->SetMarkerColor(0);
	grN->SetLineColor(9);
	grN->GetXaxis()->SetTitle("tau");
	grN->GetYaxis()->SetTitle("N(tau)");
	grN->GetHistogram()->SetMaximum(1.2);
	grN->GetHistogram()->SetMinimum(0.);
	grN->Draw("AC");

	cnv2->cd(2);
	grE->SetTitle("E_avr(tau)");
	grE->SetMarkerColor(0);
	grE->SetLineColor(9);
	grE->GetXaxis()->SetTitle("tau");
	grE->GetYaxis()->SetTitle("E_avr(tau)");
	grE->GetHistogram()->SetMaximum(grE->GetHistogram()->GetMaximum()*1.02);
	grE->GetHistogram()->SetMinimum(-.5);
	grE->Draw("AC");

	cout << par << ": Emax = " << grE->GetHistogram()->GetMaximum() << endl;

	cnv2->cd(3);
	grX->SetTitle("X_avr(tau)");
	grX->SetMarkerColor(0);
	grX->SetLineColor(9);
	grX->GetXaxis()->SetTitle("tau");
	grX->GetYaxis()->SetTitle("X_avr(tau)");
	grX->GetHistogram()->SetMaximum(1.);
	grX->GetHistogram()->SetMinimum(0.);
	grX->Draw("AC");
		
	cnv2->cd(4);
	grR0->SetTitle("ro(x)");
	grR0->SetMarkerColor(0);
	grR0->GetXaxis()->SetTitle("x");
	grR0->GetYaxis()->SetTitle("ro(x)");
	grR0->GetHistogram()->SetMaximum(3.5);
	grR0->GetHistogram()->SetMinimum(0.);
	grR0->Draw("AC");

	grR50->SetMarkerColor(0);
	grR50->SetLineColor(9);
	grR50->Draw("SAME");

	grR100->SetMarkerColor(0);
	grR100->SetLineColor(2);
	grR100->Draw("SAME");

	TLegend* leg = new TLegend(0.7, 0.7, .9, .9);
	leg->AddEntry(grR0, "tau = 0%", "l");
	leg->AddEntry(grR50, "tau = 50%", "l");
	leg->AddEntry(grR100, "tau = 100%", "l");
	leg->Draw("SAME");

	par += ".gif";
	cnv2->SaveAs(par.Data());
	cnv2->SetEditable(0);
}
