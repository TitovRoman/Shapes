#pragma once

#include <vector>
#include <string>
#include <cmath>
#include <stdexcept>

struct Size
{
    Size(double w = 0, double h = 0) : width(w), height(h)
    {
        if (w < 0 || h < 0)
        {
            throw std::invalid_argument("Circle radius < 0");
        }
    }
    double width;
    double height;
};

struct Point
{
    double x;
    double y;
};

class Image
{
private:
    std::vector<std::string> img;
public:
    Image(Size size, char def_char = ' ') : img(size.height,
        std::string(size.width, def_char))
    {}

    Size GetSize() const
    {
        double width = static_cast<double>(img.size() > 0 ? img[0].size() : 0);
        double height = static_cast<double>(img.size());
        return { width, height };
    }

    auto begin()
    {
        return img.begin();
    }

    auto end()
    {
        return img.end();
    }

    std::string& operator [](size_t ind)
    {
        return img[ind];
    }

    const std::string& operator [](size_t ind) const
    {
        return img[ind];
    }
};

inline double GetDistance(Point point_1, Point point_2)
{
    return std::hypot(point_1.x - point_2.x, point_1.y - point_2.y);
}
