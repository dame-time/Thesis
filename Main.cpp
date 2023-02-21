#include <igl/opengl/glfw/Viewer.h>
#include <igl/opengl/glfw/imgui/ImGuiPlugin.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>
#include <igl/opengl/glfw/imgui/ImGuizmoWidget.h>
#include <igl/triangle/triangulate.h>
#include <igl/readOBJ.h>

#include <Mesh.hpp>

#include <iostream>

int main(int argc, char *argv[])
{

  // Plot the mesh
  igl::opengl::glfw::Viewer viewer;

  Core::Mesh mesh("/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Assets/Models/Cube.obj", viewer);
  mesh.addToScene();

  // mesh.resize(10.0);
  mesh.test();

  // Set up the ImGui plugin
  igl::opengl::glfw::imgui::ImGuiPlugin imgui_plugin;
  viewer.plugins.push_back(&imgui_plugin);
  igl::opengl::glfw::imgui::ImGuiMenu menu;
  imgui_plugin.widgets.push_back(&menu);

  // // Iterate over all meshes in the viewer
  // for (size_t i = 0; i < viewer.data_list.size(); i++)
  // {
  //   // Initialize ImGuizmo at mesh centroid
  //   const Eigen::MatrixXd &V = viewer.data_list[i].V;
  //   if (V.size() == 0)
  //     continue;

  //   igl::opengl::glfw::imgui::ImGuizmoWidget* gizmo = new igl::opengl::glfw::imgui::ImGuizmoWidget();
  //   // gizmo->visible = false;
  //   imgui_plugin.widgets.push_back(gizmo);

  //   gizmo->T.block(0, 3, 3, 1) =
  //       0.5 * (V.colwise().maxCoeff() + V.colwise().minCoeff())
  //                 .transpose()
  //                 .cast<float>();

  //   // Update can be applied relative to this remembered initial transform
  //   const Eigen::Matrix4f T0 = gizmo->T;

  //   // TODO: Fix this strange behaviour 
  //   // Attach callback to apply ImGuizmo's transform to mesh
  //   gizmo->callback = [&](const Eigen::Matrix4f &T)
  //   {
  //     igl::opengl::ViewerData *data = new igl::opengl::ViewerData();
  //     data = &viewer.data();
  //     const Eigen::Matrix4d TT = (T * T0.inverse()).cast<double>().transpose();
  //     data->set_vertices((data->V.rowwise().homogeneous() * TT).rowwise().hnormalized());
  //     data->compute_normals();
  //   };

  //   // Set up Maya-style keyboard shortcuts for operation
  //   viewer.callback_key_pressed = [&](decltype(viewer) &, unsigned int key,
  //                                     int mod)
  //   {
  //     switch (key)
  //     {
  //     case ' ':
  //       gizmo->visible = !gizmo->visible;
  //       return true;
  //     case 'W':
  //     case 'w':
  //       gizmo->operation = ImGuizmo::TRANSLATE;
  //       return true;
  //     case 'E':
  //     case 'e':
  //       gizmo->operation = ImGuizmo::ROTATE;
  //       return true;
  //     case 'R':
  //     case 'r':
  //       gizmo->operation = ImGuizmo::SCALE;
  //       return true;
  //     }
  //     return false;
  //   };
  // }

  viewer.launch();
}
