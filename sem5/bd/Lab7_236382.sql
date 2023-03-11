--CREATE DATABASE BIBLIOTEKA;
use BIBLIOTEKA
create table Autorzy
(
IDAutora int identity(1,1) not null,
Nazwisko varchar(70) not null,
Imie varchar(50) not null,
Uwagi varchar(100) null,
)
Alter table autorzy add constraint PK_Autorzy PRIMARY KEY (IDAutora)
create table Kategorie
(
IDKategori int identity(1,1) not null PRIMARY KEY,
Nazwa_Kategori varchar(100) not null,
)
create table Wydawcy
(
IDWydawcy int identity(1,1) not null PRIMARY KEY,
Nazwa_Wydawcy varchar(100) not null,
)
create table Szafka
(
IDSzawki int identity(1,1) not null PRIMARY KEY,
Nazwa_Szawki varchar(5) not null,
)
create table Publikacja
(
IDKsiazki int identity(1,1) not null PRIMARY KEY,
IDAutora int not null,
IDKategori int not null,
Tytul varchar(250) not null,
IDWydawcy int not null,
Rok int not null,
Miejsce varchar(250) not null,
IDSzawki int not null,
S³owa_kluczowe varchar(250) not null
)
create table Egzemplarz
(
IDEgzemplarza int identity(1,1) not null PRIMARY KEY,
IDKsiazki int not null,
Ubytki varchar(100) not null
)
create table Rejestr_wyporzyczen
(
IDwyporzyczenia int identity(1,1) not null PRIMARY KEY,
NRkarty int not null,
IDEgzemplarza int not null,
DataWyp date not null,
ZwrotPrzed date null,
DataZwrotu date null,
)
create table Czytelnicy
(
NRkarty int identity(1,1) not null PRIMARY KEY,
Nazwisko varchar(70) not null,
Imie varchar(50) not null,
IDdokumentu int not null,
NRdokumentu int not null,
DataUr date not null,
MiejsceUr varchar(100) not null,
Kod varchar(10) not null,
Miasto varchar(100) not null,
Ulica varchar(100) not null,
NRdomu int not null,
Telefon int not null
)
Alter table publikacja add constraint FK_Pub_Kat FOREIGN KEY (IDKategori)
REFERENCES Kategorie (IDKategori)
Alter table publikacja add constraint FK_Pub_Wy FOREIGN KEY (IDWydawcy)
REFERENCES Wydawcy (IDWydawcy)
Alter table publikacja add constraint FK_Pub_Sza FOREIGN KEY (IDSzawki)
REFERENCES Szafka (IDSzawki)
Alter table publikacja add constraint FK_Pub_Aut FOREIGN KEY (IDAutora)
REFERENCES Autorzy (IDAutora)
Alter table Egzemplarz add constraint FK_Egz_Pub FOREIGN KEY (IDksiazki)
REFERENCES Publikacja (IDKsiazki)
Alter table Rejestr_wyporzyczen add constraint FK_RW_Egz FOREIGN KEY (IDEgzemplarza)
REFERENCES Egzemplarz (IDEgzemplarza)
Alter table Rejestr_wyporzyczen add constraint FK_RW_Czyte FOREIGN KEY (NRkarty)
REFERENCES Czytelnicy (NRkarty)