#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <math.h>
#include <time.h>

#include "psi.h"

//TODO parametry w metodach

using namespace std;

int main(int argc,char *argv[]){
	int f=1;

	psi p;

	if (argc<3){
		cout << "Podaj plik z parametrami" << endl;
		cin >> p.ipar;
		cout << "Podaj plik na NEx" << endl;
		cin >> p.oNEx;
		cout << "Podaj plik na roP" << endl;
		cin >> p.oroP;
		f=0;
	}

	clock_t tp = clock();

	if(f){
		p.getPar(argv[1]);
		p.oNEx = argv[2];
		p.oroP = argv[3];
	}
	else
		p.getPar(p.ipar.data());

	p.init();
	
	/*for(int i=0; i<p.N; ++i)
		cout << "H[" << i << "] = " << p.HR[i] << " + i " << p.HI[i] << endl;
	for(int i=0; i<p.N; ++i)
		cout << "Psi[" << i << "] = " << p.PsiR[i] << " + i " << p.PsiI[i] << endl;*/

	for(int i=0; i<p.S; ++i){
		p.calk();
		if(i%p.SNEx==0)
			p.NEx(p.oNEx.c_str());
		if(i%p.SroP==0)
			p.roP(p.oroP.c_str());
	}
	
	clock_t tk = clock() - tp;
	//cout << "program wykonywal sie " << tk/CLOCKS_PER_SEC << " s" << endl;
	
	return tk/CLOCKS_PER_SEC;
}
