#include "Vector3.h"
#include <iostream>
#include <string>
#include <math.h>

const Vector3 Vector3::ONE = Vector3(1, 1, 1);
const Vector3 Vector3::ZERO = Vector3(0, 0, 0);
const Vector3 Vector3::UP = Vector3(0, 1, 0);
const Vector3 Vector3::RIGHT = Vector3(1, 0, 0);
const Vector3 Vector3::FORWARD = Vector3(0, 0, 1);

Vector3::Vector3() {
    this->cord_XYZ[0] = 0;
    this->cord_XYZ[1] = 0;
    this->cord_XYZ[2] = 0;
}

Vector3::Vector3(double x, double y, double z) {
    this->cord_XYZ[0] = x;
    this->cord_XYZ[1] = y;
    this->cord_XYZ[2] = z;
}

void Vector3::setX(double x) {    this->cord_XYZ[0] = x;    }
void Vector3::setY(double y) {    this->cord_XYZ[1] = y;    }
void Vector3::setZ(double z) {    this->cord_XYZ[2] = z;    }
double Vector3::getX() {    return this->cord_XYZ[0];   }
double Vector3::getY() {    return this->cord_XYZ[1];   }
double Vector3::getZ() {    return this->cord_XYZ[2];   }

double Vector3::Norm() {
    return Product(*this,*this);
}

double Vector3::Magnitude() {
    return sqrt(Norm());
}

Vector3 Vector3::Normalized() {
    double m = Magnitude();

    if(m != 0) 
        return Vector3(cord_XYZ[0],cord_XYZ[1],cord_XYZ[2])/m;
        
    return Vector3::ZERO;
}

double Vector3::Angle(Vector3 v1, Vector3 v2) {
    double dotProduct = v1.Product(v1,v2);
    double magnitudeProduct = v1.Magnitude() * v2.Magnitude();

    if (magnitudeProduct == 0.0) {
        //throw std::invalid_argument("Cannot calculate angle with zero magnitude vector.");
        return 0;
    }

    double cosTheta = dotProduct / magnitudeProduct;

    if (cosTheta < -1.0) cosTheta = -1.0;
    if (cosTheta > 1.0) cosTheta = 1.0;

    return std::acos(cosTheta) / 3.14;
}


double Vector3::Distance(Vector3 v1, Vector3 v2) {
    return (v1-v2).Magnitude();
}

std::string Vector3::to_string() {
    //return ("(" + std::to_string(cord_XYZ[0]) + ", " + std::to_string(cord_XYZ[1]) + ", " + std::to_string(cord_XYZ[2]) + ")");


    return ("(" + doubleToString(cord_XYZ[0]) + ", " + doubleToString(cord_XYZ[1]) + ", " + doubleToString(cord_XYZ[2]) + ")");
}

std::string Vector3::doubleToString(double value) {
    std::string str = std::to_string(value);
    str.erase ( str.find_last_not_of('0') + 1, std::string::npos );
    str.erase ( str.find_last_not_of('.') + 1, std::string::npos );
    return str;
}



double Vector3::Product(Vector3 v1, Vector3 v2) {
    return v1.getX()*v2.getX() + v1.getY()*v2.getY() + v1.getZ()*v2.getZ();
}







Vector3 Vector3::CrossProduct(Vector3 v1, Vector3 v2) {
    //(a.y*b.z - a.z*b.y),(a.z*b.x - a.x*b.z),(a.x*b.y - a.y*b.x)
    /*std::cout << "A:" << v1.to_string() << std::endl;
    std::cout << "B:" << v2.to_string() << std::endl;

    std::cout << "X:" << (v1.getY()*v2.getZ() - v1.getZ()*v2.getY()) << std::endl;
    std::cout << "Y:" << (v1.getZ()*v2.getX() - v1.getX()*v2.getZ()) << std::endl;
    std::cout << "Z:" << (v1.getX()*v2.getY() - v1.getY()*v2.getX()) << std::endl;
    std::cout << std::endl;*/

    
    return Vector3 (
        v1.getY()*v2.getZ() - v1.getZ()*v2.getY(),
        v1.getZ()*v2.getX() - v1.getX()*v2.getZ(),
        v1.getX()*v2.getY() - v1.getY()*v2.getX()
    );
}