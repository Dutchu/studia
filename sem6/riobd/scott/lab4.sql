--PROCEDURE
-- 1. Zdefiniuj procedurę, która wyświetli na ekranie imię, nazwisko oraz pensję pracownika o identyfikatorze podanym jako pierwszy parametr. Jeżeli nie ma takiego id to zwrócony zostanie informacja o braku takiego pracownika.
CREATE OR REPLACE PROCEDURE p_pokainfo(
    id IN NUMBER
) AS
    name   VARCHAR2(50);
    salary NUMBER(10, 2);
BEGIN
    SELECT ENAME, SAL
    INTO name, salary
    FROM EMP
    WHERE EMPNO = id;

    DBMS_OUTPUT.PUT_LINE('Nazwisko: ' || name);
    DBMS_OUTPUT.PUT_LINE('Pieniazki: ' || salary);
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('Nie znaleziono pracownika o danym id: ' || id);
END p_pokainfo;
/
BEGIN
    P_POKAINFO(101);
end;

-- 2. Zdefiniować procedurę, która zwróci liczbę zatrudnionych wszystkich pracowników.
CREATE OR REPLACE PROCEDURE p_liczprac AS
    licz NUMBER;
BEGIN
    SELECT COUNT(*) INTO licz FROM EMP;
    DBMS_OUTPUT.PUT_LINE('Liczba pracownikow: ' || licz);
END p_liczprac;
/
BEGIN
    p_liczprac();
END;

-- 3. Zdefiniować procedurę, która zwróci liczbę departamentów bez pracowników.
CREATE OR REPLACE PROCEDURE p_depnoemp AS
    dept_cnt NUMBER;
BEGIN
    SELECT COUNT(*)
    INTO dept_cnt
    FROM DEPT d
             LEFT JOIN EMP e ON d.DEPTNO = e.DEPTNO
    WHERE e.EMPNO IS NULL;

    DBMS_OUTPUT.PUT_LINE('Liczba departamentow bez pracownikow: ' || dept_cnt);
END p_depnoemp;
/
BEGIN
    p_depnoemp();
END;

-- 4. Zdefiniować procedurę, która zwróci liczbę zatrudnionych w danym departamencie podanym jako pierwszy parametr typu IN. Parametr drugi typu OUT zwróci liczbę zatrudnionych.
CREATE OR REPLACE PROCEDURE p_empindept(
    dept_no IN NUMBER,
    emp_cnt OUT NUMBER
) AS
BEGIN
    SELECT COUNT(*)
    INTO emp_cnt
    FROM EMP
    WHERE DEPTNO = dept_no;

    DBMS_OUTPUT.PUT_LINE('Liczba pracownikow w departamencie ' || dept_no || ': ' || emp_cnt);
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        emp_cnt := 0;
        DBMS_OUTPUT.PUT_LINE('Brak pracownikow w departamencie: ' || dept_no);
END p_empindept;
/
DECLARE
    num NUMBER;
BEGIN
    p_empindept(50, num);
END;

-- 5. Zdefiniować procedurę, która zwróci liczbę zatrudnionych w danym departamencie na danym stanowisku pracy podanym odpowiednio jako pierwszy i drugi parametr typu IN.
-- Parametr trzeci typu OUT zwróci liczbę zatrudnionych.
CREATE OR REPLACE PROCEDURE p_empinjob(
    dept_no IN NUMBER,
    job IN VARCHAR2,
    emp_cnt OUT NUMBER
) AS
BEGIN
    SELECT COUNT(*)
    INTO emp_cnt
    FROM EMP
    WHERE DEPTNO = dept_no
      AND JOB = job;

    DBMS_OUTPUT.PUT_LINE('Number of employees in department ' || dept_no || ' with job ' || job || ': ' || emp_cnt);
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        emp_cnt := 0;
        DBMS_OUTPUT.PUT_LINE('No employees found in department ' || dept_no || ' with job ' || job);
END p_empinjob;
/
DECLARE
    num NUMBER;
BEGIN
    p_empinjob(30, 'SALESMAN', num);
END;

-- 6. Zdefiniuj procedurę, która dla danego departamentu wyświetli wszystkie nazwiska i imiona pracowników.
CREATE OR REPLACE PROCEDURE p_demptempinfo(
    dept_no IN NUMBER
) AS
    name EMP.ENAME % TYPE;
    CURSOR c_emp IS
        SELECT ENAME
        FROM EMP
        WHERE DEPTNO = dept_no;
BEGIN
    OPEN c_emp;
    LOOP
        FETCH c_emp INTO name;
        EXIT WHEN c_emp % NOTFOUND;
        DBMS_OUTPUT.PUT_LINE('Nazwiowsko pracownika: ' || name);
    END LOOP;
    CLOSE c_emp;
EXCEPTION
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('Wystapil nieoczekiwany blad: ' || SQLERRM);
END p_demptempinfo;
/

BEGIN
    p_demptempinfo(30);
END;

-- 7. Zdefiniuj procedurę która jako parametr wejściowy przyjmie id managera, a parametrem wyjściowym zwróci średnią zarobków osób podległych pod tego managera.
CREATE OR REPLACE PROCEDURE p_avgsal(
    manid IN NUMBER,
    avgsal OUT NUMBER
) AS
BEGIN
    SELECT AVG(SAL)
    INTO avgsal
    FROM EMP
    WHERE MGR = manid;

    DBMS_OUTPUT.PUT_LINE('Srednia zarobkow pod zarzadami menadzera o ID ' || manid || ' to ' || avgsal);
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        avgsal := 0;
        DBMS_OUTPUT.PUT_LINE('Nie znaleziono menadzera o ID: ' || manid);
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('Wystapil niespodziewany blad: ' || SQLERRM);
END p_avgsal;
/
DECLARE
    num NUMBER;
BEGIN
    p_avgsal(7698, num);
END;

-- FUNCTION
-- 1. Zdefiniować funkcję, która wycina spacje na początku i końcu zmiennej typu VARCHAR2 i zwraca to co zostanie.
CREATE OR REPLACE FUNCTION f_trim(
    input VARCHAR2
) RETURN VARCHAR2 AS
BEGIN
    RETURN TRIM(input);
END f_trim;
/
DECLARE
    trimed VARCHAR2(100);
BEGIN
    trimed := f_trim('   Hello World   ');
    DBMS_OUTPUT.PUT_LINE('Przyciety tekst: "' || trimed || '"');
END;
/

-- 2. Zdefiniować funkcję, która sprawdza czy dana liczba całkowita jest parzysta czy nieparzysta i zwraca wartość 'Parzysta' lub 'Nieparzysta'.
CREATE OR REPLACE FUNCTION f_parzystosc(
    num IN NUMBER
) RETURN VARCHAR2 AS
BEGIN
    IF MOD(num, 2) = 0 THEN
        RETURN 'Parzysta';
    ELSE
        RETURN 'Nieparzysta';
    END IF;
END f_parzystosc;
/
DECLARE
    res VARCHAR2(20);
BEGIN
    res := f_parzystosc(5);
    DBMS_OUTPUT.PUT_LINE('Liczba jest: ' || res);
END;
/

-- 3. Zdefiniować funkcję, która zwraca z daty podanej jako parametr wejściowy dzień tygodnia w języku polskim.
CREATE OR REPLACE FUNCTION f_polskidzien(
    data IN DATE
) RETURN VARCHAR2 AS
    dzien VARCHAR2(20);
BEGIN
    dzien := TO_CHAR(data, 'D');

    RETURN CASE
               WHEN dzien = '1' THEN 'Poniedzialek'
               WHEN dzien = '2' THEN 'Wtorek'
               WHEN dzien = '3' THEN 'Sroda'
               WHEN dzien = '4' THEN 'Czwartek'
               WHEN dzien = '5' THEN 'Piatek'
               WHEN dzien = '6' THEN 'Sobota'
               WHEN dzien = '7' THEN 'Niedziela'
        END;
END f_polskidzien;
/
DECLARE
    dzien VARCHAR2(20);
BEGIN
    dzien := f_polskidzien(SYSDATE);
    DBMS_OUTPUT.PUT_LINE('Dzien po polsku: ' || dzien);
END;
/

-- 4. Zdefiniować funkcję, która będzie zwracać średnią zarobków w dziale, którego numer funkcja będzie przyjmować jako parametr.
CREATE OR REPLACE FUNCTION f_deptavg(
    dept_no IN NUMBER -- Input parameter for department number
) RETURN NUMBER AS
    svgsal NUMBER;
BEGIN
    SELECT AVG(SAL)
    INTO svgsal
    FROM EMP
    WHERE DEPTNO = dept_no;

    RETURN svgsal;
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        RETURN NULL;
    WHEN OTHERS THEN
        RETURN NULL;
END f_deptavg;
/
SELECT f_deptavg(20) AS srednia
FROM DUAL;

-- 5. Zdefiniować funkcję z trzema parametrami, która sprawdzi czy dane boki tworzą trójkąt, a jeśli tak to obliczy jego pole.
CREATE OR REPLACE FUNCTION f_powierzchnia(
    bok1 IN NUMBER,
    bok2 IN NUMBER,
    bok3 IN NUMBER
) RETURN NUMBER AS
    temp NUMBER;
    area NUMBER;
BEGIN
    IF (bok1 + bok2 > bok3) AND
       (bok1 + bok3 > bok2) AND
       (bok2 + bok3 > bok1) THEN

        temp := (bok1 + bok2 + bok3) / 2;

        area := SQRT(temp *
                     (temp - bok1) *
                     (temp - bok2) *
                     (temp - bok3));
        RETURN area;
    ELSE
        RETURN NULL;
    END IF;
END f_powierzchnia;
/
SELECT f_powierzchnia(3, 4, 5) AS area
FROM DUAL;

-- 6. Zdefiniować funkcję zamieniającą wszystkie spacje podkreśleniem.
CREATE OR REPLACE FUNCTION f_podmianka(
    input VARCHAR2
) RETURN VARCHAR2 AS
    v_result VARCHAR2(4000);
BEGIN
    v_result := REPLACE(input, ' ', '_');

    RETURN v_result;
END f_podmianka;
/
SELECT f_podmianka('Dzien Dobry! Siemasz Eniu, wszystko dobrze?') AS modified_text
FROM DUAL;

-- 7. Zdefiniować funkcję do odwracania stringu.
CREATE OR REPLACE FUNCTION f_odwrot(
    input VARCHAR2
) RETURN VARCHAR2 AS
    odwrot VARCHAR2(4000) := '';
    dlg    NUMBER;
BEGIN
    dlg := LENGTH(input);

    FOR i IN REVERSE 1..dlg
        LOOP
            odwrot := odwrot || SUBSTR(input, i, 1);
        END LOOP;

    RETURN odwrot;
END f_odwrot;
/
SELECT f_odwrot('Siema Heniu!') AS reversed_string
FROM DUAL;

-- 8. Zdefiniować funkcję PESEL, która sprawdza czy liczba jest poprawnym typem CHAR o określonej długości zawierający tylko cyfry od 0-9 (nie sprawdzamy poprawności funkcji PESEL).
CREATE OR REPLACE FUNCTION f_pesel(
    input CHAR
) RETURN VARCHAR2 AS
BEGIN
    IF LENGTH(input) = 11 AND REGEXP_LIKE(input, '^[0-9]{11}$') THEN
        RETURN 'Wlasciwy PESEL';
    ELSE
        RETURN 'Niewlasciwy PESEL';
    END IF;
END f_pesel;
/
SELECT f_pesel('12345678901') AS result
FROM DUAL;

-- 9. Zdefiniować funkcję, która sprawdza czy dana liczba jest liczbą pierwszą.
CREATE OR REPLACE FUNCTION f_prime(
    num IN NUMBER
) RETURN VARCHAR2 AS
    i NUMBER;
BEGIN
    IF num <= 1 THEN
        RETURN 'Liczba nie jest pierwsza';
    END IF;

    FOR i IN 2 .. FLOOR(SQRT(num))
        LOOP
            IF MOD(num, i) = 0 THEN
                RETURN 'Liczba nie jest pierwsza';
            END IF;
        END LOOP;

    RETURN 'Liczba pierwsza';
END f_prime;
/
SELECT f_prime(17) AS result FROM DUAL;

-- 10. Zdefiniować funkcję do obliczenia wartości silnia z liczby całkowitej (zdefiniować obsługę błędów w przypadku liczb mniejszych od 1 i takich,
-- które przekroczą zakres wykorzystywanego typu).
CREATE OR REPLACE FUNCTION f_factorial (
    num IN NUMBER
) RETURN NUMBER AS
    wynik NUMBER := 1;
BEGIN
    IF num < 1 THEN
        RAISE_APPLICATION_ERROR(-20001, 'Input must be a positive integer greater than or equal to 1.');
    END IF;

    FOR i IN 1 .. num LOOP
        wynik := wynik * i;

        IF wynik > 1E38 THEN
            RAISE_APPLICATION_ERROR(-20002, 'Result exceeds the maximum allowable value for the NUMBER type.');
        END IF;
    END LOOP;

    RETURN wynik;

EXCEPTION
    WHEN OTHERS THEN
        RETURN NULL;
END f_factorial;
/

SELECT f_factorial(5) AS factorial_result FROM DUAL;