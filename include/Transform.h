#ifndef TRANSFORM__H
#define TRANSFORM__H
#include "Vector3.h"
#include <string>


class Transform
{
    public:
        Transform();
        Vector3 rotation;
        Vector3 position;
        Vector3 scale;

        Vector3 up();
        Vector3 right();
        Vector3 forward();

        std::string to_string();


    protected:
        Vector3 relative_vector3(Vector3 v);
};

#endif // TRANSFORM__H
