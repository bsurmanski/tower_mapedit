#version 130

uniform sampler2DArray textures;

smooth in vec3 fnormal;
smooth in vec2 fuv;
flat in int fmaterial;

out vec4 fragColor;
out vec4 fragNormal;

void main()
{
    //vec4 color = texture(textures, vec3(fuv, fmaterial/float(textureSize(textures, 0).z)));
    vec4 color = texture(textures, vec3(fuv, float(fmaterial)));

    fragColor = color;
    fragNormal = vec4(normalize(fnormal), 1.0f);
}
