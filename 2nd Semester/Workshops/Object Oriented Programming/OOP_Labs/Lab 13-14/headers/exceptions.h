#pragma once
#include <string>

class Exception : public std::exception {
public:
    /**
     * Constructor
     */
    explicit Exception(const std::string &message) : message(message) {}

    /**
     * Returneaza mesajul erorii.
     * @return Mesajul de eroare.
     */
    const std::string& get_message() const {
        return message;
    }

private:
    std::string message;
};

class AlreadyExisting : public Exception {
public:
    explicit AlreadyExisting(const std::string &message) : Exception(message) {}
};

class NotExisting : public Exception {
public:
    explicit NotExisting(const std::string &message) : Exception(message) {}
};

class NotValid : public Exception {
public:
    explicit NotValid(const std::string &message) : Exception(message) {}
};