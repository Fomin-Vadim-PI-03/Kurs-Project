#ifndef SCIENCEMAGAZINE_H
#define SCIENCEMAGAZINE_H

#include "magazine.h"

class ScienceMagazine : public Magazine
{
public:
    ScienceMagazine(std::string bookID, std::string bookName, int numOfCopiesTotal, int numOfCopiesLeft, int numOfPages, int issueNumber, std::string month, int year, std::string topic);
    std::string toString() const;

protected:
    std::string topic;
};

#endif // SCIENCEMAGAZINE_H
