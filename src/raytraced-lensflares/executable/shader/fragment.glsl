#version 330

in vec3 color;
out vec4 fragment;

void main(){
    fragment = vec4(color[0], color[1], color[2], 1.0);
}