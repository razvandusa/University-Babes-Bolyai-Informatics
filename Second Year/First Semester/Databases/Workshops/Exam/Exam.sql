CREATE DATABASE Brutarie
GO
USE Brutarie

CREATE TABLE Faina (
    id_faina INT PRIMARY KEY IDENTITY(1,1),
    denumire VARCHAR(100) NOT NULL,
    cantitate_disponibila INT NOT NULL,
    descriere VARCHAR(100)
);

INSERT INTO Faina (denumire, cantitate_disponibila, descriere)
VALUES 
('Faina alba', 120, 'faina alba pentru paine obisnuita'),
('Faina integrala', 60, 'faina integrala pentru paine neagra'),
('Faina de secara', 45, 'faina de secara pentru paine rustica'),
('Faina de ovaz', 35, 'faina din ovaz pentru aluaturi si biscuiti'),
('Faina de porumb', 25, 'faina galbena pentru mamaliga si aluaturi speciale');

CREATE TABLE Brutarie (
    id_brutarie INT PRIMARY KEY IDENTITY(1,1),
    denumire VARCHAR(100) NOT NULL,
    descriere VARCHAR(100),
    capacitate INT NOT NULL,
    program_coacere VARCHAR(100) NOT NULL
);

INSERT INTO Brutarie (denumire, descriere, capacitate, program_coacere)
VALUES
('Brutarie Central', 'brutarie in centru oras', 200, '08:00-16:00'),
('Brutarie Nord', 'brutarie zona nord', 150, '07:00-15:00'),
('Brutarie Sud', 'brutarie zona sud', 180, '06:00-14:00'),
('Brutarie Vest', 'brutarie zona vest', 120, '09:00-17:00'),
('Brutarie Est', 'brutarie zona est', 100, '08:00-16:00');

CREATE TABLE Copil (
    id_copil INT PRIMARY KEY IDENTITY(1,1),
    nume VARCHAR(100) NOT NULL,
    prenume VARCHAR(100) NOT NULL,
    gen CHAR(1) NOT NULL, 
    data_nastere DATE NOT NULL,
    CONSTRAINT chk_gen CHECK (gen IN ('M', 'F'))
)

INSERT INTO Copil (nume, prenume, gen, data_nastere)
VALUES
('Popescu', 'Andrei', 'M', '2014-05-12'),
('Ionescu', 'Maria', 'F', '2013-09-23'),
('Georgescu', 'Alex', 'M', '2015-01-30'),
('Dumitrescu', 'Elena', 'F', '2014-11-15'),
('Stan', 'Mihai', 'M', '2013-07-08');

CREATE TABLE Paine (
    id_paine INT PRIMARY KEY IDENTITY(1, 1),
    denumire VARCHAR(100) NOT NULL,
    gramaj INT NOT NULL,
    pret INT NOT NULL,
    id_brutarie INT NOT NULL,
    id_copil INT NOT NULL,
    CONSTRAINT fk_paine_brutarie FOREIGN KEY (id_brutarie) REFERENCES Brutarie(id_brutarie),
    CONSTRAINT fk_paine_copil FOREIGN KEY (id_copil) REFERENCES Copil(id_copil)
)

INSERT INTO Paine (denumire, gramaj, pret, id_brutarie, id_copil)
VALUES
('Paine alba mica', 500, 8, 1, 1),
('Paine integrala mare', 1000, 12, 2, 2),
('Paine secara rustica', 750, 10, 3, 3),
('Paine ovaz', 500, 9, 4, 4),
('Paine porumb', 600, 11, 5, 5);

/*
O paine este facuta din mai multe tipuri de faina, si o faina
este folosita la mai multe tipuri de paine, folosim un tabel
intermediar PaineFaina pentru a creea o relatie many-to-many
*/
CREATE TABLE PaineFaina (
    id_paine INT NOT NULL,
    id_faina INT NOT NULL,
    cantitate_utilizata INT NOT NULL,
    gluten BIT NOT NULL,
    data_expirare DATE NOT NULL,
    CONSTRAINT pk_painefaina PRIMARY KEY (id_paine, id_faina),
    CONSTRAINT fk_painefaina_paine FOREIGN KEY (id_paine) REFERENCES Paine(id_paine),
    CONSTRAINT fk_painefaina_faina FOREIGN KEY (id_faina) REFERENCES Faina(id_faina)
);

/*
Procedura stocata care primeste o paine, o faina, cantitatea utilizata, 
proprietatea de a avea sau nu gluten, data de expirare si adauga faina
painii. Daca deja exista, se actualizeaza cantitatea utilizata,
proprietatea de a avea sau nu gluten si data de expirare.
*/

GO
CREATE PROCEDURE AdaugaSauUpdateazaPaineFaina
    @id_paine INT,
    @id_faina INT,
    @cantitate INT,
    @gluten BIT,
    @data_expirare DATE
AS
BEGIN
    SET NOCOUNT ON;

    -- Verific daca exista deja combinatia intre paine + fain
    IF EXISTS (SELECT 1 FROM PaineFaina
               WHERE id_paine = @id_paine AND id_faina = @id_faina)
    BEGIN
        -- Daca exista, fac update
        UPDATE PaineFaina
        SET cantitate_utilizata = @cantitate,
            gluten = @gluten,
            data_expirare = @data_expirare
        WHERE id_paine = @id_paine AND id_faina = @id_faina;
    END
    ELSE
    BEGIN
        -- Daca nu exista, fac insert
        INSERT INTO PaineFaina (id_paine, id_faina, cantitate_utilizata, gluten, data_expirare)
        VALUES (@id_paine, @id_faina, @cantitate, @gluten, @data_expirare);
    END
END;
GO

-- Add
EXEC AdaugaSauUpdateazaPaineFaina 
    @id_paine = 1, 
    @id_faina = 1, 
    @cantitate = 2, 
    @gluten = 1, 
    @data_expirare = '2026-02-10';

-- Add
EXEC AdaugaSauUpdateazaPaineFaina 
    @id_paine = 2, 
    @id_faina = 2, 
    @cantitate = 3, 
    @gluten = 1, 
    @data_expirare = '2026-02-12';

-- Add
EXEC AdaugaSauUpdateazaPaineFaina 
    @id_paine = 3, 
    @id_faina = 3, 
    @cantitate = 2, 
    @gluten = 1, 
    @data_expirare = '2026-02-15';

-- Update
EXEC AdaugaSauUpdateazaPaineFaina 
    @id_paine = 1, 
    @id_faina = 1, 
    @cantitate = 10,  -- modificam cantitatea
    @gluten = 0,     -- modificam glutenul
    @data_expirare = '2026-03-01';

SELECT * FROM PaineFaina

-- Add
EXEC AdaugaSauUpdateazaPaineFaina 
    @id_paine = 4, 
    @id_faina = 4, 
    @cantitate = 1, 
    @gluten = 0, 
    @data_expirare = '2026-02-15';

-- Add
EXEC AdaugaSauUpdateazaPaineFaina 
    @id_paine = 4, 
    @id_faina = 3, 
    @cantitate = 4, 
    @gluten = 0, 
    @data_expirare = '2026-02-15';

SELECT * FROM PaineFaina

/*
Functia afiseaza denumirea painilor care au aceeasi data de expirare,
dar utilizeaza in compozitie faina de diferite tipuri
*/
GO
CREATE FUNCTION PaineAceeasiDataExpirareFainaDenumireDiferita()
RETURNS TABLE
AS
RETURN
(
    /* 
    Folosim DISTINCT ca sa evitam duplicatele daca o paine apare de mai multe ori din cauza mai multor
    tipuri de faina
    */
    /*
    Legam fiecare paine din tabelul Paine cu fiecare paine din tabelul PaineFaina pe baza id-urilor 
    ca sa putem accesa informatii de care avem nevoie precum data expirarii
    */
    SELECT DISTINCT p1.id_paine, p1.denumire, pf1.data_expirare
    FROM PaineFaina pf1
    INNER JOIN Paine p1 ON pf1.id_paine = p1.id_paine
    WHERE EXISTS (
        SELECT 1
        /*
        Legam din nou fiecare paine din tabelul Paine cu fiecare paine din tabelul PaineFaina pe baza
        id-urilor ca sa putem accesa informatii de care avem nevoie precum data expirarii
        */
        FROM PaineFaina pf2
        INNER JOIN Paine p2 ON pf2.id_paine = p2.id_paine
        /*
        Verificam daca exista cel putin o alta paine (p1.id_paine <> p2.id_paine) care sa aiba aceeasi data de expirare,
        dar sa aiba tip de faina diferit 
        */
        WHERE pf1.data_expirare = pf2.data_expirare
        AND p1.id_paine <> p2.id_paine
        AND pf1.id_faina <> pf2.id_faina
    )
);
GO

SELECT *
FROM PaineAceeasiDataExpirareFainaDenumireDiferita()