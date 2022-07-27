#version 460

layout(triangles) in;
layout(triangle_strip) out;
layout(max_vertices = 3) out;

in vec3 vcColor[];
in vec2 vAperturePos[];

out vec3 gColor;
out float intensity;

void main() {

  vec3 v0v1 = vec3(gl_in[1].gl_Position - gl_in[0].gl_Position);
  vec3 v0v2 = vec3(gl_in[2].gl_Position - gl_in[0].gl_Position);
  float calculatedArea = length(cross(v0v1, v0v2)) / 2;
  float originalArea = 0.1 * 0.1 / 2;// todo when changing grid resolution, adjust this!
  for (int i = 0; i < 3; i++) {
    gl_Position = gl_in[i].gl_Position;
    intensity = originalArea / calculatedArea;
    gColor = vec3(vAperturePos[i].x, vAperturePos[i].y, 0) * vcColor[i].g * intensity;
    EmitVertex();
  }
}