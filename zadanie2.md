1. Napisz program, tworzący N procesów potomnych, kończących się kolejno co 5
   sekund. Proces-rodzic powinien spostrzegać ich zakończenia i wyświetlać
   stosowne komunikaty.

2. Zmodyfikuj program z poprzedniego zadania tak, aby podczas oczekiwania na
   zakończenie procesu-potomka wyświetlał co 1 sekundę znak '-'; użyj
   odpowiedniej kombinacji funkcji *sleep* oraz *waitpid*.

3. Napisz program, który zapyta użytkownika czy wyświetlić listę istniejących
   procesów, czy zawartość obecnego katalogu, a następnie wykona to, o co
   poprosił użytkownik.

4. Napisz program, który stworzy wątek, a następnie poczeka na jego zakończenie
   i skończy działanie. Zmodyfikuj ten program tak, aby nie czekał na
   zakończenie wątku.

5. Zaobserwuj cykl życia wątków przy pomocy polecenia *ps*; porównaj go z
   cyklem życia procesów.

6. W programie stwórz macierz liczb całkowitych. Oblicz sumę wszystkich liczb
   tej macierzy. W tym celu uruchom osobny wątek dla każdego wiersza, a
   na koniec dodaj do siebie otrzymane wyniki.
