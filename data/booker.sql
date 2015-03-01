DROP TABLE test;
DROP TABLE test_dict;
DROP TABLE invoice_item;
DROP TABLE invoice;
DROP TABLE issuer;
DROP TABLE payment_method;
DROP TABLE contracting_party_account;
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
	name VARCHAR(256),
	first_name VARCHAR(64),
	middle_name VARCHAR(64),
	last_name VARCHAR(64),
	country VARCHAR(64),
	postal_code VARCHAR(16),
	city VARCHAR(64),
	street VARCHAR(256),
	street_number VARCHAR(64),
	flat_number VARCHAR(16),
	tin VARCHAR(16),
	email VARCHAR(64),
	webpage VARCHAR(128),
	phone VARCHAR(32),
	fax VARCHAR(32),
	extra VARCHAR(1024)
);

CREATE TABLE bank (
	id INTEGER PRIMARY KEY,
	name VARCHAR(128),
	country VARCHAR(32),
	city VARCHAR(32),
	street VARCHAR(128),
	street_number VARCHAR(8),
	postal_code VARCHAR(8),
	webpage VARCHAR(128),
	phone VARCHAR(32)
);

CREATE TABLE contracting_party_account (
	id INTEGER PRIMARY KEY,
	id_contracting_party INTEGER NOT NULL,
	id_bank INTEGER,
	iban VARCHAR(32)
);

CREATE TABLE payment_method (
	id INTEGER PRIMARY KEY,
	name VARCHAR(32)
);

CREATE TABLE issuer (
	id INTEGER PRIMARY KEY,
	name VARCHAR(255),
	signature VARCHAR(255)
);

CREATE TABLE invoice_type (
	id INTEGER PRIMARY KEY,
	name VARCHAR(32)
);

CREATE TABLE invoice (
	id INTEGER PRIMARY KEY,
	id_vendor INTEGER NOT NULL,
	id_vendee INTEGER NOT NULL,
	invoice_number VARCHAR(16),
	invoice_date DATE,
	transaction_date DATE,
	due_date INTEGER,
	id_pay_method INTEGER,
	id_invoice_type INTEGER,
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

CREATE TABLE test_dict (
	id INTEGER PRIMARY KEY,
	name VARCHAR(128)
);

CREATE TABLE test (
	id INTEGER PRIMARY KEY,
	id_test_dict INTEGER,
	v_text VARCHAR(255),
	v_int INTEGER,
	v_real FLOAT,
	v_date DATE,
	v_time TIME,
	v_datetime DATETIME
);

