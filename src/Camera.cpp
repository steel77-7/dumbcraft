#include"Header_files/Camera.h"


//initialization here
Camera:: Camera(int width, int height, glm::vec3 position){ 
    Camera::width = width;
    Camera::height = height;
    Position = position;
}

void Camera::move(float deg , float nearPlane , float farPlane, Shader& shader,  const char* uniform ){ 
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        view= glm::lookAt(Position, Position+Orientation, Up) ;
        projection = glm::perspective( glm::radians(deg),(float)(width/height), nearPlane, farPlane );

        glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform),1,GL_FALSE, glm::value_ptr(projection*view));
}
