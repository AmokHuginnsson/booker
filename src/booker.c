/*
---        `booker' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski         ---

	booker.c - this file is integral part of `booker' project.

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

#include "../config.h"

#ifdef HAVE_NCURSES_H
#	include <ncurses.h>
#elif defined ( HAVE_NCURSES_NCURSES_H )
#	include <ncurses/ncurses.h>
#else /* HAVE_NCURSES_NCURSES_H */
#	error "No ncurses header available."
#endif /* not HAVE_NCURSES_NCURSES_H */

#include "booker.h"
#include "variables.h"

/* windows begin */
#include "dictionarybank.h"
#include "dictionarycontractingpartywindow.h"
/* windows end */

#define CIP (int (HProcess::*)(void))

OMenuItem g_psInspectionSubSubMenu [ ] =
	{
		{ 0, CIP & HBookerProcess::run_account_orders, "Analityka" },
		{ 0, CIP & HBookerProcess::run_account_map, "Bilans" },
		{ 0, CIP & HBookerProcess::run_account_map, "Salda" },
		{ 0, CIP & HBookerProcess::run_account_map, "Zestawienia" },
		{ 0, 0, 0 }
	};

OMenuItem g_psDictionarySubMenu [ ] =
	{
		{ 0, CIP & HBookerProcess::run_dictionary_bank, "Banki" },
		{ 0, CIP & HBookerProcess::run_dictionary_contracting_party,"Kontrahenci" },
		{ 0, CIP & HBookerProcess::run_regular_oblige, "Zobowi±zania sta³e" },
		{ 0, 0, 0 }
	};

OMenuItem g_psAccountingSubMenu [ ] =
	{
		{ 0, CIP & HBookerProcess::run_account_orders, "Polecenia ksiêgowania" },
		{ 0, CIP & HBookerProcess::run_account_map, "Plan Kont" },
		{ g_psInspectionSubSubMenu, 0, "Przegl±danie" },
		{ 0, 0, 0 }
	};

OMenuItem g_psSystemSubMenu [ ] =
	{
		{ 0, CIP & HBookerProcess::run_subject, "Podmiot" },
		{ 0, CIP & HBookerProcess::run_config, "Konfiguracja" },
		{ 0, 0, 0 }
	};
	 
OMenuItem g_psMainMenu [ ] =
	{
		{ g_psAccountingSubMenu, 0, "Ksiêgowo¶æ" }, 
		{ g_psDictionarySubMenu, 0, "S³owniki" }, 
		{ g_psSystemSubMenu, 0, "System" }, 
		{ 0, CIP & HBookerProcess::run_quit, "Koniec pracy" }, 
		{ 0, 0, 0 }
	};

HBookerProcess::HBookerProcess ( void ) :	HDataProcess ( )
	{
	M_PROLOG
	f_poDataBase = NULL;
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
	f_oDataBase.login ( g_pcDataBase, g_pcLogin, g_pcPassword );
	HDataProcess::init ( a_pcProcessName );
	( ( HMainWindow * ) f_poForegroundWindow )->init_menu ( this, g_psMainMenu );
	return ( 0 );
	M_EPILOG
	}

int HBookerProcess::run_quit ( void )
	{
	M_PROLOG
	handler_quit ( D_KEY_COMMAND_('x') );
	return ( 0 );
	M_EPILOG
	}

int HBookerProcess::run_dictionary_bank ( void )
	{
	M_PROLOG
	add_window ( new HDictionaryBank (
				g_psDictionarySubMenu [ 0 ].f_pcLabel, theProc.data_base ( ),
				g_psDictionaryBankResources ),
			g_psDictionarySubMenu [ 0 ].f_pcLabel );
	return ( 0 );
	M_EPILOG
	}

int HBookerProcess::run_dictionary_contracting_party ( void )
	{
	M_PROLOG
	add_window ( new HDictionaryContractingPartyWindow (
				g_psDictionarySubMenu [ 1 ].f_pcLabel ),
			g_psDictionarySubMenu [ 1 ].f_pcLabel );
	return ( 0 );
	M_EPILOG
	}

int HBookerProcess::run_config ( void )
	{
	M_PROLOG
	int i;
	console::c_printf ( console::n_iHeight - 2, -1, 48, "run_config" );
	for ( i = 0; i < 8; i++ )
		{
	add_window ( new HDictionaryBank (
				g_psDictionarySubMenu [ 0 ].f_pcLabel, theProc.data_base ( ),
				g_psDictionaryBankResources ),
			g_psDictionarySubMenu [ 0 ].f_pcLabel );
		}
	refresh ( );
	return ( 0 );
	M_EPILOG
	}

int HBookerProcess::run_subject ( void )
	{
	M_PROLOG
	console::c_printf ( console::n_iHeight - 2, -1, 48, "run_subject" );
	refresh ( );
	return ( 0 );
	M_EPILOG
	}

int HBookerProcess::run_account_map ( void )
	{
	M_PROLOG
	console::c_printf ( console::n_iHeight - 2, -1, 48, "run_account_map" );
	refresh ( );
	return ( 0 );
	M_EPILOG
	}

int HBookerProcess::run_account_orders ( void )
	{
	M_PROLOG
	console::c_printf ( console::n_iHeight - 2, -1, 48, "run_account_orders" );
	refresh ( );
	return ( 0 );
	M_EPILOG
	}

int HBookerProcess::run_regular_oblige ( void )
	{
	M_PROLOG
	console::c_printf ( console::n_iHeight - 2, -1, 48, "run_regular_oblige" );
	refresh ( );
	return ( 0 );
	M_EPILOG
	}

