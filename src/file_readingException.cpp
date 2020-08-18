#include <exception>

class file_readingException : public std::exception {
    file_readingException() { }

    const char* what() {
        return "An ERROR occured during the reading of the file";
    }
};