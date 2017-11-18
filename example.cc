#include "pngimage.h"

const int size = 256;
const Color white = Color(255, 255, 255, 255);
const Color red = Color(255, 0, 0, 255);
const Color green = Color(0, 255, 0, 255);
const Color blue = Color(0, 0, 255, 255);

// void test_rgb()
// {
//     unsigned char rgb[256 * 256 * 3], *p = rgb;
//     unsigned x, y;
//     /*
//      *FILE *fopen( const char *filename, const char *mode );
//      * @param mode
//      *  "r" "w" "a" "r+" "w+" "a+"
//      *  with the mode specifiers above the file is open as a
//      *  text file. in order to open a file as a binary file,
//      *  a "b" character has to be included in the mode string.
//      *  the new standard adds a new standard subspecifier("x"),
//      *  that can be appened to any "w" specifier. this subspecifier
//      *  forces the function to fail if the file exists, instead
//      *  of overwritting it. 
//      **/
//     FILE *fp = fopen("rgb.png", "wb");
//     for (y = 0; y < 256; y++)
//     {
//         for (x = 0; x < 256; x++)
//         {
//             *p++ = static_cast<unsigned char>(x);       /* R */
//             *p++ = static_cast<unsigned char>(y);       /* G */
//             *p++ = 128;                                 /* B */
//         }
//     }
//     svpng(fp, 256, 256, rgb, 0);
//     fclose(fp);
// }

// void test_rgba()
// {
//     unsigned char rgba[256 * 256 * 4], *p = rgba;
//     unsigned x, y;
//     FILE *fp = fopen("rgba.png", "wb");
//     for (y = 0; y < 256; y++)
//     {
//         for (x = 0; x < 256; x++)
//         {
//             *p++ = static_cast<unsigned char>(x);           /* R */
//             *p++ = static_cast<unsigned char>(y);           /* G */
//             *p++ = 128;                                     /* B */
//             *p++ = static_cast<unsigned char>((x+y) / 2);   /* A */
//         }
//     }
//     svpng(fp, 256, 256, rgba, 1);
//     fclose(fp);
// }

void test_img_rgb()
{
    PNGImage img(size, size, PNGImage::Format::RGB);
    unsigned w = img.get_width(), h = img.get_height();
    for (unsigned i = 0; i < h; i++)
    {
        for (unsigned j = 0; j < w; j++)
        {
			Color pixel;
            pixel.r = static_cast<unsigned char>(j);
            pixel.g = static_cast<unsigned char>(i);
            pixel.b = 128;
            img.set(j, i, pixel);
        }
    }
    img.write_png_file("img_rgb.png");
}

void test_img_rgba()
{
    PNGImage img(size, size, PNGImage::Format::RGBA);
    unsigned w = img.get_width(), h = img.get_height();
    for (unsigned i = 0; i < h; i++)
    {
        for (unsigned j = 0; j < w; j++)
        {
			Color pixel;
            pixel.r = static_cast<unsigned char>(j);
            pixel.g = static_cast<unsigned char>(i);
            pixel.b = 128;
            pixel.a = static_cast<unsigned char>((i+j) / 2);
            img.set(j, i, pixel);
        }
    }
    img.write_png_file("img_rgba.png");
}

void line(int x0, int y0, int x1, int y1, PNGImage &img, const Color &c)
{
    for (int x = x0; x <= x1; x++)
    {
        float t = (x - x0)/(float)(x1 - x0);
        int y = y0*(1-t) + y1*t;
        img.set(x, y, c);
    }
}

int main()
{
    // test_rgb();
    // test_rgba();
    // test_img_rgb();
    // test_img_rgba();
    PNGImage img(size, size, PNGImage::Format::RGB);
    line(13, 20, 80, 40, img, white);
    line(20, 13, 40, 80, img, red); 
    line(80, 40, 13, 20, img, red);
    img.write_png_file("line.png");
    return 0;
}