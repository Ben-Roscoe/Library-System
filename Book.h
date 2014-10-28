#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include <QDate>
#include <QSqlDatabase>


class Borrower;



// All info nesscessary to idenify the book.
struct BookInfo
{
    QString             id;
    QString             title;
    QString             author;

    QString             status;
};



class Book
{



public:



    // 14 days for each borrowing.
    static const int           borrowingTime        = 14;



    //
    // Type
    //
    enum class Type
    {
        Reserved,
        Reference,
        Circulation,
    };



    //
    // Status
    //
    enum class Status
    {
        Out,
        Available,
        Hold,
        Maintenance,
    };


    static QString              GetStatusString( Status status );
    static QString              GetTypeString( Type type );
    static Status              GetStringStatus( const QString& status );
    static Type                GetStringType( const QString& type );


    Book( const QString& id, const QString& title, const QString& author, const QString& subject, const QString& publisher, const QDate& publishingDate, const QString& location, Status status, float overdueFine, float cost,
          const QString& information, Type type, const QString& borrowerID = "-1", const QDate& dueDate = QDate( 0, 0, 0 ) );
    Book();

    void                Lend( const Borrower& borrower );
    void                Return();
    void                Recall();

    const QString&      GetID() const;
    const QString&      GetTitle() const;
    const QString&      GetAuthor() const;
    const QString&      GetSubject() const;
    const QString&      GetPublisher() const;
    const QString&      GetLocation() const;
    const QString&      GetInformation() const;
    const QDate&        GetPublishingDate() const;
    const QDate&        GetDueDate() const;
    float               GetOverdueFine() const;
    float               GetCost() const;
    Type                GetType() const;
    Status              GetStatus() const;
    const QString&      GetBorrowerID() const;


    void                SetTitle( const QString& newTitle );
    void                SetAuthor( const QString& newAuthor );
    void                SetSubject( const QString& newSubject );
    void                SetPublisher( const QString& newPublisher );
    void                SetLocation( const QString& newLocation );
    void                SetInformation( const QString& newInformation );
    void                SetPublishingDate( const QDate& newDate );
    void                SetDueDate( const QDate& newDate );
    void                SetOverdueFine( float newFine );
    void                SetCost( float newCost );



private:



    QString             id;
    QString             title;
    QString             author;
    QString             subject;
    QString             publisher;
    QString             location;
    QString             information;
    QString             borrowerID;
    QDate               publishingDate;
    QDate               dueDate;

    float               overdueFine;
    float               cost;

    Type                type;
    Status              status;


};

#endif // BOOK_H
