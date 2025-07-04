#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 aColor;
  
out vec4 vertexColor; // specify a color output to the fragment shader
uniform vec3 offset;

void main()
{
    gl_Position = vec4((aPos+offset), 1.0); // see how we directly give a vec3 to vec4's constructor
    vertexColor = vec4(aColor, 1.0f); // set the output variable to a dark-red color
}