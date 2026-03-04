CREATE DATABASE ParcDeDistractii;
go
USE ParcDeDistractii;
go

CREATE TABLE Sectiuni (
    cod_s INT PRIMARY KEY,
    nume VARCHAR(100),
    descriere VARCHAR(100)
);

CREATE TABLE Atractii (
    cod_a INT PRIMARY KEY,
    nume VARCHAR(100),
    descriere VARCHAR(100),
    varsta_min INT,
    cod_s INT FOREIGN KEY REFERENCES Sectiuni(cod_s)
);

CREATE TABLE Categorii (
    cod_c INT PRIMARY KEY,
    nume VARCHAR(100)
)

CREATE TABLE Vizitatori (
    cod_v INT PRIMARY KEY,
    nume VARCHAR(100),
    email VARCHAR(100),
    cod_c INT FOREIGN KEY REFERENCES Categorii(cod_c)
)

CREATE TABLE Note (
    cod_a INT FOREIGN KEY REFERENCES Atractii(cod_a),
    cod_v INT FOREIGN KEY REFERENCES Vizitatori(cod_v),
    nota VARCHAR(100)
)

INSERT INTO Sectiuni (cod_s, nume, descriere) VALUES
(1, 'Aqua Zone', 'Zona cu tobogane si piscine tematice'),
(2, 'Adventure Park', 'Zona pentru activitati extreme'),
(3, 'Kids World', 'Zona destinata copiilor mici');

INSERT INTO Categorii (cod_c, nume) VALUES
(1, 'Copii'),
(2, 'Adolescenti'),
(3, 'Adulti');

INSERT INTO Atractii (cod_a, nume, descriere, varsta_min, cod_s) VALUES
(101, 'Toboganul Uriaș', 'Tobogan de 50m inaltime, pentru aventurieri curajosi', 12, 1),
(102, 'Piscina cu Valuri', 'Piscina mare cu valuri artificiale', 6, 1),
(103, 'Tiroliana Xtreme', 'Tiroliana de 200m lungime peste lac', 14, 2),
(104, 'Trenulețul Magic', 'Traseu lin pentru copii mici', 3, 3);

INSERT INTO Vizitatori (cod_v, nume, email, cod_c) VALUES
(201, 'Andrei Pop', 'andrei.pop@email.com', 2),
(202, 'Maria Ionescu', 'maria.ionescu@email.com', 3),
(203, 'Daria Muntean', 'daria.muntean@email.com', 1),
(204, 'Vlad Petrescu', 'vlad.petrescu@email.com', 3);

INSERT INTO Note (cod_a, cod_v, nota) VALUES
(101, 201, 9.5),
(101, 202, 8.0),
(103, 202, 9.0),
(102, 204, 7.5),
(103, 204, 8.5);
GO

CREATE PROCEDURE InsertSectiuneNoua @cod_s INT, @nume VARCHAR(100), @descriere VARCHAR(100)
AS
BEGIN
    INSERT INTO Sectiuni (cod_s, nume, descriere) VALUES
    (@cod_s, @nume, @descriere)
END;
GO

EXEC InsertSectiuneNoua 4, 'Disney Zone', 'Zona cu tematica Disney';

CREATE PROCEDURE ActualizeazaAdresaEmail @cod_v INT, @email VARCHAR(100)
AS
BEGIN
    UPDATE Vizitatori
    SET email = @email
    WHERE cod_v = @cod_v;
END;
GO

EXEC ActualizeazaAdresaEmail 202, 'maria.ionescu@gmail.com'

CREATE PROCEDURE GetVizitator
AS
BEGIN
    SELECT
        Vizitatori.nume,
        Vizitatori.email,
        (
            SELECT COUNT(*)
            FROM Note
            WHERE Note.cod_v = Vizitatori.cod_v
        ) AS NumarTotalNote
    FROM Vizitatori
    WHERE (
        SELECT COUNT(*)
        FROM Note
        WHERE Note.cod_v = Vizitatori.cod_v
    ) > 0;
END;
GO

EXEC GetVizitator