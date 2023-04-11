#pragma once

#include <igl/opengl/glfw/Viewer.h>

#include <Vector2.hpp>
#include <Vector3.hpp>
#include <Vector4.hpp>

#include <Mesh.hpp>
#include <Quadric.hpp>
#include <Region.hpp>
#include <Sphere.hpp>

#include <vector>
#include <string>
#include <cfloat>

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

    class SphereMesh
    {
        private:            
            std::vector<Sphere> sphere;
            std::vector<Sphere> initialSpheres;
            
            std::vector<Triangle> triangle;
            std::vector<Edge> edge;
        
            igl::opengl::glfw::Viewer &viewer;
            std::vector<int> renderedSpheres;
            std::vector<Core::Mesh*> renderedSphereVertexMeshes;
        
            double BDDSize;
            
            void initializeSphereMeshTriangles(const std::vector<Core::Face>& Faces);
            void initializeSpheres(const std::vector<Core::Vertex>& vertices, double initialRadius);
            
            void computeSpheresProperties(const std::vector<Core::Vertex>& vertices);
            void updateSpheres();
        
            void updateCollapseCosts(const Sphere& newSphere, int i, int j);
            void recalculateCollapseCosts(int edgeIndexToErase, const Sphere& newSphere, int i, int j);
        
            CollapsableEdge getBestCollapseBruteForce();
            CollapsableEdge getBestCollapseInConnectivity();
        
            Sphere collapseEdgeIntoSphere(const CollapsableEdge& edgeToCollapse);
            
            void updateEdgesAfterCollapse(int i, int j);
            void updateTrianglessAfterCollapse(int i, int j);
            void removeDegenerates();
            
            void drawSpheresOverEdge(const Edge &e, int nSpheres = 4);
            void drawSpheresOverTriangle(const Triangle& t, int nSpheres = 4);
        
            void renderEdge(const Math::Vector3& p1, const Math::Vector3& p2, const Math::Vector3& color = Math::Vector3(1, 0, 0));
            
            Math::Vector3 getTriangleCentroid(const Math::Vector3 &v1, const Math::Vector3 &v2, const Math::Vector3 &v3);
            Math::Vector3 getTriangleNormal(const Math::Vector3 &v1, const Math::Vector3 &v2, const Math::Vector3 &v3);
        
            void checkSphereIntersections(Sphere& s);
        
        public:
            SphereMesh(const SphereMesh& sm);
            SphereMesh(const Core::Mesh &mesh, igl::opengl::glfw::Viewer &currentViewer, double vertexSphereRadius = 0.1f);
        
            SphereMesh& operator = (const SphereMesh& sm);
            
            void constructTest();
            
            void renderSelectedSpheresOnly();
            void renderFastSelectedSpheresOnly();
            void render();
            void renderWithNSpherePerEdge(int n);
            void renderSpheresOnly();
            void renderConnectivity();
        
            void renderSphereVertices(int i);
            void clearRenderedSphereVertices();
        
            void colorSelectedSphere(int i);
            void resetColorOfSpheres();
        
            void clearRenderedEdges();
            void clearRenderedMeshes();
            
            void collapse(int sphereIndexA, int sphereIndexB);
            
            void collapseSphereMesh();
            void collapseSphereMesh(int n);
            void collapseSphereMeshFast();
            void collapseSphereMeshFast(int n);
        
            Sphere getSelectedVertexSphere(int sphereIndex);
            void resizeSphereVertex(int sphereIndex, double newSize);
            void translateSphereVertex(int sphereIndex, Math::Vector3& translation);
        
            void saveYAML(const std::string& path = ".", const std::string& fileName = "SphereMesh.yaml");
            void saveTXT(const std::string& path = ".", const std::string& fileName = "SphereMesh.txt");
            
            void clear();
        
            void reset();
    };
}
