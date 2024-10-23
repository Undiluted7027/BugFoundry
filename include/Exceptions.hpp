// Exceptions.hpp
#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <string>
#include <iostream>

// Base exception class for the application
class AppException : public std::exception
{
protected:
    std::string message;

public:
    explicit AppException(const std::string &msg) : message(msg) {}

    virtual const char *what() const noexcept override
    {
        return message.c_str();
    }
};

// Exception for file-related errors
class FileException : public AppException
{
public:
    explicit FileException(const std::string &msg) : AppException("FileException: " + msg) {}
};

// Exception for invalid data errors
class InvalidDataException : public AppException
{
public:
    explicit InvalidDataException(const std::string &msg) : AppException("InvalidDataException: " + msg) {}
};

// Exception for duplicate records
class DuplicateRecordException : public AppException
{
public:
    explicit DuplicateRecordException(const std::string &msg) : AppException("DuplicateRecordException: " + msg) {}
};

// Exception for no record found
class NoRecordFound : public AppException
{
public:
    explicit NoRecordFound(const std::string &msg) : AppException("NoRecordFound: " + msg) {}
};

// Utility function to log exception details (optional)
inline void LogException(const AppException &e)
{
    // You can implement logging to a file or any other logging mechanism here
    std::cerr << "Error: " << e.what() << std::endl << std::endl;
}

#endif // EXCEPTIONS_HPP
