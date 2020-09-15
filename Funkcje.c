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

char* wierzcholkiNieSasiadujace(char* wierzcholki, char* polaczenia, char* wierzcholekPoczatkowy)
{
	char* sasiaduja = (char*)calloc(60, sizeof(char));

	// Sprawdzamy kazde polaczenie, czy jeden z polaczonych wierzcholkow to wierzcholekPoczatkowy - jesli tak, dodajemy je do "sasiaduja". Pozostale dodajemy do "nieSasiaduja"
	// Uznajemy, ze wierzcholek poczatkowy sasiaduje sam ze soba (nie ma to wplywu na algorytm, a tylko ulatwi zwracanie poprawnej wartosci)

	sasiaduja = strcat(sasiaduja, wierzcholekPoczatkowy);
	sasiaduja = strcat(sasiaduja, ",");

	int indeksPolaczen = 0;
	int i = 0;
	int j = 0;
	char W1[3];
	char W2[3];

	while (true)
	{
		// A1_B1_1,A1_C1_4,B1_C1_...,

		if (polaczenia[indeksPolaczen] == '\0')
		{
			// Koniec napisu

			break;
		}
		else if (polaczenia[indeksPolaczen] == ',')
		{
			indeksPolaczen++;
			// Nastepne polaczenie

			i = 0;
			j = 0;

			W1[0] = ' ';
			W1[1] = ' ';
			W1[2] = ' ';

			W2[0] = ' ';
			W2[1] = ' ';
			W2[2] = ' ';
		}
		else if (polaczenia[indeksPolaczen] == '_')
		{
			//! co dla kosztu?

			if (polaczenia[++indeksPolaczen] >= 48 && polaczenia[indeksPolaczen] <= 57)
			{
				// Liczba(koszt) - pomijamy i idziemy dalej
				continue;
			}

			W1[i] = '\0';

			while (polaczenia[indeksPolaczen] != '_')
			{
				W2[j++] = polaczenia[indeksPolaczen++];
			}

			W2[j] = '\0';

			if (strcmp(wierzcholekPoczatkowy, W1) == 0)
			{
				// W2 jest sasiadem
				sasiaduja = strcat(sasiaduja, W2);
				sasiaduja = strcat(sasiaduja, ",");
			}
			else if (strcmp(wierzcholekPoczatkowy, W2) == 0)
			{
				// W1 jest sasiadem
				sasiaduja = strcat(sasiaduja, W1);
				sasiaduja = strcat(sasiaduja, ",");
			}

			i = 0;
			j = 0;
		}
		else
		{
			W1[i++] = polaczenia[indeksPolaczen++];
		}
	}

	// Dla kazdego wierzcholka sprawdzamy, czy napis "sasiaduja" zawiera ten wierzcholek; jesli nie, dodajemy go do napisu "nieSasiaduja"

	// Wartosc zwracana
	char* nieSasiaduja = (char*)calloc(60, sizeof(char));

	int indeksWierzcholkow = 0;
	i = 0;

	while (true)
	{
		if (wierzcholki[indeksWierzcholkow] == '\0')
		{
			break;
		}
		else if (wierzcholki[indeksWierzcholkow] == ',')
		{
			indeksWierzcholkow++;

			W1[i] = '\0';
			i = 0;

			if (strstr(sasiaduja, W1) == NULL)
			{
				// "sasiaduja" nie zawiera W1 - czyli nie jest on sasiadem wierzcholka poczatkowego
				nieSasiaduja = strcat(nieSasiaduja, W1);
				nieSasiaduja = strcat(nieSasiaduja, ",");
			}
		}
		else
		{
			W1[i++] = wierzcholki[indeksWierzcholkow++];
		}
	}

	// Powinno zwrocic np. D1,E1,F1,
	return nieSasiaduja;
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

	polaczenia[indeks] = '\0';

	fclose(plik);

	// Powinno zwrocic np. "A1_B1_1,A1_C1_2,..."
	return polaczenia;
}

void zapiszNaglowekDoPliku(char* wyjscie, char* wierzcholekPoczatkowy)
{
	FILE* plik = fopen(wyjscie, "a");

	if (plik == NULL)
	{
		printf("Blad przy tworzeniu pliku wyjsciowego!");
		return;
	}

	fprintf(plik, "dla wierzcholka %s:\n", wierzcholekPoczatkowy);

	fclose(plik);
}

void zapiszSciezkeDoPliku(char* wyjscie, char* sciezka, int lacznyKoszt)
{
	FILE* plik = fopen(wyjscie, "a");

	if (plik == NULL)
	{
		printf("Blad przy tworzeniu pliku wyjsciowego!");
		return;
	}

	fprintf(plik, "%s : %d\n", sciezka, lacznyKoszt);

	fclose(plik);
}

struct wierzcholek* inicjalizacja(char* nazwaPliku, char* wierzcholekPoczatkowy)
{
	int n = iloscWierzcholkow(nazwaPliku);
	int k = iloscPolaczen(nazwaPliku);

	char* wierzcholki = wczytajWierzcholki(nazwaPliku);

	char* polaczenia = wczytajPolaczenia(nazwaPliku);

	struct wierzcholek *p, *head;
	
	p = (struct wierzcholek*)malloc(sizeof(struct wierzcholek));
	head = NULL;

	// Odpowiedzialny za wyciaganie odpowiednich nazw z napisu wierzcholki
	int indeksNazwy = 0;

	// Inicjalizacja listy wierzcholkow

	for (int i = 0; i < n; i++)
	{
		if (i == 0)
		{
			head = p;
		}
		else
		{
			p->nastepny = (struct wierzcholek*)malloc(sizeof(struct wierzcholek));
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

		p->nazwa = (char*)malloc(3 * sizeof(char));
		p->nazwa = strcpy(p->nazwa,&nazwaW);
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
					p->polaczenie = (struct polaczenie*)malloc(sizeof(struct polaczenie));

					struct wierzcholek *p2 = head;

					while (strcmp(second, p2->nazwa) != 0)
					{
						p2 = p2->nastepny;
					}

					p->polaczenie->wierzcholekPolaczony = p2;
					p->polaczenie->odleglosc = value;
					p->polaczenie->nastepnePolaczenie = NULL;
					break;
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

					p->polaczenie->nastepnePolaczenie = (struct polaczenie*)malloc(sizeof(struct polaczenie));
					p->polaczenie->nastepnePolaczenie->wierzcholekPolaczony = p2;
					p->polaczenie->nastepnePolaczenie->odleglosc = value;
					p->polaczenie->nastepnePolaczenie->nastepnePolaczenie = NULL;

					break;
				}
			}

			p = p->nastepny;
		}
	}

	// Przypisanie wartosci head to instancji Wierzcholek stworzonej w deklaracji struktury?
	// chyba tak nie mozna? XD
	Wierzcholek = head;

	return head;
}

void wywolajDlaWszystkich(char* wierzcholekPoczatkowy, char* nieSasiaduja, char* wejscie, char* wyjscie)
{
	// Zmienne potrzebne do wywolania funkcji "dijkstra" - takie same dla kazdego wierzcholka
	int iloscW = iloscWierzcholkow(wejscie);
	int iloscP = iloscPolaczen(wejscie);

	// Indeks odpowiedzialny za poprawne wyciaganie wierzcholkow z napisu "nieSasiaduja"
	int indeksSasiadow = 0;
	int i = 0;

	char drugiWierzcholek[3];

	// Zapisujemy naglowek do pliku (poprawny format pliku wyjsciowego)
	zapiszNaglowekDoPliku(wyjscie, wierzcholekPoczatkowy);

	while (true)
	{
		if (nieSasiaduja[indeksSasiadow] == ',')
		{
			indeksSasiadow++;
			drugiWierzcholek[i] = '\0';
			i = 0;

			// Inicjalizujemy liste za kazdym razem, poniewaz algorytm nie zadziala poprawnie dla listy ktora juz zostala zmieniona (a przekazujac wskaznik do funkcji nie tworzymy jego kopii)
			struct wierzcholek* temp = inicjalizacja(wejscie, wierzcholekPoczatkowy);

			// Wywolanie algorytmu
			dijkstra(temp, iloscW, iloscP, wierzcholekPoczatkowy, drugiWierzcholek, wyjscie);

			// Zwalniamy pamiec potrzebna na liste
			zwolnijPamiecListy(temp);
		}
		else if (nieSasiaduja[indeksSasiadow] == '\0')
		{
			// Wywolalismy dla wszystkich wierzcholkow
			break;
		}
		else
		{
			drugiWierzcholek[i++] = nieSasiaduja[indeksSasiadow++];
		}
	}
}

void dijkstra(struct wierzcholek* head, int ileWierzcholkow, int ilePolaczen, char* wierzcholekPoczatkowy, char* wierzcholekDocelowy, char* wyjscie)
{
	// Zmienna tymczasowa, ktora bedziemy poruszac sie po liscie
	struct wierzcholek* pp = head;

	// Ilosc wierzcholkow ktore lacznie odwiedzilismy
	int iloscOdwiedzonych = 0;

	while (true)
	{
		// Poczatkowo ustawiamy koszt jako bardzo wysoki (bedzie pozniej modyfikowany)
		int min = 9999;

		// Wskaznik na wierzcholek ktory ma najnizszy koszt
		struct wierzcholek* cel = NULL;
		pp = head;

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

		// Jezeli nie znalezlismy korzystniejszego wierzcholka, wracamy na poczatek listy i ustawiamy cel na pierwszy nieodwiedzony wierzcholek
		if (cel == NULL)
		{
			pp = head;

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

		// Obliczamy koszt kazdego wierzcholka ktory ma jakiekolwiek polaczenia (koszt wierzcholka + odleglosc, czyli koszt przemieszczenia sie)
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
		}

		// Zmieniamy wartosc "odwiedzony" celu
		cel->odwiedzony = true;

		iloscOdwiedzonych++;

		if (iloscOdwiedzonych == ileWierzcholkow)
		{
			// Odwiedzilismy wszystkie wierzcholki - koniec algorytmu
			break;
		}
	}

	// Odnajdujemy wierzcholek docelowy
	struct wierzcholek* wPoczatkowy = head;
	struct wierzcholek* temp = NULL;

	// Laczny koszt aby poruszyc sie do wierzcholka docelowego
	int lacznyKoszt = 0;

	// Sciezka do wierzcholka docelowego - poczatkowo pusta (zakladamy maksymalny rozmiar 60)
	// Format: D<-W1<-W2<-...<-P
	char* sciezka = (char*)calloc(60, sizeof(char));

	while (wPoczatkowy != NULL)
	{
		if (strcmp(wPoczatkowy->nazwa, wierzcholekDocelowy) == 0)
		{
			// Znalezlismy wierzcholek docelowy, jego koszt jest lacznym kosztem
			temp = wPoczatkowy;
			lacznyKoszt = wPoczatkowy->koszt;
			break;
		}

		wPoczatkowy = wPoczatkowy->nastepny;
	}

	// Zapisujemy sciezke korzystajac z poprzednich wierzcholkow, w stosunku do znalezionego wyzej wierzcholka docelowego
	while (temp != NULL)
	{
		if (strcmp(temp->nazwa, wierzcholekPoczatkowy) == 0)
		{
			break;
		}

		strcat(sciezka, temp->nazwa);
		strcat(sciezka, "<-");

		temp = temp->poprzedni;
	}

	strcat(sciezka, wierzcholekPoczatkowy);

	printf("Sciezka: %s\n", sciezka);
	printf("Laczny koszt : %d\n", lacznyKoszt);

	// Zapisujemy sciezke i koszt do pliku (naglowek zostal zapisany wyzej)
	zapiszSciezkeDoPliku(wyjscie, sciezka, lacznyKoszt);
}

void zwolnijPamiecListy(struct wierzcholek* head)
{
	while (head != NULL)
	{
		struct wierzcholek* nextW = head->nastepny;

		while (head->polaczenie != NULL)
		{
			struct polaczenie* nextP = head->polaczenie->nastepnePolaczenie;
			free(head->polaczenie);
			head->polaczenie = nextP;
		}

		free(head->nazwa);
		free(head);

		head = nextW;
	}

	printf("Zwolniono pamiec!\n");
}