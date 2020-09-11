#pragma once
#include <stdbool.h>
#include "Struktury.h"
#include <stdio.h>
#include <string.h>

/** Wczytuje wierzcholki z pliku wejsciowego o podanej nazwie jako tablica napisow
*/
char** wczytajWierzcholki(char* nazwaPliku);

/** Wczytuje polaczenia z pliku wejsciowego o podanej nazwie jako tablica napisow
*/
char** wczytajPolaczenia(char* nazwaPliku);

/** Zlicza ilosc wierzcholkow w pliku (tylko pierwszy element w kazdym wierszu)
*/
int iloscWierzcholkow(char* nazwaPliku);

/** Zlicza ilosc polaczen w pliku (ilosc elementow poza pierwszym w kazdym wierszu)
*/
int iloscPolaczen(char* nazwaPliku);

/** Inicjalizuje liste wierzcholkow nazwana Wierzcholek (w definicji struktury)
*/
void inicjalizacja(char* nazwaPliku);

/** Wykorzustujac algorytm Dijkstry wyznacza najbardziej korzystne drogi z wierzcholka do pozostalych
*/
void dijkstra(int ileWierzcholkow, int ilePolaczen, char* nazwaPoczatkowa, char* nazwaDocelowa, char* wyjscie);

/** Wypisuje do pliku wyjsciowego o podanej nazwie sciezke oraz laczny koszt
*/
void zapiszDoPliku(char* wyjscie, char* sciezka, int dlugoscSciezki, int lacznyKoszt, char* nazwaDocelowa);

/** Zwalnia pamiec uzyta na liste wierzcholkow nazwana Wierzcholek (w definicji struktury)
*/
void zwolnijPamiecListy();