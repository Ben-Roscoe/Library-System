#ifndef LENDDIALOG_H
#define LENDDIALOG_H

#include <QDialog>
#include "DatabaseManager.h"

namespace Ui {
class LendDialog;
}




class LendDialog : public QDialog
{



    Q_OBJECT




public:



    explicit LendDialog( const Borrower& borrower, DatabaseManager* manager, QWidget* parent = 0 );
    ~LendDialog();




private slots:
    void on_cancelPushButton_clicked();

    void on_lendPushButton_clicked();

private:



    Ui::LendDialog*             ui;
    Borrower                    borrower;
    DatabaseManager*            manager;



};

#endif // LENDDIALOG_H
