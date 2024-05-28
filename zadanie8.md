1. Napisz program, w którym dwa procesy naprzemiennie będą zajmowały pewien
   zasób; skorzystaj z semaforów IPC.

2. Zaimplementuj problem ucztujących filozofów.

3. Do czytelni przychodzą dwojakiego rodzaju użytkownicy: czytelnicy i pisarze.
   Czytelnicy mogą korzystać z czytelni wspólnie (kilku czytelników może
           korzystać z niej równocześnie), a pisarze potrzebują jej na
   wyłączność (pisarz nie może współdzielić czytelni z czytelnikiem lub innym
           pisarzem). Napisz programy dla procesu-czytelnka i procesu-pisarza,
   umożliwiające każdemu użytkownikowi skorzystanie ostatecznie z czytelni,
   przy założeniu, że czytelnia może jednocześnie pomieścić nie więcej niż N
   czytelników.
