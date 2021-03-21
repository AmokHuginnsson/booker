/* Read booker/LICENSE.md file for copyright and licensing information. */

#include "invoiceprinter.hxx"
M_VCSID( "$Id: " __ID__ " $" )
#include <yaal/hdata/hdataprocess.hxx>
#include <yaal/hdata/hdatawindow.hxx>
#include <yaal/tools/keycode.hxx>

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
	  register_postprocess_handler( KEY<'p'>::command, nullptr, call( &HInvoiceWindow::handler_print, this, _1 ) );
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
		return window;
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

