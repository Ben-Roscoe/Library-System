#ifndef PHONENUMBERENTRY_H
#define PHONENUMBERENTRY_H

#include <QWidget>
#include "BorrowerNumber.h"
#include "Borrower.h"
#include "DatabaseManager.h"

namespace Ui {
class PhoneNumberEntry;
}

class PhoneNumberEntry : public QWidget
{
    Q_OBJECT

public:



    explicit PhoneNumberEntry( const BorrowerNumber& borrowerNumber, DatabaseManager* manager, QWidget *parent = 0 );
    ~PhoneNumberEntry();



private slots:


    void on_updateButton_clicked();

    void on_deleteButton_clicked();

private:



    Ui::PhoneNumberEntry*           ui;
    DatabaseManager*                manager;
    BorrowerNumber                  borrowerNumber;

};

#endif // PHONENUMBERENTRY_H
