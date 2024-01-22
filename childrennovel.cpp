#include "childrennovel.h"


ChildrenNovel::ChildrenNovel(std::string bookID, std::string bookName, int numOfCopiesTotal, int numOfCopiesLeft, int numOfPages, std::string genre, std::string publisher, int yearPublished, std::string illustrator, std::string ageGroup) :
    Novel(bookID, bookName, numOfCopiesTotal, numOfCopiesLeft, numOfPages, genre, publisher, yearPublished), illustrator(illustrator), ageGroup(ageGroup) {}

std::string ChildrenNovel::toString() const {
    return "CN " + bookID + " " + bookName + " " + std::to_string(numOfCopiesTotal) + " " + std::to_string(numOfCopiesLeft) + " " + std::to_string(numOfPages) + " " + genre + " " + publisher + " " + std::to_string(yearPublished) + " " + illustrator + " " + ageGroup;
}
