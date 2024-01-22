#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "basicbook.h"

class Magazine : public BasicBook
{
public:
    Magazine(std::string bookID, std::string bookName, int numOfCopiesTotal, int numOfCopiesLeft, int numOfPages, int issueNumber, std::string month, int year);
    std::string toString() const;

protected:
    int issueNumber;
    std::string month;
    int year;

};

#endif // MAGAZINE_H
