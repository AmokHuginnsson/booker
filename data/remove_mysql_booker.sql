use mysql;
DELETE FROM user WHERE user='booker' AND host='localhost';
DROP DATABASE IF EXISTS booker;
FLUSH PRIVILEGES;

