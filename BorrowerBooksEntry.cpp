#include "BorrowerBooksEntry.h"
#include "ui_BorrowerBooksEntry.h"




//
// BorrowerBooksEntry
//
BorrowerBooksEntry::BorrowerBooksEntry( DatabaseManager* manager, const Book& book, QWidget *parent ) : QWidget(parent), ui(new Ui::BorrowerBooksEntry)
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
}



//
// ~BorrowerBooksEntry
//
BorrowerBooksEntry::~BorrowerBooksEntry()
{
    delete ui;
}




//
// on_returnPushButton_clicked
//
void BorrowerBooksEntry::on_returnPushButton_clicked()
{
    // Return the book.
    book.Return();

    // Update the return in the database.
    manager->GetDatabase().open();
    manager->Update( book );
    manager->GetDatabase().close();

    // Book is no longer borrower to this borrower, close the form.
    close();
}




//
// on_renewPushButton_clicked
//
void BorrowerBooksEntry::on_renewPushButton_clicked()
{

}




//
// on_recallPushButton_clicked
//
void BorrowerBooksEntry::on_recallPushButton_clicked()
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
