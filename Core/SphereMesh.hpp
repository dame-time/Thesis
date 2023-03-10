#pragma once

#include <igl/opengl/glfw/Viewer.h>

#include <Vector2.hpp>
#include <Vector3.hpp>
#include <Vector4.hpp>

#include <Mesh.hpp>
#include <Quadric.hpp>

#include <vector>
#include <cfloat>

namespace SM
{
    class Region
    {
        private:
            static std::vector<Math::Vector3> directions;
            
            std::vector<Math::Vector3> vertices;
            std::vector<Math::Vector2> intervals;

            std::vector<Math::Vector3> unitSphereSampler(int numberOfDirections);

        public:
            double directionalWidth;

            Region() 
            { 
                directionalWidth = DBL_MAX;

                if (Region::directions.size() == 0)
                {
                    auto sphereSamples = unitSphereSampler(30);
                    for (int i = 0; i < sphereSamples.size(); i++)
                    {
                        Region::directions.push_back(sphereSamples[i]);
                    }
                }
            }

            Region(const Math::Vector3& initialVertex) 
            { 
                directionalWidth = DBL_MAX;
                vertices.push_back(initialVertex); 

                if (Region::directions.size() == 0)
                {
                    auto sphereSamples = unitSphereSampler(30);
                    for (int i = 0; i < sphereSamples.size(); i++)
                    {
                        Region::directions.push_back(sphereSamples[i]);
                    }
                }

                computeIntervals();
            }

            void computeIntervals();

            void addVertex(const Math::Vector3& v);
            void addVertices(const std::vector<Math::Vector3>& verticesRange);

            void join(const Region& region);
    };

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
        private:
            Quadric quadric;

        public:
            Region region;

            Math::Vector3 center;
            double radius;

            Sphere();
            Sphere(const Core::Vertex& vertex, double targetSphereRadius = 1.0f);
            Sphere(const Math::Vector3& center, double radius);

            Quadric getSphereQuadric();

            void addFace(const Math::Vector3& centroid, const Math::Vector3& normal);
            void addQuadric(const Quadric& q);

            Sphere lerp(const Sphere &s, double t);
    };

    class SphereMesh
    {
    private:
        igl::opengl::glfw::Viewer &viewer;

        std::vector<Sphere> sphere;

        std::vector<Triangle> triangle;
        std::vector<Edge> edge;

        void removeDegenerates();

        void drawSpheresOverEdge(const Edge &e) const;
        void drawSpheresOverTriangle(const Triangle& t) const;

        Math::Vector3 getTriangleCentroid(const Math::Vector3 &v1, const Math::Vector3 &v2, const Math::Vector3 &v3);
        Math::Vector3 getTriangleCentroid(const Triangle &t);

        Math::Vector3 getTriangleNormal(const Math::Vector3 &v1, const Math::Vector3 &v2, const Math::Vector3 &v3);
        Math::Vector3 getTriangleNormal(const Triangle &t);

        void getVertexAdjacentTriangles(int vertexIndex, std::vector<Triangle> &adjacentTraingles);

        int getSphereIndexFromVertex(const Math::Vector3 &vertex);

    public:
        SphereMesh(const Core::Mesh &mesh, igl::opengl::glfw::Viewer &currentViewer, double vertexSphereRadius = 0.1f);

        void constructTest();

        void render() const;
        void renderSpheresOnly() const;
        void renderWireframe() const;

        void simplify() const;

        void collapseEdge(int edgeIndex);
        void collapseTriangleSide(int triangleIndex, int sideNumber);

        void collapse(int sphereIndexA, int sphereIndexB);

        void clear();
    };
}