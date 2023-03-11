-- 1. Znaleźć produkty, które w nazwie na miejscu dwudziestym miejscu ma literę S, gdzie długość stringu jest >= 20 znaków (LEN)
	use Northwind
	select ProductName from Products
	where SUBSTRING(ProductName, 19, 20) like 's'

-- 2. Znaleźć produkty zaczynające się na litery od A do S, których cena jest z zakres 15 do 120, które należą do kategorii 1,3,6. 
	use Northwind
	select ProductName from Products
	where ProductName like '[a-s]%'
	and
	UnitPrice between 15 and 120
	and
	CategoryID like '[136]'

-- 3. Znaleźć produkty, które w nazwie mają słowo New.
	use Northwind
	select ProductName from Products
	where ProductName like '% new %'

-- 4. Łaczymy Imię, nazwisko i numer pracownika (Employees) w jeden string i wyświetlamy jedną kolumnę.
	use Northwind
	select FirstName+' '+LastName+' '+HomePhone from Employees
	-- wykorzystujemy funkcję CAST (sprawdzamy w dokumentacji)
	use Northwind
	select cast(FirstName+' '+LastName+' '+HomePhone as varchar) from Employees
	-- wykorzystujemy funkcję CONVERT (sprawdzamy w dokumentacji)
	use Northwind
	select convert(varchar,FirstName+' '+LastName+' '+HomePhone) from Employees
	-- wykorzystujemy funkcję CONCAT (sprawdzamy w dokumentacji)
	use Northwind
	select concat(FirstName,' ',LastName,' ',HomePhone) from Employees

--------------------------------------
-- Polecenia INSERT, UPDATE, DELETE --
--------------------------------------

-- Przygotowujemy dane (mogą by być z poprzednich zajęć)
select * from Categories; 
delete Products where ProductID>=78;
delete Categories where CategoryID >= 9;

--Wstawiamy nową kategorię o nazwie 'Kat 1' 
insert into Categories (CategoryName) values ('Kat 1')

--Wstawiamy dwie nowe kategorie o nazwie 'Kat 2' i 'Kat 3' jednym poleceniem 
insert  into Categories (CategoryName) values ('Kat 2'),('Kat 3');

--Wstawiamy nową kategorię o nazwie 'Kat 4' łącznie z polem Description 'Opis 4' 
insert into Categories (CategoryName, Description) values ('Kat 4','opis 4')

--Wstawiamy nową kategorię o nazwie 'Kat 5' łącznie z polem Description z wartością NULL
insert into Categories (CategoryName, Description) values ('Kat 5', NULL)

--Kasujemy rekord gdzie  CategoryName = 'Kat 5' i CategoryID >= 9
delete Categories where CategoryName = 'Kat 5' and CategoryID >= 9

--Modyfikujemy wszystkie kategorie zaczynające się na słowo 'Kat' i ustawiamy aby ich nowa nazwa była pisana dużymi literami oraz Description było wartością NULL
update Categories set CategoryName = UPPER(categoryname), Description = NULL
	 where CategoryName like 'Kat%';

-- 1. Zmodyfikuj kategorię aby była pisana małymi literami (klauzula WHERE zawiera konkretny numer kategorii)
	update Categories set CategoryName = LOWER(categoryname)
	where CategoryID = 7;
	
-- 2. Skasuj daną kategorię (klauzula WHERE zawiera konkretny numer kategorii)
	delete Categories where CategoryID = 9;

----------------
-- Transakcje --
----------------

----------------------------------------------------------------------------------------------------------------------------
-- Przykład 1 wycofanie transakcji (dla spradzenia działania wykonujemy każde polecenie po kolei)--
----------------------------------------------------------------------------------------------------------------------------
begin tran
	insert  into Categories (CategoryName) values ('Kat t1'),('Kat t2');
	-- Sprawdzamy czy faktycznnie operacja została wykonana czy wycofana
	select * from Categories where CategoryName like 'Kat%'
-- wycofujemy transkacje
rollback tran 
-- Sprawdzamy czy faktycznnie operacja została wykonana czy wycofana
select * from Categories where CategoryName like 'Kat%'
----------------------------------------------------------------------------------------------------------------------------
-- Przykład 2 zatwierdzenie transakcji (dla spradzenia działania wykonujemy każde polecenie po kolei)--
begin tran
	insert  into Categories (CategoryName) values ('Kat t1'),('Kat t2');
	-- Sprawdzamy czy faktycznnie operacja została wykonana czy wycofana
	select * from Categories where CategoryName like 'Kat%'
-- zatwierdzamy transkacje
commit tran 
-- Sprawdzamy czy faktycznnie operacja została wykonana czy wycofana
select * from Categories where CategoryName like 'Kat%'
----------------------------------------------------------------------------------------------------------------------------

-- 3.Sprawdzić i podać jaki jest ustawiony poziom izolacji transakcji i jak zmienić aktualny poziom
--SPRAWDZENIE
SELECT CASE transaction_isolation_level 
    WHEN 0 THEN 'Unspecified' 
    WHEN 1 THEN 'ReadUncommitted' 
    WHEN 2 THEN 'ReadCommitted' 
    WHEN 3 THEN 'Repeatable' 
    WHEN 4 THEN 'Serializable' 
    WHEN 5 THEN 'Snapshot' END AS TRANSACTION_ISOLATION_LEVEL 
FROM sys.dm_exec_sessions 
where session_id = @@SPID
--Ustawiony jest poziom ReadCommitted
--USTAWIANIE
SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED
-- 4.Otworzyć dwa okna i zaobserwować w drugim okienku blokowanie czytanych danych przy nie zakończonej transakcji z pierwszego okienka na danej tabeli np. categories
--Okienko 1
begin tran
	insert  into Categories (CategoryName) values ('Kat t1'),('Kat t2');
--Okienko 2
select * from Categories
--informacje w okienku 2 nie sa wyswietlanie do momentu zakonczenia tranzakcji
--Okienko 1
rollback tran
--Dopiero w tym momencie pojawiaja sie informacje w okineku 2

-- 5. j.w. tylko w drugim okienku ustawić poziom izolacji transakcji jako 'set transaction isolation level read uncommitted' i czytamy dane z tabeli categories (jaka jest różnica?)

--Dane w tabeli nie sa blokowane i wysietlane natychmiast bez koniecznosci finalizowania tranzakcji

-- 6.Dodać nową kategorię o nazwie 'Kategoria 1' a następnie dodać produkt o nazwie 'Produkt 1' należący do kategorii 'Kategoria 1' 
	-- (nie znamy categoryid danej kategorii)(pamiętajmy iż niektóre pola są wymagane do wstawienia rekordu)
insert  into Categories (CategoryName) values ('Kategoria 1');
insert  into Products (ProductName) values ('Produkt 1')
select * from Categories
select * from Products
update Products set CategoryID=9
where ProductName like ('Produkt 1')
select * from Products

-- 7.Dodać produkt 'Produkt 2' do kategorii o numerze 2000 
	-- (jak wynik zapytania podać wygenerowany błąd i poniżej odpowiedzieć na pytanie dlaczego ten błąd wystąpił i co maiało na to wpływ)
insert  into Products (ProductName,CategoryID) values ('Produkt 2',2000)
select * from Products
--The INSERT statement conflicted with the FOREIGN KEY constraint "FK_Products_Categories". The conflict occurred in database "Northwind", table "dbo.Categories", column 'CategoryID'.
--Wystapil blad poniewaz nie istnieje kategoria o takim id

--------------------
-- Łączenie tabel --
--------------------

-- Podaj nazwę produktu, jego cenę, numer kategorii i nazwę kategorii z tabel Products i Categories (wykorzystujemy klauzulę WHERE)
select ProductName, UnitPrice, P.CategoryID, CategoryName
	from Categories c, Products p
	where c.CategoryID = P.CategoryID;

-- 8.Podaj nazwę produktu, jego cenę, numer kategorii i nazwę kategorii z tabel Products i Categories (wykorzystujemy klauzulę WHERE)
	-- dla produktów z categoryid >= 8
select ProductName, UnitPrice, P.CategoryID, CategoryName
	from Categories c, Products p
	where c.CategoryID = P.CategoryID
	and
	P.CategoryID>=8;

-- Podaj nazwę produktu, jego cenę i nazwę kategorii z tabel Products i Categories (wykorzystujemy klauzulę JOIN ... ON)
	-- dla produktów z categoryid >= 8 oraz posortować malejąco po cenie
select ProductName, UnitPrice, CompanyName
	from Products inner join Suppliers
	on Products.SupplierID= Suppliers.SupplierID
	where categories.CategoryID >= 8;
	order by 2 desc

-- 9.Podaj nazwę produktu, jego cenę i nazwę firmy dostawcy (wykorzystujemy klauzulę INNER JOIN ... ON)
select ProductName, UnitPrice, CompanyName
	from Products inner join Suppliers
	on Products.SupplierID= Suppliers.SupplierID

-- 10.Podaj nazwę produktu, jego cenę i nazwę dostawcy z tabel Products i Suppliers (wykorzystujemy klauzulę INNER JOIN ... ON)
	-- dla produktów z categoryid >= 8 oraz posortować malejąco po cenie
select ProductName, UnitPrice, CompanyName
	from Products inner join Suppliers
	on Products.SupplierID= Suppliers.SupplierID
	where CategoryID>=8
	order by 2 DESC

-- 11.Podaj nazwę produktu, jego cenę, nazwę firmy dostawcy i nazwę kategorii do której należy.
select p.ProductName, p.UnitPrice, s.CompanyName,c.CategoryName
	from Products as p 
	inner join Suppliers as s
	on p.SupplierID= s.SupplierID
	inner join Categories as c
	on p.CategoryID=c.CategoryID

-- 12.Dana firma w jakiej kategorii dostarcza produkty (posortować po nazwie firmy i nazwie kategorii)
select s.CompanyName,c.CategoryName
	from Products as p 
	inner join Suppliers as s
	on p.SupplierID= s.SupplierID
	inner join Categories as c
	on p.CategoryID=c.CategoryID
	order by 1,2
-- 13.Podaj nazwę klienta, datę zamówienia i nazwę pracownika, który go obsługiwał.
select c.CompanyName,o.OrderDate,e.FirstName+' '+e.LastName as Pracownik
	from Orders as o 
	inner join Customers as c
	on o.CustomerID= c.CustomerID
	inner join Employees as e
	on o.EmployeeID=e.EmployeeID

-- 14.Podaj nazwę klienta i nazwy kategorii, w których klient kupował produkty (bez powtórzeń)
select DISTINCT ca.CategoryName,c.CompanyName from Orders o 
inner join Customers c on o.CustomerID=c.CustomerID 
inner join [Order Details] od on od.OrderID=o.OrderID 
inner join Products p on od.ProductID=p.ProductID
inner join Categories ca on ca.CategoryID=p.CategoryID
order by 1,2

-- 15.Podaj numer zamówienia, nazwę produktu i jego cenę na zamówieniu oraz upust.
select o.OrderID,p.ProductName,od.UnitPrice,od.Discount from Orders o 
inner join [Order Details] od on od.OrderID=o.OrderID 
inner join Products p on od.ProductID=p.ProductID
order by 1
----------------------------------------------------------------------------------------------------------------------------
-- Aby nie pisać zapytania za każdym razem kiedy chcemy go wykonać to możemy utworzyć widok na podstawie danego zapytania --
----------------------------------------------------------------------------------------------------------------------------
create view v_Prod_Supp(name,price,c_name) 
as
select ProductName, UnitPrice, CompanyName
	from Products inner join Suppliers
	on Products.SupplierID= Suppliers.SupplierID
	where categories.CategoryID >= 8;
GO
----------------------------------------------------------------------------------------------------------------------------

-- 16.Podaj wynik na podstawie widoku (nie tabel), gdzie kolumna price ma być >=100 i posortować względem kolumny name.
create view v_Prod_Supp(name,price,c_name) 
as
select ProductName, UnitPrice, CompanyName
	from Products inner join Suppliers
	on Products.SupplierID= Suppliers.SupplierID
GO
select * from v_Prod_Supp
where price>=100
order by 1

-- Skasuj dany widok
	drop view v_Prod_Supp;


