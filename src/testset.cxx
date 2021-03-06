/* Read booker/LICENSE.md file for copyright and licensing information. */

#include "testset.hxx"
M_VCSID( "$Id: " __ID__ " $" )

using namespace yaal::hcore;
using namespace yaal::dbwrapper;

namespace booker {

HTestSet::HTestSet( HDataBase::ptr_t dataBase_ )
	: _sQLDescriptor( dataBase_ ),
	 _id( -1 ), _idName( -1 ), _vText(), _vInt(), _vReal(), _vDate( HTime::TZ::LOCAL, _iso8601DateFormat_ ),
	_vTime( HTime::TZ::LOCAL, _iso8601TimeFormat_ ), _vDatetime( HTime::TZ::LOCAL, _iso8601DateTimeFormat_ ) {
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
	return ( _sQLDescriptor.execute( HCRUDDescriptor::MODE::READ ) );
}

void HTestSet::sync( yaal::dbwrapper::HRecordSet::iterator it ) {
	for ( int i( 0 ), c( static_cast<int>( (*it).get_size() ) ); i < c; ++ i ) {
		_sQLDescriptor[i] = it[i];
	}
	sync();
}

}

