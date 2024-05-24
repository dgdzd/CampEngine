#version 330 core
out vec4 FragColor;

in vec2 texCoords;

uniform vec4 color;
uniform vec4 outlineColor;
uniform float outlineThickness;
uniform bool hovered;
uniform vec4 hoverModifier;
uniform vec2 dimensions;

void main() {
    float isOutline = 1.0;
    if((texCoords.x * dimensions.x >= outlineThickness && texCoords.x * dimensions.x <= dimensions.x - outlineThickness) && (texCoords.y * dimensions.y >= outlineThickness && texCoords.y * dimensions.y <= dimensions.y - outlineThickness)) {
        isOutline = 0.0;
    }
    if(isOutline > 0.5) {
        FragColor = outlineColor * (hovered ? hoverModifier : vec4(1.0));
    } else {
        FragColor = color * (hovered ? hoverModifier : vec4(1.0));
    }
}
