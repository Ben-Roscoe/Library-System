#ifndef BOOKENTRYDIALOG_H
#define BOOKENTRYDIALOG_H

#include <QDialog>
#include "DatabaseManager.h"

namespace Ui {
class BookEntryDialog;
}

class BookEntryDialog : public QDialog
{



    Q_OBJECT



public:



    explicit BookEntryDialog( DatabaseManager* manager, const Book& book, QWidget *parent = 0 );
    ~BookEntryDialog();


    const Book&                     GetBook() const;


private slots:
    void on_updatePushButton_clicked();

    void on_deletePushButton_clicked();

    void on_returnPushButton_clicked();

    void on_renewPushButton_clicked();

    void on_recallPushButton_clicked();

private:



    Ui::BookEntryDialog*            ui;
    DatabaseManager*                manager;
    Book                            book;
    Borrower                        borrower;


};

#endif // BOOKENTRYDIALOG_H
