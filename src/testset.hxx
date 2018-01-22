/* Read booker/LICENSE.md file for copyright and licensing information. */

#ifndef TESTSET_HXX_INCLUDED
#define TESTSET_HXX_INCLUDED

#include <yaal/dbwrapper/hdatabase.hxx>
#include <yaal/dbwrapper/hcruddescriptor.hxx>

namespace booker {

class HTestSet {
	yaal::dbwrapper::HCRUDDescriptor _sQLDescriptor;
public:
	/*{*/
	int long _id;
	int long _idName;
	yaal::hcore::HString _vText;
	yaal::hcore::HString _vInt;
	yaal::hcore::HString _vReal;
	yaal::hcore::HTime _vDate;
	yaal::hcore::HTime _vTime;
	yaal::hcore::HTime _vDatetime;
	/*}*/
protected:
	/*{*/
	/*}*/
public:
	/*{*/
	HTestSet( yaal::dbwrapper::HDataBase::ptr_t = yaal::dbwrapper::HDataBase::ptr_t() );
	virtual ~HTestSet ( void );
	void sync( void );
	void sync( yaal::dbwrapper::HRecordSet::iterator );
	yaal::dbwrapper::HRecordSet::ptr_t get_records( void );
	/*}*/
protected:
	/*{*/
	/*}*/
};

}

#endif /* TESTSET_HXX_INCLUDED */
