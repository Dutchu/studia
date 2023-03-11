--Bart³omiej B³aszczyk
--236382
 
 use Northwind
 go

--1. Podaj jaki pracownik (Employees) którego pierwsza litera nazwiska jest w przedziale: a-g obs³u¿y³ jakie numery zamówieñ. Posortuj rezultaty alfabetycznie po nazwiskach pracowników oraz w drugiej kolejnoœci malej¹co numerach zamówieñ.
SELECT e.FirstName ,e.LastName, o.OrderID
FROM Employees e
LEFT JOIN Orders o
ON o.EmployeeID = e.EmployeeID
WHERE 
e.LastName like '[a-g]%'
ORDER BY
2 asc, 3 desc

--2. Podaj jakiej kategorii nie mamy ¿adnego produktu?

SELECT c.CategoryName
FROM Products p
INNER JOIN Categories c
ON p.CategoryID = c.CategoryID
GROUP BY c.CategoryName
HAVING COUNT(p.ProductID) = 0

--3. Jaki produkt ma cenê powy¿ej œredniej ceny liczonej ze wszystkich produktów?
SELECT p.ProductName
FROM Products p
GROUP BY p.ProductName
HAVING 
AVG(p.UnitPrice) > (SELECT AVG(UnitPrice) FROM Products)

--4. Podaj jaki pracownik (Employees) nie ma nad sob¹ ¿adnego szefa (jest szefem wszystkich praowników)?
SELECT e.EmployeeID, e.LastName, e.ReportsTo
FROM Employees e
WHERE e.ReportsTo is null

--5. Podaj zamówienia których data zamówienia pochodzi z ostatnich trzech miesiêcy realizacji zamówieñ.
SELECT o.OrderID, o.OrderDate
FROM Orders o
WHERE o.OrderDate > DATEADD(MONTH, -3, GETDATE())

--6. Podaæ z danej kategorii (nazwa Kategorii) jaka jest wartoœæ produktów w magazynie, iloœæ (ró¿nych produktów), œrednia cena produktów, cena minimalna, cena maksymalna dla których to kategorii wartoœæ produktów jest wiêksza od 4000 a iloœæ produktów wiêksza od 7.
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

-- 7. Zdefiniowaæ widok, który zwróci: nazwisko i imiê pracownika oraz ile obs³u¿y³ on zamówieñ. Wyœwietliæ jedynie tych pracowników dla których zagregowana liczba zamówieñ jest mniejsza od 20.
CREATE VIEW view_6 AS (
SELECT e.FirstName, e.LastName, count(o.OrderID)
FROM Employees e
LEFT JOIN Orders o
ON o.EmployeeID = e.EmployeeID
GROUP BY e.EmployeeID
HAVING count(o.OrderID) < 20)

--8. Zdefiniowaæ procedurê, która zwróci ca³kowit¹ sprzeda¿ w danym roku podanym jako pierwszy parametr typu INT. Parametr drugi typu OUT zwróci wartoœæ sprzeda¿y w danym roku bez upustów. Podaæ przyk³ady wyzwolenia tej procedury i prezentacji zwracanego wyniku.
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

--9. Zdefiniowaæ strukturê trzech tabel w bazie tempdb ³¹cznie z ograniczeniami PK, FK i ewentualnie CHECK:
--STUDENCI (IDSTUDENTA, NAZWISKO, IMIE, DATAURODZENIA, MIASTO),
--PRZEDMIOTY(IDPRZEDMIOTU, NAZWA, SEMESTR)
--OCENY(zaproponowaæ wymagane kolumny do przechowywania ocen danych studentów z przedmiotów. Tabela powinna zawieraæ kolumnê z dat¹ kiedy taka ocena zosta³a wprowadzona). Kolumna przechowuj¹ca datê powinna mieæ ustawion¹ wartoœæ DEFAULT (na datê bie¿¹c¹) w przypadku braku podania podczas wprowadzania. Na kolumnie przechowuj¹cej datê za³o¿yæ warunek CHECK, który zapewni, ¿e wprowadzania data bêdzie dat¹ wczeœniejsz¹ od daty zegara systemowego.

--10. Wprowadziæ do ka¿dej z tabel po 3 krotki. Nastêpnie zmodyfikowaæ jedn¹ krotkê w tabeli OCENY oraz usun¹æ jedn¹ krotkê w tabeli STUDENCI