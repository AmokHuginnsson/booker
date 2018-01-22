/* Read booker/LICENSE.md file for copyright and licensing information. */

#ifndef TESTWINDOW_HXX_INCLUDED
#define TESTWINDOW_HXX_INCLUDED

#include <yaal/hcore/hhashmap.hxx>
#include <yaal/hconsole/hwindow.hxx>
#include <yaal/hconsole/hevent.hxx>
#include <yaal/hconsole/hcomboboxwidget.hxx>

namespace booker {

class HTestWindow : public yaal::hconsole::HWindow {
protected:
	/*{*/
	typedef yaal::hcore::HHashMap<int, yaal::hcore::HPair<int, yaal::hcore::HString>> names_t;
	names_t _names;
	yaal::hconsole::HListWidget* _list;
	yaal::hconsole::HListWidget* _editableList;
	yaal::hconsole::HEditWidget* _edit;
	yaal::hconsole::HComboboxWidget* _name;
	/*}*/
public:
	/*{*/
	HTestWindow( const char* );
	virtual ~HTestWindow( void );
	/*}*/
protected:
	/*{*/
	virtual void do_init( void );
	bool handler_delete( yaal::hconsole::HEvent const& );
	bool handler_enter( yaal::hconsole::HEvent const& );
	bool on_sel_change( yaal::hconsole::HEvent const& );
	/*}*/
private:
	/*{*/
	HTestWindow( const HTestWindow& );
	HTestWindow& operator = ( const HTestWindow& );
	/*}*/
};

}

#endif /* TESTWINDOW_HXX_INCLUDED */
