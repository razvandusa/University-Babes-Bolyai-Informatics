# TCP Client-Server Applications in C

## 📌 Descriere

Se va implementa în limbajul **C** o pereche de programe **client/server** care comunică prin **socket-uri TCP/IP** pentru rezolvarea mai multor probleme de procesare a datelor.

Scopul proiectului este:
- înțelegerea comunicării prin socket-uri TCP/IP
- manipularea șirurilor și a numerelor în C
- familiarizarea cu depanarea aplicațiilor folosind `strace` și `ltrace`

---

## 🧠 Cerințe funcționale

Serverul va primi date de la client și va trimite înapoi rezultatul procesării. Se vor implementa următoarele funcționalități:

---

### 1️⃣ Suma numerelor

- **Clientul** trimite un șir de numere.
- **Serverul** returnează suma numerelor primite.

---

### 2️⃣ Număr de spații într-un șir

- **Clientul** trimite un șir de caractere.
- **Serverul** returnează numărul de caractere spațiu din șir.

---

### 3️⃣ Oglindirea unui șir

- **Clientul** trimite un șir de caractere.
- **Serverul** returnează șirul inversat (caracterele în ordine inversă).

---

### 4️⃣ Interclasarea a două șiruri ordonate

- **Clientul** trimite două șiruri de caractere ordonate.
- **Serverul** interclasează cele două șiruri și returnează șirul rezultat.

---

### 5️⃣ Divizorii unui număr

- **Clientul** trimite un număr.
- **Serverul** returnează șirul divizorilor acelui număr.

---

### 6️⃣ Pozițiile unui caracter într-un șir

- **Clientul** trimite:
  - un șir de caractere
  - un caracter

- **Serverul** returnează toate pozițiile pe care caracterul apare în șir.

---

### 7️⃣ Subșir dintr-un șir

- **Clientul** trimite:
  - un șir de caractere `s`
  - două numere `i` și `l`

- **Serverul** returnează subșirul de lungime `l` care începe la poziția `i`.

---

### 8️⃣ Numere comune între două șiruri

- **Clientul** trimite două șiruri de numere.
- **Serverul** returnează șirul numerelor comune ambelor șiruri.

---

### 9️⃣ Diferența între două șiruri de numere

- **Clientul** trimite două șiruri de numere.
- **Serverul** returnează numerele care se găsesc în primul șir, dar nu și în al doilea.

---

### 🔟 Caracterul cel mai frecvent pe poziții identice

- **Clientul** trimite două șiruri de caractere.
- **Serverul** returnează:
  - caracterul care apare de cele mai multe ori pe poziții identice în ambele șiruri
  - numărul de apariții ale acestuia

---

## 🛠️ Tehnologii utilizate

- Limbaj: **C**
- Protocol: **TCP/IP**
- API: POSIX Sockets
- Debugging și analiză:
  - `strace`
  - `ltrace`

---

## ▶️ Compilare și rulare

### Compilare

```bash
gcc server.c -o server
gcc client.c -o client
