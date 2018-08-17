#ifndef PSI_H
#define PSI_H

#include <stdlib.h>
#include <fstream>
#include <iostream>

#include <math.h>

using namespace std;

class psi{
	public:
		string oNEx, oroP, ipar;
		psi();
		~psi();
		void getPar(string ipar);				//wczytuje parametry
		void init();							//inicjalizuje uklad
		void hami(double *H, double *Psi);		//oblicza hamiltonian
		void calk();							//oblicza f-cje falowa
		void NEx(string oNEx);					//oblicza i wypisuje NEx
		void roP(string oroP);					//oblicza i wypisuje roP
		int SNEx;								//czestosc zapisu NEx
		int SroP;								//czestosc zapisu roP
		int S;									//ilosc krokow
		double *PsiR;							//tablica Psi rzeczywistych
		double *PsiI;							//tablica Psi urojonych
		double *HR;								//tablica H rzeczywistego
		double *HI;								//tablica H urojonego
		int N;									//liczba binow			
	private:
		
		int n;									//numer stanu poczatkowego
		int K;									//sila pola el
		double omega;							//czestosc pola el
		double tau;								//czas
		double dtau;							//krok czasowy
		double dx;								//szerokosc binu
		double Norm;							//norma?
		double Xavr;							//srednie polozenie
		double Eavr;							//srednia energia

};

#endif /* PSI_H */
