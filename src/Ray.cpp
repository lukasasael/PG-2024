#include "Ray.h"
#include <iostream>
#include <string>
#include <math.h>


Ray::Ray() {
    this->orig = Vector3();
    this->dir = Vector3().FORWARD;
}

std::string Ray::to_string() {
    return ("{\n\torigin: " + orig.to_string() + ",\n\tdirection: " + dir.to_string() + "\n}\n");
}

