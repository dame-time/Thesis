#define _LIBCPP_NO_EXPERIMENTAL_DEPRECATION_WARNING_FILESYSTEM
#include "../SphereMesh.hpp"

#include "../SQEM.h"

#include <Math.hpp>

#include <Eigen/Dense>
#include <Eigen/Core>
#include <Eigen/SparseCore>

#include <yaml-cpp/yaml.h>

#include <experimental/filesystem>
#include <algorithm>
#include <cassert>
#include <cmath>

void YAMLSerializeVector3(YAML::Emitter& out, const Math::Vector3& vector) {
    out << YAML::BeginMap;
    out << YAML::Key << "X" << YAML::Value << vector.coordinates.x;
    out << YAML::Key << "Y" << YAML::Value << vector.coordinates.y;
    out << YAML::Key << "Z" << YAML::Value << vector.coordinates.z;
    out << YAML::EndMap;
}

void YAMLSerializeVector4(YAML::Emitter& out, const Math::Vector4& vector) {
    out << YAML::BeginMap;
    out << YAML::Key << "X" << YAML::Value << vector.coordinates.x;
    out << YAML::Key << "Y" << YAML::Value << vector.coordinates.y;
    out << YAML::Key << "Z" << YAML::Value << vector.coordinates.z;
    out << YAML::Key << "W" << YAML::Value << vector.coordinates.w;
    out << YAML::EndMap;
}

void YAMLSerializeMatrix4(YAML::Emitter& out, const Math::Matrix4& matrix) {
    out << YAML::BeginMap;
    out << YAML::Key << "0" << YAML::Value << matrix.data[0];
    out << YAML::Key << "1" << YAML::Value << matrix.data[1];
    out << YAML::Key << "2" << YAML::Value << matrix.data[2];
    out << YAML::Key << "3" << YAML::Value << matrix.data[3];
    out << YAML::Key << "4" << YAML::Value << matrix.data[4];
    out << YAML::Key << "5" << YAML::Value << matrix.data[5];
    out << YAML::Key << "6" << YAML::Value << matrix.data[6];
    out << YAML::Key << "7" << YAML::Value << matrix.data[7];
    out << YAML::Key << "8" << YAML::Value << matrix.data[8];
    out << YAML::Key << "9" << YAML::Value << matrix.data[9];
    out << YAML::Key << "10" << YAML::Value << matrix.data[10];
    out << YAML::Key << "11" << YAML::Value << matrix.data[11];
    out << YAML::Key << "12" << YAML::Value << matrix.data[12];
    out << YAML::Key << "13" << YAML::Value << matrix.data[13];
    out << YAML::Key << "14" << YAML::Value << matrix.data[14];
    out << YAML::Key << "15" << YAML::Value << matrix.data[15];
    out << YAML::EndMap;
}

void YAMLSerializeQuadric(YAML::Emitter& out, SM::Quadric& q) {
    out << YAML::BeginMap;
    out << YAML::Key << "A" << YAML::Value;
    YAMLSerializeMatrix4(out, q.getA());
    out << YAML::Key << "b" << YAML::Value;
    YAMLSerializeVector4(out, q.getB());
    out << YAML::Key << "c" << YAML::Value << q.getC();
    out << YAML::EndMap;
}

namespace SM {
    std::vector<Math::Vector3> Region::directions;

    SphereMesh::SphereMesh(const Core::Mesh &mesh, igl::opengl::glfw::Viewer &currentViewer, double vertexSphereRadius) : viewer(currentViewer)
    {
        auto vertices = mesh.vertices;
        auto faces = mesh.faces;

        initializeSphereMeshTriangles(faces);
        initializeSpheres(vertices);
        
        computeSpheresProperties(vertices);
    }

    void SphereMesh::computeAABB(const std::vector<Core::Vertex>& vertices)
    {
        axisAlignedBoundingBox.minX = DBL_MAX;
        axisAlignedBoundingBox.minY = DBL_MAX;
        axisAlignedBoundingBox.minY = DBL_MAX;
        
        axisAlignedBoundingBox.maxX = -DBL_MAX;
        axisAlignedBoundingBox.maxY = -DBL_MAX;
        axisAlignedBoundingBox.maxY = -DBL_MAX;
        
        for (int i = 0; i < vertices.size(); i++)
        {
            if (vertices[i].position[0] < axisAlignedBoundingBox.minX)
                axisAlignedBoundingBox.minX = vertices[i].position[0];
            if (vertices[i].position[0] > axisAlignedBoundingBox.maxX)
                axisAlignedBoundingBox.maxX = vertices[i].position[0];
            
            if (vertices[i].position[1] < axisAlignedBoundingBox.minY)
                axisAlignedBoundingBox.minY = vertices[i].position[1];
            if (vertices[i].position[1] > axisAlignedBoundingBox.maxY)
                axisAlignedBoundingBox.maxY = vertices[i].position[1];
            
            if (vertices[i].position[2] < axisAlignedBoundingBox.minZ)
                axisAlignedBoundingBox.minZ = vertices[i].position[2];
            if (vertices[i].position[2] > axisAlignedBoundingBox.maxZ)
                axisAlignedBoundingBox.maxZ = vertices[i].position[2];
        }
    }

    void SphereMesh::initializeSphereMeshTriangles(const std::vector<Core::Face>& faces)
    {
        for (int i = 0; i < faces.size(); i++)
            triangle.push_back(Triangle(faces[i].i, faces[i].j, faces[i].k));
    }

    void SphereMesh::initializeSpheres(const std::vector<Core::Vertex>& vertices)
    {
        for (int i = 0; i < vertices.size(); i++)
            sphere.push_back(Sphere(vertices[i]));
    }

    void SphereMesh::setCollapseCosts()
    {
        const double EPSILON = 0.5;
        collapseCosts.clear();
        
        for (int i = 0; i < sphere.size(); i++)
        {
            for (int j = i + 1; j < sphere.size(); j++)
            {
                if (i == j || (sphere[i].center - sphere[j].center).magnitude() > EPSILON)
                    continue;
                
                collapseCosts.push_back(CollapsableEdge(sphere[i], sphere[j], i, j));
            }
        }
        
        std::make_heap(collapseCosts.begin(), collapseCosts.end(), CollapsableEdgeErrorComparator());
    }

    CollapsableEdge SphereMesh::getBestCollapseBruteForce()
    {
        const double EPSILON = 0.1;
        
        assert(sphere.size() > 1);
        
        double minErorr = DBL_MAX;
        CollapsableEdge bestEdge = CollapsableEdge(sphere[0], sphere[1], 0, 1);
        
        for (int i = 0; i < sphere.size(); i++)
        {
            for (int j = i + 1; j < sphere.size(); j++)
            {
                if (i == j || (sphere[i].center - sphere[j].center).magnitude() > EPSILON)
                    continue;
                
                CollapsableEdge candidateEdge = CollapsableEdge(sphere[i], sphere[j], i, j);
                if (candidateEdge.error < minErorr)
                {
                    bestEdge = CollapsableEdge(sphere[i], sphere[j], i, j);
                    minErorr = candidateEdge.error;
                }
            }
        }
        
        assert(bestEdge.idxI != -1 && bestEdge.idxJ != -1);
        
        if (bestEdge.idxI > bestEdge.idxJ)
            bestEdge.updateEdge(bestEdge.j, bestEdge.i, bestEdge.idxJ, bestEdge.idxI);
        
        return bestEdge;
    }

    CollapsableEdge SphereMesh::getBestCollapseInConnectivity()
    {
        const double EPSILON = DBL_MAX;
        
        assert(triangle.size() > 0 || edge.size() > 0);
        
        double minErorr = DBL_MAX;
        CollapsableEdge bestEdge;
        
        for (int i = 0; i < triangle.size(); i++)
        {
            int v1 = triangle[i].i;
            int v2 = triangle[i].j;
            int v3 = triangle[i].k;
            
            CollapsableEdge e1 = CollapsableEdge(sphere[v1], sphere[v2], v1, v2);
            CollapsableEdge e2 = CollapsableEdge(sphere[v1], sphere[v3], v1, v3);
            CollapsableEdge e3 = CollapsableEdge(sphere[v2], sphere[v3], v2, v3);
            
            CollapsableEdge bestInTriangle;
            if (e1.error <= e2.error && e1.error <= e3.error)
                bestInTriangle = e1;
            else if (e2.error <= e1.error && e2.error <= e3.error)
                bestInTriangle = e2;
            else
                bestInTriangle = e3;
            
            if (bestInTriangle.error < minErorr)
            {
                bestEdge = bestInTriangle;
                minErorr = bestEdge.error;
            }
        }
        
        for (int i = 0; i < edge.size(); i++)
        {
            int v1 = edge[i].i;
            int v2 = edge[i].j;
            
            CollapsableEdge candidateEdge = CollapsableEdge(sphere[v1], sphere[v2], v1, v2);
            if (candidateEdge.error < minErorr)
            {
                bestEdge = candidateEdge;
                minErorr = bestEdge.error;
            }
        }
        
        assert(bestEdge.idxI != -1 && bestEdge.idxJ != -1);
        
        if (bestEdge.idxI > bestEdge.idxJ)
            bestEdge.updateEdge(bestEdge.j, bestEdge.i, bestEdge.idxJ, bestEdge.idxI);
        
        return bestEdge;
    }

    void SphereMesh::computeSpheresProperties(const std::vector<Core::Vertex>& vertices)
    {
        const double sigma = 1;
        
        double AABBx = std::abs(axisAlignedBoundingBox.maxX - axisAlignedBoundingBox.minX);
        double AABBy = std::abs(axisAlignedBoundingBox.maxY - axisAlignedBoundingBox.minY);
        double AABBz = std::abs(axisAlignedBoundingBox.maxZ - axisAlignedBoundingBox.minZ);
        double BDD = std::sqrt((AABBx * AABBx) + (AABBy * AABBy) + (AABBz * AABBz));
        
        for (int i = 0; i < sphere.size(); i++)
        {
            for (int j = 0; j < triangle.size(); j++)
            {
                if (triangle[j].i == i || triangle[j].j == i || triangle[j].k == i)
                {
                    // Getting neighbor face normal and centroid in order to add the face to our sphere
                    Math::Vector3 centroid = getTriangleCentroid(vertices[triangle[j].i].position, vertices[triangle[j].j].position, vertices[triangle[j].k].position);
                    Math::Vector3 normal = getTriangleNormal(vertices[triangle[j].i].position, vertices[triangle[j].j].position, vertices[triangle[j].k].position);
                    
                    double area = 0.5 * (vertices[triangle[j].j].position - vertices[triangle[j].i].position).cross(vertices[triangle[j].k].position - vertices[triangle[j].i].position).magnitude();
                    double weight = area / 3.0;
                    
                    double totalK1 = 0.33 * vertices[triangle[j].i].curvature[0] + 0.33 * vertices[triangle[j].j].curvature[0] + 0.33 * vertices[triangle[j].k].curvature[0];
                    double totalK2 = 0.33 * vertices[triangle[j].i].curvature[1] + 0.33 * vertices[triangle[j].j].curvature[1] + 0.33 * vertices[triangle[j].k].curvature[1];
                    
//                    TODO: Chiedi al prof quale dei due e' meglio
                    weight *= (1 + sigma * BDD * BDD * ((totalK1 * totalK1) + (totalK2 * totalK2)));
//                    weight = (weight + sigma * BDD * BDD * ((totalK1 * totalK1) + (totalK2 * totalK2)));
//                    weight = (1 + sigma * BDD * BDD * ((totalK1 * totalK1) + (totalK2 * totalK2)));
//                    weight += (1 + sigma * BDD * BDD * ((totalK1 * totalK1) + (totalK2 * totalK2)));

                    sphere[i].addFace(centroid, normal, weight);
                    sphere[i].region.addVertex(vertices[triangle[j].i].position);
                    sphere[i].region.addVertex(vertices[triangle[j].j].position);
                    sphere[i].region.addVertex(vertices[triangle[j].k].position);
                }
            }
        }
    }

    Math::Vector3 SphereMesh::getTriangleCentroid(const Math::Vector3 &v1, const Math::Vector3 &v2, const Math::Vector3 &v3)
    {
        Math::Vector3 centroid;

        centroid[0] = (v1[0] + v2[0] + v3[0]) / 3.0;
        centroid[1] = (v1[1] + v2[1] + v3[1]) / 3.0;
        centroid[2] = (v1[2] + v2[2] + v3[2]) / 3.0;

        return centroid;
    }

    Math::Vector3 SphereMesh::getTriangleNormal(const Math::Vector3 &v1, const Math::Vector3 &v2, const Math::Vector3 &v3)
    {
        return (v2 - v1).cross(v3 - v1).normalized();
    }

    void SphereMesh::constructTest()
    {
        clear();

        sphere.push_back(Sphere(Math::Vector3(), 1));
        sphere.push_back(Sphere(Math::Vector3(3, 1.5f, 0.0f), 1.5f));
        sphere.push_back(Sphere(Math::Vector3(3, -1.5f, 0.0f), 0.7f));
        sphere.push_back(Sphere(Math::Vector3(6, 3, -.5f), 1));
        sphere.push_back(Sphere(Math::Vector3(6, -3, .5f), 1.2));

        triangle.push_back(Triangle(0, 1, 2));

        edge.push_back(Edge(1, 3));
        edge.push_back(Edge(2, 4));
    }

    void SphereMesh::clear ()
    {
        sphere.clear();
        triangle.clear();
        edge.clear();
    }

    void SphereMesh::drawSpheresOverEdge(const Edge &e, int ns)
    {
        int nSpheres = ns;

        const Math::Vector3 color = Math::Vector3(0.1, 0.7, 1);

        for (int i = 1; i < nSpheres - 1; i++)
        {
            Core::Mesh s = Core::Mesh::generateSphereMesh(this->viewer, color);

            s.resize(Math::lerp(sphere[e.i].radius, sphere[e.j].radius, i * 1.0 / (nSpheres - 1)));
            s.translate(Math::lerp(sphere[e.i].center, sphere[e.j].center, i * 1.0 / (nSpheres - 1)));
            
            renderedSpheres.push_back(s.ID);
        }
    }

    void SphereMesh::drawSpheresOverTriangle(const Triangle& e, int ns)
    {
        Math::Vector3 color = Math::Vector3(0.1, 0.7, 1);

        int nSpheres = ns;

        for (int i = 0; i < nSpheres; i++)
            for (int j = 0; j < nSpheres - i; j++)
            {
                int k = nSpheres - 1 - i - j;

                if (i == nSpheres - 1 || j == nSpheres - 1 || k == nSpheres - 1) continue;

                double ci = i * 1.0 / (nSpheres - 1);
                double cj = j * 1.0 / (nSpheres - 1);
                double ck = k * 1.0 / (nSpheres - 1);

                Core::Mesh s = Core::Mesh::generateSphereMesh(this->viewer, color);

                s.resize   (sphere[e.i].radius * ci + sphere[e.j].radius * cj + sphere[e.k].radius * ck);
                s.translate(sphere[e.i].center * ci + sphere[e.j].center * cj + sphere[e.k].center * ck);
                
                renderedSpheres.push_back(s.ID);
            }
    }

    void SphereMesh::renderEdge(const Math::Vector3& p1, const Math::Vector3& p2, const Math::Vector3& color)
    {
        // Define the two points of the line
        Eigen::MatrixXd V(1,3);
        V << p1[0], p1[1], p1[2];
        
        Eigen::MatrixXd V1(1, 3);
        V1 << p2[0], p2[1], p2[2];

        auto c = Eigen::RowVector3d(color[0], color[1], color[2]);
        // Add the line to the viewer
        viewer.data().add_edges(V, V1, c);
    }

    void SphereMesh::renderConnectivity()
    {
        viewer.data().clear_edges();
        
        const Math::Vector3 color = Math::Vector3(1, 1, 0);
        for (Triangle& t : triangle)
        {
            renderEdge(sphere[t.i].center, sphere[t.j].center, color);
            renderEdge(sphere[t.i].center, sphere[t.k].center, color);
            renderEdge(sphere[t.j].center, sphere[t.j].center, color);
        }
        
        for (Edge& e : edge)
            renderEdge(sphere[e.i].center, sphere[e.j].center, color);
    }

    void SphereMesh::render()
    {
        for (int i = 0; i < triangle.size(); i++)
            this->drawSpheresOverTriangle(triangle[i]);

        for (int i = 0; i < edge.size(); i++)
            this->drawSpheresOverEdge(edge[i]);

        renderSpheresOnly();
    }

    void SphereMesh::renderWithNSpherePerEdge(int n)
    {
        for (int i = 0; i < triangle.size(); i++)
            this->drawSpheresOverTriangle(triangle[i], n);

        for (int i = 0; i < edge.size(); i++)
            this->drawSpheresOverEdge(edge[i], n);
        
        renderSpheresOnly();
    }

    void SphereMesh::renderSpheresOnly()
    {
        Math::Vector3 color = Math::Vector3(1, 0, 0);

        for (int i = 0; i < sphere.size(); i++)
        {
            if (sphere[i].radius <= 0)
            {
                std::cout << "Sphere [" << i << "] has radius = " << sphere[i].radius << std::endl;
                continue;
            }

            // The point is inside the triangle
            Core::Mesh s = Core::Mesh::generateSphereMesh(this->viewer, color);

            s.resize(sphere[i].radius);
            s.translate(sphere[i].center);
            
            sphere[i].renderedMeshID = s.ID;
            
            renderedSpheres.push_back(s.ID);
        }
    }

    void SphereMesh::renderSelectedSpheresOnly()
    {
        Math::Vector3 color = Math::Vector3(0, 1, 0);
        
        CollapsableEdge e = getBestCollapseBruteForce();
        
        if (e.i.radius > 0)
        {
            // The point is inside the triangle
            Core::Mesh s = Core::Mesh::generateSphereMesh(this->viewer, color);

            auto r = e.i.radius;
            if (r > e.i.region.directionalWidth)
                r = e.i.region.directionalWidth;
            
            s.resize(r + 0.01f);
            s.translate(e.i.center);
            
            e.i.renderedMeshID = s.ID;
            
            renderedSpheres.push_back(s.ID);
        }
        
        if (e.j.radius > 0)
        {
            // The point is inside the triangle
            Core::Mesh s = Core::Mesh::generateSphereMesh(this->viewer, color);

            auto r = e.j.radius;
            if (r > e.j.region.directionalWidth)
                r = e.j.region.directionalWidth;
            
            s.resize(r + 0.01f);
            s.translate(e.j.center);
            
            e.j.renderedMeshID = s.ID;
            
            renderedSpheres.push_back(s.ID);
        }
    }

    void SphereMesh::renderFastSelectedSpheresOnly()
    {
        Math::Vector3 color = Math::Vector3(0, 1, 0);
        
        CollapsableEdge e = getBestCollapseInConnectivity();
        
        if (e.i.radius > 0)
        {
            // The point is inside the triangle
            Core::Mesh s = Core::Mesh::generateSphereMesh(this->viewer, color);

            auto r = e.i.radius;
            if (r > e.i.region.directionalWidth)
                r = e.i.region.directionalWidth;
            
            s.resize(r + 0.01f);
            s.translate(e.i.center);
            
            e.i.renderedMeshID = s.ID;
            
            renderedSpheres.push_back(s.ID);
        }
        
        if (e.j.radius > 0)
        {
            // The point is inside the triangle
            Core::Mesh s = Core::Mesh::generateSphereMesh(this->viewer, color);

            auto r = e.j.radius;
            if (r > e.j.region.directionalWidth)
                r = e.j.region.directionalWidth;
            
            s.resize(r + 0.01f);
            s.translate(e.j.center);
            
            e.j.renderedMeshID = s.ID;
            
            renderedSpheres.push_back(s.ID);
        }
    }

    void SphereMesh::renderSphereVertices(int i)
    {
        for (int idx = 0; idx < i; idx++)
            if (sphere[idx].renderedMeshID == i)
                sphere[idx].renderAssociatedVertices(this->viewer);
    }

    void SphereMesh::clearRenderedSphereVertices()
    {
        for (int idx = 0; idx < sphere.size(); idx++)
            sphere[idx].clearRenderedSpheres(viewer);
    }

    void SphereMesh::clearRenderedEdges()
    {
        viewer.data().clear_edges();
    }

    void SphereMesh::clearRenderedMeshes()
    {
        for (int i = 0; i < renderedSpheres.size(); i++)
            this->viewer.data_list[renderedSpheres[i]].clear();
        
        renderedSpheres.clear();
        viewer.data().clear_edges();
    }

    CollapsableEdge SphereMesh::selectEdgeToCollapse()
    {
        return collapseCosts.front();
    }

    Sphere SphereMesh::collapseEdgeIntoSphere(const CollapsableEdge& edgeToCollapse)
    {
        int i = edgeToCollapse.idxI;
        int j = edgeToCollapse.idxJ;
        
        Sphere collapsedSphereA = sphere[i];
        Sphere collapsedSphereB = sphere[j];
        
        Sphere newSphere = Sphere();
        newSphere.addQuadric(collapsedSphereA.getSphereQuadric());
        newSphere.addQuadric(collapsedSphereB.getSphereQuadric());
        
//      FIXME: This is done only for rendering
        for (int k = 0; k < sphere[i].vertices.size(); k++)
            newSphere.addVertex(sphere[i].vertices[k]);
        
        for (int k = 0; k < sphere[j].vertices.size(); k++)
            newSphere.addVertex(sphere[j].vertices[k]);
//
        std::cout << "New Sphere vertices -> " << sphere[j].vertices.size() + sphere[i].vertices.size() << std::endl;
        
        newSphere.region.join(collapsedSphereA.region);
        newSphere.region.join(collapsedSphereB.region);
        
        return newSphere;
    }

    void SphereMesh::collapseSphereMesh()
    {
        CollapsableEdge e = getBestCollapseBruteForce();
        Sphere newSphere = collapseEdgeIntoSphere(e);
        
        sphere[e.idxI] = newSphere;
        sphere[e.idxJ] = sphere.back();

        sphere.pop_back();
        
        updateEdgesAfterCollapse(e.idxI, e.idxJ);
        updateTrianglessAfterCollapse(e.idxI, e.idxJ);
        
        std::cout << sphere.size() << std::endl;

        removeDegenerates();
    }

    void SphereMesh::collapseSphereMeshFast()
    {
        CollapsableEdge e = getBestCollapseInConnectivity();
        Sphere newSphere = collapseEdgeIntoSphere(e);
        
        sphere[e.idxI] = newSphere;
        sphere[e.idxJ] = sphere.back();

        sphere.pop_back();

        updateEdgesAfterCollapse(e.idxI, e.idxJ);
        updateTrianglessAfterCollapse(e.idxI, e.idxJ);
        
        std::cout << sphere.size() << std::endl;

        removeDegenerates();
    }

    void SphereMesh::updateEdgesAfterCollapse(int i, int j)
    {
        int last = sphere.size();
        
        for (Edge& e : edge) {
            if (e.i == j) e.i = i;
            if (e.j == j) e.j = i;
            if (e.i == last && j != last) e.i = j;
            if (e.j == last && j != last) e.j = j;
        }
    }

    void SphereMesh::updateTrianglessAfterCollapse(int i, int j)
    {
        int last = sphere.size();
        
        for (Triangle& t : triangle) {
            if (t.i == j) t.i = i;
            if (t.j == j) t.j = i;
            if (t.k == j) t.k = i;
            if (t.i == last && j != last) t.i = j;
            if (t.j == last && j != last) t.j = j;
            if (t.k == last && j != last) t.k = j;
        }
    }

    void SphereMesh::collapseEdge(int edgeIndex)
    {
//        assert(edgeIndex < edge.size());
//        assert(edgeIndex >= 0);
//
//        CollapsableEdge e = collapseCosts[indexToCollapse];
//        Sphere newSphere = collapseEdgeIntoSphere(e);
//
//        sphere[e.idxI] = newSphere;
//        sphere[e.idxJ] = sphere.back();
//
//        int last = sphere.size() - 1;
//        sphere.pop_back();
//
//        recalculateCollapseCosts(indexToCollapse, newSphere, e.idxI, e.idxJ);
//        updateEdgesAfterCollapse(e.idxI, e.idxJ);
//        updateTrianglessAfterCollapse(e.idxI, e.idxJ);
//
//        std::cout << sphere.size() << std::endl;
//
//        removeDegenerates();
    }

    void SphereMesh::collapseTriangleSide(int triangleIndex, int sideNumber)
    {
//        assert(triangleIndex < triangle.size());
//        assert(triangleIndex >= 0);
//        assert(sideNumber <= 2 && sideNumber >= 0);
//
//        CollapsableEdge e = collapseCosts[indexToCollapse];
//        Sphere newSphere = collapseEdgeIntoSphere(e);
//
//        sphere[e.idxI] = newSphere;
//        sphere[e.idxJ] = sphere.back();
//
//        int last = sphere.size() - 1;
//        sphere.pop_back();
//
//        recalculateCollapseCosts(indexToCollapse, newSphere, e.idxI, e.idxJ);
//        updateEdgesAfterCollapse(e.idxI, e.idxJ);
//        updateTrianglessAfterCollapse(e.idxI, e.idxJ);
//
//        std::cout << sphere.size() << std::endl;
//
//        removeDegenerates();
    }

    void SphereMesh::collapseSphereMesh(int n)
    {
        while (this->sphere.size() > n)
            this->collapseSphereMesh();
    }

    void SphereMesh::collapseSphereMeshFast(int n)
    {
        while (this->sphere.size() > n)
            this->collapseSphereMeshFast();
    }

    void SphereMesh::collapse(int i, int j)
    {
        assert(i != j);
        assert(i < sphere.size());
        assert(j < sphere.size());

        if (i > j)
            std::swap(i, j);

        // Sphere newSphere = sphere[i].lerp(sphere[j], 0.5f);
        
        Sphere newSphere = Sphere();
        newSphere.addQuadric(sphere[i].getSphereQuadric());
        newSphere.addQuadric(sphere[j].getSphereQuadric());
        
//      FIXME: This is done only for rendering
        for (int k = 0; k < sphere[i].vertices.size(); k++)
            newSphere.addVertex(sphere[i].vertices[k]);
        
        for (int k = 0; k < sphere[j].vertices.size(); k++)
            newSphere.addVertex(sphere[j].vertices[k]);
//
        
        newSphere.region = sphere[i].region;
        newSphere.region.join(sphere[j].region);

        sphere[i] = newSphere;

        sphere[j] = sphere.back();

        int last = sphere.size() - 1;
        sphere.pop_back();

        for (Edge& e : edge) {
            if (e.i == j) e.i = i;
            if (e.j == j) e.j = i;
            if (e.i == last) e.i = j;
            if (e.j == last) e.j = j;
        }

        for (Triangle& t : triangle) {
            if (t.i == j) t.i = i;
            if (t.j == j) t.j = i;
            if (t.k == j) t.k = i;
            if (t.i == last) t.i = j;
            if (t.j == last) t.j = j;
            if (t.k == last) t.k = j;
        }

        removeDegenerates();
    }

    void SphereMesh::removeDegenerates()
    {
        std::vector<int> degeneratedTriangles;
        for (int i = 0; i < triangle.size(); i++)
        {
            if (triangle[i].i == triangle[i].j || triangle[i].i == triangle[i].k || triangle[i].j == triangle[i].k)
                degeneratedTriangles.push_back(i);
        }

        int reducedSize = 0;
        for (int i = 0; i < degeneratedTriangles.size(); i++)
        {
            Edge newEdge = Edge(0, 0);
            int index = degeneratedTriangles[i];

            if (triangle[index].i == triangle[index].j)
                newEdge = Edge(triangle[index].i, triangle[index].k);
            else if (triangle[index].i == triangle[index].k)
                newEdge = Edge(triangle[index].i, triangle[index].j);
            else if (triangle[index].j == triangle[index].k)
                newEdge = Edge(triangle[index].i, triangle[index].j);
            edge.push_back(newEdge);

            triangle.erase(triangle.begin() + (degeneratedTriangles[i] - reducedSize));
            reducedSize++;
        }

        std::vector<int> degeneratedEdges;
        for (int i = 0; i < edge.size(); i++)
        {
            if (edge[i].i == edge[i].j)
                degeneratedEdges.push_back(i);
        }

        reducedSize = 0;
        for (int i = 0; i < degeneratedEdges.size(); i++)
        {
            edge.erase(edge.begin() + (degeneratedEdges[i] - reducedSize));
            reducedSize++;
        }
    }

    bool SphereMesh::canCollapseSphereMesh()
    {
        return maxNumberOfCollapses() > 0;
    }

    int SphereMesh::maxNumberOfCollapses()
    {
        return collapseCosts.size();
    }

    void SphereMesh::saveYAML(const std::string& path)
    {
        YAML::Emitter out;
        
        out << YAML::Comment("Sphere Mesh YAML @ author Davide Paolillo");
        out << YAML::Key << "Spheres" << YAML::Value;
        out << YAML::BeginSeq;
            for (int i = 0; i < sphere.size(); i++)
            {
                out << YAML::BeginMap;
                    out << YAML::Key << "Center" << YAML::Value;
                    YAMLSerializeVector3(out, sphere[i].center);
                    out << YAML::Key << "Radius" << YAML::Value << sphere[i].radius;
                    out << YAML::Key << "Quadric" << YAML::Value;
                    YAMLSerializeQuadric(out, sphere[i].quadric);
                out << YAML::EndMap;
            }
        out << YAML::EndSeq;
        out << YAML::Key << "Connectivity" << YAML::Value;
        out << YAML::BeginMap;
            out << YAML::Key << "Edges" << YAML::Value;
            out << YAML::BeginSeq;
                for (int i = 0; i < edge.size(); i++)
                {
                    out << YAML::BeginMap;
                        out << YAML::Key << "E1" << YAML::Value << edge[i].i;
                        out << YAML::Key << "E2" << YAML::Value << edge[i].j;
                    out << YAML::EndMap;
                }
            out << YAML::EndSeq;
            out << YAML::Key << "Triangles" << YAML::Value;
            out << YAML::BeginSeq;
                for (int i = 0; i < triangle.size(); i++)
                {
                    out << YAML::BeginMap;
                        out << YAML::Key << "T0" << YAML::Value << triangle[i].i;
                        out << YAML::Key << "T1" << YAML::Value << triangle[i].j;
                        out << YAML::Key << "T2" << YAML::Value << triangle[i].k;
                    out << YAML::EndMap;
                }
            out << YAML::EndSeq;
        out << YAML::EndMap;
        
        
        namespace fs = std::experimental::filesystem;
        
        fs::path cwd = fs::current_path();
        
        std::ofstream fout("SphereMesh.yaml");
        std::cout << "File location: " << cwd << std::endl;
        fout << out.c_str();
        fout.close();
    }

    Sphere::Sphere()
    {
        quadric = Quadric();
        region = Region();
    }

    Sphere::Sphere(const Core::Vertex& vertex, double k)
    {
        quadric = Quadric::initializeQuadricFromVertex(vertex, 0.01) * 0.001;
        region = Region(vertex.position);

        auto result = quadric.minimizer();
        this->center = result.toQuaternion().immaginary;
        this->radius = result.coordinates.w;
        
        this->vertices.push_back(vertex);
    }

    Sphere::Sphere(const Math::Vector3& center, double radius)
    {
        this->center = center;
        this->radius = radius;
    }

    Quadric Sphere::getSphereQuadric()
    {
        return this->quadric;
    }

    void Sphere::addFace(const Math::Vector3& centroid, const Math::Vector3& normal, double weight)
    {
        this->quadric += (Quadric(centroid, normal) * weight);

        auto result = quadric.minimizer();
        this->center = result.toQuaternion().immaginary;
        this->radius = result.coordinates.w;
//        this->radius = Math::Math::clamp(0.0, DBL_MAX, this->radius);

         if (this->radius > this->region.directionalWidth)
             this->radius = this->region.directionalWidth;
        
//        this->radius = Math::Math::clamp(0.01, DBL_MAX, this->radius);
    }

    void Sphere::addQuadric(const Quadric& q)
    {
        this->quadric += q;

        auto result = quadric.minimizer();
        this->center = result.toQuaternion().immaginary;
        this->radius = result.coordinates.w;
//        this->radius = Math::Math::clamp(0.0, DBL_MAX, this->radius);

         if (this->radius > this->region.directionalWidth)
             this->radius = this->region.directionalWidth;
        
//        this->radius = Math::Math::clamp(0.01, DBL_MAX, this->radius);
    }

    void Sphere::addVertex(const Core::Vertex& vertex)
    {
        vertices.push_back(vertex);
    }

    void Sphere::renderAssociatedVertices(igl::opengl::glfw::Viewer &viewer)
    {
        const Math::Vector3 color = Math::Vector3(0, 1, 0);
        
        for (int i = 0; i < vertices.size(); i++)
        {
            // The point is inside the triangle
            Core::Mesh s = Core::Mesh::generateSphereMesh(viewer, color);
            
            s.resize(0.01f);
            s.translate(vertices[i].position);
            
            renderedSpheres.push_back(s.ID);
        }
    }

    void Sphere::clearRenderedSpheres(igl::opengl::glfw::Viewer &viewer)
    {
        for (int i = 0; i < renderedSpheres.size(); i++)
            viewer.data_list[renderedSpheres[i]].clear();
        
        renderedSpheres.clear();
    }

    Sphere Sphere::lerp(const Sphere &s, double t)
    {
        Math::Vector4 origin(this->center, this->radius);
        Math::Vector4 destination(s.center, s.radius);

        auto result = origin.lerp(destination, t);

        return Sphere(result.toQuaternion().immaginary, result.coordinates.w);
    }

    std::vector<Math::Vector3> Region::unitSphereSampler(int numDirections)
    {
        std::vector<Math::Vector3> d;

        // add the 3 canonical axes
        d.push_back(Math::Vector3(1, 0, 0));
        d.push_back(Math::Vector3(0, 1, 0));
        d.push_back(Math::Vector3(0, 0, 1));

        // add the other directions
        double goldenRatio = (1.0 + std::sqrt(5.0)) / 2.0;
        double angleIncrement = 2.0 * M_PI / goldenRatio;
        double inclinationIncrement = 2.0 / numDirections;

        for (int i = 0; i < numDirections; i++) {
            double inclination = std::acos(1.0 - (i + 0.5) * inclinationIncrement);
            double azimuth = fmod((i + 0.5) * angleIncrement, 2.0 * M_PI);
            double x = std::sin(inclination) * std::cos(azimuth);
            double y = std::sin(inclination) * std::sin(azimuth);
            double z = std::cos(inclination);
            d.push_back(Math::Vector3(x, y, z));
        }

        return d;
    }

    void Region::initializeIntervals()
    {
        auto k = Region::directions;
        
        for (int j = 0; j < k.size(); j++)
        {
            double m = DBL_MAX;
            double M = -DBL_MAX;
            
            intervals.push_back(Math::Vector2(m, M));
        }
    }

    void Region::addVertex(const Math::Vector3& v)
    {
        auto k = Region::directions;

        for (int j = 0; j < k.size(); j++)
        {
            double m = intervals[j][0];
            double M = intervals[j][1];

            m = std::min(m, v.dot(k[j]));
            M = std::max(M, v.dot(k[j]));
            
            intervals[j] = Math::Vector2(m, M);
        }

        this->computeIntervals();
    }

    void Region::addVertices(const std::vector<Math::Vector3>& verticesRange)
    {
        auto k = Region::directions;

        for (int j = 0; j < k.size(); j++)
        {
            double m = intervals[j][0];
            double M = intervals[j][1];

            for (int i = 0; i < verticesRange.size(); i++)
            {
                m = std::min(m, verticesRange[i].dot(k[j]));
                M = std::max(M, verticesRange[i].dot(k[j]));
            }
            
            intervals[j] = Math::Vector2(m, M);
        }

        this->computeIntervals();
    }

    void Region::computeIntervals()
    {
        directionalWidth = DBL_MAX;

        for (int i = 0; i < intervals.size(); i++)
            directionalWidth = std::min(directionalWidth, std::abs(intervals[i].coordinates.y - intervals[i].coordinates.x));
        
        directionalWidth *= (3.0/4.0);
    }

    void Region::join(Region& region)
    {
        directionalWidth = DBL_MAX;
        for (int i = 0; i < intervals.size(); i++)
            intervals[i] = Math::Vector2(std::min(intervals[i].coordinates.x, region.intervals[i].coordinates.x),
                                         std::max(intervals[i].coordinates.y, region.intervals[i].coordinates.y));
        
        // Recalculating the new directional width
        for (int i = 0; i < intervals.size(); i++)
            directionalWidth = std::min(directionalWidth, std::abs(intervals[i].coordinates.y - intervals[i].coordinates.x));

        directionalWidth *= (3.0/4.0);
    }
}
