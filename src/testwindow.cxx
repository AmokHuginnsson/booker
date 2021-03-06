/* Read booker/LICENSE.md file for copyright and licensing information. */

#include "testwindow.hxx"
M_VCSID( "$Id: " __ID__ " $" )
#include <yaal/hconsole/hdatewidget.hxx>
#include <yaal/hconsole/htimewidget.hxx>
#include <yaal/tools/keycode.hxx>

#include "booker.hxx"
#include "testset.hxx"

using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::hconsole;
using namespace yaal::hconsole::list_widget_helper;
using namespace yaal::dbwrapper;

namespace booker {

HTestWindow::HTestWindow( const char* title_ )
	: HWindow( title_ ), _names(), _list( nullptr ), _editableList( nullptr ), _edit( nullptr ), _name( nullptr ) {
	M_PROLOG
	register_postprocess_handler( KEY_CODE::DELETE, nullptr, call( &HTestWindow::handler_delete, this, _1 ) );
	register_postprocess_handler( '\r', nullptr, call( &HTestWindow::handler_enter, this, _1 ) );
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
	_name = create_widget<HComboboxWidget>( this, -16, 1, 9, 24, "&Name",
			HComboboxWidgetAttributes()
				.dropped_width( 32 )
				.max_string_size( 128 )
				.mask( "^[a-zA-ZąĄćĆęĘłŁńŃóÓśŚźŹżŻ \\._@-]*$" )
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
	_list = create_widget<HListWidget>( this, 1, 1, -17, -1, "&Test data", HListWidgetAttributes().searchable( true ) );
	_list->enable( true );
	_list->set_focus();
	_list->add_column( -1, make_resource<HListWidget::HColumnInfo>( "Name", 16, HWidget::BITS::ALIGN::LEFT, TYPE::HSTRING, "", _name ) );
	HWidget* control( nullptr );
	_list->add_column( -1, make_resource<HListWidget::HColumnInfo>( "Text", 32, HWidget::BITS::ALIGN::LEFT, TYPE::HSTRING, "",
			control = create_widget<HEditWidget>( this, -16, 27, 1, -1, "Te&xt",
				HEditWidgetAttributes()
				.max_string_size( 64 )
				.mask( "^[a-zA-ZąĄćĆęĘłŁńŃóÓśŚźŹżŻ !,-]*$" )
				.label_position( HWidget::LABEL::POSITION::STACKED ) ) ) );
	control->enable( true );
	_list->add_column( -1, make_resource<HListWidget::HColumnInfo>( "Int", 16, HWidget::BITS::ALIGN::RIGHT, TYPE::HSTRING, "",
			control = _edit = create_widget<HEditWidget>( this, -13, 1, 1, 20, "&Int",
				HEditWidgetAttributes()
				.max_string_size( 32 )
				.mask( "^[0-9]*$" )
				.label_position( HWidget::LABEL::POSITION::STACKED ) ) ) );
	control->enable( true );
	_list->add_column( -1, make_resource<HListWidget::HColumnInfo>( "Real", 20, HWidget::BITS::ALIGN::RIGHT, TYPE::HSTRING, "",
			control = create_widget<HEditWidget>( this, -13, 23, 1, 24, "&Real",
				HEditWidgetAttributes()
				.max_string_size( 32 )
				.mask( "^[0-9\\.-]*$" )
				.label_position( HWidget::LABEL::POSITION::STACKED ) ) ) );
	control->enable( true );
	_list->add_column( -1, make_resource<HListWidget::HColumnInfo>( "Date", 11, HWidget::BITS::ALIGN::CENTER, TYPE::HTIME, "",
			control = create_widget<HDateWidget>( this, -13, 49, "&Date",
				HWidgetAttributes()
				.label_position( HWidget::LABEL::POSITION::STACKED ) ) ) );
	control->enable( true );
	_list->add_column( -1, make_resource<HListWidget::HColumnInfo>( "Time", 11, HWidget::BITS::ALIGN::CENTER, TYPE::HTIME, "",
			control = create_widget<HTimeWidget>( this, -13, 63, "&Time",
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
	HInfoItem row( 6 );
	for ( HRecordSet::iterator it = r->begin(); it != r->end(); ++ it ) {
		rs.sync( it );
		row[ 0 ].set_integer( _names[static_cast<int>( rs._idName )].first );
		row[ 0 ].set_string( _names[static_cast<int>( rs._idName )].second );
		row[ 1 ].set_string( rs._vText );
		row[ 2 ].set_string( rs._vInt );
		row[ 3 ].set_string( rs._vReal );
		row[ 4 ].set_time( rs._vDate );
		row[ 5 ].set_time( rs._vTime );
		mC->add_tail( row );
	}
	_editableList = create_widget<HListWidget>( this, -10, 1, -3, -1, "&Edit test",
			HListWidgetAttributes()
			.editable( true )
			.searchable( true )
			.label_position( HWidget::LABEL::POSITION::STACKED ) );
	_editableList->add_column( -1, make_resource<HListWidget::HColumnInfo>( "text", 1, HWidget::BITS::ALIGN::LEFT, TYPE::HSTRING ) );
	_editableList->add_column( -1, make_resource<HListWidget::HColumnInfo>( "integer", 1, HWidget::BITS::ALIGN::RIGHT, TYPE::INT_LONG_LONG ) );
	_editableList->add_column( -1, make_resource<HListWidget::HColumnInfo>( "real", 1, HWidget::BITS::ALIGN::RIGHT, TYPE::DOUBLE_LONG ) );
	_editableList->enable( true );
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
	if ( _list->has_focus() && _list->get_row_count() ) {
		_list->remove_current_row();
	}
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

