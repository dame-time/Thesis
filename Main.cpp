#include <igl/opengl/glfw/Viewer.h>
#include <igl/opengl/glfw/imgui/ImGuiPlugin.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>
#include <igl/opengl/glfw/imgui/ImGuizmoWidget.h>
#include <igl/triangle/triangulate.h>
#include <igl/readOBJ.h>

#include <Mesh.hpp>
#include <SphereMesh.hpp>

#include <iostream>

int main(int argc, char *argv[])
{

  // Plot the mesh
  igl::opengl::glfw::Viewer viewer;

  Core::Mesh mesh("/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Assets/Models/Cube.obj", viewer);
  SM::SphereMesh sm(mesh, viewer);
  // mesh.simplifyMesh(260);

  // sm.initialize();
  // mesh.addToScene();
  // sm.constructTest();

  sm.collapse(0, 1);
  sm.collapse(0, 1);
  sm.collapse(0, 1);
  sm.collapse(0, 1);
  sm.collapse(0, 1);
  sm.collapse(0, 1);
  sm.collapse(0, 1);
  sm.renderSpheresOnly();
  mesh.addToScene();

  // mesh.resize(10.0);

  // Set up the ImGui plugin
  igl::opengl::glfw::imgui::ImGuiPlugin imgui_plugin;
  viewer.plugins.push_back(&imgui_plugin);
  igl::opengl::glfw::imgui::ImGuiMenu menu;
  imgui_plugin.widgets.push_back(&menu);

  mesh.setMeshNotFilled();

  // mesh.test();

  viewer.launch();
}
