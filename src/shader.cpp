#include "Header_files/shader.h"

std::string get_file_contents(const char *filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (in)
    {
       // std::cout << "in herer";
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return (contents);
    }
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{

    std::string vertexShaderCode = get_file_contents(vertexFile);
    std::string fragmentShaderCode = get_file_contents(fragmentFile);
    const char *vertexShaderSource = vertexShaderCode.c_str();
    const char *fragmentShaderSource = fragmentShaderCode.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    compileError(vertexShader,"VERTEX");

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    compileError(fragmentShader,"FRAGMENT");


    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);

    glLinkProgram(ID);
    compileError(ID, "PROGRAM");
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
    glUseProgram(ID);
}

void Shader::Delete()
{
    glDeleteProgram(ID);
}

void compileError(unsigned int shader, std::string type)
{
    int hasCompiled;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
        if (!hasCompiled)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "SHADER COMPILATION ERROR for: " << type << "\n" << infoLog << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
        if (!hasCompiled)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "PROGRAM LINKING ERROR:\n" << infoLog << std::endl;
        }
    }
}

