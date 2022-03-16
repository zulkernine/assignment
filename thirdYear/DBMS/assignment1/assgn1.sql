--Q1
CREATE TABLE EMP (
    EMP_CODE  char(5),
    EMP_NAME char(20),
    DEPT_CODE char(5),
    DESIG_CODE char(5),
    SEX char(1),
    ADDRESS char (25),
    CITY char (20),
    STATE char (20),
    PIN    char (6),
    BASIC DECIMAL(10,2),
    JN_DT Date,
    PRIMARY KEY(EMP_CODE)
);

CREATE TABLE DESIGNATION (
    DESIG_CODE CHAR(5),
    DESIG_DESC CHAR(20),
    PRIMARY KEY(DESIG_CODE)
);

CREATE TABLE DEPARTMENT (
    DEPT_CODE CHAR(5),
    DEPT_NAME CHAR(15),
    PRIMARY KEY(DEPT_CODE)
);

--Q3

INSERT INTO DESIGNATION
VALUES
    ('MAN43','MANAGER'),
    ('EXE65','EXECUTIVE'),
    ('OFF43','OFFICER'),
    ('CLK98','CLERK'),
    ('HLP85','HELPER');



INSERT INTO DEPARTMENT
VALUES
    ('PER54','PERSONNEL'),
    ('PRD98','PRODUCTION'),
    ('PRC09','PURCHASE'),
    ('FIN02','FINANCE'),
    ('RES84','RESEARCH');


INSERT INTO EMP
VALUES
    ('JH32K','CHIRANTAN NATH','FIN02','EXE65','M','1/A, TRIGUNA ROAD','DURGAPUR','713576',1902654,TO_DATE('17/12/2015', 'DD/MM/YYYY')),
    ('IOEJQ','AKASH SK','FIN02','OFF43','M','1/A, SUBHAS ROAD','ASANSOL','723999',1502654,DATE '2015-03-01','WEST BENGAL'),
    ('ADVNP','NEELADRI PL','PER54','CLK98','M','1/A, SAMIR ROAD','SANTIPUR','739423',2002654,DATE '2017-12-17','WEST BENGAL'),
    ('AHF32','SOUMITA PAL','RES84','MAN43','F','4/D, BIBADI ROAD','KOLKATA','700002',1702654,DATE '2011-12-06','WEST BENGAL');


--Q4
INSERT INTO EMP(EMP_CODE, EMP_NAME, DESIG_CODE, SEX, ADDRESS, CITY, STATE, PIN, JN_DT,)
VALUES
    ('KSI02','SRIRUPA RAY','HLP85','F','54A, ASAMI ROAD','DURGAPUR','713001',DATE '2015-12-02','WEST BENGAL'),
    ('WKEF5','SWARUP SAHA','OFF43','M','1SH, NH ROAD','KASIMBAJAR','742163',DATE '2012-03-01','WEST BENGAL');


--Q5
SELECT * 
FROM EMP
WHERE DEPT_CODE IS NULL;
/*
Output:
+----------+-------------+-----------+------------+------+-----------------+------------+--------+-------+------------+-------------+
| EMP_CODE | EMP_NAME    | DEPT_CODE | DESIG_CODE | SEX  | ADDRESS         | CITY       | PIN    | BASIC | JN_DT      | STATE       |
+----------+-------------+-----------+------------+------+-----------------+------------+--------+-------+------------+-------------+
| KSI02    | SRIRUPA RAY | NULL      | HLP85      | F    | 54A, ASAMI ROAD | DURGAPUR   | 713001 |  NULL | 2015-12-02 | WEST BENGAL |
| WKEF5    | SWARUP SAHA | NULL      | OFF43      | M    | 1SH, NH ROAD    | KASIMBAJAR | 742163 |  NULL | 2012-03-01 | WEST BENGAL |
+----------+-------------+-----------+------------+------+-----------------+------------+--------+-------+------------+-------------+
2 rows in set (0.01 sec)
*/

--Q6
SELECT *
FROM EMP
WHERE BASIC=0;
/*
OUTPUT: Empty set (0.00 sec)
*/

--Q7
SELECT *
FROM EMP
WHERE BASIC IS NULL;
/*
OUTPUT:
+----------+-------------+-----------+------------+------+-----------------+------------+--------+-------+------------+-------------+
| EMP_CODE | EMP_NAME    | DEPT_CODE | DESIG_CODE | SEX  | ADDRESS         | CITY       | PIN    | BASIC | JN_DT      | STATE       |
+----------+-------------+-----------+------------+------+-----------------+------------+--------+-------+------------+-------------+
| KSI02    | SRIRUPA RAY | NULL      | HLP85      | F    | 54A, ASAMI ROAD | DURGAPUR   | 713001 |  NULL | 2015-12-02 | WEST BENGAL |
| WKEF5    | SWARUP SAHA | NULL      | OFF43      | M    | 1SH, NH ROAD    | KASIMBAJAR | 742163 |  NULL | 2012-03-01 | WEST BENGAL |
+----------+-------------+-----------+------------+------+-----------------+------------+--------+-------+------------+-------------+
2 rows in set (0.00 sec)
*/


--Q8
SELECT AVG(BASIC)
FROM EMP;
/*
OUTPUT:
+----------------+
| AVG(BASIC)     |
+----------------+
| 1777654.000000 |
+----------------+
1 row in set (0.00 sec)
*/


--Q9
UPDATE EMP
SET BASIC=0
WHERE BASIC IS NULL;
/*
Query OK, 2 rows affected (0.01 sec)
Rows matched: 2  Changed: 2  Warnings: 0

-> Q6 NOW RETURNS:
+----------+-------------+-----------+------------+------+-----------------+------------+--------+-------+------------+-------------+
| EMP_CODE | EMP_NAME    | DEPT_CODE | DESIG_CODE | SEX  | ADDRESS         | CITY       | PIN    | BASIC | JN_DT      | STATE       |
+----------+-------------+-----------+------------+------+-----------------+------------+--------+-------+------------+-------------+
| KSI02    | SRIRUPA RAY | NULL      | HLP85      | F    | 54A, ASAMI ROAD | DURGAPUR   | 713001 |  0.00 | 2015-12-02 | WEST BENGAL |
| WKEF5    | SWARUP SAHA | NULL      | OFF43      | M    | 1SH, NH ROAD    | KASIMBAJAR | 742163 |  0.00 | 2012-03-01 | WEST BENGAL |
+----------+-------------+-----------+------------+------+-----------------+------------+--------+-------+------------+-------------+
2 rows in set (0.00 sec)
*/

--Q10
/*
->Q8 NEW AVG
+----------------+
| AVG(BASIC)     |
+----------------+
| 1185102.666667 |
+----------------+
1 row in set (0.00 sec)
*/

--Q11
DELETE FROM EMP
WHERE DEPT_CODE IS NULL;
/*
Query OK, 2 rows affected (0.01 sec)
*/

--Q12
SELECT EMP_NAME AS NAME, (BASIC + BASIC*0.5 + BASIC*0.4) AS NET_PAY
FROM EMP;
/*
+----------------+-------------+
| NAME           | NET_PAY     |
+----------------+-------------+
| NEELADRI PL    | 3805042.600 |
| SOUMITA PAL    | 3235042.600 |
| AKASH SK       | 2855042.600 |
| CHIRANTAN NATH | 3615042.600 |
+----------------+-------------+
4 rows in set (0.00 sec)
*/

--Q13
SELECT UPPER(EMP_NAME), BASIC
FROM EMP
ORDER BY DEPT_CODE ASC;
/*
+-----------------+------------+
| UPPER(EMP_NAME) | BASIC      |
+-----------------+------------+
| AKASH SK        | 1502654.00 |
| CHIRANTAN NATH  | 1902654.00 |
| NEELADRI PL     | 2002654.00 |
| SOUMITA PAL     | 1702654.00 |
+-----------------+------------+
4 rows in set (0.00 sec)
*/

--Q14
SELECT EMP_NAME
FROM EMP
WHERE JN_DT > ('1990-1-1');
/*
+----------------+
| EMP_NAME       |
+----------------+
| NEELADRI PL    |
| SOUMITA PAL    |
| AKASH SK       |
| CHIRANTAN NATH |
+----------------+
*/

--Q15
SELECT *
FROM EMP
WHERE to_char(JN_DT, 'mon')='jan'; --??


--Q16
SELECT MIN(BASIC) FROM EMP;
SELECT MAX(BASIC) FROM EMP;
/*
+------------+
| MIN(BASIC) |
+------------+
| 1502654.00 |
+------------+
| MAX(BASIC) |
+------------+
| 2002654.00 |
+------------+
*/


--Q17
SELECT COUNT(EMP_CODE)
FROM EMP
WHERE EMP.SEX = 'F';
/*
+-----------------+
| COUNT(EMP_CODE) |
+-----------------+
|               1 |
+-----------------+
*/

--Q18
UPDATE EMP
SET CITY = UPPER(CITY);
/*
Query OK, 0 rows affected (0.00 sec)
Rows matched: 4  Changed: 0  Warnings: 0
*/

--Q19
SELECT COUNT(DISTINCT CITY)
FROM EMP;
/*
+----------------------+
| COUNT(DISTINCT CITY) |
+----------------------+
|                    4 |
+----------------------+
*/

--Q20
SELECT *
FROM EMP
ORDER BY DEPT_CODE ASC,BASIC DESC;
/*
+----------+----------------+-----------+------------+------+-------------------+----------+--------+------------+------------+-------------+
| EMP_CODE | EMP_NAME       | DEPT_CODE | DESIG_CODE | SEX  | ADDRESS           | CITY     | PIN    | BASIC      | JN_DT      | STATE       |
+----------+----------------+-----------+------------+------+-------------------+----------+--------+------------+------------+-------------+
| JH32K    | CHIRANTAN NATH | FIN02     | EXE65      | M    | 1/A, TRIGUNA ROAD | DURGAPUR | 713576 | 1902654.00 | 2015-12-17 | WEST BENGAL |
| IOEJQ    | AKASH SK       | FIN02     | OFF43      | M    | 1/A, SUBHAS ROAD  | ASANSOL  | 723999 | 1502654.00 | 2015-03-01 | WEST BENGAL |
| ADVNP    | NEELADRI PL    | PER54     | CLK98      | M    | 1/A, SAMIR ROAD   | SANTIPUR | 739423 | 2002654.00 | 2017-12-17 | WEST BENGAL |
| AHF32    | SOUMITA PAL    | RES84     | MAN43      | F    | 4/D, BIBADI ROAD  | KOLKATA  | 700002 | 1702654.00 | 2011-12-06 | WEST BENGAL |
+----------+----------------+-----------+------------+------+-------------------+----------+--------+------------+------------+-------------+
*/

