#ifndef CHILDRENNOVEL_H
#define CHILDRENNOVEL_H

#include "novel.h"

class ChildrenNovel : public Novel
{
public:
    ChildrenNovel(std::string bookID, std::string bookName, int numOfCopiesTotal, int numOfCopiesLeft, int numOfPages, std::string genre, std::string publisher, int yearPublished, std::string illustrator, std::string ageGroup);
    std::string toString() const;

protected:
    std::string illustrator;
    std::string ageGroup;

};

#endif // CHILDRENNOVEL_H
