USE GestiuneRezervariAvioane
GO

-- Constrangere pe tabela Avioane
ALTER TABLE Avioane
ADD CONSTRAINT CK_Avioane_Capacitate CHECK (Capacitate > 0);
GO

-- Constrangere pe tabela Zboruri
ALTER TABLE Zboruri
ADD CONSTRAINT CK_Zboruri_Date CHECK (DataSosire > DataPlecare);
GO

-- Constrangeri pe tabela AvioaneZboruri
ALTER TABLE AvioaneZboruri
ADD CONSTRAINT PK_AvioaneZboruri PRIMARY KEY (AvionID, ZborID);

ALTER TABLE AvioaneZboruri
ADD CONSTRAINT FK_AZ_Avion FOREIGN KEY (AvionID)
REFERENCES Avioane(AvionID);

ALTER TABLE AvioaneZboruri
ADD CONSTRAINT FK_AZ_Zbor FOREIGN KEY (ZborID)
REFERENCES Zboruri(ZborID);
GO

-- Validare pe tabela Avioane
CREATE FUNCTION dbo.ValidCapacitate(@cap INT) RETURNS INT
AS
BEGIN 
    IF @cap BETWEEN 50 AND 400 RETURN 1
    RETURN 0
END
GO

CREATE FUNCTION dbo.ExistaAvionModel(@Model VARCHAR(50)) RETURNS INT
AS
BEGIN
    IF EXISTS (SELECT 1 FROM Avioane WHERE Model = @Model) 
        RETURN 1
    RETURN 0
END
GO

-- Validare pe tabela Zboruri
CREATE FUNCTION dbo.ValidCodZbor(@cod VARCHAR(50)) RETURNS INT
AS
BEGIN
    IF @cod LIKE '[a-z][a-z]%' RETURN 1
    RETURN 0
END
GO

CREATE FUNCTION dbo.ExistaCodZbor(@cod VARCHAR(50)) RETURNS INT
AS
BEGIN
    IF EXISTS (SELECT 1 FROM Zboruri WHERE CodZbor = @cod)
        RETURN 1
    RETURN 0
END
GO

CREATE FUNCTION dbo.ExistaAeroport(@AeroID INT) RETURNS INT
AS
BEGIN
    IF EXISTS (SELECT 1 FROM Aeroporturi WHERE AeroportID = @AeroID) RETURN 1
    RETURN 0
END
GO

CREATE FUNCTION dbo.ExistaCompanie(@CompID INT) RETURNS INT
AS
BEGIN
    IF EXISTS (SELECT 1 FROM CompaniiAeriene WHERE CompanieID = @CompID) RETURN 1
    RETURN 0
END
GO

-- Validari pe tabela Avioane Zboruri
CREATE FUNCTION dbo.ExistaAvion(@id INT) RETURNS INT
AS
BEGIN
    IF EXISTS (SELECT 1 FROM Avioane WHERE AvionID=@id) RETURN 1
    RETURN 0
END
GO

CREATE FUNCTION dbo.ExistaZbor(@ZborID INT) RETURNS INT
AS
BEGIN
    IF EXISTS (SELECT 1 FROM Zboruri WHERE ZborID = @ZborID) RETURN 1
    RETURN 0
END
GO

-- Proceduri CRUD pe tabela Avioane
-- INSERT
CREATE PROCEDURE Insert_Avioane
    @Model VARCHAR(50),
    @Capacitate INT
AS
BEGIN
    SET NOCOUNT ON;

    -- Verificare capacitate
    IF dbo.ValidCapacitate(@Capacitate) = 0
    BEGIN
        PRINT 'Insert failed: Capacitate invalida. Trebuie intre 50 si 400.';
        RETURN;
    END

    -- Verificare daca modelul exista deja
    IF dbo.ExistaAvionModel(@Model) = 1
    BEGIN
        PRINT 'Insert failed: Modelul de avion deja exista.';
        RETURN;
    END

    INSERT INTO Avioane(Model, Capacitate)
    VALUES(@Model, @Capacitate);

    PRINT 'Insert reusit: Avion adaugat cu succes!';
END
GO

EXEC Insert_Avioane @Model='Avion68', @Capacitate=90;
GO

-- SELECT
CREATE PROCEDURE Select_Avioane
AS
SELECT * FROM Avioane
GO

EXEC Select_Avioane
GO

-- UPDATE
CREATE PROCEDURE Update_Avioane
    @AvionID INT,
    @Capacitate INT
AS
BEGIN
    SET NOCOUNT ON;

    -- Verificare existenta avion
    IF dbo.ExistaAvion(@AvionID) = 0
    BEGIN
        PRINT 'Update failed: Avionul cu ID-ul specificat nu exista.';
        RETURN;
    END

    -- Verificare capacitate
    IF dbo.ValidCapacitate(@Capacitate) = 0
    BEGIN
        PRINT 'Update failed: Capacitate invalida. Trebuie intre 50 si 400.';
        RETURN;
    END

    UPDATE Avioane
    SET Capacitate = @Capacitate
    WHERE AvionID = @AvionID;

    PRINT 'Update reusit: Capacitatea avionului a fost modificata cu succes!';
END
GO

EXEC Update_Avioane @AvionID=15, @Capacitate=120
SELECT * FROM Logging_Avioane
GO

-- DELETE
CREATE PROCEDURE Delete_Avioane
    @AvionID INT
AS
BEGIN
    SET NOCOUNT ON;

    -- Verificare existenta avion
    IF dbo.ExistaAvion(@AvionID) = 0
    BEGIN
        PRINT 'Delete failed: Avionul cu ID-ul specificat nu exista.';
        RETURN;
    END

    -- Stergerea legaturilor in tabelul M:N
    DELETE FROM AvioaneZboruri 
    WHERE AvionID = @AvionID;

    -- Stergerea avionului
    DELETE FROM Avioane 
    WHERE AvionID = @AvionID;

    PRINT 'Delete reusit: Avionul a fost sters cu succes!';
END
GO

EXEC Delete_Avioane @AvionID=15
SELECT * FROM Logging_Avioane
GO

-- Proceduri CRUD pe tabela Zboruri
-- Insert
CREATE PROCEDURE Insert_Zboruri
    @Cod VARCHAR(50),
    @DataP DATETIME,
    @DataS DATETIME,
    @AeroP INT,
    @AeroS INT,
    @CompID INT
AS
BEGIN
    SET NOCOUNT ON;

    -- Verificare cod zbor
    IF dbo.ValidCodZbor(@Cod) = 0
    BEGIN
        PRINT 'Insert failed: Cod zbor invalid.';
        RETURN;
    END

    -- Verificare daca codul zborului exista deja
    IF dbo.ExistaCodZbor(@Cod) = 1
    BEGIN
        PRINT 'Insert failed: Cod zbor deja exista.';
        RETURN;
    END

    -- Verificare aeroporturi
    IF dbo.ExistaAeroport(@AeroP) = 0 OR dbo.ExistaAeroport(@AeroS) = 0
    BEGIN
        PRINT 'Insert failed: Aeroport de plecare sau sosire inexistent.';
        RETURN;
    END

    -- Verificare companie
    IF dbo.ExistaCompanie(@CompID) = 0
    BEGIN
        PRINT 'Insert failed: Compania aeriana nu exista.';
        RETURN;
    END

    -- Verificare interval date
    IF @DataS <= @DataP
    BEGIN
        PRINT 'Insert failed: Data sosire trebuie sa fie mai mare decat data plecare.';
        RETURN;
    END

    INSERT INTO Zboruri(CodZbor, DataPlecare, DataSosire, AeroportPlecare, AeroportSosire, CompanieID)
    VALUES(@Cod, @DataP, @DataS, @AeroP, @AeroS, @CompID);

    PRINT 'Insert reusit: Zborul a fost adaugat cu succes!';
END
GO

-- SELECT
CREATE PROCEDURE Select_Zboruri
AS
SELECT * FROM Zboruri
GO

-- UPDATE
CREATE PROCEDURE Update_Zboruri
    @ZborID INT,
    @DataS DATETIME
AS
BEGIN
    SET NOCOUNT ON;

    -- Verificare existenta zbor
    IF dbo.ExistaZbor(@ZborID) = 0
    BEGIN
        PRINT 'Update failed: Zborul cu ID-ul specificat nu exista.';
        RETURN;
    END

    -- Verificare date
    DECLARE @DataP DATETIME;
    SELECT @DataP = DataPlecare FROM Zboruri WHERE ZborID = @ZborID;

    IF @DataS <= @DataP
    BEGIN
        PRINT 'Update failed: Data sosire trebuie sa fie mai mare decat data plecare.';
        RETURN;
    END

    UPDATE Zboruri
    SET DataSosire = @DataS
    WHERE ZborID = @ZborID;

    PRINT 'Update reusit: Data sosire a fost modificata cu succes!';
END
GO

-- DELETE
CREATE PROCEDURE Delete_Zboruri
    @ZborID INT
AS
BEGIN
    SET NOCOUNT ON;

    -- Verificare existenta zbor
    IF dbo.ExistaZbor(@ZborID) = 0
    BEGIN
        PRINT 'Delete failed: Zborul cu ID-ul specificat nu exista.';
        RETURN;
    END

    -- Stergerea legaturilor in tabela M:N
    DELETE FROM AvioaneZboruri 
    WHERE ZborID = @ZborID;

    -- Stergerea zborului
    DELETE FROM Zboruri 
    WHERE ZborID = @ZborID;

    PRINT 'Delete reusit: Zborul a fost sters cu succes!';
END
GO

-- Proceduri CRUD pe tabela AvioaneZboruri
-- Insert
CREATE PROCEDURE Insert_AvioaneZboruri
    @AvionID INT,
    @ZborID INT
AS
BEGIN
    SET NOCOUNT ON;

    -- Verificare existenta avion
    IF dbo.ExistaAvion(@AvionID) = 0
    BEGIN
        PRINT 'Insert failed: Avionul cu ID-ul specificat nu exista.';
        RETURN;
    END

    -- Verificare existenta zbor
    IF dbo.ExistaZbor(@ZborID) = 0
    BEGIN
        PRINT 'Insert failed: Zborul cu ID-ul specificat nu exista.';
        RETURN;
    END

    -- Verificare duplicat in tabela M:N
    IF EXISTS (SELECT 1 FROM AvioaneZboruri WHERE AvionID = @AvionID AND ZborID = @ZborID)
    BEGIN
        PRINT 'Insert failed: Aceasta asociere Avion-Zbor exista deja.';
        RETURN;
    END

    INSERT INTO AvioaneZboruri(AvionID, ZborID)
    VALUES(@AvionID, @ZborID);

    PRINT 'Insert reusit: Asocierea Avion-Zbor a fost adaugata cu succes!';
END
GO

CREATE PROCEDURE Select_AvioaneZboruri
AS
SELECT * FROM AvioaneZboruri
GO

CREATE PROCEDURE Update_AvioaneZboruri
AS
PRINT 'UPDATE not allowed on M:N table'
GO

CREATE PROCEDURE Delete_AvioaneZboruri
    @AvionID INT,
    @ZborID INT
AS
BEGIN
    SET NOCOUNT ON;

    -- Verificare existenta avion
    IF dbo.ExistaAvion(@AvionID) = 0
    BEGIN
        PRINT 'Delete failed: Avionul cu ID-ul specificat nu exista.';
        RETURN;
    END

    -- Verificare existenta zbor
    IF dbo.ExistaZbor(@ZborID) = 0
    BEGIN
        PRINT 'Delete failed: Zborul cu ID-ul specificat nu exista.';
        RETURN;
    END

    -- Verificare existenta asociere
    IF NOT EXISTS (SELECT 1 FROM AvioaneZboruri WHERE AvionID=@AvionID AND ZborID=@ZborID)
    BEGIN
        PRINT 'Delete failed: Asocierea Avion-Zbor nu exista.';
        RETURN;
    END

    DELETE FROM AvioaneZboruri
    WHERE AvionID=@AvionID AND ZborID=@ZborID;

    PRINT 'Delete reusit: Asocierea Avion-Zbor a fost stearsa cu succes!';
END
GO

-- Tabel de logging pentru Avioane
CREATE TABLE Logging_Avioane (
    LogID INT IDENTITY PRIMARY KEY,
    AvionID INT,
    Model VARCHAR(50),
    Capacitate INT,
    OperationType VARCHAR(10),
    ExecutionDate DATETIME,
    sLogin NVARCHAR(128)
);
GO

-- Trigger pentru Avioane
CREATE TRIGGER trg_Avioane_Update_Delete
ON Avioane
FOR UPDATE, DELETE
AS
BEGIN
    INSERT INTO Logging_Avioane
    SELECT
        AvionID,
        Model,
        Capacitate,
        CASE
            WHEN EXISTS (SELECT * FROM inserted) THEN 'UPDATE'
            ELSE 'DELETE'
        END,
        GETDATE(),
        SUSER_SNAME()
    FROM deleted;
END;
GO

-- Tabel de logging pentru Zboruri
CREATE TABLE Logging_Zboruri (
    LogID INT IDENTITY PRIMARY KEY,
    ZborID INT,
    CodZbor VARCHAR(50),
    DataPlecare DATETIME,
    DataSosire DATETIME,
    AeroportPlecare INT,
    AeroportSosire INT,
    CompanieID INT,
    OperationType VARCHAR(10),
    ExecutionDate DATETIME,
    sLogin NVARCHAR(128)
);
GO

CREATE TRIGGER trg_Zboruri_Update_Delete
ON Zboruri
FOR UPDATE, DELETE
AS
BEGIN
    INSERT INTO Logging_Zboruri
    SELECT
        ZborID,
        CodZbor,
        DataPlecare,
        DataSosire,
        AeroportPlecare,
        AeroportSosire,
        CompanieID,
        CASE
            WHEN EXISTS (SELECT * FROM inserted) THEN 'UPDATE'
            ELSE 'DELETE'
        END,
        GETDATE(),
        SUSER_SNAME()
    FROM deleted;
END;

CREATE TABLE Logging_AvioaneZboruri (
    LogID INT IDENTITY PRIMARY KEY,
    AvionID INT,
    ZborID INT,
    OperationType VARCHAR(10),
    ExecutionDate DATETIME,
    sLogin NVARCHAR(128)
);
GO

CREATE TRIGGER trg_AvioaneZboruri_Update_Delete
ON AvioaneZboruri
FOR UPDATE, DELETE
AS
BEGIN
    INSERT INTO Logging_AvioaneZboruri
    SELECT
        AvionID,
        ZborID,
        CASE 
            WHEN EXISTS (SELECT * FROM inserted) THEN 'UPDATE'
            ELSE 'DELETE'
        END,
        GETDATE(),
        SUSER_SNAME()
    FROM deleted;
END;
GO

CREATE VIEW vw_ZboruriAvioane
AS
SELECT
    Z.CodZbor,
    A.Model
FROM Avioane A
JOIN AvioaneZboruri AZ ON A.AvionID = AZ.AvionID
JOIN Zboruri Z ON Z.ZborID = AZ.ZborID;
GO

SELECT * FROM vw_ZboruriAvioane

CREATE VIEW vw_Avioane_Model
AS
SELECT Model
FROM Avioane;
GO

SELECT Model
FROM Avioane
WHERE Model = 'Airbus A320';

SELECT * FROM vw_Avioane_Model;

SELECT CodZbor, Model FROM vw_ZboruriAvioane WHERE Model = 'Airbus A320';

CREATE NONCLUSTERED INDEX IDX_Avioane_Model
ON Avioane(Model);

CREATE NONCLUSTERED INDEX IDX_Zboruri_Cod
ON Zboruri(CodZbor);
