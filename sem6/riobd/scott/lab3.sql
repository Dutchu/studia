SET SERVEROUTPUT ON;
/*
Każdy z wyzwalaczy sprawdzamy czy działa po czym wyłączamy go przed realizacją następnego zadnia.
Wyzwalacze mają być typu FOR EACH ROW.
 */
-- 1. Zdefiniować wyzwalacz na tabeli EMPLOYEES, który przy wstawieniu lub modyfikowaniu danych pole
-- LAST_NAME i FIRST_NAME będzie zamieniane na duże litery.
CREATE OR REPLACE TRIGGER t_big
    BEFORE INSERT OR UPDATE
    ON SCOTT.EMP
    FOR EACH ROW
BEGIN
    :NEW.ENAME := UPPER(:NEW.ENAME);
END;
/
DROP TRIGGER t_big;
INSERT INTO EMP (EMPNO, ENAME, JOB, MGR, HIREDATE, SAL, COMM, DEPTNO)
VALUES (23, 'elomelo', 'obibok', 1232, CURRENT_DATE, NULL, NULL, NULL)
DELETE
FROM EMP
WHERE EMPNO = 23;
SELECT *
FROM EMP;
ALTER TRIGGER T_BIG DISABLE;

-- 2. Zdefiniować wyzwalacz na tabeli EMPLOYEES, który z wykorzystaniem sekwencji wcześniej utworzonej
-- będzie numerował EMPLOYEE_ID tabeli od wartości 210 i do wartości maksymalnie 999999.
CREATE SEQUENCE emp_id_seq
    START WITH 210
    INCREMENT BY 1
    MAXVALUE 999999
    NOCYCLE;

create or replace trigger t_index
    before insert
    on EMP
    for each row
begin
    IF :NEW.EMPNO IS NULL THEN
        :new.empno := emp_id_seq.nextval;
    end if;
end;
/
INSERT INTO EMP (EMPNO, ENAME, JOB, MGR, HIREDATE, SAL, COMM, DEPTNO)
VALUES (NULL, 'elomelo', 'obibok', 1232, CURRENT_DATE, NULL, NULL, NULL)
DELETE
FROM EMP
WHERE EMPNO = 210;
SELECT *
FROM EMP;
ALTER TRIGGER t_index DISABLE;

-- 3. Zdefiniować wyzwalacz na tabeli EMPLOYEES, który sprawdzi czy pole HIRE_DATE jest mniejsze lub równe
-- dacie systemowej +-10 dni przy wstawianiu nowego pracownika lub jego modyfikacji. Jeśli nie, zwrócony
-- zostanie komunikat o błędzie a transakcja zostanie wycofana.
create or replace trigger t_hire
    before insert or update
    on EMP
    for each row
begin
    if :new.HIREDATE < (SYSDATE - 10) OR :NEW.HIREDATE > (SYSDATE + 10) THEN
        RAISE_APPLICATION_ERROR(-20001, 'Przedział czasu HIREDATE w granicach (-10, +10) dni od dzisiaj.');
    end if;
end;
/
INSERT INTO EMP (EMPNO, ENAME, JOB, MGR, HIREDATE, SAL, COMM, DEPTNO)
VALUES (23, 'elomelo', 'obibok', 1232, CURRENT_DATE - 11, NULL, NULL, NULL);
DELETE
FROM EMP
WHERE EMPNO = 23;
SELECT *
FROM EMP;
ALTER TRIGGER t_hire DISABLE;

-- 4. Zdefiniować wyzwalacz na tabeli EMPLOYEES, który wyświetli komunikat na ekranie jaki użytkownik
-- został skasowany, wstawiony lub zmodyfikowany.
create or replace trigger t_disp
    before insert or update or delete
    on EMP
    for each row
begin
    IF INSERTING THEN
        DBMS_OUTPUT.PUT_LINE('EMP o imieniu: ' || :NEW.ENAME || ' wstawiony do tabeli EMP');
    ELSIF UPDATING THEN
        DBMS_OUTPUT.PUT_LINE('EMP o imieniu: ' || :NEW.ENAME || ' zostal zmodyfikowany w tableli EMP');
    ELSIF DELETING THEN
        DBMS_OUTPUT.PUT_LINE('EMP o imieniu: ' || :NEW.ENAME || ' zostal usunienty z tabeli EMP');
    end if;
end;
/
INSERT INTO EMP (EMPNO, ENAME, JOB, MGR, HIREDATE, SAL, COMM, DEPTNO)
VALUES (23, 'elomelo', 'obibok', 1232, CURRENT_DATE - 11, NULL, NULL, NULL);
DELETE
FROM EMP
WHERE EMPNO = 23;
SELECT *
FROM EMP;
ALTER TRIGGER t_disp DISABLE;

-- 5. Zdefiniować wyzwalcz na tabeli EMPLOYEES, który przy kasowaniu lub modyfikowaniu pracownika zapisze
-- wszystkie dane do tabeli EMP_HIST z dodatkowymi polami tj. data_czas_operacji oraz typ_operacji
-- (DELETE, UPDATE) - wcześniej trzeba przygotować daną tabelę.
CREATE TABLE EMP_HIST (
    EMPNO NUMBER,
    ENAME VARCHAR2(100),
    JOB VARCHAR2(100),
    MGR NUMBER,
    HIREDATE DATE,
    SAL NUMBER,
    COMM NUMBER,
    DEPTNO NUMBER,
    data_czas_operacji TIMESTAMP DEFAULT SYSTIMESTAMP,
    typ_operacji VARCHAR2(10)
);
CREATE OR REPLACE TRIGGER t_hist
    AFTER DELETE OR UPDATE ON EMP
    FOR EACH ROW
BEGIN
    IF DELETING THEN
        INSERT INTO EMP_HIST (EMPNO, ENAME, JOB, MGR, HIREDATE, SAL, COMM, DEPTNO, data_czas_operacji, typ_operacji)
        VALUES (:OLD.EMPNO, :OLD.ENAME, :OLD.JOB, :OLD.MGR, :OLD.HIREDATE, :OLD.SAL, :OLD.COMM, :OLD.DEPTNO, SYSTIMESTAMP, 'DELETE');

    ELSIF UPDATING THEN
        INSERT INTO EMP_HIST (EMPNO, ENAME, JOB, MGR, HIREDATE, SAL, COMM, DEPTNO, data_czas_operacji, typ_operacji)
        VALUES (:OLD.EMPNO, :OLD.ENAME, :OLD.JOB, :OLD.MGR, :OLD.HIREDATE, :OLD.SAL, :OLD.COMM, :OLD.DEPTNO, SYSTIMESTAMP, 'UPDATE');
    END IF;
END;
/
INSERT INTO EMP (EMPNO, ENAME, JOB, MGR, HIREDATE, SAL, COMM, DEPTNO)
VALUES (23, 'elomelo', 'obibok', 1232, CURRENT_DATE - 11, 100, NULL, NULL);
UPDATE EMP SET SAL = SAL + 100 WHERE EMPNO = 23;
DELETE FROM EMP WHERE EMPNO = 23;
SELECT *
FROM EMP;
SELECT *
FROM EMP_HIST;
ALTER TRIGGER t_hist DISABLE;

-- 6. Zdefiniować widok na tabeli EMPLOYEES i DEPARTMENTS. Na widoku zdefiniować wyzwalacz typu
-- INSTEAD OF, który przy poleceniu INSERT na widoku doda użytkownika, który nie będzie miał
-- przypisanego żadnego departamentu.
CREATE OR REPLACE VIEW W_EMPDEP AS
SELECT
    E.EMPNO,
    E.ENAME,
    E.JOB,
    E.MGR,
    E.HIREDATE,
    E.SAL,
    E.COMM,
    E.DEPTNO,
    D.DNAME,
    D.LOC
FROM EMP E
LEFT JOIN SCOTT.DEPT D ON E.DEPTNO = D.DEPTNO;
CREATE OR REPLACE TRIGGER t_nodep
INSTEAD OF INSERT ON W_EMPDEP
FOR EACH ROW
BEGIN
    INSERT INTO EMP (EMPNO, ENAME, JOB, MGR, HIREDATE, SAL, COMM, DEPTNO)
    VALUES (:NEW.EMPNO, :NEW.ENAME, :NEW.JOB, :NEW.MGR, :NEW.HIREDATE, :NEW.SAL, :NEW.COMM, NULL);
END;
/
INSERT INTO W_EMPDEP (EMPNO, ENAME, JOB, MGR, HIREDATE, SAL, COMM)
VALUES (101, 'jonasz', 'dozorca', 1001, SYSDATE, 5000, NULL);
SELECT * FROM W_EMPDEP;
ALTER TRIGGER t_nodep DISABLE;

-- 7. Zdefiniować wyzwalacz, który reaguje na pensję mniejszą od zera i wtedy zmienia jej wartość na 0.
CREATE OR REPLACE TRIGGER t_sal
BEFORE INSERT ON EMP
FOR EACH ROW
BEGIN
    IF :NEW.SAL < 0 THEN
        :NEW.SAL := 0;
    END IF;
END;
/
INSERT INTO EMP (EMPNO, ENAME, JOB, MGR, HIREDATE, SAL, COMM, DEPTNO)
VALUES (23, 'elomelo', 'obibok', 1232, CURRENT_DATE - 11, -100, NULL, NULL);
DELETE FROM EMP WHERE EMPNO = 23;
SELECT * FROM EMP;
ALTER TRIGGER t_sal DISABLE;

-- 8. Zdefiniować wyzwalacz na tabeli DEPARTMENTS, która zadziała przy modyfikacji pola DEPTARTMENT_ID i
-- jednocześnie zaktualizuje numer departamnetu wszystkim pracownikom pracującym w tym
-- departamencie w tabeli EMPLOYEES (tzw. kaskadowa aktualizacja - ON CASCADE UPDATE dla systemu MS
-- SQL SERVER).
create or replace trigger t_casc
    AFTER UPDATE ON DEPT
    FOR EACH ROW
    BEGIN
        UPDATE EMP
        SET DEPTNO = :NEW.DEPTNO
        WHERE DEPTNO = :OLD.DEPTNO;
    END;
/
UPDATE DEPT
SET DEPTNO = 50
WHERE DEPTNO = 10;
SELECT * FROM EMP WHERE DEPTNO = 50;
ALTER TRIGGER t_casc DISABLE;

-- 9. Zdefiniować wyzwalacz, który zapewni, że żaden pracownik nie otrzyma podwyżki większej niż 10%.
-- Dodatkowo zmiana taka ma być zarejestrowana w bazie danych w tabeli REJESTR_ZMIAN z polami
-- (Nazwisko_pracownika, data, pensja_stara, pensja_nowa, akcja).
-- Akcja podaje informację słowną ('wstawiono_rekord' lub 'Zmodyfikowano rekord') w zależności czy
-- pracownik nowy czy już jest w bazie i jest modyfikowana jego pensja (jeden wyzwalacz działa na polecenie
-- INSERT i UPDATE na polu SALARY). W przypadku głównego szefa 'PRESIDENT' ta zasada nie działa czy
-- wyzwalacz nie uruchamian się (klauzla WHEN)
CREATE TABLE REJESTR_ZMIAN (
    Nazwisko_pracownika VARCHAR2(100),
    data DATE DEFAULT SYSDATE,
    pensja_stara NUMBER,
    pensja_nowa NUMBER,
    akcja VARCHAR2(50)
);
CREATE OR REPLACE TRIGGER t_payctrl
BEFORE INSERT OR UPDATE OF SAL ON EMP
FOR EACH ROW
WHEN (NEW.JOB != 'PRESIDENT')
BEGIN
    IF INSERTING THEN

        IF :NEW.SAL > (:OLD.SAL * 1.1) THEN
            RAISE_APPLICATION_ERROR(-20002, 'Podwyzka nie moze byc wieksza niz 10%!');
        END IF;

        INSERT INTO REJESTR_ZMIAN (Nazwisko_pracownika, data, pensja_stara, pensja_nowa, akcja)
        VALUES (:NEW.ENAME, SYSDATE, :OLD.SAL, :NEW.SAL, 'wstawiono_rekord');
    ELSIF UPDATING THEN

        IF :NEW.SAL > (:OLD.SAL * 1.1) THEN
            RAISE_APPLICATION_ERROR(-20002, 'Podwyzka nie może byc wieksza niz 10%!');
        END IF;

        INSERT INTO REJESTR_ZMIAN (Nazwisko_pracownika, data, pensja_stara, pensja_nowa, akcja)
        VALUES (:NEW.ENAME, SYSDATE, :OLD.SAL, :NEW.SAL, 'Zmodyfikowano rekord');
    END IF;
END;
/
INSERT INTO EMP (EMPNO, ENAME, JOB, MGR, HIREDATE, SAL, COMM, DEPTNO)
VALUES (101, 'burczymucha', 'wazniak', 1001, SYSDATE, 5000, NULL, 10);
SELECT * FROM EMP;
DELETE FROM EMP WHERE EMPNO = 101;
UPDATE EMP
SET SAL = SAL + 600
WHERE EMPNO = 101;
SELECT * FROM REJESTR_ZMIAN;
ALTER TRIGGER t_payctrl DISABLE;

-- 10. Mamy widok, który zawiera dane pracownika i nazwę departamentu, do którego należy (z tabeli
-- departments). Zdefiniować wyzwalacz na tabeli, który sprawdzi numer departamentu i wstawi do tabeli
-- pracownicy. Jeżeli nie ma takiego numeru departamentu to wstawiamy NULL.
CREATE OR REPLACE TRIGGER t_nulldep
INSTEAD OF INSERT ON W_EMPDEP
FOR EACH ROW
DECLARE
    v_dept_count NUMBER;
BEGIN
    SELECT COUNT(*)
    INTO v_dept_count
    FROM DEPT
    WHERE DEPTNO = :NEW.DEPTNO;

    IF v_dept_count = 0 THEN
        INSERT INTO EMP (EMPNO, ENAME, JOB, MGR, HIREDATE, SAL, COMM, DEPTNO)
        VALUES (:NEW.EMPNO, :NEW.ENAME, :NEW.JOB, :NEW.MGR, :NEW.HIREDATE, :NEW.SAL, :NEW.COMM, NULL);
    ELSE
        INSERT INTO EMP (EMPNO, ENAME, JOB, MGR, HIREDATE, SAL, COMM, DEPTNO)
        VALUES (:NEW.EMPNO, :NEW.ENAME, :NEW.JOB, :NEW.MGR, :NEW.HIREDATE, :NEW.SAL, :NEW.COMM, :NEW.DEPTNO);
    END IF;
END;
/
INSERT INTO W_EMPDEP (EMPNO, ENAME, JOB, MGR, HIREDATE, SAL, COMM, DEPTNO)
VALUES (104, 'bozydar', 'pijafka', 1002, SYSDATE, 3000, NULL, 99);
SELECT * FROM EMP;
ALTER TRIGGER t_nulldep DISABLE;

-- 11. Zdefiniuj wyzwalacz na tabeli Departments, który wstawi rejestr wszystkich nazw departamnetu,
-- które są dokładane do tabeli DEPARTMENTS nawet te, które nie dodano ze względu na wycofanie
-- transakcji poleceniem ROLLBACK. Tabela REJESTR_DEPT z polami Nazwa_departamentu oraz
-- Data_wstawienia)
-- (wykorzystaj transakcje autonomiczne PRAGMA AUTONOMOUS_TRANSACTION)
CREATE TABLE REJESTR_DEPT (
    Nazwa_departamentu VARCHAR2(100),
    Data_wstawienia DATE DEFAULT SYSDATE
);
CREATE OR REPLACE TRIGGER t_log
BEFORE INSERT ON DEPT
FOR EACH ROW
DECLARE
    PRAGMA AUTONOMOUS_TRANSACTION;
BEGIN
    INSERT INTO REJESTR_DEPT (Nazwa_departamentu, Data_wstawienia)
    VALUES (:NEW.DNAME, SYSDATE);

    COMMIT;
END;
/
INSERT INTO DEPT (DEPTNO, DNAME, LOC)
VALUES (42, 'komnattajemnic', 'hogwart');
ROLLBACK;
SELECT * FROM REJESTR_DEPT;
ALTER TRIGGER t_log DISABLE;

-- 12. Zdefiniuj wyzwalacz, który sprawdzi czy dana nazwa departamentu nie powtarza się w bazie danych
-- (nie używamy ograniczenia UNIQUE). Jeśli tak to definiujemy wyjątek, który przekazujemy do bloku
-- instrukcji nadrzędnego, w którym wstawiany jest dany departament i tutaj obsługujemy dany błąd łącznie
-- z wycofaniem transakcji.
CREATE OR REPLACE TRIGGER t_unik
BEFORE INSERT OR UPDATE OF DNAME ON DEPT
FOR EACH ROW
DECLARE
    v_count NUMBER;
    duplicate_department EXCEPTION;
BEGIN
    SELECT COUNT(*)
    INTO v_count
    FROM DEPT
    WHERE DNAME = :NEW.DNAME
    AND (DEPTNO != :NEW.DEPTNO OR :NEW.DEPTNO IS NULL);

    IF v_count > 0 THEN
        RAISE duplicate_department;
    END IF;

EXCEPTION
    WHEN duplicate_department THEN
        RAISE_APPLICATION_ERROR(-20003, ' Nie moszna duplikatuf: ' || :NEW.DNAME);
END;
/
DECLARE
BEGIN
    INSERT INTO DEPT (DEPTNO, DNAME, LOC)
    VALUES (43, 'narnia', 'miszigan');

    COMMIT;

EXCEPTION
    WHEN OTHERS THEN

        IF SQLCODE = -20003 THEN
            DBMS_OUTPUT.PUT_LINE(SQLERRM);
            ROLLBACK;
        ELSE
            RAISE;
        END IF;
END;
/


INSERT INTO DEPT (DEPTNO, DNAME, LOC)
VALUES (44, 'mokotow', 'defaultcity');

BEGIN
    INSERT INTO DEPT (DEPTNO, DNAME, LOC)
    VALUES (45, 'mokotow', 'defaultcity');

    COMMIT;
EXCEPTION
    WHEN OTHERS THEN
        IF SQLCODE = -20003 THEN
            DBMS_OUTPUT.PUT_LINE(SQLERRM);
            ROLLBACK;
        ELSE
            RAISE;
        END IF;
END;
/


ALTER TRIGGER t_unik DISABLE;