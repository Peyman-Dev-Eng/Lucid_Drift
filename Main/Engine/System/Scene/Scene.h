// Copyright 2026 Peyman
// https://github.com/Peyman-Dev-Eng/Lucid_Drift
//
// This file is part of Lucid Drift.
// Licensed under GNU GPL v3.0.
// See LICENSE and ADDITIONAL-TERMS.md.

#ifndef LUCID_DRIFT_SCENE_SYSTEM_H
#define LUCID_DRIFT_SCENE_SYSTEM_H
#include <vector>
#include <Renderer/ShapeRender/ShapeRender.h>
#include <thread>
#include "Renderer/TextureRender/TextureRender.h"
#include <functional>
#include <System/SceneManager/SceneChangeAnimation/SceneAnimation.h>

#define LUCID_DRIFT_ACTOR_GEOMETRY_TYPE_C 0b01000011
#define LUCID_DRIFT_ACTOR_GEOMETRY_TYPE_P 0b01010000
#define LUCID_DRIFT_ACTOR_GEOMETRY_TYPE_L 0b01001100
#define LUCID_DRIFT_ACTOR_GEOMETRY_TYPE_T 0b01010100
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
            bool render = true;
        };

        struct POLYGON_SHAPE_INFORMATION
        {
            std::string polygonName;
            LDDrift::Actors::Polygon* polygon;
            bool render = true;
        };

        struct LINE_ACTOR_INFORMATION
        {
            std::string lineName;
            LDDrift::Actors::Line* line;
            bool render = true;
        };

        struct TEXTURE_INFORMATION
        {
            std::string textureName;
            LDDrift::Actors::Texture* texture;
            bool render = true;
        };

        struct QueueManagement
        {
            char searchInVector;
            unsigned long int index;
        };

    private:
        bool sendDataToGPU = false;
        LDDrift::Core* core = nullptr;
        LDDrift::ShapeRender* shape_render = nullptr;
        LDDrift::TextureRender* texture_render = nullptr;
        GetAnimationProgressFunction func = nullptr;

    public:
        // defaults
        bool hasData = false;
        std::pmr::vector<std::pair<LDDrift::Actors::Circle*, std::pmr::vector<LDDrift::VecCol>>> circle_colors;
        std::pmr::vector<std::pair<LDDrift::Actors::Polygon*, std::pmr::vector<LDDrift::VecCol>>> polygon_colors;
        std::pmr::vector<std::pair<LDDrift::Actors::Line*, LDDrift::VecCol>> line_colors;
        std::pmr::vector<std::pair<LDDrift::Actors::Texture*, float>> texture_multipliers;
        // main
        std::pmr::vector<CIRCLE_SHAPE_INFORMATION> circleShapes;
        std::pmr::vector<POLYGON_SHAPE_INFORMATION> polygonShapes;
        std::pmr::vector<LINE_ACTOR_INFORMATION> lines;
        std::pmr::vector<TEXTURE_INFORMATION> textures;

    private:
        LDDrift::Actors::Texture backgroundTexture;
        std::pmr::vector<QueueManagement> managements;
        void DeleteWithIndexFromManagements(const char type, const std::size_t index);

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
        // set ptr's
        void SetCorePTR(LDDrift::Core* corePtr);
        void SetRendererPTR(LDDrift::ShapeRender* rendererPTR);
        void SetTextureRendererPTR(LDDrift::TextureRender* texturePTR);
        // rebase renderer systems
        void MarkSendDataToGPU();
        void ReSendShapesToRender();
        // set auxiliary function for change color of shapes
        void SetChangeColorFunction(const GetAnimationProgressFunction& function);
        // change color functions
        void ChangeColorShapesToBlack();
        void ChangeColorShapesFromBlackToMainColor();
        // free data saved for change color
        void freeSavedData();
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
        [[nodiscard]] std::pmr::vector<std::string> GetCircleNames() const;
        [[nodiscard]] std::pmr::vector<LDDrift::Actors::Circle*> GetCircles_ptr() const;
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
                                const std::pmr::vector<LDDrift::VecCol>& colors,
                                float thickness,
                                int joinLine_A);
        bool DeletePolygonShape(const std::string& name);
        [[nodiscard]] std::pmr::vector<std::string> GetPolygonNames() const;
        [[nodiscard]] std::pmr::vector<LDDrift::Actors::Polygon*> GetPolygons_ptr() const;
        // Line
        [[nodiscard]] bool FindLineWithName(const std::string& name) const;
        [[nodiscard]] LDDrift::Actors::Line* GetLine(const std::string& name) const;
        void CreateLineActor(const std::string& name,
                             int _thickness,
                             const int* startPos,
                             const int* endPos,
                             const LDDrift::VecCol& color);
        bool DeleteLineShape(const std::string& name);
        [[nodiscard]] std::pmr::vector<std::string> GetLineNames() const;
        [[nodiscard]] std::pmr::vector<LDDrift::Actors::Line*> GetLines_ptr() const;
        // texture
        [[nodiscard]] int FindTextureWithName(const std::string& name) const;
        [[nodiscard]] LDDrift::Actors::Texture* GetTexture(const std::string& name) const;
        void CreateTexture(const std::string& name,
                           const std::filesystem::path& TexturePath,
                           const std::pmr::vector<float>& vertices);
        void DeleteTexture(const std::string& name);
        [[nodiscard]] std::pmr::vector<LDDrift::Actors::Texture*> GetTextures_Ptr() const;
        [[nodiscard]] std::pmr::vector<std::string> GetTextureNames() const;
        // scene background
        void SetSceneBackground(const std::filesystem::path& path);
        ~Scene();
    };
}

#endif
