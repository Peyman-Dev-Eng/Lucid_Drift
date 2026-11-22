#ifndef LUCID_DRIFT_EXCEPT_H
#define LUCID_DRIFT_EXCEPT_H
#include <string>

namespace LDDrift
{
    class Except
    {
    public: // constructors and destructor
        // default constructors : start
        Except();
        Except(const Except&);
        Except& operator=(const Except&);
        Except(const Except&&) noexcept;
        // default constructors : end

        // main constructors : start
        Except(const std::string& program, const std::string& message);
        Except(const std::string& program, const std::string& throwErrorFromLocation, const std::string& message);
        // main constructors : end
        ~Except();

    public:
        std::string program;
        std::string message;
        std::string ErrorFromLocation;
    };
}
#endif
