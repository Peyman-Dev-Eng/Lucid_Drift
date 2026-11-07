#ifndef LUCID_DRIFT_SCENE_SYSTEM_H
#define LUCID_DRIFT_SCENE_SYSTEM_H
#include <vector>
#include <Renderer/ShapeRender/ShapeRender.h>
#include <thread>
#include "Renderer/TextureRender/TextureRender.h"
#include <functional>
#include <System/SceneManager/SceneChangeAnimation/SceneAnimation.h>

#define LUCID_DRIFT_ACTOR_GEOMETRY_TYPE_C 0x000001
#define LUCID_DRIFT_ACTOR_GEOMETRY_TYPE_P 0x000002
#define LUCID_DRIFT_ACTOR_GEOMETRY_TYPE_L 0x000003
#define CheckFindStatus IsFound

namespace
{
    bool IsFound(const int r) {
        return r != -1;
    }
}

namespace LDDrift
{
    namespace Actors
    {
        class Shape;
        class Polygon;
        class Line;
        class Circle;
    }

    class Core;

    class Scene final
    {
    public:
        using GetAnimationProgressFunction = std::function<double()>;

        struct CIRCLE_SHAPE_INFORMATION
        {
            std::string circleName;
            LDDrift::Actors::Circle* circle;
            bool render;
        };

        struct POLYGON_SHAPE_INFORMATION
        {
            std::string polygonName;
            LDDrift::Actors::Polygon* polygon;
            bool render;
        };

        struct LINE_ACTOR_INFORMATION
        {
            std::string lineName;
            LDDrift::Actors::Line* line;
            bool render;
        };

        struct TEXTURE_INFORMATION
        {
            std::string textureName;
            LDDrift::Texture* texture;
            bool render;
        };

    private:
        bool sendDataToGPU = false;
        LDDrift::Core* core = nullptr;
        LDDrift::ShapeRender* shape_render = nullptr;
        LDDrift::TextureRender* texture_render = nullptr;
        GetAnimationProgressFunction func = nullptr;

    public:
        std::vector<CIRCLE_SHAPE_INFORMATION> circleShapes;
        std::vector<POLYGON_SHAPE_INFORMATION> polygonShapes;
        std::vector<LINE_ACTOR_INFORMATION> lines;
        std::vector<TEXTURE_INFORMATION> textures;

    private:
        // CC = Change Color | TB = To Black
        std::thread A_CC_Circle_TB;
        std::thread A_CC_Polygon_TB;
        std::thread A_CC_Line_TB;
        std::thread A_CC_Texture_TB;
        // threads of A group

        // CC = Change Color | FB = From Black | TMC = to main color
        std::thread B_CC_Circle_FB_TMC;
        std::thread B_CC_Polygon_FB_TMC;
        std::thread B_CC_Line_FB_TMC;
        std::thread B_CC_Texture_FB_TMC;
        // threads of B group
        void freeThreadsOfA_Group();
        void freeThreadsOfB_Group();
        void freeThreads();

    private:
        // group A
        void ChangeColorCirclesToBlack() const;
        void ChangeColorLinesToBlack() const;
        void ChangeColorPolygonsToBlack() const;
        void ChangeColorTexturesToBlack() const;

        // group B
        void ChangeColorCirclesToMainColor() const;
        void ChangeColorLinesToMainColor() const;
        void ChangeColorPolygonsToMainColor() const;
        void ChangeColorTexturesToMainColor() const;

    public:
        Scene();
        void SetCorePTR(LDDrift::Core* corePtr);
        void MarkSendDataToGPU();
        void SetRendererPTR(LDDrift::ShapeRender* rendererPTR);
        void SetTextureRendererPTR(LDDrift::TextureRender* texturePTR);
        void ReSendShapesToRender();
        void SetChangeColorFunction(GetAnimationProgressFunction function);
        void ChangeColorShapesToBlack();
        void ChangeColorShapesFromBlackToMainColor();
        // circle
        [[nodiscard]] bool FindCircleWithName(const std::string& name) const;
        [[nodiscard]] LDDrift::Actors::Circle* GetCircle(const std::string& name) const;
        void CreateCircleShape(const std::string& name,
                               int _pointCount,
                               int _radius,
                               int _speed,
                               const LDDrift::VecPos2D& pos,
                               const LDDrift::VecCol& color,
                               float thickness);
        bool DeleteCircleShape(const std::string& name);
        [[nodiscard]] std::vector<std::string> GetCircleNames() const;
        [[nodiscard]] std::vector<LDDrift::Actors::Circle*> GetCircles_ptr() const;
        // polygon
        [[nodiscard]] bool FindPolygonWithName(const std::string& name) const;
        [[nodiscard]] LDDrift::Actors::Polygon* GetPolygon(const std::string& name) const;
        void CreatePolygonShape(const std::string& name,
                                int _pointCount,
                                int _speed,
                                const int* pos,
                                const LDDrift::VecCol& color,
                                float thickness,
                                int joinLine_A);
        void CreatePolygonShape(const std::string& name,
                                int _pointCount,
                                int _speed,
                                const int* pos,
                                const std::vector<LDDrift::VecCol>& colors,
                                float thickness,
                                int joinLine_A);
        bool DeletePolygonShape(const std::string& name);
        [[nodiscard]] std::vector<std::string> GetPolygonNames() const;
        [[nodiscard]] std::vector<LDDrift::Actors::Polygon*> GetPolygons_ptr() const;
        // Line
        [[nodiscard]] bool FindLineWithName(const std::string& name) const;
        [[nodiscard]] LDDrift::Actors::Line* GetLine(const std::string& name) const;
        void CreateLineActor(const std::string& name,
                             int _thickness,
                             const int* startPos,
                             const int* endPos,
                             const LDDrift::VecCol& color);
        bool DeleteLineShape(const std::string& name);
        [[nodiscard]] std::vector<std::string> GetLineNames() const;
        [[nodiscard]] std::vector<LDDrift::Actors::Line*> GetLines_ptr() const;
        // texture
        [[nodiscard]] int FindTextureWithName(const std::string& name) const;
        [[nodiscard]] LDDrift::Texture* GetTexture(const std::string& name) const;
        void CreateTexture(const std::string& name,
                           const std::filesystem::path& TexturePath,
                           const unsigned short int desired_chan,
                           const std::vector<float>& vertices);
        void DeleteTexture(const std::string& name);
        [[nodiscard]] std::vector<LDDrift::Texture*> GetTextures_Ptr() const;
        [[nodiscard]] std::vector<std::string> GetTextureNames() const;
        ~Scene();
    };
}

#endif
