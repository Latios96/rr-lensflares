#version 460

uniform mat4 MVP;
in vec3 vCol;
in vec3 vPos;
out vec3 color;

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
    gl_Position = MVP * vec4(vPos, 1.0);
    color = vCol;
}