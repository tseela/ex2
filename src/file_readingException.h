#pragma once
#ifndef _FILE_READINGEXCEPTION_H
#define _FILE_READINGEXCEPTION_H

#include <exception>

class file_readingException : public std::exception {
    public:
        /**
         * @brief Construct a new file_reading Exception object.
         * 
         * @param errorCode 
         */
        file_readingException();

        /**
         * @brief Gives an error message for the exception.
         * 
         * @return const char* - The error message.
         */
        const char* what();
};

#endif