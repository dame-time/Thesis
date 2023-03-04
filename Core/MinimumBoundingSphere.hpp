#ifndef __MINIMUMBOUNDINGSPHERE_H__
#define __MINIMUMBOUNDINGSPHERE_H__

#include <Eigen/Dense>
#include <Eigen/Core>
#include <Eigen/SparseCore>

#include <Vector3.hpp>

#include <igl/adjacency_matrix.h>
#include <igl/vertex_triangle_adjacency.h>
#include <igl/edge_topology.h>

#include <vector>
#include <string>
#include <unordered_map>

#include "SQEM.h"

class Sphere
{
    public:
        Math::Vector3 center;
        float radius;

        Sphere() : center(0.0f, 0.0f, 0.0f), radius(0.0f) {}

        Sphere(const Math::Vector3 &center, float radius) : center(center), radius(radius) {}

        bool contains(const Math::Vector3 &point) const
        {
            return (point - center).squareMagnitude() <= radius * radius;
        }
};

struct NeighborVertexNormal {
    std::vector<std::vector<Math::Vector3>> vertexBatch;
    std::vector<std::vector<Math::Vector3>> normalBatch;
};

struct Plane {
    std::vector<std::vector<Math::Vector3>> vertices;
    Math::Vector3 normal;
};

class MinimumBoundingSphere
{
    public:
        static void getVertexToTripletMap(const Eigen::MatrixXd &V, const Eigen::MatrixXi &F, std::unordered_map<int, std::vector<std::vector<Math::Vector3>>> &vertexToTripletMap)
        {
            // Compute vertex to triangle adjacency list
            std::vector<std::vector<int>> VF, VFi;
            igl::vertex_triangle_adjacency(V, F, VF, VFi);

            // Initialize vertexToTripletMap with empty vectors
            for (int i = 0; i < V.rows(); i++)
            {
                vertexToTripletMap[i] = std::vector<std::vector<Math::Vector3>>();
            }

            // Iterate over vertices
            for (int vertexIdx = 0; vertexIdx < V.rows(); vertexIdx++)
            {
                // Iterate over triangles adjacent to vertex
                for (int tripletIdx : VF[vertexIdx])
                {
                    // Get the three vertices of the triplet
                    const int v1 = F(tripletIdx, 0);
                    const int v2 = F(tripletIdx, 1);
                    const int v3 = F(tripletIdx, 2);

                    // Add the triplet to the vertex's vector in the map
                    std::vector<Math::Vector3> tripletCoords;
                    tripletCoords.push_back(Math::Vector3(V.row(v1)[0], V.row(v1)[1], V.row(v1)[2]));
                    tripletCoords.push_back(Math::Vector3(V.row(v2)[0], V.row(v2)[1], V.row(v2)[2]));
                    tripletCoords.push_back(Math::Vector3(V.row(v3)[0], V.row(v3)[1], V.row(v3)[2]));

                    auto normal = Math::Vector3(V.row(v1)[0], V.row(v1)[1], V.row(v1)[2]) +
                                  Math::Vector3(V.row(v2)[0], V.row(v2)[1], V.row(v2)[2]) +
                                  Math::Vector3(V.row(v3)[0], V.row(v3)[1], V.row(v3)[2]);
                    normal /= 3;
                    tripletCoords.push_back(normal.normalized());

                    vertexToTripletMap[vertexIdx].push_back(tripletCoords);
                }
            }
        }

        static std::vector<Sphere> Compute(const std::vector<Math::Vector3> &vertices,
                                    const std::vector<Math::Vector3> &normals,
                                    const int batchSize = 1000)
        {
            // Batch the vertices and normals
            std::vector<std::vector<Math::Vector3>> vertexBatches, normalBatches;
            BatchVerticesAndNormals(vertices, normals, vertexBatches, normalBatches, 10.0f, batchSize);

            // Compute the minimum bounding sphere for each batch
            std::vector<Sphere> minimumBoundingSpheres;
            for (int i = 0; i < vertexBatches.size(); ++i)
            {
                Sphere minimumBoundingSphere;
                ComputeMinimumBoundingSphereForBatch(vertexBatches[i], normalBatches[i], minimumBoundingSphere);
                minimumBoundingSpheres.push_back(minimumBoundingSphere);
            }

            return minimumBoundingSpheres;
        }
        
        static std::vector<Sphere> ComputeWithMatrices(const Eigen::MatrixXd &V, 
                                    const Eigen::MatrixXi &F, 
                                    const Eigen::MatrixXd &N,
                                    const int batchSize = 1000)
        {
            // Batch the vertices and normals
            auto batches = GetAdjacentVertices(V, F, N);

            // Compute the minimum bounding sphere for each batch
            std::vector<Sphere> minimumBoundingSpheres;
            for (int i = 0; i < batches.vertexBatch.size(); ++i)
            {
                Sphere minimumBoundingSphere;
                ComputeMinimumBoundingSphereForBatch(batches.vertexBatch[i], batches.normalBatch[i], minimumBoundingSphere);
                minimumBoundingSpheres.push_back(minimumBoundingSphere);
            }

            return minimumBoundingSpheres;
        }
        
        static std::vector<Sphere> ComputeWithFaces(const Eigen::MatrixXd &V, 
                                    const Eigen::MatrixXi &F, 
                                    const Eigen::MatrixXd &N,
                                    const int batchSize = 1000)
        {
            // Batch the vertices and normals
            std::vector<Math::Vector3> faces;
            std::vector<Math::Vector3> normals;
            BatchFacesAndNormals(V, F, N, faces, normals, 20, batchSize);

            SQEM sqem = SQEM();
            Math::Vector3 sphereCenter;
            float sphereRadius = 0.0f;
            const float MAX_RADIUS = 10.f;

            // Compute the minimum bounding sphere for each batch
            std::vector<Sphere> minimumBoundingSpheres;
            // for (int i = 0; i < faces.size(); i += batchSize)
            // {
            //     sqem.setZero();
            //     Sphere minimumBoundingSphere;

            //     std::cout << " ======================================= " << std::endl;

            //     for (int j = i; j < i + batchSize; ++j)
            //     {
            //         if (i > faces.size() - 1)
            //             break;

            //         if (faces[j] == Math::Vector3(0, 0, 0))
            //             continue;

            //         sqem += SQEM(faces[j], normals[i]);

            //         faces[j].print();
            //         normals[j].print();
            //     }

            //     sqem.minimize(sphereCenter, sphereRadius, Math::Vector3(-MAX_RADIUS, -MAX_RADIUS, -MAX_RADIUS), Math::Vector3(MAX_RADIUS, MAX_RADIUS, MAX_RADIUS));

            //     minimumBoundingSphere.radius = sphereRadius;
            //     minimumBoundingSphere.center = sphereCenter;

            //     minimumBoundingSpheres.push_back(minimumBoundingSphere);
            // }

            for (int i = 0; i < faces.size(); i++) {
                Sphere minimumBoundingSphere;

                minimumBoundingSphere.radius = 0.1f;
                minimumBoundingSphere.center = faces[i];

                minimumBoundingSpheres.push_back(minimumBoundingSphere);
            }

            return minimumBoundingSpheres;
        }

        static NeighborVertexNormal GetAdjacentVertices(const Eigen::MatrixXd &V, const Eigen::MatrixXi &F, const Eigen::MatrixXd &N)
        {
            NeighborVertexNormal nvm;

            std::vector<Math::Vector3> neighbors;
            std::vector<Math::Vector3> neighborsNormals;

            Eigen::SparseMatrix<int> A;
            igl::adjacency_matrix(F, A);

            for (int i = 0; i < V.rows(); i++)
            {
                neighbors.clear();

                Eigen::SparseVector<int> row = A.row(i);
                int* indices = row.innerIndexPtr();

                Math::Vector3 vertex = Math::Vector3(V.row(i)[0], V.row(i)[1], V.row(i)[2]);
                Math::Vector3 normal = Math::Vector3(N.row(i)[0], N.row(i)[1], N.row(i)[2]);
                neighbors.push_back(vertex);
                neighborsNormals.push_back(normal);

                std::cout << "Starting Vertex: ";
                vertex.print();

                for (int k = 0; k < row.nonZeros(); ++k)
                {
                    int j = indices[k];

                    Math::Vector3 adjVertex = Math::Vector3(V.row(j)[0], V.row(j)[1], V.row(j)[2]);
                    Math::Vector3 adjNormal = Math::Vector3(N.row(j)[0], N.row(j)[1], N.row(j)[2]);
                    neighbors.push_back(adjVertex);
                    neighborsNormals.push_back(adjNormal);

                    std::cout << "  Adj Vertex: ";
                    adjVertex.print();
                }

                nvm.vertexBatch.push_back(neighbors);
                nvm.normalBatch.push_back(neighborsNormals);
            }

            return nvm;
        }

        // static std::unordered_map<std::string, Plane> GetAdjacentFaces(const Eigen::MatrixXd &V, const Eigen::MatrixXi &F, const Eigen::MatrixXd &N)
        // {
        //     std::vector<std::vector<Math::Vector3>> faces;

        //     for (int j = 0; j < V.rows(); j++)
        //         for (int i = 0; i < F.rows(); i++)
        //         {
        //             if (F(i, 0) == j || F(i, 1) == j || F(i, 2) == j)
        //             {
        //                 Plane plane;

        //                 std::vector<Math::Vector3> face;
        //                 face.push_back(Math::Vector3(V.row(F(i, 0))[0], V.row(F(i, 0))[1], V.row(F(i, 0))[2]));
        //                 face.push_back(Math::Vector3(V.row(F(i, 1))[0], V.row(F(i, 1))[1], V.row(F(i, 1))[2]));
        //                 face.push_back(Math::Vector3(V.row(F(i, 2))[0], V.row(F(i, 2))[1], V.row(F(i, 2))[2]));
                        

        //             }
        //         }

        //     return faces;
        // }

        static void extractFaceVertices(const Eigen::MatrixXd &V, const Eigen::MatrixXi &F,
                                        std::vector<std::vector<Math::Vector3>> &faceVertices)
        {

            faceVertices.clear();
            faceVertices.reserve(F.rows());

            for (int i = 0; i < F.rows(); ++i)
            {
                std::vector<Math::Vector3> vertices;
                vertices.reserve(3);

                for (int j = 0; j < 3; ++j)
                {
                    const int vertexIndex = F(i, j);
                    vertices.emplace_back(V(vertexIndex, 0), V(vertexIndex, 1), V(vertexIndex, 2));
                }

                faceVertices.emplace_back(std::move(vertices));
            }
        }

        static void extractFaceNormals(const Eigen::MatrixXd &V, const Eigen::MatrixXi &F, const Eigen::MatrixXd &N,
                                       std::vector<std::vector<Math::Vector3>> &faceNormals)
        {

            faceNormals.clear();
            faceNormals.reserve(F.rows());

            for (int i = 0; i < F.rows(); ++i)
            {
                std::vector<Math::Vector3> normals;
                normals.reserve(3);

                for (int j = 0; j < 3; ++j)
                {
                    const int vertexIndex = F(i, j);
                    normals.emplace_back(N(vertexIndex, 0), N(vertexIndex, 1), N(vertexIndex, 2));
                }

                faceNormals.emplace_back(std::move(normals));
            }
        }

        static Math::Vector3 ComputeCentroid(const Math::Vector3& v1, const Math::Vector3& v2, const Math::Vector3& v3)
        {
            Math::Vector3 centroid;

            centroid[0] = (v1[0] + v2[0] + v3[0]) / 3.0;
            centroid[1] = (v1[1] + v2[1] + v3[1]) / 3.0;
            centroid[2] = (v1[2] + v2[2] + v3[2]) / 3.0;

            return centroid;
        }

    private:
        static void BatchVerticesAndNormals(const std::vector<Math::Vector3> &vertices,
                                            const std::vector<Math::Vector3> &normals,
                                            std::vector<std::vector<Math::Vector3>> &vertexBatches,
                                            std::vector<std::vector<Math::Vector3>> &normalBatches,
                                            float threshold,
                                            int maxBatchSize = 1000)
        {
            std::vector<std::vector<int>> adjacencyList(vertices.size());
            for (int i = 0; i < vertices.size() - 1; ++i)
            {
                for (int j = i + 1; j < vertices.size(); ++j)
                {
                    float angle = vertices[i].angleBetween(vertices[j]);
                    if (angle <= threshold)
                    {
                        adjacencyList[i].push_back(j);
                        adjacencyList[j].push_back(i);
                    }
                }
            }

            std::vector<bool> visited(vertices.size(), false);
            std::vector<int> batch;
            std::vector<Math::Vector3> vertexBatch, normalBatch;
            for (int i = 0; i < vertices.size(); ++i)
            {
                if (!visited[i])
                {
                    batch.push_back(i);
                    visited[i] = true;

                    while (!batch.empty())
                    {
                        int vertexIndex = batch.back();
                        batch.pop_back();
                        vertexBatch.push_back(vertices[vertexIndex]);
                        normalBatch.push_back(normals[vertexIndex]);

                        for (int neighborIndex : adjacencyList[vertexIndex])
                        {
                            if (!visited[neighborIndex])
                            {
                                visited[neighborIndex] = true;
                                batch.push_back(neighborIndex);
                            }
                        }

                        if (vertexBatch.size() >= maxBatchSize)
                        {
                            vertexBatches.push_back(vertexBatch);
                            normalBatches.push_back(normalBatch);
                            vertexBatch.clear();
                            normalBatch.clear();
                        }
                    }
                }
            }

            if (!vertexBatch.empty())
            {
                vertexBatches.push_back(vertexBatch);
                normalBatches.push_back(normalBatch);
            }
        }

        static void BatchFacesAndNormals(const Eigen::MatrixXd &V,
                                         const Eigen::MatrixXi &F,
                                         const Eigen::MatrixXd &N,
                                         std::vector<Math::Vector3> &faceCentroids,
                                         std::vector<Math::Vector3> &normalBatches,
                                         float threshold,
                                         int maxBatchSize = 1000)
        {
            std::vector<std::vector<int>> adjacencyList(V.rows());
            for (int i = 0; i < F.rows(); ++i)
            {
                for (int j = 0; j < F.cols(); ++j)
                {
                    int v1 = F(i, j);
                    for (int k = j + 1; k < F.cols(); ++k)
                    {
                        int v2 = F(i, k);
                        if ((V.row(v1) - V.row(v2)).norm() <= threshold)
                        {
                            adjacencyList[v1].push_back(v2);
                            adjacencyList[v2].push_back(v1);
                        }
                    }
                }
            }

            std::vector<bool> visited(V.rows(), false);
            std::vector<int> batch;
            Math::Vector3 avgNormal;
            for (int i = 0; i < V.rows(); ++i)
            {
                if (!visited[i])
                {
                    batch.push_back(i);
                    visited[i] = true;

                    while (!batch.empty())
                    {
                        int vertexIndex = batch.back();
                        batch.pop_back();
                        std::vector<int> adjVertices = adjacencyList[vertexIndex];

                        for (int j = 0; j < adjVertices.size(); ++j)
                        {
                            int v1 = vertexIndex;
                            int v2 = adjVertices[j];

                            for (int k = j + 1; k < adjVertices.size(); ++k)
                            {
                                int v3 = adjVertices[k];
                                Eigen::Matrix<double, 3, 3> face;
                                face << V.row(v1), V.row(v2), V.row(v3);
                                Math::Vector3 centroid = (Math::Vector3(face.row(0)[0], face.row(0)[1], face.row(0)[1]) + Math::Vector3(face.row(1)[0], face.row(1)[1], face.row(1)[1]) + Math::Vector3(face.row(2)[0], face.row(2)[1], face.row(2)[1])) / 3.0;
                                faceCentroids.push_back(centroid);
                                auto n1 = (Math::Vector3(N.row(v1)[0], N.row(v1)[1], N.row(v1)[2]));
                                auto n2 = (Math::Vector3(N.row(v2)[0], N.row(v2)[1], N.row(v2)[2]));
                                auto n3 = (Math::Vector3(N.row(v3)[0], N.row(v3)[1], N.row(v3)[2]));

                                avgNormal = n1 + n2 + n3;
                                avgNormal /= 3;

                                normalBatches.push_back(avgNormal.normalized());
                            }
                        }


                        for (int neighborIndex : adjacencyList[vertexIndex])
                        {
                            if (!visited[neighborIndex])
                            {
                                visited[neighborIndex] = true;
                                batch.push_back(neighborIndex);
                            }
                        }
                    }
                }
            }

            // if (!faceCentroids.empty())
            // {
            //     normalBatches.push_back(avgNormal);
            // }
        }

        static void ComputeMinimumBoundingSphereForBatch(const std::vector<Math::Vector3> &vertexBatch,
                                                         const std::vector<Math::Vector3> &normalBatch,
                                                         Sphere &minimumBoundingSphere)
        {
            SQEM sqem = SQEM(vertexBatch[0], normalBatch[0]);
            Math::Vector3 sphereCenter;
            float sphereRadius = 0.0f;
            const float MAX_RADIUS = 100.f;

            std::cout << "=============================" << std::endl;

            for (int i = 1; i < vertexBatch.size(); ++i)
            {
                sqem += SQEM(vertexBatch[i], normalBatch[i]);
                vertexBatch[i].print();
            }

            std::cout << "=============================" << std::endl;

            sqem.minimize(sphereCenter, sphereRadius, Math::Vector3(-MAX_RADIUS, -MAX_RADIUS, -MAX_RADIUS), Math::Vector3(MAX_RADIUS, MAX_RADIUS, MAX_RADIUS));
            minimumBoundingSphere.radius = sphereRadius;
            minimumBoundingSphere.center = sphereCenter;
        }
        
        static void ComputeMinimumBoundingSphereForFace(const Math::Vector3 &face,
                                                         const Math::Vector3 &normal,
                                                         Sphere &minimumBoundingSphere)
        {
            SQEM sqem = SQEM(face, normal);
            Math::Vector3 sphereCenter;
            float sphereRadius = 0.0f;
            const float MAX_RADIUS = 100.f;

            sqem.minimize(sphereCenter, sphereRadius, Math::Vector3(-MAX_RADIUS, -MAX_RADIUS, -MAX_RADIUS), Math::Vector3(MAX_RADIUS, MAX_RADIUS, MAX_RADIUS));
            minimumBoundingSphere.radius = sphereRadius;
            minimumBoundingSphere.center = sphereCenter;
        }
};

#endif