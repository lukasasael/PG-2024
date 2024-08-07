//plane.cpp
#include "Plane.h"
#include "colorRGB.h"

Plane::Plane() : Object() {
    this->transform = Transform();
}

Plane::Plane(Vector3 scale) : Object() {
    this->transform = Transform();
    this->transform.scale = scale;
}

Plane::Plane(Vector3 scale, Vector3 position) : Object() {
    this->transform = Transform();
    this->transform.scale = scale;
    this->transform.position = position;
}

Plane::Plane(Vector3 scale, Vector3 position, Vector3 rotation ) : Object() {
    this->transform = Transform();
    this->transform.scale = scale;
    this->transform.position = position;
    this->transform.rotation = rotation;
}

double Plane::getD() {
    Vector3 normal = transform.up();
    Vector3 pos = transform.position;
    return (normal.getX()*pos.getX()) + (normal.getY()*pos.getY()) + (normal.getZ()*pos.getZ());
}

double Plane::contains (Vector3 point) {
    Vector3 normal = transform.up();
    Vector3 pos = transform.position;
    return ((normal.getX()*pos.getX()) + (normal.getY()*pos.getY()) + (normal.getZ()*pos.getZ()) - this->getD());
}

CollisionResult Plane::cast(Ray ray) {
    CollisionResult result;

    //Vector3 point, Vector3 vector
    Vector3 point = ray.origin(),
            vector = ray.direction();

    Vector3 normal = transform.up();
    Vector3 df = (point - transform.position);

    double xc = df.getX();  // VETOR (PONTO RETA) - (PONTO PLANO)
    double yc = df.getY();  // VETOR (PONTO RETA) - (PONTO PLANO)
    double zc = df.getZ();  // VETOR (PONTO RETA) - (PONTO PLANO)
    double xn = normal.getX();   // VETOR NORMAL AO PLANO
    double yn = normal.getY();   // VETOR NORMAL AO PLANO
    double zn = normal.getZ();   // VETOR NORMAL AO PLANO
    double x = vector.getX();   // VETOR DIRETOR DA RETA
    double y = vector.getY();   // VETOR DIRETOR DA RETA
    double z = vector.getZ();   // VETOR DIRETOR DA RETA
    double a = -(xn*xc + yn*yc + zn*zc);
    double b = (xn*x + yn*y + zn*z);


    double t = a/b;

    if (b == 0 || t < 0)
        return result;

    result.t = t;
    result.color = this->color;
    result.normal = normal;

    return result;
}

std::string Plane::to_string() {
    return ("{\n\tmesh: plane,\n\tcolor: (" + getColor() + ")\n\ttransform: " + this->transform.to_string() + "\n}");
}
