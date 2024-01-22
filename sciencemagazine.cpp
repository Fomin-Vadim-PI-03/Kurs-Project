#include "sciencemagazine.h"


ScienceMagazine::ScienceMagazine(std::string bookID, std::string bookName, int numOfCopiesTotal, int numOfCopiesLeft, int numOfPages, int issueNumber, std::string month, int year, std::string topic) :
    Magazine(bookID, bookName, numOfCopiesTotal, numOfCopiesLeft, numOfPages, issueNumber, month, year), topic(topic) {}


std::string ScienceMagazine::toString() const {
    return "SM " + bookID + " " + bookName + " " + std::to_string(numOfCopiesTotal) + " " + std::to_string(numOfCopiesLeft) + " " + std::to_string(numOfPages) + " " + std::to_string(issueNumber) + " " + month + " " + std::to_string(year) + " " + topic;
}
