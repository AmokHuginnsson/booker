/* Read booker/LICENSE.md file for copyright and licensing information. */

#include <yaal/hcore/hfile.hxx>
#include <yaal/tools/hfsitem.hxx>
#include <yaal/tools/hstringstream.hxx>
#include <yaal/tools/streamtools.hxx>
#include <yaal/tools/money.hxx>
M_VCSID( "$Id: " __ID__ " $" )
//M_VCSID( "$Id: " __TID__ " $" )
#include "invoice.hxx"

using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::money;

namespace invoice {

OContractingParty::OContractingParty( void )
	: _name()
	, _firstName()
	, _middleName()
	, _lastName()
	, _country()
	, _postalCode()
	, _city()
	, _street()
	, _streetNo()
	, _flatNo()
	, _tin()
	, _email()
	, _webPage()
	, _phone()
	, _fax()
	, _extra() {
}

OInvoiceItem::OInvoiceItem( void )
	: _name()
	, _price()
	, _vat()
	, _quantity() {
}

OInvoice::OInvoice( void )
	: _type( TYPE::INVALID )
	, _vendor()
	, _vendee()
	, _invoiceNo()
	, _invoiceDate()
	, _transactionDate()
	, _dueDate()
	, _payMethod()
	, _issuer()
	, _signature()
	, _items() {
}

char const INVOICE_TEMPLATE_PATH[] = "./data/invoice_";

HHashMap<HString, HString> _translations_ = {
	{ "przelew", "Bank transfer" }
};

namespace {
HString leave_characters( HString const& string_, HString const& characters_ ) {
	M_PROLOG
	HString string;
	for ( HString::const_iterator it( string_.begin() ), end( string_.end() ); it != end; ++ it ) {
		if ( characters_.find( *it ) != HString::npos ) {
			string += *it;
		}
	}
	return ( string );
	M_EPILOG
}
}

document_file_names_t print( OInvoice const& invoice_ ) {
	M_PROLOG
	HString invoiceTemplatePathName( INVOICE_TEMPLATE_PATH );
	if ( invoice_._type == OInvoice::TYPE::EU ) {
		invoiceTemplatePathName.append( "eu.tex" );
	} else if ( invoice_._type == OInvoice::TYPE::EU_VAT ) {
		invoiceTemplatePathName.append( "eu_vat.tex" );
	} else if ( invoice_._type == OInvoice::TYPE::PL ) {
		invoiceTemplatePathName.append( "pl.tex" );
	} else {
		M_THROW( "Invoice type not set: ", static_cast<int>( invoice_._type ) );
	}
	HFSItem invoiceTemplatePath( invoiceTemplatePathName );
	M_ENSURE( !! invoiceTemplatePath && invoiceTemplatePath.is_file() );
	int invoiceTemplateSize( static_cast<int>( invoiceTemplatePath.get_size() ) );
	HFile invoiceTemplate( invoiceTemplatePathName, HFile::OPEN::READING );
	HChunk readBuffer( invoiceTemplateSize );
	M_ENSURE( invoiceTemplate.read( readBuffer.raw(), invoiceTemplateSize ) == invoiceTemplateSize );
	invoiceTemplate.close();
	HString invoiceText( readBuffer.get<char>(), invoiceTemplateSize );

	invoiceText.replace( "@invoiceNo@", invoice_._invoiceNo );
	invoiceText.replace( "@invoiceDate@", invoice_._invoiceDate );
	invoiceText.replace( "@transactionDate@", invoice_._transactionDate );
	invoiceText.replace( "@dueDate@", invoice_._dueDate );

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
	invoiceText.replace( "@vendorCountry@", invoice_._vendor._country );
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
	invoiceText.replace( "@vendeeCountry@", invoice_._vendee._country );
	invoiceText.replace( "@vendeeCity@", vendeeCity );
	invoiceText.replace( "@vendeeTIN@", invoice_._vendee._tin );
	invoiceText.replace( "@vendeeExtra@", invoice_._vendee._extra );

	invoiceText.replace( "@issuer@", invoice_._issuer );
	invoiceText.replace( "@signature@", invoice_._signature );

	typedef HMap<HNumber, HNumber> taxes_t;
	taxes_t taxes;
	HStringStream items;
	int no( 1 );
	HNumber totalNetto;
	HNumber totalBrutto;
	HString unit( invoice_._type == OInvoice::TYPE::PL ? "szt." : "each" );
	for ( OInvoice::items_t::const_iterator it( invoice_._items.begin() ), end( invoice_._items.end() ); it != end; ++ it ) {
		if ( no > 1 ) {
			items << "\\hdashline" << endl;
		}
		HNumber netto( it->_price * it->_quantity );
		totalNetto += netto;
		HNumber vat( ( netto * it->_vat ) / "100" );
		HNumber brutto( netto + vat );
		items << no << '&' << it->_name << "&" << unit << "&" << it->_quantity << '&' << money_string( it->_price );
		if ( ( invoice_._type == OInvoice::TYPE::PL ) || ( invoice_._type == OInvoice::TYPE::EU_VAT ) ) {
			items << '&' << it->_vat << "\\%&" << money_string( netto ) << '&' << money_string( vat ) << '&' << money_string( brutto ) << "\\\\" << endl;
		} else {
			items << '&' << money_string( netto ) << "\\\\" << endl;
		}
		++ no;
	}
	invoiceText.replace( "@items@", items.string() );
	if ( ( invoice_._type == OInvoice::TYPE::PL ) || ( invoice_._type == OInvoice::TYPE::EU_VAT ) ) {
		for ( OInvoice::items_t::const_iterator it( invoice_._items.begin() ), end( invoice_._items.end() ); it != end; ++ it ) {
			taxes[it->_vat] += it->_quantity * it->_price;
		}
		HStringStream taxesText;
		HNumber totalVat;
		for ( taxes_t::const_iterator it( taxes.begin() ), end( taxes.end() ); it != end; ++ it ) {
			HNumber vat( ( it->first * it->second ) / "100" );
			HNumber brutto( it->second + vat );
			totalVat += vat;
			totalBrutto += brutto;
			taxesText << it->first << "\\%&" << money_string( it->second ) << '&' << money_string( vat ) << '&' << money_string( brutto ) << "\\\\" << endl;
		}
		invoiceText.replace( "@taxes@", taxesText.string() );
		invoiceText.replace( "@vatAmount@", money_string( totalVat ) );
		invoiceText.replace( "@brutto@", money_string( totalBrutto ) );
	}
	if ( invoice_._type == OInvoice::TYPE::PL ) {
		invoiceText.replace( "@amountInWords@", in_words_pl( totalBrutto, CURRENCY::PLN ) );
		invoiceText.replace( "@payMethod@", invoice_._payMethod );
	} else {
		invoiceText.replace(
			"@amountInWords@",
			in_words_en( invoice_._type == OInvoice::TYPE::EU ? totalNetto : totalBrutto, CURRENCY::PLN )
		);
		invoiceText.replace( "@payMethod@", _translations_.at( HString( invoice_._payMethod ).lower() ) );
	}
	invoiceText.replace( "@netto@", money_string( totalNetto ) );
	HString invoiceTextCopy( invoiceText );
	if ( invoice_._type == OInvoice::TYPE::PL ) {
		invoiceText.replace( "@documentType@", "ORYGINA£" );
		invoiceTextCopy.replace( "@documentType@", "KOPIA" );
	} else {
		invoiceText.replace( "@documentType@", "ORYGINAL" );
		invoiceTextCopy.replace( "@documentType@", "COPY" );
	}

	document_file_names_t documentFileNames;

	HString date( leave_characters( invoice_._invoiceDate, "0123456789-" ) );
	HString fileName;

	fileName.assign( "fv_" ).append( date ).append( "_orig.tex" );
	HFile invoice( fileName, HFile::OPEN::WRITING );
	HUTF8String utf8( invoiceText );
	invoice.write( utf8.c_str(), utf8.byte_count() );
	invoice.close();
	documentFileNames.emplace_back( fileName );

	fileName.assign( "fv_" ).append( date ).append( "_copy.tex" );
	HFile invoiceCopy( fileName, HFile::OPEN::WRITING );
	utf8 = invoiceTextCopy;
	invoice.write( utf8.c_str(), utf8.byte_count() );
	invoiceCopy.close();
	documentFileNames.emplace_back( fileName );
	return ( documentFileNames );
	M_EPILOG
}

}

