SET SERVEROUTPUT ON;

SELECT *
FROM ALL_OBJECTS
WHERE OBJECT_NAME = 'DBMS_OUTPUT';
SELECT *
FROM DBA_OBJECTS
WHERE OBJECT_NAME = 'DBMS_OUTPUT';
--Opracować przykładowy blok PL/SQL z wykorzystaniem etykiety i instrukcji skoku sprawdzający, czy podana liczba jest liczbą pierwszą:

ALTER SESSION SET CURRENT_SCHEMA = SCOTT;
DECLARE
    n        NUMBER  := 29;
    i        NUMBER  := 2;
    is_prime BOOLEAN := TRUE;
BEGIN
    /*
      This block checks if the number 'n' is prime.
      It uses a loop to test divisibility by all integers from 2 up to the square root of n.
      If 'n' is divisible by any of these numbers, it is not prime.
    */
    <<check_prime>>
        IF i <= SQRT(n) THEN
        IF MOD(n, i) = 0 THEN
            is_prime := FALSE;
            GOTO end_check;
        END IF;
        i := i + 1;
        GOTO check_prime;
    END IF;

    <<end_check>>
        IF is_prime THEN
        DBMS_OUTPUT.PUT_LINE(n || ' is a prime number.');
    ELSE
        DBMS_OUTPUT.PUT_LINE(n || ' is not a prime number.');
    END IF;
END;

--Opracować przykładowy blok PL/SQL z wykorzystaniem etykiety i instrukcji skoku sprawdzający, czy dla zadeklarowanej zmiennej typu varchar - sprawdzi czy w podanym ciąguznajduje się cyfra:

DECLARE
    my_string VARCHAR2(100) := '12345';
    my_number NUMBER;
BEGIN
    my_number := TO_NUMBER(my_string);
    DBMS_OUTPUT.PUT_LINE('The string "' || my_string || '" is numeric.');
EXCEPTION
    WHEN VALUE_ERROR THEN
        DBMS_OUTPUT.PUT_LINE('The string "' || my_string || '" is not numeric.');
END;

/*
Zdefiniować blok PL/SQL sprawdzającą poprawność hasła :
- minimalna długość hasła(tzn. długość - min 4 znaki w tym 1 litera 1 cyfra 1 znak specjalny),- hasło nie takie samo jak użytkownik, etc.
- hasło nie może zawierać popularnych wyrazów: ‚ORACLE’, ‚HASŁO’, ‚12345’ itp.
W części deklaracyjnej bloku należy zadeklarować trzy zmienne „UZYTKOWNIK”,„STAREHASLO”, „NOWEHASLO”
*/

DECLARE
    UZYTKOWNIK          VARCHAR2(50) := 'JanKowalski';
    STAREHASLO          VARCHAR2(50) := 'StareHaslo1!';
    NOWEHASLO           VARCHAR2(50) := 'Nowe@Haslo2';
    min_length CONSTANT NUMBER       := 4;
    has_letter          BOOLEAN      := FALSE;
    has_digit           BOOLEAN      := FALSE;
    has_special         BOOLEAN      := FALSE;
    invalid             BOOLEAN      := FALSE;
BEGIN
    IF STAREHASLO LIKE NOWEHASLO THEN
        DBMS_OUTPUT.PUT_LINE('Blad: Haslo nie moze byc takie samo co poprzednie.');
        RETURN;
    END IF;
    IF LENGTH(NOWEHASLO) < min_length THEN
        DBMS_OUTPUT.PUT_LINE('Blad: Haslo musi miec minimum ' || min_length || ' znakow.');
        RETURN;
    END IF;
    IF UPPER(NOWEHASLO) = UPPER(UZYTKOWNIK) THEN
        DBMS_OUTPUT.PUT_LINE('Blad: Haslo nie moze byc takie samo co nazwa uzytkownika.');
        RETURN;
    END IF;
    IF INSTR(UPPER(NOWEHASLO), 'ORACLE') > 0 OR
       INSTR(UPPER(NOWEHASLO), 'HASŁO') > 0 OR
       INSTR(UPPER(NOWEHASLO), '12345') > 0 THEN
        DBMS_OUTPUT.PUT_LINE('Blad: Haslo zawiera popularne ciagi znakow.');
        RETURN;
    END IF;

    FOR i IN 1..LENGTH(NOWEHASLO)
        LOOP
            IF SUBSTR(NOWEHASLO, i, 1) BETWEEN 'A' AND 'Z' OR SUBSTR(NOWEHASLO, i, 1) BETWEEN 'a' AND 'z' THEN
                has_letter := TRUE;
            ELSIF SUBSTR(NOWEHASLO, i, 1) BETWEEN '0' AND '9' THEN
                has_digit := TRUE;
            ELSIF INSTR('!@#$%^&*()-_=+[{]}|\;:"'',<.>/?', SUBSTR(NOWEHASLO, i, 1)) > 0 THEN
                has_special := TRUE;
            END IF;
        END LOOP;

    IF NOT has_letter THEN
        DBMS_OUTPUT.PUT_LINE('Blad: Haslo musi zawierac przynajmniej jedna litere.');
        invalid := TRUE;
    END IF;

    IF NOT has_digit THEN
        DBMS_OUTPUT.PUT_LINE('Blad: Haslo musi zawierac przynajmniej jedna cyfre.');
        invalid := TRUE;
    END IF;

    IF NOT has_special THEN
        DBMS_OUTPUT.PUT_LINE('Blad: Haslo musi zawierac przynajmniej jeden znak specjalny.');
        invalid := TRUE;
    END IF;

    IF NOT invalid THEN
        DBMS_OUTPUT.PUT_LINE('Password is valid.');
    END IF;
END;
/