#ifndef RAY_H
#define RAY_H
#include <string>
#include "Vector3.h"

class Ray {
public:
    Ray();
    Ray(Vector3 origin, Vector3 direction) : orig(origin), dir(direction) {};

    Vector3 origin()  { return orig; }
    Vector3 direction() { return dir; }
    Vector3 at(double t) { return (orig + (dir*t)); }

    std::string to_string();

private:
    Vector3 orig;
    Vector3 dir;
};

#endif
