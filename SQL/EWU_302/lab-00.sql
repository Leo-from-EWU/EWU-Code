-- create instructor and courses
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
-- xi
SELECT distinct dept_name from course_347;