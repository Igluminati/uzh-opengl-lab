#version 410 core

/* TODO update your vertex shader so that...
 *      ...it has texture samplers declared
 *      ...it outputs a diffuse texture as diffuse color
 *      ...it uses a light map to modify the specular highlights
 */

in vec3 objectColor;

/* TODO Add the required input data */

// END TODO

/* TODO declare texture samplers here */

// END TODO

/* TODO fill these structs with values from outside the shader similar
 *      to your matric variables
 */

// TODO END

out vec3 color;

void main()
{
	color = objectColor;

	/* TODO add the source code to do phong shading but with the values of the color, normal and specular texture.
	 *      Remember that you can also use the color output for debugging of the
	 *      texture maps and texture coordinates in case that you face troubles.
	 */

	// TODO END
}

