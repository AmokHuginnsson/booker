/*
---           booker.h 0.0.0 (c) 1978 by Marcin 'Amok' Konarski            ---

	dictionarycontractingpartyset.hxx - this file is integral part of booker.h project.

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

#ifndef DICTIONARYCONTRACTINGPARTYSET_HXX_INCLUDED
#define DICTIONARYCONTRACTINGPARTYSET_HXX_INCLUDED

namespace booker {

class HDictionaryContractingPartySet {
	yaal::dbwrapper::HSQLDescriptor _sQLDescriptor;
public:
	/*{*/
	yaal::hcore::HString _imie;
	yaal::hcore::HString _nazwisko;
	yaal::hcore::HString _nip;
	yaal::hcore::HString _kraj;
	yaal::hcore::HString _miasto;
	yaal::hcore::HString _ulica;
	yaal::hcore::HString _numer_ulicy;
	yaal::hcore::HString _numer_mieszkania;
	yaal::hcore::HString _kod_pocztowy;
	yaal::hcore::HString _telefon;
	yaal::hcore::HString _fax;
	yaal::hcore::HString _email;
	long int _id_account_map;
	/*}*/
protected:
	/*{*/
	/*}*/
public:
	/*{*/
	HDictionaryContractingPartySet( yaal::dbwrapper::HDataBase::ptr_t = yaal::dbwrapper::HDataBase::ptr_t() );
	virtual ~HDictionaryContractingPartySet ( void );
	void sync( void );
	void sync( yaal::dbwrapper::HRecordSet::iterator );
	yaal::dbwrapper::HRecordSet::ptr_t get_records( void );
	/*}*/
protected:
	/*{*/
	/*}*/
};

}

#endif /* DICTIONARYCONTRACTINGPARTYSET_HXX_INCLUDED */
