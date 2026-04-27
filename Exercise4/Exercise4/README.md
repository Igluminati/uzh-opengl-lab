## Texturing - Exercise 4 (5 + 1 points)
 
### Goals

- Load textures with OpenGL 
- Apply texture mapping in a shader program
- Apply a light map to the (Blinn-)Phong model
- Set uniforms for samplers in GLSL shaders
- Implement normal mapping
- Generate tangents, bitangents, and the TBN matrix

### Additional Information

To load images, we will use **CImg** in this exercise. The setup script should handle everything correctly. However, on MacOS and Windows, you may need to install **imagemagick** additionally. 

MacOS: 

	brew install imagemagick

Windows: 

Download imagemagick from the imagemagick website. The recommended version is fine. When installing, select also "Install development headers and libraries for C and C++".

Linux (Debian/Ubuntu): 

	sudo apt install graphicsmagick


### Tasks (5 points)

1. Texture Mapping and Light Map

	In this exercise, you will apply texture mapping to give the torus and cube a more detailed and interesting appearance. In the `res` folder, you can find three textures for each object: 

	- color texture
	- specular texture
	- normal texture
	
	We recommend starting with the color and the specular texture first, and adding the normal mapping later in the process. 

	- The cube (`Cube.cpp`) is simpler for generating texture coordinates. We used one texture per side for the cube.
	- Generating texture coordinates for the torus (`Torus.cpp`) is more complex. We wrapped the texture four times around it.

	#### Texture mapping
	
	To use the textures, you should:
	- load the texture onto the GPU (`Texture.cpp`)
	- bind the texture to the shader (`GLExample.cpp`)
	- sample the value in the shader (`TexturedShape.frag`, `TexturedShape.vert`)

	#### Light map

	After implementing texture mapping, you can now apply a light map (specular map) to control the specular highlights of the textured object. You should

	- apply a light map to the cube and the torus object.
	- combine the texture mapping with the (Blinn-)Phong illumination model implemented in the last exercise.	

	#### Advisable resources

	On this topic, advisable resources can be found in the chapter of [learnopengl.com](https://learnopengl.com), namely [`Textures`](https://learnopengl.com/Getting-started/Textures) and [`Lighting maps`](https://learnopengl.com/Lighting/Lighting-maps).

2. Normal Mapping

	#### Tangent and TBN

	As you have implemented the texture mapping and light map, you can now try to apply the normal mapping. The process is similar to texture mapping, except that you additionally need to 
	
	- compute the tangents for the cube and torus (`Cube.cpp` and `Torus.cpp`). Those tangents are used to map the object's normals to point in the right direction.

	- generate the TBN (tangent, bitangent, normal) matrix.

	#### Normal Visualization

	To check your solution, extend the MultiLine rendering to visualize normals using the normal map. Implement the visualization in `TexturedNormals.vert`.
	
	You might check the `BasicNormals` shader for inspiration.

	#### Advisable resources

	On this topic, advisable resources can be found in the chapter of [learnopengl.com](https://learnopengl.com), namely [`Normal Mapping`](https://learnopengl.com/Advanced-Lighting/Normal-Mapping).

### Bonus Task (+1 point)

So far, you have implemented texture mapping using image files. In this bonus task, you should generate textures procedurally using program code instead of loading image files. You should:

- Generate color, specular and normal textures to convey the impression of a checkerboard with "depth" as can be seen in the example screenshot.

- Make checkerboard size adjustable via a variable.

You could check the example screenshot in the `doc/` folder as a reference.


### Where to Implement Your Code

You will need to implement missing functionality in the following files:

- `TexturedShape.frag`
- `TexturedShape.vert`
- `TexturedNormals.vert`
- `Cube.cpp`
- `Torus.cpp`
- `GLExample.cpp`
- `Texture.cpp`

TODO comments are provided in the code to guide your implementation.

You may also modify or extend the code if necessary.

### How to Submit:

Create a **.zip** file containing:

- the source code (please include only the source files, the **src/** and **shader/** folders)
- requested screenshots of the rendering window showing your results:
    - Phong Shading page
    - Texture Shading page
    - Bonus Task page (if implemented)
	
	Please select appropriate light positions so that the key features of the tasks are clearly visible.

Upload the zip file to **OLAT** before the deadline.


### Additional Resources

- [Download Imagemagick on Windows](https://imagemagick.org/script/download.php)
- [Basic Lighting on learnopengl.com](https://learnopengl.com/Lighting/Basic-Lighting)
- [Shaders on learnopengl.com](https://learnopengl.com/Getting-started/Shaders)
- [Textures on learnopengl.com](https://learnopengl.com/Getting-started/Textures)
- [Lighting Maps on learnopengl.com](https://learnopengl.com/Lighting/Lighting-maps)
- [Normal Mapping on learnopengl.com](https://learnopengl.com/Advanced-Lighting/Normal-Mapping)
