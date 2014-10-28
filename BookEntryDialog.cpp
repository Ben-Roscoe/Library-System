#include "BookEntryDialog.h"
#include "ui_BookEntryDialog.h"

#include <QMessageBox>



//
// BookEntryDialog
//
BookEntryDialog::BookEntryDialog( DatabaseManager* manager, const Book& book, QWidget *parent ) : QDialog( parent ), ui( new Ui::BookEntryDialog )
{
    ui->setupUi( this );

    this->manager   = manager;
    this->book      = book;

    // Set all the line edits.
    ui->idLineEdit->setText( book.GetID() );
    ui->titleLineEdit->setText( book.GetTitle() );
    ui->authorLineEdit->setText( book.GetAuthor() );
    ui->subjectLineEdit->setText( book.GetSubject() );
    ui->publisherLineEdit->setText( book.GetPublisher() );
    ui->publishingDateEdit->setDate( book.GetPublishingDate() );
    ui->locationLineEdit->setText( book.GetLocation() );
    ui->statusLineEdit->setText( Book::GetStatusString( book.GetStatus() ) );
    ui->overdueFineLineEdit->setText( QString::number( book.GetOverdueFine( )) );
    ui->costLineEdit->setText( QString::number( book.GetCost() ) );
    ui->dueDateEdit->setDate( book.GetDueDate() );
    ui->informationTextEdit->setText( book.GetInformation() );
    ui->typeLineEdit->setText( Book::GetTypeString( book.GetType() ) );

    // Get the borrower if there is one.
    this->manager->GetDatabase().open();
    borrower = this->manager->GetBorrowerWhere( QString( "borrowerID = %1" ).arg( book.GetBorrowerID() ) );
    this->manager->GetDatabase().close();

    // If there is a borrower, the line edits to it's attributes.
    if( borrower.GetID() != "-1" )
    {
        ui->borrowerIDLineEdit->setText( borrower.GetID() );
        ui->borrowerNameLineEdit->setText( borrower.GetName() );
        ui->borrowerAddressLineEdit->setText( borrower.GetAddress() );
        ui->borrowerFeeTotalLineEdit->setText( QString::number( borrower.GetFeeTotal() ) );
        ui->borrowerFeeHistoryLineEdit->setText( QString::number( borrower.GetFeeHistory() ) );

        // Enable push buttons.
        ui->returnPushButton->setEnabled( true );
        ui->recallPushButton->setEnabled( true );
        ui->renewPushButton->setEnabled( true );
    }
}



//
// ~BookEntryDialog
//
BookEntryDialog::~BookEntryDialog()
{
    delete ui;
}




//
// GetBook
//
const Book& BookEntryDialog::GetBook() const
{
    return book;
}



//
// on_updatePushButton_clicked
//
void BookEntryDialog::on_updatePushButton_clicked()
{
    // Make sure no important fields are empty.
    if( ui->titleLineEdit->text() == "" )
    {
        QMessageBox::information( this, "Error updating book", "A book must have a title." );
        return;
    }
    if( ui->authorLineEdit->text() == "" )
    {
        QMessageBox::information( this, "Error updating book", "A book must have an author." );
        return;
    }
    if( ui->subjectLineEdit->text() == "" )
    {
        QMessageBox::information( this, "Error updating book", "A book must have a subject." );
        return;
    }
    if( ui->publisherLineEdit->text() == "" )
    {
        QMessageBox::information( this, "Error updating book", "A book must have a publisher." );
        return;
    }
    if( ui->locationLineEdit->text() == "" )
    {
        QMessageBox::information( this, "Error updating book", "A book must have a location." );
        return;
    }
    if( ui->overdueFineLineEdit->text() == "" )
    {
        QMessageBox::information( this, "Error updating book", "A book must have an overdue fine." );
        return;
    }
    if( ui->costLineEdit->text() == "" )
    {
        QMessageBox::information( this, "Error updating book", "A book must have a cost." );
        return;
    }
    if( ui->publishingDateEdit->date() > QDate::currentDate() )
    {
        QMessageBox::information( this, "Error updating book", "A book cannot have a publishing date greater than the current date." );
        return;
    }

    // Make sure overdue fine and cost are numbers.
    {
        bool isNumber;
        ui->overdueFineLineEdit->text().toFloat( &isNumber );
        if( !isNumber )
        {
            QMessageBox::information( this, "Error updating book", "Overdue fine must be a number." );
            return;
        }
        ui->costLineEdit->text().toFloat( &isNumber );
        if( !isNumber )
        {
            QMessageBox::information( this, "Error updating book", "Cost must be a number." );
            return;
        }
    }

    // Set the book attributes.
    book.SetTitle( ui->titleLineEdit->text() );
    book.SetAuthor( ui->authorLineEdit->text() );
    book.SetSubject( ui->subjectLineEdit->text() );
    book.SetPublisher( ui->publisherLineEdit->text() );
    book.SetPublishingDate( ui->publishingDateEdit->date() );
    book.SetLocation( ui->locationLineEdit->text() );
    book.SetOverdueFine( ui->overdueFineLineEdit->text().toFloat() );
    book.SetCost( ui->costLineEdit->text().toFloat() );
    book.SetInformation( ui->informationTextEdit->toPlainText() );

    // Finally update the book in the database.
    manager->GetDatabase().open();
    manager->Update( book );
    manager->GetDatabase().close();
}



//
// on_deletePushButtom_clicked
//
void BookEntryDialog::on_deletePushButton_clicked()
{
    auto reply = QMessageBox::question( this, "Delete Book", "Are you sure you want to delete this book entry?", QMessageBox::Yes | QMessageBox::No );
    if( reply == QMessageBox::No )
    {
        return;
    }

    // Destroy the book.
    manager->GetDatabase().open();
    manager->DestroyBook( book );
    manager->GetDatabase().close();

    // Now close this form, as the entry no long exists.
    this->accept();
}



//
// on_returnPushButton_clicked
//
void BookEntryDialog::on_returnPushButton_clicked()
{
    // Return the book.
    book.Return();

    // Update the return in the database.
    manager->GetDatabase().open();
    manager->Update( book );
    manager->GetDatabase().close();

    // Set the borrower line edits to be blank.
    ui->borrowerIDLineEdit->setText( "" );
    ui->borrowerNameLineEdit->setText( "" );
    ui->borrowerAddressLineEdit->setText( "" );
    ui->borrowerFeeTotalLineEdit->setText( "" );
    ui->borrowerFeeHistoryLineEdit->setText( "" );

    // Update line edits.
    ui->statusLineEdit->setText( Book::GetStatusString( book.GetStatus() ) );
    ui->dueDateEdit->setDate( book.GetDueDate() );

    // Disable push buttons.
    ui->returnPushButton->setEnabled( false );
    ui->recallPushButton->setEnabled( false );
    ui->renewPushButton->setEnabled( false );
}



//
// on_renewPushButton_clicked
//
void BookEntryDialog::on_renewPushButton_clicked()
{

}



//
// on_recallPushButton_clicked
//
void BookEntryDialog::on_recallPushButton_clicked()
{
    // Recall the book.
    book.Recall();

    // Update the return in the database.
    manager->GetDatabase().open();
    manager->Update( book );
    manager->GetDatabase().close();

    // Update due date edit.
    ui->dueDateEdit->setDate( book.GetDueDate() );
}
