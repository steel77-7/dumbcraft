#include "Header_files/VAO.h"

VAO::VAO(){ 
    glGenVertexArrays(1,&ID);
}

void VAO::LinkVBO(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset){ 
    VBO.Bind();
    glVertexAttribPointer(layout, numComponents, type,0, stride, offset);
    glEnableVertexAttribArray(layout); //if not enabled then the program wont work
    //enable shit first
    //VBO.Unbind();

}

void VAO::Bind(){
    glBindVertexArray(ID); 
}

void VAO::Unbind(){ 
    glBindVertexArray(0); 
    
}

void VAO::Delete(){ 
    glDeleteVertexArrays(1,&ID); 
}


