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

    void                    NewPhoneNumber( const QString& number, Borrower& borrower ) const;
    void                    DestroyPhoneNumber( const QString& number, Borrower& borrower ) const;

    void                    Update( const Borrower& borrower ) const;
    void                    Update( const Book& book ) const;
    void                    Update( const Borrower& borrower, const QString& number ) const;
    void                    Update( const Borrower& borrower, int i ) const;
    void                    UpdatePhoneNumbers( const Borrower& borrower ) const;

    QVector<Borrower>       GetBorrowersWhere( const QString& sqlWhere ) const;
    QVector<Book>           GetBooksWhere( const QString& sqlWhere ) const;
    QVector<BorrowerNumber> GetNumbersWhere( const QString& sqlWhere ) const;



private:


    const char* const       dateFormat = "yyyy.MM.dd";


    QString                 driver;
    QString                 nameDriver;
    QString                 fileLocation;



    QSqlDatabase            database;



    QString                 DateToString( const QDate& date ) const;
    QDate                   StringToDate( const QString& str ) const;


};

#endif // DATABASEMANAGER_H
