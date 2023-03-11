------------------------------------------------------
-- Agregacja danych, Group by, Having, Rollup, Cube --
------------------------------------------------------

select * from Suppliers

-- Ile jest dostawc�w i ilu dostawc�w ma podany w bazie danych faks  
select COUNT(*), COUNT(fax) from Suppliers

-- Podaj nazwy pa�stw dostawc�w bez powt�rze�
select distinct country from Suppliers

-- Ile jest pa�stw gdzie znajduj� si� nasi dostawcy (jedna liczba)
select count(distinct country) from Suppliers

-- 1. Ile jest produkt�w w tabeli Products (count), warto�� maksymalna ceny (max), minimalna cena (bez zera)(min) i warto�� �rednia (avg) (Dodaj produkt 'Prod X' z cen� NULL)
select COUNT(ProductID) count,max(UnitPrice) max,
min(UnitPrice) min,avg(UnitPrice) avg
from Products
where UnitPrice>0
-- 2. Liczymy dodatkowo warto�� �redni� jako suma podzielona przez liczb� produkt�w oraz oblicona z wykorzystaniem AVG - por�wna� wyniki.
select sum(UnitPrice)/COUNT(ProductID) avgn,avg(UnitPrice) avg
from Products
-- 3. Jaka jest warto�� towaru w magazynie
select sum(p.UnitPrice*p.UnitsInStock) from Products p
-- 4. Jaka jest ca�kowita sprzeda� (bez upust�w, z upustami, same upusty)
select sum(UnitPrice*Quantity) bez,sum(UnitPrice*Quantity-(UnitPrice*Quantity*Discount))as 'z'
,sum(UnitPrice*Quantity*Discount) as 'upust'
from [Order Details]

-- 5. Ile firm jest w danym kraju
select country,count(SupplierID) from Suppliers 
group by Country

-- 6. Ile firm jest w danym kraju zaczynaj�cych si� na litery od a do f.
select country,count(SupplierID) from Suppliers 
where CompanyName like '[a-f]%'
group by Country

-- 7. Ile firm jest w danym kraju zaczynaj�cych si� na litery od a do f. Wy�wietl te kraje gdzie liczba firm jest >=3 (GROUP BY, HAVING)
 select country,count(SupplierID) ile from Suppliers 
where CompanyName like '[a-f]%'
group by Country
having count(SupplierID)>=3
union
select Country,count(CustomerID) from Customers
where CompanyName like '[a-f]%'
group by Country
having count(CustomerID)>=3

-- 8. Podaj nazw� kraju, z kt�rych pochodz� pracownicy oraz ilu ich jest w danym kraju (tabela Employees) oraz ilo�� pracownik�w jest sumarycznie (jedno zapytanie) (jedno zapytanie z opcj� rollup)
select isnull(Country,'suma') kraj,count(country) ile from Employees
group by rollup (country)

-- Podaj na jak� kwot� znajduje sie towaru w magazynie
select sum(UnitPrice*UnitsInStock) from Products

-- Podaj na jak� kwot� znajduje sie towaru w magazynie w ka�dej kategorii (podajemy nazw� kategorii) oraz we wszystkich kategoriach (jedno zapytanie z opcj� rollup)
SELECT  CategoryName, sum(UnitPrice*UnitsInStock)
	FROM (Categories AS c INNER JOIN
	Products AS p ON c.CategoryID = p.CategoryID)
	group by rollup (CategoryName)
	ORDER BY CategoryName

-- Podaj na jak� kwot� znajduje sie towaru w magazynie w ka�dej kategorii categoryid (s� produkty bez kategorii i te� ma byc wy�wietlona ich kwota)
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

-- 9. Podaj na jak� kwot� znajduje sie towaru w magazynie w ka�dej kategorii categoryname (s� produkty bez kategorii i te� ma byc wy�wietlona ich kwota)
select c.CategoryName,sum(p.UnitPrice*p.UnitsInStock) suma from Products p
inner join Categories c on p.CategoryID=c.CategoryID
group by c.CategoryName

-- 10. Podaj sumaryczn� sprzeda� - tabela [order details] bez upust�w
select sum(UnitPrice*Quantity) suma from [Order Details]

-- 11. Podaj na jak� kwot� sprzedano towaru w ka�dej kategorii  (podaj wszystkie kategorie)
select c.CategoryName, sum(od.UnitPrice*od.Quantity) from [Order Details] od
inner join Products p on p.ProductID=od.ProductID
inner join Categories c on c.CategoryID=p.CategoryID
group by c.CategoryName

-- 12. Podaj na jak� kwot� sprzedano towaru w ka�dej kategorii - podajemy tylko te kategorie w kt�rych sprzedano towaru za kwot� powy�ej 200 000.
select c.CategoryName, sum(od.UnitPrice*od.Quantity) suma from [Order Details] od
inner join Products p on p.ProductID=od.ProductID
inner join Categories c on c.CategoryID=p.CategoryID
group by c.CategoryName
having sum(od.UnitPrice*od.Quantity)>200000

-- 13. Podaj ile rodzaj�w produkt�w by�o sprzedanych w kazdej kategorii
select c.CategoryName,count(od.orderid) from [Order Details] od
inner join Products p on p.ProductID=od.ProductID
inner join Categories c on c.CategoryID=p.CategoryID
group by c.CategoryName
-- 14. Por�wnujemy - -- nazw� kategorii, nazw� produktu i jego sprzeda� (wykorzysta� cube nast�pnie rollup i znajdujemy r�nic� odejmuj�c te zbiory)
select p.ProductName,c.CategoryName,sum(od.Quantity*od.UnitPrice) from [Order Details] od
inner join Products p on p.ProductID=od.ProductID
inner join Categories c on c.CategoryID=p.CategoryID
group by p.ProductName,c.CategoryName
order by p.ProductName

-- 15. Kt�ry z pracownik�w sprzeda� towar�w za najwi�ksz� kwot�
select e.LastName+' '+e.FirstName,sum(od.UnitPrice*od.Quantity) suma from Employees e
inner join Orders o on o.EmployeeID=e.EmployeeID
inner join [Order Details] od on od.OrderID=o.OrderID
group by e.LastName+' '+e.FirstName
order by sum(od.UnitPrice*od.Quantity) desc

-- 16. Podaj klienta, nazw� kategorii i sumaryczn� jego sprzeda� w ka�dej z nich
select c.CompanyName,ca.CategoryName,sum(od.UnitPrice*Quantity) suma from Customers c
inner join Orders o on o.CustomerID=c.CustomerID
inner join [Order Details] od on od.OrderID=o.OrderID
inner join Products p on p.ProductID=od.ProductID
inner join Categories ca on ca.CategoryID=p.CategoryID
group by rollup (ca.CategoryName),c.CompanyName
order by c.CompanyName

-- 17. Jaki spedytor przewi�z� najwi�ksz� warto�� sprzedanych towar�w
select s.CompanyName,sum(od.Quantity) from Shippers s
inner join Orders o on o.ShipVia=s.ShipperID
inner join [Order Details] od on od.OrderID=o.OrderID
group by s.CompanyName
order by sum(od.Quantity) desc

-- 18. Wykorzysta� funkcj� grouping do zapytania podaj�cego nazw� kategorii, nazw� produktu i jego sprzeda�
select c.CategoryName,p.ProductName,sum(od.Quantity*od.UnitPrice),GROUPING(c.CategoryName) from [Order Details] od
inner join Products p on p.ProductID=od.ProductID
inner join Categories c on c.CategoryID=p.CategoryID
group by (c.CategoryName),p.ProductName with rollup



------ funkcje, agregacje:
------------------------------------------------------------------------------------------
-- Agregacja danych, funkcje zwi�zan� z dat�, zapytania z podzapytaniami, zapytania CTE --
------------------------------------------------------------------------------------------

-- 1. Podaj aktualn� dat� systemow�
select GETDATE()

-- 2. Jak doda� jedn� godzin� do daty systemowej
select dateadd(hour,1,GETDATE())

-- 3. Podaj z daty systemowej osobno rok, miesi�c i dzie� podany jako typ integer (YEAR, MONTH, DAY)
select year(GETDATE()) year,MONTH(GETDATE())month,day(GETDATE())day

-- 4. Podaj z daty systemowej osobno rok, miesi�c i dzie� podany jako typ integer (funkcja DATEPART)
select DATEPART(year, GETDATE()) year,DATEPART(MONTH, GETDATE()) MONTH,DATEPART(day, GETDATE()) day

-- 5. Podaj z daty systemowej osobno godzin�, miinuty i sekundy jako typ integer (funkcja DATEPART)
select DATEPART(HOUR, GETDATE()) HOUR,DATEPART(MINUTE, GETDATE()) MINUTE,DATEPART(SECOND, GETDATE()) SECOND

-- 6. Podaj z daty systemowej osobno rok, miesi�c i dzie� podany jako typ char (funkcja DATENAME)
select datename(year, GETDATE()) year,datename(MONTH, GETDATE()) MONTH,datename(day, GETDATE()) day

-- 7. Podaj nazw� aktualnego miesi�ca podanego jako nazwa oraz dzie� w postaci nazwy (kwiecie�, poniedzia�ek) oraz (april, monday)
   -- select @@LANGUAGE
   -- set language POLISH
set language us_english
select @@LANGUAGE,datename(MONTH, GETDATE()) MONTH,datename(WEEKDAY, GETDATE()) WEEKDAY
set language POLISH
select @@LANGUAGE,datename(MONTH, GETDATE()) MONTH,datename(WEEKDAY, GETDATE()) WEEKDAY

-- 8. Ile lat up�yne�o od ostatniego zam�wienia (funkcja DATEDIFF)
select datediff(YEAR,max(OrderDate),GETDATE()) from Orders

-- 9. Ile miesi�cy up�yne�o od ostatniego zam�wienia (funkcja DATEDIFF)
select datediff(MONTH,max(OrderDate),GETDATE()) from Orders

-- 10. Dodaj do bie��cej daty 3 miesi�ce (funkcja DATEADD)
select dateadd(MONTH,3,GETDATE())

-- 11. W jaki dzie� obchodzimy w tym roku urodziny (korzystamy z funkcji CONVERT do zamiany naszej daty tekstowej na typ DATETIME lub DATE)
set language POLISH
select DATENAME(WEEKDAY,'2022/09/10')

-- 12. W jaki dzie� tygodnia przypada w przysz�ym roku w ostatni dzie� lutego oraz ile dni ma luty w przysz�ym roku 
   --(korzystamy z funkcji CONVERT do zamiany naszej daty tekstowej na typ datetime bez korzystania z funkcji EOMONTH()
   --a nast�pnie z korzystamy z funkcji EOMONTH())
set language POLISH
select DATENAME(WEEKDAY,EOMONTH('2023/02/10')) [dzien tygodnia],DATEPART(DAY, EOMONTH('2023/02/10')) [ile dni]

-- 13. W jakich kolejnych latach by�a realizowana sprzeda� w bazie NORTHWIND
select DATEPART(year,OrderDate) from Orders
group by DATEPART(year,OrderDate)
order by 1 desc

-- 14. Podaj sprzeda� towar�w, w ka�dym roku dzia�ania firmy (bez upust�w)
select DATEPART(year,o.OrderDate) rok,sum(od.UnitPrice*od.Quantity) suma from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
group by DATEPART(year,o.OrderDate)
order by 1 desc

-- 15. Podaj sprzeda� towar�w w ka�dym roku i miesi�cu dzia�ania firmy
   -- rok i miesi�c podajemy w jednej kolumnie 
select FORMAT(o.OrderDate, 'yyyy-MM') rok,sum(od.UnitPrice*od.Quantity) suma from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
group by FORMAT(o.OrderDate, 'yyyy-MM')
order by FORMAT(o.OrderDate, 'yyyy-MM')

-- 16. Podaj sprzeda� towar�w w ka�dym roku i miesi�cu dzia�ania firmy
   -- rok i miesi�c podajemy w osobnych kolumnach)
select FORMAT(o.OrderDate, 'yyyy') rok,FORMAT(o.OrderDate, 'MM') miesiac,sum(od.UnitPrice*od.Quantity) suma from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
group by FORMAT(o.OrderDate, 'yyyy'),FORMAT(o.OrderDate, 'MM')
order by FORMAT(o.OrderDate, 'yyyy'),FORMAT(o.OrderDate, 'MM')

-- 17. Do ostatniego zapytania do�� klauzul� CUBE i ROLLUP i por�wnaj wyniki obu zapyta� (EXCEPT)
select FORMAT(o.OrderDate, 'yyyy') rok,FORMAT(o.OrderDate, 'MM') miesiac,sum(od.UnitPrice*od.Quantity) suma from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
group by cube (FORMAT(o.OrderDate, 'yyyy'),FORMAT(o.OrderDate, 'MM'))
order by FORMAT(o.OrderDate, 'yyyy'),FORMAT(o.OrderDate, 'MM')

EXCEPT

select FORMAT(o.OrderDate, 'yyyy') rok,FORMAT(o.OrderDate, 'MM') miesiac,sum(od.UnitPrice*od.Quantity) suma from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
group by rollup (FORMAT(o.OrderDate, 'yyyy'),FORMAT(o.OrderDate, 'MM'))
order by FORMAT(o.OrderDate, 'yyyy'),FORMAT(o.OrderDate, 'MM');

-- 18. Podaj numery zam�wie�, ich dat� oraz ca�kowit� warto�� (orderid, orderdate, unitprice*quantity) 
	-- oraz posortuj wzgl�dem ca�kowitej warto�ci
	select o.OrderID,FORMAT(o.OrderDate, 'dd-MM-yyyy'),sum(od.UnitPrice*od.Quantity) from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
group by o.OrderID,FORMAT(o.OrderDate, 'dd-MM-yyyy')
order by 3 desc

-- 19. Podaj numery zam�wie�, ich dat� oraz ca�kowit� warto��, 
	-- kt�re by�y zrealizowane na najwi�ksz� warto�� 
select top 1 o.OrderID,FORMAT(o.OrderDate, 'dd-MM-yyyy') data,sum(od.UnitPrice*od.Quantity) as 'suma' from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
group by o.OrderID,FORMAT(o.OrderDate, 'dd-MM-yyyy')
order by 3 desc

-- 20. Podaj numery zam�wie�, ich dat� oraz ca�kowit� warto��, 
	-- kt�re by�y zrealizowane na najmniejsz� warto��(bez 0)
select top 1 o.OrderID,FORMAT(o.OrderDate, 'dd-MM-yyyy') data,sum(od.UnitPrice*od.Quantity) as 'suma' from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
group by o.OrderID,FORMAT(o.OrderDate, 'dd-MM-yyyy')
order by 3 

-- 21. Podaj numery zam�wie�, ich dat� oraz ca�kowit� warto��, 
	-- kt�re by�y zrealizowane na najwi�ksz� warto�� i na najmniejsz� warto��(bez 0) w jednym zapytaniu.
select top 1 o.OrderID,o.OrderDate data,sum(od.UnitPrice*od.Quantity) as 'suma' from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
group by o.OrderID,o.OrderDate
order by 3

select top 1 o.OrderID,o.OrderDate data,sum(od.UnitPrice*od.Quantity) as 'suma' from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
group by o.OrderID,o.OrderDate
order by 3 desc

-- 22. Podaj numery zam�wie�, ich dat� oraz ca�kowit� warto��, 
	-- kt�re by�y zrealizowane na najwi�ksz� warto�� i na najmniejsz� warto��(bez 0) w jednym zapytaniu.
	-- zapytania typu CTE zaczynaj�ce si� klauzul� WITH

-- 23. Podaj najdro�szy i najta�szy z produkt�w (bez klauzuli TOP ani FETCH FIRST) (Podzapytania)

-- 24. Podaj najdro�szy i najta�szy z produkt�w (bez klauzuli TOP ani FETCH FIRST) (Podzapytania)
	-- Zapytanie typu CTE zaczynaj�c� si� na WITH

-- 25. Podaj numery zam�wie�, ich dat� oraz ca�kowit� warto��, 
	-- kt�re by�y zrealizowane na najwi�ksz� warto�� i na najmniejsz� warto��(bez 0) w jednym zapytaniu.
	-- wykonaj powy�sze zapytanie bez klauzuli top tylko z wykorzystaniem podzapyta�

-- 26. Skasuj produkty nale��ce do kategorii CATX (nie znamy categoryid tylko categoryname)
	-- (najpierw doda� kategorie CATX i p�niej 2 produkty nale��ce do tej kategorii)
select * from Products
DELETE p FROM Products p
INNER join Categories c
on c.CategoryID=p.CategoryID
WHERE c.CategoryName='CATX'
select * from Products
-- 27. Jaka jest sprzeda� sumaryczna w roku 1996 i 1997 (bez group by)
select distinct FORMAT(o.OrderDate,'yyyy') rok,sum(od.Quantity*od.UnitPrice) OVER(PARTITION By FORMAT(o.OrderDate,'yyyy')) from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
-- 28. Podaj nazw� klienta, rok sprzeda�y oraz warto�� sprzeda�y w danym roku.
select c.CompanyName ,year(o.OrderDate),sum(od.Quantity*od.UnitPrice) from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
inner join Customers c on c.CustomerID=o.CustomerID
group by c.CompanyName,year(o.OrderDate)
order by 1
-- 29. W jaki dzie� tygodnia sumaryczenie sprzedano towaru za najw�ksz� kwot�.
select top 1 datename(WEEKDAY,o.OrderDate),sum(od.Quantity*od.UnitPrice) from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
group by datename(WEEKDAY,o.OrderDate)
order by 2 desc
-- 30. Podaj nazw� kategorii oraz rok w kt�rym w danej kategorii by�a najwi�ksza sprzeda�.
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
-- 31. W kt�rym roku by�a nawy�sza sprzeda�.
select top 1 YEAR(o.OrderDate) rok,sum(od.UnitPrice*od.Quantity) wartosc from Orders o 
inner join [Order Details] od
on o.OrderID=od.OrderID
group by yEAR(o.OrderDate)
order by 2
-- 32. Kt�ry z pracownik�w obs�u�y� klient�w za najwi�ksz� kwot�.
select top 1 e.FirstName+' '+e.LastName as 'pracownik',sum(od.Quantity*od.UnitPrice) suma from Orders o
inner join [Order Details] od on od.OrderID=o.OrderID
inner join Employees e on e.EmployeeID=o.EmployeeID
group by e.FirstName+' '+e.LastName
order by 2 desc