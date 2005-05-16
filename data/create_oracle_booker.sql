/*

The idea.

Prerequirements: database instance is called `spoon'.

We create role that has permissions to modify data in database
(SELECT, INSERT, UPDATE, DELETE) with name `dml_role'.

We create role that has permission to create users, and grant dml_role
to them with name `ddl_role'.

We create user that will be owner of all stdhapi related
databases with name `root'.

We grant ddl_role and dml_role to user `root'.

We create user with quota 0 so he can not create his own objects
with name `booker' (this is application specific).
We add role `dml_role' on root's objects to user `booker'.

*/

/*{{{ Create and configure core stuff.*/
CREATE ROLE dml_role NOT IDENTIFIED;
CREATE ROLE ddl_role NOT IDENTIFIED;
GRANT CREATE USER, CREATE TABLE, CREATE ANY SYNONYM TO ddl_role;
GRANT CREATE SESSION TO dml_role;
CREATE USER root
	IDENTIFIED BY "4dm;n1qs"
	DEFAULT TABLESPACE "USERS"
	QUOTA 4M ON "USERS"
	ACCOUNT UNLOCK
	TEMPORARY TABLESPACE "TEMP";
GRANT ddl_role TO root;
GRANT dml_role TO root WITH ADMIN OPTION;
CONNECT root/"4dm;n1qs"@spoon
CREATE USER booker
	IDENTIFIED BY "b00k3r"
	DEFAULT TABLESPACE "USERS"
	QUOTA 0 ON "USERS"
	ACCOUNT UNLOCK
	TEMPORARY TABLESPACE "TEMP";
GRANT dml_role TO booker;
/*}}}*/

/*

Here we can create tables and add priopriate permissions to this tables
for user 'booker'.

*/

/*{{{ Create config table and all supplements.*/
DROP TABLE config;

CREATE TABLE config
	(
	id INTEGER PRIMARY KEY,
	name VARCHAR(16) UNIQUE NOT NULL,
	integer_value NUMBER(4),
	text_value VARCHAR(255),
	float_value NUMBER(8,8),
	time_value TIMESTAMP(0) DEFAULT CURRENT_TIMESTAMP,
	blob_value BLOB
	);

CREATE SEQUENCE config_sequence INCREMENT BY 1 START WITH 1 NOCACHE;

CREATE OR REPLACE TRIGGER config_autonumber
	BEFORE INSERT
	ON config
FOR EACH ROW

BEGIN
	SELECT config_sequence.NEXTVAL
		INTO :NEW.id
	FROM dual;
END config_autonumber;

CREATE SYNONYM booker.config FOR config;

CREATE SYNONYM booker.config_sequence FOR config_sequence;

GRANT SELECT,INSERT,UPDATE,DELETE ON root.config TO dml_role;
/*}}}*/

/*{{{ Create account_map table and all supplements.*/
DROP TABLE account_map;

CREATE TABLE account_map
	(
	id INTEGER PRIMARY KEY,
	id_account_map NUMBER(4) NOT NULL,
	short_number VARCHAR(8),
	full_number VARCHAR(32),
	name VARCHAR(128)
	);

CREATE SEQUENCE account_map_sequence INCREMENT BY 1 START WITH 1 NOCACHE;

CREATE OR REPLACE TRIGGER account_map_autonumber 
	BEFORE INSERT
	ON account_map
FOR EACH ROW

BEGIN
	SELECT account_map_sequence.NEXTVAL
		INTO :NEW.id
	FROM dual;
END account_map_autonumber;

CREATE SYNONYM booker.account_map FOR account_map;

CREATE SYNONYM booker.account_map_sequence FOR account_map_sequence;

GRANT SELECT,INSERT,UPDATE,DELETE ON root.account_map TO dml_role;
/*}}}*/

/*{{{ Create dictionary_bank table and all supplements.*/
DROP TABLE dictionary_bank;

CREATE TABLE dictionary_bank
	(
	id INTEGER PRIMARY KEY,
	name VARCHAR(128),
	country VARCHAR(32),
	city VARCHAR(32),
	street VARCHAR(128),
	street_number VARCHAR(8),
	postal_code VARCHAR(8),
	phone VARCHAR(32),
	fax VARCHAR(32)
	);

CREATE SEQUENCE dictionary_bank_sequence INCREMENT BY 1 START WITH 1 NOCACHE;

CREATE OR REPLACE TRIGGER dictionary_bank_autonumber
	BEFORE INSERT
	ON dictionary_bank
FOR EACH ROW

BEGIN
	SELECT dictionary_bank_sequence.NEXTVAL
		INTO :NEW.id
	FROM dual;
END dictionary_bank_autonumber;

CREATE SYNONYM booker.dictionary_bank FOR dictionary_bank;

CREATE SYNONYM booker.dictionary_bank_sequence FOR dictionary_bank_sequence;

GRANT SELECT,INSERT,UPDATE,DELETE ON root.dictionary_bank TO dml_role;
/*}}}*/

/*{{{ Create dictionary_contracting_party table and all supplements.*/
DROP TABLE dictionary_contracting_party;

CREATE TABLE dictionary_contracting_party
	(
	id INTEGER PRIMARY KEY,
	name VARCHAR(32),
	surname VARCHAR(32),
	tin VARCHAR(16),
	country VARCHAR(32),
	city VARCHAR(32),
	street VARCHAR(128),
	street_number VARCHAR(8),
	flat_number VARCHAR(8),
	postal_code VARCHAR(8),
	phone VARCHAR(32),
	fax VARCHAR(32),
	email VARCHAR(32),
	id_account_map NUMBER(4)
	);

CREATE SEQUENCE dictionary_contracting_party_sequence INCREMENT BY 1 START WITH 1 NOCACHE;

CREATE OR REPLACE TRIGGER dictionary_contracting_party_autonumber
	BEFORE INSERT
	ON dictionary_contracting_party
FOR EACH ROW

BEGIN
	SELECT dictionary_contracting_party_sequence.NEXTVAL
		INTO :NEW.id
	FROM dual;
END dictionary_contracting_party_autonumber;

CREATE SYNONYM booker.dictionary_contracting_party FOR dictionary_contracting_party;

CREATE SYNONYM booker.dictionary_contracting_party_sequence FOR dictionary_contracting_party_sequence;

GRANT SELECT,INSERT,UPDATE,DELETE ON root.dictionary_contracting_party TO dml_role;
/*}}}*/

