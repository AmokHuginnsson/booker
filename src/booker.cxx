/* Read booker/LICENSE.md file for copyright and licensing information. */


#include "booker.hxx"
M_VCSID( "$Id: " __ID__ " $" )

#include "setup.hxx"

/* windows begin */
#include "dictionarybank.hxx"
#include "testwindow.hxx"
/* windows end */

using namespace yaal::hcore;
using namespace yaal::tools;
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
	HDataProcess::init_xrc_db( processName_, setup._resource, setup._dsn );
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
	cons.cmvprintf( cons.get_height() - 2, -1, COLOR::FG_BRIGHTRED, "run_config" );
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
	cons.cmvprintf ( cons.get_height() - 2, -1, COLOR::FG_BRIGHTRED, "run_subject" );
	cons.refresh ( );
	return ( true );
	M_EPILOG
}

bool HBookerProcess::run_account_map( yaal::hconsole::HEvent const& ) {
	M_PROLOG
	HConsole& cons = HConsole::get_instance();
	cons.cmvprintf ( cons.get_height() - 2, -1, COLOR::FG_BRIGHTRED, "run_account_map" );
	cons.refresh ( );
	return ( true );
	M_EPILOG
}

bool HBookerProcess::run_account_orders( yaal::hconsole::HEvent const& ) {
	M_PROLOG
	HConsole& cons = HConsole::get_instance();
	cons.cmvprintf ( cons.get_height() - 2, -1, COLOR::FG_BRIGHTRED, "run_account_orders" );
	cons.refresh ( );
	return ( true );
	M_EPILOG
}

bool HBookerProcess::run_regular_oblige( yaal::hconsole::HEvent const& ) {
	M_PROLOG
	HConsole& cons = HConsole::get_instance();
	cons.cmvprintf ( cons.get_height() - 2, -1, COLOR::FG_BRIGHTRED, "run_regular_oblige" );
	cons.refresh ( );
	return ( true );
	M_EPILOG
}

}

