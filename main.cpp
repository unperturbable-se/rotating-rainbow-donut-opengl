#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <customWindow.h>
#include <glslFile.h>
#include <vertexObject.h>
#include <donut.h>
#include <frameLimiter.h>

using namespace std;
using namespace custom;

int main()
{

    int width = 800, height = 800;
    Window window(width, height, "Donut");
    glfwMakeContextCurrent(window); // all operations will be performed on this window
    glfwSwapInterval(1); //reduces the framerate to device default(enables vsync)

    // Load OpenGL functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))throw std::runtime_error("Failed to initialize GLAD");
        

    // Create shaders and shader program
    Shader vertexShader(GL_VERTEX_SHADER, "vertex_shader.glsl");
    Shader fragmentShader(GL_FRAGMENT_SHADER, "fragment_shader.glsl");
    ShaderProgram Program(vertexShader, fragmentShader);
    custom::Donut donut(Program);

    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    donut.generateTorus(64, 32, 0.5f, 0.2f, vertices, indices);
    
    VertexArray vao;
    VertexBuffer vbo(vertices.data(), vertices.size() * sizeof(float));
    IndexBuffer ebo(indices.data(), indices.size());
    
    vao.bind();
    vbo.bind();
    ebo.bind();
    
    vao.setAttribute(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);


    while (!glfwWindowShouldClose(window))
    {
        FrameLimiter(25); //20fps speed
        glfwPollEvents();
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);//sets GL_COLOR_BUFFER_BIT
        glClear(GL_COLOR_BUFFER_BIT); //clears the screen

        Program.use();

        float timeValue = glfwGetTime();
        donut.update(timeValue, width, height);
        donut.draw();
        
        
        vao.bind();
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        
        glfwSwapBuffers(window);

       
    }

    return 0;
}
