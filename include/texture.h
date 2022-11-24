#pragma once
#include <SDL_image.h>
#include <glad/glad.h>

class texture {
private:
    
public:
    texture(const char* path);
    GLuint id;
};
