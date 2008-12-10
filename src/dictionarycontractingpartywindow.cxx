/*
---           booker 0.0.0 (c) 1978 by Marcin 'Amok' Konarski            ---

	dictionarycontractingpartywindow.cxx - this file is integral part of booker project.

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

#include <yaal/yaal.hxx> /* all hAPI headers */
M_VCSID( "$Id: "__ID__" $" )

#include "booker.hxx"
#include "dictionarycontractingpartywindow.hxx"
#include "dictionarycontractingpartyset.hxx"

using namespace yaal;
using namespace yaal::hconsole;
using namespace yaal::hconsole::list_control_helper;
using namespace yaal::dbwrapper;

namespace booker
{

HDictionaryContractingPartyWindow::HDictionaryContractingPartyWindow ( const char * a_pcTitle )
	: HWindow ( a_pcTitle ), f_poList ( NULL ), f_poEdit ( NULL )
	{
	M_PROLOG
	register_postprocess_handler ( KEY_CODES::D_DELETE, NULL,
			& HDictionaryContractingPartyWindow::handler_delete );
	register_postprocess_handler ( '\r', NULL,
			& HDictionaryContractingPartyWindow::handler_enter );
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
	l_iError = HWindow::init ( );
	f_poList = l_poList = new HListControl ( this, 1, 1, - 11, - 1,
			" &Kontrahenci: \n" );
	l_poList->enable ( true );
	l_poList->set_focus ( );
	l_poList->add_column ( -1, "Imiê", 16, HControl::BITS::ALIGN::D_LEFT, D_HSTRING,
			l_poControl = new HEditControl ( this,
				- 7, 1, 1, 18, " &Imiê: \n", 32, "",
				"^[a-zA-Z0-9±¡æÆêÊ³£ñÑóÓ¶¦¼¬¿¯ \\._@-]*$" ) );
	l_poControl->enable ( true );
	l_poList->add_column ( -1, "Nazwisko", 20, HControl::BITS::ALIGN::D_LEFT, D_HSTRING,
			l_poControl = new HEditControl ( this, - 7, 20, 1, 28, " &Nazwisko: \n",
				32, "", "^[a-zA-Z±¡æÆêÊ³£ñÑóÓ¶¦¼¬¿¯ -]*$" ) );
	l_poControl->enable ( true );
	l_poList->add_column ( -1, "Ulica", 24, HControl::BITS::ALIGN::D_LEFT, D_HSTRING,
			l_poControl = f_poEdit = new HEditControl ( this, - 7, 49, 1, 29, " &Ulica: \n",
				32, "", n_pcMaskLoose ) );
	l_poControl->enable ( true );
	l_poList->add_column ( -1, "Miasto", 20, HControl::BITS::ALIGN::D_CENTER, D_HSTRING,
			new HEditControl ( this, - 4, 1, 1, 32, " &Miasto: \n", 32, "",
				"^[a-zA-Z±¡æÆêÊ³£ñÑóÓ¶¦¼¬¿¯ \\.-]*$" ) );
	l_poList->add_column ( -1, "e-mail", 24, HControl::BITS::ALIGN::D_RIGHT, D_HSTRING,
			new HEditControl ( this, - 4, 49, 1, 29, " &E-mail: \n", 48, "",
				"^[a-zA-Z0-9\\._@-]*$" ) );
	l_poCombo = new HComboboxControl ( this, - 10, 1, 9, 24,
			" &Kombo Testowe: \n", 32, 128, n_pcMaskExtended );
	f_oControls.exchange ( 1, 6 );
	f_oControls.exchange ( 2, 6 );
	f_oControls.exchange ( 3, 6 );
	l_poCombo->add_column ( -1, "dummy_label", 1, HControl::BITS::ALIGN::D_LEFT, D_HSTRING );
	l_poCombo->HListControl::set_flags( HListControl::FLAGS::D_NONE, HListControl::FLAGS::D_DRAW_HEADER );
	l_poCombo->enable ( true );
	HListControler<>::ptr_t l_oControler = l_poCombo->get_controler();
	l_oItem [ 0 ] ( "Ala" );
	l_oControler->add_orderly ( l_oItem, 0 );
	l_oItem [ 0 ] ( "ma" );
	l_oControler->add_orderly ( l_oItem, 0 );
	l_oItem [ 0 ] ( "kota." );
	l_oControler->add_orderly ( l_oItem, 0 );
	HDictionaryContractingPartySet rs ( theProc.data_base() );
	HRecordSet::ptr_t r = rs.get_records();
	HListControler<>::ptr_t l_oMC = l_poList->get_controler();
	for ( HRecordSet::iterator it = r->begin(); it != r->end(); ++ it )
		{
		rs.sync( it );
		l_oRow [ 0 ] ( rs.m_imie );
		l_oRow [ 1 ] ( rs.m_nazwisko );
		l_oRow [ 2 ] ( rs.m_ulica );
		l_oRow [ 3 ] ( rs.m_miasto );
		l_oRow [ 4 ] ( rs.m_email );
		l_oMC->add_tail ( l_oRow );
		if ( ! rs.m_telefon.is_empty ( ) )
			{
			l_oItem [ 0 ] ( rs.m_telefon );
			l_oControler->add_orderly ( l_oItem, 0 );
			}
		}
	refresh ( );
	return ( l_iError );
	M_EPILOG
	}

int HDictionaryContractingPartyWindow::handler_delete( int, void const* )
	{
	M_PROLOG
	if ( f_poList->get_row_count() )
		f_poList->remove_current_row();
	return ( 0 );
	M_EPILOG
	}

int HDictionaryContractingPartyWindow::handler_enter( int, void const* )
	{
	M_PROLOG
//	if ( f_poList->get_row_count() )
//		f_poList->set_current_row_cell( 2, f_poEdit->get() );
	return ( 0 );
	M_EPILOG
	}

}

