#include "InvalidInputError.h"

InvalidInputError::InvalidInputError( const std::string& msg ) : std::runtime_error(msg) {}
