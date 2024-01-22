#ifndef NOVEL_H
#define NOVEL_H

#include "basicbook.h"

class Novel : public BasicBook
{
public:
    Novel(std::string bookID, std::string bookName, int numOfCopiesTotal, int numOfCopiesLeft, int numOfPages, std::string genre, std::string publisher, int yearPublished);
    std::string toString() const;

protected:
    std::string genre;
    std::string publisher;
    int yearPublished;

};

#endif // NOVEL_H
