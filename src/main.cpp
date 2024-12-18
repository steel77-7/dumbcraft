#include <iostream>
#include <glad/glad.h>
#include <math.h>
#include "glad.c"
#include <GLFW/glfw3.h>
#include "shader.cpp"
#include "VBO.cpp"
#include "VAO.cpp"
#include "EBO.cpp"
#include "Header_files/glm/glm.hpp"
#include "Header_files/glm/gtc/matrix_transform.hpp"
#include "Header_files/glm/gtc/type_ptr.hpp"
#include "Texture.cpp"
#include "Camera.cpp"
using namespace std;
const char *vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
}
)";

// Fragment Shader source
const char *fragmentShaderSource = R"(
#version 330 core
in vec3 ourColor;
out vec4 FragColor;

void main()
{
    FragColor = vec4(ourColor, 1.0);
}
)";

const char *vertexPath = "/home/steel/visual_studio/c++_projects/opengl_projects/renderer/src/resources/shaders/default.vert";
const char *fragPath = "/home/steel/visual_studio/c++_projects/opengl_projects/renderer/src/resources/shaders/default.frag";
GLfloat vertex[] = {
    //     COORDINATES         /    COLORS         /   TEXCOORDS
    // Back face
    -0.25f, -0.25f, -0.25f,  1.0f, 0.0f, 0.0f,    0.0f, 0.0f, // Bottom-left
     0.25f, -0.25f, -0.25f,  0.0f, 1.0f, 0.0f,    1.0f, 0.0f, // Bottom-right
     0.25f,  0.25f, -0.25f,  0.0f, 0.0f, 1.0f,    1.0f, 1.0f, // Top-right
    -0.25f,  0.25f, -0.25f,  1.0f, 1.0f, 0.0f,    0.0f, 1.0f, // Top-left

    // Front face
    -0.25f, -0.25f,  0.25f,  0.0f, 1.0f, 1.0f,    0.0f, 0.0f, // Bottom-left
     0.25f, -0.25f,  0.25f,  1.0f, 0.0f, 1.0f,    1.0f, 0.0f, // Bottom-right
     0.25f,  0.25f,  0.25f,  0.5f, 0.5f, 0.5f,    1.0f, 1.0f, // Top-right
    -0.25f,  0.25f,  0.25f,  1.0f, 0.5f, 0.0f,    0.0f, 1.0f, // Top-left

    // Left face
    -0.25f, -0.25f, -0.25f,  1.0f, 0.0f, 0.0f,    0.0f, 0.0f, // Bottom-left
    -0.25f,  0.25f, -0.25f,  1.0f, 1.0f, 0.0f,    1.0f, 0.0f, // Top-left
    -0.25f,  0.25f,  0.25f,  1.0f, 0.5f, 0.0f,    1.0f, 1.0f, // Top-right
    -0.25f, -0.25f,  0.25f,  0.0f, 1.0f, 1.0f,    0.0f, 1.0f, // Bottom-right

    // Right face
     0.25f, -0.25f, -0.25f,  0.0f, 1.0f, 0.0f,    0.0f, 0.0f, // Bottom-left
     0.25f,  0.25f, -0.25f,  0.0f, 0.0f, 1.0f,    1.0f, 0.0f, // Top-left
     0.25f,  0.25f,  0.25f,  0.5f, 0.5f, 0.5f,    1.0f, 1.0f, // Top-right
     0.25f, -0.25f,  0.25f,  1.0f, 0.0f, 1.0f,    0.0f, 1.0f, // Bottom-right

    // Bottom face
    -0.25f, -0.25f, -0.25f,  1.0f, 0.0f, 0.0f,    0.0f, 0.0f, // Bottom-left
     0.25f, -0.25f, -0.25f,  0.0f, 1.0f, 0.0f,    1.0f, 0.0f, // Bottom-right
     0.25f, -0.25f,  0.25f,  1.0f, 0.0f, 1.0f,    1.0f, 1.0f, // Top-right
    -0.25f, -0.25f,  0.25f,  0.0f, 1.0f, 1.0f,    0.0f, 1.0f, // Top-left

    // Top face
    -0.25f,  0.25f, -0.25f,  1.0f, 1.0f, 0.0f,    0.0f, 0.0f, // Bottom-left
     0.25f,  0.25f, -0.25f,  0.0f, 0.0f, 1.0f,    1.0f, 0.0f, // Bottom-right
     0.25f,  0.25f,  0.25f,  0.5f, 0.5f, 0.5f,    1.0f, 1.0f, // Top-right
    -0.25f,  0.25f,  0.25f,  1.0f, 0.5f, 0.0f,    0.0f, 1.0f  // Top-left
};


// Indices for vertices order
GLuint indices[] = {
    // Back face
    0, 1, 2,
    0, 2, 3,
    // Front face
    4, 5, 6,
    4, 6, 7,
    // Left face
    0, 4, 7,
    0, 7, 3,
    // Right face
    1, 5, 6,
    1, 6, 2,
    // Bottom face
    0, 1, 5,
    0, 5, 4,
    // Top face
    3, 2, 6,
    3, 6, 7};

int width = 800;
int height = 800;
int main(void)
{
    // window object
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 800, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // start everything here
    gladLoadGL();
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        // return -1;
    }
    // GLuint VBO;
    VBO vbo(vertex, sizeof(vertex));
    VAO vao;
    vao.Bind();
    EBO ebo(indices, sizeof(indices));
    ebo.Bind();

    vao.LinkVBO(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *)0);
    vao.LinkVBO(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    vao.LinkVBO(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void *)(6 * sizeof(float)));

    // glCreateShader(shaderprogram);

    // vbo.Unbind();
    Shader shaderprogram(vertexPath, fragPath);
    /* Loop until the user closes the window */
   // GLuint uniID = glGetUniformLocation(shaderprogram.ID, "scale");
   // float rotation = 0.0f;
   // double prevtime = glfwGetTime();
    glEnable(GL_DEPTH_TEST);

    Texture texture("/home/steel/visual_studio/c++_projects/opengl_projects/renderer/src/texture_wood.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    texture.texUnit(shaderprogram, "tex0", 0);
    texture.Unbind();

    float rotation = 0.0f; 
    double prevtime = glfwGetTime();

        Camera camera(width,height, glm::vec3  (0.0f,0.0f,2.0f));


    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.0f, 0.7f, 1.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderprogram.Activate();
        vao.Bind();
        texture.Bind();
        camera.move(45.0f,0.1f,100.0f, shaderprogram, "camMatrix");
        camera.inputs(window);
        // glUniform1f(uniID, 0.4);s
        // glUseProgram(shaderprogram);
        // glDrawElements(GL_TRIANGLES, sizeof(vertex) / sizeof(vertex[0]), GL_UNSIGNED_INT, NULL);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents(); // works as a state machine
    }
    shaderprogram.Delete();
    vao.Delete();
    ebo.Delete();
    texture.Delete();
    glfwTerminate();

    return 0;
}