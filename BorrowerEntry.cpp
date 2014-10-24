#include "BorrowerEntry.h"
#include "ui_BorrowerEntry.h"
#include "PhoneNumberEntry.h"

#include <QLayout>
#include <QMessageBox>



//
// BorrowerEntry
//
BorrowerEntry::BorrowerEntry( DatabaseManager* manager, const Borrower& borrower, QWidget *parent ) : QWidget(parent), ui(new Ui::BorrowerEntry)
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
}



//
// ~BorrowerEntry
//
BorrowerEntry::~BorrowerEntry()
{
    delete ui;
}



//
// on_updateButton_clicked
//
void BorrowerEntry::on_updateButton_clicked()
{
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
void BorrowerEntry::on_deleteButton_clicked()
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
    close();
}
