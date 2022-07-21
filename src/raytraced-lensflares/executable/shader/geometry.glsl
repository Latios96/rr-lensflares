#version 460

layout(triangles) in;
layout(triangle_strip) out;
layout(max_vertices=3) out;

in vec3 vcColor[];

out vec3 gColor;

void main()
{
    for (int i = 0; i < 3; i++) {
        gl_Position = gl_in[i].gl_Position;
        gColor = vcColor[i];
        //color = vec3(1,0,0);
        EmitVertex();
    }
}