#version 410 core

/* TODO update your vertex shader so that...
 *      ...it has texture samplers declared
 *      ...it outputs a diffuse texture as diffuse color
 *      ...it uses a light map to modify the specular highlights
 */

in vec3 objectColor;

/* TODO Add the required input data */

in vec3 fragWorldPos;
in vec3 fragNormal;
in vec2 texCoord;
in vec3 fragTangent;
in vec3 fragBitangent;

// END TODO

/* TODO declare texture samplers here */

uniform sampler2D diffuseTex;
uniform sampler2D specularTex;
uniform sampler2D normalTex;

// END TODO

/* TODO fill these structs with values from outside the shader similar
 *      to your matric variables
 */

uniform vec3 camPos;

uniform struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
} light;

// TODO END

out vec3 color;

void main()
{
	/* TODO add the source code to do phong shading but with the values of the color, normal and specular texture.
	 *      Remember that you can also use the color output for debugging of the
	 *      texture maps and texture coordinates in case that you face troubles.
	 */

	mat3 TBN = mat3(fragTangent, fragBitangent, fragNormal);
	vec3 mapN = texture(normalTex, texCoord).rgb * 2.0 - 1.0;
	vec3 N = normalize(TBN * mapN);

	vec3 albedo = texture(diffuseTex, texCoord).rgb;
	float specMask = texture(specularTex, texCoord).r;

	vec3 lightDir = normalize(light.position - fragWorldPos);
	vec3 viewDir = normalize(camPos - fragWorldPos);

	float ambientFactor = 0.2;
	vec3 ambient = light.ambient * ambientFactor * albedo;

	float diff = max(dot(N, lightDir), 0.0);
	vec3 diffuse = diff * light.diffuse * albedo;

	vec3 halfDir = normalize(lightDir + viewDir);
	float specAngle = max(dot(N, halfDir), 0.0);
	float spec = pow(specAngle, 32.0) * specMask;
	vec3 specular = spec * light.specular;

	color = ambient + diffuse + specular;

	// TODO END
}
