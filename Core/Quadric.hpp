#pragma once

#include <Vector3.hpp>
#include <Vector4.hpp>
#include <Matrix4.hpp>

#include <Math.hpp>
#include <Quaternion.hpp>

#include <Mesh.hpp>

#include <iostream>

namespace SM
{
    class Quadric
    {
        private:
            Math::Matrix4 A;
            Math::Vector4 b;
            double c;

        public:
            Quadric();
            Quadric(const Math::Vector3& faceOrigin, const Math::Vector3& faceNormal);

            static Quadric initializeQuadricFromVertex(const Core::Vertex& vertex, double targetSphereRadius = 1.0)
            {
                Quadric q;

                // (p * I * p - 2 * t * p + t * t) * weight -> con t sfera target, ovvero mi sposto sulla normale nella direzione negativa t = (vertex.position - k * vertex.normal, k) -> (sfera)
                Math::Vector3 n = vertex.normal;

                Math::Vector4 t = Math::Vector4(vertex.position - targetSphereRadius * n, targetSphereRadius);

                q.A = Math::Matrix4();
                q.b = (-t) * 2;
                q.c = t.dot(t);

                return  q;
            }
        
            Math::Matrix4 getA() const
            {
                return A;
            }
        
            Math::Vector4 getB() const
            {
                return b;
            }
        
            double getC() const
            {
                return c;
            }

            Quadric operator + (const Quadric& quadric);
            Quadric operator * (const double& multiplier);

            void operator += (const Quadric& quadric);
            void operator *= (const double& multiplier);

            double evaluateSQEM (const Math::Vector4& sphere);

            Math::Vector4 minimizer ();
        
            void addQuadricToTargetRadius(const double& t);

            void print ();
    };
}
