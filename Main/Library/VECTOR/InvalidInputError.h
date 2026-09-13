#include <exception>
#include <stdexcept>
class InvalidInputError : public std::runtime_error
{
public:
    explicit InvalidInputError(const std::string&);
};