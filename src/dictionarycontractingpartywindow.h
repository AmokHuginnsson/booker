/*
---           booker.h 0.0.0 (c) 1978 by Marcin 'Amok' Konarski            ---

	dictionarybank.h - this file is integral part of booker.h project.

	i.  You may not make any changes in Copyright information.
	ii. You must attach Copyright information to any part of every copy
	    of this software.

Copyright:

 You are free to use this program as is, you can redistribute binary
 package freely but:
  1. You can not use any part of sources of this software.
  2. You can not redistribute any part of sources of this software.
  3. No reverse engineering is allowed.
  4. If you want redistribute binary package you can not demand any fees
     for this software.
     You can not even demand cost of the carrier (CD for example).
  5. You can not include it to any commercial enterprise (for example 
     as a free add-on to payed software or payed newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

#ifndef __DICTIONARYCONTRACTINGPARTY_H
#define __DICTIONARYCONTRACTINGPARTY_H

class HDictionaryContractingPartyWindow : public yaal::hconsole::HWindow
	{
protected:
	/*{*/
	yaal::hconsole::HListControl * f_poList;
	yaal::hconsole::HEditControl * f_poEdit;
	/*}*/
public:
	/*{*/
	HDictionaryContractingPartyWindow ( const char * );
	virtual ~HDictionaryContractingPartyWindow ( void );
	int init ( void );
	/*}*/
protected:
	/*{*/
	int handler_delete ( int, void * );
	int handler_enter ( int, void * );
	/*}*/
private:
	/*{*/
	HDictionaryContractingPartyWindow ( const HDictionaryContractingPartyWindow & );
	HDictionaryContractingPartyWindow & operator = ( const HDictionaryContractingPartyWindow & );
	/*}*/
	};

#endif /* __DICTIONARYCONTRACTINGPARTY_H */
