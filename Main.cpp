#include <igl/opengl/glfw/Viewer.h>
#include <igl/opengl/glfw/imgui/ImGuiPlugin.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>
#include <igl/opengl/glfw/imgui/ImGuizmoWidget.h>
#include <igl/triangle/triangulate.h>
#include <igl/unproject_onto_mesh.h>
#include <igl/readOBJ.h>

#include <Eigen/Dense>
#include <Eigen/Core>
#include <Eigen/SparseCore>

#include <Mesh.hpp>
#include <Math.hpp>
#include <SphereMesh.hpp>

#include <iostream>

void drawImGuiMenu(igl::opengl::glfw::imgui::ImGuiMenu& menu, SM::SphereMesh& sm)
{
    ImGui::SetNextWindowContentSize(ImVec2(500, 500));
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
    
    Math::Math::clamp(0, sm.maxNumberOfCollapses(), j);
    
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
    
    Math::Math::clamp(0, sm.maxNumberOfCollapses(), k);
    
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
    
    Math::Math::clamp(0, sm.maxNumberOfCollapses(), f);
    
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
    
    Math::Math::clamp(0, sm.maxNumberOfCollapses(), d);
    
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
    
    if (ImGui::Button("Clear All Sphere Vertices"))
    {
        sm.clearRenderedSphereVertices();
    }
    
    ImGui::Separator();
    
    if (ImGui::Button("Save Sphere Mesh To YAML"))
    {
        sm.saveYAML();
    }

    // End the ImGui window
    ImGui::End();
}

int main(int argc, char *argv[])
{
  igl::opengl::glfw::Viewer viewer;

//  Core::Mesh mesh("/Users/davidepaollilo/Workspaces/C++/Thesis/Assets/Models/hand-1000.obj", viewer);
  Core::Mesh mesh("/Users/davidepaollilo/Workspaces/C++/Thesis/Assets/Models/camel-poses/camel-reference-600.obj", viewer);
  SM::SphereMesh sm(mesh, viewer);

  sm.renderSpheresOnly();
  mesh.addToScene();

  // mesh.resize(10.0);

  // Set up the ImGui plugin
  igl::opengl::glfw::imgui::ImGuiPlugin imgui_plugin;
  viewer.plugins.push_back(&imgui_plugin);
  igl::opengl::glfw::imgui::ImGuiMenu menu;
  imgui_plugin.widgets.push_back(&menu);
    
  menu.callback_draw_custom_window = [&]()
  {
      drawImGuiMenu(menu, sm);
  };

    // Callback for when the mouse is clicked
    viewer.callback_mouse_down =
        [&](igl::opengl::glfw::Viewer &viewer, int, int) -> bool {
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

            if (picked_mesh >= 0) {
                std::cout << "Picked mesh index: " << picked_mesh << std::endl;
                sm.renderSphereVertices(picked_mesh);
            }

            return false;
        };
    
  mesh.setMeshNotFilled();

  viewer.launch();
}
