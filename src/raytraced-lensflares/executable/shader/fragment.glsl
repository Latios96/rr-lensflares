#version 330

in vec3 gColor;
out vec4 fragment;

void main() {
  fragment = vec4(gColor[0], gColor[1], gColor[2], 1.0);
  // fragment = vec4(1,0,0,0);
}