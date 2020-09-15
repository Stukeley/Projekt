#include "Funkcje.h"

int main(int argc, char* argv[])
{
	// Wczytanie przelacznikow - program wymaga podania wszystkich z nich, w dowolnej kolejnosci

	char* wejscie = NULL;
	char* wyjscie = NULL;

	char* listaWierzcholkow = (char*)calloc(60, sizeof(char));

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
		else if (strcmp(temp, "-n") == 0)
		{
			// Napis zawierajacy wszystkie wierzcholki, dla ktorych wyznaczymy sciezki
			for (int j = i+1; j < argc; j++)
			{
				char* temp2 = argv[j];

				if (strncmp(temp2, "-", 1) == 0)
				{
					i = j - i;
					break;
				}

				listaWierzcholkow = strcat(listaWierzcholkow, temp2);
				listaWierzcholkow = strcat(listaWierzcholkow, ",");
			}
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

	// Odpowiedzialny za wyciaganie odpowiednich wierzcholkow wejsciowych z napisu listaWierzcholkow
	int indeksListy = 0;
	int i = 0;

	char obecnyWierzcholek[3];

	while (true)
	{
		if (listaWierzcholkow[indeksListy] == ',')
		{
			indeksListy++;
			obecnyWierzcholek[i] = '\0';
			i = 0;

			char* nieSasiaduja = wierzcholkiNieSasiadujace(wierzcholki, polaczenia, obecnyWierzcholek);

			// Wywolanie algorytmu Dijkstry
			wywolajDlaWszystkich(obecnyWierzcholek, nieSasiaduja, wejscie, wyjscie);
		}
		else if (listaWierzcholkow[indeksListy] == '\0')
		{
			break;
		}
		else
		{
			obecnyWierzcholek[i++] = listaWierzcholkow[indeksListy++];
		}
	}

	// Zwalnianie pamieci potrzebnej na napisy
	free(wierzcholki);
	free(polaczenia);
}