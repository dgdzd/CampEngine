#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D screenTexture;

/*
 * This fragment shader is a post-processing effect.
 * Each pixels will be rendered as the average value of r, g and b applied to these three colors
 */

void main() {
    vec4 color = texture(screenTexture, TexCoords);
    float average = (color.r + color.g + color.b) / 3;
    FragColor = vec4(average, average, average, 1.0);
}

