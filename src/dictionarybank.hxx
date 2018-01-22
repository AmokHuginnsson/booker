/* Read booker/LICENSE.md file for copyright and licensing information. */

#ifndef DICTIONARYBANK_HXX_INCLUDED
#define DICTIONARYBANK_HXX_INCLUDED

#include <yaal/hconsole/hevent.hxx>
#include <yaal/hdata/hdatawindow.hxx>

namespace booker {

class HDictionaryBank : public yaal::hdata::HDataWindow {
protected:
	/*{*/
	/*}*/
public:
	/*{*/
	HDictionaryBank( const char*, yaal::hdata::HDataProcess* );
	virtual ~HDictionaryBank( void );
	virtual bool handler_add( yaal::hconsole::HEvent const& );
	/*}*/
protected:
	/*{*/
	/*}*/
};

}

#endif /* DICTIONARYBANK_HXX_INCLUDED */

