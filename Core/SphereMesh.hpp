#pragma once

#include <igl/opengl/glfw/Viewer.h>

#include <Vector3.hpp>
#include <Vector4.hpp>

#include <Mesh.hpp>

#include <vector>

// TODO: Implementa classe quadrica
namespace SM
{
    struct Triangle
    {
        int i, j, k;

        Triangle() : i(0), j(0), k(0) {}
        Triangle(int _i, int _j, int _k) : i(_i), j(_j), k(_k) {}
    };

    struct Edge
    {
        int i, j;

        Edge(int first, int second)
        {
            i = first;
            j = second;
        }
    };

    class Sphere
    {
    public:
        std::vector<Math::Vector3> verticesRelativeTo;

        Math::Vector3 center;
        double radius;

        Sphere();
        Sphere(Math::Vector3 center, double radius);

        Sphere lerp(const Sphere &s, double t);
    };

    class SphereMesh
    {
    private:
        igl::opengl::glfw::Viewer &viewer;

        std::vector<Sphere> sphere;

        std::vector<Triangle> triangle;
        std::vector<Edge> edge;

        std::vector<Math::Vector3> vertices;

        void removeDegenerates();

        void drawSpheresOverEdge(const Edge &e) const;
        void drawSpheresOverTriangle(const Math::Vector4 &a, const Math::Vector4 &b, const Math::Vector4 &c) const;

        Math::Vector3 getTriangleCentroid(const Math::Vector3 &v1, const Math::Vector3 &v2, const Math::Vector3 &v3);
        Math::Vector3 getTriangleCentroid(const Triangle &t);

        Math::Vector3 getTriangleNormal(const Math::Vector3 &v1, const Math::Vector3 &v2, const Math::Vector3 &v3);
        Math::Vector3 getTriangleNormal(const Triangle &t);

        void getVertexAdjacentTriangles(int vertexIndex, std::vector<Triangle> &adjacentTraingles);

        int getIndexFromVertex(const Math::Vector3 &vertex);

    public:
        SphereMesh(const Core::Mesh &mesh, igl::opengl::glfw::Viewer &currentViewer);

        void constructTest();

        void initialize();

        void render() const;
        void renderWireframe() const;

        void simplify() const;

        void collapseEdge(int edgeIndex);
        void collapseTriangleSide(int triangleIndex, int sideNumber);

        void collapse(int sphereIndexA, int sphereIndexB);

        void clear();
    };
}