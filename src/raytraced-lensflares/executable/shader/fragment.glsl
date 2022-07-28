#version 330

in float intensity;
in vec2 textureCoordinate;
out vec4 fragment;

uniform sampler2D apertureTexture;

void main() {
    //fragment = vec4(textureCoordinate.x, textureCoordinate.y, 0, 1.0) * intensity;
    fragment = texture(apertureTexture, textureCoordinate) * intensity;
    //fragment = vec4(intensity, intensity, 0, 1.0);
}