/*
---        `booker' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski         ---

	booker.cxx - this file is integral part of `booker' project.

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


#include <yaal/yaal.hxx>
M_VCSID( "$Id: " __ID__ " $" )

#include "booker.hxx"
#include "setup.hxx"

/* windows begin */
#include "dictionarybank.hxx"
#include "testwindow.hxx"
/* windows end */

using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::dbwrapper;
using namespace yaal::hdata;

namespace booker {

HBookerProcess::HBookerProcess ( void )
	:	HDataProcess() {
	M_PROLOG
	return;
	M_EPILOG
}

HBookerProcess::~HBookerProcess ( void ) {
	M_PROLOG
	return;
	M_EPILOG
}

int HBookerProcess::init( const char* processName_ ) {
	M_PROLOG
	_dataBase->connect( setup._dataBase, setup._login, setup._password );
	register_command_handler( "run_quit", call( &HBookerProcess::run_quit, this, _1 ) );
	register_command_handler( "run_dictionary_contracting_party", call( &HBookerProcess::run_dictionary_contracting_party, this, _1 ) );
	register_command_handler( "run_subject", call( &HBookerProcess::run_subject, this, _1 ) );
	register_command_handler( "run_config", call( &HBookerProcess::run_config, this, _1 ) );
	register_command_handler( "run_test", call( &HBookerProcess::run_test, this, _1 ) );
	/*
	M_REGISTER_MENU_HANDLER ( run_account_orders );
	M_REGISTER_MENU_HANDLER ( run_account_map );
	M_REGISTER_MENU_HANDLER ( run_regular_oblige );
	*/
	HDataProcess::init_xrc( processName_, "booker.xrc" );
	return ( 0 );
	M_EPILOG
}

bool HBookerProcess::run_quit( yaal::hconsole::HEvent const& ) {
	M_PROLOG
	quit();
	return ( true );
	M_EPILOG
}

bool HBookerProcess::run_dictionary_contracting_party( yaal::hconsole::HEvent const& ) {
	M_PROLOG
	return ( true );
	M_EPILOG
}

bool HBookerProcess::run_config( yaal::hconsole::HEvent const& ) {
	M_PROLOG
	HConsole& cons( HConsole::get_instance() );
	cons.cmvprintf ( cons.get_height() - 2, -1, 48, "run_config" );
	cons.refresh ( );
	return ( true );
	M_EPILOG
}

bool HBookerProcess::run_test( yaal::hconsole::HEvent const& ) {
	M_PROLOG
	if ( setup._test ) {
		add_window( make_pointer<HTestWindow>( "Test" ) );
	}
	return ( true );
	M_EPILOG
}

bool HBookerProcess::run_subject( yaal::hconsole::HEvent const& ) {
	M_PROLOG
	HConsole& cons = HConsole::get_instance();
	cons.cmvprintf ( cons.get_height() - 2, -1, 48, "run_subject" );
	cons.refresh ( );
	return ( true );
	M_EPILOG
}

bool HBookerProcess::run_account_map( yaal::hconsole::HEvent const& ) {
	M_PROLOG
	HConsole& cons = HConsole::get_instance();
	cons.cmvprintf ( cons.get_height() - 2, -1, 48, "run_account_map" );
	cons.refresh ( );
	return ( true );
	M_EPILOG
}

bool HBookerProcess::run_account_orders( yaal::hconsole::HEvent const& ) {
	M_PROLOG
	HConsole& cons = HConsole::get_instance();
	cons.cmvprintf ( cons.get_height() - 2, -1, 48, "run_account_orders" );
	cons.refresh ( );
	return ( true );
	M_EPILOG
}

bool HBookerProcess::run_regular_oblige( yaal::hconsole::HEvent const& ) {
	M_PROLOG
	HConsole& cons = HConsole::get_instance();
	cons.cmvprintf ( cons.get_height() - 2, -1, 48, "run_regular_oblige" );
	cons.refresh ( );
	return ( true );
	M_EPILOG
}

}

