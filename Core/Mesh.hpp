#ifndef __MESH_H__
#define __MESH_H__

#include <igl/opengl/glfw/Viewer.h>

#include <Vector3.hpp>

#include <Eigen/Dense>
#include <Eigen/Core>
#include <Eigen/SparseCore>

#include <MeshUtils.hpp>

#include <vector>
#include <string>

namespace Core {
    class Mesh {
        private:
            igl::opengl::glfw::Viewer& viewer;

            int _ID;

            void triangulateQuads(Eigen::MatrixXd &V, Eigen::MatrixXi &F, Eigen::MatrixXd &N);
            
            void matrixToVertices();
            void matrixToNormals();
            void matrixToFaces();

            Eigen::RowVector3d getCenterOfMass();

            void getSQEMForFace(const Math::Vector3& faceCenter, const Math::Vector3& faceNormal);
            void getSQEMForFaces(std::vector<Math::Vector3> facesCenter, std::vector<Math::Vector3> facesNormal);

            Eigen::Matrix4d computeQuadric(const Eigen::MatrixXd& V, const Eigen::MatrixXi& F, int vtx);

        public:
            Eigen::MatrixXd v;
            Eigen::MatrixXi f;
            Eigen::MatrixXd n;

            std::vector<Math::Vector3> vertices;
            std::vector<Math::Vector3> normals;
            std::vector<int> faces;

            const int& ID;

            Mesh(igl::opengl::glfw::Viewer& currentViewer);
            Mesh(const Eigen::MatrixXd &v, const Eigen::MatrixXi &f, const Eigen::MatrixXd &n, igl::opengl::glfw::Viewer &currentViewer);
            Mesh(const std::string&& path, igl::opengl::glfw::Viewer& currentViewer);

            void addToScene();

            void resize(const double& size);
            void resize(const Math::Vector3& size);
            void translate(const Math::Vector3& translation);

            void simplifyMesh(const int& targetVertices);

            void test();

            double getRadius();

            void setMeshNotFilled();

            static Mesh* generateSphereMesh(igl::opengl::glfw::Viewer &currentViewer)
            {
                static Eigen::MatrixXd vtx;
                static Eigen::MatrixXi fcs;
                static Eigen::MatrixXd nrm;

                Mesh* s;

                if (vtx.size() <= 0)
                {
                    s = new Mesh("/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Assets/Models/Sphere.obj", currentViewer);
                    vtx = s->v;
                    fcs = s->f;
                    nrm = s->n;
                }
                else {
                    s = new Mesh(vtx, fcs, nrm, currentViewer);
                }

                return s;
            }

            ~Mesh();
    };
}

#endif // __MESH_H__