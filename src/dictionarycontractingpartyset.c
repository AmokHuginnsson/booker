/*
---           booker.h 0.0.0 (c) 1978 by Marcin 'Amok' Konarski            ---

	dictionarycontractingpartyset.cxx - this file is integral part of booker.h project.

	i.  You may not make any changes in Copyright information.
	ii. You must attach Copyright information to any part of every copy
	    of this software.

Copyright:

 You are free to use this program as is, you can redistribute binary
 package freely but:
  1. You can not use any part of sources of this software.
  2. You can not redistribute any part of sources of this software.
  3. No reverse engineering is allowed.
  4. If you want redistribute binary package you can not demand any fees
     for this software.
     You can not even demand cost of the carrier (CD for example).
  5. You can not include it to any commercial enterprise (for example 
     as a free add-on to payed software or payed newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

#include <yaal.h>
M_VCSID ( "$Id$" )

#include "dictionarycontractingpartyset.h"

using namespace yaal::hcore;
using namespace yaal::dbwrapper;

HDictionaryContractingPartySet::HDictionaryContractingPartySet ( HDataBase * a_poDataBase ) : HRecordSet ( a_poDataBase ),
	m_imie ( ), m_nazwisko ( ), m_nip ( ), m_kraj ( ), m_miasto ( ),
	m_ulica ( ), m_numer_ulicy ( ), m_numer_mieszkania ( ), m_kod_pocztowy ( ),
	m_telefon ( ), m_fax ( ), m_email ( ), m_id_account_map ( 0 )
	{
	M_PROLOG
	f_oTable = "dictionary_contracting_party";
	return;
	M_EPILOG
	}

HDictionaryContractingPartySet::~HDictionaryContractingPartySet ( void )
	{
	M_PROLOG
	return;
	M_EPILOG
	}

void HDictionaryContractingPartySet::sync ( void )
	{
	M_PROLOG
	HRecordSet::sync ( );
	HRecordSet::sync ( 1, m_imie );
	HRecordSet::sync ( 2, m_nazwisko );
	HRecordSet::sync ( 3, m_nip );
	HRecordSet::sync ( 4, m_kraj );
	HRecordSet::sync ( 5, m_miasto );
	HRecordSet::sync ( 6, m_ulica );
	HRecordSet::sync ( 7, m_numer_ulicy );
	HRecordSet::sync ( 8, m_numer_mieszkania );
	HRecordSet::sync ( 9, m_kod_pocztowy );
	HRecordSet::sync ( 10, m_telefon );
	HRecordSet::sync ( 11, m_fax );
	HRecordSet::sync ( 12, m_email );
	HRecordSet::sync ( 13, m_id_account_map );
	return;
	M_EPILOG
	}

