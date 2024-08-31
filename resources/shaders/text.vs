#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 TexCoords;

uniform mat4 projection;
uniform float z_depth;

void main()
{
    gl_Position = projection * vec4(vertex.xy, z_depth, 1.0);
    TexCoords = vertex.zw;
}
