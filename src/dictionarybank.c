/*
---           booker.h 0.0.0 (c) 1978 by Marcin 'Amok' Konarski            ---

	dictionarybankwindow.c - this file is integral part of booker.h project.

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

#include <stdhapi.h> /* all hAPI headers */
#include "dictionarybankwindow.h"

#include "booker.h"
#include "dictionarybankset.h"

OEditControlResource g_psDictionaryBankEditControls [ ] =
	{
		{ 160, "", "^[a-zA-Z�����ʳ����Ӷ����� \\.-]*$", false, false, false, 8 },
		{ 32, "", "^[a-zA-Z�����ʳ����Ӷ����� ]*$", false, false, false, 8 },
		{ 48, "", "^[0-9a-zA-Z�����ʳ����Ӷ����� \\.-]*$", false, false, false, 8 },
		{ 8, "", "^[0-9 -]*$", false, false, false, 8 },
		{ 6, "", "^[0-9a-zA-Z]*$", false, false, false, 8 },
		{ 17, "", "^[0-9 ()-]*$", false, false, false, 8 },
		{	0, NULL, NULL, false, false, false, 0	}
	};

OColumnInfo g_psDictionaryBankColumnInfos [ ] =
	{
		{	-1, "nazwa", 3, D_ALIGN_LEFT, D_TYPE_HSTRING },
		{ -1, "miasto", 1, D_ALIGN_LEFT, D_TYPE_HSTRING },
		{ -1, "ulica", 2, D_ALIGN_LEFT, D_TYPE_HSTRING },
		{ -1, "", 0, D_ALIGN_LEFT, D_TYPE_HSTRING },
		{ -1, "", 0, D_ALIGN_LEFT, D_TYPE_HSTRING },
		{ -1, "", 0, D_ALIGN_LEFT, D_TYPE_HSTRING },
		{	0, NULL, 0, 0, 0 }
	};

OResource x_tag_g_psDictionaryBankResources [ ] =
	{
		{
		"dicionary_bank", "*", "", "name ASC", 1, 1, -8, -1, " &Banki \n",
		NULL, D_CONTROL_MAIN, D_CONTROL_LIST, NULL, NULL, 0, NULL
		},
		{
		NULL, NULL, NULL, NULL, -7, 1, -25, 1, " &Nazwa: \n", NULL,
		D_CONTROL_DATA, D_CONTROL_EDIT,
		& g_psDictionaryBankEditControls [ 0 ],
		& g_psDictionaryBankColumnInfos [ 0 ], 0, NULL
		},
		{
		NULL, NULL, NULL, NULL, - 7, - 24, 23, 1, " &Miasto: \n", NULL,
		D_CONTROL_DATA, D_CONTROL_EDIT,
		& g_psDictionaryBankEditControls [ 1 ],
		& g_psDictionaryBankColumnInfos [ 1 ], 0, NULL
		},
		{
		NULL, NULL, NULL, NULL, - 4, 1, - 33, 1, " &Ulica: \n", NULL,
		D_CONTROL_DATA, D_CONTROL_EDIT,
		& g_psDictionaryBankEditControls [ 2 ],
		& g_psDictionaryBankColumnInfos [ 2 ], 0, NULL
		},
		{
		NULL, NULL, NULL, NULL, - 4, - 32, 7, 1, " &Kod: \n", NULL,
		D_CONTROL_DATA, D_CONTROL_EDIT,
		& g_psDictionaryBankEditControls [ 3 ],
		& g_psDictionaryBankColumnInfos [ 3 ], 0, NULL
		},
		{
		NULL, NULL, NULL, NULL, - 4, - 24, 5, 1, " &Numer: \n", NULL,
		D_CONTROL_DATA, D_CONTROL_EDIT,
		& g_psDictionaryBankEditControls [ 4 ],
		& g_psDictionaryBankColumnInfos [ 4 ], 0, NULL
		},
		{
		NULL, NULL, NULL, NULL, - 4, - 15, 14, 1, " &Telefon: \n", NULL,
		D_CONTROL_DATA, D_CONTROL_EDIT,
		& g_psDictionaryBankEditControls [ 5 ],
		& g_psDictionaryBankColumnInfos [ 5 ], 0, NULL
		},
		{
		NULL, NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, 0, 0, NULL, NULL, 0, NULL
		}
	}, * g_psDictionaryBankResources = x_tag_g_psDictionaryBankResources;

HDictionatyBankWindow::HDictionatyBankWindow ( const char * a_pcTitle,
		HDataBase * a_poDataBase, OResource * a_psResources )
								: HDataWindow ( a_pcTitle, a_poDataBase, a_psResources )
	{
	M_PROLOG
  register_postprocess_handler ( 'a', 
			( int ( HWindow::* ) ( int ) ) & HDictionatyBankWindow::handler_add );
	return;
	M_EPILOG
	}

HDictionatyBankWindow::~HDictionatyBankWindow ( void )
	{
	M_PROLOG
	return;
	M_EPILOG
	}

int HDictionatyBankWindow::init ( void )
	{
	M_PROLOG
	int l_iError = 0;
	HDataListControl * l_poList = NULL;
	HDictionaryBankSet rs ( theProc.data_base ( ) );
	l_iError = HDataWindow::init ( );
	l_poList = ( HDataListControl * ) f_poMainControl;
	rs.open ( );
	while ( ! rs.is_eof ( ) )
		{
		l_poList->add_tail ( );
		l_poList->tail ( ) [ 0 ] = rs.m_nazwa;
		l_poList->tail ( ) [ 1 ] = rs.m_miasto;
		l_poList->tail ( ) [ 2 ] = rs.m_ulica;
		l_poList->tail ( ) [ 3 ] = rs.m_kod_pocztowy;
		l_poList->tail ( ) [ 4 ] = rs.m_numer_ulicy;
		l_poList->tail ( ) [ 5 ] = rs.m_telefon;
		rs.move_next ( );
		}
	rs.close ( );
	l_poList->enable ( true );
	l_poList->set_focus ( );
	refresh ( );
	return ( l_iError );
	M_EPILOG
	}

int HDictionatyBankWindow::handler_add ( int a_iCode )
	{
	M_PROLOG
	int l_iCtr = 0;
	double l_dValue = 0;
	HAnalyser l_oAnalyser;
	HInfoList * l_poInfoList = NULL;
	l_oAnalyser.analyse ( "A+B" );
	for ( l_iCtr = 0; l_iCtr < 10000; l_iCtr ++ )
		{
		l_dValue = f_poList->quantity ( ) / 100.;
/*		
		l_oAnalyser [ 'A' ] = l_dValue;
		l_oAnalyser [ 'B' ] = l_dValue * l_dValue;
		l_dValue = l_oAnalyser.count ( );
*/
		l_poInfoList = & f_poList->add_tail ( );
		( * l_poInfoList ) [ 0 ] = util::kwota_slownie ( l_dValue );
		( * l_poInfoList ) [ 1 ] = "wype�niacz";
		( * l_poInfoList ) [ 2 ] = HString ( l_dValue );
		}
/*
 * tested list control by filling it with 276300 rows
 */
	refresh ( );
	a_iCode = 0;
	return ( a_iCode );
	M_EPILOG
	}
