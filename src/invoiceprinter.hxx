/* Read booker/LICENSE.md file for copyright and licensing information. */

#ifndef BOOKER_INVOICEPRINTER_HXX_INCLUDED
#define BOOKER_INVOICEPRINTER_HXX_INCLUDED 1

#include <yaal/dbwrapper/hdatabase.hxx>

namespace booker {

void print_invoice( yaal::dbwrapper::HDataBase::ptr_t, int );

}

#endif /* #ifndef BOOKER_INVOICEPRINTER_HXX_INCLUDED */

