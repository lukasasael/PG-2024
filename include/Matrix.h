#ifndef MATRIX_H
#define MATRIX_H
#include <string>
#include <vector>
#include <iostream>
#include "Vector3.h"



struct Matrix {
    std::vector<std::vector<double>> values;

    int size_h() {
        if(values.size() == 0)
            return 0;
        return values[0].size();
    }
    int size_v() {
        return values.size();
        
    }
    std::string to_string() {
        std::string s = "";
        for(int i = 0; i < size_v(); i++) {
            for(int j = 0; j < size_h(); j++)
                s += std::to_string(values[i][j]) + " ";
            s += "\n";
        }
        return s;
    }
    
    std::vector<std::vector<double>> create(int h, int v) {
        std::vector<double> v1 (h, 0);
        std::vector<std::vector<double>> v2(v,v1);
        return v2;
    }
    std::vector<std::vector<double>> create(int h, int v, double value) {
        std::vector<double> v1 (h, value);
        std::vector<std::vector<double>> v2(v,v1);
        return v2;
    }
    
    inline Matrix operator+(Matrix m2) {
        
        if ((size_h() != m2.size_h()) || (size_v() != size_v()))
            throw std::invalid_argument("Matrix dimensions do not match for sum");
        
        Matrix m = {values};
        for(int i = 0; i < size_v(); i++)
            for(int j = 0; j < size_h(); j++)
                m.values[i][j] += m2.values[i][j];
        return m;
    }
    
    inline Matrix operator-(Matrix m2) {
        
        if ((size_h() != m2.size_h()) || (size_v() != size_v()))
            throw std::invalid_argument("Matrix dimensions do not match for sum");
        
        Matrix m = {values};
        for(int i = 0; i < size_v(); i++)
            for(int j = 0; j < size_h(); j++)
                m.values[i][j] -= m2.values[i][j];
        return m;
    }
    
    inline Matrix operator=(Matrix m) {
        values = m.values;
        return m;
    }
    
    inline Matrix operator*(int s) {
        Matrix m = {values};
        
        for(int i = 0; i < size_v(); i++)
            for(int j = 0; j < size_h(); j++)
                m.values[i][j] *= s;
        
        return m;
    }
    
    inline Matrix operator/(double s) {
        Matrix m = {values};
        
        for(int i = 0; i < size_v(); i++)
            for(int j = 0; j < size_h(); j++)
                m.values[i][j] /= s;
        
        return m;
    }
    
    inline Matrix operator*(Matrix m2) {

        int v1 = size_v();
        int h1 = size_h();
        int v2 = m2.size_v();
        int h2 = m2.size_h();


        if (h1 != v2) {
            throw std::invalid_argument("Matrix dimensions do not match for multiplication");
        }

        Matrix m = {create(h2, v1, 0)};

        for (int i = 0; i < v1; ++i) {
            for (int j = 0; j < h2; ++j) {
                for (int k = 0; k < h1; ++k) {
                    m.values[i][j] += values[i][k] * m2.values[k][j];
                }
            }
        }
        

        return m;
    }
    
    Matrix dotProduct(Matrix m2) {
        Matrix m1 = {this->values};
        return dotProduct(m1,m2);
    }
    
    
    Matrix dotProduct(Matrix m1, Matrix m2) {
        int v1 = m1.size_v();
        int h1 = m1.size_h();
        int v2 = m2.size_v();
        int h2 = m2.size_h();
        
        std::vector<double> temp1, temp2;
        temp1 = create((v1==1?h1:v1),1)[0];
        temp2 = create((v2==1?h2:v2),1)[0];
        
        if(temp1.size() < 3 && temp2.size() < 3){
            std::cout << "Matrix dimensions do not match for dotProduct" << std::endl;
            return {{{0}}};
            //throw std::invalid_argument("Matrix dimensions do not match for dotProduct");
        
        }
        
        for(int i = 0; i < temp1.size(); i++)
            temp1[i] = (v1==1?m1.values[0][i]:m1.values[i][0]);
            
        for(int j = 0; j < temp2.size(); j++)
            temp2[j] = (v2==1?m2.values[0][j]:m2.values[j][0]);
        
        
        //i(b*z - c*y) + j(c*x - a*z) + k(a*y-bx)
        Matrix m = {{
            {temp1[1]*temp2[2] - temp1[2]*temp2[1]},
            {temp1[2]*temp2[0] - temp1[0]*temp2[2]},
            {temp1[0]*temp2[1] - temp1[1]*temp2[0]},
            {1}
        }};
        return m;
    }

    Matrix vectorToMatrix(Vector3 v) {
        Matrix m;
        m.values = {
            {v.getX()},
            {v.getY()},
            {v.getZ()},
            {1}
        };
        return m;
    }

    Vector3 to_vector() {
        if(size_v() < 3)
            return Vector3::ZERO;
            
        return Vector3(values[0][0],values[1][0],values[2][0]);
    }

};

#endif // MATRIX_H