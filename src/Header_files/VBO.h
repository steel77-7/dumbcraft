#ifndef VBO_CLASS
#define VBO_CLASS
#include <glad/glad.h>
#include <iostream>
class VBO
{
unsigned int ID;
public:
    VBO(GLfloat* vertex,GLsizeiptr size);
    void Delete();
    void Bind();
    void Unbind();
};

#endif