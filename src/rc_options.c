/*
---       `booker' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski         ---

	rc_options.c - this file is integral part of `booker' project.

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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <stdhapi.h>
M_CVSID ( "$CVSHeader$" );

#include "setup.h"

using namespace stdhapi::hcore;

bool set_variables ( HString & a_roOption, HString & a_roValue )
	{
	printf ( "option: [%s], value: [%s]\n", ( char * ) a_roOption,
			( char * ) a_roValue );
	return ( false );
	}

int process_bookerrc_file ( void )
	{
	OVariable l_psVars [ ] =
		{
			{ D_HSTRING, "log_path",	& setup.f_oLogPath },
			{ D_HSTRING, "database",	& setup.f_oDataBase },
			{ D_HSTRING, "login",			& setup.f_oLogin },
			{ D_HSTRING, "password",	& setup.f_oPassword },
			{ D_NONE, NULL, NULL }
		};
	rc_file::process_rc_file ( "booker", NULL, l_psVars, NULL );
	if ( ! setup.f_oLogPath )
		setup.f_oLogPath = "booker.log";
	return ( 0 );
	}

