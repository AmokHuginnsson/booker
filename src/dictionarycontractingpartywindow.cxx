/*
---           booker 0.0.0 (c) 1978 by Marcin 'Amok' Konarski            ---

	dictionarycontractingpartywindow.cxx - this file is integral part of booker project.

  i.  You may not make any changes in Copyright information.
  ii. You must attach Copyright information to any part of every copy
      of this software.

Copyright:

 You can use this software free of charge and you can redistribute its binary
 package freely but:
  1. You are not allowed to use any part of sources of this software.
  2. You are not allowed to redistribute any part of sources of this software.
  3. You are not allowed to reverse engineer this software.
  4. If you want to distribute a binary package of this software you cannot
     demand any fees for it. You cannot even demand
     a return of cost of the media or distribution (CD for example).
  5. You cannot involve this software in any commercial activity (for example
     as a free add-on to paid software or newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

#include <yaal/yaal.hxx> /* all hAPI headers */
M_VCSID( "$Id: " __ID__ " $" )

#include "booker.hxx"
#include "dictionarycontractingpartywindow.hxx"
#include "dictionarycontractingpartyset.hxx"

using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::hconsole::list_control_helper;
using namespace yaal::dbwrapper;

namespace booker {

HDictionaryContractingPartyWindow::HDictionaryContractingPartyWindow( const char* title_ )
	: HWindow( title_ ), _list ( NULL ), _edit ( NULL ) {
	M_PROLOG
	register_postprocess_handler( KEY_CODES::DELETE, NULL, call( &HDictionaryContractingPartyWindow::handler_delete, this, _1 ) );
	register_postprocess_handler( '\r', NULL, call( &HDictionaryContractingPartyWindow::handler_enter, this, _1 ) );
	return;
	M_EPILOG
}

HDictionaryContractingPartyWindow::~HDictionaryContractingPartyWindow ( void ) {
	M_PROLOG
	return;
	M_EPILOG
}

int HDictionaryContractingPartyWindow::init( void ) {
	M_PROLOG
	int error( 0 );
	HControl* control( NULL );
	HInfoItem item( 1 ), row( 5 );
	HListControl* list( NULL );
	HComboboxControl* combo( NULL );
	error = HWindow::init();

	_list = list = new HListControl( this, 1, 1, - 11, - 1,
			"&Kontrahenci" );
	list->enable( true );
	list->set_focus();
	list->add_column( -1, "Imi�", 16, HControl::BITS::ALIGN::LEFT, TYPE::HSTRING,
			control = new HEditControl( this,
				- 7, 1, 1, 18, "&Imi�",
				HEditControlAttrubites()
				.max_string_size( 32 )
				.pattern( "^[a-zA-Z�����ʳ����Ӷ����� \\._@-]*$" )
				.label_position( HControl::LABEL::POSITION::STACKED ) ) );
	control->enable( true );
	list->add_column( -1, "Nazwisko", 20, HControl::BITS::ALIGN::LEFT, TYPE::HSTRING,
			control = new HEditControl( this, - 7, 20, 1, 28, "&Nazwisko",
				HEditControlAttrubites()
				.max_string_size( 32 )
				.pattern( "^[a-zA-Z�����ʳ����Ӷ����� -]*$" )
				.label_position( HControl::LABEL::POSITION::STACKED ) ) );
	control->enable( true );
	list->add_column( -1, "Ulica", 24, HControl::BITS::ALIGN::LEFT, TYPE::HSTRING,
			control = _edit = new HEditControl ( this, - 7, 49, 1, 29, "&Ulica",
				HEditControlAttrubites()
				.max_string_size( 32 )
				.pattern( _maskLoose_ )
				.label_position( HControl::LABEL::POSITION::STACKED ) ) );
	control->enable( true );
	list->add_column( -1, "Miasto", 20, HControl::BITS::ALIGN::CENTER, TYPE::HSTRING,
			new HEditControl( this, - 4, 1, 1, 32, "&Miasto",
				HEditControlAttrubites()
				.max_string_size( 32 )
				.pattern( "^[a-zA-Z�����ʳ����Ӷ����� \\.-]*$" )
				.label_position( HControl::LABEL::POSITION::STACKED ) ) );
	list->add_column( -1, "e-mail", 24, HControl::BITS::ALIGN::RIGHT, TYPE::HSTRING,
			new HEditControl( this, - 4, 49, 1, 29, "&E-mail",
				HEditControlAttrubites()
				.max_string_size( 48 )
				.pattern( "^[a-zA-Z0-9\\._@-]*$" )
				.label_position( HControl::LABEL::POSITION::STACKED ) ) );
	combo = new HComboboxControl( this, - 10, 1, 9, 24,
			"&Kombo Testowe", 32, 128, _maskExtended_ );
	_list->set_label_position( HControl::LABEL::POSITION::STACKED );
	_controls.exchange( 1, 6 );
	_controls.exchange( 2, 6 );
	_controls.exchange( 3, 6 );
	combo->add_column( -1, "dummy_label", 1, HControl::BITS::ALIGN::LEFT, TYPE::HSTRING );
	combo->HListControl::set_flags( HListControl::FLAG::NONE, HListControl::FLAG::DRAW_HEADER );
	combo->enable( true );
	HListControler<>::ptr_t controler = combo->get_controler();
	item[ 0 ].set_string( "Ala" );
	controler->add_orderly( item, 0 );
	item[ 0 ].set_string( "ma" );
	controler->add_orderly( item, 0 );
	item[ 0 ].set_string( "kota." );
	controler->add_orderly( item, 0 );
	HDictionaryContractingPartySet rs( theProc.data_base() );
	HRecordSet::ptr_t r = rs.get_records();
	HListControler<>::ptr_t mC = list->get_controler();
	for ( HRecordSet::iterator it = r->begin(); it != r->end(); ++ it ) {
		rs.sync( it );
		row[ 0 ].set_string( rs._imie );
		row[ 1 ].set_string( rs._nazwisko );
		row[ 2 ].set_string( rs._ulica );
		row[ 3 ].set_string( rs._miasto );
		row[ 4 ].set_string( rs._email );
		mC->add_tail( row );
		if ( ! rs._telefon.is_empty() ) {
			item[ 0 ].set_string( rs._telefon );
			controler->add_orderly( item, 0 );
		}
	}
	paint();
	return ( error );
	M_EPILOG
}

bool HDictionaryContractingPartyWindow::handler_delete( yaal::hconsole::HEvent const& ) {
	M_PROLOG
	if ( _list->get_row_count() )
		_list->remove_current_row();
	return ( true );
	M_EPILOG
}

bool HDictionaryContractingPartyWindow::handler_enter( yaal::hconsole::HEvent const& ) {
	M_PROLOG
//	if ( _list->get_row_count() )
//		_list->set_current_row_cell( 2, _edit->get() );
	return ( true );
	M_EPILOG
}

}

