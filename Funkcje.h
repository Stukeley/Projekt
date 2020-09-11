/**
 * @file
 */
#pragma once
#include <stdbool.h>
#include "Struktury.h"
#include <stdio.h>
#include <string.h>

/** Wczytuje wierzcholki z pliku wejsciowego o podanej nazwie jako tablica napisow
* @param nazwaPliku Napis zawierajacy nazwe pliku wejsciowego
* @return Tablica napisow, gdzie kazdy napis to nazwa jednego wierzcholka
*/
char** wczytajWierzcholki(char* nazwaPliku);

/** Wczytuje polaczenia z pliku wejsciowego o podanej nazwie jako tablica napisow
* @param nazwaPliku Napis zawierajacy nazwe pliku wejsciowego
* @return Tablica napisow, gdzie kazdy napis zawiera jedno polaczenie: W1_W2_koszt
*/
char** wczytajPolaczenia(char* nazwaPliku);

/** Zlicza ilosc wierzcholkow w pliku (tylko pierwszy element w kazdym wierszu)
* @param nazwaPliku Napis zawierajacy nazwe pliku wejsciowego
* @return Ilosc wierzcholkow w pliku wejsciowym
* @note Uznajemy, ze kazda linia zawiera opis jednego wierzcholka
*/
int iloscWierzcholkow(char* nazwaPliku);

/** Zlicza ilosc polaczen w pliku (ilosc elementow poza pierwszym w kazdym wierszu)
* @param nazwaPliku Napis zawierajacy nazwe pliku wejsciowego
* @return Ilosc polaczen w pliku wejsciowym
*/
int iloscPolaczen(char* nazwaPliku);

/** Inicjalizuje liste wierzcholkow nazwana Wierzcholek (w definicji struktury)
* @param nazwaPliku Napis zawierajacy nazwe pliku wejsciowego
* @note Po wykonaniu tej funkcji, zmienna Wierzcholek (w deklaracji struktury) powinna wskazywac na pierwszy element listy jednokierunkowej wierzcholkow
*/
void inicjalizacja(char* nazwaPliku);

/** Wykorzustujac algorytm Dijkstry wyznacza najbardziej korzystne drogi z wierzcholka do pozostalych
* @param ileWierzcholkow Ilosc wierzcholkow, znaleziona za pomoca funkcji iloscWierzcholkow
* @param ilePolaczen Ilosc polaczen, znaleziona za pomoca funkcji iloscPolaczen
* @param nazwaPoczatkowa Nazwa wierzcholka, od ktorego zaczynamy sie poruszac (np. A1)
* @param nazwaDocelowa Nazwa wierzcholka, do ktorego chcemy sie poruszyc (np. D1)
* @param wyjscie Napis zawierajacy nazwe pliku wyjsciowego
*/
void dijkstra(int ileWierzcholkow, int ilePolaczen, char* nazwaPoczatkowa, char* nazwaDocelowa, char* wyjscie);

/** Wypisuje do pliku wyjsciowego o podanej nazwie sciezke oraz laczny koszt
* @note TODO
*/
void zapiszDoPliku(char* wyjscie, char* sciezka, int dlugoscSciezki, int lacznyKoszt, char* nazwaDocelowa);

/** Zwalnia pamiec uzyta na liste wierzcholkow nazwana Wierzcholek (w definicji struktury)
* @note TODO
*/
void zwolnijPamiecListy();