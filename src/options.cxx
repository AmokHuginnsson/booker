/*
---       `booker' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski         ---

	rc_options.cxx - this file is integral part of `booker' project.

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

#include <cstdlib>
#include <cstring>
#include <cstdio>

#include <yaal/yaal.hxx>
M_VCSID( "$Id: "__ID__" $" )

#include "options.hxx"
#include "version.hxx"
#include "setup.hxx"

using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::util;

namespace booker
{

bool set_variables( HString& a_roOption, HString& a_roValue )
	{
	::fprintf( stdout, "option: [%s], value: [%s]\n",
			a_roOption.raw(), a_roValue.raw() );
	return ( false );
	}

/* Set all the option flags according to the switches specified.
   Return the index of the first non-option argument.                    */

void usage( void* ) __attribute__((__noreturn__));
void usage( void* arg )
	{
	OOptionInfo* info = static_cast<OOptionInfo*>( arg );
	info->PROC( info->_opt, info->_size, setup.f_pcProgramName, "fiscal accounting software", NULL );
	throw ( setup.f_bHelp ? 0 : 1 );
	}

void version( void* ) __attribute__ ( ( __noreturn__ ) );
void version( void* )
	{
	printf ( "`booker' %s\n", VER );
	throw ( 0 );
	}

namespace
{

simple_callback_t help( usage, NULL );
simple_callback_t dump( usage, NULL );
simple_callback_t version_call( version, NULL );
OOption n_psOptions[] =
	{
		{ "log_path", TYPE::D_HSTRING, &setup.f_oLogPath, NULL, OOption::D_REQUIRED, "path", "path pointing to file for application logs", NULL },
		{ "database", TYPE::D_HSTRING, &setup.f_oDataBase, NULL, OOption::D_REQUIRED, "spec", "database specyfication", NULL },
		{ "login", TYPE::D_HSTRING, &setup.f_oLogin, NULL, OOption::D_REQUIRED, "login", "login for database", NULL },
		{ "password", TYPE::D_HSTRING, &setup.f_oPassword, NULL, OOption::D_REQUIRED, "pass", "password for database", NULL },
		{ "quiet", TYPE::D_BOOL, &setup.f_bQuiet, "q", OOption::D_NONE, NULL, "inhibit usual output", NULL },
		{ "silent", TYPE::D_BOOL, &setup.f_bQuiet, "q", OOption::D_NONE, NULL, "inhibit usual output", NULL },
		{ "verbose", TYPE::D_BOOL, &setup.f_bVerbose, "v", OOption::D_NONE, NULL, "print more information", NULL },
		{ "help", TYPE::D_BOOL, &setup.f_bHelp, "h", OOption::D_NONE, NULL, "display this help and exit", &help },
		{ "dump-configuration", TYPE::D_VOID, NULL, "W", OOption::D_NONE, NULL, "dump current configuration", &dump },
		{ "version", TYPE::D_VOID, NULL, "V", OOption::D_NONE, NULL, "output version information and exit", &version_call },
		{ NULL, TYPE::D_VOID, NULL, NULL, OOption::D_NONE, NULL, NULL, NULL }
	};

}

int process_bookerrc_file( void )
	{
	rc_file::process_rc_file( "booker", HString(), n_psOptions, NULL );
	if ( ! setup.f_oLogPath )
		setup.f_oLogPath = "booker.log";
	return ( 0 );
	}

int decode_switches ( int a_iArgc, char ** a_ppcArgv )
	{
	M_PROLOG
	int l_iUnknown = 0, l_iNonOption = 0;
	OOptionInfo info( n_psOptions, sizeof ( n_psOptions ) / sizeof ( OOption ), util::show_help );
	OOptionInfo infoConf( n_psOptions, sizeof ( n_psOptions ) / sizeof ( OOption ), util::dump_configuration );
	help.second = &info;
	dump.second = &infoConf;
	l_iNonOption = cl_switch::decode_switches( a_iArgc, a_ppcArgv, n_psOptions,
			info._size, &l_iUnknown );
	if ( l_iUnknown > 0 )
		usage( &info );
	return ( l_iNonOption );
	M_EPILOG
	}

}

