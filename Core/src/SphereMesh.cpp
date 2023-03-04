#include "../SphereMesh.hpp"

#include "../SQEM.h"

#include <algorithm>
#include <cassert>

namespace SM {
    SphereMesh::SphereMesh(const Core::Mesh &mesh, igl::opengl::glfw::Viewer &currentViewer) : viewer(currentViewer)
    {
        this->vertices = mesh.vertices;

        for (int i = 0; i < mesh.faces.size(); i += 3) 
        {
            Triangle t;

            t.i = mesh.faces[i];
            t.j = mesh.faces[i + 1];
            t.k = mesh.faces[i + 2];

            triangle.push_back(t);
        }

        for (int i = 0; i < vertices.size(); i++)
        {
            std::vector<Triangle> vertexFaces;

            getVertexAdjacentTriangles(i, vertexFaces);

            Math::Vector3 globalNormal;

            for (int j = 0; j < vertexFaces.size(); j++)
            {
                auto centroid = getTriangleCentroid(vertexFaces[j]);
                auto normal = getTriangleNormal(vertexFaces[j]);
                
                globalNormal += normal;
            }

            globalNormal /= vertexFaces.size();
            globalNormal.normalize();

            auto vertexNormal = globalNormal;
            auto sphereDisplacedPosition = vertexNormal;

            Math::Vector3 sphereCenter = sphereDisplacedPosition;
            float sphereRadius = 1;
            

            Sphere sqemSphere(sphereCenter, sphereRadius);
            sphere.push_back(sqemSphere);

            // if (i == 0)
            // {
            //     auto s = Core::Mesh::generateSphereMesh(this->viewer);

            //     s.addToScene();
            //     // setting sphere as unitary sphere
            //     auto r = s.getRadius();
            //     s.resize(1 / r);

            //     s.resize(0.05f);
            //     s.translate(vertices[i]);
            // }
        }

        // for (int i = 0; i < 1; i++)
        // {
        //     auto s = Core::Mesh::generateSphereMesh(this->viewer);

        //     s.addToScene();
        //     // setting sphere as unitary sphere
        //     auto r = s.getRadius();
        //     s.resize(1 / r);

        //     s.resize(sphere[i].radius);
        //     s.translate(sphere[i].center);

        //     s.setMeshNotFilled();
        // }
    }

    void SphereMesh::initialize()
    {
        // for (int i = 0; i < vertices.size(); i++)
        // {
        //     std::vector<Triangle> vertexFaces;

        //     getVertexAdjacentTriangles(i, vertexFaces);

        //     SQEM sqem;

        //     for (int j = 0; j < vertexFaces.size(); j++)
        //     {
        //         auto centroid = getTriangleCentroid(vertexFaces[j]);
        //         auto normal = getTriangleNormal(vertexFaces[j]);

        //         sqem += SQEM(centroid, normal);
        //     }

        //     Math::Vector3 sphereCenter;
        //     float sphereRadius;

        //     Sphere sqemSphere(sphereCenter, sphereRadius);
        //     sphere.push_back(sqemSphere);
        // }

        // for (int i = 0; i < sphere.size(); i++)
        // {
        //     Core::Mesh s("/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Assets/Models/Sphere.obj", this->viewer);

        //     s.addToScene();
        //     // setting sphere as unitary sphere
        //     auto r = s.getRadius();
        //     s.resize(1 / r);

        //     s.resize(sphere[i].radius);
        //     s.translate(sphere[i].center);
        // }
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

    Math::Vector3 SphereMesh::getTriangleCentroid(const Triangle &t)
    {
        return getTriangleCentroid(vertices[t.i], vertices[t.j], vertices[t.k]);
    }

    Math::Vector3 SphereMesh::getTriangleNormal(const Math::Vector3 &v1, const Math::Vector3 &v2, const Math::Vector3 &v3)
    {
        return (v2 - v1).cross(v3 - v1);
    }

    Math::Vector3 SphereMesh::getTriangleNormal(const Triangle &t)
    {
        return getTriangleNormal(vertices[t.i], vertices[t.j], vertices[t.k]);
    }

    int SphereMesh::getIndexFromVertex(const Math::Vector3 &vertex)
    {
        for (int i = 0; i < vertices.size(); i++)
            if (vertices[i] == vertex)
                return i;

        return -1;
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
        vertices.clear();
    }

    void SphereMesh::drawSpheresOverEdge(const Edge &e) const
    {
        auto start = Math::Vector4(sphere[e.i].center, sphere[e.i].radius);
        auto end = Math::Vector4(sphere[e.j].center, sphere[e.j].radius);

        double radius = 0.05;
        double diameter = radius * 2;

        double length = (double)(start - end).magnitude();
        int fittableSpheres = length / diameter;

        for (int i = 0; i <= fittableSpheres; i++)
        {
            auto s = Core::Mesh::generateSphereMesh(this->viewer);

            s->addToScene();
            // setting sphere as unitary sphere
            auto r = s->getRadius();
            s->resize(1 / r);

            auto newSphere = start.lerp(end, (i * diameter) / length);
            auto newPos = newSphere.toQuaternion().immaginary; // It's not a Quaternion, used so I easily get the first three components
            auto newSphereRadius = newSphere.coordinates.w;

            s->resize(newSphereRadius);
            s->translate(newPos);

            if ((newSphere - start).squareMagnitude() <= 0.01f || (newSphere - end).squareMagnitude() <= 0.01f)
            {
                Eigen::MatrixXd C(s->f.rows(), 3);
                C.rowwise() = Eigen::RowVector3d(1, 0, 0); // set all rows to red initially

                this->viewer.data_list[s->ID].set_colors(C);
            }
        }
    }

    void SphereMesh::drawSpheresOverTriangle(const Math::Vector4 &a, const Math::Vector4 &b, const Math::Vector4 &c) const
    {
        // Compute bounding box of the triangle
        Math::Vector4 min(std::min({a.coordinates.x, b.coordinates.x, c.coordinates.x}), std::min({a.coordinates.y, b.coordinates.y, c.coordinates.y}), std::min({a.coordinates.z, b.coordinates.z, c.coordinates.z}), 0);
        Math::Vector4 max(std::max({a.coordinates.x, b.coordinates.x, c.coordinates.x}), std::max({a.coordinates.y, b.coordinates.y, c.coordinates.y}), std::max({a.coordinates.z, b.coordinates.z, c.coordinates.z}), 0);

        double radius = 0.05;
        double diameter = radius * 2;

        // Iterate over all the points inside the bounding box of the triangle
        for (double x = min.coordinates.x; x <= max.coordinates.x; x += diameter)
        {
            for (double y = min.coordinates.y; y <= max.coordinates.y; y += diameter)
            {
                for (double z = min.coordinates.z; z <= max.coordinates.z; z += diameter)
                {
                    Math::Vector4 p(x, y, z, 0);

                    // Check if the point is inside the triangle
                    double u, v, w;
                    Math::Vector4 ab = b - a;
                    Math::Vector4 ac = c - a;
                    Math::Vector4 ap = p - a;
                    double denom = ab.dot(ab) * ac.dot(ac) - ab.dot(ac) * ab.dot(ac);
                    u = (ac.dot(ac) * ab.dot(ap) - ab.dot(ac) * ac.dot(ap)) / denom;
                    v = (ab.dot(ab) * ac.dot(ap) - ab.dot(ac) * ab.dot(ap)) / denom;
                    w = 1.0 - u - v;
                    if (u >= 0 && v >= 0 && w >= 0)
                    {
                        // The point is inside the triangle
                        Core::Mesh *s = Core::Mesh::generateSphereMesh(this->viewer);
                        s->addToScene();

                        // Interpolate position and radius
                        auto newPos = a.lerp(b, u).lerp(c, v);
                        auto newRadius = a.coordinates.w * u + b.coordinates.w * v + c.coordinates.w * w;

                        // Resize and translate sphere
                        s->resize(newPos.coordinates.w);
                        s->translate(newPos.toQuaternion().immaginary);

                        // Color if it's close to one of the input points
                        if ((newPos - a).squareMagnitude() <= 0.05f || (newPos - b).squareMagnitude() <= 0.05f || (newPos - c).squareMagnitude() <= 0.05f)
                        {
                            Eigen::MatrixXd C(s->f.rows(), 3);
                            C.rowwise() = Eigen::RowVector3d(1, 0, 0); // set all rows to red initially

                            s->resize(1.1f);

                            this->viewer.data_list[s->ID].set_colors(C);
                        }
                    }
                }
            }
        }
    }

    void SphereMesh::render() const
    {
        for (int i = 0; i < triangle.size(); i++) {
            auto v0 = Math::Vector4(sphere[triangle[i].i].center, sphere[triangle[i].i].radius);
            auto v1 = Math::Vector4(sphere[triangle[i].j].center, sphere[triangle[i].j].radius);
            auto v2 = Math::Vector4(sphere[triangle[i].k].center, sphere[triangle[i].k].radius);

            this->drawSpheresOverTriangle(v0, v1, v2);
        }

        for (int i = 0; i < edge.size(); i++)
            this->drawSpheresOverEdge(edge[i]);
    }

    void SphereMesh::collapse(int i, int j)
    {
        assert(i != j);

        if (i > j)
            std::swap(i, j);

        Sphere newSphere = sphere[i].lerp(sphere[j], 0.5f);
        sphere[i] = newSphere;

        sphere[j] = sphere.back();
        sphere.pop_back();

        int last = sphere.size() - 1;

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
            if (t.k == last) t.j = j;
        }

        removeDegenerates();
    }

    void SphereMesh::removeDegenerates()
    {

    }

    Sphere::Sphere()
    {

    }

    Sphere::Sphere(Math::Vector3 center, double radius)
    {
        this->center = center;
        this->radius = radius;
    }

    Sphere Sphere::lerp(const Sphere &s, double t)
    {
        return Sphere();
    }
}
