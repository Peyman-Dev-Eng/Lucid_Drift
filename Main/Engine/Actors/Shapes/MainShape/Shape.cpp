#include "Shape.h"

#include <linux/input-event-codes.h>

void LDDrift::Actors::Shape::MoveUp() {
    for (VecPosition::VecPos2D& point : points) {
        point.Y += Speed;
    }
}
