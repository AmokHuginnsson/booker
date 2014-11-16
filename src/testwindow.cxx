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
	: HWindow( title_ ), _names(), _list( NULL ), _edit( NULL ), _name( NULL ) {
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
	HWindow::do_init();
	_name = new HComboboxWidget( this, - 21, 1, 9, 24, "&Name",
			HComboboxWidgetAttributes()
				.dropped_width( 32 )
				.max_string_size( 128 )
				.pattern( "^[a-zA-Z±°Ê∆Í ≥£Ò—Û”∂¶º¨øØ \\._@-]*$" )
				.label_position( HWidget::LABEL::POSITION::STACKED )
				.up<HComboboxWidgetAttributes>()
				.searchable( true )
	);
	_name->enable( true );
	HQuery::ptr_t q( theProc.data_base()->prepare_query( "SELECT * FROM test_dict;" ) );
	HRecordSet::ptr_t dict( q->execute() );
	HAsIsValueListModel<>::ptr_t controler = _name->get_model();
	int index( 0 );
	for ( HRecordSet::values_t const& row : *dict ) {
		int id( lexical_cast<int>( *row[0] ) );
		HString const& name( *row[1] );
		_names[id] = make_pair( index ++, name );
		HInfoItem item( 1 );
		item[ 0 ].set_integer( id );
		item[ 0 ].set_string( name );
		controler->add_tail( item );
	}
	_list = new HListWidget( this, 1, 1, - 22, - 1,
			"&Test data", HListWidgetAttributes().searchable( true ) );
	_list->enable( true );
	_list->set_focus();
	_list->add_column( -1, make_resource<HListWidget::HColumnInfo>( "Name", 16, HWidget::BITS::ALIGN::LEFT, TYPE::HSTRING, _name ) );
	HWidget* control( NULL );
	_list->add_column( -1, make_resource<HListWidget::HColumnInfo>( "Text", 32, HWidget::BITS::ALIGN::LEFT, TYPE::HSTRING,
			control = new HEditWidget( this, - 21, 40, 1, 39, "&Text",
				HEditWidgetAttributes()
				.max_string_size( 32 )
				.pattern( "^[a-zA-Z±°Ê∆Í ≥£Ò—Û”∂¶º¨øØ !,-]*$" )
				.label_position( HWidget::LABEL::POSITION::STACKED ) ) ) );
	control->enable( true );
	_list->add_column( -1, make_resource<HListWidget::HColumnInfo>( "Int", 16, HWidget::BITS::ALIGN::RIGHT, TYPE::HSTRING,
			control = _edit = new HEditWidget ( this, - 18, 1, 1, 29, "&Int",
				HEditWidgetAttributes()
				.max_string_size( 32 )
				.pattern( "^[0-9]*$" )
				.label_position( HWidget::LABEL::POSITION::STACKED ) ) ) );
	control->enable( true );
	_list->add_column( -1, make_resource<HListWidget::HColumnInfo>( "Real", 20, HWidget::BITS::ALIGN::RIGHT, TYPE::HSTRING,
			control = new HEditWidget( this, - 15, 1, 1, 32, "&Real",
				HEditWidgetAttributes()
				.max_string_size( 32 )
				.pattern( "^[0-9\\.-]*$" )
				.label_position( HWidget::LABEL::POSITION::STACKED ) ) ) );
	control->enable( true );
	_list->add_column( -1, make_resource<HListWidget::HColumnInfo>( "Date", 11, HWidget::BITS::ALIGN::CENTER, TYPE::HTIME,
			control = new HDateWidget( this, - 12, 1, "&Date",
				HWidgetAttributes()
				.label_position( HWidget::LABEL::POSITION::STACKED ) ) ) );
	control->enable( true );
	_list->set_label_position( HWidget::LABEL::POSITION::STACKED );
	_list->register_event_listener( call( &HTestWindow::on_sel_change, this, _1 ) );
/*	_widgets.exchange( 1, 6 );
	_widgets.exchange( 2, 6 );
	_widgets.exchange( 3, 6 ); */
	HTestSet rs( theProc.data_base() );
	HRecordSet::ptr_t r = rs.get_records();
	HAsIsValueListModel<>::ptr_t mC = _list->get_model();
	HInfoItem row( 5 );
	for ( HRecordSet::iterator it = r->begin(); it != r->end(); ++ it ) {
		rs.sync( it );
		row[ 0 ].set_integer( _names[static_cast<int>( rs._idName )].first );
		row[ 0 ].set_string( _names[static_cast<int>( rs._idName )].second );
		row[ 1 ].set_string( rs._vText );
		row[ 2 ].set_string( rs._vInt );
		row[ 3 ].set_string( rs._vReal );
		row[ 4 ].set_time( rs._vDate );
		mC->add_tail( row );
	}
	paint();
	return;
	M_EPILOG
}

bool HTestWindow::on_sel_change( yaal::hconsole::HEvent const& ) {
	list_widget_helper::HAbstractRow& current( _list->get_current_row() );
	status_bar()->message( "cursor position: %d, %d", _name->get_cursor_position(), static_cast<int>( current[0].get_integer() ) );
	return ( true );
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

