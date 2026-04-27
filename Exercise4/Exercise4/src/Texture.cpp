#include "Texture.h"

#include <iostream>
#include <cstring>

#define cimg_display 0
#include <CImg.h>

// Bonus Task
#include <vector>
#include <numeric>
#include <algorithm>
// END Bonus

using namespace cimg_library;


namespace cgCourse
{
    void Texture::loadFromFile(const std::string & _filename)
    {
        CImg<unsigned char> img(_filename.c_str());

        int channels = img.spectrum();
        size.x = img.width();
        size.y = img.height();

        img.permute_axes("cxyz");

        /*
		 *  TODO: generate the texture here:
		 *        - generate the texture handle and set the variable texhandle
		 *        - bind the texture handle
		 *        - set the min/mag filter parameter and if it works test if you
		 *          see a difference between GL_LINEAR, MIPMAP_LINEAR, NEAREST etc..
		 *        - set the texture wrap parameters
		 *        - set the texture data with glTexImage2D
		 *        - generate mipmaps
		 *        - unbind the texture handle (we do this to have a clean state when the
		 *          function is ending and no textures are bound after this call.)
		 *   Note that depending on the channels the a different kind of texture might be created, for 4 channels GL_RGBA, for 3 GL_RGB and for one GL_RED.
         *   Some operating systems might use GL_BGRA
		 */

        // TODO END
    }

    // Bonus Task:
    void Texture::createBonus(int checkerSize) {

    }

    void Texture::createBonusSpecular(int checkerSize) {

    }

    void Texture::createBonusNormal(int checkerSize) {

    }
    // End Bonus Task

    const GLuint & Texture::getTexHandle() const
    {
        return texhandle;
    }
}