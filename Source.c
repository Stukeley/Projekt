#include "Funkcje.h"

int main(int argc, char* argv[])
{
	// Wczytanie przelacznikow - program wymaga podania wszystkich z nich, w dowolnej kolejnosci

	char* wejscie = NULL;
	char* wyjscie = NULL;

	//int* wierzcholki;	//?

	for (int i = 0; i < argc; i++)
	{
		char* temp = argv[i];

		if (strcmp(temp,"-i") == 0)
		{
			// Plik z opisem grafu
			wejscie = argv[++i];
		}
		else if (strcmp(temp, "-o") == 0)
		{
			// Plik wyjsciowy
			wyjscie = argv[++i];
		}
	}

	if (wejscie == NULL || wyjscie == NULL)
	{
		printf("Nie podano pliku wejsciowego i/lub wyjsciowego!");
	}

	int ileWierzcholkow = iloscWierzcholkow(wejscie);
	int ilePolaczen = iloscPolaczen(wejscie);

	char* wierzcholki = wczytajWierzcholki(wejscie);

	char* polaczenia = wczytajPolaczenia(wejscie);

	// Inicjalizacja listy
	inicjalizacja(wejscie);

	// Wykonanie algorytmu dla kazdego wierzcholka - poki co tylko dla jednej pary, dla testu
	// Poki co tez bez zapisu do pliku
	dijkstra(ileWierzcholkow, ilePolaczen, "A1", "D1", wyjscie);
}