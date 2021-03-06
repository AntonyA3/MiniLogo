#version 300 es
layout (location = 0) in vec3 vpos;
layout (location = 1) in vec3 vcolor;
out vec3 color;
uniform mat4 transform;
void main()
{
   gl_Position = transform * vec4(vpos, 1.0);
   color = vcolor;
}
