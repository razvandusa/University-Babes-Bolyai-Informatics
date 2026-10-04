## 1. Problema N+1 queries
Tabela cu departamente are 10 înregistrări (înregistrări părinte).
- 1 query este pentru extragerea tuturor departamentelor
- 10 query-uri (câte 1 query pentru fiecare departament) pentru extragerea tuturor angajaților din fiecare departament.

În total, 11 query-uri.

Timp de execuție: 174 ms

Pentru a rezolva problema, am folosit eager loading. Astfel, când luam lista de departamente, automat se vor încărca și angajații din fiecare departament. În acest mod, vom avea doar 1 query.

Timp de execuție: 159 ms

## 2. Analiza performanței indexării
- **Set de date**: S-au inserat 100.000 de înregistrări în tabela employees pentru a asigura o bază de date relevantă pentru testare.


- **Procedura de benchmark**: Fiecare interogare a fost executată de 100 de ori.


- **Măsurare**: S-a calculat timpul mediu de execuție pentru a elimina variațiile cauzate de latența rețelei sau de încălzirea cache-ului (warm-up).


După aplicarea indexurilor, s-a observat o schimbare radicală în planul de execuție, trecându-se de la Sequential Scan la **Index Scan** sau **Bitmap Heap Scan**.


Tabelul de Comparație a Performanței:

| Interogare          | Fără index (ms) | Cu index (ms) | Îmbunătățire |
|---------------------|-----------------|---------------|--------------|
| Căutare email       | 4.36            | 0.51          | 8.54         |
| Căutare departament | 13.95           | 9.96          | 1.40         |
| Interval salariu    | 59.03           | 41.60         | 1.41         |
| Multi-coloană       | 11.27           | 5.93          | 1.90         |

## 3. Implementare paginare
### **A. Offset pagination**

Aceasta este metoda tradițională, implementată în fereastra principală a aplicației (cu butoane „Next/Previous”).

- **Implementare SQL**: S-au folosit clauzele LIMIT și OFFSET (via setFirstResult și setMaxResults în JPA).

- **Comportament**: Motorul bazei de date trebuie să numere și să ignore toate rândurile de la început până la offset-ul specificat.

Observații EXPLAIN ANALYZE:

- Pentru prima pagină (Offset 0), timpul este aproape instantaneu (5 ms).

- Pentru ultima pagină, s-a observat o degradare a performanței (20 ms). Chiar dacă se returnează doar 20 de rânduri, baza de date face un Sequential Scan sau parcurge indexul pentru a sări peste primele 99000 de intrări.

### **B. Keyset pagination**

- **Implementare SQL**: În loc de offset, am folosit ultima valoare a cheii primare:
```sql
WHERE id > :lastId ORDER BY id ASC LIMIT 20
```

- **Comportament**: Baza de date nu mai numără rândurile anterioare. Aceasta caută direct în indexul ID-ului punctul de plecare și returnează următoarele 20 de rânduri.

Observații EXPLAIN ANALYZE:

- Planul de execuție arată un Index Scan constant. Timpul de execuție rămâne identic, indiferent dacă suntem la începutul sau la finalul tabelului.

| Poziția datelor | Timp Offset (ms) | Timp Keyset (ms) | Îmbunătățire |
|-----------------|------------------|------------------|--------------|
| Început         | 4                | 4                | 1            |
| Mijloc          | 13               | 4                | 3.25         |
| Final           | 18               | 4                | 4.5          |

## 4. Implementare caching
- Tehnologie: Spring Cache cu furnizorul Caffeine.
- Strategie: Cache-Aside. Datele sunt salvate în memoria Heap sub formă de obiecte Java.
- Setări cheie:
- - maximumSize(500): Evitarea erorilor de memorie (Memory Management).
- - expireAfterWrite(5s): TTL pentru consistență temporală.
- - recordStats(): Activarea monitorizării pentru Hit/Miss rate.

**Concluzii Analitice**

- **Eficiență**: Caching-ul a redus latența cu peste 98% pentru operațiile de citire repetate.

- **Consistență**: Prin @CacheEvict, am asigurat că utilizatorul nu vede date învechite după o modificare.

- **Scalabilitate**: Reducerea numărului de interogări SQL scade încărcarea pe serverul de bază de date (CPU/IO), permițând mai mulți utilizatori simultani.
```text
=== START TEST CACHE ===
Cache MISS pentru ID: 1. Accesăm baza de date...
Timp HIT: 2 ms
Cache INVALIDAT pentru ID: 1
Cache MISS pentru ID: 1. Accesăm baza de date...
Timp după EVICT: 3 ms
Așteptăm 6 secunde pentru expirare TTL...
Cache MISS pentru ID: 1. Accesăm baza de date...
Timp după EXPIRARE TTL: 3 ms
Statistici finale: Cache Stats - Hits: 2, Misses: 3, Hit Rate: 40.00%
=== SFÂRȘIT TEST ===
```

## 5. Optimizarea Operațiilor în masă
### **A. Actualizări individuale**
Este abordarea implicită: pentru fiecare obiect modificat în Java, se trimite o comandă UPDATE separată către baza de date.

- **Simplitate**: Maximă. Nu necesită nicio configurare specială.

- **Performanță**: Foarte slabă pentru volume mari. Fiecare comandă implică un "network round-trip" (dus-întors între aplicație și DB) și overhead de tranzacție.

- **Flexibilitate**: Ridicată. Poți avea logică diferită pentru fiecare obiect în parte.

### **B. Actualizări Batch**
- **Simplitate**: Medie. În Spring Boot, trebuie activat în application.properties (ex: batch_size=50) și necesită atenție la modul în care sunt generate ID-urile.

- **Performanță**: Bună. Reduce drastic numărul de călătorii pe rețea și overhead-ul bazei de date (DB-ul procesează tot grupul odată).

- **Flexibilitate**: Medie. Toate comenzile dintr-un batch sunt, de obicei, de același tip.

### **C. Interogare Actualizare în Masă**
- **Simplitate**: Scăzută. Trebuie să scrii interogări manuale (JPQL sau SQL), iar obiectele din memoria Java (Persistence Context) nu se actualizează automat.

- **Performanță**: Maximă. Este cea mai rapidă metodă deoarece procesarea are loc direct în motorul bazei de date, fără a încărca obiectele în memoria aplicației.

- **Flexibilitate**: Scăzută. Nu poți aplica logică de business complexă la nivel de obiect Java (ex: validări per rând).


| Abordare                | Timp (ms) |
|-------------------------|-----------|
| Actualizări individuale | 1861      |
| Actualizări batch       | 2335      |
| Actualizări în masă     | 807       |


## 6. Caching-ul Prepared Statements
### Fără reutilizare vs. Cu reutilizare (caching)
| Abordare             | Timp (ms) |
|----------------------|-----------|
| Uncached             | 1422      |
| Cached               | 1232      |