#include "EmptySnakeBodyDataStructError.h"

EmptySnakeBodyDataStruct::EmptySnakeBodyDataStruct() : std::runtime_error( "Snake Body is Empty" ){}
