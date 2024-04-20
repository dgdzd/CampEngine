#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D screenTexture;

/*
 * This fragment shader is a post-processing effect.
 * This is the base fragment shader used to make post-processing effect, and does nothing other than copying pixels from a texture buffer to the screen.
 */

void main() {
    FragColor = texture(screenTexture, TexCoords);
}
