#include "GLExample.h"

int main(int argc, char * argv[])
{
	// create the app
	cgCourse::GLExample app(glm::uvec2(1280, 1024), "Exercise 1");

	// run the app
	return app.run();
}

