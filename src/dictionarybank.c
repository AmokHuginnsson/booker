/*
---           booker.h 0.0.0 (c) 1978 by Marcin 'Amok' Konarski            ---

	dictionarybankwindow.c - this file is integral part of booker.h project.

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

#include <stdhapi.h> /* all hAPI headers */
#include "dictionarybankwindow.h"

#include "booker.h"
#include "dictionarybankset.h"

HDictionatyBankWindow::HDictionatyBankWindow ( const char * a_pcTitle )
								: HWindow ( a_pcTitle )
	{
	M_PROLOG
  register_postprocess_handler ( 'a', 
			( int ( HWindow::* ) ( int ) ) & HDictionatyBankWindow::handler_add );
	return;
	M_EPILOG
	}

HDictionatyBankWindow::~HDictionatyBankWindow ( void )
	{
	M_PROLOG
	return;
	M_EPILOG
	}

int HDictionatyBankWindow::init ( void )
	{
	M_PROLOG
	int l_iError = 0;
	HControl * l_poControl = NULL;
	HListControl * l_poList = NULL;
	HDictionaryBankSet rs ( theProc.data_base ( ) );
	l_iError = HWindow::init ( );
	f_poList = l_poList = new HListControl ( this, 1, 1, - 8, - 1,
			" &Banki: \n" );
	l_poList->add_column ( -1, "nazwa", 3, D_ALIGN_LEFT, D_TYPE_HSTRING,
			l_poControl = new HEditControl ( this, - 7, 1, - 25, 160,
				" &Nazwa: \n", "", "^[a-zA-Z±¡æÆêÊ³£ñÑóÓ¶¦¼¬¿¯ \\.-]*$" ) );
	l_poControl->enable ( true );
	l_poList->add_column ( -1, "miasto", 1, D_ALIGN_LEFT, D_TYPE_HSTRING,
			l_poControl = new HEditControl ( this, - 7, - 24, 23, 32,
				" &Miasto: \n", "",	"^[a-zA-Z±¡æÆêÊ³£ñÑóÓ¶¦¼¬¿¯ ]*$" ) );
	l_poControl->enable ( true );
	l_poList->add_column ( -1, "ulica", 2, D_ALIGN_LEFT, D_TYPE_HSTRING,
			l_poControl = new HEditControl ( this, - 4, 1, - 33, 48, " &Ulica: \n",
				"", "^[0-9a-zA-Z±¡æÆêÊ³£ñÑóÓ¶¦¼¬¿¯ \\.-]*$" ) );
	l_poControl->enable ( true );
	l_poList->add_column ( -1, "", 0, D_ALIGN_LEFT, D_TYPE_HSTRING,
			new HEditControl ( this, - 4, - 32, 7, 8, " &Kod: \n", "",
				"^[0-9 -]*$" ) );
	l_poList->add_column ( -1, "", 0, D_ALIGN_LEFT, D_TYPE_HSTRING,
			new HEditControl ( this, - 4, - 24, 5, 6, " &Numer: \n", "",
				"^[0-9a-zA-Z]*$" ) );
	l_poList->add_column ( -1, "", 0, D_ALIGN_LEFT, D_TYPE_HSTRING,
			new HEditControl ( this, - 4, - 15, 14, 17, " &Telefon: \n", "",
				"^[0-9 ()-]*$" ) );
	rs.open ( );
	while ( ! rs.is_eof ( ) )
		{
		l_poList->add_tail ( );
		l_poList->tail ( ) [ 0 ] = rs.m_nazwa;
		l_poList->tail ( ) [ 1 ] = rs.m_miasto;
		l_poList->tail ( ) [ 2 ] = rs.m_ulica;
		l_poList->tail ( ) [ 3 ] = rs.m_kod_pocztowy;
		l_poList->tail ( ) [ 4 ] = rs.m_numer_ulicy;
		l_poList->tail ( ) [ 5 ] = rs.m_telefon;
		rs.move_next ( );
		}
	rs.close ( );
	l_poList->enable ( true );
	l_poList->set_focus ( );
	refresh ( );
	return ( l_iError );
	M_EPILOG
	}

int HDictionatyBankWindow::handler_add ( int a_iCode )
	{
	M_PROLOG
	int l_iCtr = 0;
	double l_dValue = 0;
	HAnalyser l_oAnalyser;
	HInfoList * l_poInfoList = NULL;
	l_oAnalyser.analyse ( "A+B" );
	for ( l_iCtr = 0; l_iCtr < 10000; l_iCtr ++ )
		{
		l_dValue = f_poList->quantity ( ) / 100.;
/*		
		l_oAnalyser [ 'A' ] = l_dValue;
		l_oAnalyser [ 'B' ] = l_dValue * l_dValue;
		l_dValue = l_oAnalyser.count ( );
*/
		l_poInfoList = & f_poList->add_tail ( );
		( * l_poInfoList ) [ 0 ] = util::kwota_slownie ( l_dValue );
		( * l_poInfoList ) [ 1 ] = "wype³niacz";
		( * l_poInfoList ) [ 2 ] = HString ( l_dValue );
		}
/*
 * tested list control by filling it with 276300 rows
 */
	refresh ( );
	a_iCode = 0;
	return ( a_iCode );
	M_EPILOG
	}
