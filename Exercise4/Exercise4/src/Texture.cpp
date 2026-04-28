#include "Texture.h"

#include <glm/glm.hpp>

#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>

#define cimg_display 0
#include <CImg.h>

using namespace cimg_library;


namespace cgCourse
{
    void Texture::loadFromFile(const std::string & _filename)
    {
        CImg<unsigned char> img(_filename.c_str());

        int channels = img.spectrum();
        size.x = img.width();
        size.y = img.height();

        GLenum format = GL_RGB;
        GLenum internalFormat = GL_RGB8;
        if (channels == 4)
        {
            format = GL_RGBA;
            internalFormat = GL_RGBA8;
        }
        else if (channels == 3)
        {
            format = GL_RGB;
            internalFormat = GL_RGB8;
        }
        else if (channels == 1)
        {
            format = GL_RED;
            internalFormat = GL_R8;
        }

        std::vector<unsigned char> packed(static_cast<size_t>(size.x * size.y * channels));
        for (int y = 0; y < static_cast<int>(size.y); ++y)
        {
            for (int x = 0; x < static_cast<int>(size.x); ++x)
            {
                const int row = static_cast<int>(size.y) - 1 - y;
                for (int c = 0; c < channels; ++c)
                {
                    packed[static_cast<size_t>((row * static_cast<int>(size.x) + x) * channels + c)] =
                        img(x, y, 0, c);
                }
            }
        }

        glGenTextures(1, &texhandle);
        glBindTexture(GL_TEXTURE_2D, texhandle);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     static_cast<GLint>(internalFormat),
                     static_cast<GLsizei>(size.x),
                     static_cast<GLsizei>(size.y),
                     0,
                     format,
                     GL_UNSIGNED_BYTE,
                     packed.data());
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    // Bonus Task:
    void Texture::createBonus(int checkerSize)
    {
        const int w = 512;
        const int h = 512;
        const int cs = std::max(2, checkerSize);
        size.x = static_cast<float>(w);
        size.y = static_cast<float>(h);

        std::vector<unsigned char> rgba(static_cast<size_t>(w * h * 4));
        for (int y = 0; y < h; ++y)
        {
            for (int x = 0; x < w; ++x)
            {
                const bool dark = (((x / cs) + (y / cs)) & 1) == 0;
                const size_t i = static_cast<size_t>((y * w + x) * 4);
                if (dark)
                {
                    rgba[i + 0] = 40;
                    rgba[i + 1] = 40;
                    rgba[i + 2] = 55;
                    rgba[i + 3] = 255;
                }
                else
                {
                    rgba[i + 0] = 200;
                    rgba[i + 1] = 200;
                    rgba[i + 2] = 210;
                    rgba[i + 3] = 255;
                }
            }
        }

        if (texhandle != 0)
            glDeleteTextures(1, &texhandle);
        glGenTextures(1, &texhandle);
        glBindTexture(GL_TEXTURE_2D, texhandle);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgba.data());
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::createBonusSpecular(int checkerSize)
    {
        const int w = 512;
        const int h = 512;
        const int cs = std::max(2, checkerSize);
        size.x = static_cast<float>(w);
        size.y = static_cast<float>(h);

        std::vector<unsigned char> rgb(static_cast<size_t>(w * h * 3));
        for (int y = 0; y < h; ++y)
        {
            for (int x = 0; x < w; ++x)
            {
                const bool bright = (((x / cs) + (y / cs)) & 1) != 0;
                const size_t i = static_cast<size_t>((y * w + x) * 3);
                const unsigned char v = bright ? static_cast<unsigned char>(220) : static_cast<unsigned char>(25);
                rgb[i + 0] = v;
                rgb[i + 1] = v;
                rgb[i + 2] = v;
            }
        }

        if (texhandle != 0)
            glDeleteTextures(1, &texhandle);
        glGenTextures(1, &texhandle);
        glBindTexture(GL_TEXTURE_2D, texhandle);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, rgb.data());
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::createBonusNormal(int checkerSize)
    {
        const int w = 512;
        const int h = 512;
        const int cs = std::max(2, checkerSize);
        size.x = static_cast<float>(w);
        size.y = static_cast<float>(h);

        std::vector<unsigned char> rgb(static_cast<size_t>(w * h * 3));
        for (int y = 0; y < h; ++y)
        {
            for (int x = 0; x < w; ++x)
            {
                const int cx = x / cs;
                const int cy = y / cs;
                const bool raised = (((cx + cy) & 1) == 0);
                float nx = 0.0f;
                float ny = 0.0f;
                float nz = 1.0f;
                if (raised)
                {
                    const float fx = (static_cast<float>(x % cs) / static_cast<float>(cs)) - 0.5f;
                    const float fy = (static_cast<float>(y % cs) / static_cast<float>(cs)) - 0.5f;
                    nx = glm::clamp(fx * 1.8f, -0.95f, 0.95f);
                    ny = glm::clamp(fy * 1.8f, -0.95f, 0.95f);
                    nz = std::sqrt(std::max(0.01f, 1.0f - nx * nx - ny * ny));
                }
                const glm::vec3 enc = glm::normalize(glm::vec3(nx, ny, nz)) * 0.5f + 0.5f;
                const size_t i = static_cast<size_t>((y * w + x) * 3);
                rgb[i + 0] = static_cast<unsigned char>(enc.x * 255.0f);
                rgb[i + 1] = static_cast<unsigned char>(enc.y * 255.0f);
                rgb[i + 2] = static_cast<unsigned char>(enc.z * 255.0f);
            }
        }

        if (texhandle != 0)
            glDeleteTextures(1, &texhandle);
        glGenTextures(1, &texhandle);
        glBindTexture(GL_TEXTURE_2D, texhandle);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, rgb.data());
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    // End Bonus Task

    const GLuint & Texture::getTexHandle() const
    {
        return texhandle;
    }
}
