#version 460

uniform int subdivisions;

layout(triangles) in;
layout(triangle_strip) out;
layout(max_vertices = 3) out;

in vec3 vcColor[];
in vec2 vAperturePos[];
in float rayStayed[];

out vec3 gColor;
out float intensity;
out vec2 textureCoordinate;

void main() {

  vec3 v0v1 = vec3(gl_in[1].gl_Position - gl_in[0].gl_Position);
  vec3 v0v2 = vec3(gl_in[2].gl_Position - gl_in[0].gl_Position);
  float calculatedArea = length(cross(v0v1, v0v2)) / 2;
  float originalArea = pow(1.0/20, 2);
  intensity = originalArea / calculatedArea;

  if (intensity < 0.03){
    return;
  }

  for (int i = 0; i < 3; i++) {
    gl_Position = gl_in[i].gl_Position;
    intensity = rayStayed[i] * intensity;
    textureCoordinate = vAperturePos[i];
    EmitVertex();
  }
}