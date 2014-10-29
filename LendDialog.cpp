#include "LendDialog.h"
#include "ui_LendDialog.h"

#include <QMessageBox>



//
// LendDialog
//
LendDialog::LendDialog( const Borrower& borrower, DatabaseManager* manager, QWidget* parent ) : QDialog(parent), ui(new Ui::LendDialog)
{
    ui->setupUi(this);


    this->borrower  = borrower;
    this->manager   = manager;

    ui->idLineEdit->setText( borrower.GetID() );
    ui->nameLineEdit->setText( borrower.GetName() );
    ui->addressLineEdit->setText( borrower.GetAddress() );
    ui->feeTotalLineEdit->setText( QString::number( borrower.GetFeeTotal() ) );
    ui->feeHistoryLineEdit->setText( QString::number( borrower.GetFeeHistory() ) );
}



//
// ~LendDialog
//
LendDialog::~LendDialog()
{
    delete ui;
}



//
// on_cancelPushButton_clicked
//
void LendDialog::on_cancelPushButton_clicked()
{
    // Close the form.
    close();
}



//
// on_lendPushButton_clicked
//
void LendDialog::on_lendPushButton_clicked()
{
    // Check if the id is a number.
    {
        bool ok = false;
        ui->bookIDLineEdit->text().toInt( &ok );
        if( !ok )
        {
            QMessageBox::information( this, "Error lending book", "The id entered is not in a valid format. The id must be a number." );
            return;
        }
    }

    // Find a book with this id.
    manager->GetDatabase().open();
    Book        book = manager->GetBookWhere( QString( "bookID = %1" ).arg( ui->bookIDLineEdit->text() ) );
    manager->GetDatabase().close();

    if( book.GetID() == "-1" )
    {
        QMessageBox::information( this, "Error lending book", "A book with that id was not found." );
        return;
    }
    if( book.GetBorrowerID() != "-1" )
    {
        QMessageBox::information( this, "Error lending book", "This book is out." );
        return;
    }

    // If everything is okay, lend the book.
    book.Lend( borrower );
    manager->GetDatabase().open();
    manager->Update( book );
    manager->GetDatabase().close();

    // Inform the user of the lending.
    QMessageBox::information( this, "Lending successful", QString( "The book \"%1\" with ID %2 was lent to this borrower." ).arg( book.GetTitle(), book.GetID() ) );
}
