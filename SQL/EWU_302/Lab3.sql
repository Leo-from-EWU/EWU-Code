CREATE TABLE instructor_347(
    id number,
    name varchar2(20),
    dept_name varchar2(30),
    salary NUMBER(10,2)
);

create table course_347(
    course_id varchar2(20),
    title varchar(30),
    dept_name varchar(30),
    credits number
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

--Select
select * from instructor_347;
select * from course_347;


--i.
select name from instructor_347;
--ii
select course_id,title from course_347;
--iii
select name,dept_name from instructor_347 where id=22222;
--iv
select title,credits from course_347 where dept_name='Comp.Sci';
-- v
select name,dept_name from instructor_347 where salary>70000;
--vi
select title from course_347 where credits >=4;
--vii
select name,dept_name from instructor_347 where salary between 80000 and 100000;
--viii
select title,credits from course_347 where dept_name !='Comp.Sci';
--x
select * from course_347 where dept_name='Biology' and credits !=4;








