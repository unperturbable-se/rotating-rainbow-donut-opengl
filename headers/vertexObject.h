#pragma once
#include <glad/glad.h>

namespace custom
{
   class IndexBuffer
    {
        unsigned int EBO;

    public:
        IndexBuffer(unsigned int* indices, unsigned int count)
        {
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
        }

        void bind()
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        }

        void unbind()
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        ~IndexBuffer()
        {
            glDeleteBuffers(1, &EBO);
        }

        operator GLuint() const { return EBO; }
    };
    
   class VertexBuffer
   {
    unsigned int VBO;
       public:
       VertexBuffer(float* vertices,unsigned int size)
       {
           glGenBuffers(1,&VBO);
           glBindBuffer(GL_ARRAY_BUFFER,VBO);
           glBufferData(GL_ARRAY_BUFFER,size,vertices,GL_STATIC_DRAW);
       }
       void bind()
       {
           glBindBuffer(GL_ARRAY_BUFFER,VBO);
       }
   
       void unbind()
       {
           glBindBuffer(GL_ARRAY_BUFFER,0);
       }
   
       ~VertexBuffer()
       {
           glDeleteBuffers(1,&VBO);
       }
       operator GLuint()const {return VBO;}
   };
   
   class VertexArray
   {
    unsigned int VAO;
       public:
       VertexArray()
       {
           glGenVertexArrays(1,&VAO);
           glBindVertexArray(VAO);
       }
       void bind()
       {
           glBindVertexArray(VAO);
       }
       void unbind()
       {
           glBindVertexArray(0);
       }
       ~VertexArray()
       {
           glDeleteVertexArrays(1,&VAO);
       }
       operator GLuint()const {return VAO;}
       void setAttribute(unsigned int index,int size,GLenum type,GLboolean normalized,int stride,const void* pointer)
       {
           glVertexAttribPointer(index,size,type,normalized,stride,pointer);
           glEnableVertexAttribArray(index);
       }
   };
};