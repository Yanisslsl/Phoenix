#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform vec3 u_Color;
uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

out vec3 vColor;
out vec2 vTexCoord;

void main()
{
    gl_Position = u_ViewProjection * u_Model * vec4(aPos, 1.0);
    vColor = u_Color;
    vTexCoord = aTexCoord;
}