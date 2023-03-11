-- 1. Ustawiamy bazę Northwind
	use Northwind
-- 2. Wybieramy wszystkie rekordy z tabeli Categories
	use Northwind
select * from Categories
-- 3. Wybieramy wszystkie rekordy z tabeli Categories ustawiając wcześniej bazę master
	use master
	select * from Categories
-- 4. Sposób zaptań na obiektach, których nazwa zawiera znaki specjalne (np. spacje)
	po przez nawias kwardatowy np 
	select * from [tabela testowa]
	lub cudzysłów
	select * from "tabela testowa"
-- 5. Wybieramy z tabeli Categories tylko dwie kolumny: CategoryName, [Description]
	use master
	select CategoryName, Description from Categories
-- 6. Wybieramy z tabeli Products trzy kolumny kolumny: ProductName, cenę produktu * 1.23 (nowa nazwa kolumny to 'Cena z VAT'), 
-- wartość danego towaru w magazynie (nowa nazwa kolumny to 'Wartość')
	use master
	select ProductName,UnitPrice*1.23 as [Cena z VAT],UnitsInStock as [Stan w magazynie] from Products
-- 7. W tabeli pracowników definiujemy 1 kolumnę postaci np. Sz.P. Piotr Nowak 
	use master
	select TitleOfCourtesy+' '+FirstName+' '+LastName as Pracownik from Employees
-- 8. Z tabeli pracowników definiujemy 4 kolumny, gdzie podajemy: 
	-- TitleOfCourtesy FirstName LastName, 
	-- Address, 
	-- PostalCode City, 
	-- Country, 
	-- które można wykorzystac do adresowania kopert
	use master
	select TitleOfCourtesy+' '+FirstName+' '+LastName as Pracownik,
	Address as Adres,PostalCode+' '+City as [Kod podcztowy],Country as Kraj
	from Employees
-- 9. Sortowanie - Wybieramy z tabel Suppliers kolumny: nazwa_firmy, miasto, państwo a następnie sortujemy malejąco względem Country i rosnąco względem City 
	use master
	select CompanyName,City,Country
	from Suppliers
	order by Country desc,City asc
--10. Sortowanie - Wybieramy z tabel Suppliers kolumny: nazwa_firmy, miasto, państwo a następnie sortujemy malejąco względem Country, malejąco względem City i rosnąco względem nazwy firmy
	use master
	select CompanyName,City,Country
	from Suppliers
	order by Country desc,City asc,CompanyName desc
-- j.w. tylko używamy numery kolejne kolumn
	use master
	select CompanyName,City,Country
	from Suppliers
	order by 3 desc,2 asc,1 desc
-- j.w. tylko używamy numery kolejne kolumn oraz aliasy nazw kolumn
	use master
	select CompanyName as [Nazwa firmy],City as Miasto,Country as Kraj
	from Suppliers
	order by Kraj desc,2 asc,[Nazwa firmy] desc
----------------------------------------------------------------------
-- Szukamy w dokumentacji SQL Server frazy: Select (Transact-SQL)
-- https://docs.microsoft.com/en-us/sql/t-sql/queries/select-transact-sql?view=sql-server-ver15
-- mamy dostępne klauzle ALL, DISTINCT, TOP

--11. Wybieramy nazwy wszystkich państw z tabeli Dostawców (Suppliers) i sortujemy względem nich -- klauzula ALL jest defaultowa
	use Northwind
	select Country  from Suppliers 
	order by Country
--12. Wybieramy nazwy wszystkich państw bez powtórzeń z tabeli Dostawców (Suppliers) i sortujemy względem nich
	use Northwind
	select DISTINCT Country  from Suppliers 
	order by Country
--13. Wybieramy trzy najdroższe produkty
	use Northwind
	select top 3 ProductName,UnitPrice from Products
	order by UnitPrice desc
--14. Wybieramy 10% najdroższych produktów
	use Northwind
	select top 10 PERCENT ProductName,UnitPrice from Products
	order by UnitPrice desc
--15. Wybieramy 11 najdroższych produktów (sprawdzamy czy na pozycjach 12 i dalej jest taka sama wartość ceny produktu jak na pozycji 11). 
-- Jeśli tak to należy je wyświetlić.
	use Northwind
	select top 11 with ties ProductName from Products
	order by UnitPrice desc
--16. Wybieramy nazwę i cenę produktów od 11 do 15 rekordu posortowanych względem ceny malejąco
	-- wykorzystujemy składnię offset .. rows fetch first .. rows only (szukamy w dokumentacji polecenia ORDER BY)
	use Northwind
	select ProductName,UnitPrice from Products
	order by UnitPrice desc
	OFFSET 10 ROWS
	FETCH FIRST 5 ROWS ONLY
--17. Wyświetlamy nazwę dostawcy i numer faksu ( nie wyświetlamy firm bez numeru faksu (wartość NULL))
	use Northwind
	select CompanyName,Fax from Suppliers
	where Fax is not null
--18. Wyświetlamy nazwę dostawcy i numer faksu ( wyświetlamy firm bez numeru faksu (wartość NULL))
	use Northwind
	select CompanyName,Fax from Suppliers
	where Fax is null
--19. Wyświetlamy nazwę dostawcy i numer faksu. Jeśli numeru faksu nie ma to powinna pojawić się nazwa 'Brak faksu'. 
	-- Korzystamy z funkcji ISNULL (sprawdzamy w dokumentacji)
	use Northwind
	select CompanyName,isnull(Fax,'Brak faksu') from Suppliers
--20. Wyświetlamy nazwę dostawcy, numer faksu, coutry i city, który znajduje się w 'USA' lub 'France' lub w mieście 'London'
	use Northwind
	select CompanyName,isnull(Fax,'Brak faksu'),Country,City from Suppliers
	where
	Country like 'USA'
	or
	City like 'Londyn'
	or
	Country like 'France'
--21. Wyświetlamy nazwę dostawcy, numer faksu, coutry i city, który znajduje się w 'USA', 'France' lub 'Poland' (korzystamy z operatora logicznego IN)
	use Northwind
	select CompanyName,isnull(Fax,'Brak faksu'),Country,City from Suppliers
	where country in('USA','FRANCE','POLAND')
--22. Wyświetlamy nazwę dostawcy, numer faksu, coutry i city, który nie znajduje się w 'USA', 'France' lub 'Poland' (korzystamy z operatora logicznego NOT IN)
	use Northwind
	select CompanyName,isnull(Fax,'Brak faksu'),Country,City from Suppliers
	where country not in('USA','FRANCE','POLAND')
--23. Wyświetlamy produkty, których cena jest z zakresu od 50 do 100 łącznie z tymi punktami (korzystamy z operatora AND OR NOT >= <= > <)
	use Northwind
	select p.ProductName from Products p
	where p.UnitPrice>=50
	and
	p.UnitPrice<=100
--24. Wyświetlamy produkty, których cena jest z zakresu do 50 i od 100 bez tych punktów (korzystamy z operatora AND OR NOT >= <= > <)
	use Northwind
	select p.ProductName from Products p
	where p.UnitPrice>50
	and
	p.UnitPrice<100
--25. Wyświetlamy produkty, których cena jest z zakresu od 50 do 100 łącznie z tymi punktami (korzystamy z operatora BETWEEN AND)
	use Northwind
	select p.ProductName from Products p
	where UnitPrice between 50 and 100
--26. Wyświetlamy produkty, których cena jest z zakresu do 50 i od 100 bez tych punktów (korzystamy z operatora NOT BETWEEN AND)
	use Northwind
	select p.ProductName from Products p
	where UnitPrice not between 50 and 100
--27. Wyświetlamy produkty, których cena jest z zakresu <20;80) bez punktów {30;40;50;60} - korzystamy tylko z operatorów BETWEEN AND, IN, NOT, AND, OR
	-- Negacja to operatory != <> NOT
	use Northwind
	select p.ProductName  from Products p
	where p.UnitPrice>=20
	and
	p.UnitPrice<80
	and
	p.UnitPrice !='30'
	and
	p.UnitPrice !='40'
	and
	p.UnitPrice !='50'
	and
	p.UnitPrice !='60'
	order by p.UnitPrice asc
--28. Znaleźć produkty o nazwie z zakresu od litery a do litery c (stosujemy operator between i funkcję substring - sprawdzamy w dokumentacji)
	use Northwind
	select ProductName from Products
	where ProductName between 'a' and 'd'
--29. Znaleźć produkty z zakresu od a do c (korzystamy z klauzuli LIKE - sprawdzamy w dokumentacji)
	use Northwind
	select ProductName from Products
	where ProductName like '[abc]_%'
--30. Znaleźć produkty, które zaczynają się na literę a (korzystamy z klauzuli LIKE)
	use Northwind
	select ProductName from Products
	where ProductName like 'a_%'
--31. Znaleźć produkty kończące sie na literę s (gdzie korzystamy klauzula LIKE)
	use Northwind
	select ProductName from Products
	where ProductName like '%_s'
--32. Znaleźć produkty, które w nazwie mają literę a,g,k na miejscu drugim (LIKE)
	use Northwind
	select ProductName from Products
	where ProductName like '_[agk]_%'
--33. Znaleźć produkty zaczynające się na literę 'A' (LIKE)
	use Northwind
	select ProductName from Products
	where ProductName like 'A_%'
--34. Znaleźć produkty zaczynające się na litery od A do G (LIKE)
	use Northwind
	select ProductName from Products
	where ProductName like '[A-G]_%'
--35. Znaleźć produkty zaczynające się na litery A, C, G (LIKE)
	use Northwind
	select ProductName from Products
	where ProductName like '[ACG]_%'
--35. Znaleźć produkty, które zawierają ' (apostrof) (LIKE)
	use Northwind
	select ProductName from Products
	where ProductName like '%''%'
--36. Znaleźć produkty kończące sie na słowo 'up' 
	use Northwind
	select ProductName from Products
	where ProductName like '% up'
--37. Znaleźć produkty, które w nazwie na miejscu dwudziestym miejscu ma literę S, gdzie długość stringu jest >= 20 znaków (LEN)
	use Northwind
	select ProductName from Products
	where ProductName like '__________________s%'
--38. Znaleźć produkty zaczynające się na litery od A do S, których cena jest z zakres 15 do 120, które należą do kategorii 1,3,6. 
	use Northwind
	select ProductName from Products
	where ProductName like '[a-s]%'
	and
	UnitPrice between 15 and 120
	and
	CategoryID like '[136]'
--39. Znaleźć produkty, które w nazwie mają słowo New.
	use Northwind
	select ProductName from Products
	where ProductName like '% new %'
--40. Łaczymy Imię, nazwisko i numer pracownika (Employees) w jeden string i wyświetlamy jedną kolumnę.
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

