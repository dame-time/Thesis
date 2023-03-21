#include "../SphereMesh.hpp"

#include "../SQEM.h"

#include <Math.hpp>

#include <algorithm>
#include <cassert>
#include <cmath>

namespace SM {
    std::vector<Math::Vector3> Region::directions;

    SphereMesh::SphereMesh(const Core::Mesh &mesh, igl::opengl::glfw::Viewer &currentViewer, double vertexSphereRadius) : viewer(currentViewer)
    {
        auto vertices = mesh.vertices;
        auto faces = mesh.faces;

        initializeSphereMeshTriangles(faces);
        initializeSpheres(vertices);
        
        computeSpheresProperties(vertices);
        
        setCollapseCosts();
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
        const double EPSILON = 0.1;
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

    void SphereMesh::computeSpheresProperties(const std::vector<Core::Vertex>& vertices)
    {
        for (int i = 0; i < sphere.size(); i++)
        {
            for (int j = 0; j < triangle.size(); j++)
            {
                if (triangle[j].i == i || triangle[j].j == i || triangle[j].k == i)
                {
                    // Getting neighbor face normal and centroid in order to add the face to our sphere
                    auto centroid = getTriangleCentroid(vertices[triangle[j].i].position, vertices[triangle[j].j].position, vertices[triangle[j].k].position);
                    auto normal = getTriangleNormal(vertices[triangle[j].i].position, vertices[triangle[j].j].position, vertices[triangle[j].k].position);

                    sphere[i].addFace(centroid, normal);
                    sphere[i].region.addVertex(vertices[triangle[j].i].position);
                    sphere[i].region.addVertex(vertices[triangle[j].j].position);
                    sphere[i].region.addVertex(vertices[triangle[j].k].position);
                    sphere[i].region.computeIntervals();
                }
            }
        }
        
//        const double THRESHOLD = 0.0001;
//        for (auto it = sphere.begin(); it != sphere.end();)
//        {
//            if (it->radius <= THRESHOLD)
//                sphere.erase(it);
//            else
//                it++;
//        }
//
//        for (auto s : sphere)
//            std::cout << "Sphere with radius: " << s.radius << std::endl;
    }

    std::set<int> SphereMesh::getNeighborVertices(int i)
    {
        std::set<int> neighborhood;
        
        neighborhood.insert(i);
        
        for (int j = 0; j < triangle.size(); j++)
        {
            if (j == i)
                continue;
            
            if (triangle[j].i == i || triangle[j].j == i || triangle[j].k == i)
                neighborhood.insert(j);
        }
        
        return neighborhood;
    }

    void SphereMesh::getVertexAdjacentTriangles(int vertexIndex, std::vector<Triangle> &adjacentTraingles)
    {
        for (Triangle t : triangle)
            if (t.i == vertexIndex || t.j == vertexIndex || t.k == vertexIndex)
                adjacentTraingles.push_back(t);
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

    void SphereMesh::drawSpheresOverEdge(const Edge &e)
    {
        int nSpheres = 4;

        const Math::Vector3 color = Math::Vector3(0.1, 0.7, 1);

        for (int i = 1; i < nSpheres - 1; i++)
        {
            Core::Mesh s = Core::Mesh::generateSphereMesh(this->viewer, color);

            s.resize(Math::lerp(sphere[e.i].radius, sphere[e.j].radius, i * 1.0 / (nSpheres - 1)));
            s.translate(Math::lerp(sphere[e.i].center, sphere[e.j].center, i * 1.0 / (nSpheres - 1)));
            
            renderedSpheres.push_back(s.ID);
        }
    }

    void SphereMesh::drawSpheresOverTriangle(const Triangle& e)
    {
        Math::Vector3 color = Math::Vector3(0.1, 0.7, 1);

        int nSpheres = 4;

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

    void SphereMesh::render()
    {
        for (int i = 0; i < triangle.size(); i++)
            this->drawSpheresOverTriangle(triangle[i]);

        for (int i = 0; i < edge.size(); i++)
            this->drawSpheresOverEdge(edge[i]);

        renderSpheresOnly();
    }


    void SphereMesh::renderSpheresOnly()
    {
        Math::Vector3 color = Math::Vector3(1, 0, 0);

        for (int i = 0; i < sphere.size(); i++)
        {
            if (sphere[i].radius <= 0)
                continue;

            // The point is inside the triangle
            Core::Mesh s = Core::Mesh::generateSphereMesh(this->viewer, color);

            s.resize(sphere[i].radius);
            s.translate(sphere[i].center);
            
            renderedSpheres.push_back(s.ID);
        }
    }

    void SphereMesh::renderSelectedSpheresOnly()
    {
        Math::Vector3 color = Math::Vector3(0, 1, 0);
        
        CollapsableEdge e = selectEdgeToCollapse();
        
        if (e.i.radius > 0)
        {
            // The point is inside the triangle
            Core::Mesh s = Core::Mesh::generateSphereMesh(this->viewer, color);

            auto r = e.i.radius;
            if (r > e.i.region.directionalWidth)
                r = e.i.region.directionalWidth;
            
            s.resize(r + 0.01f);
            s.translate(e.i.center);
            
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
            
            renderedSpheres.push_back(s.ID);
        }
    }

    void SphereMesh::clearRenderedMeshes()
    {
        for (int i = 0; i < renderedSpheres.size(); i++)
            this->viewer.data_list[renderedSpheres[i]].clear();
        
        renderedSpheres.clear();
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
        newSphere.region.join(collapsedSphereA.region);
        newSphere.region.join(collapsedSphereB.region);
        
        return newSphere;
    }

    void SphereMesh::collapseSphereMesh()
    {
        CollapsableEdge e = selectEdgeToCollapse();
        
        std::pop_heap(collapseCosts.begin(), collapseCosts.end(), CollapsableEdgeErrorComparator());
        collapseCosts.pop_back();
        
        int i = e.idxI;
        int j = e.idxJ;
        
        Sphere newSphere = collapseEdgeIntoSphere(e);
        
        sphere[i] = newSphere;

        sphere[j] = sphere.back();

        int last = sphere.size() - 1;
        sphere.pop_back();
        
        for (int idx = 0; idx < collapseCosts.size(); idx++)
        {
            if (collapseCosts[idx].containsIndex(i))
            {
                if (collapseCosts[idx].idxI == i)
                {
                    collapseCosts[idx].i = sphere[i];
                }
                else
                {
                    collapseCosts[idx].j = sphere[i];
                }

                collapseCosts[idx].updateError();
            }
            else if (collapseCosts[idx].containsIndex(j))
            {
                if (collapseCosts[idx].idxI == j)
                {
                    collapseCosts[idx].updateEdge(newSphere, collapseCosts[idx].j, i, collapseCosts[idx].idxJ);
                }
                else
                {
                    collapseCosts[idx].updateEdge(collapseCosts[idx].i, newSphere, collapseCosts[idx].idxI, i);
                }
            }

            if (collapseCosts[idx].containsIndex(last))
            {
                if (collapseCosts[idx].idxI == last)
                {
                    collapseCosts[idx].updateEdge(sphere[j], collapseCosts[idx].j, j, collapseCosts[idx].idxJ);
                }
                else
                {
                    collapseCosts[idx].updateEdge(collapseCosts[idx].i, sphere[j], collapseCosts[idx].idxI, j);
                }
            }
        }
        std::make_heap (collapseCosts.begin(), collapseCosts.end(), CollapsableEdgeErrorComparator());

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
        
        std::cout << sphere.size() << std::endl;

        removeDegenerates();
    }

    void SphereMesh::collapseSphereMesh(int n)
    {
        while (this->sphere.size() > n)
        {
            this->collapseSphereMesh();
        }
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

    Sphere::Sphere()
    {
        quadric = Quadric();
        region = Region();
    }

    Sphere::Sphere(const Core::Vertex& vertex, double k)
    {
        quadric = Quadric::initializeQuadricFromVertex(vertex, 0.1) * 0.001;
        region = Region(vertex.position);

        auto result = quadric.minimizer();
        this->center = result.toQuaternion().immaginary;
        this->radius = result.coordinates.w;
        this->radius = Math::Math::clamp(0.01, DBL_MAX, this->radius);

//         if (this->radius > this->region.directionalWidth)
//             this->radius = this->region.directionalWidth;
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

    void Sphere::addFace(const Math::Vector3& centroid, const Math::Vector3& normal)
    {
        this->quadric += Quadric(centroid, normal);

        auto result = quadric.minimizer();
        this->center = result.toQuaternion().immaginary;
        this->radius = result.coordinates.w;
        this->radius = Math::Math::clamp(0.0, DBL_MAX, this->radius);

         if (this->radius > this->region.directionalWidth)
             this->radius = this->region.directionalWidth;
        
        this->radius = Math::Math::clamp(0.01, DBL_MAX, this->radius);
    }

    void Sphere::addQuadric(const Quadric& q)
    {
        this->quadric += q;

        auto result = quadric.minimizer();
        this->center = result.toQuaternion().immaginary;
        this->radius = result.coordinates.w;
        this->radius = Math::Math::clamp(0.0, DBL_MAX, this->radius);

         if (this->radius > this->region.directionalWidth)
             this->radius = this->region.directionalWidth;
        
        this->radius = Math::Math::clamp(0.01, DBL_MAX, this->radius);
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

    void Region::addVertex(const Math::Vector3& v)
    {
        this->vertices.push_back(v);

        this->computeIntervals();
    }

    void Region::addVertices(const std::vector<Math::Vector3>& verticesRange)
    {
        for (auto v : verticesRange)
        {
            this->vertices.push_back(v);
        }

        this->computeIntervals();
    }

    void Region::computeIntervals()
    {
        directionalWidth = DBL_MAX;
        intervals.clear();

        auto k = Region::directions;

        for (int j = 0; j < k.size(); j++)
        {
            double m = DBL_MAX;
            double M = DBL_MIN;

            for (int i = 0; i < this->vertices.size(); i++)
            {
                m = std::min(m, this->vertices[i].dot(k[j]));
                M = std::max(M, this->vertices[i].dot(k[j]));
            }

            intervals.push_back(Math::Vector2(m, M));
        }

        for (int i = 0; i < intervals.size(); i++)
            directionalWidth = std::min(directionalWidth, std::abs(intervals[i].coordinates.y - intervals[i].coordinates.x));
        
        directionalWidth *= (3.0/4.0);
    }

    void Region::join(const Region& region)
    {
        directionalWidth = DBL_MAX;
        for (int i = 0; i < intervals.size(); i++)
            intervals[i] = Math::Vector2(std::min(intervals[i].coordinates.x, region.intervals[i].coordinates.x),
                                         std::max(intervals[i].coordinates.y, region.intervals[i].coordinates.y));
        
        // Recalculating the new directional width
        for (int i = 0; i < intervals.size(); i++)
            directionalWidth = std::min(directionalWidth, std::abs(intervals[i].coordinates.y - intervals[i].coordinates.x));

        // directionalWidth = std::abs(std::min(directionalWidth, intervals[i].coordinates.y - intervals[i].coordinates.x));
        directionalWidth *= (3.0/4.0);
    }
}
