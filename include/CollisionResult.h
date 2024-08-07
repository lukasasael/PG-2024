#ifndef COLLISIONRESULT_H
#define COLLISIONRESULT_H
#include <string>
#include <algorithm>
#include "colorRGB.h"
#include "Vector3.h"

struct CollisionResult {
    double t = -1;
    Vector3 normal;
    colorRGB color;

    std::string to_string() {
        return ("{\n\tt: " + std::to_string(t) + "\n\tnormal: " + normal.to_string() + "\n\tcolor: " + color.to_string() + "\n}");
    }
};

#endif // COLLISIONRESULT_H
