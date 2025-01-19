#version 450 core
layout(location=0) in vec2 inPosition;
layout(location=1) in vec3 inColor;

out vec3 color;

void main(){
    color = vec3(inColor.xyz);
    gl_Position = vec4(inPosition.xy, 0.0, 1.0);
};