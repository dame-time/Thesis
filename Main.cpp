#include <igl/opengl/glfw/Viewer.h>
#include <igl/opengl/glfw/imgui/ImGuiPlugin.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>
#include <igl/opengl/glfw/imgui/ImGuizmoWidget.h>
#include <igl/triangle/triangulate.h>
#include <igl/readOBJ.h>

#include <Mesh.hpp>
#include <Math.hpp>
#include <SphereMesh.hpp>

#include <iostream>

void drawImGuiMenu(igl::opengl::glfw::imgui::ImGuiMenu& menu, SM::SphereMesh& sm)
{
    ImGui::SetNextWindowContentSize(ImVec2(500, 300));
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

    // End the ImGui window
    ImGui::End();
}

int main(int argc, char *argv[])
{

  // Plot the mesh
  igl::opengl::glfw::Viewer viewer;

  Core::Mesh mesh("/Users/davidepaollilo/Workspaces/C++/Thesis/Assets/Models/hand-1000.obj", viewer);
//  Core::Mesh mesh("/Users/davidepaollilo/Workspaces/C++/Thesis/Assets/Models/camel-poses/camel-reference-4040.obj", viewer);
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

  mesh.setMeshNotFilled();

  // mesh.test();

  viewer.launch();
}
