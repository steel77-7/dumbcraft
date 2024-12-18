#ifndef TEXTURE_CLASS
#define TEXTURE_CLASS
#include <glad/glad.h>
#include "stb_image.h"
#include "shader.h"

class Texture
{
    public:
    unsigned int ID;
    GLenum type;
    Texture(const char *image, GLenum textype, GLenum Slot, GLenum format, GLenum pixelType);
    void texUnit(Shader &shader, const char *uniform, GLuint unit);
    void Bind();
    void Unbind();
    void Delete();
};
#endif