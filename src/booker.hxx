/*
---       `booker' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski         ---

	booker.hxx - this file is integral part of `booker' project.

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

#ifndef PROCESS_HXX_INCLUDED
#define PROCESS_HXX_INCLUDED

namespace booker
{

class HBookerProcess : public yaal::hdata::HDataProcess
	{
protected:
	/*{*/
	/*}*/
public:
	/*{*/
	HBookerProcess( void );
	virtual ~HBookerProcess( void );
	int init( const char* = "" );
	int run_quit( void* );
	int run_dictionary_contracting_party( void* );
	int run_config( void* );
	int run_subject( void* );
	int run_account_map( void* );
	int run_account_orders( void* );
	int run_regular_oblige( void* );
	/*}*/
private:
	/*{*/
	HBookerProcess ( const HBookerProcess & );
	HBookerProcess & operator = ( const HBookerProcess & );
	/*}*/
	};

extern HBookerProcess theProc;

}

#endif /* PROCESS_HXX_INCLUDED */
