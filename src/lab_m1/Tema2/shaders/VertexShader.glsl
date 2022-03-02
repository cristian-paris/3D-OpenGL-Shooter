#version 330

// Input
layout(location=0) in vec3 position;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 object_color;

// Output
out vec3 outColor;

void main()
{
       outColor = object_color;
       gl_Position = Projection * View * Model * vec4(position, 1);
}
