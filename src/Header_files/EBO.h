#ifndef EBO_CLASS
#define EBO_CLASS
#include <glad/glad.h>
class EBO
{
    unsigned int ID;

public:
    EBO(GLuint *indices, GLsizeiptr size);
    void Bind();
    void Unbind();
    void Delete();
};

#endif