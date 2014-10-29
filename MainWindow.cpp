#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "BorrowerEntryDialog.h"
#include "BookEntryDialog.h"

#include <QtDebug>
#include <QLayout>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>



// Public:



//
// MainWindow
//
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), manager( dbDriver, dbNameDriver, QString( "%1/%2" ).arg( QCoreApplication::applicationDirPath(), dbFileName ) )
{
    ui->setupUi(this);

    ui->listWidgetBook->setUniformItemSizes( true );
    ui->listWidgetBorrower->setUniformItemSizes( true );
    //ui->searchResultsArea->setLayout( new QGridLayout() );
    //ui->searchResultsArea->setWidget( ui->scrollAreaWidgetContents_2 );
    //ui->scrollAreaWidgetContents_2->layout()->setSizeConstraint( QLayout::SetFixedSize );

   // manager.GetDatabase().open();
   // for( int i = 0; i < 990000; i++ )
  //  {
     //   manager.NewBook( "testBook", "abcd", "qwerty", "lkjh", QDate::currentDate(), "1234", Book::Status::Available, 15.0f, 50.0f, "good book", Book::Type::Circulation );
//        manager.NewBorrower( "testBorrower", "1343 5fdf", 15.0f, 45.0f, { "123", "1234", "dsadsa" } );
  //  }
  //  manager.GetDatabase().close();
}



//
// ~MainWindow
//
MainWindow::~MainWindow()
{
    delete ui;
}



// Private:




//
// on_actionE_xit_triggered
//
void MainWindow::on_actionE_xit_triggered()
{
    // Close this form.
    close();
}



//
// on_SearchButtonBorrower_clicked
//
void MainWindow::on_searchButtonBorrower_clicked()
{
    ui->listWidgetBorrower->clear();

    manager.GetDatabase().open();

    // Build the where part of the query.
    QString                     where = "";
    if( ui->borrowerIDLineEdit->text() != "" )
    {
        bool ok = false;
        ui->borrowerIDLineEdit->text().toInt( &ok );

        if( ok )
        {
            where += QString( "borrowerID = %1 AND " ).arg( ui->borrowerIDLineEdit->text() );
        }
    }
    if( ui->borrowerNameLineEdit->text() != "" )
    {
        where += QString( "fullName LIKE '%%1%' AND " ).arg( ui->borrowerNameLineEdit->text() );
    }
    if( ui->borrowerAddressLineEdit->text() != "" )
    {
        where += QString( "address LIKE '%%1%' AND " ).arg( ui->borrowerAddressLineEdit->text() );
    }
    if( ui->borrowerFeeTotalLabel->text() != "" )
    {
        bool ok = false;
        ui->borrowerFeeHistoryLineEdit->text().toFloat( &ok );

        if( ok )
        {
            where += QString( "feeTotal = %1 AND " ).arg( ui->borrowerFeeTotalLineEdit->text() );
        }
    }
    if( ui->borrowerFeeHistoryLineEdit->text() != "" )
    {
        bool ok = false;
        ui->borrowerFeeHistoryLineEdit->text().toFloat( &ok );

        if( ok )
        {
            where += QString( "feeHistory = %1 AND " ).arg( ui->borrowerFeeHistoryLineEdit->text() );
        }
    }

    // Remove the AND off the end, because it's easier than checking each one.
    if( where.endsWith( "AND " ) )
    {
        where.remove( where.size() - 4, 4 );
    }

    // Run a select which will allow us to construct new borrower objects.
    QSqlQuery                   query;
    query.setForwardOnly( true );
    query.prepare( QString( "SELECT borrowerID, fullName, address FROM Borrower " ) + ( where != "" ? QString( "WHERE %1" ).arg( where ) : "" ) );
    if( !query.exec() )
    {
        qDebug() << "Get borrowers where error: " << query.lastError().text();
        return;
    }

    // We will add the results of the query into the results vector row by row until we run out.
    while( query.next() )
    {
        QListWidgetItem*            item = new QListWidgetItem( QString( "ID: " ) + query.value( 0 ).toString() + QString( ", Name: " ) + query.value( 1 ).toString() + QString( ", Address: " ) + query.value( 2 ).toString() );
        item->setData( Qt::UserRole, query.value( 0 ).toString() );
        ui->listWidgetBorrower->addItem( item );
    }
    manager.GetDatabase().close();

    // Display the amount of results.
    QMessageBox::information( this, "Search", QString( "Search returned %1 result(s)" ).arg( QString::number( ui->listWidgetBorrower->count() ) ) );
}




//
// on_listWidgetBorrower_itemDoubleClicked
//
void MainWindow::on_listWidgetBorrower_itemDoubleClicked( QListWidgetItem* item )
{
    manager.GetDatabase().open();
    Borrower borrower = manager.GetBorrowerWhere( QString( "borrowerID = %1" ).arg( item->data( Qt::UserRole ).toString() ) );
    manager.GetDatabase().close();


    // Create the dialog.
    BorrowerEntryDialog        borrowerEntry{ &manager, borrower, this };

    // If the dialog was "accepted", the entry was deleted, so remove it from the list.
    if( borrowerEntry.exec() == QDialog::Accepted )
    {
        // The item will remove itself from the list in it's destructor.
        delete item;
        return;
    }

    // Reset the text incase the borrower has been updated.
    borrower = borrowerEntry.GetBorrower();
    item->setText( QString( "ID: " ) + borrower.GetID() + QString( ", Name: " ) + borrower.GetName() + QString( ", Address: " ) + borrower.GetAddress() );
}



//
// on_searchButtonBook_clicked
//
void MainWindow::on_searchButtonBook_clicked()
{
    ui->listWidgetBook->clear();

    manager.GetDatabase().open();

    // Build the where part of the query.
    QString                     where = QString( "(status = '%1' " ).arg( ui->bookStatusComboBox->currentText() );
    where += QString( "AND type = '%1' " ).arg( ui->bookTypeComboBox->currentText() );

    if( ui->bookIDLineEdit->text() != "" )
    {
        where += QString( "AND bookID = %1 " ).arg( ui->bookIDLineEdit->text() );
    }
    if( ui->bookTitleLineEdit->text() != "" )
    {
        where += QString( "AND title LIKE '%%1%' " ).arg( ui->bookTitleLineEdit->text() );
    }
    if( ui->bookAuthorLineEdit->text() != "" )
    {
        where += QString( "AND author LIKE '%%1%' " ).arg( ui->bookAuthorLineEdit->text() );
    }
    if( ui->bookSubjectLineEdit->text() != "" )
    {
        where += QString( "AND subject LIKE '%%1%' " ).arg( ui->bookSubjectLineEdit->text() );
    }
    if( ui->bookPublisherLineEdit->text() != "" )
    {
        where += QString( "AND publisher LIKE '%%1%' " ).arg( ui->bookPublisherLineEdit->text() );
    }
    if( ui->bookLocationLineEdit->text() != "" )
    {
        where += QString( "AND location LIKE '%%1%' " ).arg( ui->bookLocationLineEdit->text() );
    }
    if( ui->bookOverdueFineLineEdit->text() != "" )
    {
        bool ok = false;
        ui->bookOverdueFineLineEdit->text().toFloat( &ok );

        if( ok )
        {
            where += QString( "AND overdueFine = %1 " ).arg( ui->bookOverdueFineLineEdit->text() );
        }
    }
    if( ui->bookCostLineEdit->text() != "" )
    {
        bool ok = false;
        ui->bookCostLineEdit->text().toFloat( &ok );

        if( ok )
        {
            where += QString( "AND cost = %1 " ).arg( ui->bookCostLineEdit->text() );
        }
    }
    if( ui->bookInformationLineEdit->text() != "" )
    {
        where += QString( "AND information LIKE '%%1%'" ).arg( ui->bookInformationLineEdit->text() );
    }
    where += QString( ") OR publishingDate = %1 " ).arg( manager.DateToString( ui->bookPublisingDateEdit->date() ) );

    QSqlQuery                   query;
    query.setForwardOnly( true );
    query.prepare( QString( "SELECT bookID, title, author, status FROM Book WHERE %1" ).arg( where ) );
    if( !query.exec() )
    {
        qDebug() << "Get books where error: " << query.lastError().text();
        return;
    }

    ui->listWidgetBook->setUpdatesEnabled( false );
    while( query.next() )
    {
        QListWidgetItem* item = new QListWidgetItem( QString( "ID: %1, Title: %2, Author: %3, Status: %4 " ).arg( query.value( 0 ).toString(), query.value( 1 ).toString(),
                                                                        query.value( 2 ).toString(), query.value( 3 ).toString() ) );
        item->setData( Qt::UserRole, query.value( 0 ).toString() );
        ui->listWidgetBook->addItem( item );
    }
    ui->listWidgetBook->setUpdatesEnabled( true );
    manager.GetDatabase().close();


    // Display the amount of results.
    QMessageBox::information( this, "Search", QString( "Search returned %1 result(s)" ).arg( QString::number( ui->listWidgetBook->count() ) ) );
}




//
// on_addButtonBook_clicked
//
void MainWindow::on_addButtonBook_clicked()
{
    // Make sure no important fields are empty.
    if( ui->bookTitleLineEdit->text() == "" )
    {
        QMessageBox::information( this, "Error adding book", "A book cannot be added without a title." );
        return;
    }
    if( ui->bookAuthorLineEdit->text() == "" )
    {
        QMessageBox::information( this, "Error adding book", "A book cannot be added without an author." );
        return;
    }
    if( ui->bookSubjectLineEdit->text() == "" )
    {
        QMessageBox::information( this, "Error adding book", "A book cannot be added without a subject." );
        return;
    }
    if( ui->bookPublisherLineEdit->text() == "" )
    {
        QMessageBox::information( this, "Error adding book", "A book cannot be added without a publisher." );
        return;
    }
    if( ui->bookLocationLineEdit->text() == "" )
    {
        QMessageBox::information( this, "Error adding book", "A book cannot be added without a location." );
        return;
    }
    if( ui->bookOverdueFineLineEdit->text() == "" )
    {
        QMessageBox::information( this, "Error adding book", "A book cannot be added without an overdue fine." );
        return;
    }
    if( ui->bookCostLineEdit->text() == "" )
    {
        QMessageBox::information( this, "Error adding book", "A book cannot be added without a cost." );
        return;
    }
    if( ui->bookPublisingDateEdit->date() > QDate::currentDate() )
    {
        QMessageBox::information( this, "Error adding book", "A book cannot have a publishing date greater than the current date." );
        return;
    }

    // Make sure overdue fine and cost are numbers.
    {
        bool isNumber;
        ui->bookOverdueFineLineEdit->text().toFloat( &isNumber );
        if( !isNumber )
        {
            QMessageBox::information( this, "Error adding book", "Overdue fine must be a number." );
            return;
        }
        ui->bookCostLineEdit->text().toFloat( &isNumber );
        if( !isNumber )
        {
            QMessageBox::information( this, "Error adding book", "Cost must be a number." );
            return;
        }
    }


    // Ask for confirmation. If yes, add the new book to the database.
    QString         question = QString( "You are about to add a book with:\n\nTitle: %1\nAuthor: %2\nSubject: %3\nPublisher: %4\nPublishing Date: %5\nLocation: %6\nStatus: %7\nOverdue Fine: $%8\nCost: $%9\nType: %10\n\n Is this correct?" )
                                        .arg( ui->bookTitleLineEdit->text(), ui->bookAuthorLineEdit->text(), ui->bookSubjectLineEdit->text(), ui->bookPublisherLineEdit->text(),
                                              ui->bookPublisingDateEdit->date().toString(), ui->bookLocationLineEdit->text(), ui->bookStatusComboBox->currentText(),
                                              ui->bookOverdueFineLineEdit->text(), ui->bookCostLineEdit->text() ).arg( ui->bookTypeComboBox->currentText() );
    auto result = QMessageBox::question( this, "Confirm addition", question, QMessageBox::Yes | QMessageBox::No );
    if( result == QMessageBox::Yes )
    {
        manager.GetDatabase().open();
        manager.NewBook( ui->bookTitleLineEdit->text(), ui->bookAuthorLineEdit->text(), ui->bookSubjectLineEdit->text(), ui->bookPublisherLineEdit->text(),
                             ui->bookPublisingDateEdit->date(), ui->bookLocationLineEdit->text(), Book::GetStringStatus( ui->bookStatusComboBox->currentText() ),
                             ui->bookOverdueFineLineEdit->text().toFloat(), ui->bookCostLineEdit->text().toFloat(), ui->bookInformationLineEdit->text(),
                             Book::GetStringType( ui->bookTypeComboBox->currentText() ) );
        manager.GetDatabase().close();
    }
}




//
// on_addButtonBorrower
//
void MainWindow::on_addButtonBorrower_clicked()
{
    // Make sure name and address are not empty.
    if( ui->borrowerNameLineEdit->text() == "" )
    {
        QMessageBox::information( this, "Error adding borrower", "A borrower cannot be added without a name." );
        return;
    }
    if( ui->borrowerAddressLineEdit->text() == "" )
    {
        QMessageBox::information( this, "Error adding borrower", "A borrower cannot be added without an address." );
        return;
    }
    if( ui->borrowerFeeTotalLabel->text() == "" )
    {
        QMessageBox::information( this, "Error adding borrower", "A borrower cannot be added without a fee total." );
        return;
    }
    if( ui->borrowerFeeHistoryLineEdit->text() == "" )
    {
        QMessageBox::information( this, "Error adding borrower", "A borrower cannot be added without a fee history." );
        return;
    }


    // Make sure overdue fine and cost are numbers.
    {
        bool isNumber;
        ui->borrowerFeeTotalLineEdit->text().toFloat( &isNumber );
        if( !isNumber )
        {
            QMessageBox::information( this, "Error adding borrower", "Fee total must be a number." );
            return;
        }
        ui->borrowerFeeHistoryLineEdit->text().toFloat( &isNumber );
        if( !isNumber )
        {
            QMessageBox::information( this, "Error adding borrower", "Fee history must be a number." );
            return;
        }
    }

    // Ask for confirmation. If yes, add the new borrower to the database.
    QString         question = QString( "You are about to add a Borrower with:\n\nName: %1\nAddress: %2\nFee Total: $%3\nFee History: $%4\n\n Is this correct?" )
                                        .arg( ui->borrowerNameLineEdit->text(), ui->borrowerAddressLineEdit->text(), ui->borrowerFeeTotalLineEdit->text(), ui->borrowerFeeHistoryLineEdit->text() );
    auto result = QMessageBox::question( this, "Confirm addition", question, QMessageBox::Yes | QMessageBox::No );
    if( result == QMessageBox::Yes )
    {
        manager.GetDatabase().open();
        manager.NewBorrower( ui->borrowerNameLineEdit->text(), ui->borrowerAddressLineEdit->text(), ui->borrowerFeeTotalLineEdit->text().toFloat(), ui->borrowerFeeHistoryLineEdit->text().toFloat(), QVector<QString>() );
        manager.GetDatabase().close();
    }
}




//
// on_listWidgetBook_itemDoubleClicked
//
void MainWindow::on_listWidgetBook_itemDoubleClicked( QListWidgetItem* item )
{
    manager.GetDatabase().open();
    Book book = manager.GetBookWhere( QString( "bookID = %1" ).arg( item->data( Qt::UserRole ).toString() ) );
    manager.GetDatabase().close();

    // Create the dialog.
    BookEntryDialog        bookEntry{ &manager, book, this };

    // If the dialog was "accepted", the entry was deleted, so remove it from the list.
    if( bookEntry.exec() == QDialog::Accepted )
    {
        // The item will remove itself from the list in it's destructor.
        delete item;
        return;
    }

    // Reset the text incase the book has been updated.
    book = bookEntry.GetBook();
    item->setText( QString( "ID: %1, Title: %2, Author: %3, Status: %4" ).arg( book.GetID(), book.GetTitle(), book.GetAuthor(), Book::GetStatusString( book.GetStatus() ) ) );
}
