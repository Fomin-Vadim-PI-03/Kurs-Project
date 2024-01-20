#include "educationalbook.h"

EducationalBook::EducationalBook(std::string bookID, std::string bookName, int numOfCopiesTotal, int numOfCopiesLeft, int numOfPages, std::string subject, std::string level, std::string author) :
    BasicBook(bookID, bookName, numOfCopiesTotal, numOfCopiesLeft, numOfPages), subject(subject), level(level), author(author) {}

std::string EducationalBook::toString() const {
    return "EB " + bookID + " " + bookName + " " + std::to_string(numOfCopiesTotal) + " " + std::to_string(numOfCopiesLeft) + " " + std::to_string(numOfPages) + " " + subject + " " + level + " " + author;
}
