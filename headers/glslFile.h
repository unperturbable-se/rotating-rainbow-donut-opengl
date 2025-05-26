#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace custom
{
    class GlslFile
    {
     protected:
     std::string fileContents;
     public:
     GlslFile(std::string filename)
     {
       std::ifstream file("glsl/" + filename);

        try
        {
            if (!file.is_open())throw std::runtime_error("Failed to open shader file: glsl/" + filename);
            std::stringstream buffer;
            buffer << file.rdbuf();
            fileContents = buffer.str();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }   
     }
     operator const char*()const {return fileContents.c_str();}
    };

    class Shader: public GlslFile
    {
        unsigned int shaderID;
        GLenum type;
        public:
        Shader(GLenum type,std::string filename):GlslFile(filename),type(type)
        {
            const char* source=fileContents.c_str();
            shaderID = glCreateShader(type);
            glShaderSource(shaderID,1,&source,NULL);
            std::cout << "=== Compiling Shader: " << filename << " ===\n";
            glCompileShader(shaderID);

            try
            {
                int success;
                char infoLog[512];
                glGetShaderiv(shaderID,GL_COMPILE_STATUS,&success);
                if(!success)
                {
                    glGetShaderInfoLog(shaderID,512,NULL,infoLog);
                    throw std::runtime_error("Shader compilation failed\n"+std::string(infoLog));
                }
                std::cout<<"Shader compiled successfully\n";
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            
        }
        operator GLuint()const {return shaderID;}
        ~Shader(){glDeleteShader(shaderID);} 
    };

    class ShaderProgram
    {
        unsigned int shaderProgramID;
        public:
        ShaderProgram(const Shader& vertexShader,const Shader& fragmentShader)
        {
            shaderProgramID = glCreateProgram();
            glAttachShader(shaderProgramID,(GLuint)vertexShader);
            glAttachShader(shaderProgramID,(GLuint)fragmentShader);
            glLinkProgram(shaderProgramID);

            try
            {
                int success;
                char infoLog[512];
                glGetProgramiv(shaderProgramID,GL_LINK_STATUS,&success);
                if(!success)
                {
                    glGetProgramInfoLog(shaderProgramID,512,NULL,infoLog);
                    throw std::runtime_error("Shader program linking failed\n"+std::string(infoLog));
                }
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            
        }
        void use()const {glUseProgram(shaderProgramID);}
        ~ShaderProgram(){glDeleteProgram(shaderProgramID);}
        operator GLuint()const {return shaderProgramID;}
    };
}