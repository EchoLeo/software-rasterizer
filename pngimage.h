#ifndef PNGIMAGE_H_
#define PNGIMAGE_H_

struct Color
{
    union
    {
        unsigned int val;
        struct
        {
            unsigned char r, g, b, a;
        };
        unsigned char c[4];
    };

    Color() : val(0) {}
};


class PNGImage
{
public:
    enum Format
    {
        NONE = 0, RGB = 3, RGBA = 4
    };

    PNGImage();
    PNGImage(int w, int h, Format f);
    PNGImage(const PNGImage &img);
    bool read_png_file(const char *filename);
    bool write_png_file(const char *filename);
    Color get(int x, int y);
    int get_width();
    int get_height();
    int get_format();
    bool set(int x, int y, Color c);
    PNGImage & operator =(const PNGImage &img);
    void clear();
    ~PNGImage();

protected:
    unsigned char *data;
    int width = 0;
    int height = 0;
    int format = NONE;
    void print();
};




#endif