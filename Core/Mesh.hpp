#ifndef __MESH_H__
#define __MESH_H__

#include <igl/opengl/glfw/Viewer.h>

#include <Vector3.hpp>

#include <Eigen/Dense>

#include <vector>
#include <string>

namespace Core {
    class Mesh {
        private:
            Eigen::MatrixXd v;
            Eigen::MatrixXi f;
            Eigen::MatrixXd n;

            igl::opengl::glfw::Viewer& viewer;

            int _ID;

            void triangulateQuads(Eigen::MatrixXd &V, Eigen::MatrixXi &F, Eigen::MatrixXd &N);
            
            void matrixToVertices();
            void matrixToNormals();
            void matrixToFaces();

            Eigen::RowVector3d getCenterOfMass();
            double getRadius();

        public:
            std::vector<Math::Vector3> vertices;
            std::vector<Math::Vector3> normals;
            std::vector<int> faces;

            const int& ID;

            Mesh(igl::opengl::glfw::Viewer& currentViewer);
            Mesh(const Eigen::MatrixXd &v, const Eigen::MatrixXi &f, const Eigen::MatrixXd &n, igl::opengl::glfw::Viewer &currentViewer);
            Mesh(const std::string&& path, igl::opengl::glfw::Viewer& currentViewer);

            void addToScene();

            void resize(const double&& size);
            void resize(const Math::Vector3& size);
            void translate(const Math::Vector3& translation);

            void test();

            ~Mesh();
    };
}

#endif // __MESH_H__