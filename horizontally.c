/*
	Zadanie zaliczeniowe 2: Poziomka
	
	Kompilacja poleceniem:
	gcc @opcje ... poziomka_ver1.c -o poziomka_ver1 (do opcjonalnego podania: POLA, WIERSZE, KOLUMNY, WYBOR)

	Program gra jako Prawy z poziomkê.
	
	autor: Magdalena Czapiewska <mc427863@students.mimuw.edu.pl>
	data: 6 grudnia 2021

*/

#include <stdio.h>
#include <stdbool.h>

#ifndef POLA
# define POLA 5
#endif

#ifndef WIERSZE
# define WIERSZE 26
#endif

#ifndef KOLUMNY
# define KOLUMNY 26
#endif

#ifndef WYBOR
# define WYBOR 1000
#endif

typedef struct stan_gry{
	
	bool plansza[WIERSZE][KOLUMNY]; //tablica tablic, w ktorej przechowywany jest aktualny stan planszy - wartosc 0 oznacza, ze pole jest puste, a 1, ze zajete
	int wielka, mala; //zmienne, do ktorych wczytywany jest ruch Lewego, kodowany przez wielka i mala litere
	bool koniec_gry; //zmienna, w ktorej przechowywana jest informacja o trwaniu gry (wartosc 0) lub jej koncu (wartosc 1)
	int mozliwosci[WIERSZE*KOLUMNY][2]; //tablica, do ktorej zapisywane sa mozliwe ruchy Prawego
	int oplacalnosc[WIERSZE*KOLUMNY]; //tablica, w ktorej przechowywane sa informacje o ocenie planszy wg Prawego po danym ruchu
	int maksymalny; //zmienna, w ktorej jest przechowywana maksymalna wartosc z tablicy oplacalnosc
	int indeks; //zmienna, ktora informuje, ile mozliwych do wykonania w aktualnej kolejce ruchow Prawego juz zapamietano
	int n; //zmienna, ktora informuje, ile ruchow jest rownie oplacalnych dla Prawego (i najbardziej oplacalnych)
	
} stan_gry;


int ile_prawy(stan_gry gra){ //funkcja, ktora oblicza, ile przy danym stanie planszy gracz Prawy moglby postawic na raz blokow
	
	int wynik = 0;
	int suma = 0;
	int ostatni = KOLUMNY - POLA; //najwiekszy mozliwy indeks kolumny, gdzie moze znajdowac sie lewy koniec kreski rysowanej przez Prawego gracza
	for(int i = 0; i < WIERSZE; i++){
		for(int j = 0; j <= ostatni; j++){
			suma = 0;
			for(int k = j; k < (j + POLA); k++){
				suma += gra.plansza[i][k];
			}
			if(suma == 0){
				wynik++;
				j += (POLA - 1);
			}
		}
	}
	return wynik;
	
}

int ile_lewy(stan_gry gra){ //funkcja, ktora oblicza, ile przy danym stanie planszy gracz Lewy moglby postawic na raz blokow
	
	int wynik = 0;
	int suma = 0;
	int ostatni = WIERSZE - POLA; //najwiekszy mozliwy indeks wiersza, gdzie moze znajdowac sie lewy koniec kreski rysowanej przez Lewego gracza (patrzac z jego perspektywy)
	for(int i = 0; i < KOLUMNY; i++){
		for(int j = 0; j <= ostatni; j++){
			suma = 0;
			for(int k = j; k < (j + POLA); k++){
				suma += gra.plansza[k][i];
			}
			if(suma == 0){
				wynik++;
				j += (POLA - 1);
			}
		}
	}
	return wynik;
	
}

stan_gry zapisz_mozliwosc(stan_gry gra, int i, int j){ //funkcja, ktora zapamietuje ruch mozliwy do wykonania przez Prawego
	
	gra.mozliwosci[gra.indeks][0] = i;
	gra.mozliwosci[gra.indeks][1] = j;
	gra.oplacalnosc[gra.indeks] = (ile_prawy(gra) - ile_lewy(gra));
	if(gra.oplacalnosc[gra.indeks] > gra.maksymalny){
		gra.maksymalny = gra.oplacalnosc[gra.indeks];
	}
	gra.indeks++;
	
	return gra;
	
}

stan_gry znajdz_ruchy(stan_gry gra){ //funkcja, ktora znajduje ruchy, ktore moze wykonac Prawy
	
	gra.indeks = 0;
	int suma = 0;
	gra.maksymalny = (-1)*(WIERSZE/POLA)*KOLUMNY; //poczatkowa wartosc: jakby prawy nie mogl postawic kreski nigdzie, a lewy wszedzie, to taka by byla ocena planszy wg Prawego
	int ostatni = KOLUMNY - POLA; //najwiekszy mozliwy indeks kolumny, gdzie moze znajdowac sie lewy koniec kreski rysowanej przez Prawego gracza
	for(int i = 0; i < WIERSZE; i++){
		for(int j = 0; j <= ostatni; j++){
			suma = 0;
			for(int k = j; k < (j + POLA); k++){
				suma += gra.plansza[i][k];
			}
			if(suma == 0){ //jezeli Prawy moze postawic kreske rozpoczynajaca sie w gra.plansza[i][k]
				for(int k = j; k < (j + POLA); k++){
					gra.plansza[i][k] = 1; //stawiamy hipotetyczna kreske
				}
				gra = zapisz_mozliwosc(gra, i, j);
				for(int k = j; k < (j + POLA); k++){
					gra.plansza[i][k] = 0; //cofamy postawienie hipotetycznej kreski
				}	
			}
		}
	}
	return gra;
	
}

stan_gry zamien(stan_gry gra, int mniejszy_indeks, int wiekszy_indeks){

	int pom1, pom2;
	pom1 = gra.mozliwosci[mniejszy_indeks][0];
	pom2 = gra.mozliwosci[mniejszy_indeks][1];
	gra.mozliwosci[mniejszy_indeks][0] = gra.mozliwosci[wiekszy_indeks][0];
	gra.mozliwosci[mniejszy_indeks][1] = gra.mozliwosci[wiekszy_indeks][1];
	gra.mozliwosci[wiekszy_indeks][0] = pom1;
	gra.mozliwosci[wiekszy_indeks][1] = pom2;
	
	return gra;
}

stan_gry wybierz_najbardziej_oplacalne(stan_gry gra){ //funkcja, wybiera ruchy, po ktorych ocena planszy dla Prawego bedzie najwieksza
	
	gra.n = 0;
	for(int i = 0; i < gra.indeks; i++){
		if(gra.oplacalnosc[i] == gra.maksymalny){
			if(gra.n != i){
				gra = zamien(gra, gra.n, i);
			}
			(gra.n)++;
		}
	}
	return gra;	
	
}

int dokonaj_wyboru(stan_gry gra){
	
	return WYBOR%gra.n;
}

stan_gry ruch_prawego(stan_gry gra){ //funkcja, ktora wykonuje ruch Prawego
	
	gra = znajdz_ruchy(gra);
	gra = wybierz_najbardziej_oplacalne(gra);
	if(gra.n == 0){
		printf(".\n");
		gra.koniec_gry = 1;
	}
	else{
		int decyzja = dokonaj_wyboru(gra);
		for(int i = (gra.mozliwosci[decyzja][1]); i < (gra.mozliwosci[decyzja][1] + POLA); i++){
			gra.plansza[gra.mozliwosci[decyzja][0]][i] = 1;
		}
		printf("%c%c\n", (char)(gra.mozliwosci[decyzja][0] + (int)'a'), (char)(gra.mozliwosci[decyzja][1]) + (int)'A');
	}
	
	
	return gra;
}

stan_gry ruch_lewego(stan_gry gra){ //funkcja, ktora modyfikuje plansze wskutek wykonania ruchu przez Lewego (przy zalozeniu o poprawnosci danych czyli mozliwosci wykonania takiego ruchu)
	
	for(int i = gra.mala; i < (gra.mala + POLA); i++){
		gra.plansza[i][gra.wielka] = 1;
	}
	return gra;
	
}

stan_gry wyzeruj_tablice(stan_gry gra){ //funkcja, ktora umieszcza w tablicy tablic informacje, ze wszystkie pola sa puste
	
	for(int i = 0; i < WIERSZE; i++){
		for(int j =0; j < KOLUMNY; j++){
			gra.plansza[i][j] = 0;
		}
	}
	return gra;
}

int main(){
	
	stan_gry gra;
	gra = wyzeruj_tablice(gra);
	gra.koniec_gry = 0;
	gra.indeks = 0;
	gra.n = 0;
	gra.wielka = getchar();
	
	if(gra.wielka == '-'){ //gracz Lewy przekazuje pierwszy ruch Prawemu
		getchar(); //to jest wczytanie konca linii
		gra = ruch_prawego(gra);
		if(!gra.koniec_gry){
			gra.wielka = getchar(); //wczytuje pierwszy znak ruchu od gracza Lewego
			if(gra.wielka == '.'){ //gracz Lewy sie poddal
				gra.koniec_gry = 1;
			}
			else{
				gra.mala = getchar(); //wczytuje drugi znak ruchu od gracza Lewego
				getchar(); //to jest wczytanie konca linii
				gra.wielka -= (int)'A';
				gra.mala -= (int)'a';
			}
		}
	}
	else if(gra.wielka == '.'){ //gracz Lewy nie przekazal pierwszego ruchu i poddal sie w pierwszym ruchu
		gra.koniec_gry = 1;
	}
	else{
		gra.mala = getchar();
		getchar(); //to jest wczytanie konca linii
		gra.wielka -= (int)'A';
		gra.mala -= (int)'a';
	}
	
	while(!gra.koniec_gry){
		gra = ruch_lewego(gra);
		if(!gra.koniec_gry){
			gra = ruch_prawego(gra);
		}
		if(!gra.koniec_gry){
			gra.wielka = getchar();
			if(gra.wielka == '.'){ //gracz Lewy sie poddal
				gra.koniec_gry = 1;
			}
			else{
				gra.mala = getchar();
				getchar(); //to jest wczytanie konca linii
				gra.wielka -= (int)'A';
				gra.mala -= (int)'a';
			}
		}
		
	}
	
	return 0;
}
