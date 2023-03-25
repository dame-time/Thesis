#include "../Mesh.hpp"

#include "../SQEM.h"
#include "../MinimumBoundingSphere.hpp"

#include <igl/triangle/triangulate.h>
#include <igl/readOBJ.h>
#include <igl/centroid.h>
#include <igl/opengl/glfw/Viewer.h>
#include <igl/per_face_normals.h>
#include <igl/principal_curvature.h>

#include <igl/is_edge_manifold.h>
#include <igl/qslim.h>

#include <igl/boundary_loop.h>
#include <igl/edge_topology.h>
#include <igl/edge_flaps.h>
#include <igl/remove_unreferenced.h>
#include <igl/boundary_facets.h>

#include <igl/unique_edge_map.h>

#include <cmath>

namespace Core {
    Mesh::Mesh(igl::opengl::glfw::Viewer &currentViewer) : ID(this->ID), viewer(currentViewer) {
        this->_ID = -1;
    }

    Mesh::Mesh(const Eigen::MatrixXd& v, const Eigen::MatrixXi& f, const Eigen::MatrixXd& n, igl::opengl::glfw::Viewer &currentViewer) : ID(this->_ID), viewer(currentViewer) {
        this->_ID = -1;

        this->v = v;
        this->f = f;
        this->n = n;

        // this->triangulateQuads(this->v,this->f, this->n);

        // Translate the mesh to the origin
        this->v = this->v.rowwise() - getCenterOfMass();

        matrixToVertices();
        matrixToFaces();
    }

    Mesh::Mesh(const std::string& path, igl::opengl::glfw::Viewer &currentViewer) : ID(this->_ID), viewer(currentViewer) {
        this->_ID = -1;

        igl::readOBJ(path, v, f);
        igl::per_face_normals(v, f, n);

        this->triangulateQuads(v, f, n);

        // Translate the mesh to the origin
        v = v.rowwise() - getCenterOfMass();

        igl::per_face_normals(v, f, n);

        matrixToVertices();
        matrixToFaces();
        
        computePerVertexCurvature();
    }

    void Mesh::matrixToVertices() {
        vertices.clear();

        for (int i = 0; i < v.rows(); i++)
            vertices.push_back(Vertex(Math::Vector3(v(i, 0), v(i, 1), v(i, 2)), Math::Vector3(n(i, 0), n(i, 1), n(i, 2))));
    }

    void Mesh::matrixToFaces() {
        faces.clear();

        for (int i = 0; i < f.rows(); i++)
            faces.push_back(Face(f(i, 0), f(i, 1), f(i, 2)));
    }

    void Mesh::computePerVertexCurvature()
    {
        Eigen::MatrixXd PD1, PD2;
        Eigen::VectorXd PV1, PV2;
        
        std::vector<int> bad_vertices;
        
        igl::principal_curvature(this->v, this->f, PD1, PD2, PV1, PV2, bad_vertices);
        
        for (int i = 0; i < this->vertices.size(); i++)
            vertices[i].curvature = Math::Vector2(PV1(i, 0), PV2(i, 0));
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
        }
    }

    void Mesh::addToScene() {
        this->_ID = viewer.append_mesh();

        viewer.data_list[this->ID].set_mesh(v, f);
        viewer.data_list[this->ID].set_normals(n);
    }

    
    Eigen::Matrix4d Mesh::computeQuadric(const Eigen::MatrixXd& V, const Eigen::MatrixXi& F, int vtx) {
        Eigen::Matrix4d Q = Eigen::Matrix4d::Zero();

        for (int i = 0; i < F.rows(); i++)
        {
            if (F(i, 0) == vtx || F(i, 1) == vtx || F(i, 2) == vtx)
            {
                Eigen::RowVector3d p1 = V.row(F(i, 0));
                Eigen::RowVector3d p2 = V.row(F(i, 1));
                Eigen::RowVector3d p3 = V.row(F(i, 2));
                Eigen::RowVector3d n = (p2 - p1).cross(p3 - p1);
                double area = n.norm() / 2.0;
                n.normalize();
                double d = -n.dot(p1);
                Eigen::RowVector4d plane(n(0), n(1), n(2), d);
                Q += area * plane.transpose() * plane;
            }
        }

        return Q;
    }

    void Mesh::simplifyMesh(const int& targetVertices)
    {
        auto isManifold = igl::is_edge_manifold(f);
        if (isManifold == false)
        {
            std::cout << "Mesh is not manifold!" << std::endl;
            return;
        }

        std::cout << "Vertices before: " << v.rows() << std::endl;
        std::cout << "Faces before: " << f.rows() << std::endl;

        // Initialize simplified mesh with the original mesh
        // Eigen::MatrixXd vtx = v;
        // Eigen::MatrixXi fcs = f;
        // Eigen::VectorXi J, I;

        // std::cout << v.size() << std::endl;

        // igl::qslim(v, f, targetVertices, vtx, fcs, J, I);

        // std::cout << vtx.size() << std::endl;

        // v = vtx;
        // f = fcs;

        simplify_quadric_error(v, f, targetVertices);

        n.resize(v.rows(), v.cols());
        igl::per_face_normals(v, f, n);

        matrixToVertices();
        matrixToFaces();

        std::cout << "Vertices after: " << v.rows() << std::endl;
        std::cout << "Faces after: " << f.rows() << std::endl;
    }

    void Mesh::resize(const double& size) {
        for (int i = 0; i < v.rows(); i++) {
            v.row(i)[0] *= size;
            v.row(i)[1] *= size;
            v.row(i)[2] *= size;
        }
        matrixToVertices();
        // igl::per_face_normals(this->v, this->f, this->n);
        // matrixToNormals();

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
        // igl::per_face_normals(this->v, this->f, this->n);
        // matrixToNormals();

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
        // igl::per_face_normals(this->v, this->f, this->n);
        // matrixToNormals();

        viewer.data_list[this->ID].set_mesh(v, f);
        viewer.data_list[this->ID].set_normals(n);
    }

    void Mesh::setMeshNotFilled() {
        this->viewer.data_list[this->_ID].show_faces = false;
        this->viewer.data_list[this->_ID].show_lines = true;
    }

    
    void Mesh::setMeshFilled()
    {
        this->viewer.data_list[this->_ID].show_faces = true;
        this->viewer.data_list[this->_ID].show_lines = false;
    }

    void Mesh::setColor(const Math::Vector3& color)
    {
        Eigen::MatrixXd C(f.rows(), 3);
        C.rowwise() = Eigen::RowVector3d(color.coordinates.x, color.coordinates.y, color.coordinates.z);

        this->viewer.data_list[ID].set_colors(C);
    }

    Mesh::~Mesh() {
        // TODO
    }
}
