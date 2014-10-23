#ifndef BORROWERNUMBER_H
#define BORROWERNUMBER_H


#include <QString>


class BorrowerNumber
{



public:



    BorrowerNumber( const QString& id, const QString phoneNumber );
    BorrowerNumber();


    const QString&      GetID() const;
    const QString&      GetPhoneNumber() const;

    void                SetPhoneNumber( const QString& newNumber );


private:



    QString             id;
    QString             phoneNumber;



};




#endif // BORROWERNUMBER_H
