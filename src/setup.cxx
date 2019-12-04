/* Read booker/LICENSE.md file for copyright and licensing information. */

#include "setup.hxx"
M_VCSID( "$Id: " __ID__ " $" )
#include <yaal/hcore/hfile.hxx>
#include <yaal/tools/util.hxx>

using namespace yaal::hcore;

namespace booker {

void OSetup::test_setup( void ) {
	M_PROLOG
	if ( _quiet && _verbose ) {
		yaal::tools::util::failure( 1,
				_( "quiet and verbose options are exclusive\n" ) );
	}
	if ( _verbose ) {
		clog.reset_owned( make_pointer<HFile>( stdout, HFile::OWNERSHIP::EXTERNAL ) );
	}
	if ( _quiet ) {
		cout.reset();
	}
	if ( ! _logPath ) {
		M_THROW( _( "log file name not set" ), errno );
	}
	if ( ! _resource ) {
		M_THROW( _( "resource name not set" ), errno );
	}
	return;
	M_EPILOG
}

}

