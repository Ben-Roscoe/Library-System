#include "PhoneNumberEntry.h"
#include "ui_PhoneNumberEntry.h"

#include <QMessageBox>



//
// PhoneNumberEntry
//
PhoneNumberEntry::PhoneNumberEntry( const BorrowerNumber& borrowerNumber, DatabaseManager* manager, QWidget *parent ) : QWidget( parent ), ui( new Ui::PhoneNumberEntry )
{
    ui->setupUi(this);

    this->manager               = manager;
    this->borrowerNumber        = borrowerNumber;

    // Set the line edits to initial values.
    ui->idLineEdit->setText( borrowerNumber.GetID() );
    ui->borrowerIDLineEdit->setText( borrowerNumber.GetID() );
    ui->numberLineEdit->setText( borrowerNumber.GetPhoneNumber() );
}



//
// ~PhoneNumberEntry
//
PhoneNumberEntry::~PhoneNumberEntry()
{
    delete ui;
}



//
// on_updateButton_clicked
//
void PhoneNumberEntry::on_updateButton_clicked()
{
    // Set the number attributes.
    borrowerNumber.SetPhoneNumber( ui->numberLineEdit->text() );

    // Update the borrower in the database.
    manager->GetDatabase().open();
    manager->Update( borrowerNumber );
    manager->GetDatabase().close();
}



//
// on_delete_button_clicked
//
void PhoneNumberEntry::on_deleteButton_clicked()
{
    // Check for comfirmation.
    auto reply = QMessageBox::question( this, "Delete Phone Number", "Are you sure you want to delete this phone number entry?", QMessageBox::Yes | QMessageBox::No );
    if( reply == QMessageBox::No )
    {
        return;
    }

    // Delete the number from the database.
    manager->GetDatabase().open();
    manager->DestroyPhoneNumber( borrowerNumber );
    manager->GetDatabase().close();

    // Close this form.
    close();
}
