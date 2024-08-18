#version 330 core
in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D text;
uniform vec4 textColor;

void main()
{
    vec4 sampled = vec4(1.0f, 1.0f, 1.0f, texture(text, TexCoords).r);
    FragColor = textColor * sampled;
}
