#ifndef __MESHUTILS_H__
#define __MESHUTILS_H__

#include <Eigen/Core>

#include <vector>
#include <queue>
#include <cmath>

#include <iostream>

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
            p << P.row(i)(0), P.row(i)(1), P.row(i)(2), 1;
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

double compute_collapse_cost(Quadric q0, Quadric q1, Eigen::RowVector3d p0, Eigen::RowVector3d p1);

// Define a function to perform an edge collapse
void perform_collapse(int e, Eigen::MatrixXd &V, Eigen::MatrixXi &F, std::vector<Quadric> &quadrics, std::priority_queue<Edge, std::vector<Edge>, CompareEdges> &queue);

// Define a function to perform mesh simplification using quadric error metrics
void simplify_quadric_error(Eigen::MatrixXd &V, Eigen::MatrixXi &F, int target_num_vertices);

#endif
