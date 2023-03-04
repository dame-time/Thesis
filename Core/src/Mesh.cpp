#include "../Mesh.hpp"

#include "../SQEM.h"
#include "../MinimumBoundingSphere.hpp"

#include <igl/triangle/triangulate.h>
#include <igl/readOBJ.h>
#include <igl/centroid.h>
#include <igl/opengl/glfw/Viewer.h>
#include <igl/per_face_normals.h>

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

        this->triangulateQuads(this->v,this->f, this->n);

        // Translate the mesh to the origin
        this->v = this->v.rowwise() - getCenterOfMass();

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

        igl::per_face_normals(v, f, n);

        matrixToVertices();
        matrixToFaces();
        matrixToNormals();
    }

    void Mesh::matrixToVertices() {
        vertices.clear();

        for (int i = 0; i < v.rows(); i++)
            vertices.push_back(Math::Vector3(v(i, 0), v(i, 1), v(i, 2)));
    }

    void Mesh::matrixToNormals() {
        normals.clear();

        for (int i = 0; i < n.rows(); i++)
            normals.push_back(Math::Vector3(n(i, 0), n(i, 1), n(i, 2)));
    }

    void Mesh::matrixToFaces() {
        faces.clear();

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
        matrixToNormals();

        std::cout << "Vertices after: " << v.rows() << std::endl;
        std::cout << "Faces after: " << f.rows() << std::endl;
    }

    void Mesh::test() {
        Math::Vector3 sphereCenter;
        float sphereRadius;
        const float MAX_RADIUS = 10.f;

        Eigen::MatrixXd triangleCenters(f.rows(), 3);
        std::vector<Math::Vector3> centersVec;
        std::vector<Math::Vector3> normalsVec;
        for (int i = 0; i < f.rows(); i++)
        {
            Eigen::RowVector3i face = f.row(i);
            Eigen::MatrixXd verts(3, 3);
            verts.row(0) = v.row(face[0]);
            verts.row(1) = v.row(face[1]);
            verts.row(2) = v.row(face[2]);
            Eigen::RowVector3d center = verts.colwise().mean();
            triangleCenters.row(i) = center;
            Math::Vector3 centerVec(center(0), center(1), center(2));
            centersVec.push_back(centerVec);
            Math::Vector3 e1(verts(1, 0) - verts(0, 0), verts(1, 1) - verts(0, 1), verts(1, 2) - verts(0, 2));
            Math::Vector3 e2(verts(2, 0) - verts(0, 0), verts(2, 1) - verts(0, 1), verts(2, 2) - verts(0, 2));
            Math::Vector3 normal = e1.cross(e2).normalized();
            normalsVec.push_back(normal);
        }

        std::unordered_map<int, std::vector<std::vector<Math::Vector3>>> vf;
        MinimumBoundingSphere::getVertexToTripletMap(v, f, vf);

        int partitions = 5;
        int steps = vf.size() / partitions;

        // // FIXME: SEG FAULT
        // std::vector<std::vector<std::vector<std::vector<Math::Vector3>>>> batches(partitions);

        // int idx = 0;
        // for (const auto& pair : vf)
        // {
        //     batches[idx % steps].push_back(pair.second);
        //     idx++;
        // }
        // //

        // SQEM sqem;
        // for (int i = 0; i < batches.size(); i++) {
        //     sqem.setZero();
        //     for (int j = 0; j < batches[i].size(); j++) {
        //         auto analyzedV = batches[i][j];
        //         for (int k = 0; k < analyzedV.size(); k++) {
        //             auto v0 = analyzedV[k][0];
        //             auto v1 = analyzedV[k][1];
        //             auto v2 = analyzedV[k][2];

        //             auto centroid = MinimumBoundingSphere::ComputeCentroid(v0, v1, v2);
        //             auto normal = (v1 - v0).cross(v2 - v0);
        //             normal = normal.normalized();

        //             sqem += SQEM(centroid, normal);
        //         }
        //     }
        //     sqem.minimize(sphereCenter, sphereRadius, Math::Vector3(-MAX_RADIUS, -MAX_RADIUS, -MAX_RADIUS), Math::Vector3(MAX_RADIUS, MAX_RADIUS, MAX_RADIUS));

        //     Mesh s("/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Assets/Models/Sphere.obj", this->viewer);
        //     s.addToScene();

        //     // setting sphere as unitary sphere
        //     auto radius = s.getRadius();
        //     s.resize(1 / radius);

        //     // Setting the optimal sphere
        //     s.resize(sphereRadius);
        //     s.translate(sphereCenter);

        //     std::cout << sphereRadius << std::endl;
        //     sphereCenter.print();
        // }

        // ======================================================

        SQEM sqem;

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < vf[i].size(); j++) {

                auto centroid = MinimumBoundingSphere::ComputeCentroid(vf[i][j][0], vf[i][j][1], vf[i][j][2]);
                auto normal = (vf[i][j][1] - vf[i][j][0]).cross(vf[i][j][2] - vf[i][j][0]);
                normal = normal.normalized();

                Mesh s("/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Assets/Models/Sphere.obj", this->viewer);

                s.addToScene();
                // setting sphere as unitary sphere
                auto radius = s.getRadius();
                s.resize(1 / radius);

                // Setting the optimal sphere
                s.resize(0.05f);
                s.translate(centroid);

                sqem += SQEM(centroid, normal);
            }
        }

        sqem.minimize(sphereCenter, sphereRadius, Math::Vector3(-MAX_RADIUS, -MAX_RADIUS, -MAX_RADIUS), Math::Vector3(MAX_RADIUS, MAX_RADIUS, MAX_RADIUS));

        Mesh s("/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Assets/Models/Sphere.obj", this->viewer);

        s.addToScene();
        // setting sphere as unitary sphere
        auto radius = s.getRadius();
        s.resize(1 / radius);

        // Setting the optimal sphere
        s.resize(sphereRadius);
        s.translate(sphereCenter);

        std::cout << sphereRadius << std::endl;
        sphereCenter.print();

        sqem.setZero();

        for (int i = vf.size() - 5; i < vf.size(); i++) {
            for (int j = 0; j < vf[i].size(); j++) {

                auto centroid = MinimumBoundingSphere::ComputeCentroid(vf[i][j][0], vf[i][j][1], vf[i][j][2]);
                auto normal = (vf[i][j][1] - vf[i][j][0]).cross(vf[i][j][2] - vf[i][j][0]);
                normal = normal.normalized();

                Mesh s("/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Assets/Models/Sphere.obj", this->viewer);

                s.addToScene();
                // setting sphere as unitary sphere
                auto radius = s.getRadius();
                s.resize(1 / radius);

                // Setting the optimal sphere
                s.resize(0.05f);
                s.translate(centroid);

                sqem += SQEM(centroid, normal);
            }
        }

        sqem.minimize(sphereCenter, sphereRadius, Math::Vector3(-MAX_RADIUS, -MAX_RADIUS, -MAX_RADIUS), Math::Vector3(MAX_RADIUS, MAX_RADIUS, MAX_RADIUS));

        Mesh s1("/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Assets/Models/Sphere.obj", this->viewer);

        s1.addToScene();
        // setting sphere as unitary sphere
        radius = s1.getRadius();
        s1.resize(1 / radius);

        // Setting the optimal sphere
        s1.resize(sphereRadius);
        s1.translate(sphereCenter);

        std::cout << sphereRadius << std::endl;
        sphereCenter.print();

        // ============================================

        // std::vector<std::vector<Math::Vector3>> faces;
        // std::vector<std::vector<Math::Vector3>> normalsBatch;
        // std::vector<Math::Vector3> centroids;
        // std::vector<Math::Vector3> normals;
        // MinimumBoundingSphere::extractFaceVertices(v, f, faces);
        // MinimumBoundingSphere::extractFaceNormals(v, f, n, normalsBatch);

        // for (int i = 0; i < faces.size(); i++) {
        //     auto centroid = MinimumBoundingSphere::ComputeCentroid(faces[i][0], faces[i][1], faces[i][2]);
        //     auto normal = normalsBatch[i][0] + normalsBatch[i][1] + normalsBatch[i][2];
        //     normal /= 3;

        //     centroids.push_back(centroid);
        //     normals.push_back(normal.normalized());
        // }

        // for (int i = 0; i < centroids.size(); i++) {
        //     SQEM sqem = SQEM(centroids[i], normals[i]);
        //     centroids[i].print();

        //     Math::Vector3 sphereCenter;
        //     float sphereRadius = 0.0f;
        //     float MAX_RADIUS = 100.f;

        //     sqem.minimize(sphereCenter, sphereRadius, Math::Vector3(-MAX_RADIUS, -MAX_RADIUS, -MAX_RADIUS), Math::Vector3(MAX_RADIUS, MAX_RADIUS, MAX_RADIUS));

        //     sphereCenter.print();
            
        //     Mesh s("/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Assets/Models/Sphere.obj", this->viewer);

        //     s.addToScene();
        //     // setting sphere as unitary sphere
        //     auto radius = s.getRadius();

        //     // Setting the optimal sphere
        //     s.resize(sphereRadius + 0.1f);
        //     s.translate(sphereCenter);
        // }

        // for (int i = 0; i < centersVec.size(); i++)
        //     getSQEMForFace(centersVec[i], normalsVec[i]);

        // getSQEMForFaces(centersVec, normalsVec);

        // MinimumBoundingSphere::GetAdjacentVertices(v, f, n);

        // auto spheres = MinimumBoundingSphere::ComputeWithFaces(v, f, n, 6);
        // for (auto sphere : spheres)
        // {
        //     if (sphere.radius <= 0.0f)
        //         continue;

        //     std::cout << "    Sphere: center: ";
        //     sphere.center.print();
        //     std::cout << ", radius: " << sphere.radius << std::endl;

        //     Mesh s("/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Assets/Models/Sphere.obj", this->viewer);
        //     s.addToScene();

        //     // setting sphere as unitary sphere
        //     auto radius = s.getRadius();
        //     s.resize(1 / radius);

        //     // Setting the optimal sphere
        //     s.resize(sphere.radius);
        //     s.translate(sphere.center);
        // }
    }

    void Mesh::getSQEMForFace(const Math::Vector3 &faceCenter, const Math::Vector3 &faceNormal) {
        // Math::Vector3 sphereCenter;
        // float sphereRadius;
        // const float MAX_RADIUS = 10.f;

        // SQEM sqem(faceCenter, faceNormal);
        // sqem.minimize(sphereCenter, sphereRadius, Math::Vector3(-MAX_RADIUS, -MAX_RADIUS, -MAX_RADIUS), Math::Vector3(MAX_RADIUS, MAX_RADIUS, MAX_RADIUS));
        
        // std::cout << "    Result: optimal sphere centered at [" << sphereCenter[0] << ", " << sphereCenter[1] << ", " << sphereCenter[2] << "], with radius " << sphereRadius << "." << std::endl;
        
        // Mesh sphere("/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Assets/Models/Sphere.obj", this->viewer);
        // sphere.addToScene();

        // // setting sphere as unitary sphere
        // auto radius = sphere.getRadius();
        // sphere.resize(1 / radius);

        // // Setting the optimal sphere
        // sphere.resize(sphereRadius);
        // sphere.translate(sphereCenter);

        // std::cout << sphere.getCenterOfMass() << std::endl;
        // std::cout << sphere.getRadius() << std::endl;
    }

    void Mesh::getSQEMForFaces(std::vector<Math::Vector3> facesCenter, std::vector<Math::Vector3> facesNormal) {
        Math::Vector3 sphereCenter;
        float sphereRadius;
        const float MAX_RADIUS = 10.f;

        SQEM sqem(facesCenter[0], facesNormal[0]);
        for (int i = 1; i < facesCenter.size(); i++)
            sqem += SQEM(facesCenter[i], facesNormal[i]);

        sqem.minimize(sphereCenter, sphereRadius, Math::Vector3(-MAX_RADIUS, -MAX_RADIUS, -MAX_RADIUS), Math::Vector3(MAX_RADIUS, MAX_RADIUS, MAX_RADIUS));

        std::cout << "    Result: optimal sphere centered at [" << sphereCenter[0] << ", " << sphereCenter[1] << ", " << sphereCenter[2] << "], with radius " << sphereRadius << "." << std::endl;
        Mesh sphere("/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Assets/Models/Sphere.obj", this->viewer);
        sphere.addToScene();

        // setting sphere as unitary sphere
        auto radius = sphere.getRadius();
        sphere.resize(1 / radius);

        // Setting the optimal sphere
        sphere.resize(sphereRadius);
        sphere.translate(sphereCenter);
        std::cout << sphere.getCenterOfMass() << std::endl;
        std::cout << sphere.getRadius() << std::endl;
    }

    void Mesh::resize(const double& size) {
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

    void Mesh::setMeshNotFilled() {
        this->viewer.data_list[this->_ID].show_faces = false;
        this->viewer.data_list[this->_ID].show_lines = true;
    }

    Mesh::~Mesh() {
        // TODO
    }
}