#include <igl/opengl/glfw/Viewer.h>
#include <igl/opengl/glfw/imgui/ImGuiPlugin.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>
#include <igl/opengl/glfw/imgui/ImGuizmoWidget.h>
#include <igl/triangle/triangulate.h>
#include <igl/readOBJ.h>

#include <Mesh.hpp>
#include <SphereMesh.hpp>

#include <iostream>

void myFunction()
{
    std::cout << "Hi" << std::endl;
}

void drawImGuiMenu(igl::opengl::glfw::imgui::ImGuiMenu& menu, SM::SphereMesh& sm)
{
    // Start a new ImGui window
    ImGui::Begin("My Custom Window");

    // Create a button
    if (ImGui::Button("Collapse Best Sphere Mesh Edge"))
    {
        sm.clearRenderedMeshes();
        sm.collapseSphereMesh();
        sm.renderSpheresOnly();
    }
    
    if (ImGui::Button("Select Best Sphere Mesh Edge"))
    {
        sm.renderSelectedSpheresOnly();
    }
    
    if (ImGui::Button("Render Full Sphere Mesh"))
    {
        sm.render();
    }

    // End the ImGui window
    ImGui::End();
}

int main(int argc, char *argv[])
{

  // Plot the mesh
  igl::opengl::glfw::Viewer viewer;

//  Core::Mesh mesh("/Users/davidepaollilo/Workspaces/C++/Thesis/Assets/Models/TrafficCone.obj", viewer);
  Core::Mesh mesh("/Users/davidepaollilo/Workspaces/C++/Thesis/Assets/Models/camel-poses/camel-reference-600.obj", viewer);
  SM::SphereMesh sm(mesh, viewer);
  // mesh.simplifyMesh(260);

  // sm.initialize();
  // mesh.addToScene();
  // sm.constructTest();
    sm.collapseSphereMesh(280);

//  sm.collapse(0, 1);
//  sm.collapse(0, 1);
//  sm.collapse(0, 1);
//  sm.collapse(0, 1);
//  sm.collapse(0, 1);
//  sm.collapse(0, 1);
//  sm.collapse(0, 1);
//  sm.collapse(0, 1);
  sm.render();
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
