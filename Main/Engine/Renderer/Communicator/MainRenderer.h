#ifndef LUCID_DRIFT_MAIN_RENDERER_H
#define LUCID_DRIFT_MAIN_RENDERER_H
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Actors/Shapes/MainShape/Shape.h>
#include <Actors/Line/Line.h>

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
        static void StaticDrawer(const LDDrift::Core* _core,
                                 const std::vector<LDDrift::Actors::Shape*>& shapes,
                                 const std::vector<LDDrift::Actors::Line*>& lines);
        void SetCorePTR(LDDrift::Core* core_ptr);
        [[nodiscard]] glm::mat4 UpdateViewMatrix() const;
    };
} // LDDrift

#endif
