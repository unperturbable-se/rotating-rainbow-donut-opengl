#version 450 core

layout (location = 0) in vec3 aPos;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform float uTime;

out vec3 vertexColor;

// Rainbow color function
vec3 rainbow(float t) 
{
    float r = 0.5 + 0.5 * sin(6.2831 * t + 0.0);
    float g = 0.5 + 0.5 * sin(6.2831 * t + 2.0944); // 2π/3
    float b = 0.5 + 0.5 * sin(6.2831 * t + 4.1888); // 4π/3
    return vec3(r, g, b);
}

void main()
{
    // Apply model, view, and projection
    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);

    // Map position to rainbow
    float t = (aPos.x + aPos.y + aPos.z + 3.0) * 0.1 + uTime * 0.2;
    vertexColor = rainbow(t);
}
