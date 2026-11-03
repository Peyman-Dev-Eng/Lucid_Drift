#ifndef LUCID_DRIFT_MAIN_RENDERER_H
#define LUCID_DRIFT_MAIN_RENDERER_H
#include <glm/glm.hpp>

namespace LDDrift
{
    class Core;

    class MainRenderer
    {
    private:
        LDDrift::Core* core = nullptr;
    public :
        MainRenderer();
        ~MainRenderer();
        void SetCorePTR(LDDrift::Core* core_ptr);
        [[nodiscard]] glm::mat4 UpdateViewMatrix() const;
    };
} // LDDrift

#endif
