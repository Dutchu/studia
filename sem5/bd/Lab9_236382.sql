-----------------------------
-- Procedury przechowywane -- 
-----------------------------
USE NORTHWIND
GO
	IF EXISTS (SELECT * FROM sysobjects WHERE name = N'sample_procedure' AND type = 'P') DROP PROCEDURE sample_procedure
	GO
--lub w nowszych wersjach SQL Server
DROP PROCEDURE IF EXISTS dbo.sample_procedure;
GO
CREATE PROCEDURE sample_procedure 
	@p1 int = 0, 
	@p2 int = 0
AS
	SELECT @p1, @p2
GO
-- Przyk³ad wykonania procedury przechowywanej -- 
EXECUTE sample_procedure 1, 2
GO

---------------------------------------------------------------
-- Definicja procedury sk³adowanej z parametrami typu OUTPUT --
---------------------------------------------------------------
DROP PROCEDURE IF EXISTS dbo.your_procedure_name
GO

CREATE PROCEDURE your_procedure_name 
	@p1 int = 0, 
	@p2 int  OUTPUT
AS
	SELECT @p2 = @p2 + @p1
GO

-- Przyk³ad wykonania procedury przechowywanej -- 
DECLARE @p2_output int 
EXECUTE your_procedure_name 1, @p2_output OUTPUT
SELECT @p2_output
GO

------------------------------------------------------
-- Procedury przechwowywane (sk³adowane) - przyk³ad --
------------------------------------------------------
DROP PROC IF EXISTS dbo.GetCustomerOrders;
GO

CREATE PROC dbo.GetCustomerOrders
  @custid   AS INT,
  @fromdate AS DATETIME = '19000101',
  @todate   AS DATETIME = '99991231',
  @numrows  AS INT OUTPUT
AS
SET NOCOUNT ON;

SELECT orderid, CustomerID, EmployeeID, OrderDate
FROM dbo.Orders
WHERE CustomerID = @custid
  AND OrderDate >= @fromdate
  AND Orderdate < @todate;

SET @numrows = @@rowcount;
GO

DECLARE @rc AS INT;

EXEC dbo.GetCustomerOrders
  @custid   = 1, -- Also try with 100
  @fromdate = '19970101',
  @todate   = '19980101',
  @numrows  = @rc OUTPUT;

SELECT @rc AS numrows;
GO



-------------
-- FUNCKJE --
-------------

------------------------------
-- Tworzenie funkcji INLINE --
------------------------------
IF EXISTS (SELECT * FROM   sysobjects WHERE  name = N'test_function')
	DROP FUNCTION test_function
GO

CREATE FUNCTION test_function 
	(@p1 int, 
	 @p2 char)
RETURNS TABLE 
AS
	RETURN SELECT @p1 AS c1, @p2 AS c2
GO

--------------------------------
-- Przyk³ad wywo³ania funkcji --
--------------------------------
SELECT * 
FROM dbo.test_function (1, 'a')
GO

---------------------------------
-- Tworzenie funkcji skalarnej --
---------------------------------
IF EXISTS (SELECT * FROM sysobjects WHERE  name = N'test_function')
	DROP FUNCTION test_function
GO

CREATE FUNCTION test_function 
	(@p1 int, 
	 @p2 int)
RETURNS int
AS
BEGIN
	RETURN @p1 + @p2
--	lub
--	DECLARE @sum AS int
--	SELECT @sum = @p1 + @P2
--	RETURN @sum
END
GO

--------------------------------
-- Przyk³ad wywo³ania funkcji --
--------------------------------
SELECT dbo.test_function (1, 2)
GO

-------------------------------------
-- Tworzenie funkcji tabelarycznej --
-------------------------------------
IF EXISTS (SELECT * FROM   sysobjects WHERE  name = N'test_function')
	DROP FUNCTION test_function
GO

CREATE FUNCTION test_function 
	(@p1 int, 
	 @p2 int)
RETURNS @table_var TABLE 
	(c1 int, 
	 c2 int)
AS
BEGIN
	INSERT @table_var SELECT @p1, @p2
	INSERT @table_var SELECT @p1*@p1, @p2*@p2
	INSERT @table_var SELECT @p1*@p2, @p1*@p2
	RETURN 
END
GO
--------------------------------
-- Przyk³ad wywo³ania funkcji --
--------------------------------
SELECT * FROM dbo.test_function (4, 7)
GO

---------------------------------------------------------------------
-- Funkcje definiowane przez u¿ytkownika
---------------------------------------------------------------------

DROP FUNCTION IF EXISTS dbo.GetAge;
GO

CREATE FUNCTION dbo.GetAge
(
  @birthdate AS DATE,
  @eventdate AS DATE
)
RETURNS INT
AS
BEGIN
  RETURN
    DATEDIFF(year, @birthdate, @eventdate)
    - CASE WHEN 100 * MONTH(@eventdate) + DAY(@eventdate)
              < 100 * MONTH(@birthdate) + DAY(@birthdate)
           THEN 1 ELSE 0
      END;
END;
GO

-- Test funkcji
SELECT
  EmployeeID, firstname, lastname, birthdate,
  dbo.GetAge(birthdate, '20200212') AS age
FROM dbo.Employees;

---------------------------------------------------------------------
-- Funkcje definiowane przez u¿ytkownika
---------------------------------------------------------------------

DROP FUNCTION IF EXISTS dbo.GetAge;
GO

CREATE FUNCTION dbo.GetAge
(
  @birthdate AS DATE,
  @eventdate AS DATE
)
RETURNS INT
AS
BEGIN
  RETURN
    DATEDIFF(year, @birthdate, @eventdate)
    - CASE WHEN 100 * MONTH(@eventdate) + DAY(@eventdate)
              < 100 * MONTH(@birthdate) + DAY(@birthdate)
           THEN 1 ELSE 0
      END;
END;
GO

-- Test funkcji
SELECT
  EmployeeID, FirstName, Lastname, Birthdate,
  dbo.GetAge(birthdate, '20200212') AS age
FROM dbo.Employees;
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------

----------------------------------------------
-- Obs³uga b³êdu z wykorzytsaniem procedury --
-- Opakowywanie kodu do ponownego u¿ycia    --
----------------------------------------------
DROP PROC IF EXISTS dbo.ErrInsertHandler;
GO

CREATE PROC dbo.ErrInsertHandler
AS
SET NOCOUNT ON;

IF ERROR_NUMBER() = 2627
  BEGIN
    PRINT '    Obs³uga naruszenia PK...';
  END
  ELSE IF ERROR_NUMBER() = 547
  BEGIN
    PRINT '    Obs³uga naruszenia ograniczenia CHECK/FK...';
  END
  ELSE IF ERROR_NUMBER() = 515
  BEGIN
    PRINT '    Obs³uga nieprawid³owej wartoœci NULL...';
  END
  ELSE IF ERROR_NUMBER() = 245
  BEGIN
    PRINT '    Obs³uga b³êdu konwersji...';
  END
  ELSE
  BEGIN
    PRINT 'Obs³uga nieznanego b³êdu...';
    THROW; -- tylko system SQL Server 2012 
  END

  PRINT '    Numer b³êdu    : ' + CAST(ERROR_NUMBER() AS VARCHAR(10));
  PRINT '    Komunikat b³êdu: ' + ERROR_MESSAGE();
  PRINT '    Wa¿noœæ b³êdu  : ' + CAST(ERROR_SEVERITY() AS VARCHAR(10));
  PRINT '    Stan b³êdu      : ' + CAST(ERROR_STATE() AS VARCHAR(10));
  PRINT '    Wiersz b³êdu    : ' + CAST(ERROR_LINE() AS VARCHAR(10));
  PRINT '    Procedura b³êdu  : ' + COALESCE(ERROR_PROCEDURE(), 'Not within proc');
GO

-- Wywo³anie procedury w bloku CATCH
BEGIN TRY

  INSERT INTO dbo.Employees(EmployeeID, LastName, ReportsTo)
    VALUES(1, 'Emp1', NULL);

END TRY
BEGIN CATCH

  IF ERROR_NUMBER() IN (2627, 547, 515, 245)
    EXEC dbo.ErrInsertHandler;
  ELSE
    THROW;
  
END CATCH;


-------------------------------------------------------------------------
-- Wykorzystanie kursora bez definiowania procedury zwracaj¹cej kursor --
-- oraz to samo z wkorzystaniem procedury                              --
-------------------------------------------------------------------------
USE Northwind;  
GO  
-- blok Transact-SQL bez procedury
-- deklarujemy zmienne, aby zapisaæ wartoœci zwrócone przez FETCH.  
DECLARE @LastName varchar(50), @FirstName varchar(50);  
  
DECLARE contact_cursor CURSOR FOR  
SELECT LastName, FirstName FROM dbo.Employees  
WHERE LastName LIKE '[B-F]%'  
ORDER BY LastName, FirstName;  
  
OPEN contact_cursor;  
  
-- Wykonaj pierwsze pobranie i zapisz wartoœci w zmiennych.
-- Uwaga: Zmienne s¹ w tej samej kolejnoœci, co kolumny w instrukcji SELECT.  
FETCH NEXT FROM contact_cursor INTO @LastName, @FirstName;  
  
-- Sprawdzamy @@FETCH_STATUS czy s¹ jeszcze wiersze do pobrania  
WHILE @@FETCH_STATUS = 0  
BEGIN  
   PRINT 'Contact Name: ' + @FirstName + ' ' +  @LastName  
   -- Jest to wykonywane, dopóki poprzednie pobranie rekordu powiedzie siê  
   FETCH NEXT FROM contact_cursor INTO @LastName, @FirstName;  
END  
  
CLOSE contact_cursor;  
DEALLOCATE contact_cursor;  
GO

----------------------------------------------------------------------------
-- Tworzenie procedury przechowywanej z parametrem wyjœciowym typu CURSOR --
----------------------------------------------------------------------------
DROP PROCEDURE IF EXISTS dbo.sample_procedure
GO
-- Definicja procedury przechowywanej z parametrem wyjœciowym typu CURSOR 
CREATE PROCEDURE sample_procedure 
	@sample_procedure_cursor CURSOR VARYING OUTPUT
AS
   SET @sample_procedure_cursor = CURSOR FOR
		SELECT LastName, FirstName FROM dbo.Employees  
		WHERE LastName LIKE '[B-F]%'  
		ORDER BY LastName, FirstName;  
   OPEN @sample_procedure_cursor
GO

-------------------------------------------------
-- blok Transact-SQL z procedur¹ przechowywan¹ --
-------------------------------------------------
-- Deklarujemy zmienne, aby zapisaæ wartoœci zwrócone przez FETCH.  
DECLARE @LastName varchar(50), @FirstName varchar(50),
		@test_cursor_variable CURSOR

EXEC sample_procedure @sample_procedure_cursor = @test_cursor_variable OUTPUT;  
  
-- Wykonaj pierwsze pobranie i zapisz wartoœci w zmiennych.
-- Uwaga: Zmienne s¹ w tej samej kolejnoœci, co kolumny w instrukcji SELECT.  
  
FETCH NEXT FROM @test_cursor_variable  INTO @LastName, @FirstName;  
  
WHILE @@FETCH_STATUS = 0  
BEGIN  
   PRINT 'Contact Name: ' + @FirstName + ' ' +  @LastName;  
   FETCH NEXT FROM @test_cursor_variable INTO @LastName, @FirstName;  
END;  
CLOSE @test_cursor_variable;
DEALLOCATE @test_cursor_variable; 
GO
--------------------------------------------------------------------------------------------
-- Zadania --

------PROCEDURE
-- 1. Zdefiniuj procedurê, która wyœwietli na ekranie imiê, nazwisko oraz pensjê pracownika o identyfikatorze podanym 
--jako pierwszy parametr. Je¿eli nie ma takiego id to zwrócony zostanie informacja a braku takiego pracownika.
create or alter proc pracownik(
@id nvarchar(250)
)
as
if exists (select * from Employees where @id=EmployeeID)
select EmployeeID,FirstName,LastName from Employees
where EmployeeID like @id
else
PRINT 'Brak pracownika o podanym id';
go
exec pracownik '11'
-- 2. Zdefiniowaæ procedurê, która zwróci liczbê zatrudnionych wszystkich pracowników.
create or alter procedure liczba_pracownikow
as
select count(EmployeeID) as [liczba pracownikow] from Employees
go
exec liczba_pracownikow
-- 3. Zdefiniowaæ procedurê, która zwróci liczbê produktów w danej kategorii podanej jako pierwszy parametr. 
--Parametr drugi typu OUT zwróci liczbê produktów.
create or alter procedure licz_prod_z_kat(
@katid int,
@wynik int output
)
as
set @wynik=(select count(ProductID) as [liczba produktow] from Products
where CategoryID=@katid)
go

declare @wynik int
declare @katid int = 3
exec licz_prod_z_kat @katid,@wynik output
SELECT 'liczba produktow z katergori '+ CONVERT(varchar(50), @katid)+' wynosi ' +
CONVERT(varchar(50), @wynik)
------FUNCTION
--	1. Zdefiniowaæ funkcjê, która wycina spacje na pocz¹tku i koñcu zmiennej typu VARCHAR
--	i zwraca to co zostanie.
DROP function IF EXISTS dbo.usun_spacje;
GO

CREATE FUNCTION usun_spacje (@wejscie varchar(200))
RETURNS varchar(200)
AS
begin
	declare @wynik varchar(200);
	set @wynik = (SELECT LTRIM(RTRIM(@wejscie)))
	return @wynik;
end
GO

declare @wartosc varchar(200)  = '                      TEST                       ';
SELECT @wartosc as pre,dbo.usun_spacje(@wartosc) as post

-- 2. Zdefiniowaæ funkcjê, która dla categoryid zwraca wartoœæ œredni¹ z wszystkich produktów w tej kategorii
DROP function IF EXISTS dbo.srednia_z_catid;
GO

CREATE FUNCTION srednia_z_catid (@wejscie int)
RETURNS float
AS
begin
	declare @wynik float;
	set @wynik = (
	SELECT avg(UnitPrice) from Products
	where CategoryID=@wejscie
	)
	return @wynik;
end
GO

declare @wartosc int  = 4;
SELECT @wartosc as numer_kategori ,dbo.srednia_z_catid(@wartosc) as srednia

-- 3. Zdefiniowaæ funkcjê, która dla categoryname zwraca wartoœæ œredni¹ z wszystkich produktów w tej kategorii
DROP function IF EXISTS dbo.srednia_z_catname;
GO

CREATE FUNCTION srednia_z_catname (@wejscie varchar(200))
RETURNS float
AS
begin
	declare @wynik float;
	set @wynik = (
	SELECT avg(p.UnitPrice) from Products p
	inner join Categories c on p.CategoryID=c.CategoryID
	where c.CategoryName=@wejscie
	)
	return @wynik;
end
GO

declare @wartosc varchar(200)  = 'Confections';
SELECT @wartosc as nazwa_kategori ,dbo.srednia_z_catname(@wartosc) as srednia

-- 4. Zdefiniowaæ funkcjê do konewrsji typu date na string postaci YYYY-MM-DD.
DROP function IF EXISTS dbo.konwersja_daty;
GO

CREATE FUNCTION konwersja_daty (@wejscie date)
RETURNS VARCHAR(200)
AS
begin
	declare @wynik VARCHAR(200);
	set @wynik = CONCAT(DATEPART(YEAR,@wejscie),'-',DATEPART(MONTH,@wejscie),'-',DATEPART(DAY,@wejscie));
	return @wynik;
end
GO

declare @wartosc date  = getdate();
SELECT @wartosc as data ,dbo.konwersja_daty(@wartosc) as TEKST

-- 5. Zdefiniowaæ funkcjê, która zwraca z daty podanej jako parametr wejœciowy dzieñ tygodnia w jêzyku polskim.
DROP function IF EXISTS dbo.data_na_dzien;
GO

CREATE FUNCTION data_na_dzien (@wejscie date)
RETURNS VARCHAR(200)
AS
begin
	declare @wynik VARCHAR(200);
	declare @tmp int;
	set @tmp = DATEPART(WEEKDAY,@wejscie);
	if		@tmp=1
		set @wynik='Nieziela'
	else if @tmp=2
		set @wynik='Poniedzia³ek'
	else if @tmp=3
		set @wynik='Wtorek'
	else if @tmp=4
		set @wynik='Œroda'
	else if @tmp=5
		set @wynik='Czwartek'
	else if @tmp=6
		set @wynik='Pi¹tek'
	else if @tmp=7
		set @wynik='Sobota'
	else
		set @wynik='Niema takiego dnia tygodnia'
	return @wynik;
end
GO

declare @wartosc date  = getdate();
SELECT @wartosc as data ,dbo.data_na_dzien(@wartosc) as Dzieñ_tygodnia

-- 6. Zdefiniowaæ funkcjê z trzema parametrami, która sprawdzi czy dane boki tworz¹ trój¹t, a jeœli tak to obliczyæ jego pole.
DROP function IF EXISTS dbo.pole_trojkata;
GO

CREATE FUNCTION pole_trojkata (@A float,@B float,@C float)
RETURNS float
AS
begin
	declare @wynik float;
	declare @tmp float;
	declare @obw float;
	--SZUKANIE MAX BOKU
	if @A>@B and @A>@C
		set @A=@A;
	else if  @B>@A and @B>@C
		begin
			set @tmp=@B;
			set @B=@A;
			set @A=@tmp;
		end;
	else if @C>@B and @C>@A
		begin
			set @tmp=@C;
			set @C=@A;
			set @A=@tmp;
		end;
	else if @A=@B and @A=@C and @B=@C
		set @A=@A;
	
	--SPRAWDZANIE WARUNKU TROJKATA
	if @B+@C>@A
		begin
			set @obw=@A+@B+@C;
			set @obw=@obw/2;
			set @tmp=@obw*(@obw-@A)*(@obw-@B)*(@obw-@C);
			set @wynik=SQRT(@tmp);
		end;
	return @wynik;
end
GO

SELECT dbo.pole_trojkata(3,2,2) AS POLE

-- 7. Zdefiniowaæ funkcjê zamieniajac¹ wszystkie spacje podkreœleniem.
DROP function IF EXISTS dbo.spacja_na_podloge;
GO

CREATE FUNCTION spacja_na_podloge (@wejscie varchar(200))
RETURNS varchar(200)
AS
begin
	declare @wynik varchar(200);
	set @wynik=REPLACE(@wejscie,' ','_');
	return @wynik;
end
GO
declare @zmienna varchar(200)='         test             ';
SELECT @zmienna,dbo.spacja_na_podloge(@zmienna)

-- 8. Zdefiniowaæ funkcjê do odwracania stringu.
DROP function IF EXISTS dbo.tekst_obrocony;
GO

CREATE FUNCTION tekst_obrocony (@wejscie varchar(200))
RETURNS varchar(200)
AS
begin
	declare @wynik varchar(200);
	set @wynik=REVERSE(@wejscie);
	return @wynik;
end
GO
declare @zmienna varchar(200)='Mo¿e jutro ta dama sama da tortu je¿om';
SELECT @zmienna,dbo.tekst_obrocony(@zmienna)

-- 9. Zdefiniowaæ funkcjê, która sprawdza czy dana liczba ca³kowita jest parzysta czy nieparzysta i zwraca wartoœæ 'Parzysta' lub 'Nieparzysta'.
DROP function IF EXISTS dbo.P_czy_N;
GO

CREATE FUNCTION P_czy_N (@wejscie int)
RETURNS varchar(200)
AS
begin
	declare @wynik varchar(200);
	declare @tmp int;
	set @tmp=@wejscie%2;
	if @tmp=1
		set @wynik='Nieparzysta';
	else
		set @wynik='Parzysta';
	return @wynik;
end
GO
declare @zmienna int = 0;
SELECT @zmienna,dbo.P_czy_N(@zmienna)
--10. Zdefiniowaæ funkcjê do obliczenia wartoœci silnia z liczby ca³kowitej (zdefiniowaæ obs³ugê b³êdów w przypadku liczb mniejszych od 1 i takich, które przekrocz¹ zakres wykorzystywaneo typu.
DROP function IF EXISTS dbo.silnia;
GO

CREATE FUNCTION silnia(@wejscie int)
RETURNS int
AS
begin
	declare @wynik int;
	set @wynik=1;
	
	while @wejscie>0
	begin
		set @wynik=@wynik*@wejscie;
		set @wejscie=@wejscie-1;
	end;

	return @wynik;
end
GO
declare @zmienna int = 5;
SELECT @zmienna as liczba,dbo.silnia(@zmienna) as silnia