DROP TABLE dictionary_bank;
DROP TABLE dictionary_contracting_party;
DROP TABLE account_map;
DROP TABLE config;
CREATE TABLE config
	(
	id INTEGER PRIMARY KEY,
	name VARCHAR(16) NOT NULL,
	integer_value INT4,
	text_value VARCHAR(255),
	float_value FLOAT8,
	time_value TIMESTAMP(0) DEFAULT CURRENT_TIMESTAMP,
	blob_value TEXT
	);
CREATE TABLE account_map
	(
	id INTEGER PRIMARY KEY,
	id_account_map INT4 NOT NULL,
	number VARCHAR(8),
	full_number VARCHAR(32),
	name VARCHAR(128)
	);
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
	id_account_map INT4
	);
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

