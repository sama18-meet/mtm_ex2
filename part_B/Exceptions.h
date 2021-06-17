
namespace mtm {

    class Exception : std::exception {};

    class IllegalArgument : Exception {
        const char* what() const noexcept override;
    };
    class IllegalCell : Exception {
        const char* what() const noexcept override;
    };
    class CellEmpty : Exception {
        const char* what() const noexcept override;
    };
    class MoveTooFar : Exception {
        const char* what() const noexcept override;
    };
    class CellOccupied : Exception {
        const char* what() const noexcept override;
    };
    class OutOfRange : Exception {
        const char* what() const noexcept override;
    };
    class OutOfAmmo : Exception {
        const char* what() const noexcept override;
    };
    class IllegalTarget : Exception {
        const char* what() const noexcept override;
    };
}
