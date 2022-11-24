#pragma once
#include <glm/glm.hpp>
#include <vector>

struct Object {
public:
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 force;
    float mass;
};

class World {
private:
    std::vector<Object*> m_objects;
    glm::vec3 m_gravity;
    
    void AddObject(Object* object);
    void RemoveObject(Object* object);
    
    void loop(float dl);
    
};
