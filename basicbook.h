#ifndef BASICBOOK_H
#define BASICBOOK_H

#include <string>

class BasicBook
{
public:
    BasicBook(std::string bookID, std::string bookName, int numOfCopiesTotal, int numOfCopiesLeft, int numOfPages);
    virtual std::string toString() const;
    bool giveCopies(int numOfCopiesToGive);            // Возвращает false, если операция не прошла успешно - прибавить к numOfCopiesLeft
    bool receiveCopies(int numOfCopiesToReceive);      // Возвращает false, если операция не прошла успешно - отнять от numOfCopiesLeft
    std::string getID();                               // Получить bookID


protected:
    std::string bookID;
    std::string bookName;
    int numOfCopiesTotal;
    int numOfCopiesLeft;
    int numOfPages;

};

#endif // BASICBOOK_H
