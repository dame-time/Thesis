#include <Window.hpp>
#include <Shader.hpp>

int main() {
    System::Window* window = new System::Window(800, 600, "MyApplication", false);

    System::Shader *testShader = new System::Shader("./Shaders/test.vert", "./Shaders/test.frag");
    testShader->use();

    while (!glfwWindowShouldClose(window->window)) {
        window->clear();
        window->update();
    }
    
    return 0;
}