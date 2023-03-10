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
    struct Face 
    {
        int i, j, k;

        Face() : i(0), j(0), k(0) {};
        Face(int a, int b, int c) : i(a), j(b), k(c) {};
    };

    struct Vertex
    {
        Math::Vector3 position;
        Math::Vector3 normal;

        Vertex() : position(Math::Vector3()), normal(Math::Vector3(1, 0, 0)) {}
        Vertex(const Math::Vector3& p, const Math::Vector3& n) : position(p), normal(n) {}
    };

    class Mesh {
        private:
            igl::opengl::glfw::Viewer& viewer;

            int _ID;

            void triangulateQuads(Eigen::MatrixXd &V, Eigen::MatrixXi &F, Eigen::MatrixXd &N);
            
            void matrixToVertices();
            void matrixToFaces();

            Eigen::RowVector3d getCenterOfMass();

            Eigen::Matrix4d computeQuadric(const Eigen::MatrixXd& V, const Eigen::MatrixXi& F, int vtx);

        public:
            Eigen::MatrixXd v;
            Eigen::MatrixXi f;
            Eigen::MatrixXd n;

            std::vector<Vertex> vertices;
            std::vector<Face> faces;

            const int& ID;

            Mesh(igl::opengl::glfw::Viewer& currentViewer);
            Mesh(const Eigen::MatrixXd &v, const Eigen::MatrixXi &f, const Eigen::MatrixXd &n, igl::opengl::glfw::Viewer &currentViewer);
            Mesh(const std::string& path, igl::opengl::glfw::Viewer& currentViewer);

            void addToScene();

            void resize(const double& size);
            void resize(const Math::Vector3& size);
            void translate(const Math::Vector3& translation);

            void simplifyMesh(const int& targetVertices);

            double getRadius();

            void setMeshNotFilled();
            void setMeshFilled();

            Mesh& operator = (const Mesh& other)
            {
                this->v = other.v;
                this->f = other.f;
                this->n = other.n;

                this->vertices = other.vertices;
                this->faces = other.faces;

                this->_ID = other.ID;
                this->viewer = other.viewer;

                return *this;
            }

            static Mesh generateSphereMesh(igl::opengl::glfw::Viewer &currentViewer, Math::Vector3 color)
            {
                // static Eigen::MatrixXd vtx;
                // static Eigen::MatrixXi fcs;
                // static Eigen::MatrixXd nrm;

                Mesh s = Mesh("/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Assets/Models/Sphere.obj", currentViewer);

                s.addToScene();

                s.setMeshFilled();

                // setting sphere as unitary sphere
                auto r = s.getRadius();
                s.resize(1 / r);

                Eigen::MatrixXd C(s.f.rows(), 3);
                C.rowwise() = Eigen::RowVector3d(color.coordinates.x, color.coordinates.y, color.coordinates.z);

                currentViewer.data_list[s.ID].set_colors(C);

                return s;
            }

            ~Mesh();
    };
}

#endif // __MESH_H__