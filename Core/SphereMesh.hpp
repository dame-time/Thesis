#pragma once

#include <igl/opengl/glfw/Viewer.h>

#include <Vector2.hpp>
#include <Vector3.hpp>
#include <Vector4.hpp>

#include <Mesh.hpp>
#include <Quadric.hpp>

#include <vector>
#include <cfloat>
#include <queue>
#include <set>
#include <limits>

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
        public:
            Quadric quadric;
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

    struct CollapsableEdge
    {
        Sphere i, j;
        
        int idxI, idxJ;
        
        double error;
        
        CollapsableEdge(const Sphere& _i, const Sphere& _j, int _idxI, int _idxJ)
        {
            updateEdge(_i, _j, _idxI, _idxJ);
        }
        
        void updateEdge(const Sphere& _i, const Sphere& _j, int _idxI, int _idxJ)
        {
            i = _i;
            j = _j;
            idxI = _idxI;
            idxJ = _idxJ;
            
            updateError();
        }
        
        bool containsIndex(int a)
        {
            return a == idxI || a == idxJ;
        }
        
        void updateError()
        {
            error = 0;
            
            error += i.getSphereQuadric().evaluateSQEM(Math::Vector4(i.center, i.radius));
            error += j.getSphereQuadric().evaluateSQEM(Math::Vector4(j.center, j.radius));
        }
    };

    struct CollapsableEdgeErrorComparator
    {
        bool operator() (const CollapsableEdge& a, const CollapsableEdge& b)
        {
            // Smallest element to the top
            return a.error > b.error;
        }
    };

    class SphereMesh
    {
        private:
            std::vector<CollapsableEdge> collapseCosts;
        
            igl::opengl::glfw::Viewer &viewer;
            
            std::vector<Sphere> sphere;
            
            std::vector<Triangle> triangle;
            std::vector<Edge> edge;
        
            std::vector<int> renderedSpheres;
            
            void initializeSphereMeshTriangles(const std::vector<Core::Face>& Faces);
            void initializeSpheres(const std::vector<Core::Vertex>& vertices);
            
            void computeSpheresProperties(const std::vector<Core::Vertex>& vertices);
        
            void setCollapseCosts();
        
            CollapsableEdge selectEdgeToCollapse();
            Sphere collapseEdgeIntoSphere(const CollapsableEdge& edgeToCollapse);
            
            void removeDegenerates();
            
            void drawSpheresOverEdge(const Edge &e);
            void drawSpheresOverTriangle(const Triangle& t);
            
            Math::Vector3 getTriangleCentroid(const Math::Vector3 &v1, const Math::Vector3 &v2, const Math::Vector3 &v3);
            
            Math::Vector3 getTriangleNormal(const Math::Vector3 &v1, const Math::Vector3 &v2, const Math::Vector3 &v3);
            
            void getVertexAdjacentTriangles(int vertexIndex, std::vector<Triangle> &adjacentTraingles);
        
            std::set<int> getNeighborVertices(int i);
            
        public:
            SphereMesh(const Core::Mesh &mesh, igl::opengl::glfw::Viewer &currentViewer, double vertexSphereRadius = 0.1f);
            
            void constructTest();
            
            void renderSelectedSpheresOnly();
            void render();
            void renderSpheresOnly();
            void renderWireframe();
            void clearRenderedMeshes();
            
            void simplify() const;
            
            void collapseEdge(int edgeIndex);
            void collapseTriangleSide(int triangleIndex, int sideNumber);
            
            void collapse(int sphereIndexA, int sphereIndexB);
            
            void collapseSphereMesh();
            void collapseSphereMesh(int n);
            
            void clear();
    };
}
