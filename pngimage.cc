#include "pngimage.h"
#include "svpng.inc"
#include <cstring>
#include <iostream>

PNGImage::PNGImage() : data(nullptr), width(0), height(0), format(NONE) {}

PNGImage::PNGImage(int w, int h, Format f) : width(w), height(h), format(f) 
{
    auto size = width * height * format;
    data = new unsigned char[size];
    memset(data, 0, size);
}

PNGImage::PNGImage(const PNGImage &img)
{
    width = img.width;
    height = img.height;
    format = img.format;
    auto size = width * height * format;
    data = new unsigned char[size];
    memcpy(data, img.data, size);
}

bool PNGImage::read_png_file(const char *filename)
{
    return false;
}

bool PNGImage::write_png_file(const char *filename)
{
    FILE *fp = fopen(filename, "wb");
    svpng(fp, width, height, data, format == RGBA ? 1:0);
    fclose(fp);
    return true;
}

void PNGImage::print()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = 0; k < format; k++)
            {
                std::cout << data[(i*width + j)*format + k] << ' ';
            }
        }
    }
}

PNGImage::~PNGImage()
{
    if (data)
    {
        delete [] data;
    }
}

Color PNGImage::get(int w, int h)
{
    Color pixel;
    for(auto i = 0; i < format; i++)
    {
        pixel.c[i] = data[h*height + w + i];
    }
    return pixel;
}

bool PNGImage::set(int w, int h, Color c)
{
    for (auto i = 0; i < format; i++)
    {
        data[(h*width + w)*format + i] = c.c[i];
    }
    return true;
}

int PNGImage::get_width()
{
    return width;
}

int PNGImage::get_height()
{
    return height;
}

int PNGImage::get_format()
{
    return format;
}

void PNGImage::clear()
{
    memset(data, 0, width * height * format);
}

PNGImage & PNGImage::operator =(const PNGImage &img)
{
    if (this != &img)
    {
        if (data)
        {
            delete [] data;
        }
        width = img.width;
        height = img.height;
        format = img.format;
        auto size = width * height * format;
        data = new unsigned char[size];
        memcpy(data, img.data, size);
    }
    return *this;
}