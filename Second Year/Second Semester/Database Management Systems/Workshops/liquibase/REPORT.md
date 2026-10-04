# Migrarea schemei BD și metode avansate
În aplicațiile reale, schema bazei de date evoluează constant (se adaugă coloane, se modifică tipuri de date, se creează tabele noi).
Modificarea manuală a bazei de date poate produce:
- inconsistențe între medii;
- conflicte între membri ai echipei;
- dificultăți de rollback;
- pierderea istoricului modificărilor.

În cadrul laboratorului s-a ales utilizarea Liquibase datorită:
- integrării foarte bune cu Spring Boot;
- suportului pentru rollback;
- versionării automate a modificărilor;
- posibilității de utilizare în echipe mari.

## Migrarea inițială a bazei de date
Prima migrare a avut rolul de a crea schema inițială a bazei de date.

Au fost create tabelele:
- departments
- employees

Tabelul employees conținea:
- id
- name
- email
- salary
- department_id

Au fost definite:
- chei primare
- constrângeri NOT NULL
- relații foreign key
- coloane unice

Liquibase a executat automat această migrare la pornirea aplicației și a salvat istoricul în tabela:
DATABASECHANGELOG.

## Adăugarea unei coloane noi
A fost creată o migrare pentru adăugarea coloanei:
```sql
phone VARCHAR(20)
```

S-a implementat:
- rollback pentru eliminarea coloanei;
- actualizarea entității Java;
- suport pentru valori NULL.

## Adăugarea unui tabel nou
A fost creat tabelul projects.
Acesta conține:
- id
- name
- description
- start_date
- department_id

A fost definită o relație foreign key către tabela:
departments.

Au fost adăugate:
- constrângeri NOT NULL
- relații ORM
- date inițiale de test folosind seeding

## Modificarea unei coloane
A fost modificată coloana salary din DECIMAL(10, 2) în DECIMAL(12, 2).

## Adăugarea index-urilor
Au fost create index-urile:
```sql
CREATE INDEX idx_employees_department
ON employees(department_id);
```

```sql
CREATE INDEX idx_employees_email
ON employees(email);
```

Comparație performanță:

| Interogare               | Fără index                       | Cu index                         |
|--------------------------|----------------------------------|----------------------------------|
| Căutare email            | 69 ms prima dată, apoi 0.69 ms   | 148 ms prima dată, apoi 2.23 ms  |
| Căutare după departament | 262 ms prima dată, apoi 56.24 ms | 355 ms prima dată, apoi 57.47 ms |


## Optimist locking
În aplicațiile multi-user pot apărea conflicte concurente, de exemplu 2 utilizatori modifică aceeași înregistrare simultan.

### Soluție:
- Optimistic locking

### Implementare:

Am adăugat următoarea coloană în tabela employees:
```sql
version INTEGER DEFAULT 0
```

În entitatea Employee:
```java
@Version
private Integer version;
```

Hibernate utilizează automat această coloană pentru verificarea concurenței.

### Scenariu care simulează doi utilizatori concurenți:
1. User A citește employee cu:
```text
version = 1
```

2. User B citește aceeași entitate:
```text
version = 1
```

3. User A actualizează salary și salvează.

4. Hibernate crește automat:
```text
version = 2
```

5. User B încearcă să salveze folosind:
```text
version = 1
```

6. Hibernate detectează conflictul și aruncă:
```text
ObjectOptimisticLockingFailureException
```

### Gestionarea Conflictului
Conflictul a fost tratat folosind:
- try/catch
- logging
- afișare mesaj prietenos pentru utilizator

Sistemul oferă utilizatorului următoarele opțiuni:
- reload latest data
- force update
- cancel operation

## Soft and hard delete

### Soft delete
Soft delete reprezintă o alternativă la ștergerea fizică a datelor.

În loc de:
```sql
DELETE FROM employees WHERE id = ?
```

sistemul marchează înregistrarea:
```sql
is_deleted = true
deleted_at = now()
deleted_by = ?
```

Datele rămân în baza de date și pot fi restaurate ulterior.

### Hard delete
Aceasta șterge permanent datele din baza de date.
```sql
DELETE FROM employees WHERE id = ?
```

### Hard vs. Soft delete:

| Caracteristică  | Soft Delete     | Hard Delete |
|-----------------|-----------------|-------------|
| Recuperare date | Da              | Nu          |
| Audit trail     | Da              | Nu          |
| Siguranță       | Ridicată        | Scăzută     |
| Performanță     | Ușor mai redusă | Mai bună    |
| Istoric         | Păstrat         | Pierdut     |

## Best practices
În cadrul laboratorului au fost respectate următoarele:
- fiecare modificare a schemei a fost separată în migrare proprie;
- s-au implementat rollback-uri;
- s-a utilizat versionare automată;
- au fost adăugate index-uri pentru performanță;
- conflictele concurente au fost gestionate corect;
- s-a implementat audit trail;
- s-au utilizat query-uri native doar unde a fost necesar;
- s-a implementat logging pentru debugging.

## Provocări / probleme întâmpinate
Am avut o problemă de compatibilitate între Spring Boot, Liquibase, și versiunea de Java folosită. Problema s-a rezolvat după ce am căutat versiunile compatibile și am trecut la versiunea de Java 21.