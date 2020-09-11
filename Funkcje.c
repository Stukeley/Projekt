#include "Funkcje.h"

// to nie do konca jest poprawne - moga byc wierzcholki ktore nie maja polaczen
int iloscWierzcholkow(char* nazwaPliku)
{
	FILE* plik = fopen(nazwaPliku, "r");

	if (plik == NULL)
	{
		printf("Nie znalzeiono pliku wejsciowego!");
		return NULL;
	}

	int ilosc = 1;

	// Buffer dla funkcji getc
	char str[60];

	// Obecny znak
	char znak;

	// Kazda linia w pliku wejsciowym to jeden wierzcholek

	znak = getc(plik);

	while (znak != EOF)
	{
		if (znak == '\n')
		{
			ilosc++;
		}

		znak = getc(plik);
	}

	fclose(plik);

	return ilosc;
}

int iloscPolaczen(char* nazwaPliku)
{
	int iloscWierzch = iloscWierzcholkow(nazwaPliku);

	FILE* plik = fopen(nazwaPliku, "r");

	if (plik == NULL)
	{
		printf("Nie znalzeiono pliku wejsciowego!");
		return NULL;
	}

	int iloscPol = 0;

	// Buffer dla funkcji fgets
	char str[60];

	// Kazdy element w linii przed srednikiem (poza pierwszym - nazwa wierzcholka) to jedno polaczenie

	for (int i = 0; i < iloscWierzch; i++)
	{
		char* linia = fgets(str, 60, plik);

		for (int j = 0; j < strlen(linia); j++)
		{
			if (linia[j] == ';')
			{
				iloscPol++;
			}
		}
	}

	fclose(plik);

	return iloscPol;
}

char** wczytajWierzcholki(char* nazwaPliku)
{
	int ilosc = iloscWierzcholkow(nazwaPliku);

	FILE* plik = fopen(nazwaPliku, "r");

	if (plik == NULL)
	{
		printf("Nie znalzeiono pliku wejsciowego!");
		return NULL;
	}

	// Tworzenie tablicy wyjsciowej o rozmiarze ilosc

	char** wierzcholki = (char**)malloc(ilosc * sizeof(char*));

	// Buffer dla funkcji fgets
	char str[60];

	for (int i = 0; i < ilosc; i++)
	{
		char* linia = fgets(str, 60, plik);

		// Zakladamy ze maksymalna dlugosc nazwy to 2, np. A1
		wierzcholki[i] = (char*) malloc(3 * sizeof(char));

		// Wczytujemy z pliku tylko nazwe wierzcholka, np. A1
		wierzcholki[i] = strtok(linia, ":");
	}

	fclose(plik);

	// Powinno zwrocic np. { "A1", "B1", "C1", "D1", "E1", "F1" }
	return wierzcholki;
}

char** wczytajPolaczenia(char* nazwaPliku)
{
	int ilosc = iloscPolaczen(nazwaPliku);

	FILE* plik = fopen(nazwaPliku, "r");

	if (plik == NULL)
	{
		printf("Nie znalzeiono pliku wejsciowego!");
		return NULL;
	}

	// Tworzenie tablicy wyjsciowej o rozmiarze ilosc (kazdy indeks bedzie jednym polaczeniem)

	char** polaczenia = (char**)malloc(ilosc*sizeof(char*));

	int licznik = 0;

	// Buffer dla funkcji fgets
	char str[60];

	char* linia;

	while ((linia = fgets(str, 60, plik))!=NULL)
	{
		// Naglowek linii - pierwszy wierzcholek polaczony ("first")
		char* pierwszy = strtok(linia, ':');

		for (int i = 0; i < strlen(linia); i++)
		{
			if (linia[i] == ' ')
			{
				// Drugi polaczony wierzcholek - zakladamy ze zawsze max 2 znaki (np. A1)
				char* drugi = linia[i + 1] + linia[i + 2];

				// Zakldamy ze koszt to maksymalnie 4-cyfrowa liczba
				char* koszt[4];

				int k = 0;

				for (int j = i + 3; j < strlen(linia); j++)
				{
					if (linia[j] == ' ')
					{
						i = j;
						break;
					}
					else
					{
						koszt[k++] = linia[j];
					}
				}

				polaczenia[licznik] = (char*)malloc(11 * sizeof(char));

				// Docelowy format dla kazdego indeksu w tablicy: W1_W2_koszt

				char* polaczenie = strcat(pierwszy, "_");
				polaczenie = strcat(polaczenie, drugi);
				polaczenie = strcat(polaczenie, "_");
				polaczenie = strcat(polaczenie, koszt);

				polaczenia[licznik] = polaczenie;
			}
		}
	}

	fclose(plik);

	// Powinno zwrocic np. { "A1_B1_1", "A1_C1_2", ... }
	return polaczenia;
}

void inicjalizacja(char* nazwaPliku)
{
	int n = iloscWierzcholkow(nazwaPliku);
	int k = iloscPolaczen(nazwaPliku);

	char** wierzcholki = wczytajWierzcholki(nazwaPliku);

	char** polaczenia = wczytajPolaczenia(nazwaPliku);

	struct wierzcholek* p, *head;
	
	p = malloc(sizeof(struct wierzcholek));
	head = NULL;

	// Inicjalizacja listy wierzcholkow

	for (int i = 0; i < n; i++)
	{
		if (i == 0)
		{
			head = p;
		}
		else
		{
			p->nastepny = malloc(sizeof(struct wierzcholek));
			p = p->nastepny;
		}

		p->nazwa = wierzcholki[i];
		p->koszt = 9999;	// poczatkowo ustawiamy bardzo duza wartosc, ale pozniej bedzie ona modyfikowana
		p->odwiedzony = false;
		p->poprzedni = NULL;
		p->polaczenie = NULL;
		p->nastepny = NULL;
	}

	// Inicjalizacja list polaczen dla kazdego wierzcholka

	for (int i = 0; i < k; i++)
	{
		p = head;

		char* first = (char*)malloc(sizeof(char) * 11);
		char* second = (char*)malloc(sizeof(char) * 11);
		int* value = (int*)malloc(sizeof(int));

		// TODO: dla kazdego polaczenia w tablicy "polaczenia" (np. "A1_B1_1")
		// first: pierwszy wierzcholek, A1
		// second: drugi wierzcholek, B1
		// value: koszt, 1

		while (p != NULL)
		{
			if (strcmp(p->nazwa,first) == 0)
			{
				if (p->polaczenie == NULL)
				{
					p->polaczenie = malloc(sizeof(struct polaczenie));

					struct wierzcholek* p2 = head;

					while (strcmp(second, p2->nazwa) != 0)
					{
						p2 = p2->nastepny;
					}

					p->polaczenie->wierzcholekPolaczony = p2;
					p->polaczenie->odleglosc = value;
					p->polaczenie->nastepnePolaczenie = NULL;
				}
				else
				{
					while (p->polaczenie->nastepnePolaczenie != NULL)
					{
						p->polaczenie = p->polaczenie->nastepnePolaczenie;
					}

					struct wierzcholek* p2 = head;

					while (strcmp(second, p2->nazwa) != 0)
					{
						p2 = p2->nastepny;
					}

					p->polaczenie->nastepnePolaczenie = malloc(sizeof(struct polaczenie));
					p->polaczenie->nastepnePolaczenie->wierzcholekPolaczony = p2;
					p2->polaczenie->nastepnePolaczenie->odleglosc = value;
					p->polaczenie->nastepnePolaczenie->nastepnePolaczenie = NULL;

					break;
				}
			}

			p = p->nastepny;
		}
	}

	// Przypisanie wartosci head to instancji Wierzcholek stworzonej w deklaracji struktury?
	Wierzcholek = head;
}

void dijkstra(int ileWierzcholkow, int ilePolaczen, char* nazwaPoczatkowa, char* nazwaDocelowa, char* wyjscie)
{
	struct wierzcholek* pp = Wierzcholek;

	while (true)
	{
		int min = 9999;	// poczatkowo ustawiamy koszt jako bardzo wysoki
		int iloscOdwiedzonych = 0;	// ilosc wierzcholkow ktore lacznie odwiedzilismy

		// Wskaznik na wierzcholek ktory ma najnizszy koszt
		struct wierzcholek* cel = NULL;
		pp = Wierzcholek;

		// Sprawdzamy ktory wierzcholek ma najnizszy koszt

		while (pp != NULL)
		{
			if (pp->koszt < min && pp->odwiedzony == false)
			{
				min = pp->koszt;
				cel = pp;
			}
			pp = pp->nastepny;
		}

		if (cel == NULL)
		{
			pp = Wierzcholek;

			while (true)
			{
				if (pp->odwiedzony == false)
				{
					cel = pp;
					break;
				}
				pp = pp->nastepny;
			}
		}

		// Obliczamy koszt kazdego wierzcholka ktory ma jakiekolwiek polaczenia
		if (cel->polaczenie != NULL)
		{
			if (cel->polaczenie->wierzcholekPolaczony->koszt > cel->koszt + cel->polaczenie->odleglosc)
			{
				cel->polaczenie->wierzcholekPolaczony->koszt = cel->koszt + cel->polaczenie->odleglosc;
				cel->polaczenie->wierzcholekPolaczony->poprzedni = cel;
			}

			// Jezeli jest wiecej niz jedno polaczenie
			struct polaczenie* ppTemp = cel->polaczenie->nastepnePolaczenie;

			while (ppTemp != NULL)
			{
				if (ppTemp->wierzcholekPolaczony->koszt > cel->koszt + ppTemp->odleglosc)
				{
					ppTemp->wierzcholekPolaczony->koszt = cel->koszt + ppTemp->odleglosc;
					ppTemp->wierzcholekPolaczony->poprzedni = cel;
				}
				ppTemp = ppTemp->nastepnePolaczenie;
			}

			// Zmieniamy wartosc "odwiedzony" celu
			cel->odwiedzony = true;

			iloscOdwiedzonych++;

			if (iloscOdwiedzonych == ileWierzcholkow)
			{
				// Odwiedzilismy wszystkie wierzcholki
				break;
			}
		}
	}

	// Odnajdujemy wierzcholek docelowy
	struct wierzcholek* wPoczatkowy;
	struct wierzcholek* temp = NULL;

	// Laczny koszt aby poruszyc sie do wierzcholka docelowego
	int lacznyKoszt = 0;
	int i = 0;

	char** odwrocone = (char**)malloc((ilePolaczen+1) * sizeof(char*));
	wPoczatkowy = Wierzcholek;

	while (wPoczatkowy != NULL)
	{
		if (strcmp(wPoczatkowy->nazwa,nazwaDocelowa) == 0)
		{
			temp = wPoczatkowy;
			lacznyKoszt = wPoczatkowy->koszt;
			break;
		}

		wPoczatkowy = wPoczatkowy->nastepny;
	}

	while (temp->poprzedni != NULL)
	{
		if (strcmp(temp->poprzedni->nazwa,nazwaPoczatkowa) == 0)
		{
			break;
		}
		odwrocone[i] = temp->poprzedni->nazwa;
		temp = temp->poprzedni;
		i++;
	}

	for (int j = i - 1; j >= 0; j--)
	{
		printf("%s", odwrocone[j]);
	}

	printf("%s\n", nazwaPoczatkowa);
	printf("Laczny koszt : %d\n", lacznyKoszt);

	//zapiszDoPliku(wyjscie, odwrocone, i, lacznyKoszt, nazwaDocelowa);
}

void zapiszDoPliku(char* wyjscie, char* sciezka, int dlugoscSciezki, int lacznyKoszt, char* nazwaDocelowa)
{
	//
}

void zwolnijPamiecListy()
{
	//
}