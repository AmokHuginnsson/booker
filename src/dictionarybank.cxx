/* Read booker/LICENSE.md file for copyright and licensing information. */

#include <libintl.h>

#include "dictionarybank.hxx"
M_VCSID( "$Id: " __ID__ " $" )
#include <yaal/tools/hexpression.hxx>
#include <yaal/tools/money.hxx>

#include "setup.hxx"
#include "booker.hxx"

using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::hconsole::list_widget_helper;
using namespace yaal::tools;
using namespace yaal::dbwrapper;
using namespace yaal::hdata;

namespace booker {

HDictionaryBank::HDictionaryBank( const char* title_, HDataProcess* owner_ )
		: HDataWindow( title_, owner_ ) {
	M_PROLOG
  register_postprocess_handler( 'a', NULL, call( &HDictionaryBank::handler_add, this, _1 ) );
	return;
	M_EPILOG
}

HDictionaryBank::~HDictionaryBank ( void ) {
	M_PROLOG
	return;
	M_EPILOG
}

bool HDictionaryBank::handler_add( hconsole::HEvent const& ) {
	M_PROLOG
	double value( 0 );
	HExpression analyser;
	HInfoItem item( 6 );
	HRandomizer rnd( 0 );
	HDataListWidget* list = dynamic_cast<HDataListWidget*>( _widgets.get_widget_by_no( 1 ) );
	M_ASSERT( list != NULL );
	analyser.compile( "A+B" );
	int long const TO_ADD = 500000;
	_statusBar->init_progress ( TO_ADD, _( "Precaching ..." ) );
	HAsIsValueListModel<>::ptr_t controler = list->get_model();
	for ( int long ctr = 0; ctr < TO_ADD; ctr ++ ) {
/*		value = list->size ( ) / 100.;*/
		value = static_cast<double>( rnd() ) / 100.;
/*
		analyser [ 'A' ] = value;
		analyser [ 'B' ] = value * value;
		value = analyser.evaluate ( );
*/
		item[ 0 ].set_string( tools::money::in_words_pl( value, money::CURRENCY::PLN ) );
		item[ 1 ].set_string( "wype³niacz" );
/*		iitem [ 2 ] = HString ( value );*/
		item[ 2 ].set_real( value );
		controler->add_tail( item );
		_statusBar->update_progress();
	}
/*
 * tested list control by filling it with 276300 rows
 */
	paint();
	return ( true );
	M_EPILOG
}

}

