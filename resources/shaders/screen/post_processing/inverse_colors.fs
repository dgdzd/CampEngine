#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D screenTexture;

/*
 * This fragment shader is a post-processing effect.
 * The goal of that shader is simply to invert all colors on the screen.
 */

void main() {
    FragColor = vec4(vec3(1.0 - texture(screenTexture, TexCoords)), 1.0);
}
