#include "shaderprogram.h"
#include "filehandler.h"
#include <iostream>
#include <string>
#include <glm/gtc/type_ptr.hpp>

P_Shader::P_Shader(const char* vs, const char* fs)
{
    /** V_Shader (VertexShader) */
    GLuint V_Shader;
    /** F_Shader (FragmentShader)*/
    GLuint F_Shader;
    
    V_Shader = glCreateShader(GL_VERTEX_SHADER);
    F_Shader = glCreateShader(GL_FRAGMENT_SHADER);
    
    char log1[1024];
    
    std::string temp1 = readFile(vs).c_str();
    std::string temp2 = readFile(fs).c_str();
    
    const char* V_ShaderSource = temp1.c_str();
    const char* F_ShaderSource = temp2.c_str();
    
    //shader source
    glShaderSource(V_Shader, 1, &V_ShaderSource, NULL);
    glShaderSource(F_Shader, 1, &F_ShaderSource, NULL);
    
    //compile Shader
    
        //cout log after compile
        std::cout << "compiling vertex Shader" << std::endl;    
        glCompileShader(V_Shader);
        glGetShaderInfoLog(V_Shader, 1024, NULL, log1);
        std::cout << log1;
        std::cout << "compiling fragment Shader" << std::endl;
        glCompileShader(F_Shader);
        glGetShaderInfoLog(F_Shader, 1024, NULL, log1);
        std::cout << log1 << std::endl;
    std::fill_n(log1, 1024, 0);
    P_Id = glCreateProgram();
    //link Shader
    
        glAttachShader(P_Id, V_Shader);
        glAttachShader(P_Id, F_Shader);
        glLinkProgram(P_Id);
        glGetShaderInfoLog(P_Id, 1024, NULL, log1);
        std::cout << "linking program\n" << log1 << std::endl;
    
    //delete shader
    glDeleteShader(F_Shader);
    glDeleteShader(V_Shader);
}

void P_Shader::SetUniformMatrix4fv(const char* name, glm::mat4 val)
{
    glUniformMatrix4fv(glGetUniformLocation(P_Id, name), 1, GL_FALSE, glm::value_ptr(val));
}


void P_Shader::SetUniform1i(const char* name, int val)
{
    glUniform1i(glGetUniformLocation(P_Id, name), val);    
}

P_Shader::P_Shader()
{P_Id = 0;}

void P_Shader::UseProgram(int tf)
{
    switch (tf) {
        case 0:
            glUseProgram(0);
            break;
        case 1:
            glUseProgram(P_Id);
            break;
    }
}

