#include <iostream>
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <string>

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "filehandler.h"
#include "shaderprogram.h"
#include "texture.h"

SDL_Window* window = NULL;
SDL_GLContext glContext;
SDL_Event windowEvents;
bool closeWindow = false;
P_Shader shaderProgram;
glm::mat4 view = glm::mat4(1.0f);
glm::mat4 projection = glm::mat4(1.0f);
glm::mat4 model = glm::mat4(1.0f);
/** S = SCREEN */ GLuint S_WIDTH = 800, S_HEIGHT = 600;

int main() 
{
    printf("start\n");
    if(SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        std::cout << "Cannot initialize SDL : \n" << SDL_GetError();
        return 1;
    }
    //create window with opengl
    window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, S_WIDTH , S_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (window == NULL) 
    {
        std::cout << "Cannot Create window :\n" << SDL_GetError();
        return 1;
    }
    printf("window initialized\n");
    
    //specify OpenGL version
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
    //create opengl context
    glContext = SDL_GL_CreateContext(window);
    if (glContext == NULL) {
        std::cout << "Cannot Create OpenGL Context: \n" << SDL_GetError();
        return 1;
    }
    printf("opengl context created\n");
    
    gladLoadGLLoader(SDL_GL_GetProcAddress);
    glEnable(GL_DEPTH_TEST);
    
    
    //renderable creation
    float vertices[] {
        -0.5f,-0.5f, 0.0f, 0.0f, 0.0f, // B-left
         0.5f,-0.5f, 0.0f, 0.0f, 1.0f, // B-right
         0.5f, 0.5f, 0.0f, 1.0f, 1.0f, // T-right
        
        -0.5f,-0.5f, 0.0f, 0.0f, 0.0f, // B-left
        -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, // T-left
         0.5f, 0.5f, 0.0f, 1.0f, 1.0f, // T-right
    };
    
    glm::vec3 posa(vertices[0], vertices[1], vertices[2]);
    
    
    const glm::vec3 GRAVITY = glm::vec3(0.0f,-0.09f,0.0f);
    
    glm::vec3 cubePosition = glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 cubeVelocity = glm::vec3(0.0f);
    glm::vec3 cubeForce = glm::vec3(0.0f);
    float cubeMass = 0.001f;
    
    int num_triangles = (sizeof(vertices)/sizeof(float)/5)*3;
    std::cout << num_triangles << "\n";
    
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    texture texture("resources/image.jpeg");
    
    //creating shader
    printf("creating shader\n");
//     P_Shader temp_ShaderProgam ("resources/vertex.vs", "resources/fragment.fs");
    shaderProgram = P_Shader("resources/vertex.vs", "resources/fragment.fs");
    
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
//     shaderProgram.UseProgram(true);
//     shaderProgram.SetUniform1i("tex", 0);
    
    //matrixs math what evr
    printf("doing maths");
    projection = glm::perspective(glm::radians(45.0f), (float)S_WIDTH/(float)S_HEIGHT, 0.1f, 1000.0f);
    
    view = glm::translate(view, glm::vec3(0.0f,0.0f,-5.0f));
    
    model = glm::mat4(1.0f);
    model = glm::translate(model, cubePosition);
    
    shaderProgram.UseProgram(true);
    shaderProgram.SetUniformMatrix4fv("projection",projection);
    shaderProgram.SetUniformMatrix4fv("view", view);
    shaderProgram.SetUniformMatrix4fv("model", model);
    shaderProgram.UseProgram(false);
    
    double deltatime;
    Uint64 currenttime = SDL_GetPerformanceCounter();
    Uint64 lastframe = 0;
    
    glm::vec3 positions[2] = {glm::vec3(0.0f,1.6f,0.0f), glm::vec3(0.0f,-1.6f,0.0f)};
    
    //loop
    printf("loop start\n"); std::cout << std::endl;
    while (closeWindow == false) 
    {
        lastframe = currenttime;
        currenttime = SDL_GetPerformanceCounter();
        deltatime = (currenttime-lastframe)*1e-8f;
        
//         std::cout << deltatime << std::endl;
        
        glViewport(0,0,800,600);
//         cubeVelocity = (cubeVelocity != glm::vec3(0.0f)) glm::vec3(0.0f) ?  : glm::vec3(0.0f);
        
        cubeForce += cubeMass * GRAVITY;
        
        while (SDL_PollEvent(&windowEvents)){
            switch (windowEvents.type) {
                case SDL_QUIT:
                    closeWindow = true;
                    break;
                case SDL_KEYDOWN:
                    
                    switch (windowEvents.key.keysym.sym) {
                        case SDLK_SPACE:
                            cubeForce = glm::vec3(0.0f);
                            cubeForce.y += cubeMass * 3.0f;
                        break;
                        case SDLK_LEFT:
                            cubeForce = glm::vec3(0.0f);
                            cubePosition.x -= 0.1f;
                        
                    }
                    break;
                default:break;
            }
        }
        
        cubeVelocity += cubeForce / cubeMass * (float)deltatime;
        cubePosition += cubeVelocity * (float)deltatime;
        
        if (cubePosition.y < -1.6f) {
            cubeVelocity.y = 0;
            cubePosition.y = -1.6f;
        } /*else if (cubePosition.y > 1.6f) {
            cubeVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
            cubePosition = glm::vec3(0.0f, 1.6f, 0.0f);
        }*/
        
        cubeForce = glm::vec3(0.0f);
        
        glClearColor(0.0f,1.0f,0.0f,1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        
//         glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.id);
        
        shaderProgram.UseProgram(true);
        
        glBindVertexArray(VAO);
        
        for (int i(0); i < 3; i++) {
            
            if (positions[i-1].x < -3.3f) {
                positions[i-1].x = 3.3f;
                std::cout << "limit " << positions << std::endl;
            } else {
                positions[i-1].x -= 0.05f * deltatime;
            }
            
            model = glm::mat4(1.0f);
            
            switch (i) {
                case 0:
                    model = glm::translate(model, cubePosition);
                    break;
                default:
                    model = glm::translate(model, positions[i-1]);
                    break;
            }
            shaderProgram.SetUniformMatrix4fv("model", model);
            
            glDrawArrays(GL_TRIANGLES, 0, num_triangles);    
        }
        
        SDL_GL_SwapWindow(window);
    }
    
    cubePosition = view * glm::vec4(cubePosition, 1.0f);
    std::cout << cubePosition.x << std::endl;
    
    //end
    printf("deconstructing\n");
    SDL_DestroyWindow(window);
    SDL_Quit();
    printf("end");
    return 0;
}
