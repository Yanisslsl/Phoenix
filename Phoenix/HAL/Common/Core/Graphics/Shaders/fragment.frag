#version 330 core
out vec4 FragColor;

in vec3 vColor;
in vec2 vTexCoord;

uniform sampler2D ourTexture;

void main()
{
    if(vColor != vec3(0.0, 0.0, 0.0)){
        FragColor = vec4(vColor, 1.0f);
    } else {
        vec4 texColor = texture(ourTexture, vTexCoord);
        if(texColor.a < 0.1)
            discard;
        FragColor = texColor;
    }
    
}