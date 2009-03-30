/*
---       `booker' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski         ---

	setup.hxx - this file is integral part of `booker' project.

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

#ifndef SETUP_HXX_INCLUDED
#define SETUP_HXX_INCLUDED

#include <libintl.h>

namespace booker
{

struct OSetup
	{
	bool f_bQuiet;			/* --quiet, --silent */
	bool f_bVerbose;		/* --verbose */
	char * f_pcProgramName;
	yaal::hcore::HString f_oLogPath;
	yaal::hcore::HString f_oDataBase;
	yaal::hcore::HString f_oLogin;
	yaal::hcore::HString f_oPassword;
	/* self-sufficient */
	OSetup( void )
		: f_bQuiet( false ), f_bVerbose( false ),
		f_pcProgramName( NULL ),
		f_oLogPath(), f_oDataBase(),
		f_oLogin(), f_oPassword() {}
	void test_setup( void )
		{
		M_PROLOG
		if ( ! f_oDataBase )
			M_THROW( _( "database not set" ), errno );
		if ( ! f_oLogin )
			M_THROW( _( "database login not set" ), errno );
		if ( ! f_oPassword )
			M_THROW( _( "database password not set" ), errno );
		if ( ! f_oLogPath )
			M_THROW( _( "log file name not set" ), errno );
		return;
		M_EPILOG
		}
private:
	OSetup ( OSetup const& );
	OSetup& operator = ( OSetup const& );
	};

extern OSetup setup;

}

#endif /* SETUP_HXX_INCLUDED */
