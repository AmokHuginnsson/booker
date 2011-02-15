/*
---           `booker' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski            ---

	setup.cxx - this file is integral part of `booker' project.

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

#include <cstdio>

#include <yaal/yaal.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "setup.hxx"

using namespace yaal::hcore;

namespace booker
{

void OSetup::test_setup( void )
	{
	M_PROLOG
	if ( _quiet && _verbose )
		yaal::tools::util::failure( 1,
				_( "quiet and verbose options are exclusive\n" ) );
	if ( _verbose )
		clog.reset( HStreamInterface::ptr_t( new HFile( stdout ) ) );
	if ( _quiet )
		cout.reset();
	if ( ! _dataBase )
		M_THROW( _( "database not set" ), errno );
	if ( ! _login )
		M_THROW( _( "database login not set" ), errno );
	if ( ! _password )
		M_THROW( _( "database password not set" ), errno );
	if ( ! _logPath )
		M_THROW( _( "log file name not set" ), errno );
	return;
	M_EPILOG
	}

}

