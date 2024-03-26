1. Napisz program, który po wczytaniu dowolnych danych od użytkownika stworzy
   wątek, który będzie wykonwał pętlę nieskończoną. Następnie, po kolejnym
   wczytaniu od użytkownika, niech program zakończy działanie. Zaobserwuj cykl
   życia wątków przy pomocy polecenia *ps*; porównaj go z cyklem życia
   procesów.

2. Stwórz statyczną macierz losowych liczb całkowitych. Napisz funkcję, która
   obliczy sumę wszystkich elementów tej macierzy.
   
3. Pracuj na macierzy z zadania 2. Tym razem napisz kod, który stworzy osobny
   wątek dla każdego wiersza macierzy, a następnie zsumuj wyniki uzyskane ze
   wszystkich wątków. Skorzystaj z argumentów oraz wartości zwracanych przez
   funkcję, od której wątki rozpoczynają działanie.

4. Zmodyfikuj zadanie 3 tak, aby sumy wszystkich wierszy trafiały bezpośrednio
   do pewnej statycznej zmiennej `unsigned sum`.

5. Pomiędzy odczyt zmiennej statycznej, a zapisanie nowej wartości, w każdym
   wątku dodaj losowy czas oczekiwania (`sleep()`). Sprawdź poprawność wyników.

6. Jak zmodyfikować program z zadania 5, aby działał poprawnie? Zaproponuj
   i zaimplementuj modyfikację.
