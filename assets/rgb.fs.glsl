#version 450 core
in vec3 color;

layout(location=0) out vec4 outColor;

void main(){
    outColor = vec4(color.xyz, 1.0);
};