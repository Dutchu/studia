<div style="display: flex; justify-content: space-between; align-items: center;">
   <div><img src="https://weeia.p.lodz.pl/themes/custom/tul_faculty/img/logos/weeia.svg" alt="logo" width="200px" /></div>
</div>

# Kolokwium 1

---Podstawowe zadanie (ocena 3,0)---

Napisz program, który wczyta z plików wyrazy i obliczy ich liczbę wystąpień. Przygotuj
funkcje zgodnie z poniższą specyfikacją. Kod przygotowanych funkcji umieść w pliku `defs.c`,
a prototypy oraz struktury danych i typy wyliczeniowe w pliku `defs.h`.

Przygotuj strukturę `word_t` do przechowywania wyrazów i ilości ich występowania:

```c
struct word_t
{
    char* word;
    int count;
};


gdzie:

*   `word` - wyraz,
*   `count` - liczba wystąpień danego wyrazu w analizowanym pliku.

Przygotuj strukturę `file_t` do przechowywania nazw plików i tablicy wskaźników do słów:

```c
struct file_t
{
    char* name;
    struct word_t** words;
};
```

gdzie:

*   `name` - nazwa pliku,
*   `words` - tablica wskaźników do słów występujących w pliku.

---

Przygotuj typ wyliczeniowy `error_code_t` i zadeklaruj go w pliku `defs.h`. Typ wyliczeniowy ma
posiadać następujące pola:

```c
ERROR_CODE_OK - 0
ERROR_CODE_INCORRECT_PARAMETERS - 1
ERROR_CODE_FILE_NOT_EXISTS - 2
ERROR_CODE_FILE_CORRUPTED - 3
ERROR_CODE_FAILED_TO_ALLOCATE_MEMORY - 4
```

Zaimplementuj następujące API:

```c
struct file_t** words_read (const char* filename, enum error_code_t* error);
void words_display (struct file_t** files, enum error_code_t* error);
void words_free (struct file_t*** files, enum error_code_t* error);
```

```c
struct file_t** words_read (const char* filename, enum error_code_t* error);
```

Funkcja czyta z plików tekstowych zawarte w nich słowa.

gdzie:

*   `filename` - nazwa pliku tekstowego zawierającego listę nazw plików, z których mają
    zostać odczytane słowa,
*   `error` - adres zmiennej, w której zachowany będzie kod błędu.

Funkcja zwraca terminowaną `NULL` tablicę typu `struct file_t**`. Każdy element tej tablicy to
wskaźnik do zmiennej typu `struct file_t*` zawierającej listę słów z pojedynczego pliku wraz
z jego nazwą. W przypadku błędu funkcja zwraca `NULL` i ustawia kod błędu w `enum
error_code_t* error` (jeśli różne od `NULL`). Funkcja może zaalokować tylko tyle pamięci ile
jest niezbędne do przechowywania odczytanych danych. Słowa w plikach tekstowych składają
się wyłącznie z liter alfabetu łacińskiego. Jeśli wystąpi cyfra lub plik będzie pusty ma zwrócić
`ERROR_CODE_FILE_CORRUPTED`. Każdy inny znak (np. kropka) traktowany jest jak znak
biały (separator między słowami). Słowa mogą być rozdzielone dowolną liczbą różnych
separatorów.

Wartość zwracana:

`ERROR_CODE_OK` - w przypadku powodzenia.

`ERROR_CODE_INCORRECT_PARAMETERS` - w przypadku przekazania do
funkcji nieprawidłowych danych.

`ERROR_CODE_FILE_NOT_EXISTS` - gdy plik o podanej nazwie nie istnieje.

---

`ERROR_CODE_FAILED_TO_ALLOCATE_MEMORY` - w przypadku
niepowodzenia alokacji pamięci.

`ERROR_CODE_FILE_CORRUPTED` – jeśli dane są uszkodzone w pliku.

```c
void words_display (struct file_t** files, enum error_code_t* error);
```

Funkcja wyświetla zawartość tablicy zawierającej słowa odczytane z plików w formacie:

```
nazwa_plikul
slowol liczba_wystąpień
słowo2 liczba_wystąpień
...
nazwa_pliku2
słowol liczba_wystąpień
słowo2 liczba_wystąpień
...
```

gdzie:

*   `files` - wskaźnik do tablicy, której zawartość ma zostać wyświetlona,
*   `error` - adres zmiennej, w której zachowany będzie kod błędu.

W przypadku błędu funkcja kończy działanie i ustawia kod błędu w `enum error_code_t* error`
(jeśli różne od `NULL`).

```c
void words_free (struct file_t*** files, enum error_code_t* error);
```

Funkcja zwalnia pamięć przydzieloną podczas odczytu słów z plików.

gdzie:

*   `files` - wskaźnik do tablicy, która ma zostać zwolniona,
*   `error` - adres zmiennej, w której zachowany będzie kod błędu.

W przypadku błędu funkcja zwraca `NULL` i ustawia kod błędu w `enum error_code_t* error`
(jeśli różne od `NULL`).

Napisz program, który w oparciu o przygotowane funkcje wczyta z plików dane, a następnie
wyświetli je w konsoli. Jeżeli operacja otwarcia pliku się nie powiedzie, to program powinien
wyświetlić komunikat `Couldn't open file` i zakończyć się z kodem błędu 4. Po wczytaniu pliku

---

program powinien wyświetlić zawartość tablicy struktur w taki sam sposób, jak funkcja
`words_display`.

Jeżeli wystąpi błąd związany z alokacją pamięci, to program powinien wyświetlić komunikat
`Failed to allocate memory` i zakończyć się z kodem błędu 8. Jeżeli dane w pliku będą
uszkodzone, to program powinien wyświetlić komunikat `File corrupted` i zakończyć się
z kodem błędu 6.

Przykład interakcji (błąd alokacji):

```
Failed to allocate memory
```

Przykład interakcji (nieistniejący plik):

```
Couldn't open file
```

Przykład interakcji (dane uszkodzone):

```
File corrupted
```

Przykład:

Plik `files.txt` zawiera listę plików:

```
plik1.txt
plik2.txt
```

Zawartość pliku `plik1.txt`:

```
Ala ma kota. Ala nie ma kota.
```

Zawartość pliku `plik2.txt`:

```
hi hi hi ha ha ha
```

---

Przykład interakcji (sukces):

```
file1.txt
Ala 2
ma 2
kota 2
nie 1
file2.txt
hi 3
ha 3
```

Uwagi

*   Wszystkie operacje na tablicach powinny być wykonywane za pomocą wskaźników,
    a nie operatora `[]`.
*   W programie można zadeklarować pomocniczą tablice, deklaracja tablicy musi
    wyglądać następująco:

    ```c
    char text[31];
    ```

---

---Rozszerz poprzednie zadanie o następującą funkcje (ocena 4,0)---

```c
void words_sort (struct file_t** files, enum error_code_t* error);
```

Funkcja ma za zadanie posortować rosnąco (alfabetycznie) słowa odczytane z każdego
z plików. Sortowane są niezależnie tablice `struct word_t** words` w każdej ze struktur
`struct file_t`.

gdzie:

*   `files` - wskaźnik do tablicy, w której mają zostać posortowane przechowywane słowa,
*   `error` - adres zmiennej, w której zachowany będzie kod błędu.

Przykład:

Plik `files.txt` zawiera listę plików:

```
plik1.txt
plik2.txt
```

Zawartość pliku `plik1.txt`:

```
Ala ma kota. Ala nie ma kota.
```

Zawartość pliku `plik2.txt`:

```
hi hi hi ha ha ha
```

Przykład działania funkcji:

```
file1.txt
Ala 2
kota 2
ma 2
nie 1
file2.txt
ha 3
hi 3
```

---

Uwagi

*   Wszystkie operacje na tablicach powinny być wykonywane za pomocą wskaźników,
    a nie operatora `[]`.
*   W programie można zadeklarować pomocniczą tablice, deklaracja tablicy musi
    wyglądać następująco:

    ```c
    char text[31];
    ```

---

---Rozszerz poprzednie zadanie o następującą funkcje (ocena 5,0)---

```c
void words_save (const char* filename, const struct file_t** files,
                 enum error_code_t* error);
```

Funkcja zapisuje do pliku binarnego listy posortowanych słów odczytanych z plików
tekstowych.

gdzie:

*   `filename` - nazwa zapisywanego pliku,
*   `files` - wskaźnik do tablicy, której zawartość ma zostać zapisana,
*   `error` - adres zmiennej, w której zachowany będzie kod błędu.

Funkcja zapisuje do pliku binarnego w następującym formacie:

```
4 bajty - ilość plików
4 bajty - długość nazwy pliku 1
n bajtów - nazwa pliku 1 (wraz ze znakiem końca łańcucha)
4 bajty - ilość słów w pliku 1
4 bajty - długość słowa 1
n bajtów - słowo 1 (wraz ze znakiem końca łańcucha)
4 bajty - ilość wystąpień słowa 1
...
4 bajty - długość słowa N
n bajtów - słowo N (wraz ze znakiem końca łańcucha)
4 bajty - ilość wystąpień słowa N
4 bajty - długość nazwy pliku N
n bajtów - nazwa pliku N (wraz ze znakiem końca łańcucha)
4 bajty - ilość słów w pliku N
4 bajty - długość słowa 1
n bajtów - słowo 1 (wraz ze znakiem końca łańcucha)
4 bajty - ilość wystąpień słowa 1
...
4 bajty - długość słowa N
n bajtów - słowo N (wraz ze znakiem końca łańcucha)
4 bajty - ilość wystąpień słowa N
```

---

Uwagi

*   Wszystkie operacje na tablicach powinny być wykonywane za pomocą wskaźników,
    a nie operatora `[]`.
*   W programie można zadeklarować pomocniczą tablice, deklaracja tablicy musi
    wyglądać następująco:

    ```c
    char text[31];
    ```