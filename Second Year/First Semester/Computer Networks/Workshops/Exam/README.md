# Aplicație Chat Client-Server TCP în C

## Scop
Implementarea unei aplicații de tip chat care permite comunicarea între mai mulți clienți printr-un server TCP, cu suport pentru mesaje private, canale și mesaje globale.

## Cerințe

### Server (`server.c`)
- Server-ul trebuie să asculte pe portul **8080** (sau alt port specificat).
- Suportă până la **100 de clienți simultan**.
- Gestionarea concurenței se face folosind **thread-uri (pthread)** și protecție cu **mutex** pentru accesul la lista de clienți.
- Server-ul trebuie să gestioneze următoarele operații:
  1. **Mesaj în canalul curent** – trimite mesajul tuturor clienților din același canal.
  2. **Mesaj privat (/pm)** – trimite un mesaj unui client specific.
  3. **Schimbarea canalului (/join)** – clientul poate intra într-un canal nou, notificând toți ceilalți clienți.
  4. **Mesaj global (@everyone)** – trimite mesajul către toți clienții conectați, indiferent de canal.

- Server-ul trebuie să afișeze în consolă conectările și deconectările clienților.

### Client (`client.c`)
- Clientul se conectează la server pe **127.0.0.1:8080** (sau alt IP/port specificat).
- Clientul introduce un **username** la conectare.
- Clientul poate trimite comenzi și mesaje:
  - `/pm <user> <mesaj>` – mesaj privat către un utilizator.
  - `/join <canal>` – schimbă canalul curent.
  - `@everyone <mesaj>` – mesaj global către toți utilizatorii conectați.
  - Mesaj simplu – trimis doar în canalul curent.
- Clientul primește mesaje de la server printr-un thread separat, afișându-le în timp real.

### Funcționalități suplimentare
- Mesajele sunt afișate cu format clar:
  - `[username #canal]: mesaj` pentru mesaje în canal.
  - `[PM de la username]: mesaj` pentru mesaje private.
  - `[username către toți]: mesaj` pentru mesaje globale.
- Serverul gestionează corect deconectarea unui client și eliberează resursele.

### Tehnologii și librării folosite
- Limbaj: **C**
- Socket TCP (`<sys/socket.h>`, `<arpa/inet.h>`)
- Thread-uri cu **pthread**
- Mutex pentru protecția resurselor comune

## Instalare și rulare

1. Compilare server și client:

```bash
gcc server.c -o server -lpthread
gcc client.c -o client -lpthread
