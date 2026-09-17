#include "Shape.h"

#include <linux/input-event-codes.h>

void LDDrift::Actors::Shape::MoveUp() {
    for (VecPos2D& point : points) {
        point.Y += Speed;
    }
}

void LDDrift::Actors::Shape::MoveDown() {
    for (VecPos2D& point : points) {
        point.Y -= Speed;
    }
}

void LDDrift::Actors::Shape::MoveLeft() {
    for (VecPos2D& point : points) {
        point.X -= Speed;
    }
}

void LDDrift::Actors::Shape::MoveRight() {
    for (VecPos2D& point : points) {
        point.X += Speed;
    }
}

void LDDrift::Actors::Shape::Rotate(const Angle& angle) {
    float radians = angle.GetAngleRadians();

}
