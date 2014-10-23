#include "BorrowerNumber.h"




//
// BorrowerNumber
//
BorrowerNumber::BorrowerNumber( const QString& id, const QString phoneNumber )
{
    this->id            = id;
    this->phoneNumber   = phoneNumber;
}



//
// BorrowerNumber
//
BorrowerNumber::BorrowerNumber()
{
    this->id           = "";
    this->phoneNumber  = "";
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
// SetPhoneNumber
//
void BorrowerNumber::SetPhoneNumber( const QString& newNumber )
{
    phoneNumber = newNumber;
}
