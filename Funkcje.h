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
* @note Uznajemy, ze kazda linia zawiera opis jednego wierzcholka (puste linie sa pomijane)
*/
int iloscWierzcholkow(char* nazwaPliku);

/** Zlicza ilosc polaczen w pliku (ilosc elementow poza pierwszym w kazdym wierszu)
* @param nazwaPliku Napis zawierajacy nazwe pliku wejsciowego
* @return Ilosc polaczen w pliku wejsciowym
* @note Uznajemy, ze kazde polaczenie zakonczone jest srednikiem
*/
int iloscPolaczen(char* nazwaPliku);

/** Zwraca napis zawierajacy wszystkie nazwy wierzcholkow oprocz wierzcholka poczatkowego, podanego jako parametr
* @param wierzcholki Napis zawierajacy wierzcholki wczytane z pliku (zwrocony przez funkcje "wczytajWierzcholki")
* @param wierzcholekPoczatkowy Napis zawierajacy nazwe wierzcholka poczatkowego (od ktorego zaczynamy szukac sciezki do kolejnych)
* @retun Napis zawierajacy wszystkie wierzcholki oprocz poczatkowego, oddzielone przecinkami, np. B1,C1,D1,E1,F1
*/
char* wierzcholkiPozostale(char* wierzcholki, char* wierzcholekPoczatkowy);

/** Zapisuje naglowek do pliku wyjsciowego (aby format byl zgodny z poleceniem)
* @param wyjscie Napis zawierajacy nazwe pliku wyjsciowego
* @param wierzcholekPoczatkowy Napis zawierajacy nazwe wierzcholka poczatkowego
* @note Funkcja zapisze do pliku napis np. "dla wierzcholka A1"
*/
void zapiszNaglowekDoPliku(char* wyjscie, char* wierzcholekPoczatkowy);

/** Wypisuje do pliku wyjsciowego o podanej nazwie sciezke oraz laczny koszt
* @param wyjscie Napis zawierajacy nazwe pliku wyjsciowego
* @param sciezka Napis zawierajacy sciezke do wierzcholka docelowego, w nastepujacym formacie: do W1 przez (W2) : koszt
* @param lacznyKoszt Laczny koszt dla tej sciezki (moze nie byc calkowity)
*/
void zapiszSciezkeDoPliku(char* wyjscie, char* sciezka, float lacznyKoszt);

/** Czysci plik wyjsciowy, tak by przy kazdym uruchomieniu programu znajdowaly sie w nim tylko obecne dane wyjsciowe
* @param wyjscie Napis zawierajacy nazwe pliku wyjsciowego
* @note Funkcja otwiera plik wyjsciowy z przelacznikiem "w", co usuwa cala jego zawartosc. Jesli plik nie istnieje, zostanie stowrzony (i rowniez bedzie pusty)
*/
void wyczyscPlikWyjsciowy(char* wyjscie);

/** Inicjalizuje liste wierzcholkow nazwana i zwraca wskaznik na pierwszy jej element
* @param nazwaPliku Napis zawierajacy nazwe pliku wejsciowego
* @param wierzcholekPoczatkowy Napis zawierajacy nazwe wierzcholka poczatkowego (od ktorego zaczynamy szukac sciezki do kolejnych)
* @return Wskaznik na pierwszy element listy wierzcholkow
*/
struct wierzcholek* inicjalizacja(char* nazwaPliku, char* wierzcholekPoczatkowy);

/** Wywoluje algorytm Dijkstry (funkcja "dijkstra") dla wszystkich wierzcholkow oprocz wierzcholka poczatkowego, podanego jako parametr
* @param wierzcholekPoczatkowy Wierzcholek, dla ktorego bedziemy wywolywac algorytm
* @param pozostale Napis zawierajacy wierzcholki pozostale (wszystkie poza poczatkowym - zwrocony przez funkcje wierzcholkiPozostale)
* @param wyjscie Napis zawierajacy nazwe pliku wyjsciowego
* @note Ta funkcja wykona algorytm Dijkstry dla wierzcholka poczatkowego oraz kazdego wierzcholka zawartego w napisie "pozostale"
* @note Funkcja zapisuje do pliku wyjsciowego wyniki dzialania algorytmu (sciezki wraz ze srednimi kosztami)
*/
void wywolajDlaWszystkich(char* wierzcholekPoczatkowy, char* pozostale, char* wejscie, char* wyjscie);

/** Wykorzystujac algorytm Dijkstry wyznacza najbardziej korzystne drogi z jednego wierzcholka do drugiego
* @param head Wskaznik na pierwszy element listy wierzcholkow
* @param ileWierzcholkow Ilosc wierzcholkow, znaleziona za pomoca funkcji iloscWierzcholkow
* @param ilePolaczen Ilosc polaczen, znaleziona za pomoca funkcji iloscPolaczen
* @param wierzcholekPoczatkowy Nazwa wierzcholka, od ktorego zaczynamy sie poruszac (np. A1)
* @param wierzcholekDocelowy Nazwa wierzcholka, do ktorego chcemy sie poruszyc (np. D1)
* @return Koszt poruszenia sie z wierzcholka poczatkowego do docelowego (np. 5)
* @note Funkcja jest wywolywana dla par wierzcholkow przez funkcje "wywolajDlaWszystkich"
*/
int dijkstra(struct wierzcholek* head, int ileWierzcholkow, int ilePolaczen, char* wierzcholekPoczatkowy, char* wierzcholekDocelowy);

/** Zwalnia pamiec uzyta na liste wierzcholkow, listy polaczen oraz napisy
* @param head Wskaznik na pierwszy element listy, ktorej pamiec zwalniamy
* @note Funkcja zwolni rowniez pamiec zaalokowana na listy polaczen oraz napisy
*/
void zwolnijPamiecListy(struct wierzcholek* head);