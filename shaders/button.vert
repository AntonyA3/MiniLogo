#version 300 es
layout (location = 0) in vec2 vpos;
layout (location = 1) in vec3 vcolor;
layout (location = 2) in vec3 vIconCoord;

out vec3 color;
out vec3 iconCoord;
uniform mat4 transform;
void main()
{
   gl_Position = transform * vec4(vpos, 0.0f, 1.0);
   color = vcolor;
   iconCoord = vIconCoord;
}
