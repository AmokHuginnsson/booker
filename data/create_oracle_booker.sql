/*

The idea.

We create user that will be owner of all stdhapi related
databases with name 'h_db_owner'.

We create role that has permissions to modify data in database
(SELECT, INSERT, UPDATE, DELETE) with name 'dml_role'.

We create user with quota 0 so hi can not create any own objects
with name 'booker' (this is application specific).
We add role 'dml_role' to user 'booker'.
We add access rights for user 'booker' to specyfic tables owned by
'h_db_owner'.

*/

CREATE OR REPLACE USER h_db_owner
	IDENTIFIED BY "hdb0wn3r"
	DEFAULT TABLESPACE "USERS"
	QUOTA 4M ON "USERS"
	ACCOUNT UNLOCK
	TEMPORARY TABLESPACE "TEMP";
CREATE OR REPLACE ROLE dml_role NOT IDENTIFIED;
GRANT SELECT,INSERT,UPDATE,DELETE TO dml_role;
GRANT CREATE SESSION TO dml_role;
CREATE OR REPLACE USER booker
	IDENTIFIED BY "b00k3r"
	DEFAULT TABLESPACE "USERS"
	QUOTA 0 ON "USERS"
	ACCOUNT UNLOCK
	TEMPORARY TABLESPACE "TEMP";
GRANT dml_role TO booker;

/*

Here we can create tables and add priopriate permissions to this tables
for user 'booker'.

*/

CREATE OR REPLACE TABLE config
 ... dalej nie wiem co.
