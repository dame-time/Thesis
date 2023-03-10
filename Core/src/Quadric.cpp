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
        Math::Vector3 matrixTopLeftRow = Math::Vector3(faceNormal.dot(faceNormal), faceNormal.dot(faceNormal), faceNormal.dot(faceNormal));
        A.setZero();
        A.setTopLeftMatrix3(Math::Matrix3(matrixTopLeftRow, matrixTopLeftRow, matrixTopLeftRow));
        A.setRowVector(3, Math::Vector4(faceNormal, 1));
        A.setColumnVector(3, Math::Vector4(faceNormal, 1));
        A *= 2;

        auto omogeneousFaceNormalPoint = Math::Vector4(faceNormal, 1);
        b = omogeneousFaceNormalPoint * (2 * faceNormal.dot(faceOrigin));

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
        return 0.5 * s.dot(A * s) - 2 * b.dot(s) + c;
    }

    Math::Vector4 Quadric::minimize()
    {
        Math::Vector4 result;

        try
        {
            result = A.inverse() * 2 *  b;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Matrix has determinat 0 for this quadric" << std::endl;
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