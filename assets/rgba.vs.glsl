#version 450 core
layout(location=0) in vec2 inPos;
layout(location=1) in vec4 inCol;

out vec4 color;

void main(){
    color = vec4(inCol.xyzw);
    gl_Position = vec4(inPos.xy, 0.0, 1.0);
};