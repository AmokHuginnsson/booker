/*
---           booker.h 0.0.0 (c) 1978 by Marcin 'Amok' Konarski            ---

	dictionarycontractingpartyset.h - this file is integral part of booker.h project.

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

#ifndef __DICTIONARYCONTRACTINGPARTYSET_H
#define __DICTIONARYCONTRACTINGPARTYSET_H

class HDictionaryContractingPartySet : public yaal::dbwrapper::HRecordSet
	{
public:
	/*{*/
	yaal::hcore::HString m_imie;
	yaal::hcore::HString m_nazwisko;
	yaal::hcore::HString m_nip;
	yaal::hcore::HString m_kraj;
	yaal::hcore::HString m_miasto;
	yaal::hcore::HString m_ulica;
	yaal::hcore::HString m_numer_ulicy;
	yaal::hcore::HString m_numer_mieszkania;
	yaal::hcore::HString m_kod_pocztowy;
	yaal::hcore::HString m_telefon;
	yaal::hcore::HString m_fax;
	yaal::hcore::HString m_email;
	long int m_id_account_map;
	/*}*/
protected:
	/*{*/
	/*}*/
public:
	/*{*/
	HDictionaryContractingPartySet ( yaal::dbwrapper::HDataBase * = NULL );
	virtual ~HDictionaryContractingPartySet ( void );
	/*}*/
protected:
	/*{*/
	void sync ( void );
	/*}*/
	};

#endif /* __DICTIONARYCONTRACTINGPARTYSET_H */
