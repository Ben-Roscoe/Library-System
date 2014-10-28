#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H


#include <QSqlDatabase>
#include <QString>
#include <QVector>

#include "Borrower.h"
#include "Book.h"
#include "BorrowerNumber.h"



class DatabaseManager
{



public:



    DatabaseManager( QString driver, QString nameDriver, QString fileLocation );


    QSqlDatabase&           GetDatabase();

    Borrower                NewBorrower( const QString& name, const QString& address, float feeTotal, float feeHistory, const QVector<QString>& phoneNumbers ) const;
    void                    DestroyBorrower( const Borrower& borrower ) const;

    Book                    NewBook( const QString& title, const QString& author, const QString& subject, const QString& publisher, const QDate& publishingDate,
                                     const QString& location, Book::Status status, float overdueFine, float cost, const QString& information, Book::Type type ) const;
    void                    DestroyBook( const Book& book ) const;

    BorrowerNumber          NewPhoneNumber( const QString& number, Borrower& borrower ) const;
    void                    DestroyPhoneNumber( const BorrowerNumber& number ) const;

    void                    Update( const Borrower& borrower ) const;
    void                    Update( const Book& book ) const;
    void                    Update( const BorrowerNumber& number ) const;
    void                    UpdatePhoneNumbers( const Borrower& borrower ) const;

    Borrower                GetBorrowerWhere( const QString& sqlWhere ) const;
    Book                    GetBookWhere( const QString& sqlWhere ) const;
    QVector<BorrowerNumber> GetNumbersWhere( const QString& sqlWhere ) const;
    QVector<Book>           GetBooksWhere( const QString& sqlWhere ) const;


    QString                 DateToString( const QDate& date ) const;
    QDate                   StringToDate( const QString& str ) const;


private:



    const char* const       dateFormat = "yyyy.MM.dd";


    QString                 driver;
    QString                 nameDriver;
    QString                 fileLocation;



    QSqlDatabase            database;


};

#endif // DATABASEMANAGER_H
