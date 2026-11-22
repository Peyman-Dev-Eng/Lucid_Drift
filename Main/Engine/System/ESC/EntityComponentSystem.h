#ifndef LUCID_DRIFT_ENTITY_COMPONENT_SYSTEM_H
#define LUCID_DRIFT_ENTITY_COMPONENT_SYSTEM_H
#include <string>
#include <type_traits>

namespace LDDrift
{
    class EntityComponentSystem
    {
    private:
        std::size_t ID;
        std::string Name;
        bool Active;
    public:
        EntityComponentSystem();
        ~EntityComponentSystem();
    };
}

#endif
