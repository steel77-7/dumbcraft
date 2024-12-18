#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <iostream>
#include <glad/glad.h>
#include <fstream>
#include <string.h>

class Shader
{
    public:
    unsigned int ID;
    Shader(const char *vertexSource, const char *fragmentSource);

    void Delete();
    void Activate();
};

void compileError(unsigned int shader, std::string type);

#endif