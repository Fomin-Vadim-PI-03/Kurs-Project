#ifndef BASICBOOK_H
#define BASICBOOK_H

#include <string>

class BasicBook
{
public:
    BasicBook(std::string bookID, std::string bookName, int numOfCopiesTotal, int numOfCopiesLeft, int numOfPages);
    virtual std::string toString() const;
    bool giveCopies(int numOfCopiesToGive);
    bool receiveCopies(int numOfCopiesToReceive);
    std::string getID();


protected:
    std::string bookID;
    std::string bookName;
    int numOfCopiesTotal;
    int numOfCopiesLeft;
    int numOfPages;
};

#endif // BASICBOOK_H
