--Creez tabelul in care salvam legaturile pe care le vom sterge--
CREATE TABLE Legaturi_Eliminare (
    ID INT IDENTITY(1,1) PRIMARY KEY,
    NumeTabelSt VARCHAR(100),
    IdSt INT,
    NumeTabelDr VARCHAR(100),
    IdDr INT
)

/*
Relatia dintre CompaniiAeriene si Avioane o vom modifica astfel:
Situatie curenta : o companie detine unul sau mai multe avioane, un avion nu poate sa fie detinut de mai multe companii
Transformare : un avion va fi detinut de mai multe companii
Procedura step-by-step 1:N -> N:1 :
1.  Adaugam coloana AvionID in CompaniiAeriene
2.  Populam AvionID cu valoarea maxima a ID-ului avionului detinut de acea companie
3.  Salvam in Legaturi_Eliminate restul avioanelor care nu au fost selectate
4.  Stergem vechea coloana CompanieID din tabela Avioane
*/

ALTER TABLE CompaniiAeriene ADD AvionID INT;
ALTER TABLE CompaniiAeriene ADD CONSTRAINT FK_CompaniiAvioane FOREIGN KEY (AvionID) REFERENCES Avioane(AvionID)

INSERT INTO Legaturi_Eliminare (NumeTabelSt, IdSt, NumeTabelDr, IdDr)
SELECT 'CompaniiAeriene', t1.CompanieID, 'Avioane', t1.AvionID
FROM Avioane t1
WHERE t1.AvionID < (
    SELECT MAX(t2.AvionID)
    FROM Avioane t2
    WHERE t2.CompanieID = t1.CompanieID
)

UPDATE C
SET C.AvionID = A.MAXAvionID
FROM CompaniiAeriene C
INNER JOIN (
    SELECT CompanieID, MAX(AvionID) as MaxAvionID
    FROM Avioane
    GROUP BY CompanieID
) A ON C.CompanieID = A.CompanieID

ALTER TABLE Avioane DROP CONSTRAINT FK__Avioane__Compani__4E88ABD4;
ALTER TABLE Avioane DROP COLUMN CompanieID;

/*
Relatia dintre Avioane si Zboruri o vom modifica astfel:
Situatie curenta : un avion face mai multe zboruri, un zbor este facut de un singur avion
Transformarea : un avion face mai multe zboruri, dar si un zbor poate fi operat de mai multe avioane
Procedura step-by-step 1:N -> M:N
1.  Aici nu pierdem date deci nu vom folosi tabela pentru Legaturi_Eliminate
2.  Trebuie creat un tabel de legatura pe care o populam cu datele din Zboruri
3.  Stergem vechea coloana AvionID din tabela Zboruri
*/

CREATE TABLE AvioaneZboruri (
    AvionID INT,
    ZborID INT,
    Primary KEY (AvionID, ZborID),
    FOREIGN KEY (AvionID) REFERENCES Avioane(AvionID),
    FOREIGN KEY (ZborID) REFERENCES Zboruri(ZborID)
)

INSERT INTO AvioaneZboruri(AvionID, ZBORID)
SELECT AvionID, ZborID
FROM Zboruri

ALTER TABLE Zboruri DROP CONSTRAINT FK__Zboruri__AvionID__5441852A;
ALTER TABLE Zboruri DROP COLUMN AvionID;

/*
Relatie dintre Pasageri si Zboruri prin PasageriZboruri o vom modifica astfel:
Situatie curenta : Un pasager poate avea mai multe zboruri si un zbor poate avea mai multi pasageri
Transformare : Un pasager sa fie asociat unui singur zbor, un zbor poate sa aiba mai multi pasageri
Procedura step-by-step M:N -> 1:N
1.  Adaugam coloana ZborID in tabela Pasageri
2.  Salvam legaturile eliminate, adica zborurile care nu au ID-ul maxim pentru un pasager
3.  Populam Pasageri cu ZborID-ul maxim
4.  Stergem tabela de legatura
*/

ALTER TABLE Pasageri ADD ZborID INT;
ALTER TABLE Pasageri ADD CONSTRAINT FK_Pasageri FOREIGN KEY (ZborID) REFERENCES Zboruri(ZborID)

INSERT INTO Legaturi_Eliminare (NumeTabelSt, IdSt, NumeTabelDr, IdDr)
SELECT 'Pasageri', PZ.PasagerID, 'Zboruri', PZ.ZborID
FROM PasageriZboruri PZ
WHERE PZ.ZborID < (
    SELECT MAX(PZ2.ZborID)
    FROM PasageriZboruri PZ2
    WHERE PZ2.PasagerID=PZ.PasagerID
)

UPDATE P
SET P.ZborID = PZ.MaxZborID
FROM Pasageri P
INNER JOIN (
    SELECT PasagerID, MAX(ZborID) as MaxZborID
    FROM PasageriZboruri
    GROUP BY PasagerID
) PZ ON P.PasagerID = PZ.PasagerID;

DROP TABLE PasageriZboruri

/*
Relatia dintre Rezervari si Bilete o vom modifica astfel:
Situatie curenta : O rezervare poate sa includa mai multe bilete
Transformare : Restrictionam astfel incat o rezervare sa aiba un singur bilet asociat
Procedura step-by-step 1:N -> 1:1
1.  Identificam si salvam biletele care vor fi detasate de rezervare
2.  Pastram Biletul cu ID-ul cel mai mare pentru fiecare rezervare
3.  Stergem legaturile (NULL) pentru biletele care nu au ID-ul cel mai mare
4.  Adaugam constrangerea de 1:1
*/

INSERT INTO Legaturi_Eliminare (NumeTabelSt, IdSt, NumeTabelDr, IdDr)
SELECT 'Rezervari', RezervareID, 'Bilete', BiletID
FROM Bilete b1
WHERE RezervareID IS NOT NULL
    AND BiletID < (
        SELECT MAX(b2.BiletID)
        FROM Bilete b2
        WHERE b2.RezervareID = b1.RezervareID
    );

UPDATE Bilete
SET RezervareID = NULL
WHERE RezervareID IS NOT NULL
    AND BiletID NOT IN (
        SELECT MAX(BiletID)
        FROM Bilete
        WHERE RezervareID IS NOT NULL
        GROUP BY RezervareID
    )

ALTER TABLE Bilete
ADD CONSTRAINT UQ_Bilete_Rezervare UNIQUE (RezervareID)