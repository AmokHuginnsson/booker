use booker

CREATE TABLE IF NOT EXISTS config
	(
	id INT(10) UNSIGNED PRIMARY KEY AUTO_INCREMENT,
	name VARCHAR(16) UNIQUE NOT NULL,
	integer_value INT(4),
	text_value VARCHAR(255),
	float_value FLOAT(8),
	time_value DATETIME,
	blob_value TEXT
	);
CREATE TABLE IF NOT EXISTS account_map
	(
	id INT(10) UNSIGNED PRIMARY KEY AUTO_INCREMENT,
	id_account_map INT(4) NOT NULL,
	number VARCHAR(8),
	full_number VARCHAR(32),
	name VARCHAR(128)
	);
CREATE TABLE IF NOT EXISTS dictionary_contracting_party
	(
	id INT(10) UNSIGNED PRIMARY KEY AUTO_INCREMENT,
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
	id_account_map INT(4)
	);
CREATE TABLE IF NOT EXISTS  dictionary_bank
	(
	id INT(10) UNSIGNED PRIMARY KEY AUTO_INCREMENT,
	name VARCHAR(128),
	country VARCHAR(32),
	city VARCHAR(32),
	street VARCHAR(128),
	street_number VARCHAR(8),
	postal_code VARCHAR(8),
	phone VARCHAR(32),
	fax VARCHAR(32)
	);

GRANT SELECT,INSERT,UPDATE,DELETE ON booker.* TO booker@localhost IDENTIFIED BY 'b00k3r';
