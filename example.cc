#include "pngimage.h"
#include <algorithm>
#include "module.h"
#include <vector>
#include "geometry.h"

const int width = 1024;
const int height = 1024;
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
    PNGImage img(width, height, PNGImage::Format::RGB);
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
    PNGImage img(width, height, PNGImage::Format::RGBA);
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

void line1(int x0, int y0, int x1, int y1, PNGImage &img, const Color &c)
{
    for (float t = 0; t < 1; t += 0.01)
    {
        int x = x0*(1-t) + x1*t;
        int y = y0*(1.-t) + y1*t;
        img.set(x, y, c);
    }
}

void line2(int x0, int y0, int x1, int y1, PNGImage &img, const Color &c)
{
    for (int x = x0; x <= x1; x++)
    {
        float t = (x - x0)/(float)(x1 - x0);
        int y = y0*(1-t) + y1*t;
        img.set(x, y, c);
    }
}

void line3(int x0, int y0, int x1, int y1, PNGImage &img, const Color &c)
{
    bool steep = false;

    if ( std::abs(x0-x1) < std::abs(y0-y1) )
    {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0 > x1)
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    for (int x = x0; x <= x1; x++)
    {
        float t = (x-x0) / (float)(x1-x0);
        int y = y0*(1-t) + y1*t;
        if (steep)
        {
            img.set(y, x, c);
        }
        else
        {
            img.set(x, y, c);
        }
    }
}

void line4(int x0, int y0, int x1, int y1, PNGImage &img, const Color &c)
{
    bool steep = false;
    if (std::abs(x0-x1) < std::abs(y0-y1))
    {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0 > x1)
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    float derror = std::abs( (y1-y0)/(float)(x1-x0) );
    float error = 0.f;
    int y = y0;
    for (int x = x0; x <= x1; x++)
    {
        if (steep)
        {
            img.set(y, x, c);
        }
        else
        {
            img.set(x, y, c);
        }
        
        error += derror;
        if (error >= 0.5f)
        {
            y += (y1>y0?1:-1);
            error -= 1;
        }
    }
}

void line5(int x0, int y0, int x1, int y1, PNGImage &img, const Color &c)
{
    bool steep = false;
    if (std::abs(x0-x1) < std::abs(y0-y1))
    {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0 > x1)
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int dx = std::abs(x1 - x0);
    int derror = std::abs( (y1-y0) ) * 2;
    int error = 0;
    int y = y0;
    for (int x = x0; x <= x1; x++)
    {
        if (steep)
        {
            img.set(y, x, c);
        }
        else
        {
            img.set(x, y, c);
        }
        
        error += derror;
        if (error >= dx)
        {
            y += (y1>y0?1:-1);
            error -= 2*dx;
        }
    }
}

void line5(Vec2i v0, Vec2i v1, PNGImage &img, const Color &c)
{
    line5(v0.x, v0.y, v1.x, v1.y, img, c);
}

void triangle(Vec2i v0, Vec2i v1, Vec2i v2, PNGImage &img, const Color &c)
{
    line5(v0, v1, img, c);
    line5(v1, v2, img, c);
    line5(v2, v0, img, c);
}

void test_line()
{
    PNGImage img(width, height, PNGImage::Format::RGB);
    line5(13, 20, 80, 40, img, white);
    line5(20, 13, 40, 80, img, red); 
    line5(80, 40, 13, 20, img, red);
    line5(30, 40, 30, 80, img, red);
    line5(30, 40, 80, 40, img, red);

    img.write_png_file("line.png");
}

void test_module()
{
    PNGImage img(width, height, PNGImage::Format::RGB);
    Module module("./obj/african_head.obj");

    for (int i = 0; i < module.nfaces(); i++)
    {
        std::vector<int> face = module.face(i);
        for (int j = 0; j < 3; j++)
        {
            Vec3f v0 = module.vert(face[j]);
            Vec3f v1 = module.vert(face[(j+1) % 3]);
            int x0 = (v0.x+1.)*width/2.; 
            int y0 = (v0.y+1.)*height/2.; 
            int x1 = (v1.x+1.)*width/2.; 
            int y1 = (v1.y+1.)*height/2.;
            line5(x0, y0, x1, y1, img, white);
        }
    }

    img.write_png_file("african_head.png");
}

void test_triangle()
{
    PNGImage img(width, height, PNGImage::Format::RGB);

    Vec2i t0[3] = {Vec2i(10, 70),   Vec2i(50, 160),  Vec2i(70, 80)}; 
    Vec2i t1[3] = {Vec2i(180, 50),  Vec2i(150, 1),   Vec2i(70, 180)}; 
    Vec2i t2[3] = {Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180)}; 
    triangle(t0[0], t0[1], t0[2], img, red); 
    triangle(t1[0], t1[1], t1[2], img, white); 
    triangle(t2[0], t2[1], t2[2], img, green);

    img.write_png_file("triangle.png");
}

void fill_triangle(Vec2i v0, Vec2i v1, Vec2i v2, PNGImage &img, const Color &c)
{
    if ( v0.y > v1.y ) std::swap(v0, v1);
    if ( v0.y > v2.y ) std::swap(v0, v2);
    if ( v1.y > v2.y ) std::swap(v1, v2);

    int total_height = v2.y - v0.y;
    int up_segment = v2.y - v1.y + 1;
    int down_segment = v1.y - v0.y + 1;
    for (int y = v0.y; y <= v1.y; y++)
    {
        float alpha = (y-v0.y)/(float)(down_segment);
        float beta = (y-v0.y)/(float)(total_height);
        Vec2i A = v0 + (v1-v0)*alpha;
        Vec2i B = v0 + (v2-v0)*beta;
        if (A.x > B.x)
            std::swap(A, B);
        for (int x = A.x; x <= B.x; x++)
        {
            img.set(x, y, c);
        }
    }

    for (int y = v2.y; y > v1.y; --y)
    {
        float alpha = (v2.y-y)/(float)(up_segment);
        float beta = (v2.y-y)/(float)(total_height);
        Vec2i A = v2 + (v1-v2)*alpha;
        Vec2i B = v2 + (v0-v2)*beta;
        if (A.x > B.x)
            std::swap(A, B);
        for (int x = A.x; x <= B.x; x++)
        {
            img.set(x, y, c);
        }
    }
}

void fill_triangle2(Vec2i v0, Vec2i v1, Vec2i v2, PNGImage &img, const Color &c)
{
    if ( v0.y > v1.y ) std::swap(v0, v1);
    if ( v0.y > v2.y ) std::swap(v0, v2);
    if ( v1.y > v2.y ) std::swap(v1, v2);

    int total_height = v2.y - v0.y;
    int up_segment = v2.y - v1.y + 1;
    int down_segment = v1.y - v0.y + 1;
    for (int y = v0.y; y <= v2.y; y++)
    {
        float alpha, beta;
        Vec2i A, B;
        if (y <= v1.y)
        {
            alpha = (y-v0.y)/(float)(down_segment);
            beta = (y-v0.y)/(float)(total_height);
            A = v0 + (v1-v0)*alpha;
            B = v0 + (v2-v0)*beta;
        }
        else
        {
            alpha = (v2.y-y)/(float)(up_segment);
            beta = (v2.y-y)/(float)(total_height);
            A = v2 + (v1-v2)*alpha;
            B = v2 + (v0-v2)*beta;
        }
        if (A.x > B.x)
            std::swap(A, B);
        for (int x = A.x; x <= B.x; x++)
        {
            img.set(x, y, c);
        }
    }
}

void test_file_triangle()
{
    PNGImage img(width, height, PNGImage::Format::RGB);

    Vec2i t0[3] = {Vec2i(10, 70),   Vec2i(50, 160),  Vec2i(70, 80)}; 
    Vec2i t1[3] = {Vec2i(180, 50),  Vec2i(150, 1),   Vec2i(70, 180)}; 
    Vec2i t2[3] = {Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180)}; 
    fill_triangle2(t0[0], t0[1], t0[2], img, red); 
    fill_triangle2(t1[0], t1[1], t1[2], img, white); 
    fill_triangle2(t2[0], t2[1], t2[2], img, green);

    img.write_png_file("file_triangle.png");
}

int main()
{
    // test_rgb();
    // test_rgba();
    test_img_rgb();
    test_img_rgba();
    test_line();
    test_module();
    test_triangle();
    test_file_triangle();
    

    return 0;
}