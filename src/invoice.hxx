/*
---           `invoice' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski            ---

	invoice.hxx - this file is integral part of `invoice' project.

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

