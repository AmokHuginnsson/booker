/*
---           `invoice' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski            ---

	invoice.cxx - this file is integral part of `invoice' project.

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

#include <yaal/hcore/hfile.hxx>
#include <yaal/tools/hfsitem.hxx>
#include <yaal/tools/hstringstream.hxx>
#include <yaal/tools/streamtools.hxx>
#include <yaal/tools/util.hxx>
M_VCSID( "$Id: " __ID__ " $" )
//M_VCSID( "$Id: " __TID__ " $" )
#include "invoice.hxx"

using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::util;

namespace invoice {

OContractingParty::OContractingParty( void )
	: _name(), _firstName(), _middleName(), _lastName(), _country(),
	_postalCode(), _city(), _street(), _streetNo(), _flatNo(), _tin(),
	_email(), _webPage(), _phone(), _fax(), _extra()
	{}

OInvoiceItem::OInvoiceItem( void )
	: _name(), _price(), _vat(), _quantity()
	{}

OInvoice::OInvoice( void )
	: _vendor(), _vendee(), _invoiceNo(), _invoiceDate(),
	_transactionDate(), _dueDate(), _payMethod(), _issuer(),
	_signature(), _items()
	{}

char const INVOICE_TEMPLATE_PATH[] = "./data/invoice.tex";

namespace {
HString leave_characters( HString const& string_, HString const& characters_ ) {
	M_PROLOG
	HString string;
	for ( HString::const_iterator it( string_.begin() ), end( string_.end() ); it != end; ++ it ) {
		if ( characters_.find( *it ) != HString::npos )
			string += *it;
	}
	return ( string );
	M_EPILOG
}
}

document_file_names_t print( OInvoice const& invoice_ ) {
	M_PROLOG
	HFSItem invoiceTemplatePath( INVOICE_TEMPLATE_PATH );
	M_ENSURE( !! invoiceTemplatePath && invoiceTemplatePath.is_file() );
	int invoiceTemplateSize( static_cast<int>( invoiceTemplatePath.get_size() ) );
	HFile invoiceTemplate( INVOICE_TEMPLATE_PATH, HFile::OPEN::READING );
	HChunk readBuffer( invoiceTemplateSize );
	M_ENSURE( invoiceTemplate.read( readBuffer.raw(), invoiceTemplateSize ) == invoiceTemplateSize );
	invoiceTemplate.close();
	HString invoiceText( readBuffer.get<char>(), invoiceTemplateSize );

	invoiceText.replace( "@invoiceNo@", invoice_._invoiceNo );
	invoiceText.replace( "@invoiceDate@", invoice_._invoiceDate );
	invoiceText.replace( "@transactionDate@", invoice_._transactionDate );
	invoiceText.replace( "@dueDate@", invoice_._dueDate );
	invoiceText.replace( "@payMethod@", invoice_._payMethod );

	HString vendorName( invoice_._vendor._name );
	if ( vendorName.is_empty() ) {
		vendorName += invoice_._vendor._firstName;
		if ( ! invoice_._vendor._middleName.is_empty() ) {
			vendorName += " ";
			vendorName += invoice_._vendor._middleName;
		}
		vendorName += " ";
		vendorName += invoice_._vendor._lastName;
	}
	invoiceText.replace( "@vendorName@", vendorName );
	HString vendorStreet( invoice_._vendor._street );
	if ( ! invoice_._vendor._streetNo.is_empty() ) {
		vendorStreet += " ";
		vendorStreet += invoice_._vendor._streetNo;
	}
	invoiceText.replace( "@vendorStreet@", vendorStreet );
	HString vendorCity( invoice_._vendor._city );
	if ( ! invoice_._vendor._postalCode.is_empty() ) {
		vendorCity = invoice_._vendor._postalCode;
		vendorCity += " ";
		vendorCity += invoice_._vendor._city;
	}
	invoiceText.replace( "@vendorCity@", vendorCity );
	invoiceText.replace( "@vendorTIN@", invoice_._vendor._tin );
	invoiceText.replace( "@vendorExtra@", invoice_._vendor._extra );

	HString vendeeName( invoice_._vendee._name );
	if ( vendeeName.is_empty() ) {
		vendeeName += invoice_._vendee._firstName;
		if ( ! invoice_._vendee._middleName.is_empty() ) {
			vendeeName += " ";
			vendeeName += invoice_._vendee._middleName;
		}
		vendeeName += " ";
		vendeeName += invoice_._vendee._lastName;
	}
	invoiceText.replace( "@vendeeName@", vendeeName );
	HString vendeeStreet( invoice_._vendee._street );
	if ( ! invoice_._vendee._streetNo.is_empty() ) {
		vendeeStreet += " ";
		vendeeStreet += invoice_._vendee._streetNo;
	}
	invoiceText.replace( "@vendeeStreet@", vendeeStreet );
	HString vendeeCity( invoice_._vendee._city );
	if ( ! invoice_._vendee._postalCode.is_empty() ) {
		vendeeCity = invoice_._vendee._postalCode;
		vendeeCity += " ";
		vendeeCity += invoice_._vendee._city;
	}
	invoiceText.replace( "@vendeeCity@", vendeeCity );
	invoiceText.replace( "@vendeeTIN@", invoice_._vendee._tin );
	invoiceText.replace( "@vendeeExtra@", invoice_._vendee._extra );

	invoiceText.replace( "@issuer@", invoice_._issuer );
	invoiceText.replace( "@signature@", invoice_._signature );

	typedef HMap<HNumber, HNumber> taxes_t;
	taxes_t taxes;
	HStringStream items;
	int no( 1 );
	for ( OInvoice::items_t::const_iterator it( invoice_._items.begin() ), end( invoice_._items.end() ); it != end; ++ it ) {
		if ( no > 1 )
			items << "\\hdashline" << endl;
		HNumber netto( it->_price * it->_quantity );
		HNumber vat( ( netto * it->_vat ) / "100" );
		HNumber brutto( netto + vat );
		items << no << '&' << it->_name << "&szt.&" << it->_quantity << '&' << money_string( it->_price )
			<< '&' << it->_vat << "\\%&" << money_string( netto ) << '&' << money_string( vat ) << '&' << money_string( brutto ) << "\\\\" << endl;
		++ no;
	}
	invoiceText.replace( "@items@", items.string() );
	for ( OInvoice::items_t::const_iterator it( invoice_._items.begin() ), end( invoice_._items.end() ); it != end; ++ it ) {
		taxes[it->_vat] += it->_quantity * it->_price;
	}
	HStringStream taxesText;
	HNumber totalNetto;
	HNumber totalVat;
	HNumber totalBrutto;
	for ( taxes_t::const_iterator it( taxes.begin() ), end( taxes.end() ); it != end; ++ it ) {
		HNumber vat( ( it->first * it->second ) / "100" );
		HNumber brutto( it->second + vat );
		totalNetto += it->second;
		totalVat += vat;
		totalBrutto += brutto;
		taxesText << it->first << "\\%&" << money_string( it->second ) << '&' << money_string( vat ) << '&' << money_string( brutto ) << "\\\\" << endl;
	}
	invoiceText.replace( "@taxes@", taxesText.string() );
	invoiceText.replace( "@netto@", money_string( totalNetto ) );
	invoiceText.replace( "@vatAmount@", money_string( totalVat ) );
	invoiceText.replace( "@brutto@", money_string( totalBrutto ) );
	invoiceText.replace( "@amountInWords@", in_words_pl( totalBrutto ) );
	HString invoiceTextCopy( invoiceText );
	invoiceText.replace( "@documentType@", "ORYGINA£" );
	invoiceTextCopy.replace( "@documentType@", "KOPIA" );

	document_file_names_t documentFileNames;

	HString date( leave_characters( invoice_._invoiceDate, "0123456789-" ) );
	HString fileName;

	fileName.assign( "fv_" ).append( date ).append( "_orig.tex" );
	HFile invoice( fileName, HFile::OPEN::WRITING );
	invoice.write( invoiceText.raw(), invoiceText.get_length() );
	invoice.close();
	documentFileNames.emplace_back( fileName );

	fileName.assign( "fv_" ).append( date ).append( "_copy.tex" );
	HFile invoiceCopy( fileName, HFile::OPEN::WRITING );
	invoiceCopy.write( invoiceTextCopy.raw(), invoiceTextCopy.get_length() );
	invoiceCopy.close();
	documentFileNames.emplace_back( fileName );
	return ( documentFileNames );
	M_EPILOG
}

}

