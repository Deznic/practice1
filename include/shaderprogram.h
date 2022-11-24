#pragma once

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

/** Program_Shader (Shader Program) */
class P_Shader {
private:
    /** P_Id (ProgramId)*/
    GLuint P_Id;
public:
    P_Shader();
    /** vs: VertexShader path, fs: FragmentShader path*/
    P_Shader(const char* vs, const char* fs);
    /** tf: true/false */
    void UseProgram(int tf);
    void SetUniform1i(const char* name, int val);
    void SetUniformMatrix4fv(const char* name, glm::mat4 val);
};
