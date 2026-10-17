CREATE DATABASE IF NOT EXISTS Leo;
USE Leo;


create table instructor_347(
    id int,
    name varchar(50),
    dept_name varchar(50),
    salary decimal (10,2)
);

create table course_347(
    course_id varchar(20),
    title varchar(30),
    dept_name varchar(30),
    credits int
    );

-- Insert instructor_347
insert into instructor_347 values(10101,'Srinivasan','Comp.Sci',65000.50);
insert into instructor_347 values(12121,'Wasif','Finance',90000);
insert into instructor_347 values(151515,'Mozart','Music',40000);
insert into instructor_347 values(22222,'Einstein','Physics',95000);
insert into instructor_347 values(32343,'EL Said','History',60000);
insert into instructor_347 values(33456,'Goblin','Physics',87000.50);
insert into instructor_347 values(45565,'Katz','Comp.Sci',75000);
insert into instructor_347 values(58583,'Califieri','History',65000.50);

--course_347
insert into course_347 values('BIO-101','Intro.to Biology','Biology',4);
insert into course_347 values('BIO-301','Genetics','Biology',4);
insert into course_347 values('BIO-399','Computational Biology','Biology',3);
insert into course_347 values('CS-101','Intro.to Computer Science','Comp.Sci',4);
insert into course_347 values('CS-190','Game Design','Comp.Sci',4);
insert into course_347 values('CS-319','Image Processing','Comp.Sci',3);
insert into course_347 values('CS-347','Database System Concepts','Comp.Sci',3);
insert into course_347 values('EE-181','Intro.to Digital Systems','Elec.Eng',3);
insert into course_347 values('FIN-201','Investing Banking','Finance',3);

-- Drop table    
drop table instructor_347;
drop table course_347;

--Select
select * from instructor_347;
select * from course_347;

-- 1
SELECT count(id) from instructor_347;

-- 2
SELECT avg(salary) from instructor_347 where dept_name ='Comp.Sci';

-- 3
SELECT   max(salary) as leo  from instructor_347;

-- 4
SELECT dept_name ,sum(salary) from instructor_347 group by dept_name;

-- 5
SELECT dept_name ,count(id) from instructor_347 group by dept_name;

--6
SELECT min(salary) as Physics from instructor_347 where dept_name= 'physics';

-- 7- string rltd
SELECT * FROM instructor_347 where name like 'S%';



-- 10

SELECT dept_name , count(course_id) from course_347 group by dept_name;


--11
SELECT * from instructor_347 where name like '%a%';

-- 15
SELECT * from instructor_347 where name like '______';



