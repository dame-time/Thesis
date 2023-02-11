#include <Window.hpp>

int main() {
    System::Window* window = new System::Window(800, 600, "MyApplication", false);

    while (!glfwWindowShouldClose(window->window)) {
        window->clear();
        window->update();
    }
    
    return 0;
}