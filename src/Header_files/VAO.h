#ifndef VAO_CLASS
#define VAO_CLASS
#include "VBO.h"

class VAO
{

    unsigned int ID;

public:
    VAO();
    void LinkVBO(VBO VBO, unsigned int layout, unsigned int numComponents, GLenum type, GLsizeiptr stride, void *offset);
    void Unbind();
    void Bind();
    void Delete();
};

#endif