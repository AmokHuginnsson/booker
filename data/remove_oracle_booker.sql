DROP TRIGGER root.account_map_autonumber;
DROP SEQUENCE root.account_map_sequence;
DROP TABLE root.account_map;

DROP TRIGGER root.dictionary_contracting_party_autonumber;
DROP SEQUENCE root.dictionary_contracting_party_sequence;
DROP TABLE root.dictionary_contracting_party;

DROP TRIGGER root.dictionary_bank_autonumber
DROP SEQUENCE root.dictionary_bank_sequence;
DROP TABLE root.dictionary_bank;

DROP TRIGGER root.config_autonumber;
DROP SEQUENCE root.config_sequence;
DROP TABLE root.config;

DROP USER booker;
DROP USER root;
DROP ROLE dml_role;
DROP ROLE ddl_role;
