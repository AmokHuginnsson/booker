/*
---           booker 0.0.0 (c) 1978 by Marcin 'Amok' Konarski            ---

  invoicewindow.cxx - this file is integral part of `booker' project.

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

#include "invoiceprinter.hxx"
M_VCSID( "$Id: " __ID__ " $" )
#include <yaal/hdata/hdataprocess.hxx>
#include <yaal/hdata/hdatawindow.hxx>

using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::dbwrapper;
using namespace yaal::hconsole;
using namespace yaal::hdata;

namespace booker {

class HInvoiceWindow : public HDataWindow {
public:
	HInvoiceWindow( yaal::hcore::HString const& title_, HDataProcess* tui_ )
		: HDataWindow( title_, tui_ ) {
	  register_postprocess_handler( KEY<'p'>::command, NULL, call( &HInvoiceWindow::handler_print, this, _1 ) );
		return;
	}
	bool handler_print( hconsole::HEvent const& ) {
		print_invoice( dynamic_cast<HDataProcess*>( _tuiProcess )->data_base(), static_cast<int>( get_current_id() ) );
		schedule_repaint( true );
		return ( true );
	}
};

class HInvoiceWindowCreator : public HDataWindowCreator {
	virtual hconsole::HWindow::ptr_t do_new_instance( hconsole::HTUIProcess* tui_, yaal::tools::HXml::HConstNodeProxy const& node_ ) {
		HDataProcess* dp( dynamic_cast<HDataProcess*>( tui_ ) );
		M_ENSURE( dp );
		HString name( xml::attr_val( node_, "title" ) );
		HWindow::ptr_t window( make_pointer<HInvoiceWindow>( name, dp ) );
		return ( window );
	}
};

}

namespace {

bool register_creator( void ) {
	HWindowFactory::get_instance().register_window_creator( "invoicewindow", make_pointer<booker::HInvoiceWindowCreator>() );
	return ( true );
}

bool volatile registered = register_creator();

}

