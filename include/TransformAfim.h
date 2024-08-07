#ifndef TransformAfim_H
#define TransformAfim_H
#include <string>
#include "Object.h"
#include "Screen.h"
#include <vector>

using namespace std;

class TransformAfim 
{
    public:
        TransformAfim();
        TransformAfim(string tipo ,double angle, double x,double y , double z );
        std::vector<std::vector<double>> rotX(double angle);
        std::vector<std::vector<double>> rotY(double angle);
        std::vector<std::vector<double>> rotZ(double angle);
        std::vector<std::vector<double>> Product(std::vector<std::vector<double>> a, std::vector<std::vector<double>> b);
        std::vector<std::vector<double>> matrix;
        std::vector<std::vector<double>> matrizReturn; 
        std::vector<double> getCoord();

    private:
};

#endif // CAMERA_H