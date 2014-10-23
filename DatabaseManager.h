#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H


#include <QSqlDatabase>
#include <QString>
#include <QVector>

#include "Borrower.h"
#include "Book.h"



class DatabaseManager
{



public:



    DatabaseManager( QString driver, QString nameDriver, QString fileLocation );


    QSqlDatabase&           GetDatabase();

    Borrower                NewBorrower( const QString& name, const QString& address, float feeTotal, float feeHistory, const QVector<QString>& phoneNumbers );
    void                    DestroyBorrower( const Borrower& borrower );

    Book                    NewBook( const QString& title, const QString& author, const QString& subject, const QString& publisher, const QDate& publishingDate,
                                     const QString& location, Book::Status status, float overdueFine, float cost, const QString& information, Book::Type type );
    void                    DestroyBook( const Book& book );

    void                    NewPhoneNumber( const QString& number, Borrower& borrower );
    void                    DestroyPhoneNumber( const QString& number, Borrower& borrower );

    void                    Update( const Borrower& borrower );
    void                    Update( const Book& book );
    void                    Update( const Borrower& borrower, const QString& number );
    void                    Update( const Borrower& borrower, int i );
    void                    UpdatePhoneNumbers( const Borrower& borrower );



private:


    const char* const       dateFormat = "yyyy.MM.dd";


    QString                 driver;
    QString                 nameDriver;
    QString                 fileLocation;



    QSqlDatabase            database;



    QString                 DateToString( const QDate& date ) const;


};

#endif // DATABASEMANAGER_H
