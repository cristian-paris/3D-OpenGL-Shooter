#version 330

// Input
layout(location=0) in vec3 position;
layout(location=1) in vec3 v_normal;


// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 object_color;

uniform float Time;

// Output
out vec3 outColor;


float rand(vec3 co)
{
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{   
       outColor = object_color;
       vec3 newPos = 0.5 * v_normal * rand(sin(Time) * position) + position;
       gl_Position = Projection * View * Model * vec4(newPos, 1);
}
