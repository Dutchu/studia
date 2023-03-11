--Bart�omiej B�aszczyk
--236382
 
 use Northwind
 go

--1. Podaj jaki pracownik (Employees) kt�rego pierwsza litera nazwiska jest w przedziale: a-g obs�u�y� jakie numery zam�wie�. Posortuj rezultaty alfabetycznie po nazwiskach pracownik�w oraz w drugiej kolejno�ci malej�co numerach zam�wie�.
SELECT e.FirstName ,e.LastName, o.OrderID
FROM Employees e
LEFT JOIN Orders o
ON o.EmployeeID = e.EmployeeID
WHERE 
e.LastName like '[a-g]%'
ORDER BY
2 asc, 3 desc

--2. Podaj jakiej kategorii nie mamy �adnego produktu?

SELECT c.CategoryName
FROM Products p
INNER JOIN Categories c
ON p.CategoryID = c.CategoryID
GROUP BY c.CategoryName
HAVING COUNT(p.ProductID) = 0

--3. Jaki produkt ma cen� powy�ej �redniej ceny liczonej ze wszystkich produkt�w?
SELECT p.ProductName
FROM Products p
GROUP BY p.ProductName
HAVING 
AVG(p.UnitPrice) > (SELECT AVG(UnitPrice) FROM Products)

--4. Podaj jaki pracownik (Employees) nie ma nad sob� �adnego szefa (jest szefem wszystkich praownik�w)?
SELECT e.EmployeeID, e.LastName, e.ReportsTo
FROM Employees e
WHERE e.ReportsTo is null

--5. Podaj zam�wienia kt�rych data zam�wienia pochodzi z ostatnich trzech miesi�cy realizacji zam�wie�.
SELECT o.OrderID, o.OrderDate
FROM Orders o
WHERE o.OrderDate > DATEADD(MONTH, -3, GETDATE())

--6. Poda� z danej kategorii (nazwa Kategorii) jaka jest warto�� produkt�w w magazynie, ilo�� (r�nych produkt�w), �rednia cena produkt�w, cena minimalna, cena maksymalna dla kt�rych to kategorii warto�� produkt�w jest wi�ksza od 4000 a ilo�� produkt�w wi�ksza od 7.
SELECT c.CategoryName, 
	SUM(p.UnitPrice) * SUM(p.UnitsInStock) as 'category sum value', 
	SUM(p.UnitsInStock) as 'category Units In Stock', 
	AVG(p.UnitPrice) 'category avg UnitPrice',
	MIN(p.UnitPrice) 'category min UnitPrice',
	MAX(p.UnitPrice) 'category max UnitPrice'
FROM Categories c
LEFT JOIN Products p
ON c.CategoryID = p.CategoryID
GROUP BY c.CategoryName
HAVING 
	SUM(p.UnitPrice) * SUM(p.UnitsInStock) > 4000 AND
	SUM(p.UnitsInStock) > 7

-- 7. Zdefiniowa� widok, kt�ry zwr�ci: nazwisko i imi� pracownika oraz ile obs�u�y� on zam�wie�. Wy�wietli� jedynie tych pracownik�w dla kt�rych zagregowana liczba zam�wie� jest mniejsza od 20.
CREATE VIEW view_6 AS (
SELECT e.FirstName, e.LastName, count(o.OrderID)
FROM Employees e
LEFT JOIN Orders o
ON o.EmployeeID = e.EmployeeID
GROUP BY e.EmployeeID
HAVING count(o.OrderID) < 20)

--8. Zdefiniowa� procedur�, kt�ra zwr�ci ca�kowit� sprzeda� w danym roku podanym jako pierwszy parametr typu INT. Parametr drugi typu OUT zwr�ci warto�� sprzeda�y w danym roku bez upust�w. Poda� przyk�ady wyzwolenia tej procedury i prezentacji zwracanego wyniku.
use Northwind
go

CREATE OR ALTER PROCEDURE proc1 (
	@year DATE, 
	@sold int OUTPUT
)AS
SET @sold = (
	SELECT SUM(od.UnitPrice)
	FROM Orders o
	INNER JOIN [Order Details] od
	ON o.OrderID = od.OrderID
	group by YEAR(o.OrderDate)
	having YEAR(o.OrderDate) = YEAR(@year)
)
GO

DECLARE @sold varchar(255);
DECLARE @year DATE = '1996-12-12'

EXEC proc1
@year,
@sold = @sold output;

print CONCAT('SOLD = ', @sold, ' PLN');

--9. Zdefiniowa� struktur� trzech tabel w bazie tempdb ��cznie z ograniczeniami PK, FK i ewentualnie CHECK:
--STUDENCI (IDSTUDENTA, NAZWISKO, IMIE, DATAURODZENIA, MIASTO),
--PRZEDMIOTY(IDPRZEDMIOTU, NAZWA, SEMESTR)
--OCENY(zaproponowa� wymagane kolumny do przechowywania ocen danych student�w z przedmiot�w. Tabela powinna zawiera� kolumn� z dat� kiedy taka ocena zosta�a wprowadzona). Kolumna przechowuj�ca dat� powinna mie� ustawion� warto�� DEFAULT (na dat� bie��c�) w przypadku braku podania podczas wprowadzania. Na kolumnie przechowuj�cej dat� za�o�y� warunek CHECK, kt�ry zapewni, �e wprowadzania data b�dzie dat� wcze�niejsz� od daty zegara systemowego.

--10. Wprowadzi� do ka�dej z tabel po 3 krotki. Nast�pnie zmodyfikowa� jedn� krotk� w tabeli OCENY oraz usun�� jedn� krotk� w tabeli STUDENCI