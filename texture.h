#pragma once

#include <memory>

#include "utilities.h"


class ITexture
{
public:
    virtual ~ITexture() = default;

    virtual char GetPixel(Point) const = 0;
    virtual void SetPixel(char& pixel, Point point) const = 0;
};

class Texture : public ITexture
{
private:
    Image image_;
    bool repeat_x_ = true;
    bool repeat_y_ = true;

    bool PointInTexture(Point p) const;
public:
    Texture(Image img, bool repeat_x = true, bool repeat_y = true);

    char GetPixel(Point p) const;

    void SetPixel(char& pixel, Point point) const;
};

std::shared_ptr<ITexture> MakeSolidTexture(Size size, char pixel,
    bool repeat_x = true,
    bool repeat_y = true);

std::shared_ptr<ITexture> MakeCheckerTexture(Size size, char pixel1,
    char pixel2, bool repeat_x = true,
    bool repeat_y = true);
