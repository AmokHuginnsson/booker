use mysql;
REVOKE ALL PRIVILEGES, GRANT OPTION FROM booker@localhost;
FLUSH PRIVILEGES;
DELETE FROM user WHERE user='booker' AND host='localhost';
-- from version 4.1.1 of mysql database we could use DROP USER command
DROP DATABASE IF EXISTS booker;
FLUSH PRIVILEGES;

