------------------------
-- ��czenie tabel cd. --
------------------------

-- Wykonaj dwa polecenia
insert into Categories (CategoryName) values ('A1');
insert into Products (ProductName) values ('P1');
-- czy wykonuj�c zapytanie widzimy wprowadzone rekordy ?
select ProductName, UnitPrice, CategoryName
	from (Categories inner join Products
	on Categories.CategoryID=Products.CategoryID)

-- Podaj nazw� produktu, jego cen� i nazw� kategorii z tabel Products i Categories.
	-- chcemy tak�e wy�wietli� wszystkie nazwy kategorii nawet te przez przypisanych produkt�w 
select ProductName, UnitPrice, CategoryName
	from Categories left join Products   -- left outer join 
	on Categories.CategoryID=Products.CategoryID

-- Podaj nazw� produktu, jego cen� i nazw� kategorii z tabel Products i Categories.
	-- chcemy tak�e wy�wietli� wszystkie produkty nawet bez przypisanej kategorii 
select ProductName, UnitPrice, CategoryName
	from (Categories right join Products   --right outer join
	on Categories.CategoryID=Products.CategoryID)

-- Podaj nazw� produktu, jego cen� i nazw� kategorii z tabel Products i Categories.
	-- chcemy tak�e wy�wietli� wszystkie produkty i wszystkie kategorie 
select ProductName, UnitPrice, CategoryName
	from (Categories full outer join Products   --full outer join
	on Categories.CategoryID=Products.CategoryID)

-- 1.Podaj nazwy kategorii, kt�re nie maj� przypisanych produkt�w.
select CategoryName
from Categories left join Products
on Categories.CategoryID=Products.CategoryID
where ProductName is null

-- 2.Podaj nazwy produkt�w, kt�re nie maj� przypisanej kategorii (z wykorzystaniem JOIN'a) 
select ProductName
from (Categories right join Products
on Categories.CategoryID=Products.CategoryID)
where CategoryName is null

-- 3.Podaj nazwy produkt�w, kt�re nie maj� przypisanej kategorii (bez wykorzystania JOIN'a) 
select ProductName from Products
where CategoryID is null

-- 4. Podaj nazw� produktu, jego cen� i nazw� kategorii z tabel Products i Categories.
	-- chcemy tak�e wy�wietli� wszystkie produkty i wszystkie kategorie 
select ProductName, UnitPrice, CategoryName
from (Categories full outer join Products
on Categories.CategoryID=Products.CategoryID)

-- 5. Z tabeli Employees podaj nazwisko pracownika i nazwisko jego szefa (wykorzysta� pole ReportsTo) - zale�no�ci s�u�bowe
select a.lastname as [Pracownik],b.LastName as [SZEF] from Employees a
inner join Employees b on b.EmployeeID=a.ReportsTo

-- 6. Z tabeli Employees podaj nazwiska wszystkich pracownik�w i nazwisko ich szefa (wykorzysta� pole ReportsTo) - zale�no�ci s�u�bowe
select a.lastname as [Pracownik],ISNULL(b.LastName, 'SZEF WSZYSTKICH SZEF�W')as [SZEF] from Employees a
left join Employees b on b.EmployeeID=a.ReportsTo

-- 7. Podaj nazwiska pracownik�w, kt�rzy nie maj� szefa
Select LastName from Employees
where ReportsTo is null

-- 8. Podaj nazw� klienta i nazwy produkt�w, kt�re kupowa� (bez powt�rze�) 
	--dla konkretnego jednego klienta o nazwie 'Wolski  Zajazd' (zapytanie powinno zwr�ci� kilka rekord�w)
select distinct p.ProductName as 'lista produktow "Wolski  Zajazd"' from Customers c
inner join Orders o on o.CustomerID=c.CustomerID
inner join [Order Details] od on od.OrderID=o.OrderID
inner join Products p on p.ProductID=od.ProductID
where CompanyName like 'Wolski  Zajazd'
order by p.ProductName

-- 9. Podaj nazw� dostwacy(Suppliers) i nazw� spedytor�w (Shippers), kt�rzy dostarczaj� produkty danego dostwcy. Podaj tak�e kraj pochodzenia dostwacy 
select distinct sup.CompanyName as 'Supplier',sup.Country,shi.CompanyName as 'Shipper' from Shippers shi
inner join Orders o on o.ShipVia=shi.ShipperID
inner join [Order Details] od on od.OrderID=o.OrderID
inner join Products p on p.ProductID=od.ProductID
inner join Suppliers sup on p.SupplierID=sup.SupplierID
order by sup.CompanyName,shi.CompanyName

--10. Podaj numer zam�wienia i nazw� towar�w sprzedanych na kazdym z nich, w jakiej ilo�ci i po jakiej cenie
select o.OrderID,p.ProductName,od.Quantity,od.UnitPrice from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
inner join Products p on p.ProductID=od.ProductID
order by o.OrderID

--11. Podaj nazwisko pracownik�w, kt�rzy nie s� jednocze�nie szefami dla innych pracownik�w.
select b.LastName from Employees a
right join Employees b on b.EmployeeID=a.ReportsTo
where a.LastName is null
order by b.LastName

--12. Znale�� pracownik�w, kt�rzy maj� szefa jako samego siebie (dodaj pracownika, kt�ry ma szefa jako siebie samego) bez klauzli WHERE
select a.lastname as [Pracownik],b.LastName as [SZEF] from Employees a
inner join Employees b on b.EmployeeID=a.ReportsTo
where a.EmployeeID=b.EmployeeID

-- kolejno�� join'�w typu outer w zapytaniu ma znaczenie przy zapytaniach ze sprze�eniami zewn�trznymi, gdy jest wi�cej ni� dwie tabele
-- (z poprzednich �wicze� mamy przynajmniej jedn� kategori� i produkt nie powi�zany ze sob�)
-- sprawdzi� ilo�� zwracanych rekord�w i dane kt�re s� zwracane
SELECT c.CategoryName, p.ProductName, s.CompanyName
	FROM Suppliers AS s INNER JOIN
	Products AS p ON s.SupplierID = p.SupplierID RIGHT JOIN
	Categories AS c ON p.CategoryID = c.CategoryID

-- sprawdzi� ilo�� zwracanych rekord�w i dane kt�re s� zwracane
SELECT c.CategoryName, p.ProductName, s.CompanyName
	FROM Categories AS c LEFT JOIN
	Products AS p ON p.CategoryID = c.CategoryID INNER JOIN
	Suppliers AS s ON s.SupplierID = p.SupplierID

-- sprawdzi� ilo�� zwracanych rekord�w i dane kt�re s� zwracane
SELECT c.CategoryName, p.ProductName, s.CompanyName
	FROM Categories AS c FULL JOIN
	Products AS p ON p.CategoryID = c.CategoryID LEFT JOIN
	Suppliers AS s ON s.SupplierID = p.SupplierID

-- ka�de z zapyta� powinno zwr�ci� inn� liczb� rekord�w
SELECT c.CategoryName, p.ProductName, s.CompanyName
	FROM Categories AS c FULL JOIN
	Products AS p ON p.CategoryID = c.CategoryID LEFT JOIN
	Suppliers AS s ON s.SupplierID = p.SupplierID

-- mo�na wykorzysta� nawiasy do okre�lenia kolejno�ci z��cze� (zapytanie j.w.)
SELECT c.CategoryName, p.ProductName, s.CompanyName
	FROM (Categories AS c FULL JOIN
	Products AS p ON p.CategoryID = c.CategoryID) LEFT JOIN
	Suppliers AS s ON s.SupplierID = p.SupplierID

--13. Czy s� kategorie w kt�rych produkty nie by�y ani razu sprzedane (lub produkty niesprzedane ale bez kategorii)
select o.OrderID,p.ProductName, c.CategoryName from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
inner join Products p on p.ProductID=od.ProductID
inner join Categories c on c.CategoryID=p.CategoryID
where c.CategoryName is null
-----------------------------------------------------------------
-- Operacje na zbiorach (union , union all, intersect, except) --
-----------------------------------------------------------------

--14. -- Dodaj trzy zestawy danych i posortuj wzgl�dem nazwy. Kolumny wynikowe powinny si� nazywa� 'Name', 'Country', 'Type'
-- pierwszy zbi�r - Zawiera nazw� dostawcy, kraj z kt�rego pochodzi oraz informacj� w kolumnie trzeciej w postaci stringu 'Supplier'
-- drugi zbi�r - Zawiera nazw� klienta, kraj z kt�rego pochodzi oraz informacj� w kolumnie trzeciej w postaci stringu 'Customer' 
-- trzeci zbi�r - Zawiera nazwisko pracownika, kraj z kt�rego pochodzi oraz informacj� w kolumnie trzeciej w postaci stringu 'Employee' 
select CompanyName as 'Name',Country,'Supplier' as 'Type' from Suppliers
union
select CompanyName,Country,'Customer' from Customers
union
select LastName,Country,'Employee' from Employees

--15. Sprawd� czy s� klienci, kt�rzy s� zarazem dostawcami (dodaj odpowiednie rekordy, kt�re zwr�c� wynik zapytania z danymi)
select CompanyName from Suppliers
intersect
select CompanyName from Customers

--16. Podaj tylko nazwy kraj�w dostawc�w i klient�w z powt�rzeniami
select Country from Suppliers
union all
select Country from Customers

--17. Czy s� dostawcy z kraj�w, w kt�rych nie ma klient�w w danej bazie danych (poda� tylko nazw� kraju)
select Country from Suppliers
except
select Country from Customers

--18. Czy s� klienci z kraj�w, w kt�rych nie ma dostawc�w w danej bazie danych (poda� tylko nazw� kraju)
select Country from Customers
except
select Country from Suppliers

-----------------------
-- Zadania dodatkowe --
----------------------- 
--19. Znale�� produkty wycofane ze sprzeda�y.
select ProductName from Products
where Discontinued=1

--20. Znale�� produkty, kt�ry osi�gn�y minimalny stan magazynowy (wykorzysta� sk�adni� case), 
	-- =0 'brak produktu'
	-- >0 and <= 10 'produkt nale�y zam�wic'
	-- >10 and <= 20 'ko�czy si� produkt'
	-- >20 'OK'
select ProductName,UnitsInStock,
	case
		when UnitsInStock = 0 then 'Brak produktu'
		when 0 < UnitsInStock and UnitsInStock <= 10 then 'Produkt nale�y zam�wic'
		when 10 < UnitsInStock and UnitsInStock <= 20 then 'Ko�czy si� produkt'
		else 'ok'
	end
from Products

--21. Czy istniej� produkty, kt�re s� aktualnie sprzedawane, dla kt�rych stan magazynu + zam�wiony towar < Poziomu minimalnego
select ProductName from Products
WHERE UnitsInStock+UnitsOnOrder<ReorderLevel

--22. Czy towary wycofne ze sprzeda�y znajduj� si� w magazynie
select ProductName from Products
WHERE Discontinued=1
and
UnitsInStock>0
select * from Products

--23. Poda� nazw� pracownika i regiony, w kt�rych realizuje sprzeda� (podajemy opr�cz nazwy regionu tak�e numer regionu)
select distinct e.LastName, r.RegionDescription from Employees e
inner join EmployeeTerritories et on e.EmployeeID=et.EmployeeID
inner join Territories t on et.TerritoryID=t.TerritoryID
inner join Region r on r.RegionID=t.RegionID
order by e.LastName

--24. Czy s� produkty, kt�rych cena sprzeda�y nie zmieni�a si� w trakcie funkcjonowania firmy
(select distinct p.ProductName,od.UnitPrice from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
inner join Products p on p.ProductID=od.ProductID
except
select ProductName,UnitPrice from Products)
intersect
select ProductName,UnitPrice from Products;
