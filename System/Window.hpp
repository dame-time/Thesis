#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace System
{
    struct Screen
    {
        int width;
        int height;
    };

    class Window
    {
        public:
            static Screen screen;
            static GLFWwindow *window;

            GLFWwindow *test;

            Window(std::string name = "MyApplication", bool cursorDisabled = false);
            Window(const int &width, const int &height, std::string name = "MyApplication", bool cursorDisabled = false);

            void clear();
            void update();

            ~Window();

        private:
            void setWindowIcon();
            void initializeImGUI();
    };
} // namespace System

#endif // __WINDOW_H__