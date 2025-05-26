#pragma once
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace custom
{
    struct Window 
    {
     protected:
     GLFWwindow* window;
     public:
     Window(int width,int height,std::string title)
           {
              try
              {
                if(!glfwInit())throw std::runtime_error("GLFW init failed");
                window = glfwCreateWindow(width,height,title.c_str(),NULL,NULL);
                if(!window)throw std::runtime_error("GLFW window creation failed");
              }
              catch(const std::exception& e)
              {
                std::cerr << e.what() << '\n';
                return;
              }
           }
     ~Window(){glfwDestroyWindow(window);}  
     operator GLFWwindow*()const {return window;}  
    };
}