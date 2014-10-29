#include "Book.h"
#include "Borrower.h"



// Public:



//
// GetStatusString
//
QString Book::GetStatusString( Status status )
{
    if( status == Status::Out )
    {
        return "Out";
    }
    else if( status == Status::Available )
    {
        return "Available";
    }
    else if( status == Status::Hold )
    {
        return "Hold";
    }
    return "Maintenance";
}



//
// GetTypeString
//
QString Book::GetTypeString( Type type )
{
    if( type == Type::Reserved )
    {
        return "Reserved";
    }
    else if( type == Type::Reference )
    {
        return "Reference";
    }
    return "Circulation";
}



//
// GetStringStatus
//
Book::Status Book::GetStringStatus( const QString& status )
{
    QString     lower   = status.toLower();

    if( lower == "out" )
    {
        return Status::Out;
    }
    else if( lower == "available" )
    {
        return Status::Available;
    }
    else if( lower == "hold" )
    {
        return Status::Hold;
    }
    return Status::Maintenance;
}



//
// GetStringType
//
Book::Type Book::GetStringType( const QString& type )
{
    QString     lower   = type.toLower();

    if( lower == "reserved" )
    {
        return Type::Reserved;
    }
    else if( type == "reference" )
    {
        return Type::Reference;
    }
    return Type::Circulation;
}




//
// Book
//
Book::Book( const QString& id, const QString& title, const QString& author, const QString& subject,
            const QString& publisher, const QDate& publishingDate, const QString& location, Status status,
            float overdueFine, float cost, const QString& information, Type type, const QString& borrowerID, const QDate& dueDate )
{
    this->id                = id;
    this->title             = title;
    this->author            = author;
    this->subject           = subject;
    this->publisher         = publisher;
    this->publishingDate    = publishingDate;
    this->location          = location;
    this->status            = status;
    this->overdueFine       = overdueFine;
    this->cost              = cost;
    this->information       = information;
    this->type              = type;
    this->borrowerID        = borrowerID;
    this->dueDate           = dueDate;
}



//
// Book
//
Book::Book()
{
    this->id                = "-1";
    this->borrowerID        = "-1";
}



//
// Lend
//
void Book::Lend( const Borrower& borrower )
{
    // The book is out.
    status      = Status::Out;

    // Set the due date to now + 14 days.
    dueDate     = QDate::currentDate();
    dueDate.addDays( borrowingTime );

    // This is who borrowed it.
    borrowerID = borrower.GetID();
}



//
// Return
//
void Book::Return()
{
    // The book is no longer out.
    status      = Status::Available;

    // Set the due date to 0.
    dueDate = QDate::currentDate();

    // Remove the borrower.
    borrowerID = "-1";
}



//
// Recall
//
void Book::Recall()
{
    if( borrowerID != "-1" )
    {
        dueDate = dueDate.addDays( borrowingTime );
    }
}



//
// GetID
//
const QString& Book::GetID() const
{
    return id;
}



//
// GetTitle
//
const QString& Book::GetTitle() const
{
    return title;
}



//
// GetAuthor
//
const QString& Book::GetAuthor() const
{
    return author;
}



//
// GetSubject
//
const QString& Book::GetSubject() const
{
    return subject;
}



//
// GetPublisher
//
const QString& Book::GetPublisher() const
{
    return publisher;
}



//
// GetLocation
//
const QString& Book::GetLocation() const
{
    return location;
}



//
// GetInformation
//
const QString& Book::GetInformation() const
{
    return information;
}



//
// GetPublishingDate
//
const QDate& Book::GetPublishingDate() const
{
    return publishingDate;
}



//
// GetDueDate
//
const QDate& Book::GetDueDate() const
{
    return dueDate;
}



//
// GetOverdueFine
//
float Book::GetOverdueFine() const
{
    return overdueFine;
}



//
// GetCost
//
float Book::GetCost() const
{
    return cost;
}



//
// GetType
//
Book::Type Book::GetType() const
{
    return type;
}



//
// GetStatus
//
Book::Status Book::GetStatus() const
{
    return status;
}



//
// GetBorrower
//
const QString& Book::GetBorrowerID() const
{
    return borrowerID;
}




//
// SetTitle
//
void Book::SetTitle( const QString& newTitle )
{
    title = newTitle;
}



//
// SetAuthor
//
void Book::SetAuthor( const QString& newAuthor )
{
    author = newAuthor;
}



//
// SetSubject
//
void Book::SetSubject( const QString& newSubject )
{
    subject = newSubject;
}



//
// SetPublisher
//
void Book::SetPublisher( const QString& newPublisher )
{
    publisher = newPublisher;
}



//
// SetLocation
//
void Book::SetLocation( const QString& newLocation )
{
    location = newLocation;
}



//
// SetInformation
//
void Book::SetInformation( const QString& newInformation )
{
    information = newInformation;
}



//
// SetPublishingDate
//
void Book::SetPublishingDate( const QDate& newDate )
{
    publishingDate = newDate;
}



//
// SetDueDate
//
void Book::SetDueDate( const QDate& newDate )
{
    dueDate = newDate;
}



//
// SetOverdueFine
//
void Book::SetOverdueFine( float newFine )
{
    overdueFine = newFine;
}



//
// SetCost
//
void Book::SetCost( float newCost )
{
    cost = newCost;
}


