#ifndef CAMERA_CLASSS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Camera
{

public:
    glm::vec3 Position;
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    int height, width;
    Camera(int width, int height, glm::vec3 postion);
    void move(float deg , float nearPlane , float farPlane, Shader& shader,  const char* uniform );
    void inputs(GLFWwindow* window);
};

#endif