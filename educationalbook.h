#ifndef EDUCATIONALBOOK_H
#define EDUCATIONALBOOK_H

#include "basicbook.h"

class EducationalBook : public BasicBook
{
public:
    EducationalBook(std::string bookID, std::string bookName, int numOfCopiesTotal, int numOfCopiesLeft, int numOfPages, std::string subject, std::string level, std::string author);
    std::string toString() const;

protected:
    std::string subject;
    std::string level;
    std::string author;
};

#endif // EDUCATIONALBOOK_H
