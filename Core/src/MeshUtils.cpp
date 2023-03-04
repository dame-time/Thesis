#include "../MeshUtils.hpp"

#include <igl/readOBJ.h>
#include <igl/per_face_normals.h>
#include <igl/per_vertex_normals.h>
#include <igl/qslim.h>

double compute_collapse_cost(Quadric q0, Quadric q1, Eigen::RowVector3d p0, Eigen::RowVector3d p1)
{
    // Compute the combined quadric and its error
    Quadric q = q0;
    q.Q += q1.Q;
    q.error += q0.error + q1.error;

    // Compute the center of the sphere that best approximates the region
    Eigen::Vector4d c = q.Q.inverse() * Eigen::Vector4d::Ones();
    Eigen::Vector3d center = c.head<3>() / c(3);

    // Compute the radius of the sphere
    double radius = (center - Eigen::Vector3d(p0(0), p0(1), p0(2))).norm();

    // Compute the error of the collapse
    Eigen::Vector4d p0_h, p1_h;
    p0_h << p0(0), p0(1), p0(2), 1;
    double error = p0_h.transpose() * q.Q * p0_h;
    p1_h << p1(0), p1(1), p1(2), 1;
    error += p1_h.transpose() * q.Q * p1_h;

    return error - q.error + 2 * radius;
}

void perform_collapse(int e, Eigen::MatrixXd &V, Eigen::MatrixXi &F, std::vector<Quadric> &quadrics, std::priority_queue<Edge, std::vector<Edge>, CompareEdges> &queue)
{
    // Get the indices of the edge
    int v0 = F(e, 0);
    int v1 = F(e, 1);

    // Remove the edge from the queue
    queue = std::priority_queue<Edge, std::vector<Edge>, CompareEdges>(queue);
    std::vector<Edge> edges_to_remove;

    // Make a copy of the queue
    auto queue_copy = queue;

    while (!queue_copy.empty())
    {
        Edge edge = queue_copy.top();
        if (edge.v0 == v0 || edge.v0 == v1 || edge.v1 == v0 || edge.v1 == v1)
        {
            edges_to_remove.push_back(edge);
        }
        queue_copy.pop();
    }

    for (const auto &edge : edges_to_remove)
    {
        if (edge.v0 != v1 && edge.v1 != v1)
        {
            queue.push(edge);
        }
    }

    // Compute the new vertex
    Eigen::RowVector3d p0 = V.row(v0);
    Eigen::RowVector3d p1 = V.row(v1);
    Eigen::RowVector3d p_new = (p0 + p1) / 2;
    // Update the vertex and quadric at v0
    V.row(v0) = p_new;
    quadrics[v0] = Quadric(V.rowwise() - p_new, Eigen::VectorXd::Ones(V.rows()));

    // Update the connectivity and quadrics of v1
    int num_v1_neighbors = 0;
    Eigen::MatrixXi F_tmp = Eigen::MatrixXi::Zero(F.rows(), 3);
    int j = 0;
    for (int i = 0; i < F.rows(); i++)
    {
        if (F(i, 0) != v1 && F(i, 1) != v1 && F(i, 2) != v1)
        {
            F_tmp.row(j++) = F.row(i);
        }
        else
        {
            int v2 = F(i, 0) == v1 ? F(i, 1) : F(i, 0);
            if (F(i, 2) != v1)
            {
                v2 = F(i, 2);
            }
            F_tmp.row(j++) << v0, v1, v2;
            quadrics[v2] = Quadric(V.rowwise() - V.row(v2), Eigen::VectorXd::Ones(V.rows()));
            num_v1_neighbors++;
        }
    }
    F = F_tmp.topRows(j);
    quadrics[v1] = Quadric();

    if (v1 < V.rows() - 1) {
        V.row(v1) = V.row(V.rows() - 1);
        quadrics[v1] = quadrics[V.rows() - 1];
        // Update the indices in the faces array
        for (int i = 0; i < F.rows(); i++) {
            for (int j = 0; j < 3; j++)
            {
                if (F(i, j) == V.rows() - 1)
                {
                    F(i, j) = v1;
                }
            }
        }
    }

    // Resize V
    if (V.rows() > 1)
        V.conservativeResize(V.rows() - 1, V.cols());
}

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

    // Initialize a vector to mark faces that should be removed
    std::vector<bool> remove_face(F.rows(), false);

    // Decimate the mesh until the desired number of vertices is reached
    while (V.rows() > target_num_vertices && !queue.empty())
    {
        std::cout << "Current Rows: " << V.rows() << " -> target: " << target_num_vertices << std::endl;

        // Get the edge with the lowest cost
        Edge edge = queue.top();
        queue.pop();
        // Perform the edge collapse
        perform_collapse(edge.v0 < edge.v1 ? edge.v0 : edge.v1, V, F, quadrics, queue);

        // Mark faces that involve the vertices that are being collapsed
        for (int i = 0; i < F.rows(); i++)
        {
            if (F(i, 0) == edge.v0 || F(i, 0) == edge.v1 || F(i, 1) == edge.v0 || F(i, 1) == edge.v1 || F(i, 2) == edge.v0 || F(i, 2) == edge.v1)
            {
                remove_face[i] = true;
            }
        }
    }

    // Remove the marked faces
    int j = 0;
    for (int i = 0; i < F.rows(); i++)
    {
        if (!remove_face[i])
        {
            F.row(j++) = F.row(i);
        }
    }
    F.conservativeResize(j, F.cols());
}
