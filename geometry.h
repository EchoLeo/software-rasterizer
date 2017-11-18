#ifndef GEOMETRY_H_
#define GEOMETRY_H_

template <class t> struct Vec2
{
    union
    {
        struct { t u, v; };
        struct { t x, y; };
        t raw[2];
    };
    Vec2() : u(0), v(0) {}
    Vec2(t u_, t v_) : u(u_), v(v_) {}
};

template <class t> struct Vec3
{
    union
    {
        struct { t ivert, iuv, inorm; };
        struct { t x, y, z; };
        t raw[3];
    };
    Vec3() : x(0), y(0), z(0) {}
    Vec3(t x_, t y_, t z_) : x(x_), y(y_), z(z_) {}
};

typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;
typedef Vec3<float> Vec3f;
typedef Vec3<int> Vec3i;

#endif