#version 330 core
out vec4 FragColor;

in vec2 texCoords;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
};

uniform sampler2D aTexture;
uniform sampler2D ambient;
uniform Material material;

void main() {
    vec4 ambientValue = texture(ambient, texCoords) * vec4(1.0);
    FragColor = ambientValue * texture(aTexture, texCoords);
}
