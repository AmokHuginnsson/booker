/*
---           booker 0.0.0 (c) 1978 by Marcin 'Amok' Konarski            ---

	dictionarybankwindow.cxx - this file is integral part of booker project.

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

#include <libintl.h>
#include <yaal/yaal.hxx> /* all hAPI headers */
M_VCSID( "$Id: "__ID__" $" )

#include "booker.hxx"
#include "dictionarybank.hxx"

using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::hconsole::list_control_helper;
using namespace yaal::tools;
using namespace yaal::dbwrapper;
using namespace yaal::hdata;

namespace booker
{

HDictionaryBank::HDictionaryBank( const char* a_pcTitle,
		HDataProcess* a_poOwner, OResource* a_psResources )
								: HDataWindow( a_pcTitle, a_poOwner, a_psResources )
	{
	M_PROLOG
  register_postprocess_handler ( 'a', NULL,
			& HDictionaryBank::handler_add );
	return;
	M_EPILOG
	}

HDictionaryBank::~HDictionaryBank ( void )
	{
	M_PROLOG
	return;
	M_EPILOG
	}

int HDictionaryBank::handler_add ( int a_iCode, void const* )
	{
	M_PROLOG
	double l_dValue = 0;
	HExpression l_oAnalyser;
	HItem l_oItem ( 6 );
	HRandomizer l_oRnd ( 0 );
	HDataListControl * l_poList = dynamic_cast<HDataListControl*>( f_oControls.get_control_by_no( 1 ) );
	M_ASSERT( l_poList != NULL );
	l_oAnalyser.compile( "A+B" );
	int long const D_TO_ADD = 500000;
	f_oStatusBar->init_progress ( D_TO_ADD, _( " Precaching ... " ) );
	HListControler<>::ptr_t l_oControler = l_poList->get_controler();
	for ( int long l_iCtr = 0; l_iCtr < D_TO_ADD; l_iCtr ++ )
		{
/*		l_dValue = l_poList->size ( ) / 100.;*/
		l_dValue = ( ( double ) l_oRnd.rnd ( ) ) / 100.;
/*		
		l_oAnalyser [ 'A' ] = l_dValue;
		l_oAnalyser [ 'B' ] = l_dValue * l_dValue;
		l_dValue = l_oAnalyser.evaluate ( );
*/
		l_oItem [ 0 ] = util::kwota_slownie ( l_dValue );
		l_oItem [ 1 ] = "wypełniacz";
/*		l_oIitem [ 2 ] = HString ( l_dValue );*/
		l_oItem [ 2 ] = l_dValue;
		l_oControler->add_tail ( l_oItem );
		f_oStatusBar->update_progress();
		}
/*
 * tested list control by filling it with 276300 rows
 */
	refresh ( );
	a_iCode = 0;
	return ( a_iCode );
	M_EPILOG
	}

}

extern "C"
HWindow::ptr_t window_bank( HString const& title, HDataProcess* proc, OResource* res )
	{
	M_PROLOG
	return ( HWindow::ptr_t( new booker::HDictionaryBank( title.raw(), proc, res ) ) );
	M_EPILOG
	}

