------------------------
-- £¹czenie tabel cd. --
------------------------

-- Wykonaj dwa polecenia
insert into Categories (CategoryName) values ('A1');
insert into Products (ProductName) values ('P1');
-- czy wykonuj¹c zapytanie widzimy wprowadzone rekordy ?
select ProductName, UnitPrice, CategoryName
	from (Categories inner join Products
	on Categories.CategoryID=Products.CategoryID)

-- Podaj nazwê produktu, jego cenê i nazwê kategorii z tabel Products i Categories.
	-- chcemy tak¿e wyœwietliæ wszystkie nazwy kategorii nawet te przez przypisanych produktów 
select ProductName, UnitPrice, CategoryName
	from Categories left join Products   -- left outer join 
	on Categories.CategoryID=Products.CategoryID

-- Podaj nazwê produktu, jego cenê i nazwê kategorii z tabel Products i Categories.
	-- chcemy tak¿e wyœwietliæ wszystkie produkty nawet bez przypisanej kategorii 
select ProductName, UnitPrice, CategoryName
	from (Categories right join Products   --right outer join
	on Categories.CategoryID=Products.CategoryID)

-- Podaj nazwê produktu, jego cenê i nazwê kategorii z tabel Products i Categories.
	-- chcemy tak¿e wyœwietliæ wszystkie produkty i wszystkie kategorie 
select ProductName, UnitPrice, CategoryName
	from (Categories full outer join Products   --full outer join
	on Categories.CategoryID=Products.CategoryID)

-- 1.Podaj nazwy kategorii, które nie maj¹ przypisanych produktów.
select CategoryName
from Categories left join Products
on Categories.CategoryID=Products.CategoryID
where ProductName is null

-- 2.Podaj nazwy produktów, które nie maj¹ przypisanej kategorii (z wykorzystaniem JOIN'a) 
select ProductName
from (Categories right join Products
on Categories.CategoryID=Products.CategoryID)
where CategoryName is null

-- 3.Podaj nazwy produktów, które nie maj¹ przypisanej kategorii (bez wykorzystania JOIN'a) 
select ProductName from Products
where CategoryID is null

-- 4. Podaj nazwê produktu, jego cenê i nazwê kategorii z tabel Products i Categories.
	-- chcemy tak¿e wyœwietliæ wszystkie produkty i wszystkie kategorie 
select ProductName, UnitPrice, CategoryName
from (Categories full outer join Products
on Categories.CategoryID=Products.CategoryID)

-- 5. Z tabeli Employees podaj nazwisko pracownika i nazwisko jego szefa (wykorzystaæ pole ReportsTo) - zale¿noœci s³u¿bowe
select a.lastname as [Pracownik],b.LastName as [SZEF] from Employees a
inner join Employees b on b.EmployeeID=a.ReportsTo

-- 6. Z tabeli Employees podaj nazwiska wszystkich pracowników i nazwisko ich szefa (wykorzystaæ pole ReportsTo) - zale¿noœci s³u¿bowe
select a.lastname as [Pracownik],ISNULL(b.LastName, 'SZEF WSZYSTKICH SZEFÓW')as [SZEF] from Employees a
left join Employees b on b.EmployeeID=a.ReportsTo

-- 7. Podaj nazwiska pracowników, którzy nie maj¹ szefa
Select LastName from Employees
where ReportsTo is null

-- 8. Podaj nazwê klienta i nazwy produktów, które kupowa³ (bez powtórzeñ) 
	--dla konkretnego jednego klienta o nazwie 'Wolski  Zajazd' (zapytanie powinno zwróciæ kilka rekordów)
select distinct p.ProductName as 'lista produktow "Wolski  Zajazd"' from Customers c
inner join Orders o on o.CustomerID=c.CustomerID
inner join [Order Details] od on od.OrderID=o.OrderID
inner join Products p on p.ProductID=od.ProductID
where CompanyName like 'Wolski  Zajazd'
order by p.ProductName

-- 9. Podaj nazwê dostwacy(Suppliers) i nazwê spedytorów (Shippers), którzy dostarczaj¹ produkty danego dostwcy. Podaj tak¿e kraj pochodzenia dostwacy 
select distinct sup.CompanyName as 'Supplier',sup.Country,shi.CompanyName as 'Shipper' from Shippers shi
inner join Orders o on o.ShipVia=shi.ShipperID
inner join [Order Details] od on od.OrderID=o.OrderID
inner join Products p on p.ProductID=od.ProductID
inner join Suppliers sup on p.SupplierID=sup.SupplierID
order by sup.CompanyName,shi.CompanyName

--10. Podaj numer zamówienia i nazwê towarów sprzedanych na kazdym z nich, w jakiej iloœci i po jakiej cenie
select o.OrderID,p.ProductName,od.Quantity,od.UnitPrice from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
inner join Products p on p.ProductID=od.ProductID
order by o.OrderID

--11. Podaj nazwisko pracowników, którzy nie s¹ jednoczeœnie szefami dla innych pracowników.
select b.LastName from Employees a
right join Employees b on b.EmployeeID=a.ReportsTo
where a.LastName is null
order by b.LastName

--12. ZnaleŸæ pracowników, którzy maj¹ szefa jako samego siebie (dodaj pracownika, który ma szefa jako siebie samego) bez klauzli WHERE
select a.lastname as [Pracownik],b.LastName as [SZEF] from Employees a
inner join Employees b on b.EmployeeID=a.ReportsTo
where a.EmployeeID=b.EmployeeID

-- kolejnoœæ join'ów typu outer w zapytaniu ma znaczenie przy zapytaniach ze sprze¿eniami zewnêtrznymi, gdy jest wiêcej ni¿ dwie tabele
-- (z poprzednich æwiczeñ mamy przynajmniej jedn¹ kategoriê i produkt nie powi¹zany ze sob¹)
-- sprawdziæ iloœæ zwracanych rekordów i dane które s¹ zwracane
SELECT c.CategoryName, p.ProductName, s.CompanyName
	FROM Suppliers AS s INNER JOIN
	Products AS p ON s.SupplierID = p.SupplierID RIGHT JOIN
	Categories AS c ON p.CategoryID = c.CategoryID

-- sprawdziæ iloœæ zwracanych rekordów i dane które s¹ zwracane
SELECT c.CategoryName, p.ProductName, s.CompanyName
	FROM Categories AS c LEFT JOIN
	Products AS p ON p.CategoryID = c.CategoryID INNER JOIN
	Suppliers AS s ON s.SupplierID = p.SupplierID

-- sprawdziæ iloœæ zwracanych rekordów i dane które s¹ zwracane
SELECT c.CategoryName, p.ProductName, s.CompanyName
	FROM Categories AS c FULL JOIN
	Products AS p ON p.CategoryID = c.CategoryID LEFT JOIN
	Suppliers AS s ON s.SupplierID = p.SupplierID

-- ka¿de z zapytañ powinno zwróciæ inn¹ liczbê rekordów
SELECT c.CategoryName, p.ProductName, s.CompanyName
	FROM Categories AS c FULL JOIN
	Products AS p ON p.CategoryID = c.CategoryID LEFT JOIN
	Suppliers AS s ON s.SupplierID = p.SupplierID

-- mo¿na wykorzystaæ nawiasy do okreœlenia kolejnoœci z³¹czeñ (zapytanie j.w.)
SELECT c.CategoryName, p.ProductName, s.CompanyName
	FROM (Categories AS c FULL JOIN
	Products AS p ON p.CategoryID = c.CategoryID) LEFT JOIN
	Suppliers AS s ON s.SupplierID = p.SupplierID

--13. Czy s¹ kategorie w których produkty nie by³y ani razu sprzedane (lub produkty niesprzedane ale bez kategorii)
select o.OrderID,p.ProductName, c.CategoryName from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
inner join Products p on p.ProductID=od.ProductID
inner join Categories c on c.CategoryID=p.CategoryID
where c.CategoryName is null
-----------------------------------------------------------------
-- Operacje na zbiorach (union , union all, intersect, except) --
-----------------------------------------------------------------

--14. -- Dodaj trzy zestawy danych i posortuj wzglêdem nazwy. Kolumny wynikowe powinny siê nazywaæ 'Name', 'Country', 'Type'
-- pierwszy zbiór - Zawiera nazwê dostawcy, kraj z którego pochodzi oraz informacjê w kolumnie trzeciej w postaci stringu 'Supplier'
-- drugi zbiór - Zawiera nazwê klienta, kraj z którego pochodzi oraz informacjê w kolumnie trzeciej w postaci stringu 'Customer' 
-- trzeci zbiór - Zawiera nazwisko pracownika, kraj z którego pochodzi oraz informacjê w kolumnie trzeciej w postaci stringu 'Employee' 
select CompanyName as 'Name',Country,'Supplier' as 'Type' from Suppliers
union
select CompanyName,Country,'Customer' from Customers
union
select LastName,Country,'Employee' from Employees

--15. SprawdŸ czy s¹ klienci, którzy s¹ zarazem dostawcami (dodaj odpowiednie rekordy, które zwróc¹ wynik zapytania z danymi)
select CompanyName from Suppliers
intersect
select CompanyName from Customers

--16. Podaj tylko nazwy krajów dostawców i klientów z powtórzeniami
select Country from Suppliers
union all
select Country from Customers

--17. Czy s¹ dostawcy z krajów, w których nie ma klientów w danej bazie danych (podaæ tylko nazwê kraju)
select Country from Suppliers
except
select Country from Customers

--18. Czy s¹ klienci z krajów, w których nie ma dostawców w danej bazie danych (podaæ tylko nazwê kraju)
select Country from Customers
except
select Country from Suppliers

-----------------------
-- Zadania dodatkowe --
----------------------- 
--19. ZnaleŸæ produkty wycofane ze sprzeda¿y.
select ProductName from Products
where Discontinued=1

--20. ZnaleŸæ produkty, który osi¹gnê³y minimalny stan magazynowy (wykorzystaæ sk³adniê case), 
	-- =0 'brak produktu'
	-- >0 and <= 10 'produkt nale¿y zamówic'
	-- >10 and <= 20 'koñczy siê produkt'
	-- >20 'OK'
select ProductName,UnitsInStock,
	case
		when UnitsInStock = 0 then 'Brak produktu'
		when 0 < UnitsInStock and UnitsInStock <= 10 then 'Produkt nale¿y zamówic'
		when 10 < UnitsInStock and UnitsInStock <= 20 then 'Koñczy siê produkt'
		else 'ok'
	end
from Products

--21. Czy istniej¹ produkty, które s¹ aktualnie sprzedawane, dla których stan magazynu + zamówiony towar < Poziomu minimalnego
select ProductName from Products
WHERE UnitsInStock+UnitsOnOrder<ReorderLevel

--22. Czy towary wycofne ze sprzeda¿y znajduj¹ siê w magazynie
select ProductName from Products
WHERE Discontinued=1
and
UnitsInStock>0
select * from Products

--23. Podaæ nazwê pracownika i regiony, w których realizuje sprzeda¿ (podajemy oprócz nazwy regionu tak¿e numer regionu)
select distinct e.LastName, r.RegionDescription from Employees e
inner join EmployeeTerritories et on e.EmployeeID=et.EmployeeID
inner join Territories t on et.TerritoryID=t.TerritoryID
inner join Region r on r.RegionID=t.RegionID
order by e.LastName

--24. Czy s¹ produkty, których cena sprzeda¿y nie zmieni³a siê w trakcie funkcjonowania firmy
(select distinct p.ProductName,od.UnitPrice from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
inner join Products p on p.ProductID=od.ProductID
except
select ProductName,UnitPrice from Products)
intersect
select ProductName,UnitPrice from Products;
