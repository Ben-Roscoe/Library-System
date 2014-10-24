#include "BorrowerNumber.h"




//
// BorrowerNumber
//
BorrowerNumber::BorrowerNumber( const QString& id, const QString phoneNumber, const QString& borrowerID )
{
    this->id            = id;
    this->phoneNumber   = phoneNumber;
    this->borrowerID    = borrowerID;
}



//
// BorrowerNumber
//
BorrowerNumber::BorrowerNumber()
{
    this->id           = "";
    this->phoneNumber  = "";
    this->borrowerID   = "";
}



//
// GetID
//
const QString& BorrowerNumber::GetID() const
{
    return id;
}



//
// GetPhoneNumber
//
const QString& BorrowerNumber::GetPhoneNumber() const
{
    return phoneNumber;
}



//
// GetBorrowerID
//
const QString&BorrowerNumber::GetBorrowerID() const
{
    return borrowerID;
}



//
// SetPhoneNumber
//
void BorrowerNumber::SetPhoneNumber( const QString& newNumber )
{
    phoneNumber = newNumber;
}
