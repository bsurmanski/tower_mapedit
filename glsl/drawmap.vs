#version 130

uniform mat4 tmat;

in vec3 position;
in vec3 normal;
in vec2 uv;
in float material;

smooth out vec3 fnormal;
smooth out vec2 fuv;
flat   out int fmaterial;

void main()
{
    gl_Position = tmat * vec4(position, 1.0f);
    fnormal = (tmat * vec4(normal, 0.0f)).xyz;
    fnormal.z = -fnormal.z;
    fuv = uv;
    fmaterial = int(material);
}
