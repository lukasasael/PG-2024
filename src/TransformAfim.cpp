#include "TransformAfim.h"
#include "Object.h"
#include "Screen.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <string>

using namespace std;

TransformAfim::TransformAfim() {
}

TransformAfim::TransformAfim(string tipo ,double angle, double x,double y , double z ){

    if(tipo == "rotX") {
        this->matrix = rotX(angle);
    } else if(tipo == "rotY") {
        this->matrix = rotY(angle);
    } else if(tipo == "rotZ") {
        this->matrix = rotZ(angle);
    }

    std::vector<std::vector<double>> matrizPoint = {{x,y,z,1}};
    this->matrizReturn = Product(matrizPoint,this->matrix);
}

std::vector<double> TransformAfim::getCoord() {
    return {this->matrizReturn[0][0],this->matrizReturn[0][1],this->matrizReturn[0][2]};
}


std::vector<std::vector<double>> TransformAfim::Product(std::vector<std::vector<double>> a, std::vector<std::vector<double>> b) {
    std::vector<std::vector<double>> result;
    for(int i = 0; i < 1; i++) {
        result.push_back({0,0,0,0});
        for(int j = 0; j < 4; j++) {
            for(int k = 0; k < 4; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return result;
}


std::vector<std::vector<double>>  TransformAfim::rotX(double angle) {

    return {{1,0,0,0},
            {0,std::cos(angle),-std::sin(angle),0}
            ,{0,std::sin(angle),std::cos(angle),0}
            ,{0,0,0,1}
        };

}

// faça rotação em y e z a partir de um angulo
std::vector<std::vector<double>>  TransformAfim::rotY(double angle) {

    return {{std::cos(angle),0,std::sin(angle),0}
            ,{0,1,0,0}
            ,{-std::sin(angle),0,std::cos(angle),0}
            ,{0,0,0,1}
            };

}


std::vector<std::vector<double>>  TransformAfim::rotZ(double angle) {

    return {{std::cos(angle),-std::sin(angle),0,0}
            ,{std::sin(angle),std::cos(angle),0,0}
            ,{0,0,1,0}
            ,{0,0,0,1}
            };

}