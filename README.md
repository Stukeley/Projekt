# Projekt
Projekt PK

## Temat projektu
![temat](https://i.imgur.com/XVyT7QF.png)

## Reference
[Podobny projekt](https://github.com/ayns01/dijkstra-algorithm)

## Co działa
1. iloscWierzcholkow - zwraca poprawną ilość
2. iloscPolaczen - zwraca poprawną ilość
3. wczytajWierzcholki - wczytuje poprawnie, ale zwraca tylko ostatni element tablicy (np. "F1" zamiast całej tablicy {"A1", "B1", ...})

## Co nie działa
1. wczytajPolaczenia - Access Violation podczas modyfikacji linii z pliku (sama linia jest wczytana poprawnie); być może coś jest też nie tak połączeniem stringów w jedno
2. inicjalizacja - powinno tworzyć początkową listę wierzchołków oraz listy połączeń i zapisywać wskaźnik na pierwszy element do zmiennej Wierzcholek (w deklaracji struktury)
3. dijkstra - powinno wypisać do konsoli ścieżkę oraz łączny koszt.

## Co póki co nie jest zaimplementowane
1. zwalnianie pamięci - chcę żeby najpierw działało
2. zapisywanie do pliku - myślę, że to najmniejszy problem
3. wykorzystanie listy wierzchołków z polecenia - póki co chcę żeby działało chociaż dla 2 dowolnych wierzchołków

Addendum: myślę, że format pliku nie ma aż takiego znaczenia. Nie mam zbyt wysokich oczekiwań co do tego projektu. Załóżmy, że każdy wierzchołek grafu to osobna linia w pliku .txt, a każde połączenie kończy się średnikiem. W razie problemów zmiana samego wczytywania nie powinna być problemem.
