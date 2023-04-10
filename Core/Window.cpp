//
//  Window.cpp
//  Thesis
//
//  Created by Davide Paollilo on 06/04/23.
//

#include "Window.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Core
{

    Window::Window()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

        // glfw window creation
        // --------------------
        window = glfwCreateWindow(800, 800, "Initial Window", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
//        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }
        
        initializeImGUI();

        // Enable depth test
        glEnable(GL_DEPTH_TEST);
    }

    void Window::initializeImGUI()
    {
        IMGUI_CHECKVERSION();

        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410 core");
        ImGui::StyleColorsDark();
    }

    void Window::update()
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Process here the data
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(this->window, true);
        
        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }

    void Window::clear()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    bool Window::shouldClose()
    {
        return glfwWindowShouldClose(this->window);
    }

    Window::~Window()
    {
//        ImGui_ImplOpenGL3_Shutdown();
//        ImGui_ImplGlfw_Shutdown();
//        ImGui::DestroyContext();

        glfwTerminate();
    }
}
