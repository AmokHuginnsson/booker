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
		log.rehash ( g_pcLogFileName, 0 );
/* enabling ncurses ablilities  */
//		if ( ! console::is_enabled ( ) )console::enter_curses ();
//		theProc.init ( g_pcProgramName );
//		theProc.run ( );
		HList < int > l_oList;
/*
		l_oList.add_element ( 3 );
		l_oList.add_element ( 2 );
		l_oList.add_element ( 4 );
		l_oList.add_element ( 1 );
		l_oList.add_element ( 7 );
		l_oList.add_element ( 5 );
		l_oList.add_element ( 6 );
		l_oList.go ( 3 );
		l_oList.add_element ( 9 );
*/
		l_oList.add_orderly ( 3 );
		l_oList.add_orderly ( 2 );
//		l_oList.add_orderly ( 4 );
//		l_oList.add_orderly ( 1 );
		for ( int i = 0; i < 2; i ++ )
			fprintf ( stderr, "%d\n", l_oList [ i ] );
/* ending ncurses sesion        */
		if ( console::is_enabled ( ) )console::leave_curses ();
/*	... there is the place main loop ends.               :OD-OT */
		}
	catch ( HException * e ) 
		{
/* ending ncurses sesion        */
		if ( console::is_enabled ( ) )console::leave_curses ();
		e->log ( __WHERE__ );
		e->print_error ( true );
		delete e; 
		}
	if ( g_pcLogFileName )
		xfree ( ( void * ) g_pcLogFileName );
	if ( g_pcPassword )
		xfree ( ( void * ) g_pcPassword );
	if ( g_pcLogin )
		xfree ( ( void * ) g_pcLogin );
	if ( g_pcDataBase )
		xfree ( ( void * ) g_pcDataBase );
	fprintf ( stderr, "Done.\n" ); 
	return ( 0 );
	}

/*
		int i, f = ( int ) D_TREAT_AS_OPENED;
		HList<int> lst;
		HRandomizer rnd;
		for ( i = 0; i < 8; i ++ )
			lst.add_tail ( ) = rnd.rnd ( ) % 11;
		
		if ( lst.quantity ( ) )
			{
			lst.go ( 0 );
			while ( f == ( int ) D_TREAT_AS_OPENED )
				fprintf ( stderr, "%4d", lst.to_tail ( 1, & f ) );
			fprintf ( stderr, "\n" );
			f = ( int ) D_TREAT_AS_OPENED;
			while ( f == ( int ) D_TREAT_AS_OPENED )
				fprintf ( stderr, "%4d", lst.to_head ( 1, & f ) );
			fprintf ( stderr, "\n---\n" );
			lst.sort_by_contents ( D_DESCENDING );
			
			i = 0;
			lst.go ( 0 );
			f = ( int ) D_TREAT_AS_OPENED;
			while ( ( f | ( int ) D_TREAT_AS_OPENED ) && ( i ++ < 10 ) )
				fprintf ( stderr, "%4d", lst.to_tail ( 1 ) );
			fprintf ( stderr, "\n" );
			i = 0;
			lst.go ( -1 );
			f = ( int ) D_TREAT_AS_OPENED;
			while ( ( f | ( int ) D_TREAT_AS_OPENED ) && ( i ++ < 10 ) )
				fprintf ( stderr, "%4d", lst.to_head ( 1 ) );
			fprintf ( stderr, "\n" );
			}	
			
		HList<int> * l_poList;
		l_poList = new HList<int>;
		l_poList->add_tail ( 1 );
		l_poList->add_tail ( 2 );
		l_poList->exchange ( -2, -1 );
		l_poList->go ( - 2 );
		l_poList->add_tail ( 3 );
		l_poList->exchange ( -2, -1 );
		l_poList->go ( - 2 );
		for ( l_iOpt = 0; l_iOpt < 9; l_iOpt ++ )
			fprintf ( stderr, "%d\n", l_poList->to_tail ( ) );
		delete l_poList;
		
		double l_dVal = 0;
		HString l_oString;
		HMap < HString, double > l_oMap ( 10 );
		l_oMap [ "Asia" ] = 13.7;
		l_oMap [ "Kasia" ] = 3.14159256;
		l_oMap [ "Honorata" ] = 1.42421;
		l_oMap [ "Natalia" ] = 2.735;
		if ( l_oMap.get ( "Klotylda", l_dVal ) )
			fprintf ( stderr, "Klotylda = %f\n", l_dVal );
		else
			fprintf ( stderr, "Klotylda was not found\n" );
		if ( l_oMap.get ( "Asia", l_dVal ) )
			fprintf ( stderr, "Asia = %f\n", l_dVal );
		else
			fprintf ( stderr, "Asia was not found\n" );
		fprintf ( stderr, "Natalia = %f\n", l_oMap [ "Natalia" ] );
		fprintf ( stderr, "Kasia = %f\n", l_oMap [ "Kasia" ] );
		fprintf ( stderr, "Honorata = %f\n", l_oMap [ "Honorata" ] );
		l_oMap.remove ( "Kasia" );
		l_oMap.rewind ( );
		while ( l_oMap.iterate ( l_oString, l_dVal ) )
			fprintf ( stderr, "%s = %f\n", ( char * ) l_oString, l_dVal );
			
		HDataBase l_oDB;
		HSerial l_oSerial ( "/dev/ttyS0" );
		l_oDB.login ( "booker", "booker", "b00k3r" );
		HRecordSet l_oRS ( & l_oDB );
		l_oRS.open ( "SELECT * FROM dictionary_contracting_party ORDER BY surname;" );
		while ( ! l_oRS.is_eof ( ) )
			{
			fprintf ( stderr, "%s\r\n", ( char * ) l_oRS.get ( 2 ) );
			l_oRS.move_next ( );
			}
		read_colector ( l_oSerial );
*/
