//
//  Sphere.cpp
//  Thesis
//
//  Created by Davide Paollilo on 10/04/23.
//

#include <Sphere.hpp>

namespace SM {
    Sphere::Sphere()
    {
        quadric = Quadric();
        region = Region();
        
        this->quadricWeights = 0.0;
    }

    Sphere::Sphere(const Core::Vertex& vertex, double k)
    {
        quadric = Quadric::initializeQuadricFromVertex(vertex, k) * 1e-6;
        region = Region(vertex.position);

        auto result = quadric.minimizer();
        this->center = result.toQuaternion().immaginary;
        this->radius = result.coordinates.w;
        
        this->quadricWeights = 1e-6;
        
        this->vertices.push_back(vertex);
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

    void Sphere::addFace(const Math::Vector3& centroid, const Math::Vector3& normal, double weight)
    {
        this->quadric += (Quadric(centroid, normal) * weight);

        auto result = quadric.minimizer();
        this->center = result.toQuaternion().immaginary;
        this->radius = result.coordinates.w;

         if (this->radius > this->region.directionalWidth)
             this->radius = this->region.directionalWidth;
    }

    void Sphere::addQuadric(const Quadric& q)
    {
        this->quadric += q;

        auto result = quadric.minimizer();
        this->center = result.toQuaternion().immaginary;
        this->radius = result.coordinates.w;

         if (this->radius > this->region.directionalWidth)
             this->radius = this->region.directionalWidth;
    }

    void Sphere::addVertex(const Core::Vertex& vertex)
    {
        vertices.push_back(vertex);
    }

    void Sphere::renderAssociatedVertices(igl::opengl::glfw::Viewer &viewer, double sphereSize)
    {
        const Math::Vector3 color = Math::Vector3(0, 1, 0);
        
        for (int i = 0; i < vertices.size(); i++)
        {
            // The point is inside the triangle
            Core::Mesh s = Core::Mesh::generateSphereMesh(viewer, color);
            
            s.resize(sphereSize);
            s.translate(vertices[i].position);
            
            renderedSpheres.push_back(s.ID);
        }
    }

    void Sphere::clearRenderedSpheres(igl::opengl::glfw::Viewer &viewer)
    {
        for (int i = 0; i < renderedSpheres.size(); i++)
            viewer.data_list[renderedSpheres[i]].clear();
        
        renderedSpheres.clear();
    }

    Sphere Sphere::lerp(const Sphere &s, double t)
    {
        Math::Vector4 origin(this->center, this->radius);
        Math::Vector4 destination(s.center, s.radius);

        auto result = origin.lerp(destination, t);

        return Sphere(result.toQuaternion().immaginary, result.coordinates.w);
    }
}
