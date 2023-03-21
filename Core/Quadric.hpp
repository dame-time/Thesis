#pragma once

#include <Vector4.hpp>
#include <Matrix4.hpp>

#include <Math.hpp>

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

            static Quadric initializeQuadricFromVertex(const Core::Vertex& vertex, double targetSphereRadius = 1.0f)
            {
                Quadric q;

                // (p * I * p - 2 * t * p + t * t) * weight -> con t sfera target, ovvero mi sposto sulla normale nella direzione negativa t = (vertex.position - k * vertex.normal, k) -> (sfera)
                bool a = Math::Math::sign(vertex.position.coordinates.x) != Math::Math::sign(vertex.normal.coordinates.x);
                bool b = Math::Math::sign(vertex.position.coordinates.y) != Math::Math::sign(vertex.normal.coordinates.y);
                bool c = Math::Math::sign(vertex.position.coordinates.z) != Math::Math::sign(vertex.normal.coordinates.z);

                // FIXME: utile nel caso del cubo, non so se sia sempre utile
                // possibile fix effettuare un clamp su t, al massimo puo' assumere le coordinate del vertice stesso
                Math::Vector3 n = vertex.normal;
                if (vertex.normal.coordinates.x != 0 && a)
                    n.coordinates.x *= -1;
                else if (vertex.normal.coordinates.y != 0 && b)
                    n.coordinates.y *= -1;
                else if (vertex.normal.coordinates.z != 0 && c)
                    n.coordinates.z *= -1;

                Math::Vector4 t = Math::Vector4(vertex.position - targetSphereRadius * n, targetSphereRadius);

                q.A = Math::Matrix4();
                q.b = (-t) * 2;
                q.c = t.dot(t);

                return  q;
            }

            Quadric operator + (const Quadric& quadric);
            Quadric operator * (const double& multiplier);

            void operator += (const Quadric& quadric);
            void operator *= (const double& multiplier);

            double evaluateSQEM (const Math::Vector4& sphere);

            Math::Vector4 minimizer () const;

            void print ();
    };
}
