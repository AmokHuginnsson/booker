/* Read booker/LICENSE.md file for copyright and licensing information. */

#include <cstdlib>
#include <libintl.h>

#include <yaal/hcore/hlog.hxx>
#include <yaal/tools/hthreadpool.hxx>
#include <yaal/tools/signals.hxx>
#include <yaal/tools/util.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "booker.hxx"
#include "setup.hxx"
#include "options.hxx"

using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace booker;

namespace booker {

OSetup setup;
HBookerProcess theProc;

}

int main( int argc_, char **argv_ ) {
	HScopeExitCall secTP( call( &HThreadPool::stop, &HThreadPool::get_instance() ) );
	HScopeExitCall sec( call( &HSignalService::stop, &HSignalService::get_instance() ) );
	M_PROLOG
	try {
		HSignalService::get_instance();
/*	TO-DO:				                    enter main loop code here */
		setup._programName = argv_ [ 0 ];
		handle_program_options( argc_, argv_ );
		hcore::log.rehash( setup._logPath, setup._programName );
		setup.test_setup();
/* enabling ncurses ablilities  */
		if ( ! HConsole::get_instance().is_enabled() )
			HConsole::get_instance().enter_curses();
		theProc.init( setup._programName );
		theProc.run();
/* ending ncurses sesion        */
		if ( HConsole::get_instance().is_enabled() )
			HConsole::get_instance().leave_curses();
/*	... there is the place main loop ends.               :OD-OT */
	} catch ( ... ) {
/* ending ncurses sesion        */
		if ( HConsole::get_instance().is_enabled() )
			HConsole::get_instance().leave_curses();
		throw;
	}
	cerr << _( "Done" ) << endl;
	return ( 0 );
	M_FINAL
}

