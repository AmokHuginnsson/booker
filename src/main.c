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

void read_colector ( HSerial & );
bool test_char ( const char *, int );
int send ( HSerial &, char *, int );
int receive ( HSerial &, char * const );
int establish_connection ( HSerial & );
int wait_for_connection ( HSerial & );

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
		if ( ! console::is_enabled ( ) )console::enter_curses ();
//		theProc.init ( g_pcProgramName );
//		theProc.run ( );
		HSerial l_oSerial;
		read_colector ( l_oSerial );
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

void read_colector ( HSerial & a_oPort ) 
	{
	int l_iErr = 0;
	int l_iRet = 0;
	long l_lCount = 0;
	char l_pcBuffer [ 64 ];
	HString l_oErr;
	if ( ! a_oPort.open ( )	&& ( wait_for_connection ( a_oPort ) >= 0 ) )
		{
		memset ( l_pcBuffer, 0, 64 );
		while ( strncmp ( l_pcBuffer, "QNTT", 4 ) && ( l_iRet >= 0 ) )
			l_iRet = receive ( a_oPort, l_pcBuffer );
		l_lCount = atol ( l_pcBuffer + 4 );
		if ( l_iRet < 0 )l_lCount = 0;
		while ( l_lCount )
			{
			memset ( l_pcBuffer, 0, 64 );
			l_iErr += receive ( a_oPort, l_pcBuffer );
			if ( l_iRet < 0 )
				{
				l_iErr -= l_iRet;
				break;
				}
			if ( ! ( strncmp ( l_pcBuffer, "END\r\n", 5 ) && strncmp ( l_pcBuffer, "BRK\r\n", 5 ) ) )break;
//			l_oErr.format ( "Postêp wczytywania zamówienia z kolektora ...  (%d)", l_iErr );
//			console::c_printf ( 0, 0, 7, l_oErr );
			fprintf ( stderr, "%s", l_pcBuffer );
			l_pcBuffer [ 5 ] = 0;
			}
		}
	return;
	}

bool test_char ( const char * a_pcBuffer, int a_iIndex )
	{
	return ( a_pcBuffer [ a_iIndex ]
							&& ( ( ( a_pcBuffer [ a_iIndex ] >= '0' )
									&& ( a_pcBuffer [ a_iIndex ] <= '9' ) )
								|| ( ( a_pcBuffer [ a_iIndex ] >= 'A' )
									&& ( a_pcBuffer [ a_iIndex ] <= 'Z' ) )
								|| ( ( ( a_pcBuffer [ a_iIndex ] == 10 )
										|| ( a_pcBuffer [ a_iIndex ] == 13 )
										|| ( a_pcBuffer [ a_iIndex ] == '?' ) )
									&& a_iIndex ) ) );
	}

int send ( HSerial & a_oPort, char * a_pcBuffer, int a_iLength )
	{
	int l_iCnt = 0;
	char l_cCRC = 0;
	char l_pcReadBuf [ 32 ];
	for ( l_iCnt = 0; l_iCnt < a_iLength; l_iCnt++ )
		l_cCRC += a_pcBuffer [ l_iCnt ];
	for ( l_iCnt = 0; l_iCnt < 32; l_iCnt++ )l_pcReadBuf [ l_iCnt ] = 0;
	l_iCnt = 0;
	while ( 1 )
		{
		a_oPort.write ( a_pcBuffer, a_iLength );
		a_oPort.read ( l_pcReadBuf, 1 );
		if ( l_pcReadBuf [ 0 ] == l_cCRC )break;
		l_iCnt ++;
		}
	a_oPort.write ( "OK\r\n", 4 );
	return ( l_iCnt );
	}

int receive ( HSerial & a_oPort, char * const a_pcBuffer )
	{
	int l_iErr = 0;
	int l_iLen = 0;
	int l_iCnt = 0;
	char l_cCRC = 0;
	char l_pcReadBuf [ 64 ];
	char l_pcBuffer [ 64 ];
	do
		{
		memset ( l_pcReadBuf, 0, 64 );
		memset ( l_pcBuffer, 0, 64 );
		l_iCnt = 0;
		l_iLen = 0;
		while ( l_iCnt < 64 )
			{
			if( a_oPort.read ( l_pcReadBuf + l_iCnt, 1 ) )
				if ( test_char ( l_pcReadBuf, l_iCnt ) )l_iCnt ++;
			if ( l_iCnt && ( l_pcReadBuf [ l_iCnt - 1 ] == '\n' ) )break;
			if ( console::kbhit ( ) == 'q' )return ( -1 );
			}
		do
			{
			l_iLen = l_iCnt;
			l_cCRC = 0;
			for ( l_iCnt = 0; l_iCnt < 64; l_iCnt++ )l_cCRC += l_pcReadBuf [ l_iCnt ];
			l_pcBuffer [ 0 ] = l_cCRC;
			a_oPort.write ( l_pcBuffer, 1 );
			l_iCnt = 0;
			l_iLen = 0;
			memset ( l_pcBuffer, 0, 64 );
			while ( l_iCnt < 64 )
				{
				if( a_oPort.read ( l_pcBuffer + l_iCnt, 1 ) )
					if ( test_char ( l_pcReadBuf, l_iCnt ) )l_iCnt ++;
				if ( l_iCnt && ( l_pcBuffer [ l_iCnt - 1 ] == '\n' ) )break;
				if ( console::kbhit ( ) == 'q' )return ( -1 );
				}
			if ( strncmp ( l_pcBuffer, "OK\r\n", 4 ) )
				{
				memset ( l_pcReadBuf, 0, 64 );
				strncpy ( l_pcReadBuf, l_pcBuffer, 64 );
				l_iErr ++;
				}
			}
		while ( strncmp ( l_pcBuffer, "OK\r\n", 4 ) );
		}
	while ( strncmp ( l_pcBuffer, "OK\r\n", 4 ) );
	l_iLen = strlen ( l_pcReadBuf );
	strncpy ( a_pcBuffer, l_pcReadBuf, l_iLen );
	return ( l_iErr );
	}

int establish_connection ( HSerial & a_oPort )
	{
	int l_iErr = 0;
	int l_iCnt = 0;
	char l_pcReadBuf [ 8 ];
	unsigned long l_ulTimeOut = 0;
	memset ( l_pcReadBuf, 0, 8 );
	while ( 1 )
		{
		strncpy ( l_pcReadBuf, "KO?\r\n", 5 );
		for ( l_iCnt = 0; l_iCnt < 5; l_iCnt ++ )
			a_oPort.write ( l_pcReadBuf + l_iCnt, 1 );
		memset ( l_pcReadBuf, 0, 8 );
		l_ulTimeOut = time ( 0 );
		l_iCnt = 0;
		while ( l_iCnt < 64 )
			{
			if ( a_oPort.read ( l_pcReadBuf + l_iCnt, 1 ) )
				if ( test_char ( l_pcReadBuf, l_iCnt ) )l_iCnt ++;
			if ( l_iCnt && ( l_pcReadBuf [ l_iCnt - 1 ] == '\n' ) )break;
			if ( console::kbhit ( ) == 'q' )return ( -1 );
			}
		if ( ! strncmp ( l_pcReadBuf, "OK\r\n", 4 ) )break;
		l_iErr ++;
		}
	return ( l_iErr );
	}

int wait_for_connection ( HSerial & a_oPort )
	{
	int l_iErr = 0;
	int l_iCnt = 0;
	char l_pcReadBuf [ 8 ];
	unsigned long l_ulTimeOut = 0;
	memset ( l_pcReadBuf, 0, 8 );
	while ( 1 )
		{
		l_ulTimeOut = time ( 0 );
		l_iCnt = 0;
		while ( l_iCnt < 64 )
			{
			if ( a_oPort.read ( l_pcReadBuf + l_iCnt, 1 ) )
				if ( test_char ( l_pcReadBuf, l_iCnt ) )l_iCnt ++;
			if ( l_iCnt && ( l_pcReadBuf [ l_iCnt - 1 ] == '\n' ) )break;
			if ( console::kbhit ( ) == 'q' )return ( -1 );
			}
		if ( ! strncmp ( l_pcReadBuf, "KO?\r\n", 5 ) )
			{
			strncpy ( l_pcReadBuf, "OK\r\n", 4 );
			for ( l_iCnt = 0; l_iCnt < 4; l_iCnt ++ )
				a_oPort.write ( l_pcReadBuf + l_iCnt, 1 );
			break;
			}
		l_iErr ++;
		}
	fprintf ( stderr, "Connected !\r\n" );
	return ( 0 );
	}

