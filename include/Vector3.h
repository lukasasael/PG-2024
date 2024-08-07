#ifndef VECTOR3_H
#define VECTOR3_H
#include <string>
#include <iostream>

class Vector3 {
public:
    static const Vector3 ONE;
    static const Vector3 ZERO;
    static const Vector3 UP;
    static const Vector3 RIGHT;
    static const Vector3 FORWARD;

    Vector3();
    Vector3(double x, double y, double z);
    std::string to_string();

    Vector3 operator+(const Vector3 other) const { return Vector3(cord_XYZ[0]+other.cord_XYZ[0], cord_XYZ[1]+other.cord_XYZ[1], cord_XYZ[2]+other.cord_XYZ[2]); }
    Vector3 operator-(const Vector3 other) const { return Vector3(cord_XYZ[0]-other.cord_XYZ[0], cord_XYZ[1]-other.cord_XYZ[1], cord_XYZ[2]-other.cord_XYZ[2]); }
    Vector3 operator*(const double scale) const { return Vector3(cord_XYZ[0]*scale, cord_XYZ[1]*scale, cord_XYZ[2]*scale); }
    Vector3 operator/(const double scale) const { return Vector3(cord_XYZ[0]/scale, cord_XYZ[1]/scale, cord_XYZ[2]/scale); }

    double Norm();
    double Magnitude();
    Vector3 Normalized();
    static double Angle(Vector3 v1, Vector3 v2);
    static double Distance(Vector3 v1, Vector3 v2);
    static double Product(Vector3 v1, Vector3 v2);
    static Vector3 CrossProduct(Vector3 v1, Vector3 v2);

    void setX(double x);
    void setY(double y);
    void setZ(double y);
    double getX();
    double getY();
    double getZ();

private:
    double cord_XYZ[3];
    std::string doubleToString(double value);
};

#endif
