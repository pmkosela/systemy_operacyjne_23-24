1. Zmodyfikuj program z zadania 3.5 tak, aby uzyskane wyniki były poprawne.
   Skorzystaj ze zmiennych typu `pthread_mutex_t`.

2. Napisz kod, w którym dwa wątki równolegle inkrementują pewną
   współdzieloną zmienną w zmiennych (losowych) odstępach czasu. Spraw, aby
   wątki te nie przeszkadzały sobie nawzajem.

3. Stwórz program złożony z dwóch wątków. Niech pierwszy z nich jedynie
   wyświetla dowolny komunikat i przechodzi w stan uśpienia, zaś drugi, co
   pewien stały okres, budzi pierwszy wątek. Użyj zmiennych warunkowych
   `pthread_cond_t`.

4. W pewnej fabryce wątek-magazynier odpowiedzialny jest za wyciąganie pewnej
   liczby części ze składowiska i wkładanie ich do zmiennej-pudła. Zajmuje mu
   to T sekund. Wątek-budowniczy zużywa K części z pudła. Jeśli w pudle zostało
   mniej niż K części, to zatrzymuje swoją pracę i prosi magazyniera o
   przyniesienie M części z magazynu. Napisz program, modelujący ten system.

5. Zaimplementuj rozwiązanie problemu producenta-konsumenta. Niech
   współdzielony zasób stanowi łańcuch znaków. Wątek-konsument powinien
   drukować string, aż do napotkania znaku `\n` oraz czyścić bufor, o ile bufor
   nie będzie pusty. Wątek-producent będzie dodawał pewien losowy napis do
   bufora i przesuwał `\n` na koniec, o ile zmieści się on w buforze.
