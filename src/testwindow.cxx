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
#include "testwindow.hxx"
#include "testset.hxx"

using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::hconsole::list_widget_helper;
using namespace yaal::dbwrapper;

namespace booker {

HTestWindow::HTestWindow( const char* title_ )
	: HWindow( title_ ), _list ( NULL ), _edit ( NULL ) {
	M_PROLOG
	register_postprocess_handler( KEY_CODES::DELETE, NULL, call( &HTestWindow::handler_delete, this, _1 ) );
	register_postprocess_handler( '\r', NULL, call( &HTestWindow::handler_enter, this, _1 ) );
	return;
	M_EPILOG
}

HTestWindow::~HTestWindow ( void ) {
	M_PROLOG
	return;
	M_EPILOG
}

void HTestWindow::do_init( void ) {
	M_PROLOG
	HWidget* control( NULL );
	HInfoItem item( 1 ), row( 5 );
	HListWidget* list( NULL );
	HComboboxWidget* combo( NULL );
	HWindow::do_init();

	_list = list = new HListWidget( this, 1, 1, - 20, - 1,
			"&Kontrahenci", HListWidgetAttributes().searchable( true ) );
	list->enable( true );
	list->set_focus();
	list->add_column( -1, "Name", 16, HWidget::BITS::ALIGN::LEFT, TYPE::HSTRING,
			control = new HEditWidget( this,
				- 19, 1, 1, 18, "&Name",
				HEditWidgetAttributes()
				.max_string_size( 32 )
				.pattern( "^[a-zA-Z±¡æÆêÊ³£ñÑóÓ¶¦¼¬¿¯ \\._@-]*$" )
				.label_position( HWidget::LABEL::POSITION::STACKED ) ) );
	control->enable( true );
	list->add_column( -1, "Text", 32, HWidget::BITS::ALIGN::LEFT, TYPE::HSTRING,
			control = new HEditWidget( this, - 19, 40, 1, 39, "&Text",
				HEditWidgetAttributes()
				.max_string_size( 32 )
				.pattern( "^[a-zA-Z±¡æÆêÊ³£ñÑóÓ¶¦¼¬¿¯ !,-]*$" )
				.label_position( HWidget::LABEL::POSITION::STACKED ) ) );
	control->enable( true );
	list->add_column( -1, "Int", 16, HWidget::BITS::ALIGN::RIGHT, TYPE::HSTRING,
			control = _edit = new HEditWidget ( this, - 16, 1, 1, 29, "&Int",
				HEditWidgetAttributes()
				.max_string_size( 32 )
				.pattern( "^[0-9]*$" )
				.label_position( HWidget::LABEL::POSITION::STACKED ) ) );
	control->enable( true );
	list->add_column( -1, "Real", 20, HWidget::BITS::ALIGN::RIGHT, TYPE::HSTRING,
			control = new HEditWidget( this, - 13, 1, 1, 32, "&Real",
				HEditWidgetAttributes()
				.max_string_size( 32 )
				.pattern( "^[0-9\\.-]*$" )
				.label_position( HWidget::LABEL::POSITION::STACKED ) ) );
	control->enable( true );
	list->add_column( -1, "Date", 11, HWidget::BITS::ALIGN::CENTER, TYPE::HTIME,
			control = new HDateWidget( this, - 10, 1, "&Date",
				HWidgetAttributes()
				.label_position( HWidget::LABEL::POSITION::STACKED ) ) );
	control->enable( true );
	combo = new HComboboxWidget( this, - 16, 40, 9, 24, "&Kombo Testowe",
			HComboboxWidgetAttributes()
				.dropped_width( 32 )
				.max_string_size( 128 )
				.pattern( _maskExtended_ )
				.label_position( HWidget::LABEL::POSITION::STACKED )
				.up<HComboboxWidgetAttributes>()
				.searchable( true )
	);
	_list->set_label_position( HWidget::LABEL::POSITION::STACKED );
/*	_widgets.exchange( 1, 6 );
	_widgets.exchange( 2, 6 );
	_widgets.exchange( 3, 6 ); */
	combo->add_column( -1, "dummy_label", 1, HWidget::BITS::ALIGN::LEFT, TYPE::HSTRING );
	combo->HListWidget::set_flags( HListWidget::FLAG::NONE, HListWidget::FLAG::DRAW_HEADER );
	combo->enable( true );
	HAsIsValueListModel<>::ptr_t controler = combo->get_model();
	item[ 0 ].set_string( "Ala" );
	controler->add_orderly( item, 0 );
	item[ 0 ].set_string( "ma" );
	controler->add_orderly( item, 0 );
	item[ 0 ].set_string( "kota." );
	controler->add_orderly( item, 0 );
	HTestSet rs( theProc.data_base() );
	HRecordSet::ptr_t r = rs.get_records();
	HAsIsValueListModel<>::ptr_t mC = list->get_model();
	for ( HRecordSet::iterator it = r->begin(); it != r->end(); ++ it ) {
		rs.sync( it );
		row[ 0 ].set_string( rs._name );
		row[ 1 ].set_string( rs._vText );
		row[ 2 ].set_string( rs._vInt );
		row[ 3 ].set_string( rs._vReal );
		row[ 4 ].set_time( rs._vDate );
		mC->add_tail( row );
		item[ 0 ].set_time( rs._vTime );
		controler->add_orderly( item, 0 );
	}
	paint();
	return;
	M_EPILOG
}

bool HTestWindow::handler_delete( yaal::hconsole::HEvent const& ) {
	M_PROLOG
	if ( _list->get_row_count() )
		_list->remove_current_row();
	return ( true );
	M_EPILOG
}

bool HTestWindow::handler_enter( yaal::hconsole::HEvent const& ) {
	M_PROLOG
//	if ( _list->get_row_count() )
//		_list->set_current_row_cell( 2, _edit->get() );
	return ( true );
	M_EPILOG
}

}

