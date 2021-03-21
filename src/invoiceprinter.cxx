/* Read booker/LICENSE.md file for copyright and licensing information. */

#include <cstdlib>
#include <cstring>

#include "invoiceprinter.hxx"
M_VCSID( "$Id: " __ID__ " $" )
#include <yaal/hcore/hlog.hxx>
#include <yaal/tools/filesystem.hxx>
#include <yaal/dbwrapper/hcruddescriptor.hxx>

#include "invoice.hxx"

using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::dbwrapper;

using namespace invoice;

namespace booker {

namespace {

OContractingParty get_contracting_party(  HDataBase::ptr_t db_, int id_ ) {
	HCRUDDescriptor crud( db_ );
	crud.set_table( "contracting_party" );
	crud.set_filter( "id" );
	crud.set_filter_value( to_string( id_ ) );
	HRecordSet::ptr_t rs( crud.execute( HCRUDDescriptor::MODE::READ ) );
	HRecordSet::HIterator it( rs->begin() );
	M_ENSURE( it != rs->end(), "no such record" );
	HRecordSet::values_t contractingPartyData( *it );
	rs.reset();

	OContractingParty contractingParty;
	HString name( contractingPartyData[1] ? *contractingPartyData[1] : "" );
	if ( name.is_empty() ) {
		name.assign( contractingPartyData[2] ? *contractingPartyData[2] : "" );
		if ( ! name.is_empty() )
			name.append( " " );
		name.append( contractingPartyData[4] ? *contractingPartyData[4] : "" );
	}
	contractingParty._name.assign( name );
	contractingParty._country.assign( contractingPartyData[5] ? *contractingPartyData[5] : "" );
	contractingParty._postalCode.assign( contractingPartyData[6] ? *contractingPartyData[6] : "" );
	contractingParty._city.assign( contractingPartyData[7] ? *contractingPartyData[7] : "" );
	contractingParty._street.assign( contractingPartyData[8] ? *contractingPartyData[8] : "" );
	contractingParty._streetNo.assign( contractingPartyData[9] ? *contractingPartyData[9] : "" );
	contractingParty._flatNo.assign( contractingPartyData[10] ? *contractingPartyData[10] : "" );
	contractingParty._tin.assign( contractingPartyData[11] ? *contractingPartyData[11] : "" );
	contractingParty._extra.assign( contractingPartyData[16] ? *contractingPartyData[16] : "" );
	return contractingParty;
}

}

void print_invoice( HDataBase::ptr_t db_, int id_ ) {
	HString sql(
			"SELECT i.*, pm.name, issuer.*, invoice_type.name"
			" FROM invoice AS i "
			" LEFT JOIN payment_method AS pm ON pm.id = i.id_pay_method"
			" LEFT JOIN issuer ON issuer.id = i.id_issuer"
			" LEFT JOIN invoice_type ON invoice_type.id = i.id_invoice_type"
			" WHERE i.id = "
	);
	sql.append( to_string( id_ ) );
	HRecordSet::ptr_t rs( db_->execute_query( sql ) );
	HRecordSet::HIterator it( rs->begin() );
	M_ENSURE( it != rs->end(), "no such record" );
	HRecordSet::values_t document( *it );
	rs.reset();
	OInvoice inv;
	inv._vendor = get_contracting_party( db_, lexical_cast<int>( *document[1] ) );
	inv._vendee = get_contracting_party( db_, lexical_cast<int>( *document[2] ) );
	inv._invoiceNo.assign( document[3] ? *document[3] : "" );
	inv._invoiceDate.assign( document[4] ? *document[4] : "" );
	inv._transactionDate.assign( document[5] ? *document[5] : "" );
	inv._dueDate.assign( document[6] ? *document[6] : "" );
	inv._payMethod.assign( document[10] ? *document[10] : "" );
	inv._issuer.assign( document[12] ? *document[12] : "" );
	inv._signature.assign( document[13] ? *document[13] : "" );
	if ( !! document[14] ) {
		HString type( *document[14] );
		type.lower();
		if ( type == "eu" ) {
			inv._type = OInvoice::TYPE::EU;
			inv._dueDate.append( " days" );
		} else if ( type == "eu vat" ) {
			inv._type = OInvoice::TYPE::EU_VAT;
			inv._dueDate.append( " days" );
		} else if ( type == "pl" ) {
			inv._type = OInvoice::TYPE::PL;
			inv._dueDate.append( " dni" );
		} else {
			M_THROW( "Unsupported invoice type: `"_ys.append( type ).append( "'." ), 0 );
		}
	}
	HCRUDDescriptor crud( db_ );
	crud.set_table( "invoice_item" );
	crud.set_filter( "id_invoice" );
	crud.set_filter_value( to_string( id_ ) );
	crud.set_sort( "id ASC" );
	rs = crud.execute( HCRUDDescriptor::MODE::READ );
	for ( HRecordSet::values_t const& itemData : *rs ) {
		OInvoiceItem item;
		item._name.assign( itemData[2] ? *itemData[2] : "" );
		item._price = ( itemData[3] ? *itemData[3] : "0" );
		item._vat = ( itemData[4] ? *itemData[4] : "0" );
		item._quantity = ( itemData[5] ? *itemData[5] : "0" );
		inv._items.push_back( item );
	}
	document_file_names_t dfn( print( inv ) );
	HString cmd;
	for ( HString const& fn : dfn ) {
		HString ext( fn.right( 4 ) );
		M_ENSURE( ext == ".tex" );
		HString base( fn.left( fn.get_size() - 4 ) );
		cmd.assign( "pdflatex " ).append( fn );
		HUTF8String utf8( cmd );
		if ( ::system( utf8.c_str() ) != 0 ) {
			log << strerror( errno ) << endl;
		}
		if ( ::system( utf8.c_str() ) != 0 ) { /* Use .aux to get prettier output. */
			log << strerror( errno ) << endl;
		}
		filesystem::remove( fn );
		filesystem::remove( base + ".aux" );
		filesystem::remove( base + ".log" );
	}
	return;
}

}

