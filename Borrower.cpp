#include "Borrower.h"

#include <qsqlquery.h>
#include <QVariant>
#include <QtDebug>
#include <QSqlError>


// Public:



//
// Borrower
//
Borrower::Borrower( const QString& id, const QString& name, const QString& address, float feeTotal, float feeHistory, const QVector<BorrowerNumber>& phoneNumbers )
{
    this->id            = id;
    this->name          = name;
    this->address       = address;
    this->feeTotal      = feeTotal;
    this->feeHistory    = feeHistory;
    this->phoneNumbers  = phoneNumbers;
}



//
// Borrower
//
Borrower::Borrower()
{
    this->id           = "-1";
    this->name         = "";
    this->address      = "";
    this->feeTotal     = 0.0f;
    this->feeHistory   = 0.0f;
}



//
// PayFee
//
int Borrower::PayFee( int amount )
{
    feeTotal -= amount;
    if( feeTotal < 0.0f )
    {
        int temp = feeTotal;
        feeTotal = 0;
        return std::abs( temp );
    }
    return 0;
}



//
// AddToFee
//
void Borrower::AddToFee( int amount )
{
    feeTotal        += amount;
    feeHistory      += amount;
}



//
// GetID
//
const QString& Borrower::GetID() const
{
    return id;
}



//
// GetName
//
const QString& Borrower::GetName() const
{
    return name;
}



//
// GetAddress
//
const QString& Borrower::GetAddress() const
{
    return address;
}



//
// GetFeeTotal
//
float Borrower::GetFeeTotal() const
{
    return feeTotal;
}



//
// GetFeeHistory
//
float Borrower::GetFeeHistory() const
{
    return feeHistory;
}



//
// GetPhoneNumber
//
const BorrowerNumber& Borrower::GetPhoneNumber( int i ) const
{
    return phoneNumbers[i];
}



//
// GetPhoneNumbers
//
const QVector<BorrowerNumber>& Borrower::GetPhoneNumbers() const
{
    return phoneNumbers;
}



//
// SetName
//
void Borrower::SetName( const QString& newName )
{
    name = newName;
}



//
// SetAddress
//
void Borrower::SetAddress( const QString& newAddress )
{
    address = newAddress;
}



//
// SetPhoneNumber
//
void Borrower::SetPhoneNumber( const QString& number, int i )
{
    if( i < phoneNumbers.size() && i >= 0 )
    {
        phoneNumbers[i].SetPhoneNumber( number );
    }
}



//
// SetPhoneNumber
//
void Borrower::SetPhoneNumber( const BorrowerNumber& number, const QString& newNumber )
{
    int i = IndexOfPhoneNumber( number.GetID() );
    if( i != -1 )
    {
        phoneNumbers[i].SetPhoneNumber( newNumber );
        qDebug() << "fsafsa";
    }
}



//
// SetPhoneNumbers
//
void Borrower::SetPhoneNumbers( const QVector<BorrowerNumber>& newNumbers )
{
    phoneNumbers = newNumbers;
}



//
// AddPhoneNumber
//
void Borrower::AddPhoneNumber( const BorrowerNumber& newNumber )
{
    phoneNumbers.push_back( newNumber );
}



//
// RemovePhoneNumber
//
void Borrower::RemovePhoneNumber( int i )
{
    if( i < phoneNumbers.size() && i >= 0 )
    {
        phoneNumbers.removeAt( i );
    }
}



//
// RemovePhoneNumber
//
void Borrower::RemovePhoneNumber( const QString& number )
{
    int i = IndexOfPhoneNumber( number );
    if( i != -1 )
    {
        phoneNumbers.removeAt( i );
    }
}



//
// IndexOfPhoneNumber
//
int Borrower::IndexOfPhoneNumber( const QString& number ) const
{
    for( int i = 0; i < phoneNumbers.size(); i++ )
    {
        if( phoneNumbers[i].GetID() == number )
        {
            return i;
        }
    }
    return -1;
}

