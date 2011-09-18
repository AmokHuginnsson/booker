/*
---           booker 0.0.0 (c) 1978 by Marcin 'Amok' Konarski            ---

	dictionarycontractingpartyset.cxx - this file is integral part of booker project.

	i.  You may not make any changes in Copyright information.
	ii. You must attach Copyright information to any part of every copy
	    of this software.

Copyright:

 You are free to use this program as is, you can redistribute binary
 package freely but:
  1. You cannot use any part of sources of this software.
  2. You cannot redistribute any part of sources of this software.
  3. No reverse engineering is allowed.
  4. If you want redistribute binary package you cannot demand any fees
     for this software.
     You cannot even demand cost of the carrier (CD for example).
  5. You cannot include it to any commercial enterprise (for example 
     as a free add-on to payed software or payed newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

#include <yaal/yaal.hxx>
M_VCSID( "$Id: "__ID__" $" )

#include "dictionarycontractingpartyset.hxx"

using namespace yaal::hcore;
using namespace yaal::dbwrapper;

namespace booker {

HDictionaryContractingPartySet::HDictionaryContractingPartySet( HDataBase::ptr_t dataBase_ )
	: _sQLDescriptor( dataBase_ ),
	m_imie ( ), m_nazwisko ( ), m_nip ( ), m_kraj ( ), m_miasto ( ),
	m_ulica ( ), m_numer_ulicy ( ), m_numer_mieszkania ( ), m_kod_pocztowy ( ),
	m_telefon ( ), m_fax ( ), m_email ( ), m_id_account_map ( 0 ) {
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
	_sQLDescriptor.sync( 1, m_imie );
	_sQLDescriptor.sync( 2, m_nazwisko );
	_sQLDescriptor.sync( 3, m_nip );
	_sQLDescriptor.sync( 4, m_kraj );
	_sQLDescriptor.sync( 5, m_miasto );
	_sQLDescriptor.sync( 6, m_ulica );
	_sQLDescriptor.sync( 7, m_numer_ulicy );
	_sQLDescriptor.sync( 8, m_numer_mieszkania );
	_sQLDescriptor.sync( 9, m_kod_pocztowy );
	_sQLDescriptor.sync( 10, m_telefon );
	_sQLDescriptor.sync( 11, m_fax );
	_sQLDescriptor.sync( 12, m_email );
	_sQLDescriptor.sync( 13, m_id_account_map );
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

