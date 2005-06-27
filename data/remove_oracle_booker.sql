DROP TRIGGER root.account_map_idinc;
DROP SEQUENCE root.account_map_seq;
DROP TABLE root.account_map;

DROP TRIGGER root.dict_contracting_party_idinc;
DROP SEQUENCE root.dict_contracting_party_seq;
DROP TABLE root.dictionary_contracting_party;

DROP TRIGGER root.dictionary_bank_idinc
DROP SEQUENCE root.dictionary_bank_seq;
DROP TABLE root.dictionary_bank;

DROP TRIGGER root.config_idinc;
DROP SEQUENCE root.config_seq;
DROP TABLE root.config;

DROP USER booker CASCADE;
DROP USER root CASCADE;
DROP ROLE dml_role;
DROP ROLE ddl_role;
