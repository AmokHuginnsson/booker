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

#include "testset.hxx"

using namespace yaal::hcore;
using namespace yaal::dbwrapper;

namespace booker {

HTestSet::HTestSet( HDataBase::ptr_t dataBase_ )
	: _sQLDescriptor( dataBase_ ),
	 _id( -1 ), _idName( -1 ), _vText(), _vInt(), _vReal(), _vDate( HTime::LOCAL, _iso8601DateFormat_ ),
	_vTime( HTime::LOCAL, _iso8601TimeFormat_ ), _vDatetime( HTime::LOCAL, _iso8601DateTimeFormat_ ) {
	M_PROLOG
	_sQLDescriptor.set_table( "test" );
	return;
	M_EPILOG
}

HTestSet::~HTestSet ( void ) {
	M_PROLOG
	return;
	M_EPILOG
}

void HTestSet::sync( void ) {
	M_PROLOG
	_sQLDescriptor.sync( 1, _idName );
	_sQLDescriptor.sync( 2, _vText );
	_sQLDescriptor.sync( 3, _vInt );
	_sQLDescriptor.sync( 4, _vReal );
	_sQLDescriptor.sync( 5, _vDate );
	_sQLDescriptor.sync( 6, _vTime );
	_sQLDescriptor.sync( 7, _vDatetime );
	_sQLDescriptor.sync( 0, _id );
	return;
	M_EPILOG
}

HRecordSet::ptr_t HTestSet::get_records( void ) {
	return ( _sQLDescriptor.execute( HCRUDDescriptor::MODE::SELECT ) );
}

void HTestSet::sync( yaal::dbwrapper::HRecordSet::iterator it ) {
	_sQLDescriptor.sync( it );
	sync();
}

}

