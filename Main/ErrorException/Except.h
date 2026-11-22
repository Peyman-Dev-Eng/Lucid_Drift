#ifndef LUCID_DRIFT_EXCEPT_H
#define LUCID_DRIFT_EXCEPT_H
#include <string>
#define NULL_STRING "NULL_VALUE"

namespace LDDrift
{
    class Except
    {
    public: // constructors and destructor
        // default constructors : start
        Except();
        Except(const Except&);
        Except& operator=(const Except&);
        Except& operator=(Except&&) noexcept;
        Except(Except&&) noexcept;
        // default constructors : end

        // main constructors : start
        Except(const std::string& _program, const std::string& _message);
        Except(const std::string& _program, const std::string& _throwErrorFromLocation, const std::string& _message);
        // main constructors : end
        ~Except();

    public:
        std::string program;
        std::string message;
        std::string ErrorFromLocation;
    };
}
#endif
