#version 450 core
in vec4 color;

layout(location=0) out vec4 outCol;

void main(){
    outCol = vec4(color.xyzw);
};