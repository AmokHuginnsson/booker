/*
---           booker 0.0.0 (c) 1978 by Marcin 'Amok' Konarski            ---

	dictionarybankwindow.cxx - this file is integral part of booker project.

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

#include <libintl.h>
#include <yaal/yaal.hxx> /* all hAPI headers */
M_VCSID( "$Id: " __ID__ " $" )

#include "setup.hxx"
#include "booker.hxx"
#include "dictionarybank.hxx"

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
		item[ 0 ].set_string( tools::util::kwota_slownie( value ) );
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

