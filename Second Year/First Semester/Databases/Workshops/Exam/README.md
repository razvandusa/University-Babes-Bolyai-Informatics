# Proiect Baza de Date – Gestionare Brutarie

## Descriere

Acest proiect presupune proiectarea si implementarea unei baze de date in SQL Server pentru gestionarea activitatii unei brutarii.

---

## 1. Model relational

Se creeaza un model relational care contine urmatoarele entitati:

- **Brutarie** – informatii despre brutarii
- **Paine** – tipurile de paine produse
- **Faina** – tipurile de faina utilizate
- **Copil** – evidenta copiilor
- **PaineFaina** – tabel de legatura intre Paine si Faina (relatie many-to-many)

### Tabelul PaineFaina contine:

- id_paine (FK)
- id_faina (FK)
- cantitate_utilizata (INT)
- gluten (BIT)
- data_expirare (DATE)

### Cerinte suplimentare:

- definirea cheilor primare
- definirea cheilor externe
- respectarea integritatii referentiale
- fara utilizarea optiunii ON DELETE CASCADE

---

## 2. Procedura stocata

Se implementeaza procedura stocata:

AdaugaSauUpdateazaPaineFaina

### Parametri:

- @id_paine INT
- @id_faina INT
- @cantitate INT
- @gluten BIT
- @data_expirare DATE

### Comportament:

- Daca exista deja combinatia (id_paine, id_faina) in tabelul PaineFaina → se face UPDATE
- Daca nu exista → se face INSERT

Procedura trebuie sa utilizeze:
- SET NOCOUNT ON
- instructiuni IF EXISTS

---

## 3. Inserare date de test

Se insereaza cel putin:

- 5 inregistrari in Faina
- 5 inregistrari in Paine
- 5 inregistrari in Brutarie
- 5 inregistrari in Copil

Se testeaza procedura prin:
- adaugarea unor inregistrari noi
- modificarea unor inregistrari existente (suprapunere)

---

## 4. Functie tabelara

Se creeaza o functie de tip:

RETURNS TABLE

Functia trebuie sa returneze:

Denumirea painilor care au aceeasi data de expirare cu alte paini, dar utilizeaza in compozitie faina de tip diferit.

### Cerinte:

- utilizarea JOIN
- utilizarea subinterogarii (EXISTS sau echivalent)
- evitarea duplicatelor
- testarea functiei prin SELECT

---

## 5. Testare

Se realizeaza interogari pentru:

- verificarea continutului tabelului PaineFaina
- testarea procedurii stocate
- testarea functiei tabelare

---

## Tehnologie utilizata

- SQL Server
- T-SQL
