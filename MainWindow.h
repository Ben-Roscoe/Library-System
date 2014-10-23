#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Borrower.h"
#include "DatabaseManager.h"


namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:



    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:


    void on_actionE_xit_triggered();



    void on_searchButton_clicked();

    void on_addButton_clicked();

private:



    const char* const       dbDriver      =  "QODBC";
    const char* const       dbNameDriver  =  "{Microsoft Access Driver (*.mdb, *.accdb)}";
    const char* const       dbFileName    =  "libraryDatabase.accdb";


    Ui::MainWindow*         ui;
    DatabaseManager         manager;




};

#endif // MAINWINDOW_H
