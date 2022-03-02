#version 330

// Input
in vec3 outColor;
// Output
layout(location=0) out vec4 fragColor;

void main()
{
   fragColor = vec4(outColor, 1);
}
