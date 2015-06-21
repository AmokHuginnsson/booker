/*
---           `booker' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski            ---

	invoiceprinter.cxx - this file is integral part of `booker' project.

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

#include <cstdlib>

#include "invoiceprinter.hxx"
M_VCSID( "$Id: " __ID__ " $" )
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
	crud.set_filter( to_string( "id = " ).append( to_string( id_ ) ) );
	HRecordSet::ptr_t rs( crud.execute( HCRUDDescriptor::MODE::SELECT ) );
	HRecordSet::HIterator it( rs->begin() );
	M_ENSURE_EX( it != rs->end(), "no such record" );
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
	contractingParty._tin.assign( contractingPartyData[11] ? *contractingPartyData[11] : "" );
	contractingParty._extra.assign( contractingPartyData[16] ? *contractingPartyData[16] : "" );
	return ( contractingParty );
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
	M_ENSURE_EX( it != rs->end(), "no such record" );
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
		} else if ( type == "pl" ) {
			inv._type = OInvoice::TYPE::PL;
			inv._dueDate.append( " dni" );
		} else {
			M_THROW( "Unsupported invoice type: `"_ys.append( type ).append( "'." ), 0 );
		}
	}
	HCRUDDescriptor crud( db_ );
	crud.set_table( "invoice_item" );
	crud.set_filter( to_string( "id_invoice = " ).append( to_string( id_ ) ) );
	crud.set_sort( "id ASC" );
	rs = crud.execute( HCRUDDescriptor::MODE::SELECT );
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
		::system( cmd.c_str() );
		::system( cmd.c_str() ); /* Use .aux to get prettier output. */
		filesystem::remove( fn );
		filesystem::remove( base + ".aux" );
		filesystem::remove( base + ".log" );
	}
	return;
}

}

