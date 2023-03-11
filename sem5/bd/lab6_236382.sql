----------------------------------------------------------------------------
-- Zapytania z podzapytaniami skorelowane i nieskorelowane, zapytania CTE --
----------------------------------------------------------------------------

--1. Wyœwietl najdro¿sze produkty w danej kategorii.
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

--2. ZnaleŸæ kategoriê do której nie przypisano ¿adnego produktu
   --a. wykorzystuj¹c operator JOIN
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


--3. Który z pracowników zrealizowa³ najwiêksz¹ liczbê zamówieñ, w ka¿dym z lat funkcjonowania firmy.
select rok,max(ile)ile from
(
select year(OrderDate) rok,e.LastName+' '+e.FirstName Pracownik,count(o.EmployeeID) ile from Employees e
inner join Orders o on e.EmployeeID=o.EmployeeID
group by year(OrderDate),e.LastName+' '+e.FirstName
)k1
group by rok
--4. Który z pracowników zrealizowa³ zamówienia sumarycznie za najwy¿sz¹ kwotê w danym roku.
select rok,max(ile)ile from
(
select year(o.OrderDate)rok,e.EmployeeID,sum(od.UnitPrice*od.Quantity) ile from [Order Details] od
inner join Orders o on od.OrderID=o.OrderID
inner join Employees e on o.EmployeeID=e.EmployeeID
group by year(o.OrderDate),e.EmployeeID
)k1
group by rok
--5. Jaki klient kupi³ za najwiêksz¹ kwotê sumarycznie, w ka¿dym z lat funkcjonowania firmy.
select rok,max(ile)ile from
(
select year(o.OrderDate)rok,c.CustomerID,sum(od.UnitPrice*od.Quantity) ile from [Order Details] od
inner join Orders o on od.OrderID=o.OrderID
inner join Customers c on c.CustomerID=o.CustomerID
group by year(o.OrderDate),c.CustomerID
)k1
group by rok
--6. ZnajdŸ faktury ka¿dego z klientów opiewaj¹ce na najwy¿sze kwoty.
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
--7. Podaj najlepiej sprzedaj¹ce siê produkty, w ka¿dej kategorii.
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
--8. Podaj jakiego towaru, ka¿dego z dostawców jest w magazynie na najwy¿sz¹ kwotê.
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
--9. Podaj najlepiej sprzedaj¹cy siê produkt, w ka¿dym z roku i kwartale funkcjonowania firmy.
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
--10. W jaki dzieñ tygodnia by³a najwiêksza i najmniejsza sprzeda¿.
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
--11. Tworzenie tabel na podstawie wyników polecenia: select * from products  (SELECT INTO)
   -- Do³ó¿ do wczeœniej utworzonej tabeli na podstawie zapytania jeszcze raz te same dane.
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
--12. Skasuj produkty nale¿¹ce do kategorii CAT1 (najpierw dodaæ 2 produkty bez kategorii, nastêpnie now¹ kategoriê CAT1 i przypisaæ    --dodanym wczeœniej produktom t¹ kategoriê)
   --a. wykorzystaæ zapytanie z podzapytaniem
   --b. oraz zapytanie typu JOIN - jeœli siê da
   select * from Products
DELETE p FROM Products p
INNER join Categories c
on c.CategoryID=p.CategoryID
WHERE c.CategoryName='CAT1'
select * from Products
--13. Zmodyfikuj cenê produktów o 20% dla produktów nale¿¹cych do kategorii o nazwie CAT1.
update Products set UnitPrice=UnitPrice*1.2 
from Products p
join Categories c on p.CategoryID=c.CategoryID
where c.CategoryName='CATX'
--14. Podaj w pierwszej kolumnie ROK, w nastêpnych kolumnach miesi¹ce od 1 do 12.
  --W kolejnych rekordach podajemy sprzeda¿ w danym roku w danym miesi¹cu. Wykorzystaæ funkcjê COALESCE.

--15. Wyœwietl najdro¿sze dwa produkty w danej kategorii (podajemy nazwê kategorii, nazwê produktu i jego cenê)
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
--16. Napisz kilka przyk³adowych zapytañ wykorzystuj¹cych operator [ANY|SOME, ALL] na bazie Northwind. Zadaj pytania, na które odpowiadaj¹ dane przyk³ady.


------------------------
-- funkcje rankongowe --
------------------------
--17. Ponumerowaæ rekordy w tabeli PRODUCTS zgodnie z narastaj¹c¹ wartoœci¹ kolumny productname-ROW_NUMBER().
select ProductName, 
rank() over ( order by ProductName asc) as numer
from Products 
--18. Ponumerowaæ rekordy w tabeli PRODUCTS malej¹co po cenie produktu - ROW_NUMBER(), RANK(), DENSE_RANK().
select ProductName,UnitPrice, 
rank() over ( order by UnitPrice asc) as numer
from Products
order by 1
--19. Ponumerowaæ rekordy rosn¹co po numerze kategorii produktu i malej¹co po cenie produktu.
select ProductName,UnitPrice, 
row_number() over ( order by UnitPrice asc) as numer_C,
dense_rank() over ( order by CategoryID asc) as numer_K
from Products
order by 1
--20. Podaj nazwê kategorii, nazwê produktu oraz jego cenê oraz ranking wg. cen w danej kategorii (PARTITION BY)
select ProductName,c.CategoryName,UnitPrice, 
row_number() over (PARTITION BY c.CategoryName order by UnitPrice desc) as numer_C
from Products p
inner join Categories c on p.CategoryID=c.CategoryID
--21. Podaj ranking sprzeda¿y, w ka¿dej z kategorii.
select p.ProductName,c.CategoryName,sum(od.UnitPrice*od.Quantity),
row_number() over (PARTITION BY c.CategoryName order by sum(od.UnitPrice*od.Quantity) ) as numer_C
from Products p
inner join Categories c on p.CategoryID=c.CategoryID
inner join [Order Details] od on od.ProductID=p.ProductID
group by p.ProductName,c.CategoryName
order by 2
--22. Podaj trzy kategorie, w których sprzedano produktów za najwy¿sz¹ kwotê.
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


 

