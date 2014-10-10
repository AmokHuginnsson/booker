DROP TABLE test;
DROP TABLE invoice_item;
DROP TABLE invoice;
DROP TABLE issuer;
DROP TABLE pay_method;
DROP TABLE bank;
DROP TABLE contracting_party;
DROP TABLE config;

CREATE TABLE config (
	id INTEGER PRIMARY KEY,
	name VARCHAR(64) NOT NULL,
	integer_value INTEGER,
	text_value VARCHAR(255),
	float_value FLOAT,
	time_value DATETIME DEFAULT CURRENT_TIMESTAMP,
	blob_value TEXT
);

CREATE TABLE contracting_party (
	id INTEGER PRIMARY KEY,
	name VARCHAR(64),
	first_name VARCHAR(32),
	middle_name VARCHAR(32),
	last_name VARCHAR(32),
	country VARCHAR(64),
	postal_code VARCHAR(8),
	city VARCHAR(64),
	street VARCHAR(128),
	street_number VARCHAR(8),
	flat_number VARCHAR(8),
	tin VARCHAR(16),
	email VARCHAR(64),
	webpage VARCHAR(128),
	phone VARCHAR(32),
	fax VARCHAR(32),
	extra VARCHAR(255),
	id_bank INTEGER
);

CREATE TABLE bank (
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

CREATE TABLE pay_method (
	id INTEGER PRIMARY KEY,
	name VARCHAR(32)
);

CREATE TABLE issuer (
	id INTEGER PRIMARY KEY,
	name VARCHAR(255),
	signature VARCHAR(255)
);

CREATE TABLE invoice (
	id INTEGER PRIMARY KEY,
	id_vendor INTEGER NOT NULL,
	id_vendee INTEGER NOT NULL,
	invoice_number VARCHAR(16),
	invoice_date DATE,
	transaction_date DATE,
	due_date DATE,
	id_pay_method INTEGER,
	id_issuer INTEGER
);

CREATE TABLE invoice_item (
	id INTEGER PRIMARY KEY,
	id_invoice INTEGER NOT NULL,
	name VARCHAR(255) NOT NULL,
	price FLOAT,
	vat INTEGER,
	quantity INTEGER
);

CREATE TABLE test (
	id INTEGER PRIMARY KEY,
	name VARCHAR(128),
	v_text VARCHAR(255),
	v_int INTEGER,
	v_real FLOAT,
	v_date DATE,
	v_time TIME,
	v_datetime DATETIME
);

