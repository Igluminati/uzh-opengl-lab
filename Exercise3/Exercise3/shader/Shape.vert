#version 410 core

/* Update your vertex shader so that...
 *      ...it emits all necessary information to the fragment shader for phong illumination
 *      ...it emits the color in case you do gouraud shading
 */

// Input vertex data
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec3 vNormal;

// Output data will be interpolated for each fragment.
// Tip: Try to use the flat modifier to make color associations of a fragment visible for debugging.
out vec3 objectColor;
out vec3 normal;
out vec3 worldPos;

// matrices that stay constant for the whole mesh.
uniform mat4 modelMatrix;
uniform mat4 mvpMatrix;

uniform bool gouraudShading;

// TODO Additional variables
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
out vec3 gouraudColor; 
// END TODO

void main()
{
    normal = mat3(transpose(inverse(modelMatrix))) * vNormal;

    // Output position of the vertex, in clip space : MVP * vPosition
    gl_Position = mvpMatrix * vec4(vPosition, 1);

    // The color of each vertex will be interpolated
    // to produce the color of each fragment
    // ... uncomment this for color
    objectColor = vColor;

    // ... uncomment this for color according to normals
    // objectColor = vNormal;

    worldPos = vec3(modelMatrix * vec4(vPosition, 1));

    if(gouraudShading)
    {
        // TODO add there code for gouraud shading
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
        objectColor = (ambient + (diffuse + specular) * intensity) * vColor;      
        // END TODO
    }
}

