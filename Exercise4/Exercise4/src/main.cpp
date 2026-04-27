#include "GLExample.h"

int main(int argc, char * argv[])
{
	cgCourse::GLExample app(glm::uvec2(1200, 1000), "Exercise 3");
	return app.run();
}

