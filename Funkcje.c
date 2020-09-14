#include "Funkcje.h"

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

char* wczytajWierzcholki(char* nazwaPliku)
{
	int ilosc = iloscWierzcholkow(nazwaPliku);

	FILE* plik = fopen(nazwaPliku, "r");

	if (plik == NULL)
	{
		printf("Nie znalzeiono pliku wejsciowego!");
		return NULL;
	}

	// Tworzenie napisu wyjsciowego o rozmiarze 3 * ilosc + 1 (kazdy wierzcholek to 2 znaki + przecinek + jeden znak konca napisu)

	char* wierzcholki = (char*)malloc((3 * ilosc + 1) * sizeof(char));

	// Buffer dla funkcji fgets (60 - maksymalny rozmiar pojedynczej linii)
	char str[60];

	// Indeks odpowiedzialny za poprawna konstrukcje napisu
	int indeks = 0;

	for (int i = 0; i < ilosc; i++)
	{
		char* linia = fgets(str, 60, plik);

		// Wczytujemy z pliku tylko nazwe wierzcholka, np. A1
		char* nazwaW = strtok(linia, ":");

		wierzcholki[indeks++] = nazwaW[0];
		wierzcholki[indeks++] = nazwaW[1];
		wierzcholki[indeks++] = ',';
	}

	wierzcholki[indeks] = '\0';

	fclose(plik);

	// Powinno zwrocic np. "A1,B1,C1,D1"
	return wierzcholki;
}

char* wczytajPolaczenia(char* nazwaPliku)
{
	int iloscW = iloscWierzcholkow(nazwaPliku);
	int iloscP = iloscPolaczen(nazwaPliku);

	FILE* plik = fopen(nazwaPliku, "r");

	if (plik == NULL)
	{
		printf("Nie znalzeiono pliku wejsciowego!");
		return NULL;
	}

	// Tworzenie napisu wyjsciowego o rozmiarze 13 * ilosc + 1 (2 wierzcholki * 2 znaki + 4 cyfry kosztu + 2 podkreslenia + przecinek na kazde polaczenie + jeden znak konca napisu)

	char* polaczenia = (char*)malloc((13 * iloscP + 1) * sizeof(char));

	// Indeks odpowiedzialny za poprawna konstrukcje napisu
	int indeks = 0;

	// Buffer dla funkcji fgets
	char str[60];

	for (int i = 0; i < iloscW; i++)
	{
		char* linia = fgets(str, 60, plik);

		char* tempLinia = (char*)malloc(60*sizeof(char));

		strcpy(tempLinia, linia);

		// Naglowek linii - pierwszy wierzcholek polaczony ("first")
		char* pierwszy = strtok(tempLinia, ":");

		int rozmiarLinii = strlen(linia);

		for (int j = 0; j < rozmiarLinii; j++)
		{
			if (linia[j] == ' ')
			{
				// Drugi polaczony wierzcholek - zakladamy ze zawsze max 2 znaki (np. A1)
				char drugi[3];
				drugi[0] = linia[j + 1];
				drugi[1] = linia[j + 2];
				
				// Zakldamy ze koszt to maksymalnie 4-cyfrowa liczba
				char koszt[5];

				int x = 0;

				for (int k = j + 4; k < rozmiarLinii; k++)
				{
					if (linia[k] == ';')
					{
						j = k;
						break;
					}
					else
					{
						koszt[x++] = linia[k];
					}
				}

				// Tworzenie poprawnego formatu napisu
				polaczenia[indeks++] = pierwszy[0];
				polaczenia[indeks++] = pierwszy[1];
				polaczenia[indeks++] = '_';

				polaczenia[indeks++] = drugi[0];
				polaczenia[indeks++] = drugi[1];
				polaczenia[indeks++] = '_';

				
				for (int s = 0; s < x; s++)
				{
					polaczenia[indeks++] = koszt[s];
				}

				polaczenia[indeks++] = ',';
			}
		}
	}

	fclose(plik);

	// Powinno zwrocic np. "A1_B1_1,A1_C1_2,..."
	return polaczenia;
}

void inicjalizacja(char* nazwaPliku, char* wierzcholekPoczatkowy, char* wierzcholekDocelowy)
{
	int n = iloscWierzcholkow(nazwaPliku);
	int k = iloscPolaczen(nazwaPliku);

	char* wierzcholki = wczytajWierzcholki(nazwaPliku);

	char* polaczenia = wczytajPolaczenia(nazwaPliku);

	struct wierzcholek *p, *head;
	
	p = malloc(sizeof(struct wierzcholek));
	head = NULL;

	// Odpowiedzialny za wyciaganie odpowiednich nazw z napisu wierzcholki
	int indeksNazwy = 0;

	// Inicjalizacja listy wierzcholkow

	//! Blad: head wskazuje na to samo co p (ostatni element), zamiast na pierwszy

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

		//poprawne nazwy z napisow (i polaczenia)
		char nazwaW[3];
		int i = 0;

		while (wierzcholki[indeksNazwy] != ',')
		{
			nazwaW[i++] = wierzcholki[indeksNazwy++];
		}

		nazwaW[i] = '\0';

		indeksNazwy++;

		p->nazwa = nazwaW;
		p->odwiedzony = false;
		p->poprzedni = NULL;
		p->polaczenie = NULL;
		p->nastepny = NULL;

		// Jezeli wczytywany wierzcholek jest poczatkowym, to koszt jest rowny zero; w innym przypadku, koszt jest bardzo duzy (ale bedzie potem modyfikowany przez algorytm D)
		if (strcmp(nazwaW, wierzcholekPoczatkowy) == 0)
		{
			p->koszt = 0;
		}
		else
		{
			p->koszt = 9999;
		}
		
	}

	// W tym miejscu mamy liste wierzcholkow, np. A1->B1->C1->...

	// Inicjalizacja list polaczen dla kazdego wierzcholka

	// Odpowiedzialny za wyciaganie odpowiednich nazw pierwszego i drugiego wierzcholka oraz kosztu, dla kazdego polaczenia
	int indeksPolaczenia = 0;

	for (int i = 0; i < k; i++)
	{
		p = head;

		char first[3];	// Pierwszy wierzcholek polaczony, np. A1
		char second[3];	// Drugi wierzcholek polaczony, np. B1
		char valueChar[5];	// Napis bedacy kosztem poruszenia sie z first do second
		int value;	// Koszt jako liczba

		int i = 0;

		// Wczytywanie nazw

		while (polaczenia[indeksPolaczenia] != '_')
		{
			first[i++] = polaczenia[indeksPolaczenia++];
		}

		first[i] = '\0';

		indeksPolaczenia++;
		i = 0;

		while (polaczenia[indeksPolaczenia] != '_')
		{
			second[i++] = polaczenia[indeksPolaczenia++];
		}

		second[i] = '\0';

		indeksPolaczenia++;
		i = 0;

		while (polaczenia[indeksPolaczenia] != ',')
		{
			valueChar[i++] = polaczenia[indeksPolaczenia++];
		}

		valueChar[i] = '\0';

		indeksPolaczenia++;
		value = atoi(valueChar);


		while (p != NULL)
		{
			if (strcmp(p->nazwa,first) == 0)
			{
				if (p->polaczenie == NULL)
				{
					p->polaczenie = malloc(sizeof(struct polaczenie));

					struct wierzcholek *p2 = head;

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

void dijkstra(int ileWierzcholkow, int ilePolaczen, char* wierzcholekPoczatkowy, char* wierzcholekDocelowy, char* wyjscie)
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
		if (strcmp(wPoczatkowy->nazwa,wierzcholekDocelowy) == 0)
		{
			temp = wPoczatkowy;
			lacznyKoszt = wPoczatkowy->koszt;
			break;
		}

		wPoczatkowy = wPoczatkowy->nastepny;
	}

	while (temp->poprzedni != NULL)
	{
		if (strcmp(temp->poprzedni->nazwa,wierzcholekPoczatkowy) == 0)
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

	printf("%s\n", wierzcholekPoczatkowy);
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