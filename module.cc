#include "module.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

Module::Module(const char *filename)
{
    std::ifstream in;
    in.open(filename, std::ifstream::in);
    if (in.fail()) return;
    std::string line;
    while (!in.eof())
    {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v "))
        {
            iss >> trash;
            Vec3f v;
            for (int i = 0; i < 3; i++)
            {
                iss >> v.raw[i];
            }
            verts.push_back(v);
        }
        else if(!line.compare(0, 2, "f "))
        {
            std::vector<int> f;
            int itrash, idx;
			iss >> trash;
            while (iss >> idx >> trash >> itrash >> trash >> itrash)
            {
                idx--;
                f.push_back(idx);
            }
            faces.push_back(f);
        }
    }
    in.close();
    std::cerr << "# v# " << verts.size() << " f# " << faces.size() << std::endl;
}

Module::~Module()
{}

int Module::nverts()
{
    return (int)verts.size();
}

int Module::nfaces()
{
    return (int)faces.size();
}

std::vector<int> Module::face(int idx)
{
    return faces[idx];
}

Vec3f Module::vert(int i)
{
    return verts[i];
}