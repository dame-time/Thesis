#ifndef __MESH_H__
#define __MESH_H__

#include <igl/opengl/glfw/Viewer.h>

#include <Vector3.hpp>

#include <Eigen/Dense>
#include <Eigen/Core>
#include <Eigen/SparseCore>

#include <vector>
#include <string>
#include <limits>
#include <cfloat>

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
        
        Math::Vector2 curvature;

        Vertex() : position(Math::Vector3()), normal(Math::Vector3(1, 0, 0)) {}
        Vertex(const Math::Vector3& p, const Math::Vector3& n) : position(p), normal(n) {}
    };

    struct AABB
    {
        Math::Vector3 minCorner = Math::Vector3(DBL_MAX, DBL_MAX, DBL_MAX);
        Math::Vector3 maxCorner = Math::Vector3(-DBL_MAX, -DBL_MAX, -DBL_MAX);
        
        void addPoint(const Math::Vector3& p)
        {
            for (int i = 0; i < 3; i++)
                if (p[i] > maxCorner[i])
                    maxCorner[i] = p[i];
            
            for (int i = 0; i < 3; i++)
                if (p[i] < minCorner[i])
                    minCorner[i] = p[i];
        }
        
        Math::Vector3 BDD() const
        {
            return maxCorner - minCorner;
        }
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
        
            void computePerVertexCurvature();
        
            void updateAABB();

        public:
            AABB bbox;
        
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

            double getRadius();

            void setMeshNotFilled();
            void setMeshFilled();
        
            void setColor(const Math::Vector3& color);

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
                Mesh s = Mesh("/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Assets/Models/Sphere.obj", currentViewer);

                s.addToScene();

                s.setMeshFilled();

                // setting sphere as unitary sphere
                auto r = s.getRadius();
                s.resize(1 / r);

                Eigen::MatrixXd C(s.f.rows(), 3);
                C.rowwise() = Eigen::RowVector3d(color.coordinates.x, color.coordinates.y, color.coordinates.z);
                
                currentViewer.data_list[s.ID].set_colors(C);
                currentViewer.data_list[s.ID].set_face_based(true);

                return s;
            }
        
            static Mesh generateSphereMesh(igl::opengl::glfw::Viewer &currentViewer, Math::Vector3 color, std::vector<Mesh*>& renderedMeshes)
            {
                Mesh s = Mesh("/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Assets/Models/Sphere.obj", currentViewer);

                s.addToScene();

                s.setMeshFilled();

                // setting sphere as unitary sphere
                auto r = s.getRadius();
                s.resize(1 / r);

                Eigen::MatrixXd C(s.f.rows(), 3);
                C.rowwise() = Eigen::RowVector3d(color.coordinates.x, color.coordinates.y, color.coordinates.z);
                
                currentViewer.data_list[s.ID].set_colors(C);
                currentViewer.data_list[s.ID].set_face_based(true);
                
                renderedMeshes.push_back(&s);

                return s;
            }

            ~Mesh();
    };
}

#endif // __MESH_H__
