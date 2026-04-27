#version 410 core

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

uniform vec3 camPos;

uniform struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
} light;

void main()
{
    normal = normalize(mat3(transpose(inverse(modelMatrix))) * vNormal);

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

        objectColor = (ambientColor + diffuseColor + specularColor) * objectColor.rgb, 1.0;
    }
}

