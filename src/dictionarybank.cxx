/*
---           booker.h 0.0.0 (c) 1978 by Marcin 'Amok' Konarski            ---

	dictionarybankwindow.cxx - this file is integral part of booker.h project.

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

#include <libintl.h>
#include <yaal/yaal.h> /* all hAPI headers */
M_VCSID ( "$Id$" )

#include "booker.h"
#include "dictionarybank.h"

using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::dbwrapper;
using namespace yaal::hdata;

OEditControlResource g_psDictionaryBankEditControls [ ] =
	{
		{ 160, "", "^[a-zA-Z�����ʳ����Ӷ����� \\.-]*$", false, false, false, false, false, 8 },
		{ 32, "", "^[a-zA-Z�����ʳ����Ӷ����� ]*$", false, false, false, false, false, 8 },
		{ 48, "", "^[0-9a-zA-Z�����ʳ����Ӷ����� \\.-]*$", false, false, false, false, false, 8 },
		{ 8, "", "^[0-9 -]*$", false, false, false, false, false, 8 },
		{ 6, "", "^[0-9a-zA-Z]*$", false, false, false, false, false, 8 },
		{ 17, "", "^[0-9 ()-]*$", false, false, false, false, false, 8 },
		{	0, NULL, NULL, false, false, false, false, false, 0	}
	};

OListControlResource g_psDictionaryBankListControls [ ] =
	{
		{ true, true, true, true, true },
		{ false, false, false, false, false	}
	};

OColumnInfo g_psDictionaryBankColumnInfos [ ] =
	{
		{	-1, "nazwa", 4, HControl::BITS::ALIGN::D_LEFT, D_HSTRING },
		{ -1, "miasto", 2, HControl::BITS::ALIGN::D_LEFT, D_HSTRING },
		{ -1, "ulica", 3, HControl::BITS::ALIGN::D_LEFT, D_HSTRING },
		{ -1, "kod", 1, HControl::BITS::ALIGN::D_LEFT, D_HSTRING },
		{ -1, "", 0, HControl::BITS::ALIGN::D_LEFT, D_HSTRING },
		{ -1, "", 0, HControl::BITS::ALIGN::D_LEFT, D_HSTRING },
		{	0, NULL, 0, HControl::BITS::ALIGN::D_LEFT, D_VOID }
	};

OResource x_tag_g_psDictionaryBankResources [ ] =
	{
		{
		"dictionary_bank",
		"name, city, street, postal_code, street_number, phone, id",
		"", "name ASC", 1, 1, -8, -1, " &Banki \n",
		NULL, DATACONTROL_BITS::ROLE::D_MAIN, DATACONTROL_BITS::TYPE::D_LIST,
		& g_psDictionaryBankListControls [ 0 ],	NULL, 0
		},
		{
		NULL, NULL, NULL, NULL, -7, 1, 1, -25, " &Nazwa: \n", NULL,
		DATACONTROL_BITS::ROLE::D_DATA, DATACONTROL_BITS::TYPE::D_EDIT,
		& g_psDictionaryBankEditControls [ 0 ],
		& g_psDictionaryBankColumnInfos [ 0 ], 0
		},
		{
		NULL, NULL, NULL, NULL, - 7, - 24, 1, 23, " &Miasto: \n", NULL,
		DATACONTROL_BITS::ROLE::D_DATA, DATACONTROL_BITS::TYPE::D_EDIT,
		& g_psDictionaryBankEditControls [ 1 ],
		& g_psDictionaryBankColumnInfos [ 1 ], 0
		},
		{
		NULL, NULL, NULL, NULL, - 4, 1, 1, - 33, " &Ulica: \n", NULL,
		DATACONTROL_BITS::ROLE::D_DATA, DATACONTROL_BITS::TYPE::D_EDIT,
		& g_psDictionaryBankEditControls [ 2 ],
		& g_psDictionaryBankColumnInfos [ 2 ], 0
		},
		{
		NULL, NULL, NULL, NULL, - 4, - 32, 1, 7, " &Kod: \n", NULL,
		DATACONTROL_BITS::ROLE::D_DATA, DATACONTROL_BITS::TYPE::D_EDIT,
		& g_psDictionaryBankEditControls [ 3 ],
		& g_psDictionaryBankColumnInfos [ 3 ], 0
		},
		{
		NULL, NULL, NULL, NULL, - 4, - 24, 1, 5, " &Numer: \n", NULL,
		DATACONTROL_BITS::ROLE::D_DATA, DATACONTROL_BITS::TYPE::D_EDIT,
		& g_psDictionaryBankEditControls [ 4 ],
		& g_psDictionaryBankColumnInfos [ 4 ], 0
		},
		{
		NULL, NULL, NULL, NULL, - 4, - 15, 1, 14, " &Telefon: \n", NULL,
		DATACONTROL_BITS::ROLE::D_DATA, DATACONTROL_BITS::TYPE::D_EDIT,
		& g_psDictionaryBankEditControls [ 5 ],
		& g_psDictionaryBankColumnInfos [ 5 ], 0
		},
		{
/*	tabl, colu, wher, orde, r, c, h, w, labe, attr, f, t, spec, coli, parent */
		NULL, NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL,
		DATACONTROL_BITS::ROLE::D_INVALID, DATACONTROL_BITS::TYPE::D_INVALID,
		NULL, NULL, 0
		}
	}, * g_psDictionaryBankResources = x_tag_g_psDictionaryBankResources;

HDictionaryBank::HDictionaryBank ( const char * a_pcTitle,
		HDataBase * a_poDataBase, OResource * a_psResources )
								: HDataWindow ( a_pcTitle, a_poDataBase, a_psResources )
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

int HDictionaryBank::handler_add ( int a_iCode, void * )
	{
	M_PROLOG
	int l_iCtr = 0;
	double l_dValue = 0;
	HAnalyser l_oAnalyser;
	HItem l_oItem ( 6 );
	HRandomizer l_oRnd ( 0 );
	HDataListControl * l_poList = reinterpret_cast < HDataListControl * > ( f_oControls.get_control_by_no( 0 ) );
	l_oAnalyser.analyse ( "A+B" );
	f_oStatusBar->init_progress ( 10000, _( " Precaching ... " ) );
	for ( l_iCtr = 0; l_iCtr < 10000; l_iCtr ++ )
		{
/*		l_dValue = l_poList->size ( ) / 100.;*/
		l_dValue = ( ( double ) l_oRnd.rnd ( ) ) / 100.;
/*		
		l_oAnalyser [ 'A' ] = l_dValue;
		l_oAnalyser [ 'B' ] = l_dValue * l_dValue;
		l_dValue = l_oAnalyser.count ( );
*/
		l_oItem [ 0 ] = util::kwota_slownie ( l_dValue );
		l_oItem [ 1 ] = "wype�niacz";
/*		l_oIitem [ 2 ] = HString ( l_dValue );*/
		l_oItem [ 2 ] = l_dValue;
		l_poList->add_tail ( l_oItem );
		f_oStatusBar->update_progress ( l_iCtr );
		}
/*
 * tested list control by filling it with 276300 rows
 */
	refresh ( );
	a_iCode = 0;
	return ( a_iCode );
	M_EPILOG
	}
