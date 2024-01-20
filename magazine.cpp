#include "magazine.h"

Magazine::Magazine (std::string bookID, std::string bookName, int numOfCopiesTotal, int numOfCopiesLeft, int numOfPages, int issueNumber, std::string month, int year) :
    BasicBook(bookID, bookName, numOfCopiesTotal, numOfCopiesLeft, numOfPages), issueNumber(issueNumber), month(month), year(year) {}

std::string Magazine::toString() const {
    return "M " + bookID + " " + bookName + " " + std::to_string(numOfCopiesTotal) + " " + std::to_string(numOfCopiesLeft) + " " + std::to_string(numOfPages) + " " + std::to_string(issueNumber) + " " + month + " " + std::to_string(year);
}
