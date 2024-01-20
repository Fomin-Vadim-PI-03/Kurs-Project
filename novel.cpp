#include "novel.h"

Novel::Novel(std::string bookID, std::string bookName, int numOfCopiesTotal, int numOfCopiesLeft, int numOfPages, std::string genre, std::string publisher, int yearPublished) :
    BasicBook(bookID, bookName, numOfCopiesTotal, numOfCopiesLeft, numOfPages), genre(genre), publisher(publisher), yearPublished(yearPublished) {}


std::string Novel::toString() const {
    return "N " + bookID + " " + bookName + " " + std::to_string(numOfCopiesTotal) + " " + std::to_string(numOfCopiesLeft) + " " + std::to_string(numOfPages) + " " + genre + " " + publisher + " " + std::to_string(yearPublished);
}
