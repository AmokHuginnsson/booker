/* Read booker/LICENSE.md file for copyright and licensing information. */

#ifndef SETUP_HXX_INCLUDED
#define SETUP_HXX_INCLUDED

#include <libintl.h>

#include "config.hxx"
#include <yaal/hcore/hstring.hxx>

namespace booker {

struct OSetup {
	bool _quiet;			/* --quiet, --silent */
	bool _verbose;		/* --verbose */
	bool _test;
	char * _programName;
	yaal::hcore::HString _logPath;
	yaal::hcore::HString _resource;
	/* self-sufficient */
	OSetup( void )
		: _quiet( false )
		, _verbose( false )
		, _test( false )
		, _programName( nullptr )
		, _logPath()
		, _resource() {
		return;
	}
	void test_setup( void );
private:
	OSetup ( OSetup const& );
	OSetup& operator = ( OSetup const& );
};

extern OSetup setup;

}

#endif /* SETUP_HXX_INCLUDED */
