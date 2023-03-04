#include <iostream>
#include <igl/readOBJ.h>
#include <igl/per_face_normals.h>
#include <igl/per_vertex_normals.h>
#include <igl/qslim.h>
#include <Eigen/Core>
#include <queue>
#include <cmath>

// Define a struct for a quadric
struct Quadric
{
    Eigen::Matrix4d Q;
    double error;
    Quadric() : Q(Eigen::Matrix4d::Zero()), error(0) {}
    Quadric(Eigen::MatrixXd P, Eigen::VectorXd w) : Q(Eigen::Matrix4d::Zero()), error(0)
    {
        for (int i = 0; i < P.rows(); i++)
        {
            Eigen::Vector4d p;
            p << P.row(i), 1;
            Q += w(i) * p * p.transpose();
            error += p.transpose() * Q * p;
        }
    }
};

// Define a struct for an edge
struct Edge
{
    int v0;
    int v1;
    double cost;
    Edge() : v0(-1), v1(-1), cost(0) {}
    Edge(int _v0, int _v1, double _cost) : v0(_v0), v1(_v1), cost(_cost) {}
};

// Define a comparison operator for edges
struct CompareEdges
{
    bool operator()(const Edge &e1, const Edge &e2) const
    {
        return e1.cost > e2.cost;
    }
};

double compute_collapse_cost(Quadric q0, Quadric q1, Eigen::RowVector3d p0, Eigen::RowVector3d p1)
{
    // // Compute the combined quadric and its error
    // Quadric q = q0;
    // q.Q += q1.Q;
    // q.error += q0.error + q1.error;

    // // Compute the center of the sphere that best approximates the region
    // Eigen::Vector4d c = q.Q.inverse() * Eigen::Vector4d::Ones();
    // Eigen::Vector3d center = c.head<3>() / c(3);

    // // Compute the radius of the sphere
    // double radius = (center - Eigen::RowVector4d(p0(0), p0(1), p0(2), 1.0)).norm();

    // // Compute the error of the collapse
    // Eigen::Vector4d p0_h, p1_h;
    // p0_h << p0, 1;
    // double error = p0_h.transpose() * q.Q * p0_h;
    // p1_h << p1, 1;
    // error += p1_h.transpose() * q.Q * p1_h;

    // return error - q.error + 2 * radius;
    return 0;
}

// Define a function to perform an edge collapse
void perform_collapse(int e, Eigen::MatrixXd &V, Eigen::MatrixXi &F, std::vector<Quadric> &quadrics, std::priority_queue<Edge, std::vector<Edge>, CompareEdges> &queue)
{
    // Get the indices of the edge
    int v0 = F(e, 0);
    int v1 = F(e, 1);

    // Remove the edge from the queue
    queue = std::priority_queue<Edge, std::vector<Edge>, CompareEdges>(queue);

    // Compute the new vertex
    Eigen::RowVector3d p0 = V.row(v0);
    Eigen::RowVector3d p1 = V.row(v1);
    Eigen::RowVector3d p_new = (p0 + p1) / 2;
    // Update the vertex and quadric at v0
    V.row(v0) = p_new;
    quadrics[v0] = Quadric(V.rowwise() - p_new, Eigen::VectorXd::Ones(V.rows()));

    // Update the connectivity and quadrics of v1
    int num_v1_neighbors = 0;
    Eigen::MatrixXi F_tmp(F.rows(), 3);
    for (int i = 0; i < F.rows(); i++)
    {
        int v2 = -1;
        for (int j = 0; j < 3; j++)
        {
            if (F(i, j) == v1)
            {
                F_tmp.row(i) << v0, F(i, (j + 1) % 3), F(i, (j + 2) % 3);
                v2 = F(i, (j + 1) % 3);
            }
        }
        if (v2 != -1)
        {
            quadrics[v2] = Quadric(V.rowwise() - V.row(v2), Eigen::VectorXd::Ones(V.rows()));
            num_v1_neighbors++;
        }
        else
        {
            F_tmp.row(i) = F.row(i);
        }
    }
    F = F_tmp.topRows(F.rows() - 2);
    quadrics[v1] = Quadric();

    // Update the connectivity and quadrics of v0
    for (int i = 0; i < F.rows(); i++)
    {
        int v2 = -1;
        for (int j = 0; j < 3; j++)
        {
            if (F(i, j) == v0)
            {
                v2 = F(i, (j + 1) % 3);
            }
        }
        if (v2 != -1)
        {
            quadrics[v2] = Quadric(V.rowwise() - V.row(v2), Eigen::VectorXd::Ones(V.rows()));
            Edge edge(v0, v2, compute_collapse_cost(quadrics[v0], quadrics[v2], p_new, V.row(v2)));
            queue.push(edge);
        }
    }

    // Remove any collapsed edges from the queue
    std::priority_queue<Edge, std::vector<Edge>, CompareEdges> new_queue;
    while (!queue.empty())
    {
        Edge edge = queue.top();
        queue.pop();
        if (edge.v0 != v1 && edge.v1 != v1)
        {
            new_queue.push(edge);
        }
    }
    queue = new_queue;
}

// Define a function to perform mesh simplification using quadric error metrics
void simplify_quadric_error(Eigen::MatrixXd &V, Eigen::MatrixXi &F, int target_num_vertices)
{
    // Initialize the quadrics
    std::vector<Quadric> quadrics(V.rows());
    for (int i = 0; i < V.rows(); i++)
    {
        quadrics[i] = Quadric(V.rowwise() - V.row(i), Eigen::VectorXd::Ones(V.rows()));
    }
    // Initialize the priority queue
    std::priority_queue<Edge, std::vector<Edge>, CompareEdges> queue;
    for (int i = 0; i < F.rows(); i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int v0 = F(i, j);
            int v1 = F(i, (j + 1) % 3);
            if (v0 < v1)
            {
                Edge edge(v0, v1, compute_collapse_cost(quadrics[v0], quadrics[v1], V.row(v0), V.row(v1)));
                queue.push(edge);
            }
        }
    }

    // Decimate the mesh until the desired number of vertices is reached
    while (V.rows() > target_num_vertices)
    {
        // Get the edge with the lowest cost
        Edge edge = queue.top();
        queue.pop();
        // Perform the edge collapse
        perform_collapse(edge.v0 < edge.v1 ? edge.v0 : edge.v1, V, F, quadrics, queue);
    }
}
