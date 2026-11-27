// Copyright (C) 2026 Peyman
//
// This file is part of Lucid Drift.
// Lucid Drift is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
// This software is distributed without any warranty.
// See the LICENSE file for the full license text.
// See ADDITIONAL-TERMS.md for additional terms under GPL-3.0 Section 7.

#ifndef LUCID_DRIFT_ENTITY_COMPONENT_SYSTEM_H
#define LUCID_DRIFT_ENTITY_COMPONENT_SYSTEM_H
#include <string>
#include <type_traits>
#include <optional>
#include <SubSystems/Components/ColliderComponent/CMP_Collider.h>
#include <SubSystems/Components/TransComponent/CMP_Transform.h>
#include "Actors/Shapes/Circle/CircleShape.h"
#include <Actors/Shapes/Polygon/Polygon.h>
#include <Actors/Texture/Texture.h>
#include <Actors/Line/Line.h>
#include "Except.h"
#include <memory>
#include "Logger.h"
#include <System/Core/Core.h>

namespace LDDrift
{
    template <typename SHAPE_T, bool USE_COLLIDER_COMPONENT = false, bool USE_TRANSFORM_COMPONENT = false>
    class EntityComponentSystem
    {
    private:
        SHAPE_T* actor;
        std::size_t ID;
        std::string Name;
        bool Active;
        // components
        std::optional<LDDrift::CMP_Collider> collider = std::nullopt;
        std::optional<LDDrift::CMP_Transform> transform = std::nullopt;

    public:
        EntityComponentSystem() = default;

        explicit EntityComponentSystem(const SHAPE_T* actor_ptr) :
            actor(actor_ptr), ID(CORE_PTR->idGenerator.GenerateID()), Active(true) {}

        template <typename COMPONENT>
        void AddComponent() {
            if constexpr (std::is_same_v<COMPONENT, LDDrift::CMP_Collider>) {
                if (!collider)
                    collider.emplace();
            } else if constexpr (std::is_same_v<COMPONENT, LDDrift::CMP_Transform>) {
                if (!transform)
                    transform.emplace();
            }
        }

        template <typename COMPONENT>
        void RemoveComponent() {
            if constexpr (std::is_same_v<COMPONENT, LDDrift::CMP_Collider>) {
                collider.reset();
            } else if constexpr (std::is_same_v<COMPONENT, LDDrift::CMP_Transform>) {
                transform.reset();
            }
        }

        void Initialize() {
            if constexpr (USE_COLLIDER_COMPONENT) {
                collider.emplace();
            }
            if constexpr (USE_TRANSFORM_COMPONENT) {
                transform.emplace();
            }
        }

        [[nodiscard]] const LDDrift::CMP_Collider& GetColliderComponent() const {
            if (collider.has_value() == false) {
                throw LDDrift::Except("Engine", "EntityComponentSystem",
                                      "Collider component has not been initialized");
            }
            return collider.value();
        }

        LDDrift::CMP_Collider& GetColliderComponent() {
            if (collider.has_value() == false) {
                throw LDDrift::Except("Engine", "EntityComponentSystem",
                                      "Collider component has not been initialized");
            }
            return collider.value();
        }

        [[nodiscard]] const LDDrift::CMP_Transform& GetTransformComponent() const {
            if (transform.has_value() == false) {
                throw LDDrift::Except("Engine", "EntityComponentSystem",
                                      "Transform component has not been initialized");
            }
            return transform.value();
        }

        LDDrift::CMP_Transform& GetTransformComponent() {
            if (transform.has_value() == false) {
                throw LDDrift::Except("Engine", "EntityComponentSystem",
                                      "Transform component has not been initialized");
            }
            return transform.value();
        }

        ~EntityComponentSystem() = default;
    };
}

#endif
