1. Napisz program, który stworzy kolejkę komunikatów z użyciem parametru
   `IPC_PRIVATE`. Następnie program powinien podzielić się na dwa procesy:
   jeden prześle liczbę naturalną przy pomocy stworzonej kolejki, a drugi
   odczyta ją i wyświetli.

2. Napisz programy klienta i serwera. Serwer powinien sumować liczby wysyłane
   przez klienta. Liczby są przesyłane jako komunikat typu `M_NUMBER`, a ostatnia
   z liczb jest wysyłana jako komunikat `M_LAST`. Po otrzymaniu tego komunikatu
   serwer odsyła wynik sumowania komunikatem typu `M_WYNIK`.
