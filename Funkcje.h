/**
 * @file
 */
#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Struktury.h"

/** Wczytuje wierzcholki z pliku wejsciowego o podanej nazwie jako jeden napis
* @param nazwaPliku Napis zawierajacy nazwe pliku wejsciowego
* @return Napis zawierajacy wszystkie wierzcholki oddzielone przecinkami, np. A1,B1,C1,D1
*/
char* wczytajWierzcholki(char* nazwaPliku);

/** Wczytuje polaczenia z pliku wejsciowego o podanej nazwie jako jeden napis
* @param nazwaPliku Napis zawierajacy nazwe pliku wejsciowego
* @return Napis zawierajacy wszystkie polaczenia oddzielone przecinkami, np. A1_B1_1,A1_C1_2
*/
char* wczytajPolaczenia(char* nazwaPliku);

/** Zlicza ilosc wierzcholkow w pliku (tylko pierwszy element w kazdym wierszu)
* @param nazwaPliku Napis zawierajacy nazwe pliku wejsciowego
* @return Ilosc wierzcholkow w pliku wejsciowym
* @note Uznajemy, ze kazda linia zawiera opis jednego wierzcholka
*/
int iloscWierzcholkow(char* nazwaPliku);

/** Zlicza ilosc polaczen w pliku (ilosc elementow poza pierwszym w kazdym wierszu)
* @param nazwaPliku Napis zawierajacy nazwe pliku wejsciowego
* @return Ilosc polaczen w pliku wejsciowym
* @note Uznajemy, ze kazde polaczenie zakonczone jest srednikiem
*/
int iloscPolaczen(char* nazwaPliku);

/** Zwraca napis zawierajacy wszystkie nazwy wierzcholkow, ktore nie sasiaduja z danym wierzcholkiem poczatkowym
* @param wierzcholki Napis zawierajacy wierzcholki wczytane z pliku (zwrocony przez funkcje "wczytajWierzcholki")
* @param polaczenia Napis zawierajacy polaczenia wczytane z pliku (zwrocony przez funkcje "wczytajPolaczenia")
* @param wierzcholekPoczatkowy Napis zawierajacy nazwe wierzcholka poczatkowego (od ktorego zaczynamy szukac sciezki do kolejnych)
* @retun Napis zawierajacy wszystkie wierzcholki, ktore nie sasiaduja z podanym wierzcholkiem poczatkowym, oddzielone przecinkami, np. D1,E1,F1
*/
char* wierzcholkiNieSasiadujace(char* wierzcholki, char* polaczenia, char* wierzcholekPoczatkowy);

/** Zapisuje naglowek do pliku wyjsciowego (aby format byl zgodny z poleceniem)
* @param wyjscie Napis zawierajacy nazwe pliku wyjsciowego
* @param wierzcholekPoczatkowy Napis zawierajacy nazwe wierzcholka poczatkowego
* @note Funkcja zapisze do pliku napis np. "dla wierzcholka A1"
* @note Funkcja tworzy plik wyjsciowy, jesli nie istnieje
*/
void zapiszNaglowekDoPliku(char* wyjscie, char* wierzcholekPoczatkowy);

/** Wypisuje do pliku wyjsciowego o podanej nazwie sciezke oraz laczny koszt
* @param wyjscie Napis zawierajacy nazwe pliku wyjsciowego
* @param sciezka Napis zawierajacy sciezke do wierzcholka docelowego, w nastepujacym formacie: D<-W1<-W2<-...<-P
* @param lacznyKoszt Laczny koszt dla tej sciezki
*/
void zapiszSciezkeDoPliku(char* wyjscie, char* sciezka, int lacznyKoszt);

/** Inicjalizuje liste wierzcholkow nazwana i zwraca wskaznik na pierwszy jej element
* @param nazwaPliku Napis zawierajacy nazwe pliku wejsciowego
* @param wierzcholekPoczatkowy Napis zawierajacy nazwe wierzcholka poczatkowego (od ktorego zaczynamy szukac sciezki do kolejnych)
* @return Wskaznik na pierwszy element listy wierzcholkow
*/
struct wierzcholek* inicjalizacja(char* nazwaPliku, char* wierzcholekPoczatkowy);

/** Wywoluje algorytm Dijkstry (funkcja "dijkstra") dla wszystkich wierzcholkow, ktore nie sasiaduja z wierzcholkiem poczatkowym, podanym jako parametr
* @param wierzcholekPoczatkowy Wierzcholek, dla ktorego bedziemy wywolywac algorytm
* @param nieSasiaduja Napis zawierajacy wierzcholki, ktore nie sasiaduja z wierzcholkiem poczatkowym (zwrocony przez funkcje "wierzcholkiNieSasiadujace")
* @param wyjscie Napis zawierajacy nazwe pliku wyjsciowego
* @note Ta funkcja wykona algorytm Dijkstry dla wierzcholka poczatkowego oraz kazdego wierzcholka zawartego w napisie "nieSasiaduja"
*/
void wywolajDlaWszystkich(char* wierzcholekPoczatkowy, char* nieSasiaduja, char* wejscie, char* wyjscie);

/** Wykorzystujac algorytm Dijkstry wyznacza najbardziej korzystne drogi z jednego wierzcholka do drugiego
* @param head Wskaznik na pierwszy element listy wierzcholkow
* @param ileWierzcholkow Ilosc wierzcholkow, znaleziona za pomoca funkcji iloscWierzcholkow
* @param ilePolaczen Ilosc polaczen, znaleziona za pomoca funkcji iloscPolaczen
* @param wierzcholekPoczatkowy Nazwa wierzcholka, od ktorego zaczynamy sie poruszac (np. A1)
* @param wierzcholekDocelowy Nazwa wierzcholka, do ktorego chcemy sie poruszyc (np. D1)
* @param wyjscie Napis zawierajacy nazwe pliku wyjsciowego
* @note Funkcja jest wywolywana dla par wierzcholkow przez funkcje "wywolajDlaWszystkich"
* @note Funkcja zapisuje sciezke wraz z kosztem do pliku wyjsciowego
*/
void dijkstra(struct wierzcholek* head, int ileWierzcholkow, int ilePolaczen, char* wierzcholekPoczatkowy, char* wierzcholekDocelowy, char* wyjscie);

/** Zwalnia pamiec uzyta na liste wierzcholkow, listy polaczen oraz napisy
* @param head Wskaznik na pierwszy element listy, ktorej pamiec zwalniamy
* @note Funkcja zwolni rowniez pamiec zaalokowana na listy polaczen oraz napisy
*/
void zwolnijPamiecListy(struct wierzcholek* head);