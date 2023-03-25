#include "../Quadric.hpp"

#include <Matrix3.hpp>

namespace SM 
{

    Quadric::Quadric ()
    {
        A.setZero();
        b = Math::Vector4(0, 0, 0, 0);
        c = 0;
    }

    Quadric::Quadric (const Math::Vector3 &faceOrigin, const Math::Vector3 &faceNormal)
    {
        A.setZero();
        A.setTopLeftMatrix3(faceNormal.outer(faceNormal));
        A.setRowVector(3, Math::Vector4(faceNormal, 1));
        A.setColumnVector(3, Math::Vector4(faceNormal, 1));
        
        Math::Vector4 omogeneousFaceNormalPoint = Math::Vector4(faceNormal, 1);
        b = omogeneousFaceNormalPoint * (2 * -faceNormal.dot(faceOrigin));

        c = faceNormal.dot(faceOrigin) * faceNormal.dot(faceOrigin);
    }

    Quadric Quadric::operator + (const Quadric &quadric)
    {
        Quadric result;

        result.A = this->A + quadric.A;
        result.b = this->b + quadric.b;
        result.c = this->c + quadric.c;

        return result;
    }

    Quadric Quadric::operator * (const double &multiplier)
    {
        Quadric result;

        result.A = this->A * multiplier;
        result.b = this->b * multiplier;
        result.c = this->c * multiplier;

        return result;
    }

    void Quadric::operator += (const Quadric& quadric)
    {
        this->A = this->A + quadric.A;
        this->b = this->b + quadric.b;
        this->c = this->c + quadric.c;
    }

    void Quadric::operator *= (const double& multiplier)
    {
        this->A = this->A * multiplier;
        this->b = this->b * multiplier;
        this->c = this->c * multiplier;
    }

    double Quadric::evaluateSQEM (const Math::Vector4 &s)
    {
//        return 0.5 * s.dot(A * s) - 2 * b.dot(s) + c;
        return s.dot(A * s) - 2 * b.dot(s) + c;
    }

    Math::Vector4 Quadric::minimizer()
    {
        Math::Vector4 result;
        
        const double minRadius = 0.01;

        try
        {
            result = A.inverse() * (-b/2);
        }
        catch (const std::exception& e)
        {
            std::cerr << "Matrix has determinat 0 for this quadric" << std::endl;
        }
        
        if (result.coordinates.w < 0)
        {
            const int newQuadricWeight = 1000;
            
            Quadric q = Quadric();
            
            q.A = Math::Matrix4(0, 0, 0, 0,
                                0, 0, 0, 0,
                                0, 0, 0, 0,
                                0, 0, 0, 1);
            q.b = Math::Vector4(0, 0, 0, -minRadius * 2);
            q.c = minRadius;
            
            auto newQ = *this + (q * newQuadricWeight);
            
            result = newQ.A.inverse() * (-newQ.b/2);
        }

        return result;
    }

    void Quadric::print ()
    {
        this->A.print();
        this->b.print();
        std::cout << this->c << std::endl;
    }
}
