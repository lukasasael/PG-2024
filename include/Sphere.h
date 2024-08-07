#ifndef SPHcolorERE_H
#define SPHERE_H

#include "Object.h"
#include <string>
#include <vector>


class Sphere : public Object
{
    public:
        Sphere();
        Sphere(Vector3 scale);
        Sphere(Vector3 scale, Vector3 position);
        Sphere(Vector3 scale, Vector3 position, Vector3 rotation);
        std::string to_string() override;
        CollisionResult cast(Ray ray) override;

    protected:

    private:
};

#endif // SPHERE_H
