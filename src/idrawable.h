#pragma once

#include "camera.h"

class IDrawable {
    public:
        virtual float order() = 0;
        virtual void draw(const Camera& camera) = 0;
        virtual ~IDrawable() = default;
};
