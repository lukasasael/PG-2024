#ifndef MESH_H
#define MESH_H

#include "Object.h"
#include "Vector3.h"
#include "Ray.h"
#include "Transform.h"
#include "colorRGB.h"
#include <vector>
#include <tuple>
#include "Plane.h"


class Mesh : public Object {

    public:
        Mesh() {};
        Mesh(const std::vector<Vector3>& vertices, const std::vector<std::tuple<int, int, int>>& faces);
        std::string to_string() override;
        CollisionResult cast(Ray ray) override;

        Vector3 normal_v(int v);
        Vector3 normal_f(int f);
        CollisionResult cast_face(Ray ray, int f);



        int v() {return vertices.size();}
        int f() {return faces.size();}



    protected:
        std::vector<Vector3> vertices;
        std::vector<std::tuple<int, int, int>> faces;

    private:
        std::vector<Vector3> vertice_normal;
        std::vector<Vector3> face_normal;
        std::vector<double> face_areas;
        std::vector<Vector3> face_barycenters;
};

#endif // MESH_H
