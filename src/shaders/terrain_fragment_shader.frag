
#version 330 core

const int numLights = 4;

in vec2 pass_textureCoords;
in vec3 surfaceNormal;
in vec3 toLightVector[numLights];
in vec3 toCameraVector;
in float visibility;

out vec4 out_colour;

uniform sampler2D backgroundTexture;
uniform sampler2D rTexture;
uniform sampler2D gTexture;
uniform sampler2D bTexture;
uniform sampler2D blendMap;

uniform vec3 lightColour[numLights];
uniform vec3 attenuation[numLights];
uniform float shineDamper;
uniform float reflectivity;
uniform vec3 skyColour;

void main(void)
{
    vec4 blendMapColour = texture(blendMap, pass_textureCoords);

    float backTextureAmount = 1 - (blendMapColour.r + blendMapColour.g + blendMapColour.b);
    vec2 tiledCoords = pass_textureCoords * 40.0f;
    vec4 backgroundTextureColour = texture(backgroundTexture, tiledCoords) * backTextureAmount;
    vec4 rTextureColour = texture(rTexture, tiledCoords) * blendMapColour.r;
    vec4 gTextureColour = texture(gTexture, tiledCoords) * blendMapColour.g;
    vec4 bTextureColour = texture(bTexture, tiledCoords) * blendMapColour.b;

    vec4 totalColour = backgroundTextureColour + rTextureColour
            + gTextureColour + bTextureColour;
    vec3 unitNormal = normalize(surfaceNormal);
    vec3 unitVectorToCamera = normalize(toCameraVector);
    vec3 totalDiffuse = vec3(0.0f);
    vec3 totalSpecular = vec3(0.0f);

    for (int i = 0; i < numLights; i++) {
        float distance = length(toLightVector[i]);
        float attFactor = attenuation[i].x + attenuation[i].y * distance + attenuation[i].z * distance * distance;
        vec3 unitLightVector = normalize(toLightVector[i]);

        float nDotl = dot(unitNormal, unitLightVector);
        float brightness = max(nDotl, 0.0f);
        vec3 diffuse = brightness * lightColour[i]/attFactor;
        totalDiffuse = totalDiffuse + diffuse;

        vec3 lightDirection = -unitLightVector;
        vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);

        float specularFactor = dot(reflectedLightDirection, unitVectorToCamera);
        specularFactor = max(specularFactor, 0.0);
        float dampedFactor = pow(specularFactor, shineDamper);
        vec3 finalSpecular = (dampedFactor * reflectivity * lightColour[i])/attFactor;
        totalSpecular += finalSpecular;
    }

    out_colour = vec4(totalDiffuse, 1.0) * totalColour + vec4(totalSpecular, 1.0);

    out_colour = mix(vec4(skyColour, 1.0), out_colour, visibility);
}
