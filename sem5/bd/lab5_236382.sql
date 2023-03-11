------------------------------------------------------
-- Agregacja danych, Group by, Having, Rollup, Cube --
------------------------------------------------------

select * from Suppliers

-- Ile jest dostawców i ilu dostawców ma podany w bazie danych faks  
select COUNT(*), COUNT(fax) from Suppliers

-- Podaj nazwy pañstw dostawców bez powtórzeñ
select distinct country from Suppliers

-- Ile jest pañstw gdzie znajduj¹ siê nasi dostawcy (jedna liczba)
select count(distinct country) from Suppliers

-- 1. Ile jest produktów w tabeli Products (count), wartoœæ maksymalna ceny (max), minimalna cena (bez zera)(min) i wartoœæ œrednia (avg) (Dodaj produkt 'Prod X' z cen¹ NULL)
select COUNT(ProductID) count,max(UnitPrice) max,
min(UnitPrice) min,avg(UnitPrice) avg
from Products
where UnitPrice>0
-- 2. Liczymy dodatkowo wartoœæ œredni¹ jako suma podzielona przez liczbê produktów oraz oblicona z wykorzystaniem AVG - porównaæ wyniki.
select sum(UnitPrice)/COUNT(ProductID) avgn,avg(UnitPrice) avg
from Products
-- 3. Jaka jest wartoœæ towaru w magazynie
select sum(p.UnitPrice*p.UnitsInStock) from Products p
-- 4. Jaka jest ca³kowita sprzeda¿ (bez upustów, z upustami, same upusty)
select sum(UnitPrice*Quantity) bez,sum(UnitPrice*Quantity-(UnitPrice*Quantity*Discount))as 'z'
,sum(UnitPrice*Quantity*Discount) as 'upust'
from [Order Details]

-- 5. Ile firm jest w danym kraju
select country,count(SupplierID) from Suppliers 
group by Country

-- 6. Ile firm jest w danym kraju zaczynaj¹cych siê na litery od a do f.
select country,count(SupplierID) from Suppliers 
where CompanyName like '[a-f]%'
group by Country

-- 7. Ile firm jest w danym kraju zaczynaj¹cych siê na litery od a do f. Wyœwietl te kraje gdzie liczba firm jest >=3 (GROUP BY, HAVING)
 select country,count(SupplierID) ile from Suppliers 
where CompanyName like '[a-f]%'
group by Country
having count(SupplierID)>=3
union
select Country,count(CustomerID) from Customers
where CompanyName like '[a-f]%'
group by Country
having count(CustomerID)>=3

-- 8. Podaj nazwê kraju, z których pochodz¹ pracownicy oraz ilu ich jest w danym kraju (tabela Employees) oraz iloœæ pracowników jest sumarycznie (jedno zapytanie) (jedno zapytanie z opcj¹ rollup)
select isnull(Country,'suma') kraj,count(country) ile from Employees
group by rollup (country)

-- Podaj na jak¹ kwotê znajduje sie towaru w magazynie
select sum(UnitPrice*UnitsInStock) from Products

-- Podaj na jak¹ kwotê znajduje sie towaru w magazynie w ka¿dej kategorii (podajemy nazwê kategorii) oraz we wszystkich kategoriach (jedno zapytanie z opcj¹ rollup)
SELECT  CategoryName, sum(UnitPrice*UnitsInStock)
	FROM (Categories AS c INNER JOIN
	Products AS p ON c.CategoryID = p.CategoryID)
	group by rollup (CategoryName)
	ORDER BY CategoryName

-- Podaj na jak¹ kwotê znajduje sie towaru w magazynie w ka¿dej kategorii categoryid (s¹ produkty bez kategorii i te¿ ma byc wyœwietlona ich kwota)
			-- funkcja CAST (sprawdzamy w dokumentacji)
SELECT  isnull(cast(CategoryID as varchar),'brak kategorii'), sum(UnitPrice*UnitsInStock)
	FROM Products
	group by CategoryID
	ORDER BY CategoryID
	--funkcja CONVERT (sprawdzamy w dokumentacji)
SELECT  isnull(convert(varchar, CategoryID),'brak kategorii') numer, sum(UnitPrice*UnitsInStock)
	FROM Products
	group by rollup(isnull(convert(varchar, CategoryID),'brak kategorii'))
	ORDER BY 1

-- 9. Podaj na jak¹ kwotê znajduje sie towaru w magazynie w ka¿dej kategorii categoryname (s¹ produkty bez kategorii i te¿ ma byc wyœwietlona ich kwota)
select c.CategoryName,sum(p.UnitPrice*p.UnitsInStock) suma from Products p
inner join Categories c on p.CategoryID=c.CategoryID
group by c.CategoryName

-- 10. Podaj sumaryczn¹ sprzeda¿ - tabela [order details] bez upustów
select sum(UnitPrice*Quantity) suma from [Order Details]

-- 11. Podaj na jak¹ kwotê sprzedano towaru w ka¿dej kategorii  (podaj wszystkie kategorie)
select c.CategoryName, sum(od.UnitPrice*od.Quantity) from [Order Details] od
inner join Products p on p.ProductID=od.ProductID
inner join Categories c on c.CategoryID=p.CategoryID
group by c.CategoryName

-- 12. Podaj na jak¹ kwotê sprzedano towaru w ka¿dej kategorii - podajemy tylko te kategorie w których sprzedano towaru za kwotê powy¿ej 200 000.
select c.CategoryName, sum(od.UnitPrice*od.Quantity) suma from [Order Details] od
inner join Products p on p.ProductID=od.ProductID
inner join Categories c on c.CategoryID=p.CategoryID
group by c.CategoryName
having sum(od.UnitPrice*od.Quantity)>200000

-- 13. Podaj ile rodzajów produktów by³o sprzedanych w kazdej kategorii
select c.CategoryName,count(od.orderid) from [Order Details] od
inner join Products p on p.ProductID=od.ProductID
inner join Categories c on c.CategoryID=p.CategoryID
group by c.CategoryName
-- 14. Porównujemy - -- nazwê kategorii, nazwê produktu i jego sprzeda¿ (wykorzystaæ cube nastêpnie rollup i znajdujemy ró¿nicê odejmuj¹c te zbiory)
select p.ProductName,c.CategoryName,sum(od.Quantity*od.UnitPrice) from [Order Details] od
inner join Products p on p.ProductID=od.ProductID
inner join Categories c on c.CategoryID=p.CategoryID
group by p.ProductName,c.CategoryName
order by p.ProductName

-- 15. Który z pracowników sprzeda³ towarów za najwiêksz¹ kwotê
select e.LastName+' '+e.FirstName,sum(od.UnitPrice*od.Quantity) suma from Employees e
inner join Orders o on o.EmployeeID=e.EmployeeID
inner join [Order Details] od on od.OrderID=o.OrderID
group by e.LastName+' '+e.FirstName
order by sum(od.UnitPrice*od.Quantity) desc

-- 16. Podaj klienta, nazwê kategorii i sumaryczn¹ jego sprzeda¿ w ka¿dej z nich
select c.CompanyName,ca.CategoryName,sum(od.UnitPrice*Quantity) suma from Customers c
inner join Orders o on o.CustomerID=c.CustomerID
inner join [Order Details] od on od.OrderID=o.OrderID
inner join Products p on p.ProductID=od.ProductID
inner join Categories ca on ca.CategoryID=p.CategoryID
group by rollup (ca.CategoryName),c.CompanyName
order by c.CompanyName

-- 17. Jaki spedytor przewióz³ najwiêksz¹ wartoœæ sprzedanych towarów
select s.CompanyName,sum(od.Quantity) from Shippers s
inner join Orders o on o.ShipVia=s.ShipperID
inner join [Order Details] od on od.OrderID=o.OrderID
group by s.CompanyName
order by sum(od.Quantity) desc

-- 18. Wykorzystaæ funkcjê grouping do zapytania podaj¹cego nazwê kategorii, nazwê produktu i jego sprzeda¿
select c.CategoryName,p.ProductName,sum(od.Quantity*od.UnitPrice),GROUPING(c.CategoryName) from [Order Details] od
inner join Products p on p.ProductID=od.ProductID
inner join Categories c on c.CategoryID=p.CategoryID
group by (c.CategoryName),p.ProductName with rollup



------ funkcje, agregacje:
------------------------------------------------------------------------------------------
-- Agregacja danych, funkcje zwi¹zan¹ z dat¹, zapytania z podzapytaniami, zapytania CTE --
------------------------------------------------------------------------------------------

-- 1. Podaj aktualn¹ datê systemow¹
select GETDATE()

-- 2. Jak dodaæ jedn¹ godzinê do daty systemowej
select dateadd(hour,1,GETDATE())

-- 3. Podaj z daty systemowej osobno rok, miesi¹c i dzieñ podany jako typ integer (YEAR, MONTH, DAY)
select year(GETDATE()) year,MONTH(GETDATE())month,day(GETDATE())day

-- 4. Podaj z daty systemowej osobno rok, miesi¹c i dzieñ podany jako typ integer (funkcja DATEPART)
select DATEPART(year, GETDATE()) year,DATEPART(MONTH, GETDATE()) MONTH,DATEPART(day, GETDATE()) day

-- 5. Podaj z daty systemowej osobno godzinê, miinuty i sekundy jako typ integer (funkcja DATEPART)
select DATEPART(HOUR, GETDATE()) HOUR,DATEPART(MINUTE, GETDATE()) MINUTE,DATEPART(SECOND, GETDATE()) SECOND

-- 6. Podaj z daty systemowej osobno rok, miesi¹c i dzieñ podany jako typ char (funkcja DATENAME)
select datename(year, GETDATE()) year,datename(MONTH, GETDATE()) MONTH,datename(day, GETDATE()) day

-- 7. Podaj nazwê aktualnego miesi¹ca podanego jako nazwa oraz dzieñ w postaci nazwy (kwiecieñ, poniedzia³ek) oraz (april, monday)
   -- select @@LANGUAGE
   -- set language POLISH
set language us_english
select @@LANGUAGE,datename(MONTH, GETDATE()) MONTH,datename(WEEKDAY, GETDATE()) WEEKDAY
set language POLISH
select @@LANGUAGE,datename(MONTH, GETDATE()) MONTH,datename(WEEKDAY, GETDATE()) WEEKDAY

-- 8. Ile lat up³yne³o od ostatniego zamówienia (funkcja DATEDIFF)
select datediff(YEAR,max(OrderDate),GETDATE()) from Orders

-- 9. Ile miesiêcy up³yne³o od ostatniego zamówienia (funkcja DATEDIFF)
select datediff(MONTH,max(OrderDate),GETDATE()) from Orders

-- 10. Dodaj do bie¿¹cej daty 3 miesi¹ce (funkcja DATEADD)
select dateadd(MONTH,3,GETDATE())

-- 11. W jaki dzieñ obchodzimy w tym roku urodziny (korzystamy z funkcji CONVERT do zamiany naszej daty tekstowej na typ DATETIME lub DATE)
set language POLISH
select DATENAME(WEEKDAY,'2022/09/10')

-- 12. W jaki dzieñ tygodnia przypada w przysz³ym roku w ostatni dzieñ lutego oraz ile dni ma luty w przysz³ym roku 
   --(korzystamy z funkcji CONVERT do zamiany naszej daty tekstowej na typ datetime bez korzystania z funkcji EOMONTH()
   --a nastêpnie z korzystamy z funkcji EOMONTH())
set language POLISH
select DATENAME(WEEKDAY,EOMONTH('2023/02/10')) [dzien tygodnia],DATEPART(DAY, EOMONTH('2023/02/10')) [ile dni]

-- 13. W jakich kolejnych latach by³a realizowana sprzeda¿ w bazie NORTHWIND
select DATEPART(year,OrderDate) from Orders
group by DATEPART(year,OrderDate)
order by 1 desc

-- 14. Podaj sprzeda¿ towarów, w ka¿dym roku dzia³ania firmy (bez upustów)
select DATEPART(year,o.OrderDate) rok,sum(od.UnitPrice*od.Quantity) suma from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
group by DATEPART(year,o.OrderDate)
order by 1 desc

-- 15. Podaj sprzeda¿ towarów w ka¿dym roku i miesi¹cu dzia³ania firmy
   -- rok i miesi¹c podajemy w jednej kolumnie 
select FORMAT(o.OrderDate, 'yyyy-MM') rok,sum(od.UnitPrice*od.Quantity) suma from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
group by FORMAT(o.OrderDate, 'yyyy-MM')
order by FORMAT(o.OrderDate, 'yyyy-MM')

-- 16. Podaj sprzeda¿ towarów w ka¿dym roku i miesi¹cu dzia³ania firmy
   -- rok i miesi¹c podajemy w osobnych kolumnach)
select FORMAT(o.OrderDate, 'yyyy') rok,FORMAT(o.OrderDate, 'MM') miesiac,sum(od.UnitPrice*od.Quantity) suma from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
group by FORMAT(o.OrderDate, 'yyyy'),FORMAT(o.OrderDate, 'MM')
order by FORMAT(o.OrderDate, 'yyyy'),FORMAT(o.OrderDate, 'MM')

-- 17. Do ostatniego zapytania do³ó¿ klauzulê CUBE i ROLLUP i porównaj wyniki obu zapytañ (EXCEPT)
select FORMAT(o.OrderDate, 'yyyy') rok,FORMAT(o.OrderDate, 'MM') miesiac,sum(od.UnitPrice*od.Quantity) suma from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
group by cube (FORMAT(o.OrderDate, 'yyyy'),FORMAT(o.OrderDate, 'MM'))
order by FORMAT(o.OrderDate, 'yyyy'),FORMAT(o.OrderDate, 'MM')

EXCEPT

select FORMAT(o.OrderDate, 'yyyy') rok,FORMAT(o.OrderDate, 'MM') miesiac,sum(od.UnitPrice*od.Quantity) suma from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
group by rollup (FORMAT(o.OrderDate, 'yyyy'),FORMAT(o.OrderDate, 'MM'))
order by FORMAT(o.OrderDate, 'yyyy'),FORMAT(o.OrderDate, 'MM');

-- 18. Podaj numery zamówieñ, ich datê oraz ca³kowit¹ wartoœæ (orderid, orderdate, unitprice*quantity) 
	-- oraz posortuj wzglêdem ca³kowitej wartoœci
	select o.OrderID,FORMAT(o.OrderDate, 'dd-MM-yyyy'),sum(od.UnitPrice*od.Quantity) from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
group by o.OrderID,FORMAT(o.OrderDate, 'dd-MM-yyyy')
order by 3 desc

-- 19. Podaj numery zamówieñ, ich datê oraz ca³kowit¹ wartoœæ, 
	-- które by³y zrealizowane na najwiêksz¹ wartoœæ 
select top 1 o.OrderID,FORMAT(o.OrderDate, 'dd-MM-yyyy') data,sum(od.UnitPrice*od.Quantity) as 'suma' from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
group by o.OrderID,FORMAT(o.OrderDate, 'dd-MM-yyyy')
order by 3 desc

-- 20. Podaj numery zamówieñ, ich datê oraz ca³kowit¹ wartoœæ, 
	-- które by³y zrealizowane na najmniejsz¹ wartoœæ(bez 0)
select top 1 o.OrderID,FORMAT(o.OrderDate, 'dd-MM-yyyy') data,sum(od.UnitPrice*od.Quantity) as 'suma' from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
group by o.OrderID,FORMAT(o.OrderDate, 'dd-MM-yyyy')
order by 3 

-- 21. Podaj numery zamówieñ, ich datê oraz ca³kowit¹ wartoœæ, 
	-- które by³y zrealizowane na najwiêksz¹ wartoœæ i na najmniejsz¹ wartoœæ(bez 0) w jednym zapytaniu.
select top 1 o.OrderID,o.OrderDate data,sum(od.UnitPrice*od.Quantity) as 'suma' from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
group by o.OrderID,o.OrderDate
order by 3

select top 1 o.OrderID,o.OrderDate data,sum(od.UnitPrice*od.Quantity) as 'suma' from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
group by o.OrderID,o.OrderDate
order by 3 desc

-- 22. Podaj numery zamówieñ, ich datê oraz ca³kowit¹ wartoœæ, 
	-- które by³y zrealizowane na najwiêksz¹ wartoœæ i na najmniejsz¹ wartoœæ(bez 0) w jednym zapytaniu.
	-- zapytania typu CTE zaczynaj¹ce siê klauzul¹ WITH

-- 23. Podaj najdro¿szy i najtañszy z produktów (bez klauzuli TOP ani FETCH FIRST) (Podzapytania)

-- 24. Podaj najdro¿szy i najtañszy z produktów (bez klauzuli TOP ani FETCH FIRST) (Podzapytania)
	-- Zapytanie typu CTE zaczynaj¹c¹ siê na WITH

-- 25. Podaj numery zamówieñ, ich datê oraz ca³kowit¹ wartoœæ, 
	-- które by³y zrealizowane na najwiêksz¹ wartoœæ i na najmniejsz¹ wartoœæ(bez 0) w jednym zapytaniu.
	-- wykonaj powy¿sze zapytanie bez klauzuli top tylko z wykorzystaniem podzapytañ

-- 26. Skasuj produkty nale¿¹ce do kategorii CATX (nie znamy categoryid tylko categoryname)
	-- (najpierw dodaæ kategorie CATX i póŸniej 2 produkty nale¿¹ce do tej kategorii)
select * from Products
DELETE p FROM Products p
INNER join Categories c
on c.CategoryID=p.CategoryID
WHERE c.CategoryName='CATX'
select * from Products
-- 27. Jaka jest sprzeda¿ sumaryczna w roku 1996 i 1997 (bez group by)
select distinct FORMAT(o.OrderDate,'yyyy') rok,sum(od.Quantity*od.UnitPrice) OVER(PARTITION By FORMAT(o.OrderDate,'yyyy')) from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
-- 28. Podaj nazwê klienta, rok sprzeda¿y oraz wartoœæ sprzeda¿y w danym roku.
select c.CompanyName ,year(o.OrderDate),sum(od.Quantity*od.UnitPrice) from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
inner join Customers c on c.CustomerID=o.CustomerID
group by c.CompanyName,year(o.OrderDate)
order by 1
-- 29. W jaki dzieñ tygodnia sumaryczenie sprzedano towaru za najwêksz¹ kwotê.
select top 1 datename(WEEKDAY,o.OrderDate),sum(od.Quantity*od.UnitPrice) from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
group by datename(WEEKDAY,o.OrderDate)
order by 2 desc
-- 30. Podaj nazwê kategorii oraz rok w którym w danej kategorii by³a najwiêksza sprzeda¿.
use Northwind
select nazwa,max(suma) 
from(
select c.CategoryName as 'nazwa',YEAR(o.OrderDate) as 'rok',sum(od.UnitPrice*od.Quantity) as'suma' from Orders o 
inner join [Order Details] od
on o.OrderID=od.OrderID
inner join Products p
on p.ProductID=od.ProductID
inner join Categories c
on c.CategoryID=p.CategoryID
group by c.CategoryName,year(o.OrderDate)
) a
group by nazwa
order by 2 desc
-- 31. W którym roku by³a nawy¿sza sprzeda¿.
select top 1 YEAR(o.OrderDate) rok,sum(od.UnitPrice*od.Quantity) wartosc from Orders o 
inner join [Order Details] od
on o.OrderID=od.OrderID
group by yEAR(o.OrderDate)
order by 2
-- 32. Który z pracowników obs³u¿y³ klientów za najwiêksz¹ kwotê.
select top 1 e.FirstName+' '+e.LastName as 'pracownik',sum(od.Quantity*od.UnitPrice) suma from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
inner join Employees e on e.EmployeeID=o.EmployeeID
group by e.FirstName+' '+e.LastName
order by 2 desc