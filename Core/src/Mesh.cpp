#include "../Mesh.hpp"

#include "../SQEM.h"

#include <igl/triangle/triangulate.h>
#include <igl/readOBJ.h>
#include <igl/centroid.h>
#include <igl/opengl/glfw/Viewer.h>
// #include <igl/translate.h>

namespace Core {
    Mesh::Mesh(igl::opengl::glfw::Viewer &currentViewer) : ID(this->ID), viewer(currentViewer) {
        this->_ID = -1;
    }

    Mesh::Mesh(const Eigen::MatrixXd& v, const Eigen::MatrixXi& f, const Eigen::MatrixXd& n, igl::opengl::glfw::Viewer &currentViewer) : ID(this->_ID), viewer(currentViewer) {
        this->_ID = -1;

        this->v = v;
        this->f = f;
        this->n = n;

        this->triangulateQuads(this->v,this->f, this->n);

        // Translate the mesh to the origin
        this->v = this->v.rowwise() - getCenterOfMass();
        std::cout << "Centroid: " << getCenterOfMass() << std::endl;

        matrixToVertices();
        matrixToFaces();
        matrixToNormals();
    }

    Mesh::Mesh(const std::string &&path, igl::opengl::glfw::Viewer &currentViewer) : ID(this->_ID), viewer(currentViewer) {
        this->_ID = -1;

        igl::readOBJ(path, v, f);
        igl::per_face_normals(v, f, n);

        this->triangulateQuads(v, f, n);

        // Translate the mesh to the origin
        v = v.rowwise() - getCenterOfMass();

        std::cout << "Centroid: " << getCenterOfMass() << std::endl;
        igl::per_face_normals(v, f, n);

        std::cout << "Radius: " << getRadius() << std::endl;
        
        matrixToVertices();
        matrixToFaces();
        matrixToNormals();
    }

    void Mesh::matrixToVertices() {
        for (int i = 0; i < v.rows(); i++)
            vertices.push_back(Math::Vector3(v(i, 0), v(i, 1), v(i, 2)));
    }

    void Mesh::matrixToNormals() {
        for (int i = 0; i < n.rows(); i++)
            normals.push_back(Math::Vector3(n(i, 0), n(i, 1), n(i, 2)));
    }

    void Mesh::matrixToFaces() {
        for (int i = 0; i < f.rows(); i++) {
            faces.push_back(f(i, 0));
            faces.push_back(f(i, 1));
            faces.push_back(f(i, 2));
        }
    }

    Eigen::RowVector3d Mesh::getCenterOfMass()
    {
        Eigen::RowVector3d centroid;
        igl::centroid(v, f, centroid);

        return centroid;
    }

    double Mesh::getRadius() {
        // Compute the maximum distance between the center and any vertex
        double max_distance = 0;

        auto centerOfMass = getCenterOfMass();

        for (int i = 0; i < v.rows(); i++)
        {
            double dist = (v.row(i) - centerOfMass).norm();
            if (dist > max_distance)
            {
                max_distance = dist;
            }
        }

        // Compute radius
        double radius = max_distance;

        return radius;
    }

    void Mesh::triangulateQuads(Eigen::MatrixXd &V, Eigen::MatrixXi &F, Eigen::MatrixXd &N) {
        // Check if the mesh is made of quads
        if (F.cols() == 4)
        {
            // Triangulate the mesh
            Eigen::MatrixXd V_out;
            Eigen::MatrixXi F_out;
            Eigen::MatrixXd H(0, 0);

            igl::triangle::triangulate(V, F, H, "", V_out, F_out);

            // Replace the old mesh with the new triangulated mesh
            V_out.colwise().normalize();
            V_out *= 0.5;
            V = V_out;
            F = F_out;

            igl::per_face_normals(V, F, N);

            std::cout << "Mesh was triangulated!" << std::endl;
        }
        else if (F.cols() == 3)
            std::cout << "Mesh is already triangulated!" << std::endl;
        else
            std::cerr << "Mesh contains neither triangles nor quads!" << std::endl;
    }

    void Mesh::addToScene() {
        this->_ID = viewer.append_mesh();

        std::cout << "Mesh added to scene with ID " << this->_ID << std::endl;

        viewer.data_list[this->ID].set_mesh(v, f);
        viewer.data_list[this->ID].set_normals(n);
    }

    void Mesh::test() {
        Math::Vector3 sphereCenter;
        float sphereRadius;
        const float MAX_RADIUS = 10.f;
        
        SQEM sqem(vertices[0], normals[0]);
        for (int i = 1; i < vertices.size(); i++)
            sqem += SQEM(vertices[i], normals[i]);

        sqem.minimize(sphereCenter, sphereRadius, Math::Vector3(-MAX_RADIUS, -MAX_RADIUS, -MAX_RADIUS), Math::Vector3(MAX_RADIUS, MAX_RADIUS, MAX_RADIUS));

        std::cout << "    Result: optimal sphere centered at [" << sphereCenter[0] << ", " << sphereCenter[1] << ", " << sphereCenter[2] << "], with radius " << sphereRadius << "." << std::endl;
        Mesh sphere("/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Assets/Models/Sphere.obj", this->viewer);
        sphere.addToScene();
        auto radius = sphere.getRadius();
        // setting sphere as unitary sphere
        sphere.resize(1 / radius);
        sphere.resize(sphereRadius);
        sphere.translate(sphereCenter);
        std::cout << sphere.getCenterOfMass() << std::endl;
        std::cout << sphere.getRadius() << std::endl;
    }

    void Mesh::resize(const double&& size) {
        for (int i = 0; i < v.rows(); i++) {
            v.row(i)[0] *= size;
            v.row(i)[1] *= size;
            v.row(i)[2] *= size;
        }
        matrixToVertices();
        igl::per_face_normals(this->v, this->f, this->n);
        matrixToNormals();

        viewer.data_list[this->ID].set_mesh(v, f);
        viewer.data_list[this->ID].set_normals(n);
    }

    void Mesh::resize(const Math::Vector3& size) {
        for (int i = 0; i < v.rows(); i++) {
            v.row(i)[0] *= size[0];
            v.row(i)[1] *= size[1];
            v.row(i)[2] *= size[2];
        }
        matrixToVertices();
        igl::per_face_normals(this->v, this->f, this->n);
        matrixToNormals();

        viewer.data_list[this->ID].set_mesh(v, f);
        viewer.data_list[this->ID].set_normals(n);
    }

    void Mesh::translate(const Math::Vector3& translation) {
        for (int i = 0; i < v.rows(); i++) {
            v.row(i)[0] += translation[0];
            v.row(i)[1] += translation[1];
            v.row(i)[2] += translation[2];
        }
        matrixToVertices();
        igl::per_face_normals(this->v, this->f, this->n);
        matrixToNormals();

        viewer.data_list[this->ID].set_mesh(v, f);
        viewer.data_list[this->ID].set_normals(n);
    }

    Mesh::~Mesh() {
        // TODO
    }
}