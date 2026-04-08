#version 410 core
/* Update your vertex shader so that...
 *      ...it emits the color for phong illumination
 *      ...it emits the color from the vertex shader in case you do gouraud shading there
 */

in vec3 objectColor;
in vec3 normal;
in vec3 worldPos;

/* TODO fill these structs with values from outside the shader similar
 *      to your matrix variables
 */
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;
uniform bool showAmbient;
uniform bool showDiffuse;
uniform bool showSpecular;
uniform bool useSpotlight;
uniform vec3 spotlightDir;
uniform float spotlightCutOff;
uniform float spotlightOuterCutOff;
// END TODO

uniform bool gouraudShading;

// Ouput data
out vec3 color;

void main()
{
    // Output color = color specified in the vertex shader,
    // interpolated between all 3 surrounding vertices
    color = objectColor;

    if(!gouraudShading)
    {
        // TODO add there code for phong lighting
        vec3 norm = normalize(normal);
        vec3 lightDir = normalize(lightPos - worldPos);
        vec3 viewDir = normalize(viewPos - worldPos);
        vec3 reflectDir = reflect(-lightDir, norm);

        // Ambient
        float ambientStrength = 0.1;
        vec3 ambient = showAmbient ? ambientStrength * lightColor : vec3(0.0);

        // Diffuse
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = showDiffuse ? diff * lightColor : vec3(0.0);

        // Specular
        float specularStrength = 0.5;
        float shininess = 32.0;
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
        vec3 specular = showSpecular ? specularStrength * spec * lightColor : vec3(0.0);

        // Spotlight attenuation
        float intensity = 1.0;
        if(useSpotlight)
        {
            float theta = dot(lightDir, normalize(-spotlightDir));
            float epsilon = spotlightCutOff - spotlightOuterCutOff;
            intensity = clamp((theta - spotlightOuterCutOff) / epsilon, 0.0, 1.0);
        }

        // Combine
        color = (ambient + (diffuse + specular) * intensity) * objectColor;
        // END TODO
    }
}

