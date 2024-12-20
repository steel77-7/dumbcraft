#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H
#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"

//#include "glm/gtx/rotate_vector.hpp>"


class Camera
{
public:
    glm::vec3 Position;
    glm::vec3 Orientation = glm ::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    int width, height;
    float sensitivity = 0.1f;

    // Constructors
    Camera();
    Camera(int width, int height, glm::vec3 position);

    // Methods
    void move(const float deg, const float nearPlane, const float farPlane, Shader &shader, const char *uniform);
    void inputs(GLFWwindow *window);

    // Destructor
    virtual ~Camera() = default;
};

#endif
