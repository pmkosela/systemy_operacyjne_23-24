1. Napisz program, który stworzy segment pamięci współdzielonej z użyciem
   parametru `IPC_PRIVATE`. Następnie program powinien podzielić się na dwa
   procesy: jeden zapisujący stałą do pamięci współdzielonej, a drugi
   odczytujący i wyświetlający ją.

2. Stwórz dwa programy. Pierwszy powinien w pętli nieskończonej zapisywać
   naprzemiennie dwa napisy, np. "kot" i "pies", do segmentu pamięci
   współdzielonej. Drugi program, również w pętli nieskończonej, odczytuje
   napis i w przypadku gdy to nie jest ani "kot", ani "pies" wyświetla błąd.

3. Zbadaj zachowanie poprzednich programów, drukując timestampy wraz z błędami
   oraz zmniejszając częstotliwość zamiany słów, np. co 1 sekundę.

4. Zmodyfikuj poprzednie programy tak, aby błędy się nie pojawiały. Skorzystaj
   z kolejki komunikatów: niech każdy program czeka z wykonaniem swojego
   zadania na sygnał od partnera.
