#include "psi.h"
#include <math.h>

psi::psi(){
	oNEx = "";
	oroP = "";
	ipar = "";
	N = 100;
	tau = 0.;
	dtau = .0001;
	n = 0;
	K = 1;
	omega = 1.;
	PsiR = new double [N+1];
	PsiI = new double [N+1];
	HR = new double [N+1];
	HI = new double [N+1];
}

psi::~psi(){
	delete[] PsiR;
	delete[] PsiI;
	delete[] HR;
	delete[] HI;
}

void psi::getPar(string ipar){
	ifstream fileIn(ipar.c_str());
	fileIn >> N >> n >> K >> omega >> dtau >> SNEx >> SroP >> S;
	fileIn.close();
}

void psi::init(){
	dx = (double)1/N;

	PsiR[0] = .0;
	PsiI[0] = .0;
	PsiR[N] = .0;
	PsiI[N] = .0;
	HR[0] = .0;
	HI[0] = .0;
	
	for(int i = 1; i<N; ++i){
		PsiR[i] = sqrt(2)*sin(n*M_PI*i*dx);
		PsiI[i] = .0;
		HR[i] = .0;
		HI[i] = .0;
	}
}

void psi::hami(double *H, double *Psi){
	for(int i = 1; i<(N-1); i++){
		H[i] = -.5*(Psi[i-1]+Psi[i+1]-2*Psi[i])/pow(dx,2) + K*((double)i*dx-.5)*Psi[i]*sin(omega*tau);
	}
}

void psi::calk(){
	//ofstream fileOut1("psi.dat", ios::in | ios::out | ios::app);
	//ofstream fileOut2("ham.dat", ios::in | ios::out | ios::app);

	hami(HI, PsiI);
	for(int i = 0; i<N; i++)
		PsiR[i] += HI[i]*dtau*.5;
	tau += .5*dtau;
	hami(HR, PsiR);
	for(int i = 0; i<N; i++)
		PsiI[i] -= HR[i]*dtau;
	tau += .5*dtau;
	hami(HI, PsiI);
	for(int i = 0; i<N; i++)
		PsiR[i] += HI[i]*dtau*.5;


	/*for(int i = 0; i<N; ++i)
		fileOut1 << PsiR[i] << "+ i " << PsiI[i] << "\t";
		
	for(int i = 0; i<N; ++i)
		fileOut2 << HR[i] << "+ i " << HI[i] << "\t";

	fileOut1 << endl;
	fileOut2 << endl;
	fileOut1.close();
	fileOut2.close();*/
}

void psi::NEx(string oNEx){
	ofstream fileOut(oNEx.c_str(), ios::in | ios::out | ios::app);
	Norm = .0;
	Xavr = .0;
	Eavr = .0;
	
	for(int i=0; i<N; ++i){
		Norm += pow(PsiR[i],2) + pow(PsiI[i],2);
		Xavr += dx*i*(pow(PsiR[i],2) + pow(PsiI[i],2));
		Eavr += PsiR[i]*HR[i] + PsiI[i]*HI[i];
	}
	
	Norm *= dx;
	Xavr *= dx;
	Eavr *= dx;

	fileOut << tau << "\t" << Norm << "\t" << Xavr << "\t" << Eavr << endl;
	fileOut.close();
}

void psi::roP(string oroP){
	ofstream fileOut(oroP.c_str(), ios::in | ios::out | ios::app);
	double r;
	//double ro[N];
	//for(int i=0; i<N; ++i){
		//ro[i] = pow(PsiR[i],2) + pow(PsiI[i],2);
		//fileOut << ro[i] << "\t";
	//}
	for(int i=0; i<N; ++i){
		r = pow(PsiR[i],2) + pow(PsiI[i],2);
		fileOut << r << "\t";
	}
	fileOut << endl;
	fileOut.close();
}
