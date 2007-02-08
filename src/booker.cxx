/*
---        `booker' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski         ---

	booker.cxx - this file is integral part of `booker' project.

	i.  You may not make any changes in Copyright information.
	ii. You must attach Copyright information to any part of every copy
	    of this software.

Copyright:

 You are free to use this program as is, you can redistribute binary
 package freely but:
  1. You can not use any part of sources of this software.
  2. You can not redistribute any part of sources of this software.
  3. No reverse engineering is allowed.
  4. If you want redistribute binary package you can not demand any fees
     for this software.
     You can not even demand cost of the carrier (CD for example).
  5. You can not include it to any commercial enterprise (for example 
     as a free add-on to payed software or payed newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/


#include <yaal/yaal.h>
M_VCSID ( "$Id$" )

#include "booker.h"
#include "setup.h"

/* windows begin */
#include "dictionarybank.h"
#include "dictionarycontractingpartywindow.h"
/* windows end */

using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::dbwrapper;
using namespace yaal::hdata;

#define D_MENU_HANDLERS_MAP_SIZE 32

HBookerProcess::HBookerProcess ( void )
	:	HDataProcess ( ), f_poDataBase ( NULL )
	{
	M_PROLOG
/*
	f_poDataBase = new HDataBase ( );
*/
	return;
	M_EPILOG
	}

HBookerProcess::~HBookerProcess ( void )
	{
	M_PROLOG
	if ( f_poDataBase )delete f_poDataBase;
	f_poDataBase = NULL;
	return;
	M_EPILOG
	}

int HBookerProcess::init ( const char * a_pcProcessName )
	{
	M_PROLOG
	f_oDataBase.login ( setup.f_oDataBase, setup.f_oLogin, setup.f_oPassword );
	menu_handlers_map_t l_oHandlers ( D_MENU_HANDLERS_MAP_SIZE );
	M_REGISTER_MENU_HANDLER ( run_quit );
	M_REGISTER_MENU_HANDLER ( run_account_orders );
	M_REGISTER_MENU_HANDLER ( run_account_map );
	l_oHandlers [ "" ] = NULL;
	M_REGISTER_MENU_HANDLER ( run_dictionary_bank );
	M_REGISTER_MENU_HANDLER ( run_dictionary_contracting_party );
	M_REGISTER_MENU_HANDLER ( run_regular_oblige );
	M_REGISTER_MENU_HANDLER ( run_subject );
	M_REGISTER_MENU_HANDLER ( run_config );
	HDataProcess::init_xrc ( a_pcProcessName, "booker.xrc", l_oHandlers );
	return ( 0 );
	M_EPILOG
	}

int HBookerProcess::run_quit ( void )
	{
	M_PROLOG
	handler_quit ( KEY < 'x' >::command );
	return ( 0 );
	M_EPILOG
	}

int HBookerProcess::run_dictionary_bank ( void )
	{
	M_PROLOG
	add_window ( HWindow::ptr_t( new HDictionaryBank (
					"Banki", theProc.data_base ( ),
					g_psDictionaryBankResources ) ) );
	return ( 0 );
	M_EPILOG
	}

int HBookerProcess::run_dictionary_contracting_party ( void )
	{
	M_PROLOG
	add_window ( HWindow::ptr_t ( new HDictionaryContractingPartyWindow (
					"Kontrahenci" ) ) );
	return ( 0 );
	M_EPILOG
	}

int HBookerProcess::run_config ( void )
	{
	M_PROLOG
	int i;
	c_printf ( n_iHeight - 2, -1, 48, "run_config" );
	for ( i = 0; i < 8; i++ )
		{
	add_window ( HWindow::ptr_t ( new HDictionaryBank (
					"Banki", theProc.data_base ( ),
					g_psDictionaryBankResources ) ) );
		}
	c_refresh ( );
	return ( 0 );
	M_EPILOG
	}

int HBookerProcess::run_subject ( void )
	{
	M_PROLOG
	c_printf ( n_iHeight - 2, -1, 48, "run_subject" );
	c_refresh ( );
	return ( 0 );
	M_EPILOG
	}

int HBookerProcess::run_account_map ( void )
	{
	M_PROLOG
	c_printf ( n_iHeight - 2, -1, 48, "run_account_map" );
	c_refresh ( );
	return ( 0 );
	M_EPILOG
	}

int HBookerProcess::run_account_orders ( void )
	{
	M_PROLOG
	c_printf ( n_iHeight - 2, -1, 48, "run_account_orders" );
	c_refresh ( );
	return ( 0 );
	M_EPILOG
	}

int HBookerProcess::run_regular_oblige ( void )
	{
	M_PROLOG
	c_printf ( n_iHeight - 2, -1, 48, "run_regular_oblige" );
	c_refresh ( );
	return ( 0 );
	M_EPILOG
	}
