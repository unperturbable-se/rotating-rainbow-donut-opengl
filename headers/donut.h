#pragma once

#include <vector>
#include <cmath>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glslFile.h>
#include <vertexObject.h>

namespace custom {

    class Donut {
    private:
        VertexArray vao;
        VertexBuffer* vbo;
        IndexBuffer* ebo;
        ShaderProgram& shader;
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
    public:    

     inline void generateTorus(
            unsigned int segments,
            unsigned int rings,
            float majorRadius,
            float minorRadius,
            std::vector<float>& vertices,
            std::vector<unsigned int>& indices
        );

        Donut(ShaderProgram& shaderProgram) : shader(shaderProgram)
        {
            generateTorus(64, 32, 0.5f, 0.2f, vertices, indices);

            vbo = new VertexBuffer(vertices.data(), vertices.size() * sizeof(float));
            ebo = new IndexBuffer(indices.data(), indices.size());

            vao.bind();
            vbo->bind();
            ebo->bind();
            vao.setAttribute(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        }

        ~Donut()
        {
            delete vbo;
            delete ebo;
        }

        void update(float time, int width, int height)
        {
            shader.use();

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::rotate(model, time * 0.7f, glm::vec3(1, 0, 0));
            model = glm::rotate(model, time * 0.9f, glm::vec3(0, 1, 0));
            model = glm::rotate(model, time * 1.1f, glm::vec3(0, 0, 1));
            glUniformMatrix4fv(glGetUniformLocation(shader, "uModel"), 1, GL_FALSE, glm::value_ptr(model));

            glm::mat4 projection = glm::perspective(glm::radians(45.0f), width / (float)height, 0.1f, 100.0f);
            glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
            glUniformMatrix4fv(glGetUniformLocation(shader, "uProjection"), 1, GL_FALSE, glm::value_ptr(projection));
            glUniformMatrix4fv(glGetUniformLocation(shader, "uView"), 1, GL_FALSE, glm::value_ptr(view));

            glUniform1f(glGetUniformLocation(shader, "uTime"), time);
        }

        void draw()
        {
            vao.bind();
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        }
    };

    // Must be inline to prevent multiple definition errors
    inline void Donut::generateTorus(
        unsigned int segments,
        unsigned int rings,
        float majorRadius,
        float minorRadius,
        std::vector<float>& vertices,
        std::vector<unsigned int>& indices)
    {
        vertices.clear();
        indices.clear();

        const float PI = 3.14159265359f;

        for (unsigned int i = 0; i <= segments; ++i) {
            float theta = 2.0f * PI * i / segments;
            float cosTheta = cos(theta);
            float sinTheta = sin(theta);

            for (unsigned int j = 0; j <= rings; ++j) {
                float phi = 2.0f * PI * j / rings;
                float cosPhi = cos(phi);
                float sinPhi = sin(phi);

                float x = (majorRadius + minorRadius * cosPhi) * cosTheta;
                float y = (majorRadius + minorRadius * cosPhi) * sinTheta;
                float z = minorRadius * sinPhi;

                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);
            }
        }

        for (unsigned int i = 0; i < segments; ++i) {
            for (unsigned int j = 0; j < rings; ++j) {
                unsigned int first = i * (rings + 1) + j;
                unsigned int second = first + rings + 1;

                indices.push_back(first);
                indices.push_back(second);
                indices.push_back(first + 1);

                indices.push_back(second);
                indices.push_back(second + 1);
                indices.push_back(first + 1);
            }
        }
    }

} // namespace custom
