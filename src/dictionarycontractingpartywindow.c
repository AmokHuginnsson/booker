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
M_CVSID ( "$CVSHeader$" );

#ifdef HAVE_NCURSES_H
#	include <ncurses.h>
#elif defined ( HAVE_NCURSES_NCURSES_H )
#	include <ncurses/ncurses.h>
#else /* HAVE_NCURSES_NCURSES_H */
#	error "No ncurses header available."
#endif /* not HAVE_NCURSES_NCURSES_H */

#include "booker.h"
#include "dictionarycontractingpartywindow.h"
#include "dictionarycontractingpartyset.h"

using namespace stdhapi::hcore;
using namespace stdhapi::hconsole;

HDictionaryContractingPartyWindow::HDictionaryContractingPartyWindow ( const char * a_pcTitle )
	: HWindow ( a_pcTitle ), f_poList ( NULL ), f_poEdit ( NULL )
	{
	M_PROLOG
	M_REGISTER_POSTPROCESS_HANDLER ( KEY_DELETE, NULL,
			HDictionaryContractingPartyWindow::handler_delete );
	M_REGISTER_POSTPROCESS_HANDLER ( '\r', NULL,
			HDictionaryContractingPartyWindow::handler_enter );
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
	HItem l_oItem ( 1 ), l_oRow ( 5 );
	HListControl * l_poList = NULL;
	HComboboxControl * l_poCombo = NULL;
	HDictionaryContractingPartySet rs ( theProc.data_base ( ) );
	l_iError = HWindow::init ( );
	f_poList = l_poList = new HListControl ( this, 1, 1, - 11, - 1,
			" &Kontrahenci: \n" );
	l_poList->add_column ( -1, "Imiê", 16, D_ALIGN_LEFT, D_HSTRING,
			l_poControl = new HEditControl ( this,
				- 7, 1, 1, 18, " &Imiê: \n", 32, "",
				"^[a-zA-Z0-9±¡æÆêÊ³£ñÑóÓ¶¦¼¬¿¯ \\._@-]*$" ) );
	l_poControl->enable ( true );
	l_poList->add_column ( -1, "Nazwisko", 24, D_ALIGN_LEFT, D_HSTRING,
			l_poControl = new HEditControl ( this, - 7, 20, 1, 28, " &Nazwisko: \n",
				32, "", "^[a-zA-Z±¡æÆêÊ³£ñÑóÓ¶¦¼¬¿¯ -]*$" ) );
	l_poControl->enable ( true );
	l_poList->add_column ( -1, "Ulica", 24, D_ALIGN_LEFT, D_HSTRING,
			l_poControl = f_poEdit = new HEditControl ( this, - 7, 49, 1, 29, " &Ulica: \n",
				32, "", D_MASK_LOOSE ) );
	l_poControl->enable ( true );
	l_poList->add_column ( -1, "", 0, D_ALIGN_LEFT, D_HSTRING,
			new HEditControl ( this, - 4, 1, 1, 32, " &Miasto: \n", 32, "",
				"^[a-zA-Z±¡æÆêÊ³£ñÑóÓ¶¦¼¬¿¯ \\.-]*$" ) );
	l_poList->add_column ( -1, "", 0, D_ALIGN_LEFT, D_HSTRING,
			new HEditControl ( this, - 4, 49, 1, 29, " &E-mail: \n", 48, "",
				"^[a-zA-Z0-9\\._@-]*$" ) );
	l_poCombo = new HComboboxControl ( this, - 10, 1, 9, 24,
			" &Kombo Testowe: \n", 32, 128, D_MASK_EXTENDED );
	f_oControls.exchange ( 1, 6 );
	f_oControls.exchange ( 2, 6 );
	f_oControls.exchange ( 3, 6 );
	l_poCombo->add_column ( -1, "dummy_label", 1, D_ALIGN_LEFT, D_HSTRING );
	l_poCombo->enable ( true );
	l_oItem [ 0 ] ( "Ala" );
	l_poCombo->add_orderly ( l_oItem );
	l_oItem [ 0 ] ( "ma" );
	l_poCombo->add_orderly ( l_oItem );
	l_oItem [ 0 ] ( "kota." );
	l_poCombo->add_orderly ( l_oItem );
	rs.open ( );
	while ( ! rs.is_eof ( ) )
		{
		l_oRow [ 0 ] ( rs.m_imie );
		l_oRow [ 1 ] ( rs.m_nazwisko );
		l_oRow [ 2 ] ( rs.m_ulica );
		l_oRow [ 3 ] ( rs.m_miasto );
		l_oRow [ 4 ] ( rs.m_email );
		l_poList->add_tail ( & l_oRow );
		if ( ! rs.m_telefon.is_empty ( ) )
			{
			l_oItem [ 0 ] ( rs.m_telefon );
			l_poCombo->add_orderly ( l_oItem );
			}
		rs.move_next ( );
		}
	rs.close ( );
	l_poList->enable ( true );
	l_poList->set_focus ( );
	refresh ( );
	return ( l_iError );
	M_EPILOG
	}

int HDictionaryContractingPartyWindow::handler_delete ( int, void * )
	{
	M_PROLOG
	if ( f_poList->quantity ( ) )
		f_poList->remove_element ( D_EMPTY_IF_NOT_EMPTIED );
	return ( 0 );
	M_EPILOG
	}

int HDictionaryContractingPartyWindow::handler_enter ( int, void * )
	{
	M_PROLOG
	if ( f_poList->quantity ( ) )
		f_poList->present( ) [ 2 ] = f_poEdit->get ( );
	return ( 0 );
	M_EPILOG
	}

