/*
---           booker 0.0.0 (c) 1978 by Marcin 'Amok' Konarski            ---

	main.cxx - this file is integral part of `booker' project.

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

#include <cstdlib>
#include <libintl.h>

#include <yaal/yaal.hxx> /* all hAPI headers */
M_VCSID( "$Id: "__ID__" $" )

#include "booker.hxx"
#include "setup.hxx"
#include "options.hxx"

using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace booker;

namespace booker
{

OSetup setup;
HBookerProcess theProc;

}

int main( int a_iArgc, char **a_ppcArgv )
	{
	M_PROLOG
/*	variables declarations for main loop: */
	int l_iOpt = 0;
/*	end. */
	try 
		{
		HSignalServiceFactory::get_instance();
/*	TO-DO:				                    enter main loop code here */
		setup.f_pcProgramName = a_ppcArgv [ 0 ];
		l_iOpt = handle_program_options( a_iArgc, a_ppcArgv );
		hcore::log( call( static_cast<void ( HLog::* )( HString const&, char const* const )>( &HLog::rehash ), _1, setup.f_oLogPath, setup.f_pcProgramName ) );
		setup.test_setup();
/* enabling ncurses ablilities  */
		if ( ! HCons::get_instance().is_enabled() )
			HCons::get_instance().enter_curses();
		theProc.init( setup.f_pcProgramName );
		theProc.run();
/* ending ncurses sesion        */
		if ( HCons::get_instance().is_enabled() )
			HCons::get_instance().leave_curses();
/*	... there is the place main loop ends.               :OD-OT */
		}
	catch ( ... ) 
		{
/* ending ncurses sesion        */
		if ( HCons::get_instance().is_enabled() )
			HCons::get_instance().leave_curses();
		throw;
		}
	fprintf( stderr, "%s.\n", _( "Done" ) ); 
	return ( 0 );
	M_FINAL
	}

