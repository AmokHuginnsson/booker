/*
---       `booker' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski         ---

	booker.hxx - this file is integral part of `booker' project.

  i.  You may not make any changes in Copyright information.
  ii. You must attach Copyright information to any part of every copy
      of this software.

Copyright:

 You can use this software free of charge and you can redistribute its binary
 package freely but:
  1. You are not allowed to use any part of sources of this software.
  2. You are not allowed to redistribute any part of sources of this software.
  3. You are not allowed to reverse engineer this software.
  4. If you want to distribute a binary package of this software you cannot
     demand any fees for it. You cannot even demand
     a return of cost of the media or distribution (CD for example).
  5. You cannot involve this software in any commercial activity (for example
     as a free add-on to paid software or newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

#ifndef PROCESS_HXX_INCLUDED
#define PROCESS_HXX_INCLUDED

#include <yaal/hdata/hdataprocess.hxx>

namespace booker {

class HBookerProcess : public yaal::hdata::HDataProcess {
public:
	typedef HBookerProcess this_type;
	HBookerProcess( void );
	virtual ~HBookerProcess( void );
	int init( const char* = "" );
	bool run_quit( yaal::hconsole::HEvent const& );
	bool run_dictionary_contracting_party( yaal::hconsole::HEvent const& );
	bool run_config( yaal::hconsole::HEvent const& );
	bool run_test( yaal::hconsole::HEvent const& );
	bool run_subject( yaal::hconsole::HEvent const& );
	bool run_account_map( yaal::hconsole::HEvent const& );
	bool run_account_orders( yaal::hconsole::HEvent const& );
	bool run_regular_oblige( yaal::hconsole::HEvent const& );
private:
	HBookerProcess ( const HBookerProcess & );
	HBookerProcess & operator = ( const HBookerProcess & );
};

extern HBookerProcess theProc;

}

#endif /* PROCESS_HXX_INCLUDED */
