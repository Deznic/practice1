#include <texture.h>

#include <glad/glad.h>
#include <SDL_image.h>
#include <iostream>

texture::texture(const char* path) {
    SDL_Surface* image = IMG_Load(path);
    std::cout << "creating image \n " << SDL_GetError() << std::endl;
    
    
    
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    
    
    SDL_FreeSurface(image);
    
}
