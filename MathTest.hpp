//
//  MathTest.h
//  Thesis
//
//  Created by Davide Paollilo on 05/04/23.
//

#ifndef MathTest_h
#define MathTest_h

#include <Matrix4.hpp>
#include <Math.hpp>

#include <iostream>
#include <cmath>

namespace Math::Test {

    void testMatrix4()
    {
        // Test default constructor
        Matrix4 mat1;
        mat1.setZero();
        for (int i = 0; i < 16; i++) {
            assert(mat1.data[i] == 0.0);
        }

        // Test constructor with scalar value
        Matrix4 mat2(2.0);
        for (int i = 0; i < 16; i++) {
            assert(mat2.data[i] == 2.0);
        }

        // Test constructor with vector inputs
        Vector4 vec1(1.0, 2.0, 3.0, 4.0);
        Vector4 vec2(5.0, 6.0, 7.0, 8.0);
        Vector4 vec3(9.0, 10.0, 11.0, 12.0);
        Vector4 vec4(13.0, 14.0, 15.0, 16.0);
        Matrix4 mat3(vec1, vec2, vec3, vec4);
        assert(mat3.data[0] == 1.0 && mat3.data[1] == 2.0 && mat3.data[2] == 3.0 && mat3.data[3] == 4.0);
        assert(mat3.data[4] == 5.0 && mat3.data[5] == 6.0 && mat3.data[6] == 7.0 && mat3.data[7] == 8.0);
        assert(mat3.data[8] == 9.0 && mat3.data[9] == 10.0 && mat3.data[10] == 11.0 && mat3.data[11] == 12.0);
        assert(mat3.data[12] == 13.0 && mat3.data[13] == 14.0 && mat3.data[14] == 15.0 && mat3.data[15] == 16.0);

        // Test copy constructor
        Matrix4 mat4(mat3);
        for (int i = 0; i < 16; i++) {
            assert(mat4.data[i] == mat3.data[i]);
        }

        // Test multiplication with scalar value
        mat4 *= 2.0;
        for (int i = 0; i < 16; i++) {
            assert(mat4.data[i] == mat3.data[i] * 2.0);
        }

        // Test division with scalar value
        mat4 /= 2.0;
        for (int i = 0; i < 16; i++) {
            assert(mat4.data[i] == mat3.data[i]);
        }

        // Test addition and subtraction with other matrix
        mat4 += mat3;
        for (int i = 0; i < 16; i++) {
            assert(mat4.data[i] == mat3.data[i] * 2.0);
        }

        mat4 -= mat3;
        for (int i = 0; i < 16; i++) {
            assert(mat4.data[i] == mat3.data[i]);
        }

        // Test multiplication with another matrix
        Matrix4 mat5(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0);
        Matrix4 result5 = mat4 * mat5;
        Matrix4 expected5(90.0, 100.0, 110.0, 120.0, 202.0, 228.0, 254.0, 280.0, 314.0, 356.0, 398.0, 440.0, 426.0, 484.0, 542.0, 600.0);
        assert(result5 == expected5);
        if (result5 == expected5)
        {
            std::cout << "Matrix multiplication test passed." << std::endl;
        }
        else
        {
            std::cout << "Matrix multiplication test failed." << std::endl;
            std::cout << "Expected: " << std::endl;
            expected5.print();
            std::cout << "Result: " << std::endl;
            result5.print();
        }
        
        // Test vector multiplication
        Vector4 vec(1.0, 2.0, 3.0, 4.0);
        Vector4 result6 = mat4 * vec;
        Vector4 expected6(30.0, 70.0, 110.0, 150.0);
        if (result6 == expected6)
        {
            std::cout << "Vector multiplication test passed." << std::endl;
        }
        else
        {
            std::cout << "Vector multiplication test failed." << std::endl;
            std::cout << "Expected: " << std::endl;
            expected6.print();
            std::cout << "Result: " << std::endl;
            result6.print();
        }
        assert(result6 == expected6);

        // Test scalar multiplication
        Scalar scalar = 2.0;
        Matrix4 result7 = mat4 * scalar;
        Matrix4 expected7(2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0, 22.0, 24.0, 26.0, 28.0, 30.0, 32.0);
        if (result7 == expected7)
        {
            std::cout << "Scalar multiplication test passed." << std::endl;
        }
        else
        {
            std::cout << "Scalar multiplication test failed." << std::endl;
            std::cout << "Expected: " << std::endl;
            expected7.print();
            std::cout << "Result: " << std::endl;
            result7.print();
        }
        assert(result7 == expected7);

        // Test matrix addition
        Matrix4 mat6(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0);
        Matrix4 result8 = mat4 + mat6;
        Matrix4 expected8(2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0, 22.0, 24.0, 26.0, 28.0, 30.0, 32.0);
        if (result8 == expected8)
        {
            std::cout << "Test 8 passed\n";
        } else {
            std::cout << "Test 8 failed\n";
            std::cout << "Expected output:\n";
            expected8.print();
            std::cout << "Actual output:\n";
            result8.print();
        }
        assert(result8 == expected8);

        // Test multiplication with a scalar
        Matrix4 mat9(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0);
        Scalar scalar9 = 2.0;
        Matrix4 result9 = mat9 * scalar9;
        Matrix4 expected9(2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0, 22.0, 24.0, 26.0, 28.0, 30.0, 32.0);
        if (result9 == expected9) {
            std::cout << "Test 9 passed\n";
        } else {
            std::cout << "Test 9 failed\n";
            std::cout << "Expected output:\n";
            expected9.print();
            std::cout << "Actual output:\n";
            result9.print();
        }
        assert(result9 == expected9);

        // Test addition with another matrix
        Matrix4 mat10(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0);
        Matrix4 mat11(2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0, 22.0, 24.0, 26.0, 28.0, 30.0, 32.0);
        Matrix4 result10 = mat10 + mat11;
        Matrix4 expected10(3.0, 6.0, 9.0, 12.0, 15.0, 18.0, 21.0, 24.0, 27.0, 30.0, 33.0, 36.0, 39.0, 42.0, 45.0, 48.0);
        if (result10 == expected10) {
            std::cout << "Test 10 passed\n";
        } else {
            std::cout << "Test 10 failed\n";
            std::cout << "Expected output:\n";
            expected10.print();
            std::cout << "Actual output:\n";
            result10.print();
        }
        assert(result10 == expected10);

        // Test subtraction with another matrix
        Matrix4 mat12(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0);
        Matrix4 mat13(4.0, 3.0, 2.0, 1.0, 8.0, 7.0, 6.0, 5.0, 12.0, 11.0, 10.0, 9.0, 16.0, 15.0, 14.0, 13.0);
        Matrix4 result11 = mat12 - mat13;
        Matrix4 expected11(-3.0, -1.0, 1.0, 3.0, -3.0, -1.0, 1.0, 3.0, -3.0, -1.0, 1.0, 3.0, -3.0, -1.0, 1.0, 3.0);
        if (result11 == expected11)
            std::cout << "Test subtraction with another matrix: PASSED\n";
        else
            std::cout << "Test subtraction with another matrix: FAILED\n";
        assert(result11 == expected11);

        // Test division with scalar
        Matrix4 mat14(2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0, 22.0, 24.0, 26.0, 28.0, 30.0, 32.0);
        Scalar dividend = 2.0;
        mat14 /= dividend;
        Matrix4 expected12(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0);
        if (mat14 == expected12)
            std::cout << "Test division with scalar: PASSED\n";
        else
            std::cout << "Test division with scalar: FAILED\n";
        assert(mat14 == expected12);

        // Test inverse
        Matrix4 mat15(1.0, 2.0, 3.0, 4.0, 0.0, 1.0, 2.0, 3.0, 1.0, 0.0, 1.0, 2.0, 4.0, 3.0, 0.0, 1.0);
        Matrix4 expected13(1.0/2.0, -1.0, 1.0/2.0, 0.0,
                           -1.0/4.0, 3.0/4.0, -3.0/4.0, 1.0/4.0,
                           2.0, -5.0/2.0, 0.0, -1.0/2.0,
                           -5.0/4.0, 7.0/4.0, 1.0/4.0, 1.0/4.0);
        if (mat15.inverse() == expected13)
            std::cout << "Test inverse: PASSED\n";
        else
            std::cout << "Test inverse: FAILED\n";
        assert(mat15.inverse() == expected13);

        // Test transposed matrix
        Matrix4 mat16(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0);
        Matrix4 result16 = mat16.transposed();
        Matrix4 expected16(1.0, 5.0, 9.0, 13.0, 2.0, 6.0, 10.0, 14.0, 3.0, 7.0, 11.0, 15.0, 4.0, 8.0, 12.0, 16.0);
        if (result16 == expected16)
            std::cout << "Test transposed matrix: PASSED\n";
        else
            std::cout << "Test transposed matrix: FAILED\n";
        assert(result16 == expected16);
        

        // Test setting the top-left 3x3 matrix
        Matrix4 mat17(0.0, 0.0, 0.0, 4.0, 0.0, 0.0, 0.0, 8.0, 0.0, 0.0, 0.0, 12.0, 13.0, 14.0, 15.0, 16.0);
        Matrix3 mat3_1(1.0, 2.0, 3.0, 5.0, 6.0, 7.0, 9.0, 10.0, 11.0);
        mat17.setTopLeftMatrix3(mat3_1);
        Matrix4 expected17(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0);
        if (mat17 == expected17)
            std::cout << "Test setting top-left 3x3 matrix: PASSED\n";
        else
            std::cout << "Test setting top-left 3x3 matrix: FAILED\n";
        assert(mat17 == expected17);

        // Test setting a row vector
        Matrix4 mat18(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0);
        Vector4 rowVector(0.0, 0.0, 0.0, 1.0);
        mat18.setRowVector(2, rowVector);
        Matrix4 expected18(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 0.0, 0.0, 0.0, 1.0, 13.0, 14.0, 15.0, 16.0);
        if (mat18 == expected18)
            std::cout << "Test setting row vector: PASSED\n";
        else
            std::cout << "Test setting row vector: FAILED\n";
        assert(mat18 == expected18);

        // Test setting column vector
        Matrix4 mat19;
        mat19.setColumnVector(0, Vector4(1.0, 2.0, 3.0, 4.0));
        mat19.setColumnVector(1, Vector4(5.0, 6.0, 7.0, 8.0));
        mat19.setColumnVector(2, Vector4(9.0, 10.0, 11.0, 12.0));
        mat19.setColumnVector(3, Vector4(13.0, 14.0, 15.0, 16.0));
        Matrix4 expected19(1.0, 5.0, 9.0, 13.0, 2.0, 6.0, 10.0, 14.0, 3.0, 7.0, 11.0, 15.0, 4.0, 8.0, 12.0, 16.0);
        if (mat19 == expected19)
            std::cout << "Test setting column vector: PASSED\n";
        else
            std::cout << "Test setting column vector: FAILED\n";
        assert(mat19 == expected19);

        // Test transform direction
//        Matrix4 mat20(Vector4(1.0, 0.0, 0.0, 0.0), Vector4(0.0, 1.0, 0.0, 0.0), Vector4(0.0, 0.0, 1.0, 0.0), Vector4(0.0, 0.0, 0.0, 1.0));
//        Vector3 vec20(1.0, 2.0, 3.0);
//        Vector3 expected20(1.0, 2.0, 3.0);
//        if (mat20.transformDirection(vec20) == expected20)
//            std::cout << "Test transform direction: PASSED\n";
//        else
//            std::cout << "Test transform direction: FAILED\n";
//        assert(mat20.transformDirection(vec20) == expected20);

        // Test transform inverse direction
//        Matrix4 mat21(Vector4(1.0, 0.0, 0.0, 0.0), Vector4(0.0, 1.0, 0.0, 0.0), Vector4(0.0, 0.0, 1.0, 0.0), Vector4(0.0, 0.0, 0.0, 1.0));
//        Vector3 vec21(1.0, 2.0, 3.0);
//        Vector3 expected21(1.0, 2.0, 3.0);
//        if (mat21.transformInverseDirection(vec21) == expected21)
//            std::cout << "Test transform inverse direction: PASSED\n";
//        else
//            std::cout << "Test transform inverse direction: FAILED\n";
//        assert(mat21.transformInverseDirection(vec21) == expected21);

        // Test local to world direction
//        Matrix4 mat22(Vector4(1.0, 0.0, 0.0, 0.0), Vector4(0.0, 1.0, 0.0, 0.0), Vector4(0.0, 0.0, 1.0, 0.0), Vector4(0.0, 0.0, 0.0, 1.0));
//        Vector3 vec22(1.0, 2.0, 3.0);
//        Matrix4 transform22(Vector4(1.0, 0.0, 0, 0.0), Vector4(0.0, 1.0, 0.0, 0.0), Vector4(0.0, 0.0, 1.0, 0.0), Vector4(4.0, 5.0, 6.0, 1.0));
//        Vector3 result22 = mat22.localToWorldDir(vec22, transform22);
//        Vector3 expected22(5.0, 7.0, 9.0);
//        if (result22 == expected22)
//            std::cout << "Test local to world direction: PASSED\n";
//        else
//            std::cout << "Test local to world direction: FAILED\n";
//        assert(result22 == expected22);

        // Test world to local direction
//        Matrix4 mat23(Vector4(1.0, 0.0, 0.0, 0.0), Vector4(0.0, 1.0, 0.0, 0.0), Vector4(0.0, 0.0, 1.0, 0.0), Vector4(0.0, 0.0, 0.0, 1.0));
//        Vector3 vec23(1.0, 2.0, 3.0);
//        Matrix4 transform23(Vector4(1.0, 0.0, 0.0, 0.0), Vector4(0.0, 1.0, 0.0, 0.0), Vector4(0.0, 0.0, 1.0, 0.0), Vector4(4.0, 5.0, 6.0, 1.0));
//        Vector3 result23 = mat23.worldToLocalDir(vec23, transform23);
//        Vector3 expected23(-3.0, -3.0, -3.0);
//        if (result23 == expected23)
//            std::cout << "Test world to local direction: PASSED\n";
//        else
//            std::cout << "Test world to local direction: FAILED\n";
//        assert(result23 == expected23);

        // Test inverse transform with no translation
//        Matrix4 mat24(Vector4(1.0, 2.0, 3.0, 0.0), Vector4(0.0, 1.0, 0.0, 0.0), Vector4(0.0, 0.0, 1.0, 0.0), Vector4(0.0, 0.0, 0.0, 1.0));
//        Vector3 vec24(1.0, 2.0, 3.0);
//        Vector3 result24 = mat24.transformInverse(vec24);
//        Vector3 expected24(-1.0, 2.0, -3.0);
//        if (result24 == expected24)
//            std::cout << "Test inverse transform with no translation: PASSED\n";
//        else
//            std::cout << "Test inverse transform with no translation: FAILED\n";
//        assert(result24 == expected24);

        // Test transform with a vector
//        Matrix4 mat25(Vector4(1.0, 0.0, 0.0, 0.0), Vector4(0.0, 1.0, 0.0, 0.0), Vector4(0.0, 0.0, 1.0, 0.0), Vector4(1.0, 2.0, 3.0, 1.0));
//        Vector3 vec25(1.0, 2.0, 3.0);
//        Vector3 result25 = mat25.transform(vec25);
//        Vector3 expected25(2.0, 4.0, 6.0);
//        if (result25 == expected25) {
//            std::cout << "Test transform with a vector: PASSED\n";
//        } else {
//            std::cout << "Test transform with a vector: FAILED\n";
//            std::cout << "Expected result: ";
//            expected25.print();
//            std::cout << "Result: ";
//            result25.print();
//        }
//        assert(result25 == expected25);
    }

    void testVector4()
    {
        // Test default constructor
        Vector4 v1;
        assert(v1.coordinates.x == 0.0 && v1.coordinates.y == 0.0 && v1.coordinates.z == 0.0 && v1.coordinates.w == 0.0);

        // Test constructor with parameters
        Vector4 v2(1.0, 2.0, 3.0, 4.0);
        assert(v2.coordinates.x == 1.0 && v2.coordinates.y == 2.0 && v2.coordinates.z == 3.0 && v2.coordinates.w == 4.0);

        // Test copy constructor
        Vector4 v3(v2);
        assert(v3.coordinates.x == 1.0 && v3.coordinates.y == 2.0 && v3.coordinates.z == 3.0 && v3.coordinates.w == 4.0);

        // Test dot product
        Vector4 v4(2.0, 3.0, 4.0, 5.0);
        assert(v2.dot(v4) == 40.0);

        // Test component-wise multiplication
        Vector4 v5(1.0, 2.0, 3.0, 4.0);
        Vector4 v6(2.0, 3.0, 4.0, 5.0);
        Vector4 v7 = v5.componentWise(v6);
        assert(v7.coordinates.x == 2.0 && v7.coordinates.y == 6.0 && v7.coordinates.z == 12.0 && v7.coordinates.w == 20.0);

        // Test magnitude and squareMagnitude
        assert(v4.magnitude() == sqrt(54));
        assert(v4.squareMagnitude() == 54);

        // Test normalization
        v4.normalize();
        assert(v4.magnitude() == 1.0);

        // Test indexing operator
        assert(v5[0] == 1.0 && v5[1] == 2.0 && v5[2] == 3.0 && v5[3] == 4.0);

        // Test equality operator
        assert(v2 == v3 && !(v2 == v4));

        // Test negation, scalar multiplication and division
        Vector4 v8 = -v5;
        Vector4 v9 = v5 * 2.0;
        Vector4 v10 = v5 / 2.0;
        assert(v8.coordinates.x == -1.0 && v8.coordinates.y == -2.0 && v8.coordinates.z == -3.0 && v8.coordinates.w == -4.0);
        assert(v9.coordinates.x == 2.0 && v9.coordinates.y == 4.0 && v9.coordinates.z == 6.0 && v9.coordinates.w == 8.0);
        assert(v10.coordinates.x == 0.5 && v10.coordinates.y == 1.0 && v10.coordinates.z == 1.5 && v10.coordinates.w == 2.0);

        // Test compound assignment operators
        v5 += v6;
        assert(v5.coordinates.x == 3.0 && v5.coordinates.y == 5.0 && v5.coordinates.z == 7.0 && v5.coordinates.w == 9.0);

        v5 -= v6;
        assert(v5.coordinates.x == 1.0 && v5.coordinates.y == 2.0 && v5.coordinates.z == 3.0 && v5.coordinates.w == 4.0);
        // Test scalar multiplication
        Vector4 vA(1.0, 2.0, 3.0, 4.0);
        vA *= 2.0;
        assert(vA.coordinates.x == 2.0 && vA.coordinates.y == 4.0 && vA.coordinates.z == 6.0 && vA.coordinates.w == 8.0);

        // Test scalar division
        Vector4 vB(2.0, 4.0, 6.0, 8.0);
        vB /= 2.0;
        assert(vB.coordinates.x == 1.0 && vB.coordinates.y == 2.0 && vB.coordinates.z == 3.0 && vB.coordinates.w == 4.0);

        // Test dot product
        Vector4 vC(1.0, 2.0, 3.0, 4.0);
        Vector4 vD(2.0, 3.0, 4.0, 5.0);
        Scalar result = vC.dot(vD);
        assert(result == 40.0);

        // Test component wise product
        Vector4 v11(1.0, 2.0, 3.0, 4.0);
        Vector4 v12(2.0, 3.0, 4.0, 5.0);
        Vector4 v13 = v11.componentWise(v12);
        assert(v13.coordinates.x == 2.0 && v13.coordinates.y == 6.0 && v13.coordinates.z == 12.0 && v13.coordinates.w == 20.0);

        // Test magnitude
        Vector4 v14(1.0, 2.0, 3.0, 4.0);
        Scalar magnitude = v14.magnitude();
        assert(abs(magnitude - 5.477225575051661) < EPSILON);

        // Test square magnitude
        Vector4 v15(1.0, 2.0, 3.0, 4.0);
        Scalar squareMagnitude = v15.squareMagnitude();
        assert(squareMagnitude == 30.0);

        // Test normalization
        Vector4 v16(1.0, 2.0, 3.0, 4.0);
        v16.normalize();
        assert(abs(v16.magnitude() - 1.0) < EPSILON);

        // Test operator[]
        Vector4 v17(1.0, 2.0, 3.0, 4.0);
        assert(v17[0] == 1.0 && v17[1] == 2.0 && v17[2] == 3.0 && v17[3] == 4.0);

        // Test angleBetween
        Vector4 v18(1.0, 2.0, 3.0, 4.0);
        Vector4 v19(2.0, 3.0, 4.0, 5.0);
        Scalar angle = v18.angleBetween(v19);
        assert(abs(angle - 6.379370208442824) < EPSILON);

        // Test lerp
        Vector4 v20(1.0, 2.0, 3.0, 4.0);
        Vector4 v21(2.0, 3.0, 4.0, 5.0);
        Vector4 v22 = v20.lerp(v21, 0.5);
        assert(v22.coordinates.x == 1.5 && v22.coordinates.y == 2.5 && v22.coordinates.z == 3.5 && v22.coordinates.w == 4.5);

        // Test angleBetween
        Vector4 v24(1.0, 0.0, 0.0, 0.0);
        Vector4 v25(0.0, 1.0, 0.0, 0.0);
        assert(v24.angleBetween(v25) == 90.0);

        // Test truncateToVector3
        Vector4 v26(1.0, 2.0, 3.0, 4.0);
        Vector3 v27 = v26.truncateToVector3();
        assert(v27.coordinates.x == 1.0 && v27.coordinates.y == 2.0 && v27.coordinates.z == 3.0);

        // Test asVersor4
//        Vector4 v28(1.0, 2.0, 3.0, 0.0);
//        Versor4 v29 = v28.asVersor4();
//        assert(v29.coordinates.x == 1.0/3.0 && v29.coordinates.y == 2.0/3.0 && v29.coordinates.z == 3.0/3.0 && v29.coordinates.w == 0.0);

        // Test asPoint4
//        Vector4 v30(1.0, 2.0, 3.0, 0.0);
//        Point4 v31 = v30.asPoint4();
//        assert(v31.coordinates.x == 1.0 && v31.coordinates.y == 2.0 && v31.coordinates.z == 3.0 && v31.coordinates.w == 1.0);

        // Test isZero and areEquals
        Vector4 v32(0.0, 0.0, 0.0, 0.0);
        assert(v32.isZero());

        Vector4 v33(1.0, 2.0, 3.0, 4.0);
        assert(!v33.isZero());

        Vector4 v34(1.0, 2.0, 3.0, 4.0);
        Vector4 v35(1.0, 2.0, 3.0, 4.0);
        Vector4 v36(1.0, 2.0, 3.0, 5.0);
        assert(v34.areEquals(v35));
        assert(!v34.areEquals(v36));

        // Test truncateToVector3
        Vector4 v37(1.0, 2.0, 3.0, 4.0);
        Vector3 v38 = v37.truncateToVector3();
        assert(v38.coordinates.x == 1.0 && v38.coordinates.y == 2.0 && v38.coordinates.z == 3.0);

        // Test asVersor4
//        Vector4 v39(1.0, 2.0, 3.0, 0.0);
//        Versor4 v40 = v39.asVersor4();
//        assert(v40.coordinates.x == v39.coordinates.x && v40.coordinates.y == v39.coordinates.y && v40.coordinates.z == v39.coordinates.z && v40.coordinates.w == 0.0);
        
        // Test truncateToVector3
        Vector4 vG(1.0, 2.0, 3.0, 4.0);
        Vector3 vH = vG.truncateToVector3();
        assert(vH.coordinates.x == 1.0 && vH.coordinates.y == 2.0 && vH.coordinates.z == 3.0);

        // Test print
        std::cout << "vH: ";
        vH.print();
    }

    void testVector3() {
        // Test default constructor
        Vector3 v1;
        assert(v1.coordinates.x == 0.0 && v1.coordinates.y == 0.0 && v1.coordinates.z == 0.0);

        // Test constructor with values
        Vector3 v2(1.0, 2.0, 3.0);
        assert(v2.coordinates.x == 1.0 && v2.coordinates.y == 2.0 && v2.coordinates.z == 3.0);

        // Test copy constructor
        Vector3 v3(v2);
        assert(v3.coordinates.x == 1.0 && v3.coordinates.y == 2.0 && v3.coordinates.z == 3.0);

        // Test assignment operator
        v1 = v2;
        assert(v1.coordinates.x == 1.0 && v1.coordinates.y == 2.0 && v1.coordinates.z == 3.0);

        // Test component-wise addition
        Vector3 v4(2.0, 3.0, 4.0);
        Vector3 v5 = v2 + v4;
        assert(v5.coordinates.x == 3.0 && v5.coordinates.y == 5.0 && v5.coordinates.z == 7.0);

        // Test component-wise subtraction
        Vector3 v6 = v2 - v4;
        assert(v6.coordinates.x == -1.0 && v6.coordinates.y == -1.0 && v6.coordinates.z == -1.0);

        // Test scalar multiplication
        Vector3 v7 = v2 * 2.0;
        assert(v7.coordinates.x == 2.0 && v7.coordinates.y == 4.0 && v7.coordinates.z == 6.0);

        // Test scalar division
        Vector3 v8 = v2 / 2.0;
        assert(v8.coordinates.x == 0.5 && v8.coordinates.y == 1.0 && v8.coordinates.z == 1.5);

        // Test dot product
        Scalar dot = v2 * v4;
        assert(dot == 20.0);

        // Test cross product
        Vector3 v9 = Vector3::cross(v2, v4);
        assert(v9.coordinates.x == -1.0 && v9.coordinates.y == 2.0 && v9.coordinates.z == -1.0);

        // Test magnitude
        Scalar mag = v2.magnitude();
        assert(mag == std::sqrt(14.0));

        // Test normalization
        Vector3 v10 = v2.normalized();
        assert(std::abs(v10.magnitude() - 1.0) < 0.0001);

        // Test distance
        Scalar dist = Vector3::distance(v2, v4);
        assert((dist - 1.73205) < 0.0001);

        // Test lerp
        Vector3 v11 = v2.lerp(v4, 0.5);
        assert(v11.coordinates.x == 1.5 && v11.coordinates.y == 2.5 && v11.coordinates.z == 3.5);
        
        // Test outer product
        Vector3 vA(1.0, 2.0, 3.0);
        Vector3 vB(4.0, 5.0, 6.0);
        Matrix3 m1 = vA.outer(vB);
        Matrix3 expected1(4.0, 5.0, 6.0, 8.0, 10.0, 12.0, 12.0, 15.0, 18.0);
        for (int i = 0; i < 9; i++) {
            assert(m1.data[i] == expected1.data[i]);
        }
    }
}

#endif /* MathTest_h */
