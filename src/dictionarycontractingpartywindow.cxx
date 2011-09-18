/*
---           booker 0.0.0 (c) 1978 by Marcin 'Amok' Konarski            ---

	dictionarycontractingpartywindow.cxx - this file is integral part of booker project.

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

#include <yaal/yaal.hxx> /* all hAPI headers */
M_VCSID( "$Id: "__ID__" $" )

#include "booker.hxx"
#include "dictionarycontractingpartywindow.hxx"
#include "dictionarycontractingpartyset.hxx"

using namespace yaal;
using namespace yaal::hconsole;
using namespace yaal::hconsole::list_control_helper;
using namespace yaal::dbwrapper;

namespace booker {

HDictionaryContractingPartyWindow::HDictionaryContractingPartyWindow ( const char * title_ )
	: HWindow ( title_ ), _list ( NULL ), _edit ( NULL ) {
	M_PROLOG
	register_postprocess_handler ( KEY_CODES::DELETE, NULL,
			& HDictionaryContractingPartyWindow::handler_delete );
	register_postprocess_handler ( '\r', NULL,
			& HDictionaryContractingPartyWindow::handler_enter );
	return;
	M_EPILOG
}

HDictionaryContractingPartyWindow::~HDictionaryContractingPartyWindow ( void ) {
	M_PROLOG
	return;
	M_EPILOG
}

int HDictionaryContractingPartyWindow::init ( void ) {
	M_PROLOG
	int error = 0;
	HControl * control = NULL;
	HItem item ( 1 ), row ( 5 );
	HListControl * list = NULL;
	HComboboxControl * combo = NULL;
	error = HWindow::init ( );
	_list = list = new HListControl ( this, 1, 1, - 11, - 1,
			" &Kontrahenci: \n" );
	list->enable ( true );
	list->set_focus ( );
	list->add_column ( -1, "Imiê", 16, HControl::BITS::ALIGN::LEFT, TYPE::HSTRING,
			control = new HEditControl ( this,
				- 7, 1, 1, 18, " &Imiê: \n", 32, "",
				"^[a-zA-Z0-9±¡æÆêÊ³£ñÑóÓ¶¦¼¬¿¯ \\._@-]*$" ) );
	control->enable ( true );
	list->add_column ( -1, "Nazwisko", 20, HControl::BITS::ALIGN::LEFT, TYPE::HSTRING,
			control = new HEditControl ( this, - 7, 20, 1, 28, " &Nazwisko: \n",
				32, "", "^[a-zA-Z±¡æÆêÊ³£ñÑóÓ¶¦¼¬¿¯ -]*$" ) );
	control->enable ( true );
	list->add_column ( -1, "Ulica", 24, HControl::BITS::ALIGN::LEFT, TYPE::HSTRING,
			control = _edit = new HEditControl ( this, - 7, 49, 1, 29, " &Ulica: \n",
				32, "", _maskLoose_ ) );
	control->enable ( true );
	list->add_column ( -1, "Miasto", 20, HControl::BITS::ALIGN::CENTER, TYPE::HSTRING,
			new HEditControl ( this, - 4, 1, 1, 32, " &Miasto: \n", 32, "",
				"^[a-zA-Z±¡æÆêÊ³£ñÑóÓ¶¦¼¬¿¯ \\.-]*$" ) );
	list->add_column ( -1, "e-mail", 24, HControl::BITS::ALIGN::RIGHT, TYPE::HSTRING,
			new HEditControl ( this, - 4, 49, 1, 29, " &E-mail: \n", 48, "",
				"^[a-zA-Z0-9\\._@-]*$" ) );
	combo = new HComboboxControl ( this, - 10, 1, 9, 24,
			" &Kombo Testowe: \n", 32, 128, _maskExtended_ );
	_controls.exchange ( 1, 6 );
	_controls.exchange ( 2, 6 );
	_controls.exchange ( 3, 6 );
	combo->add_column ( -1, "dummy_label", 1, HControl::BITS::ALIGN::LEFT, TYPE::HSTRING );
	combo->HListControl::set_flags( HListControl::FLAG::NONE, HListControl::FLAG::DRAW_HEADER );
	combo->enable ( true );
	HListControler<>::ptr_t controler = combo->get_controler();
	item [ 0 ] ( "Ala" );
	controler->add_orderly ( item, 0 );
	item [ 0 ] ( "ma" );
	controler->add_orderly ( item, 0 );
	item [ 0 ] ( "kota." );
	controler->add_orderly ( item, 0 );
	HDictionaryContractingPartySet rs ( theProc.data_base() );
	HRecordSet::ptr_t r = rs.get_records();
	HListControler<>::ptr_t mC = list->get_controler();
	for ( HRecordSet::iterator it = r->begin(); it != r->end(); ++ it ) {
		rs.sync( it );
		row [ 0 ] ( rs.m_imie );
		row [ 1 ] ( rs.m_nazwisko );
		row [ 2 ] ( rs.m_ulica );
		row [ 3 ] ( rs.m_miasto );
		row [ 4 ] ( rs.m_email );
		mC->add_tail ( row );
		if ( ! rs.m_telefon.is_empty ( ) ) {
			item [ 0 ] ( rs.m_telefon );
			controler->add_orderly ( item, 0 );
		}
	}
	refresh ( );
	return ( error );
	M_EPILOG
}

int HDictionaryContractingPartyWindow::handler_delete( int, void const* ) {
	M_PROLOG
	if ( _list->get_row_count() )
		_list->remove_current_row();
	return ( 0 );
	M_EPILOG
}

int HDictionaryContractingPartyWindow::handler_enter( int, void const* ) {
	M_PROLOG
//	if ( _list->get_row_count() )
//		_list->set_current_row_cell( 2, _edit->get() );
	return ( 0 );
	M_EPILOG
}

}

