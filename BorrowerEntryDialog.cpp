#include "BorrowerEntryDialog.h"
#include "ui_BorrowerEntryDialog.h"
#include "PhoneNumberEntry.h"
#include "BorrowerBooksEntry.h"
#include "LendDialog.h"

#include <QLayout>
#include <QMessageBox>



//
// BorrowerEntryDialog
//
BorrowerEntryDialog::BorrowerEntryDialog( DatabaseManager* manager, const Borrower& borrower, QWidget *parent ) : QDialog(parent), ui(new Ui::BorrowerEntryDialog)
{
    ui->setupUi(this);

    this->manager       = manager;
    this->borrower      = borrower;

    // Set the line edits to initial values.
    ui->idLineEdit->setText( borrower.GetID() );
    ui->nameLineEdit->setText( borrower.GetName() );
    ui->addressLineEdit->setText( borrower.GetAddress() );
    ui->feeTotalLineEdit->setText( QString::number( borrower.GetFeeTotal() ) );
    ui->feeHistoryLineEdit->setText( QString::number( borrower.GetFeeHistory() ) );

    // Set up the numbers scroll area.
    ui->scrollArea->setWidget( ui->scrollAreaWidgetContents );
    ui->scrollAreaWidgetContents->setLayout( new QVBoxLayout() );
    for( const BorrowerNumber& number : borrower.GetPhoneNumbers() )
    {
        ui->scrollAreaWidgetContents->layout()->addWidget( new PhoneNumberEntry( number, manager ) );
    }

    AddAllBooksToWidgetList();
}



//
// ~BorrowerEntryDialog
//
BorrowerEntryDialog::~BorrowerEntryDialog()
{
    delete ui;
}




//
// GetBorrower
//
const Borrower&BorrowerEntryDialog::GetBorrower() const
{
    return borrower;
}



//
// on_updateButton_clicked
//
void BorrowerEntryDialog::on_updateButton_clicked()
{
    if( ui->nameLineEdit->text() == "" )
    {
        QMessageBox::information( this, "Error updating borrower", "A borrower must have a name." );
        return;
    }
    if( ui->addressLineEdit->text() == "" )
    {
        QMessageBox::information( this, "Error updating borrower", "A borrower must have an address." );
        return;
    }

    // Set the borrower's new attributes.
    borrower.SetName( ui->nameLineEdit->text() );
    borrower.SetAddress( ui->addressLineEdit->text() );

    // Update in the database.
    manager->GetDatabase().open();
    manager->Update( borrower );
    manager->GetDatabase().close();
}



//
// on_deleteButton_clicked
//
void BorrowerEntryDialog::on_deleteButton_clicked()
{
    // Check for comfirmation.
    auto reply = QMessageBox::question( this, "Delete Borrower", "Are you sure you want to delete this borrower entry?", QMessageBox::Yes | QMessageBox::No );
    if( reply == QMessageBox::No )
    {
        return;
    }

    // Destroy the borrower.
    manager->GetDatabase().open();
    manager->DestroyBorrower( borrower );
    manager->GetDatabase().close();

    // Now close this form, as the entry no longer exists.
    this->accept();
}



//
// on_addPhoneNumberButton_clicked
//
void BorrowerEntryDialog::on_addPhoneNumberButton_clicked()
{
    if( ui->newPhoneNumberLineEdit->text() == "" )
    {
        QMessageBox::information( this, "Error adding phone number.", "You must enter a phone number to add." );
        return;
    }

    manager->GetDatabase().open();
    // Create the new number in the database and then add the new form.
    BorrowerNumber number = manager->NewPhoneNumber( ui->newPhoneNumberLineEdit->text(), borrower );

    // Number is not valid.
    if( number.GetID() == "" )
    {
        QMessageBox::information( this, "Error adding phone number.", "There was a problem adding the phone number. The number is most likely already present on this borrower." );
        return;
    }
    manager->GetDatabase().close();

    // Number is valid, add the form.
    ui->scrollAreaWidgetContents->layout()->addWidget( new PhoneNumberEntry( number, manager ) );
}



//
// on_lendBookButton_clicked
//
void BorrowerEntryDialog::on_lendBookButton_clicked()
{
    LendDialog          lendDialog( borrower, manager, this );
    lendDialog.exec();

    AddAllBooksToWidgetList();
}



//
// AddAllBooksToWidgetList
//
void BorrowerEntryDialog::AddAllBooksToWidgetList()
{
    if( ui->booksScrollAreaContents->layout() != nullptr )
    {
        delete ui->booksScrollAreaContents->layout();
    }
    ui->bookScrollArea->setWidget( ui->booksScrollAreaContents );
    ui->booksScrollAreaContents->setLayout( new QVBoxLayout() );

    // Find all books that are borrowered by this borrowered and put them in the borrower scroll area.
    manager->GetDatabase().open();
    QVector<Book> books = manager->GetBooksWhere( QString( "borrowerID = %1" ).arg( borrower.GetID() ) );
    manager->GetDatabase().close();

    for( const Book& book : books )
    {
        ui->booksScrollAreaContents->layout()->addWidget( new BorrowerBooksEntry( manager, book, borrower ) );
    }
}
