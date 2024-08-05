#version 330 core
out vec4 FragColor;

in vec2 texCoords;

uniform vec4 color;
uniform vec4 outlineColor;
uniform float outlineThickness;
uniform bool hovered;
uniform vec4 hoverModifier;
uniform vec2 center;
uniform float radius;

void main() {
    float isOutline = 1.0;
    float dis = distance(texCoords * radius, center);
    if(dis < radius - outlineThickness) {
        isOutline = 0.0;
    } else if(dis < radius) {
        if(isOutline > 0.5) {
            FragColor = outlineColor * (hovered ? hoverModifier : vec4(1.0));
        } else {
            FragColor = color * (hovered ? hoverModifier : vec4(1.0));
        }
    } else {
        FragColor = vec4(0.0);
    }
}
