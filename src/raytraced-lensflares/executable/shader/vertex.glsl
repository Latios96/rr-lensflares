#version 460

uniform mat4 MVP;
in vec3 vCol;
in vec3 vPos;

layout(std430, binding = 3) buffer reflectionSequences
{
    ivec2 indices[];
};

struct Lens{
    float curvatureRadius;
    float thickness;
    float ior;
    float apertureRadius;
    float center;
} lens;

layout(std430, binding = 4) buffer lensSystem
{
    Lens lenses[];
};

void main(){
    gl_Position = vPos;
}