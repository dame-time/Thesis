#include <igl/opengl/glfw/Viewer.h>
#include <igl/colormap.h>
#include <igl/opengl/glfw/imgui/ImGuiPlugin.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>
#include <igl/opengl/glfw/imgui/ImGuizmoWidget.h>
#include <igl/triangle/triangulate.h>
#include <igl/unproject_onto_mesh.h>
#include <igl/readOBJ.h>
#include <igl/file_dialog_open.h>

#include <Eigen/Dense>
#include <Eigen/Core>
#include <Eigen/SparseCore>

#include <Mesh.hpp>
#include <Math.hpp>
#include <SphereMesh.hpp>

#include "MathTest.hpp"
#include <Window.hpp>

#include <iostream>
#include <chrono>

void drawImGuiMenu(igl::opengl::glfw::imgui::ImGuiMenu& menu, igl::opengl::glfw::Viewer &viewer, SM::SphereMesh& sm, Core::Mesh& mesh, std::vector<int>& selectedSpheres)
{
    ImGui::SetNextWindowContentSize(ImVec2(700, 700));
    // Start a new ImGui window
    ImGui::Begin("My Custom Window");
    
    // Create a button
    if (ImGui::Button("Collapse Best BF Sphere Mesh Edge"))
    {
        sm.clearRenderedMeshes();
        sm.collapseSphereMesh();
        sm.renderSpheresOnly();
    }
    
    static int j = 0;
    ImGui::PushItemWidth(120);
    ImGui::InputInt("Number Of Spheres to Reach After Collapse", &j);
    ImGui::PopItemWidth();
    
    ImGui::SameLine();
    
    if (ImGui::Button("Render Sphere BF Mesh Vetices Collapsed"))
    {
        sm.clearRenderedMeshes();
        sm.collapseSphereMesh(j);
        sm.renderSpheresOnly();
    }
    
    static int k = 0;
    ImGui::PushItemWidth(120);
    ImGui::InputInt("Number Of Spheres to Collapse", &k);
    ImGui::PopItemWidth();
    
    ImGui::SameLine();
    
    if (ImGui::Button("Render BF Sphere Mesh Vetices"))
    {
        sm.clearRenderedMeshes();
        for (int i = 0; i < k; i++)
            sm.collapseSphereMesh();
        sm.renderSpheresOnly();
    }
    
    if (ImGui::Button("Select Best BF Sphere Mesh Edge"))
    {
        sm.renderSelectedSpheresOnly();
    }
    
    ImGui::Separator();
    
    if (ImGui::Button("Collapse Best Fast Sphere Mesh Edge"))
    {
        sm.clearRenderedMeshes();
        sm.collapseSphereMeshFast();
        sm.renderSpheresOnly();
    }
    
    static int f = 0;
    ImGui::PushItemWidth(120);
    ImGui::InputInt("Number Of Fast Spheres to Collapse", &f);
    ImGui::PopItemWidth();
    
    ImGui::SameLine();
    
    if (ImGui::Button("Render Fast Sphere Mesh Vetices"))
    {
        sm.clearRenderedMeshes();
        for (int i = 0; i < f; i++)
            sm.collapseSphereMeshFast();
        sm.renderSpheresOnly();
    }
    
    static int d = 0;
    ImGui::PushItemWidth(120);
    ImGui::InputInt("Number Of Fast Spheres to Reach After Collapse", &d);
    ImGui::PopItemWidth();
    
    ImGui::SameLine();
    
    if (ImGui::Button("Render Fast Sphere Mesh Vetices Collapsed"))
    {
        sm.clearRenderedMeshes();
        sm.collapseSphereMeshFast(d);
        sm.renderSpheresOnly();
    }
    
    if (ImGui::Button("Select Fast Best Sphere Mesh Edge"))
    {
        sm.renderFastSelectedSpheresOnly();
    }
    
    ImGui::Separator();
    
    static int n = 1;
    ImGui::PushItemWidth(120);
    ImGui::InputInt("Spheres Per Edge", &n);
    ImGui::PopItemWidth();
    
    Math::Math::clamp(1, 20, n);
    
    ImGui::SameLine();
    
    if (ImGui::Button("Render N Full Sphere Mesh"))
    {
        sm.clearRenderedMeshes();
        sm.renderWithNSpherePerEdge(n);
    }
    
    if (ImGui::Button("Render Full Sphere Mesh"))
    {
        sm.render();
    }
    
    if (ImGui::Button("Render Sphere Only Sphere Mesh"))
    {
        sm.renderSpheresOnly();
    }
    
    if (ImGui::Button("Render Connectivity of Sphere Mesh"))
    {
        sm.renderConnectivity();
    }
    
    if (ImGui::Button("Clear Connectivity of Sphere Mesh"))
    {
        sm.clearRenderedEdges();
    }
    
    if (ImGui::Button("Clear Sphere Mesh"))
    {
        sm.clearRenderedMeshes();
    }
    
    ImGui::Separator();
    
    if (ImGui::Button("Save Sphere Mesh To YAML"))
    {
        sm.saveYAML();
    }
    
    if (ImGui::Button("Save Sphere Mesh To TXT"))
    {
        sm.saveTXT();
    }
    
    ImGui::Separator();
    
    static double newSize = 1.0;
    ImGui::PushItemWidth(120);
    ImGui::InputDouble("New Spheres Size", &newSize);
    ImGui::PopItemWidth();
    
    ImGui::SameLine();
    
    if (ImGui::Button("Resize Selected Spheres"))
    {
        sm.clearRenderedMeshes();
        
        for (int i = 0; i < selectedSpheres.size(); i++)
        {
            sm.resizeSphereVertex(selectedSpheres[i], newSize);
        }
        
        sm.renderSpheresOnly();
    }
    
    if (selectedSpheres.size() > 0)
    {
        ImGui::SameLine();
        std::string selectedSpheresSize = "Current Sphere Sizes: ";
        for (int i = 0; i < selectedSpheres.size() - 1; i++)
        {
            selectedSpheresSize += std::to_string((float)sm.getSelectedVertexSphere(selectedSpheres[i]).radius) + ", ";
        }
        selectedSpheresSize += std::to_string((float)sm.getSelectedVertexSphere(selectedSpheres[selectedSpheres.size() - 1]).radius) + ".";
        ImGui::Text(selectedSpheresSize.c_str());
    }
    
    static Math::Vector3 newPos = Math::Vector3();
    float newPosArray[3] = { static_cast<float>(newPos[0]), static_cast<float>(newPos[1]), static_cast<float>(newPos[2])};
    ImGui::PushItemWidth(120);
    ImGui::InputFloat3("New Spheres Position", newPosArray);
    ImGui::PopItemWidth();
    
    newPos = Math::Vector3(newPosArray[0], newPosArray[1], newPosArray[2]);
    
    ImGui::SameLine();
    if (ImGui::Button("Translate Selected Spheres"))
    {
        sm.clearRenderedMeshes();
        
        for (int i = 0; i < selectedSpheres.size(); i++)
        {
            sm.translateSphereVertex(selectedSpheres[i], newPos);
        }
        
        sm.renderSpheresOnly();
    }
    
    if (selectedSpheres.size() > 0)
    {
        ImGui::SameLine();
        std::string selectedSpheresSize = "Current Sphere Sizes: ";
        for (int i = 0; i < selectedSpheres.size() - 1; i++)
        {
            selectedSpheresSize += "<" + std::to_string((float)sm.getSelectedVertexSphere(selectedSpheres[i]).center[0]) + ", " + std::to_string((float)sm.getSelectedVertexSphere(selectedSpheres[i]).center[1]) + ", " + std::to_string((float)sm.getSelectedVertexSphere(selectedSpheres[i]).center[2]) + ">" +"; ";
        }
        selectedSpheresSize += "<" + std::to_string((float)sm.getSelectedVertexSphere(selectedSpheres[selectedSpheres.size() - 1]).center[0]) + ", " + std::to_string((float)sm.getSelectedVertexSphere(selectedSpheres[selectedSpheres.size() - 1]).center[1]) + ", " + std::to_string((float)sm.getSelectedVertexSphere(selectedSpheres[selectedSpheres.size() - 1]).center[2]) + ">.";
        ImGui::Text(selectedSpheresSize.c_str());
    }
    
    ImGui::Separator();
    
    if (ImGui::Button("Show C0"))
    {
        Eigen::MatrixXd colors(mesh.v.rows(), 3);
        Eigen::MatrixXd K(mesh.v.rows(), 2);
        for (int i = 0; i < mesh.vertices.size(); i++)
        {
            K(i, 0) = mesh.vertices[i].curvature[0];
            K(i, 1) = mesh.vertices[i].curvature[1];
        }
        igl::colormap(igl::COLOR_MAP_TYPE_VIRIDIS, K.col(0), false, colors);
        viewer.data_list[mesh.ID].set_colors(colors);
    }
    
    if (ImGui::Button("Show C1"))
    {
        Eigen::MatrixXd colors(mesh.v.rows(), 3);
        Eigen::MatrixXd K(mesh.v.rows(), 2);
        for (int i = 0; i < mesh.vertices.size(); i++)
        {
            K(i, 0) = mesh.vertices[i].curvature[0];
            K(i, 1) = mesh.vertices[i].curvature[1];
        }
        igl::colormap(igl::COLOR_MAP_TYPE_VIRIDIS, K.col(1), false, colors);
        viewer.data_list[mesh.ID].set_colors(colors);
    }
    
    if (ImGui::Button("Show AVG Curvature"))
    {
        Eigen::MatrixXd colors(mesh.v.rows(), 3);
        Eigen::MatrixXd K(mesh.v.rows(), 1);
        for (int i = 0; i < mesh.vertices.size(); i++)
        {
            K(i, 0) = (mesh.vertices[i].curvature[0] + mesh.vertices[i].curvature[1]) * 0.5;
        }
        igl::colormap(igl::COLOR_MAP_TYPE_VIRIDIS, K.col(0), false, colors);
        viewer.data_list[mesh.ID].set_colors(colors);
    }
    
    ImGui::Separator();
    
    if (ImGui::Button("Load new Mesh from OBJ file"))
    {
        std::string fname = igl::file_dialog_open();
        
        viewer.data_list[mesh.ID].clear();
        mesh = Core::Mesh(fname, viewer);
        mesh.addToScene();
        sm.clear();
        sm.clearRenderedMeshes();
        auto tmp = SM::SphereMesh(mesh, viewer);
        sm = tmp;
        sm.renderSpheresOnly();
        std::cout << fname << std::endl;
    }
    
    ImGui::Separator();
    
    ImGui::Text("Click over a sphere in order to select it");
    ImGui::Text("Press 'C' to collapse the last two spheres selected");
    ImGui::Text("Press 'S' to visualize the vertices of the selected spheres");
    ImGui::Text("Press 'R' to reset the selection");
    ImGui::Text("Press 'E' to reset the Sphere Mesh to the original Sphere Mesh");
    ImGui::Text("Press 'F' to toggle the filling of the mesh");
    ImGui::Text("Press 'W' to toggle the wireframe of the mesh");
    ImGui::Text("Press 'Z' to zoom out of the mesh");
    ImGui::Text("Press 'X' to zoom in of the mesh");
    ImGui::Text("Press 'M' to increase zoom percentage");
    ImGui::Text("Press 'N' to increase zoom percentage");
    
    // End the ImGui window
    ImGui::End();
}

int selectSphere(igl::opengl::glfw::Viewer &viewer, Core::Mesh& mesh, SM::SphereMesh& sm)
{
    float x = viewer.current_mouse_x;
    float y = viewer.core().viewport(3) - viewer.current_mouse_y;
    Eigen::Vector2f click_pos(x, y);
    
    int picked_mesh = -1;
    int picked_face = -1;
    float min_distance = std::numeric_limits<float>::max();
    Eigen::Vector3f bc;
    
    // Iterate over all meshes to find the closest intersection
    for (size_t i = 0; i < viewer.data_list.size(); ++i) {
        int fid;
        Eigen::Vector3f _bc;
        
        if (i == mesh.ID)
            continue;
        
        if (igl::unproject_onto_mesh(click_pos, viewer.core().view, viewer.core().proj, viewer.core().viewport,
                                     viewer.data_list[i].V, viewer.data_list[i].F, fid, _bc)) {
            Eigen::Vector3f intersection = viewer.data_list[i].V.row(viewer.data_list[i].F(fid, 0)).cast<float>() * _bc(0) +
            viewer.data_list[i].V.row(viewer.data_list[i].F(fid, 1)).cast<float>() * _bc(1) +
            viewer.data_list[i].V.row(viewer.data_list[i].F(fid, 2)).cast<float>() * _bc(2);
            
            Eigen::Vector3f click_pos_3d;
            Eigen::Vector3f click_pos_3f(x, y, 0.0f);
            igl::unproject(click_pos_3f, viewer.core().view, viewer.core().proj, viewer.core().viewport,
                           click_pos_3d);
            float distance = (intersection - click_pos_3d).squaredNorm();
            
            if (distance < min_distance) {
                min_distance = distance;
                picked_mesh = i;
                picked_face = fid;
                bc = _bc;
            }
        }
    }
    
    return picked_mesh;
}

int main(int argc, char *argv[])
{
    static std::vector<int> pickedMeshes;
    igl::opengl::glfw::Viewer viewer;
    
    std::string path = "/Users/davidepaollilo/Workspaces/C++/Thesis/Assets/Models/camel-poses/camel-reference-600.obj";
//    std::string path = "/Users/davidepaollilo/Workspaces/C++/Thesis/Assets/Models/foot-500.obj";
//    std::string path = "/Users/davidepaollilo/Workspaces/C++/Thesis/Assets/Models/hand-1000.obj";
    
//      Core::Mesh mesh("/Users/davidepaollilo/Workspaces/C++/Thesis/Assets/Models/hand-1000.obj", viewer);
    Core::Mesh mesh(path, viewer);
    SM::SphereMesh sm(mesh, viewer);
    
    sm.renderSpheresOnly();
    mesh.addToScene();
    
    // Set up the ImGui plugin
    igl::opengl::glfw::imgui::ImGuiPlugin imgui_plugin;
    viewer.plugins.push_back(&imgui_plugin);
    igl::opengl::glfw::imgui::ImGuiMenu menu;
    imgui_plugin.widgets.push_back(&menu);
    
    // TODO: Setup a way to load a new mesh
    menu.callback_draw_custom_window = [&]()
    {
        drawImGuiMenu(menu, viewer, sm, mesh, pickedMeshes);
    };
    
    // Callback for when the mouse is clicked
    viewer.callback_mouse_down =
    [&](igl::opengl::glfw::Viewer &viewer, int button, int) -> bool {
        int pickedMesh = selectSphere(viewer, mesh, sm);
        if (pickedMesh >= 0)
        {
            int idx = -1;
            for (int i = 0; i < pickedMeshes.size(); i++)
            {
                if (pickedMeshes[i] == pickedMesh)
                {
                    idx = i;
                    break;
                }
            }
            
            if (idx == -1)
            {
                pickedMeshes.push_back(pickedMesh);
                sm.colorSelectedSphere(pickedMesh);
            }
            else
            {
                pickedMeshes.erase(pickedMeshes.begin() + idx);
                sm.resetColorOfSpheres();
                for (int i = 0; i < pickedMeshes.size(); i++)
                    sm.colorSelectedSphere(i);
            }
        }
        
        return false;
    };
    
    viewer.callback_key_down = [&](igl::opengl::glfw::Viewer &viewer, unsigned int key, int modifiers) -> bool {
        static bool status = false;
        if (key == GLFW_KEY_C) { // Replace 'X' with the key you want to use
            if (pickedMeshes.size() < 2)
                return false;
            
            if (pickedMeshes[pickedMeshes.size() - 1] == pickedMeshes[pickedMeshes.size() - 2])
                return false;
            
            sm.clearRenderedMeshes();
            sm.collapse(pickedMeshes[pickedMeshes.size() - 1], pickedMeshes[pickedMeshes.size() - 2]);
            sm.renderSpheresOnly();
            pickedMeshes.clear();
            
            return true;
        }
        
        if (key == GLFW_KEY_R)
        {
            pickedMeshes.clear();
            sm.resetColorOfSpheres();
            sm.clearRenderedSphereVertices();
            status = false;
            return true;
        }
        
        if (key == GLFW_KEY_E)
        {
            pickedMeshes.clear();
            sm.clearRenderedMeshes();
            sm.reset();
            sm.renderSpheresOnly();
            status = false;
            return true;
        }
        
        if (key == GLFW_KEY_S && pickedMeshes.size() > 0)
        {
            if (!status)
                for (int i = 0; i < pickedMeshes.size(); i++)
                    sm.renderSphereVertices(pickedMeshes[i]);
            else
                sm.clearRenderedSphereVertices();
            
            status = !status;
            return true;
        }
        
        static bool isMeshFilled = true;
        if (key == GLFW_KEY_F)
        {
            if (isMeshFilled)
                viewer.data_list[mesh.ID].show_faces = false;
            else
                viewer.data_list[mesh.ID].show_faces = true;
            
            isMeshFilled = !isMeshFilled;
        }
        
        static bool isMeshWireframe = true;
        if (key == GLFW_KEY_W)
        {
            if (isMeshWireframe)
                viewer.data_list[mesh.ID].show_lines = false;
            else
                viewer.data_list[mesh.ID].show_lines = true;
            
            isMeshWireframe = !isMeshWireframe;
        }
        
        static double zoomPower = 0.1;
        if (key == GLFW_KEY_Z)
            viewer.core().camera_zoom -= zoomPower;
        
        if (key == GLFW_KEY_X)
            viewer.core().camera_zoom += zoomPower;
        
        if (key == GLFW_KEY_M)
            zoomPower += 0.1;
        
        if (key == GLFW_KEY_N)
            zoomPower -= 0.1;
        
        return false;
    };
    
    viewer.launch();
}
