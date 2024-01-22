#include "basicbook.h"


BasicBook::BasicBook(std::string bookID, std::string bookName, int numOfCopiesTotal, int numOfCopiesLeft, int numOfPages) :
    bookID(bookID), bookName(bookName), numOfCopiesTotal(numOfCopiesTotal), numOfCopiesLeft(numOfCopiesLeft), numOfPages(numOfPages) {}

std::string BasicBook::toString() const {
    return "BB " + bookID + " " + bookName + " " + std::to_string(numOfCopiesTotal) + " " + std::to_string(numOfCopiesLeft) + " " + std::to_string(numOfPages);
}

bool BasicBook::giveCopies(int numOfCopiesToGive){            // Прибавить к numOfCopiesLeft
    if((numOfCopiesLeft >= numOfCopiesToGive) && (numOfCopiesToGive > 0)){
        numOfCopiesLeft -= numOfCopiesToGive;
        return true;
    }else{
        return false; // Возвращает false, если операция не прошла успешно
    }
}

bool BasicBook::receiveCopies(int numOfCopiesToReceive){      // Отнять от numOfCopiesLeft
    if((numOfCopiesLeft + numOfCopiesToReceive <= numOfCopiesTotal) && (numOfCopiesToReceive > 0)){
        numOfCopiesLeft += numOfCopiesToReceive;
        return true;
    }else{
        return false; // Возвращает false, если операция не прошла успешно
    }
}

std::string BasicBook::getID(){
    return bookID;
}
