#ifndef MODULE_H_
#define MODULE_H_

#include <vector>
#include "geometry.h"

class Module
{
private:
    std::vector<Vec3f> verts;
    std::vector<std::vector<int>> faces;
public:
    Module(const char *filename);
    ~Module();
    int nverts();
    int nfaces();
    Vec3f vert(int i);
    std::vector<int> face(int idx);
};

#endif