/* Read booker/LICENSE.md file for copyright and licensing information. */

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
