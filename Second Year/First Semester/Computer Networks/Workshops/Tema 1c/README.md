# TCP vs UDP – Aplicații Client/Server în C folosind UDP

## 📌 Descriere

Se va implementa în limbajul **C** o pereche de programe **client/server** care comunică prin **socket-uri UDP** pentru rezolvarea mai multor probleme.

⚠️ Spre deosebire de TCP:
- UDP este **connectionless**
- Nu garantează livrarea
- Nu garantează ordinea pachetelor
- Este mai rapid și mai simplu

---

## 🎯 Obiective

- Utilizarea socket-urilor UDP (`SOCK_DGRAM`)
- Trimiterea și primirea mesajelor folosind:
  - `sendto()`
  - `recvfrom()`
- Manipularea datelor binare (octeți fără semn, short-uri etc.)
- Conversii între host/network byte order (`htons`, `ntohs`, `htonl`, `ntohl`)
- Lucrul cu structuri de timp și rezolvare DNS

---

## 🧠 Cerințe funcționale

---

### 1️⃣ Suma a două numere

- **Clientul** trimite două numere.
- **Serverul** returnează suma lor.

---

### 2️⃣ Verificare număr prim

- **Clientul** trimite un număr.
- **Serverul** returnează un boolean:
  - `1` → numărul este prim
  - `0` → numărul nu este prim

---

### 3️⃣ Număr de spații într-un șir

- **Clientul** trimite un șir (maxim 100 caractere).
- **Serverul** returnează numărul caracterelor spațiu.

---

### 4️⃣ Oglindirea unui șir

- **Clientul** trimite un șir (maxim 100 caractere).
- **Serverul** returnează șirul inversat.

---

### 5️⃣ Divizorii unui număr (1 octet fără semn)

- **Clientul** trimite un număr reprezentat pe **1 octet fără semn** (`uint8_t`).
- **Serverul** returnează șirul divizorilor acelui număr.

---

### 6️⃣ Pozițiile unui caracter într-un șir

- **Clientul** trimite:
  - un șir (max 100 caractere)
  - un caracter

- **Serverul** returnează toate pozițiile unde apare caracterul.

---

### 7️⃣ Subșir dintr-un șir

- **Clientul** trimite:
  - un șir `s` (max 100 caractere)
  - două numere `i` și `l`

- **Serverul** returnează subșirul de lungime `l` care începe la poziția `i`.

---

### 8️⃣ CMMDC și CMMMC

- **Clientul** trimite două numere reprezentate pe **2 octeți fără semn** (`uint16_t`).
- **Serverul** returnează:
  - CMMDC
  - CMMMC

⚠️ Se vor folosi conversii `htons()` și `ntohs()`.

---

### 9️⃣ Data și ora curentă

- **Clientul** trimite o cerere.
- **Serverul** returnează un `int` reprezentând:
  - numărul de secunde trecute de la **1 ianuarie 1970** (Epoch time).

- **Clientul** va converti și afișa data folosind:
  - `localtime()`
  - `strftime()`

---

### 🔟 Rezolvare nume calculator în adresă IP

- **Clientul** trimite un nume de calculator (max 100 caractere).
- **Serverul** returnează:
  - un număr pe 4 octeți fără semn (`uint32_t`) reprezentând adresa IP
  - sau un cod de eroare

- **Clientul** afișează:
  - adresa IP în format zecimal cu punct (`192.168.1.1`)
  - sau mesaj de eroare dacă rezolvarea eșuează

🔧 Se poate folosi:
- `gethostbyname()` sau `getaddrinfo()`

---

## 🛠️ Structură generală UDP

### Server

1. `socket(AF_INET, SOCK_DGRAM, 0)`
2. `bind()`
3. Buclă infinită:
   - `recvfrom()`
   - procesare
   - `sendto()`

### Client

1. `socket(AF_INET, SOCK_DGRAM, 0)`
2. `sendto()`
3. `recvfrom()`
4. `close()`

---

## ▶️ Compilare

```bash
gcc server.c -o server
gcc client.c -o client 
