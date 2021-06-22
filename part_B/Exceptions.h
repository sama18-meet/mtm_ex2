#ifndef _EXCEPTIONS_H
#define _EXCEPTIONS_H

#include <exception>


/**
*  All exceptions used in the program. When input/ move/ attack is illegal according 
*  to the game and character requirmenets and lows. 
*/ 

namespace mtm {

    class Exception: public std::exception {};

    class IllegalArgument : public Exception {
    public:
        const char* what() const noexcept override;
    };
    class IllegalCell : public Exception {
    public:
        const char* what() const noexcept override;
    };
    class CellEmpty : public Exception {
    public:
        const char* what() const noexcept override;
    };
    class MoveTooFar : public Exception {
    public:
        const char* what() const noexcept override;
    };
    class CellOccupied : public Exception {
    public:
        const char* what() const noexcept override;
    };
    class OutOfRange : public Exception {
    public:
        const char* what() const noexcept override;
    };
    class OutOfAmmo : public Exception {
    public:
        const char* what() const noexcept override;
    };
    class IllegalTarget : public Exception {
    public:
        const char* what() const noexcept override;
    };
}

#endif
