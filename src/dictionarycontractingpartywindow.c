/*
---           booker.h 0.0.0 (c) 1978 by Marcin 'Amok' Konarski            ---

	dictionarybank.c - this file is integral part of booker.h project.

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
#include "dictionarycontractingpartywindow.h"

#include "booker.h"
#include "dictionarycontractingpartyset.h"

HDictionaryContractingPartyWindow::HDictionaryContractingPartyWindow ( const char * a_pcTitle )
								: HWindow ( a_pcTitle )
	{
	M_PROLOG
	return;
	M_EPILOG
	}

HDictionaryContractingPartyWindow::~HDictionaryContractingPartyWindow ( void )
	{
	M_PROLOG
	return;
	M_EPILOG
	}

int HDictionaryContractingPartyWindow::init ( void )
	{
	M_PROLOG
	int l_iError = 0;
	HControl * l_poControl = NULL;
	HListControl * l_poList = NULL;
	HDictionaryContractingPartySet rs ( theProc.data_base ( ) );
	l_iError = HWindow::init ( );
	l_poList = new HListControl ( this, 1, 1, - 8, - 1, " &Kontrahenci: \n" );
	l_poList->add_column ( -1, "Imiê", 16, D_ALIGN_LEFT, D_TYPE_HSTRING,
			l_poControl = new HEditControl ( this,
				- 7, 1, 18, 32, " &Imiê: \n", "",
				"^[a-zA-Z0-9±¡æÆêÊ³£ñÑóÓ¶¦¼¬¿¯ \\._@-]*$" ) );
	l_poControl->enable ( true );
	l_poList->add_column ( -1, "Nazwisko", 24, D_ALIGN_LEFT, D_TYPE_HSTRING,
			l_poControl = new HEditControl ( this, - 7, 20, 28, 32, " &Nazwisko: \n",
				"", "^[a-zA-Z±¡æÆêÊ³£ñÑóÓ¶¦¼¬¿¯ -]*$" ) );
	l_poControl->enable ( true );
	l_poList->add_column ( -1, "Ulica", 24, D_ALIGN_LEFT, D_TYPE_HSTRING,
			l_poControl = new HEditControl ( this, - 7, 49, 29, 32, " &Ulica: \n",
				"", "^[a-zA-Z±¡æÆêÊ³£ñÑóÓ¶¦¼¬¿¯ -]*$" ) );
	l_poControl->enable ( true );
	l_poList->add_column ( -1, "", 0, D_ALIGN_LEFT, D_TYPE_HSTRING,
			new HEditControl ( this, - 4, 1, 32, 32, " &Miasto: \n", "",
				"^[a-zA-Z±¡æÆêÊ³£ñÑóÓ¶¦¼¬¿¯ \\.-]*$" ) );
	l_poList->add_column ( -1, "", 0, D_ALIGN_LEFT, D_TYPE_HSTRING,
			new HEditControl ( this, - 4, 49, 29, 48, " &E-mail: \n", "",
				"^[a-zA-Z0-9\\._@-]*$" ) );
	rs.open ( );
	while ( ! rs.is_eof ( ) )
		{
		l_poList->add_tail ( );
		l_poList->tail ( ) [ 0 ] = rs.m_imie;
		l_poList->tail ( ) [ 1 ] = rs.m_nazwisko;
		l_poList->tail ( ) [ 2 ] = rs.m_ulica;
		l_poList->tail ( ) [ 3 ] = rs.m_miasto;
//		l_poList->tail ( ) [ 4 ] = l_sMySqlRow [ 5 ];
		rs.move_next ( );
		}
	rs.close ( );
	l_poList->enable ( true );
	l_poList->set_focus ( );
	refresh ( );
	return ( l_iError );
	M_EPILOG
	}

