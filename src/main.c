/*
---           booker 0.0.0 (c) 1978 by Marcin 'Amok' Konarski            ---

	prog.c - this file is integral part of `booker' project.

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

#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <libintl.h>

#include <stdhapi.h> /* all hAPI headers */
M_CVSID ( "$CVSHeader$" );

#include "booker.h"
#include "define.h"                                                    
#include "variables.h"
#include "cli_options.h"
#include "rc_options.h"

HBookerProcess theProc;

int main ( int a_iArgc, char **a_ppcArgv )
	{
	M_PROLOG
/*	variables declarations for main loop: */
	int l_iOpt = 0;
/*	end. */
	try 
		{
		signals::set_handlers ( );
/*	TO-DO:				                    enter main loop code here */
		g_pcProgramName = a_ppcArgv [ 0 ];
		process_bookerrc_file ( );
		l_iOpt = decode_switches ( a_iArgc, a_ppcArgv ); 
		test_globals ( );
		core::log.rehash ( g_pcLogFileName, 0 );
/* enabling ncurses ablilities  */
		if ( ! console::is_enabled ( ) )console::enter_curses ();
		theProc.init ( g_pcProgramName );
		theProc.run ( );
/* ending ncurses sesion        */
		if ( console::is_enabled ( ) )console::leave_curses ();
/*	... there is the place main loop ends.               :OD-OT */
		}
	catch ( HException * e ) 
		{
/* ending ncurses sesion        */
		if ( console::is_enabled ( ) )console::leave_curses ();
		}
	if ( g_pcLogFileName )
		xfree ( g_pcLogFileName );
	if ( g_pcPassword )
		xfree ( g_pcPassword );
	if ( g_pcLogin )
		xfree ( g_pcLogin );
	if ( g_pcDataBase )
		xfree ( g_pcDataBase );
	fprintf ( stderr, "%s.\n", _( "Done" ) ); 
	return ( 0 );
	M_FINAL
	}

