#include <exception>
#include <stdexcept>

class EmptySnakeBodyDataStruct : public std::runtime_error
{
public:
    EmptySnakeBodyDataStruct();
};
