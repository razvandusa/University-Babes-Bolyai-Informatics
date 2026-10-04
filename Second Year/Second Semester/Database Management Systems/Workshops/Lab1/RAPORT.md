# Raport de comparație
## 1. Comparație cod: înainte (JDBC) vs după (ORM)

În implementarea inițială a aplicației, accesul la baza de date era realizat prin JDBC, folosind clase repository care gestionau manual conexiunile, interogările SQL și maparea rezultatelor. De exemplu, pentru entitatea Student, metoda de citire din baza de date implica utilizarea explicită a Connection, PreparedStatement și ResultSet, precum și construirea manuală a obiectelor de tip Student.

În varianta ORM (Hibernate/JPA), accesul la date a fost simplificat semnificativ. Operațiile CRUD sunt realizate prin intermediul EntityManager, iar entitățile sunt mapate direct la tabelele din baza de date folosind adnotări precum @Entity, @Table, @Id și relații precum @ManyToOne. De exemplu, în locul unei interogări SQL explicite pentru verificarea existenței unei înregistrări, se utilizează em.find(Entity.class, id) sau interogări JPQL.

```java
// Varianta inițială (JDBC)
public Boolean existsCourse(int id) {
    String sql = "SELECT EXISTS (SELECT * FROM Course WHERE id=?);";
    try (Connection conn = dbUtils.getConnection();
         PreparedStatement ps = conn.prepareStatement(sql)) {
        ps.setInt(1, id);
        ResultSet rs = ps.executeQuery();
        if (rs.next()) {
            return rs.getBoolean(1);
        }
    } catch (SQLException e) {
        System.out.println("Error checking if course exists in database: " + e.getMessage());
    }
    return false;
}
```
```java
// Varianta ORM (Hibernate/JPA)
public Boolean existsCourse(int id) {
        try (EntityManager em = emf.createEntityManager()) {
            return em.find(Course.class, id) != null;
        } catch (Exception e) {
            System.out.println("Error checking if course exists in database: " + e.getMessage());
            return false;
        }
    }
```
Pentru relația many-to-many dintre Student și Course, în JDBC era necesară gestionarea manuală a tabelului intermediar Enrollment, inclusiv scrierea de SQL pentru inserare, ștergere și căutare. În Hibernate, această logică este abstractizată, iar relațiile sunt gestionate prin obiecte și asocieri între entități.

## 2. Analiza reducerii liniilor de cod
Migrarea la ORM a dus la o reducere semnificativă a cantității de cod necesare pentru operațiile de bază:
* Eliminarea completă a gestionării manuale a conexiunilor (Connection, PreparedStatement, ResultSet)
* Reducerea codului SQL scris manual în repository-uri
* Eliminarea mapării manuale între rânduri din baza de date și obiecte Java

În JDBC, fiecare operație CRUD necesita zeci de linii de cod repetitive. În Hibernate, aceleași operații sunt reduse la câteva apeluri simple precum persist(), find() sau remove().

De asemenea, codul devine mai ușor de citit și întreținut, deoarece logica de acces la date este separată de implementarea SQL.

## 3. Rezultatele măsurătorilor de performanță și interpretarea lor
În cadrul testelor de performanță realizate, s-a comparat timpul de creare a 100 de conexiuni la baza de date în două scenarii:

**Fără connection pooling:**
- Fiecare conexiune este creată de la zero
- Timp total semnificativ mai mare
- Cost ridicat din cauza autentificării și inițializării conexiunii
- Timp mediu per conexiune ridicat (de ordinul zecilor sau sutelor de milisecunde)

**Cu HikariCP connection pooling:**
- Conexiunile sunt reutilizate din pool
- Timp total mult mai mic
- Timp mediu per conexiune foarte redus (sub câteva milisecunde în mod normal)

```console
=== WITHOUT CONNECTION POOLING ===
=== Without Pooling RESULTS ===
Total time: 1448.927445 ms
Average per connection: 14.48927445 ms

=== WITH HIKARI POOLING ===
=== With Pooling RESULTS ===
Total time: 27.390135 ms
Average per connection: 0.27390135 ms
```

Interpretarea rezultatelor arată clar că utilizarea connection pooling reduce dramatic overhead-ul de creare a conexiunilor și îmbunătățește performanța aplicației (în acest caz de 53 de ori), mai ales în scenarii cu acces frecvent la baza de date.

## 4. Avantaje și dezavantaje ale ORM observate
**Avantaje:**
- Reducerea semnificativă a codului SQL manual
- Productivitate mai mare și dezvoltare mai rapidă
- Gestionarea automată a relațiilor între entități
- Reducerea erorilor de tip SQL

**Dezavantaje:**
- Debugging mai dificil (SQL generat automat)
- Curba de învățare mai abruptă
- Posibile probleme de performanță dacă ORM-ul este folosit incorect

## 5. Provocări întâmpinate în timpul migrării
- Configurarea corectă a persistence.xml și a EntityManagerFactory
- Gestionarea dependențelor Maven/Gradle și rezolvarea incompatibilităților între versiunile Jakarta Persistence și Hibernate
- Adaptarea modelului de date de la stilul relațional (ID-uri directe) la modelul orientat pe obiecte (relații între entități)