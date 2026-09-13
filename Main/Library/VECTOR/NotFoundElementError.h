#include <exception>
#include <stdexcept>

class NotFoundElementError : public std::runtime_error
{
public:
    NotFoundElementError();
};
