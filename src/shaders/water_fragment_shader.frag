#version 330 core

out vec4 out_Color;

in vec4 clipSpace;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;

void main(void) {

    vec2 ndc = (clipSpace.xy/clipSpace.w)/2.0 + 0.5;
    vec2 refractTexCoords = ndc;
    vec2 reflectTexCoords = vec2(ndc.x, -ndc.y);

    vec4 reflectColour = texture(reflectionTexture, reflectTexCoords);
    vec4 refractColour = texture(refractionTexture, refractTexCoords);

    out_Color = mix(reflectColour, refractColour, 0.5);
}