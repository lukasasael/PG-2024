#ifndef PLANE_H
#define PLANE_H
#include "Object.h"


class Plane : public Object
{
    public:
        Plane();
        Plane(Vector3 scale);
        Plane(Vector3 scale, Vector3 position);
        Plane(Vector3 scale, Vector3 position, Vector3 rotation);
        std::string to_string() override;
        CollisionResult cast(Ray ray) override;
        double contains (Vector3 point);
        double getD();

    protected:

    private:
};

#endif // PLANE_H
