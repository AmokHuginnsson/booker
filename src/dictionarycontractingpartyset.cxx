/*
---           booker 0.0.0 (c) 1978 by Marcin 'Amok' Konarski            ---

	dictionarycontractingpartyset.cxx - this file is integral part of booker project.

  i.  You may not make any changes in Copyright information.
  ii. You must attach Copyright information to any part of every copy
      of this software.

Copyright:

 You can use this software free of charge and you can redistribute its binary
 package freely but:
  1. You are not allowed to use any part of sources of this software.
  2. You are not allowed to redistribute any part of sources of this software.
  3. You are not allowed to reverse engineer this software.
  4. If you want to distribute a binary package of this software you cannot
     demand any fees for it. You cannot even demand
     a return of cost of the media or distribution (CD for example).
  5. You cannot involve this software in any commercial activity (for example
     as a free add-on to paid software or newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

#include <yaal/yaal.hxx>
M_VCSID( "$Id: " __ID__ " $" )

#include "dictionarycontractingpartyset.hxx"

using namespace yaal::hcore;
using namespace yaal::dbwrapper;

namespace booker {

HDictionaryContractingPartySet::HDictionaryContractingPartySet( HDataBase::ptr_t dataBase_ )
	: _sQLDescriptor( dataBase_ ),
	_imie(), _nazwisko(), _nip(), _kraj(), _miasto(),
	_ulica(), _numer_ulicy(), _numer_mieszkania(), _kod_pocztowy(),
	_telefon(), _fax(), _email( ), _id_account_map( 0 ) {
	M_PROLOG
	_sQLDescriptor.set_table( "dictionary_contracting_party" );
	return;
	M_EPILOG
}

HDictionaryContractingPartySet::~HDictionaryContractingPartySet ( void ) {
	M_PROLOG
	return;
	M_EPILOG
}

void HDictionaryContractingPartySet::sync( void ) {
	M_PROLOG
	_sQLDescriptor.sync( 1, _imie );
	_sQLDescriptor.sync( 2, _nazwisko );
	_sQLDescriptor.sync( 3, _nip );
	_sQLDescriptor.sync( 4, _kraj );
	_sQLDescriptor.sync( 5, _miasto );
	_sQLDescriptor.sync( 6, _ulica );
	_sQLDescriptor.sync( 7, _numer_ulicy );
	_sQLDescriptor.sync( 8, _numer_mieszkania );
	_sQLDescriptor.sync( 9, _kod_pocztowy );
	_sQLDescriptor.sync( 10, _telefon );
	_sQLDescriptor.sync( 11, _fax );
	_sQLDescriptor.sync( 12, _email );
	_sQLDescriptor.sync( 13, _id_account_map );
	return;
	M_EPILOG
}

HRecordSet::ptr_t HDictionaryContractingPartySet::get_records( void ) {
	return ( _sQLDescriptor.execute( HSQLDescriptor::MODE::SELECT ) );
}

void HDictionaryContractingPartySet::sync( yaal::dbwrapper::HRecordSet::iterator it ) {
	_sQLDescriptor.sync( it );
	sync();
}

}

