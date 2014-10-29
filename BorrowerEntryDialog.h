#ifndef BORROWERENTRYDIALOG_H
#define BORROWERENTRYDIALOG_H

#include <QDialog>
#include "DatabaseManager.h"

namespace Ui {
class BorrowerEntryDialog;
}

class BorrowerEntryDialog : public QDialog
{
    Q_OBJECT

public:



    explicit BorrowerEntryDialog( DatabaseManager* manager, const Borrower& borrower, QWidget *parent = 0 );
    ~BorrowerEntryDialog();


    const Borrower&                 GetBorrower() const;



private slots:


    void on_updateButton_clicked();
    void on_deleteButton_clicked();


    void on_addPhoneNumberButton_clicked();

    void on_lendBookButton_clicked();

private:



    Ui::BorrowerEntryDialog*        ui;
    DatabaseManager*                manager;
    Borrower                        borrower;


    void                            AddAllBooksToWidgetList();


};

#endif // BORROWERENTRYDIALOG_H
