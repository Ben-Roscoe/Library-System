#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "BorrowerEntry.h"

#include <QtDebug>
#include <QLayout>



// Public:



//
// MainWindow
//
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), manager( dbDriver, dbNameDriver, QString( "%1/%2" ).arg( QCoreApplication::applicationDirPath(), dbFileName ) )
{
    ui->setupUi(this);

    //ui->searchResultsArea->setLayout( new QGridLayout() );
    ui->searchResultsArea->setWidget( ui->scrollAreaWidgetContents_2 );
    //ui->scrollAreaWidgetContents_2->layout()->setSizeConstraint( QLayout::SetFixedSize );
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
    manager.GetDatabase().open();
    QVector<Borrower>       borrowers       = manager.GetBorrowersWhere( "fullName = 'testBorrower'" );
    manager.GetDatabase().close();

    for( const Borrower& borrower : borrowers )
    {
        ui->scrollAreaWidgetContents_2->layout()->addWidget( new BorrowerEntry( &manager, borrower ) );
    }
}



//
// on_addButton_clicked
//
void MainWindow::on_addButton_clicked()
{

}
