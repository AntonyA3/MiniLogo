#version 300 es
precision mediump float;
out vec4 FragColor;
in vec3 color;

void main()
{         
   FragColor = vec4(color, 1.0);
}
