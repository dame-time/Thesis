//
//  Sphere.hpp
//  Thesis
//
//  Created by Davide Paollilo on 10/04/23.
//

#ifndef Sphere_hpp
#define Sphere_hpp

#include <Mesh.hpp>
#include <Quadric.hpp>
#include <Region.hpp>

#include <iostream>
#include <vector>

namespace SM {
    class Sphere
    {
        private:
            std::vector<int> renderedSpheres;
        
        public:
            std::vector<Core::Vertex> vertices;
        
            int renderedMeshID;
        
            double quadricWeights;
        
            Quadric quadric;
            Region region;

            Math::Vector3 center;
            double radius;

            Sphere();
            Sphere(const Core::Vertex& vertex, double targetSphereRadius);
            Sphere(const Math::Vector3& center, double radius);

            Quadric getSphereQuadric();

            void addFace(const Math::Vector3& centroid, const Math::Vector3& normal, double weight = 1.0);
            void addQuadric(const Quadric& q);
        
            void addVertex(const Core::Vertex& vertex);
        
            void renderAssociatedVertices(igl::opengl::glfw::Viewer &viewer, double sphereSize = 0.01f);
            void clearRenderedSpheres(igl::opengl::glfw::Viewer &viewer);
        
            void operator = (const Sphere& s)
            {
                this->quadric = s.quadric;
                this->region = s.region;
                
                this->center = s.center;
                this->radius = s.radius;
                this->vertices = s.vertices;
            }

            Sphere lerp(const Sphere &s, double t);
    };
}

#endif /* Sphere_hpp */
