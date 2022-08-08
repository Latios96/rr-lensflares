#version 330

in float intensity;
in vec2 textureCoordinate;
out vec4 fragment;

uniform sampler2D apertureTexture;

void main() { fragment = texture(apertureTexture, textureCoordinate) * intensity; }