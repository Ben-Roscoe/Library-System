#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QtDebug>



// Public:



//
// MainWindow
//
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), manager( dbDriver, dbNameDriver, QString( "%1/%2" ).arg( QCoreApplication::applicationDirPath(), dbFileName ) )
{
    ui->setupUi(this);

    manager.GetDatabase().open();
    //Borrower b( manager.NewBorrower( "testBorrower", "123 dsadas", 15, 30, { "123", "1234" } ) );
    //b.SetPhoneNumber( "12345678910", 0 );
    //b.SetPhoneNumber( "909090", 1 );
    //manager.UpdatePhoneNumbers( b );
    //b.SetName( "Ben" );
    //manager.Update( b );
    //manager.NewPhoneNumber( "1570", b );
    //manager.DestroyPhoneNumber( "1570", b );
    //manager.DestroyBorrower( b );
    Book lbook = manager.NewBook( "abcd", "qqq", "qt", "lkj", QDate::currentDate().addDays( 24 ), "third floor", Book::Status::Available, 5.0f, 25.0f, "dsfafdsaf", Book::Type::Circulation );
    //book.Lend( b );
    //manager.Update( book );
    //manager.DestroyBook( book );
    QVector<Book> book = manager.GetBooksWhere( "title = 'hello'" );

    if( !book.isEmpty() )
    {
        qDebug() << QString( "Book: %1, %2, %3, %4, %5, %6, %7, %8, %9, %10, %11, %12, %13" ).arg( book[0].GetID(), book[0].GetTitle(), book[0].GetAuthor(), book[0].GetPublisher(), book[0].GetPublishingDate().toString( "yyyy.MM.dd" ), book[0].GetLocation(), Book::GetStatusString( book[0].GetStatus() ), QString::number( book[0].GetOverdueFine() ), book[0].GetDueDate().toString( "yyy.MM.dd" ) );
    }
    else
    {
        qDebug() << "Did not get book.";
    }
    manager.GetDatabase().close();
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
// on_searchButton_clicked
//
void MainWindow::on_searchButton_clicked()
{

}



//
// on_addButton_clicked
//
void MainWindow::on_addButton_clicked()
{

}
