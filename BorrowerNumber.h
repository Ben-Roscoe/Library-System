#ifndef BORROWERNUMBER_H
#define BORROWERNUMBER_H


#include <QString>


class BorrowerNumber
{



public:



    BorrowerNumber( const QString& id, const QString phoneNumber, const QString& borrowerID );
    BorrowerNumber();


    const QString&      GetID() const;
    const QString&      GetPhoneNumber() const;
    const QString&      GetBorrowerID() const;

    void                SetPhoneNumber( const QString& newNumber );


private:



    QString             id;
    QString             phoneNumber;
    QString             borrowerID;



};




#endif // BORROWERNUMBER_H
