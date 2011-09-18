/*
---        `booker' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski         ---

	booker.cxx - this file is integral part of `booker' project.

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


#include <yaal/yaal.hxx>
M_VCSID( "$Id: "__ID__" $" )

#include "booker.hxx"
#include "setup.hxx"

/* windows begin */
#include "dictionarybank.hxx"
#include "dictionarycontractingpartywindow.hxx"
/* windows end */

using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::dbwrapper;
using namespace yaal::hdata;

namespace booker {

static int const MENU_HANDLERS_MAP_SIZE = 32;

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

int HBookerProcess::init ( const char * processName_ ) {
	M_PROLOG
	_dataBase->connect( setup._dataBase, setup._login, setup._password );
	menu_handlers_map_t handlers ( MENU_HANDLERS_MAP_SIZE );
	M_REGISTER_MENU_HANDLER ( run_quit );
	M_REGISTER_MENU_HANDLER ( run_account_orders );
	M_REGISTER_MENU_HANDLER ( run_account_map );
	handlers [ "" ] = NULL;
	M_REGISTER_MENU_HANDLER ( run_dictionary_contracting_party );
	M_REGISTER_MENU_HANDLER ( run_regular_oblige );
	M_REGISTER_MENU_HANDLER ( run_subject );
	M_REGISTER_MENU_HANDLER ( run_config );
	HDataProcess::init_xrc ( processName_, "booker.xrc", handlers );
	return ( 0 );
	M_EPILOG
}

int HBookerProcess::run_quit( void* ) {
	M_PROLOG
	handler_quit ( KEY < 'x' >::command );
	return ( 0 );
	M_EPILOG
}

int HBookerProcess::run_dictionary_contracting_party( void* ) {
	M_PROLOG
	add_window( make_pointer<HDictionaryContractingPartyWindow>( "Kontrahenci" ) );
	return ( 0 );
	M_EPILOG
}

int HBookerProcess::run_config( void* ) {
	M_PROLOG
	HConsole& cons( HConsole::get_instance() );
	cons.c_cmvprintf ( cons.get_height() - 2, -1, 48, "run_config" );
	cons.c_refresh ( );
	return ( 0 );
	M_EPILOG
}

int HBookerProcess::run_subject( void* ) {
	M_PROLOG
	HConsole& cons = HConsole::get_instance();
	cons.c_cmvprintf ( cons.get_height() - 2, -1, 48, "run_subject" );
	cons.c_refresh ( );
	return ( 0 );
	M_EPILOG
}

int HBookerProcess::run_account_map( void* ) {
	M_PROLOG
	HConsole& cons = HConsole::get_instance();
	cons.c_cmvprintf ( cons.get_height() - 2, -1, 48, "run_account_map" );
	cons.c_refresh ( );
	return ( 0 );
	M_EPILOG
}

int HBookerProcess::run_account_orders( void* ) {
	M_PROLOG
	HConsole& cons = HConsole::get_instance();
	cons.c_cmvprintf ( cons.get_height() - 2, -1, 48, "run_account_orders" );
	cons.c_refresh ( );
	return ( 0 );
	M_EPILOG
}

int HBookerProcess::run_regular_oblige( void* ) {
	M_PROLOG
	HConsole& cons = HConsole::get_instance();
	cons.c_cmvprintf ( cons.get_height() - 2, -1, 48, "run_regular_oblige" );
	cons.c_refresh ( );
	return ( 0 );
	M_EPILOG
}

}

