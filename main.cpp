#include <iostream>
#include <vector>
#include <tuple>
#include <cmath>


#include "Object.h"
#include "Sphere.h"
#include "Plane.h"
#include "Mesh.h"
#include "Vector3.h"
#include "Camera.h"
#include "Vector3.h"
#include "Matrix.h"

#include "FileWriter.h"
#include "TransformAfim.h"

using namespace std;

Object* CreateCube() {
    std::vector<Vector3> vertices = {
        {0, 0, 0}, {1, 0, 0}, {1, 1, 0}, {0, 1, 0},
        {0, 0, 1}, {1, 0, 1}, {1, 1, 1}, {0, 1, 1}
    };

    std::vector<std::tuple<int, int, int>> faces = {
        {0, 1, 2}, {2, 3, 0},{4, 5, 6}, {6, 7, 4}, 
        {0, 1, 5}, {5, 4, 0},{2, 3, 7}, {7, 6, 2},
        {1, 2, 6}, {6, 5, 1},{0, 3, 7}, {7, 4, 0} 
    };

    Matrix matrix, translate, rotateY;
    int angle = -30;
    double c = std::cos(angle),
           s = std::sin(angle);
    rotateY.values = {{ c,0,s,0},
                      { 0,1,0,0},
                      {-s,0,c,0},
                      { 0,0,0,1}
    };
    translate.values = {{1,0,0,0},
                        {0,1,0,0.5},
                        {0,0,1,0},
                        {0,0,0,1}
    };

    matrix = translate*rotateY;
    for (int i = 0; i < vertices.size(); i++) {
        Matrix cord = matrix.vectorToMatrix(vertices[i]);
        vertices[i] = (matrix * cord).to_vector();
    }
    

    return new Mesh(vertices, faces);
}

Object* CreateIcosaedro() {
    const double t = (1.0 + std::sqrt(5.0)) / 2.0;
    std::vector<Vector3> vertices = {
        {-1,  t,  0}, { 1,  t,  0}, {-1, -t,  0}, { 1, -t,  0},
        { 0, -1,  t}, { 0,  1,  t}, { 0, -1, -t}, { 0,  1, -t},
        { t,  0, -1}, { t,  0,  1}, {-t,  0, -1}, {-t,  0,  1}
    };

    std::vector<std::tuple<int, int, int>> faces = {
        {0, 11, 5}, {0, 5, 1}, {0, 1, 7}, {0, 7, 10}, {0, 10, 11},
        {1, 5, 9}, {5, 11, 4}, {11, 10, 2}, {10, 7, 6}, {7, 1, 8},
        {3, 9, 4}, {3, 4, 2}, {3, 2, 6}, {3, 6, 8}, {3, 8, 9},
        {4, 9, 5}, {2, 4, 11}, {6, 2, 10}, {8, 6, 7}, {9, 8, 1}
    };


    Matrix matrix, translate, rotateY, scale;
    int angle = 0;
    double c = std::cos(angle),
           s = std::sin(angle);
    rotateY.values = {{ c,0,s,0},
                      { 0,1,0,0},
                      {-s,0,c,0},
                      { 0,0,0,1}
    };
    translate.values = {{1,0,0,0},
                        {0,1,0,0.5},
                        {0,0,1,5},
                        {0,0,0,1}
    };
    scale.values = {{0.5,0,0,0},
                    {0,0.5,0,0},
                    {0,0,0.5,0},
                    {0,0,0,1}
    };
    
    matrix = translate*scale*rotateY;
    for (int i = 0; i < vertices.size(); i++) {
        Matrix cord = matrix.vectorToMatrix(vertices[i]);
        vertices[i] = (matrix * cord).to_vector();
    }


    return new Mesh(vertices, faces);
}

void Scene_1() {
    colorRGB RED   = {255,0,0};
    colorRGB GREEN = {0,255,0};
    colorRGB BLUE  = {0,0,255};
    colorRGB YELLOW  = {255,255,0};

    int RESOLUTION = 1080;
    Camera camera = Camera(RESOLUTION, RESOLUTION, (RESOLUTION/512)*1000);
    camera.transform.position = Vector3(-5,5,-10);
    camera.transform.rotation = Vector3(10,25,0);




    Object* sphere = new Sphere(Vector3().ONE*1, Vector3(2,1.5,0.25));
    Object* mesh = new Mesh({Vector3(0,2,0),Vector3(0,0,0),Vector3(2,0,0),Vector3(2,2,0)}, {{1,2,3}});
    Object* plane = new Plane(Vector3().ONE, Vector3(0,0,0), Vector3(0,0,0));
    Object* cube = CreateCube();

    // Transformação 

    // std::vector<Vector3> vertices = {
    //     {0, 0, 0}, {1, 0, 0}, {1, 1, 0}, {0, 1, 0},
    //     {0, 0, 1}, {1, 0, 1}, {1, 1, 1}, {0, 1, 1}
    // };

    // std::vector<std::tuple<int, int, int>> faces = {
    //     {0, 1, 2}, {2, 3, 0},{4, 5, 6}, {6, 7, 4}, 
    //     {0, 1, 5}, {5, 4, 0},{2, 3, 7}, {7, 6, 2},
    //     {1, 2, 6}, {6, 5, 1},{0, 3, 7}, {7, 4, 0} 
    // };
    // std::vector<Vector3> newVertices;

    // for (int i = 0; i < vertices.size(); i++) {
    //     TransformAfim transform = TransformAfim("rotY", 90, vertices[i].getX(), vertices[i].getY(), vertices[i].getZ());
    //     std::vector<double> coord = transform.getCoord();
    //     newVertices.push_back({coord[0], coord[1], coord[2]});

    // }
    // cube = new Mesh(newVertices, faces);


    sphere->color = BLUE;
    plane->color = GREEN;
    mesh->color = RED;
    cube->color = YELLOW;

    vector<Object*> objects;
    objects.push_back(sphere);
    objects.push_back(plane);
    objects.push_back(mesh);
    objects.push_back(cube);

    string image_ppm = camera.render(objects);
    FileWriter::saveAsImage(image_ppm);
}

void Scene_2() {
    colorRGB RED   = {255,0,0};
    colorRGB GREEN = {0,255,0};
    colorRGB BLUE  = {0,0,255};
    colorRGB YELLOW  = {255,255,0};

    int RESOLUTION = 512;
    Camera camera = Camera(RESOLUTION, RESOLUTION, (RESOLUTION/512)*1000);
    camera.transform.position = Vector3(-5,5,-10);
    camera.transform.rotation = Vector3(10,25,0);

    Vector3 v_cord = Vector3(0,0,0);
    Matrix m_cord = Matrix().vectorToMatrix(v_cord);
    Matrix translate = {{{ 1, 0, 0,   2},
                         { 0, 1, 0, 1.5},
                         { 0, 0, 1, 0.25},
                         { 0, 0, 0,   1}
    }};

    Object* sphere = new Sphere(Vector3().ONE*1, (translate*m_cord).to_vector());
    Object* plane = new Plane(Vector3().ONE, Vector3(0,0,0), Vector3(0,0,0));

    sphere->color = BLUE;
    plane->color = GREEN;

    vector<Object*> objects;
    objects.push_back(sphere);
    objects.push_back(plane);

    string image_ppm = camera.render(objects);
    FileWriter::saveAsImage(image_ppm);
}

void Scene_3(){
    colorRGB RED   = {255,0,0};
    colorRGB GREEN = {0,255,0};
    colorRGB BLUE  = {0,0,255};
    colorRGB YELLOW  = {255,255,0};

    int RESOLUTION = 512;
    Camera camera = Camera(RESOLUTION, RESOLUTION, ((double)RESOLUTION/512)*1000);
    camera.transform.position = Vector3(0,2,-10);
    camera.transform.rotation = Vector3(5,0,0);



    //Object* plane = new Plane(Vector3().ONE, Vector3(0,0,0), Vector3(0,0,0));
    //Object* cube = CreateCube();
    Object* icosaedro = CreateIcosaedro();

    //plane->color = GREEN;
    //cube->color = YELLOW;
    icosaedro->color = RED;


    vector<Object*> objects;
    //objects.push_back(plane);
    //objects.push_back(cube);
    objects.push_back(icosaedro);

    string image_ppm = camera.render(objects);
    FileWriter::saveAsImage(image_ppm);
}

class Toro {
    public:

    Toro(double centro_y, double centro_z, double R, double r) :
        //centro_y(centro_y),
        //centro_z(centro_z),
        R(R),
        r(r) {}
        //double centro_y;
        //double centro_z;
        double R;
        double r;

    double calculatePi(int terms) {
        double sum = 0.0;
        for (int i = 0; i < terms; i++) {
            if (i % 2 == 0) {  // índice par
                sum += 1.0 / (2 * i + 1);
            } else {           // índice ímpar
                sum -= 1.0 / (2 * i + 1);
            }
        }
        return sum * 4;
    }

    double pi = calculatePi(300);
    //double pi = 2 * atan(1);

    Vector3 pointOnSurface(double theta, double alpha) {
        double x = (this->R + this->r * cos(theta)) * cos(alpha);
        double z = (this->R + this->r * cos(theta)) * sin(alpha);
        double y = this->r * sin(theta);
        Vector3 point = {x, y, z};
        return point;
    }

    std::vector<double> definirEspacamento(double espacamento) {
        std::vector<double> valores;
        for (double i = 0; i <= 2 * pi + espacamento; i += espacamento) {
            valores.push_back(i);
        }
        if (valores.back() > 2 * pi) {
            valores.pop_back();
        }
        if (valores.back() < 2 * pi) {
            valores.push_back(2 * pi);
        }
        return valores;
    }

    Mesh* triangularizar(double espacamento) {
        vector<Vector3> pontosToro;
        std::vector<double> theta_values = definirEspacamento(espacamento); //pontos do circulo
        std::vector<double> alpha_values = definirEspacamento(espacamento); //circulos

        for (double theta : theta_values) {
            for (double alpha : alpha_values) {
                Vector3 ponto = pointOnSurface(theta, alpha);
                pontosToro.push_back(ponto);
            }
        }

        // Lista para armazenar os triângulos como triplas de índices
        vector<tuple<int, int, int>> triplas;
        int n = static_cast<int>(2 * pi / espacamento);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if ((i + 1) * (n + 1) + j + 1 < pontosToro.size() &&
                    (i + 1) * (n + 1) + j < pontosToro.size() &&
                    i * (n + 1) + j + 1 < pontosToro.size()) {
                    triplas.push_back({i * (n + 1) + j, (i + 1) * (n + 1) + j, i * (n + 1) + j + 1});
                    triplas.push_back({(i + 1) * (n + 1) + j, (i + 1) * (n + 1) + j + 1, i * (n + 1) + j + 1});
                }
            }
        }

        return new Mesh(pontosToro, triplas);
    }
};

Object* CreateToro() {
    Toro toro(0, 0, 1, 0.5);
    return toro.triangularizar(1.0);
}

void Scene_4(){
    colorRGB RED   = {255,0,0};
    colorRGB GREEN = {0,255,0};
    colorRGB BLUE  = {0,0,255};
    colorRGB YELLOW  = {255,255,0};

    int RESOLUTION = 512;
    Camera camera = Camera(RESOLUTION, RESOLUTION, ((double)RESOLUTION/512)*1000);
    camera.transform.position = Vector3(0,2,-10);
    camera.transform.rotation = Vector3(5,0,0);

    Object* renderToro = CreateToro();

    //plane->color = GREEN;
    //cube->color = YELLOW;
    renderToro->color = RED;


    vector<Object*> objects;
    objects.push_back(renderToro);

    string image_ppm = camera.render(objects);
    FileWriter::saveAsImage(image_ppm);
}

// Função auxiliar para calcular o fatorial
unsigned long factorial(unsigned int n) {
    unsigned long result = 1;
    for (unsigned int i = 2; i <= n; ++i)
        result = i;
    return result;
}
// Função auxiliar para calcular o coeficiente binomial
unsigned long binomial(unsigned int n, unsigned int k) {
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;
    return factorial(n) / (factorial(k) * factorial(n - k));
}

class Curva {
public:
    vector<Vector3> pontosdeControle;
    Curva(vector<Vector3> pontos) {
        this->pontosdeControle = pontos;
    }

    // Função que um ponto na Curva
    Vector3 pontosdaCurva(double t, const std::vector<Vector3>& points) {
        Vector3 result = Vector3::ZERO;
        unsigned int n = points.size() - 1;  // Grau do polinômio de Bernstein

        for (unsigned int i = 0; i <= n; ++i) {
            double coefficient = binomial(n, i) * std::pow(t, i) * std::pow(1 - t, n - i);
            result = result + points[i] * coefficient;
        }

        return result;
    }

};

class SuperficieBezier {
public:
    vector<Curva> curvas;
    SuperficieBezier(vector<Curva> curvas) {
        this->curvas = curvas;
    }

    // Função que retorna um ponto na superfície de Bézier
    Vector3 pontoSuperficie(double u, double v) {
        Vector3 result = Vector3::ZERO;
        unsigned int n = curvas.size() - 1; // Grau da superfície de Bézier

        for (unsigned int i = 0; i <= n; ++i) {
            double coefficient = binomial(n, i) * std::pow(u, i) * std::pow(1 - u, n - i);
            result = result + curvas[i].pontosdaCurva(v, curvas[i].pontosdeControle) * coefficient;
        }

        return result;
    }

    // Função que gera uma malha de pontos para a superfície de Bézier
    vector<Vector3> gerarMalha(int resolucaoU, int resolucaoV) {
        vector<Vector3> malha;
        for (int i = 0; i <= resolucaoU; ++i) {
            for (int j = 0; j <= resolucaoV; ++j) {
                double u = (double)i / resolucaoU;
                double v = (double)j / resolucaoV;
                malha.push_back(pontoSuperficie(u, v));
            }
        }
        return malha;
    }
};

Object* CreateBezier() {
    // Define os pontos de controle da superfície de Bézier
    vector<Vector3> pontosControleCurva1 = {Vector3(-2, -2, 0), Vector3(-1, 2, 0), Vector3(1, 2, 0), Vector3(2, -2, 0)};
    vector<Vector3> pontosControleCurva2 = {Vector3(-2, -1, 0), Vector3(-1, 1, 0), Vector3(1, 1, 0), Vector3(2, -1, 0)};
    vector<Vector3> pontosControleCurva3 = {Vector3(-2, 0, 0), Vector3(-1, 0, 0), Vector3(1, 0, 0), Vector3(2, 0, 0)};
    vector<Vector3> pontosControleCurva4 = {Vector3(-2, 1, 0), Vector3(-1, -1, 0), Vector3(1, -1, 0), Vector3(2, 1, 0)};

    // Cria as curvas de Bézier
    Curva curva1 = Curva(pontosControleCurva1);
    Curva curva2 = Curva(pontosControleCurva2);
    Curva curva3 = Curva(pontosControleCurva3);
    Curva curva4 = Curva(pontosControleCurva4);

    // Cria a superfície de Bézier
    vector<Curva> curvas = {curva1, curva2, curva3, curva4};
    SuperficieBezier superficie = SuperficieBezier(curvas);

    // Gera a malha de pontos para a superfície de Bézier
    vector<Vector3> malha = superficie.gerarMalha(10, 10);

    // Cria o objeto de renderização
    Object* object = new Object();
    object->type = ObjectType::MESH;
    object->mesh = new Mesh();
    object->mesh->vertices = malha;
    object->mesh->indices = {};

    return object;
}

void Scene_5(){

    colorRGB RED   = {255,0,0};
    colorRGB GREEN = {0,255,0};
    colorRGB BLUE  = {0,0,255};
    colorRGB YELLOW  = {255,255,0};

    int RESOLUTION = 512;
    Camera camera = Camera(RESOLUTION, RESOLUTION, ((double)RESOLUTION/512)*1000);
    camera.transform.position = Vector3(0,2,-10);
    camera.transform.rotation = Vector3(5,0,0);

    Object* renderBezier = CreateBezier();
    renderBezier->color = GREEN;

    vector<Object*> objects;
    objects.push_back(renderBezier);

    string image_ppm = camera.render(objects);
    FileWriter::saveAsImage(image_ppm);

}

int main() {
    //Scene_1();
    //Scene_2();
    //Scene_3();
    //Scene_4();
    Scene_5();

    
    std::cout << "\n===============================\n" << std::endl;
    return 0;
}
