CREATE DATABASE IF NOT EXISTS data;
USE data;

CREATE TABLE customer_data(
    customer_id INT primary key,
    customer varchar(50),
    mode varchar(30),
    city varchar(50)
);

INSERT INTO customer_data VALUES (101,'Olivia','Netbanking','Portland');
INSERT INTO customer_data VALUES (102,'Ethan','Credit','Miami');
INSERT INTO customer_data VALUES (103,'Maya','Credit','Seattle');
INSERT INTO customer_data VALUES (104,'Sopiha','Netbanking','Dhaka');
INSERT INTO customer_data VALUES (105,'Liam','Credit','England');
INSERT INTO customer_data VALUES (106,'Sadim','Debit','Noakhali');
INSERT INTO customer_data VALUES (107,'Ray','Netbanking','Chadpur');
INSERT INTO customer_data VALUES (108,'Leo','Debit','Dhaka');

SELECT * FROM customer_data;

SELECT mode, count(customer) FROM customer_data GROUP BY mode;
drop DATABASE IF EXISTS data;