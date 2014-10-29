#ifndef BORROWERBOOKSENTRY_H
#define BORROWERBOOKSENTRY_H

#include <QWidget>
#include "DatabaseManager.h"

namespace Ui {
class BorrowerBooksEntry;
}

class BorrowerBooksEntry : public QWidget
{



    Q_OBJECT



public:



    explicit BorrowerBooksEntry( DatabaseManager* manager, const Book& book, const Borrower& borrower, QWidget *parent = 0 );
    ~BorrowerBooksEntry();



private slots:
    void on_returnPushButton_clicked();

    void on_renewPushButton_clicked();

    void on_recallPushButton_clicked();

private:



    Ui::BorrowerBooksEntry*         ui;
    Book                            book;
    Borrower                        borrower;
    DatabaseManager*                manager;


};

#endif // BORROWERBOOKSENTRY_H
