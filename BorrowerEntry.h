#ifndef BORROWERENTRY_H
#define BORROWERENTRY_H

#include <QWidget>
#include "DatabaseManager.h"

namespace Ui {
class BorrowerEntry;
}


class BorrowerEntry : public QWidget
{
    Q_OBJECT

public:


    BorrowerEntry( DatabaseManager* manager, const Borrower& borrower, QWidget *parent = 0 );
    ~BorrowerEntry();




private slots:
    void on_updateButton_clicked();

    void on_deleteButton_clicked();

private:


    Ui::BorrowerEntry*              ui;
    DatabaseManager*                manager;
    Borrower                        borrower;
};

#endif // BORROWERENTRY_H
