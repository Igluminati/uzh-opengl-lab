#version 410 core

in vec3 objectColor;
in vec3 normal;
in vec3 worldPos;

uniform vec3 camPos;

uniform struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
} light;


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
        float ambientFactor = 0.2f;
        vec3 ambientColor = (light.ambient.xyz * ambientFactor);

        // diffuse shading
        vec3 lightDir = vec3(normalize(light.position - worldPos));
        float diffDot = max(dot(normal, lightDir), 0.0);
        vec3 diffuseColor = diffDot * light.diffuse;

        // specular shading (phong version)
        vec3 viewDir = vec3(normalize(camPos - worldPos));
        vec3 reflectDir = reflect(-lightDir, normal);
        float specDot = max(dot(viewDir, reflectDir), 0.0);
        float spec = pow(specDot, 32);
        float specStrength = 1.0;
        vec3 specularColor = specStrength * spec * light.specular;

        color = (ambientColor + diffuseColor + specularColor) * objectColor.rgb, 1.0;
    }
}

