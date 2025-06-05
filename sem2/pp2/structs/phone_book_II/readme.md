# Zadanie 2.15

| Trudność   |
|------------|
| ★★★⯪☆ (3.5) |

## 2. Struktury

### 16. Książka telefoniczna 2

---
Rozbuduj program z zadania [2.15 Książka telefoniczna](https://dante.iis.p.lodz.pl/?#/student/subject/46/topic/2753/task/2415) o możliwość usunięcia wybranego rekordu z bazy danych oraz możliwość zapisu bazy do pliku.

Nowe funkcje powinny mieć następujące prototypy:

```c
int remove_entry_by_last_name(struct entry_t* p, int size, const char* last_name);
```

Funkcja usuwa z bazy kontaktów pierwszy wpis o podanym nazwisku last_name. Jeżeli w bazie brak kontaktu o nazwisku last_name to funkcja nie podejmuje żadnych akcji.

*Wartośc zwracana*:

* W przypadku sukcesu funkcja zwraca nowy rozmiar tablicy.
* W przypadku błędu funkcja zwraca ten sam rozmiar tablicy (size).

---

```c
int save_phonebook_t(const char *filename, const struct entry_t* p, int size);
```
Funkcja zapisuje do pliku tekstowego ```file_name``` kontakty z tablicy ```p``` w liczbie ```size``` rekordów.

*Parametry*:
* ```filename``` - nazwa pliku, do którego ma zostać zapisana baza kontaktów,
* ```p``` - tablica struktur, przechowującej dane do zapisu na dysk,
* ```size``` - liczba elementów w tablicy p.

*Wartość zwracana*:
* ```-1``` - w przypadku podania błędnych danych przy wywołaniu funkcji,
* ```-2``` - jeżeli nie uda się utworzyć pliku,
* ```>0``` - w przypadku sukcesu liczba zapisanych rekordów.

*Format pliku*

* Dane w pliku mają być oddzielone symbolami |, każdy rekord w osobnej linii (patrz zadanie 2.15 Książka telefoniczna).

---

Napisz program, który pobierze od użytkownika nazwę pliku tekstowego (nie dłuższą niż 100 znaków) z książką telefoniczną. Z podanego pliku program powinien wczytać nie więcej niż 10 pierwszych kontaktów.

Jeżeli nie uda się odczytać bazy danych z dysku program powinien wyświetlić komunikat <font color="red">Couldn't</font> open file i zwrócić wartość <font color="red">4</font> lub w przypadku braku w bazie danych rekordów, komunikat <font color="red">File corrupted</font> i zakończyć działanie z kodem błędu <font color="red">6</font>.

Po wczytaniu bazy danych do pamięci program ma zapytać użytkownika o podanie nazwiska osoby, której informacje kontaktowe mają zostać usunięte z podanej bazy danych.

W przypadku braku osoby o podanym nazwisku w bazie, program powinien wyświetlić komunikat <font color="red">Couldn't find name</font> i zakończyć działanie z kodem błędu <font color="red">0</font>. Znaleziona osobę należy usunąć z wczytanej bazy, potwierdzając to komunikatem <font color="red">Entry removed</font> a następnie należy zapisać zmienioną bazę na dysk, do pliku o tej samej nazwie.

Jezeli zapis się nie powiedzie program powinien wyświetlić komunikat <font color="red">Couldn't create file</font> i zakończyć działanie z kodem błędu <font color="red">6</font>. W przypadku sukcesu program kończy się komunikatem <font color="red">File saved</font>.

**Przykładowa interakcja z programem -- sukces** (wejście: [2415test.txt](http://pp.iis.p.lodz.pl/lib/exe/fetch.php?media=przyklady_pp2:2415test.txt), wyjście [2416test.txt](http://pp.iis.p.lodz.pl/lib/exe/fetch.php?media=przyklady_pp2:2416test.txt)):
```cmd
Enter file name: 2416test.txt⏎
Enter last name: Kowalski⏎
Entry removed⏎
File saved
```
**Przykładowa interakcja z programem -- sukces, brak nazwiska**:
```cmd
Enter file name: king.txt⏎
Enter last name: Redford⏎
Couldn't find name
```
**Przykładowa interakcja z programem -- brak pliku wejściowego lub błąd danych**:
```cmd
Enter file name:⏎
floor.txt⏎
Couldn't open file
```
```cmd
Enter file name:⏎
silver.txt⏎
File corrupted
```
**Przykładowa interakcja z programem -- błąd zapisu danych** (np. plik wejściowy tylko do odczytu):
```cmd
Enter file name: 2416test.txt⏎
Enter last name: Kowalski⏎
Entry removed⏎
Couldn't create file
```
### **Uwagi**
* W programie nie wolno używać funkcji alokujących pamięć.
* Wszystkie operacje na tablicach powinny być wykonywane za pomocą wskaźników, a nie operatora ```[]```.