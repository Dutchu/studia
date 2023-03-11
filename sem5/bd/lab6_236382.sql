----------------------------------------------------------------------------
-- Zapytania z podzapytaniami skorelowane i nieskorelowane, zapytania CTE --
----------------------------------------------------------------------------

--1. Wy�wietl najdro�sze produkty w danej kategorii.
Select c.CategoryName,ProductName,UnitPrice
from Products p1
inner join(
	Select CategoryID as CatID,
	MAX(unitprice) Max_Unit_Price_by_category 
	from Products
	group by CategoryID
)p2
ON p1.CategoryID=p2.CatID
inner join Categories c on c.CategoryID=p1.CategoryID
AND p1.UnitPrice=p2.Max_Unit_Price_by_category
Order by UnitPrice desc

--2. Znale�� kategori� do kt�rej nie przypisano �adnego produktu
   --a. wykorzystuj�c operator JOIN
select c.CategoryName,p.CategoryID from Categories c
full outer join(
select CategoryID from Products
group by CategoryID)p
on p.CategoryID=c.CategoryID
where p.CategoryID is null
   --b. zapytanie z podzapytaniem skorelowane --np. EXISTS lub NOT EXISTS
select c.CategoryID,c.CategoryName from Categories c
where not exists
(select CategoryID from Products p
where p.CategoryID=c.CategoryID)
   --c. zapytanie z podzapytaniem nieskorelowane


--3. Kt�ry z pracownik�w zrealizowa� najwi�ksz� liczb� zam�wie�, w ka�dym z lat funkcjonowania firmy.
select rok,max(ile)ile from
(
select year(OrderDate) rok,e.LastName+' '+e.FirstName Pracownik,count(o.EmployeeID) ile from Employees e
inner join Orders o on e.EmployeeID=o.EmployeeID
group by year(OrderDate),e.LastName+' '+e.FirstName
)k1
group by rok
--4. Kt�ry z pracownik�w zrealizowa� zam�wienia sumarycznie za najwy�sz� kwot� w danym roku.
select rok,max(ile)ile from
(
select year(o.OrderDate)rok,e.EmployeeID,sum(od.UnitPrice*od.Quantity) ile from [Order Details] od
inner join Orders o on od.OrderID=o.OrderID
inner join Employees e on o.EmployeeID=e.EmployeeID
group by year(o.OrderDate),e.EmployeeID
)k1
group by rok
--5. Jaki klient kupi� za najwi�ksz� kwot� sumarycznie, w ka�dym z lat funkcjonowania firmy.
select rok,max(ile)ile from
(
select year(o.OrderDate)rok,c.CustomerID,sum(od.UnitPrice*od.Quantity) ile from [Order Details] od
inner join Orders o on od.OrderID=o.OrderID
inner join Customers c on c.CustomerID=o.CustomerID
group by year(o.OrderDate),c.CustomerID
)k1
group by rok
--6. Znajd� faktury ka�dego z klient�w opiewaj�ce na najwy�sze kwoty.
select Klient,faktura,wartosc from
(
	Select o.CustomerID Klient,max(ile) wartosc from Orders o
	inner join
	(
		select o.OrderID od1,sum(od.UnitPrice*od.Quantity) ile from [Order Details] od
		inner join Orders o on od.OrderID=o.OrderID
		group by o.OrderID
	)
	k1 on o.OrderID=k1.od1
	group by o.CustomerID
)k2
inner join 
(
	select o.OrderID faktura,sum(od.UnitPrice*od.Quantity) ile from [Order Details] od
	inner join Orders o on od.OrderID=o.OrderID
	group by o.OrderID
)k3 on k2.wartosc=k3.ile
--7. Podaj najlepiej sprzedaj�ce si� produkty, w ka�dej kategorii.
select c.CategoryName,k3.nazwa,k2.ile from
(
	select p.CategoryID kategoria,max(ile) ile from products p
	inner join 
	(
	select p.ProductName,sum(od.Quantity) ile from [Order Details] od
	inner join Products p on p.ProductID=od.ProductID
	group by p.ProductName
	)k1 on p.ProductName=k1.ProductName
	group by p.CategoryID
)k2
inner join 
(
	select p.ProductName nazwa,sum(od.Quantity) ile from [Order Details] od
	inner join Products p on p.ProductID=od.ProductID
	group by p.ProductName
)k3 on k3.ile=k2.ile
	inner join Categories c on k2.kategoria=c.CategoryID
--8. Podaj jakiego towaru, ka�dego z dostawc�w jest w magazynie na najwy�sz� kwot�.
select k2.nazwa_firmy,k3.produkt,k2.wartosc from
(
	select s.CompanyName nazwa_firmy,MAX(wartosc) wartosc from Suppliers s
	inner join
	(
		select p.ProductName produkt,s.CompanyName nazwa_firmy,p.UnitsInStock*UnitPrice wartosc from Products p
		inner join Suppliers s on p.SupplierID=s.SupplierID
	)k1 on k1.nazwa_firmy=s.CompanyName
	group by s.CompanyName
)k2
inner join 
(
	select p.ProductName produkt,s.CompanyName nazwa_firmy,p.UnitsInStock*UnitPrice wartosc from Products p
	inner join Suppliers s on p.SupplierID=s.SupplierID
)k3 on k2.wartosc=k3.wartosc
--9. Podaj najlepiej sprzedaj�cy si� produkt, w ka�dym z roku i kwartale funkcjonowania firmy.
select k2.rok,k2.kwartal,k3.nazwa,k2.ile from
(
	select k1.rok,k1.kwartal,max(ile) ile from
	(
		select  year(o.OrderDate) rok,DATEPART(QUARTER,o.OrderDate) kwartal,p.ProductName nazwa,sum(od.Quantity) ile
		from Products p
		inner join [Order Details] od on p.ProductID=od.ProductID
		inner join Orders o on od.OrderID=o.OrderID
		group by year(o.OrderDate),DATEPART(QUARTER,o.OrderDate),p.ProductName
	)k1
	group by k1.rok,k1.kwartal
)k2
inner join
(
	select  year(o.OrderDate) rok,DATEPART(QUARTER,o.OrderDate) kwartal,p.ProductName nazwa,sum(od.Quantity) ile
	from Products p
	inner join [Order Details] od on p.ProductID=od.ProductID
	inner join Orders o on od.OrderID=o.OrderID
	group by year(o.OrderDate),DATEPART(QUARTER,o.OrderDate),p.ProductName
)k3 on k3.ile=k2.ile
--10. W jaki dzie� tygodnia by�a najwi�ksza i najmniejsza sprzeda�.
	select 'max',k1.dzien,wartosc from
	(
		select DATENAME(weekday,o.OrderDate) dzien,sum(od.Quantity*od.UnitPrice) wartosc from Orders o
		inner join [Order Details] od on o.OrderID=od.OrderID
		group by DATENAME(weekday,o.OrderDate)
	)k1
	where wartosc=
	(select max(wartosc) maxi from 
		(
		select DATENAME(weekday,o.OrderDate) dzien,sum(od.Quantity*od.UnitPrice) wartosc from Orders o
		inner join [Order Details] od on o.OrderID=od.OrderID
		group by DATENAME(weekday,o.OrderDate)
		)k1
	)

	union

	select 'min',k1.dzien,wartosc from
	(
		select DATENAME(weekday,o.OrderDate) dzien,sum(od.Quantity*od.UnitPrice) wartosc from Orders o
		inner join [Order Details] od on o.OrderID=od.OrderID
		group by DATENAME(weekday,o.OrderDate)
	)k1
	where wartosc=
	(select min(wartosc) maxi from 
		(
		select DATENAME(weekday,o.OrderDate) dzien,sum(od.Quantity*od.UnitPrice) wartosc from Orders o
		inner join [Order Details] od on o.OrderID=od.OrderID
		group by DATENAME(weekday,o.OrderDate)
		)k1
	)
--11. Tworzenie tabel na podstawie wynik�w polecenia: select * from products  (SELECT INTO)
   -- Do�� do wcze�niej utworzonej tabeli na podstawie zapytania jeszcze raz te same dane.
   INSERT INTO [dbo].[Products_backup]
           ([productid]
		   ,[ProductName]
           ,[SupplierID]
           ,[CategoryID]
           ,[QuantityPerUnit]
           ,[UnitPrice]
           ,[UnitsInStock]
           ,[UnitsOnOrder]
           ,[ReorderLevel]
           ,[Discontinued])
select * from Products
--12. Skasuj produkty nale��ce do kategorii CAT1 (najpierw doda� 2 produkty bez kategorii, nast�pnie now� kategori� CAT1 i przypisa�    --dodanym wcze�niej produktom t� kategori�)
   --a. wykorzysta� zapytanie z podzapytaniem
   --b. oraz zapytanie typu JOIN - je�li si� da
   select * from Products
DELETE p FROM Products p
INNER join Categories c
on c.CategoryID=p.CategoryID
WHERE c.CategoryName='CAT1'
select * from Products
--13. Zmodyfikuj cen� produkt�w o 20% dla produkt�w nale��cych do kategorii o nazwie CAT1.
update Products set UnitPrice=UnitPrice*1.2 
from Products p
join Categories c on p.CategoryID=c.CategoryID
where c.CategoryName='CATX'
--14. Podaj w pierwszej kolumnie ROK, w nast�pnych kolumnach miesi�ce od 1 do 12.
  --W kolejnych rekordach podajemy sprzeda� w danym roku w danym miesi�cu. Wykorzysta� funkcj� COALESCE.

--15. Wy�wietl najdro�sze dwa produkty w danej kategorii (podajemy nazw� kategorii, nazw� produktu i jego cen�)
select p.ProductName,k1.CategoryName,k1.cena from(
select c.CategoryName,max(p.UnitPrice) cena from Products p
inner join Categories c on p. CategoryID=c.CategoryID
group by c.CategoryName
union
select c.CategoryName,max(p.UnitPrice) as cena from Products p
inner join Categories c on p. CategoryID=c.CategoryID
where p.UnitPrice not in (select max(p.UnitPrice) from Products p
group by p.CategoryID)
group by c.CategoryName
)k1
inner join Products p on  k1.cena=p.UnitPrice
order by 2,3 desc
--16. Napisz kilka przyk�adowych zapyta� wykorzystuj�cych operator [ANY|SOME, ALL] na bazie Northwind. Zadaj pytania, na kt�re odpowiadaj� dane przyk�ady.


------------------------
-- funkcje rankongowe --
------------------------
--17. Ponumerowa� rekordy w tabeli PRODUCTS zgodnie z narastaj�c� warto�ci� kolumny productname-ROW_NUMBER().
select ProductName, 
rank() over ( order by ProductName asc) as numer
from Products 
--18. Ponumerowa� rekordy w tabeli PRODUCTS malej�co po cenie produktu - ROW_NUMBER(), RANK(), DENSE_RANK().
select ProductName,UnitPrice, 
rank() over ( order by UnitPrice asc) as numer
from Products
order by 1
--19. Ponumerowa� rekordy rosn�co po numerze kategorii produktu i malej�co po cenie produktu.
select ProductName,UnitPrice, 
row_number() over ( order by UnitPrice asc) as numer_C,
dense_rank() over ( order by CategoryID asc) as numer_K
from Products
order by 1
--20. Podaj nazw� kategorii, nazw� produktu oraz jego cen� oraz ranking wg. cen w danej kategorii (PARTITION BY)
select ProductName,c.CategoryName,UnitPrice, 
row_number() over (PARTITION BY c.CategoryName order by UnitPrice desc) as numer_C
from Products p
inner join Categories c on p.CategoryID=c.CategoryID
--21. Podaj ranking sprzeda�y, w ka�dej z kategorii.
select p.ProductName,c.CategoryName,sum(od.UnitPrice*od.Quantity),
row_number() over (PARTITION BY c.CategoryName order by sum(od.UnitPrice*od.Quantity) ) as numer_C
from Products p
inner join Categories c on p.CategoryID=c.CategoryID
inner join [Order Details] od on od.ProductID=p.ProductID
group by p.ProductName,c.CategoryName
order by 2
--22. Podaj trzy kategorie, w kt�rych sprzedano produkt�w za najwy�sz� kwot�.
select top 3 c.CategoryName,sum(od.UnitPrice*od.Quantity),
row_number() over (order by sum(od.UnitPrice*od.Quantity ) desc) as numer_C
from Products p
inner join Categories c on p.CategoryID=c.CategoryID
inner join [Order Details] od on od.ProductID=p.ProductID
group by c.CategoryName
--23. Podaj w danej kategorii 3 najlepiej sprzedawane produkty.
select * from(select p.ProductName,c.CategoryName kategoria,sum(od.Quantity) ile, 
row_number() over (PARTITION BY c.CategoryName order by sum(od.Quantity) desc) as numer_C
from Products p
inner join Categories c on p.CategoryID=c.CategoryID
inner join [Order Details] od on od.ProductID=p.ProductID
group by p.ProductName,c.CategoryName
)k1
where k1.numer_C like '[1-3]'


 

