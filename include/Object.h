// object.h
#ifndef OBJECT_H
#define OBJECT_H

#include "Vector3.h"
#include "Ray.h"
#include "Transform.h"
#include "colorRGB.h"
#include "CollisionResult.h"
#include <vector>

class Object {

    public:
        Object();
        virtual ~Object();
        virtual std::string to_string();
        virtual CollisionResult cast(Ray ray);
        Transform transform;
        colorRGB color;

        void setColor(int r, int g, int b);
        std::string getColor();

    protected:

    private:
};

#endif // OBJECT_H
