#pragma once

/** Lista jednokierunkowa polaczen wychodzacych z danego wierzcholka. Kazdy wierzcholek ma liste polaczen z niego wychodzacych.
*/
struct polaczenie
{
    int odleglosc;  ///< Odleglosc wierzcholka (do ktorego nalezy ta lista polaczen) od wierzcholka bedacego obecnym elementem listy
    struct wierzcholek* wierzcholekPolaczony;   ///< Wskaznik na wierzcholek, do ktorego prowadzi to polaczenie
    struct polaczenie* nastepnePolaczenie;  ///< Nastepny element listy polaczen
} *Polaczenie;

/** Struktura odpowiedzialna za wierzcholek grafu - zawiera jego nazwe, liste jednokierunkowa polaczen wychodzacych z niego oraz zmienne potrzebne przy implementacji algorytmu Dijkstry.
*/
struct wierzcholek
{
    char* nazwa;    ///< Nazwa wierzcholka, np. A1
    bool odwiedzony; ///< Czy wierzcholek byl juz odwiedzony - ta zmienna potrzebna nam jest do algorytmu Dijkstry
    int koszt;  ///< Koszt poruszenia sie do wierzcholka - ta zmienna potrzebna nam jest do algorytmu Dijkstry
    struct wierzcholek* poprzedni;  ///< Poprzedni wierzcholek
    struct wierzcholek* nastepny;   ///< Nastepny wierzcholek
    struct polaczenie* polaczenie;  ///< Lista jednokierunkowa polaczen z danego wierzcholka
} *Wierzcholek;