/* Read booker/LICENSE.md file for copyright and licensing information. */

#ifndef INVOICE_INVOICE_HXX_INCLUDED
#define INVOICE_INVOICE_HXX_INCLUDED 1

#include <yaal/hcore/hstring.hxx>
#include <yaal/hcore/hnumber.hxx>
#include <yaal/hcore/harray.hxx>

namespace invoice {

struct OContractingParty {
	yaal::hcore::HString _name;
	yaal::hcore::HString _firstName;
	yaal::hcore::HString _middleName;
	yaal::hcore::HString _lastName;
	yaal::hcore::HString _country;
	yaal::hcore::HString _postalCode;
	yaal::hcore::HString _city;
	yaal::hcore::HString _street;
	yaal::hcore::HString _streetNo;
	yaal::hcore::HString _flatNo;
	yaal::hcore::HString _tin;
	yaal::hcore::HString _email;
	yaal::hcore::HString _webPage;
	yaal::hcore::HString _phone;
	yaal::hcore::HString _fax;
	yaal::hcore::HString _extra;
	OContractingParty( void );
};

struct OInvoiceItem {
	yaal::hcore::HString _name;
	yaal::hcore::HNumber _price;
	yaal::hcore::HNumber _vat;
	yaal::hcore::HNumber _quantity;
	OInvoiceItem( void );
};

struct OInvoice {
	enum class TYPE {
		INVALID,
		EU,
		EU_VAT,
		PL
	};
	typedef yaal::hcore::HArray<OInvoiceItem> items_t;
	TYPE _type;
	OContractingParty _vendor;
	OContractingParty _vendee;
	yaal::hcore::HString _invoiceNo;
	yaal::hcore::HString _invoiceDate;
	yaal::hcore::HString _transactionDate;
	yaal::hcore::HString _dueDate;
	yaal::hcore::HString _payMethod;
	yaal::hcore::HString _issuer;
	yaal::hcore::HString _signature;
	items_t _items;
	OInvoice( void );
};

typedef yaal::hcore::HArray<yaal::hcore::HString> document_file_names_t;
document_file_names_t print( OInvoice const& );

}

#endif /* #ifndef INVOICE_INVOICE_HXX_INCLUDED */

