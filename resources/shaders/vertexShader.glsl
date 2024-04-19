#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

struct Object {
    vec3 position;
};

out vec3 newColor;
out vec2 texCoords;

uniform Object object;
uniform Object camera;

void main() {
    gl_Position = vec4(aPos, 1.0);
    texCoords = aTexCoords;
}
