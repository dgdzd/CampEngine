//
//  material.h
//  CampEngine++
//
//  Created by Noah Campagne on 20/04/2024.
//

#ifndef material_h
#define material_h

#include <glm/glm.hpp>
#include <shaders/shader.h>
#include <textures/texture.h>

class UnlitMaterial {
public:
    Shader shader;
    Texture texture;
    
    UnlitMaterial(Shader shader, Texture texture);
};

class LitMaterial {
public:
    Texture diffuse, specular;
    Shader shader;
    Texture texture;
    float shineStrength;
    
    LitMaterial();
};

#endif /* material_h */
