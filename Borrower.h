#ifndef BORROWER_H
#define BORROWER_H

#include <QString>
#include <QVector>
#include <QSqlDatabase>

#include "BorrowerNumber.h"

class Borrower
{



public:



    Borrower( const QString& id, const QString& name, const QString& address, float feeTotal, float feeHistory, const QVector<BorrowerNumber>& phoneNumbers );

    // Return value is excess.
    int                                 PayFee( int amount );
    void                                AddToFee( int amount );

    const QString&                      GetID() const;
    const QString&                      GetName() const;
    const QString&                      GetAddress() const;
    float                               GetFeeTotal() const;
    float                               GetFeeHistory() const;
    const BorrowerNumber&               GetPhoneNumber( int i ) const;
    const QVector<BorrowerNumber>&      GetPhoneNumbers() const;


    void                                SetName( const QString& newName );
    void                                SetAddress( const QString& newAddress );
    void                                SetPhoneNumber( const QString& number, int i );
    void                                SetPhoneNumber( const QString& number, const QString& newNumber );
    void                                SetPhoneNumbers( const QVector<BorrowerNumber>& newNumbers );
    void                                AddPhoneNumber( const BorrowerNumber& newNumber );
    void                                RemovePhoneNumber( const QString& number );
    void                                RemovePhoneNumber( int i );

    int                                 IndexOfPhoneNumber( const QString& number ) const;

private:



    QString                             id;
    QString                             name;
    QString                             address;

    float                               feeTotal;
    float                               feeHistory;

    QVector<BorrowerNumber>             phoneNumbers;


};

#endif // BORROWER_H
