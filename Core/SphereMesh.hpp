#pragma once

#include <igl/opengl/glfw/Viewer.h>

#include <Vector2.hpp>
#include <Vector3.hpp>
#include <Vector4.hpp>

#include <Mesh.hpp>
#include <Quadric.hpp>

#include <vector>
#include <string>
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
            
            std::vector<Math::Vector2> intervals;

            std::vector<Math::Vector3> unitSphereSampler(int numberOfDirections);
        
            void initializeIntervals();

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
                
                initializeIntervals();
            }

            Region(const Math::Vector3& initialVertex) 
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

                initializeIntervals();
                addVertex(initialVertex);
            }

            void computeIntervals();

            void addVertex(const Math::Vector3& v);
            void addVertices(const std::vector<Math::Vector3>& verticesRange);

            void join(Region& region);
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
            std::vector<int> renderedSpheres;
        
        public:
            std::vector<Core::Vertex> vertices;
        
            int renderedMeshID;
        
            Quadric quadric;
            Region region;

            Math::Vector3 center;
            double radius;

            Sphere();
            Sphere(const Core::Vertex& vertex, double targetSphereRadius = 1.0f);
            Sphere(const Math::Vector3& center, double radius);

            Quadric getSphereQuadric();

            void addFace(const Math::Vector3& centroid, const Math::Vector3& normal, double weight = 1.0);
            void addQuadric(const Quadric& q);
        
            void addVertex(const Core::Vertex& vertex);
        
            void renderAssociatedVertices(igl::opengl::glfw::Viewer &viewer);
            void clearRenderedSpheres(igl::opengl::glfw::Viewer &viewer);
        
            void operator = (const Sphere& s)
            {
                this->quadric = s.quadric;
                this->region = s.region;
                
                this->center = s.center;
                this->radius = s.radius;
                this->vertices = s.vertices;
            }

            Sphere lerp(const Sphere &s, double t);
    };

    struct CollapsableEdge
    {
        Sphere i, j;
        
        int idxI, idxJ;
        
        double error;
        
        CollapsableEdge()
        {
            updateEdge(Sphere(), Sphere(), -1, -1);
        }
        
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

    struct AABB
    {
        double minX;
        double maxX;
        
        double minY;
        double maxY;
        
        double minZ;
        double maxZ;
    };

    class SphereMesh
    {
        private:
            std::vector<CollapsableEdge> collapseCosts;
            
            std::vector<Sphere> sphere;
            
            std::vector<Triangle> triangle;
            std::vector<Edge> edge;
        
            igl::opengl::glfw::Viewer &viewer;
            std::vector<int> renderedSpheres;
            
            void initializeSphereMeshTriangles(const std::vector<Core::Face>& Faces);
            void initializeSpheres(const std::vector<Core::Vertex>& vertices);
            
            void computeSpheresProperties(const std::vector<Core::Vertex>& vertices);
        
            void setCollapseCosts();
            void updateCollapseCosts(const Sphere& newSphere, int i, int j);
            void recalculateCollapseCosts(int edgeIndexToErase, const Sphere& newSphere, int i, int j);
        
            CollapsableEdge getBestCollapseBruteForce();
            CollapsableEdge getBestCollapseInConnectivity();
        
            CollapsableEdge selectEdgeToCollapse();
            Sphere collapseEdgeIntoSphere(const CollapsableEdge& edgeToCollapse);
            
            void updateEdgesAfterCollapse(int i, int j);
            void updateTrianglessAfterCollapse(int i, int j);
            void removeDegenerates();
            
            void drawSpheresOverEdge(const Edge &e, int nSpheres = 4);
            void drawSpheresOverTriangle(const Triangle& t, int nSpheres = 4);
        
            void renderEdge(const Math::Vector3& p1, const Math::Vector3& p2, const Math::Vector3& color = Math::Vector3(1, 0, 0));
        
            void computeAABB(const std::vector<Core::Vertex>& vertices);
            
            Math::Vector3 getTriangleCentroid(const Math::Vector3 &v1, const Math::Vector3 &v2, const Math::Vector3 &v3);
            Math::Vector3 getTriangleNormal(const Math::Vector3 &v1, const Math::Vector3 &v2, const Math::Vector3 &v3);
        
        public:
            AABB axisAlignedBoundingBox;
        
            SphereMesh(const Core::Mesh &mesh, igl::opengl::glfw::Viewer &currentViewer, double vertexSphereRadius = 0.1f);
            
            void constructTest();
            
            void renderSelectedSpheresOnly();
            void renderFastSelectedSpheresOnly();
            void render();
            void renderWithNSpherePerEdge(int n);
            void renderSpheresOnly();
            void renderConnectivity();
        
            void renderSphereVertices(int i);
            void clearRenderedSphereVertices();
        
            void clearRenderedEdges();
            void clearRenderedMeshes();
            
            void collapseEdge(int edgeIndex);
            void collapseTriangleSide(int triangleIndex, int sideNumber);
            
            void collapse(int sphereIndexA, int sphereIndexB);
            
            void collapseSphereMesh();
            void collapseSphereMesh(int n);
            void collapseSphereMeshFast();
            void collapseSphereMeshFast(int n);
        
            bool canCollapseSphereMesh();
            int maxNumberOfCollapses();
        
            void saveYAML(const std::string& path = ".");
            
            void clear();
    };
}
