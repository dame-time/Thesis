#include "../Window.hpp"

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <ImGuizmo.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace System {
    GLFWwindow *Window::window;
    Screen Window::screen;

    // Improve the implementation 
    Window::Window(std::string name, bool cursorDisabled) {   
        screen.width = 800;
        screen.height = 600;

        if (!glfwInit())
            std::cerr << "Failed to initialize GLFW" << std::endl;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

        this->window = glfwCreateWindow(screen.width, screen.height, name.c_str(), NULL, NULL);

        if (window == NULL) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }

        auto frameBufferCallback = [](GLFWwindow *window, int w, int h) {
            Window::screen.width = w;
            Window::screen.height = h;

            if (Window::screen.width > Window::screen.height)
                glViewport(0, (Window::screen.height - Window::screen.width) / 2, Window::screen.width, Window::screen.width);
            else
                glViewport((Window::screen.width - Window::screen.height) / 2, 0, Window::screen.height, Window::screen.height);

            if (w < h) {
                Window::screen.width = h;
                Window::screen.height = h;
            }
            else {
                Window::screen.width = w;
                Window::screen.height = w;
            }
        };

        glfwMakeContextCurrent(this->window);
        glfwSetFramebufferSizeCallback(this->window, frameBufferCallback);

        if (cursorDisabled)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        else
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            std::cerr << "Failed to initialize GLAD" << std::endl;

        // Enable depth test
        glEnable(GL_DEPTH_TEST);

        initializeImGUI();

        setWindowIcon();
    }

    Window::Window(const int &width, const int &height, std::string name, bool cursorDisabled)
    {
        screen.width = width;
        screen.height = height;

        if (!glfwInit())
            std::cerr << "Failed to initialize GLFW" << std::endl;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

        this->window = glfwCreateWindow(screen.width, screen.height, name.c_str(), NULL, NULL);

        if (window == NULL)
        {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }

        auto frameBufferCallback = [](GLFWwindow *window, int w, int h)
        {
            Window::screen.width = w;
            Window::screen.height = h;

            if (Window::screen.width > Window::screen.height)
                glViewport(0, (Window::screen.height - Window::screen.width) / 2, Window::screen.width, Window::screen.width);
            else
                glViewport((Window::screen.width - Window::screen.height) / 2, 0, Window::screen.height, Window::screen.height);

            if (w < h)
            {
                Window::screen.width = h;
                Window::screen.height = h;
            }
            else
            {
                Window::screen.width = w;
                Window::screen.height = w;
            }
        };

        glfwMakeContextCurrent(this->window);
        glfwSetFramebufferSizeCallback(this->window, frameBufferCallback);

        if (cursorDisabled)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        else
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            std::cerr << "Failed to initialize GLAD" << std::endl;

        // Enable depth test
        glEnable(GL_DEPTH_TEST);

        initializeImGUI();

        setWindowIcon();
    }

    void Window::initializeImGUI() {
        IMGUI_CHECKVERSION();

        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        float fontSize = 15;
        io.Fonts->AddFontFromFileTTF("./Assets/Fonts/Roboto-Regular.ttf", fontSize);
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410 core");
        ImGui::StyleColorsDark();

        // const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        // sceneFrameBuffer = new Buffers::FrameBuffer(mode->width * 2, mode->height * 2, true);

        // Input::keyboard = new Keyboard();
    }

    void Window::clear()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGuizmo::BeginFrame();

        // sceneFrameBuffer->bind();
    }

    void Window::update()
    {
        // sceneFrameBuffer->blit();

        // gameFrameBuffer->copyAnotherFrameBuffer(this->sceneFrameBuffer->ID);

        // ImGui::ShowDemoWindow();
        // dockspace->createDockspace();
        // Odysseus::SceneManager::activeScene->sceneEditor->onEditorUpdate();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(this->window, true);

        // FIXME: This is a temporary solution remove this when implement frame buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }

    void Window::setWindowIcon() {
        GLFWimage icons[1];
        int w, h, channels;
        stbi_uc *img = stbi_load("./Resources/mesh.png", &w, &h, &channels, 0);
        icons->height = h;
        icons->width = w;
        icons[0].pixels = img;
        glfwSetWindowIcon(this->window, 1, icons);
    }

    Window::~Window() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwTerminate();
    }
}