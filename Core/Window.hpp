//
//  Window.hpp
//  Thesis
//
//  Created by Davide Paollilo on 06/04/23.
//

#ifndef Window_hpp
#define Window_hpp

#include <igl/opengl/glfw/Viewer.h>
#include <igl/opengl/glfw/imgui/ImGuiPlugin.h>

#include <iostream>
#include <stdio.h>

namespace Core {
    class Window
    {
        private:
            void initializeImGUI();
        
        public:
            GLFWwindow* window;
        
            Window();
        
            void update();
            void clear();
        
            bool shouldClose();
        
            ~Window();
    };
}

#endif /* Window_hpp */
