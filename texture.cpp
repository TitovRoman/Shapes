#include <memory>

#include "texture.h"
#include "utilities.h"


bool Texture::PointInTexture(Point p) const
{
    Size img_size = image_.GetSize();
    return p.x >= 0 && p.y >= 0
        && p.x < img_size.width&& p.y < img_size.height;
}


Texture::Texture(Image img, bool repeat_x, bool repeat_y)
    : image_(std::move(img))
    , repeat_x_(repeat_x)
    , repeat_y_(repeat_y)
{

}

char Texture::GetPixel(Point p) const
{
    Size img_size = image_.GetSize();
    if (repeat_x_)
    {
        p.x = std::fmod(p.x, img_size.width);
    }
    if (repeat_y_)
    {
        p.y = std::fmod(p.y, img_size.height);
    }

    if (PointInTexture(p))
    {
        return image_[p.y][p.x];
    }
    else {
        return '\0';
    }
}

void Texture::SetPixel(char& pixel, Point point) const
{
    char pixel_tex = GetPixel(point);
    if (pixel_tex)
    {
        pixel = pixel_tex;
    }
}



std::shared_ptr<ITexture> MakeSolidTexture(Size size, char pixel,
    bool repeat_x, bool repeat_y)
{
    if (repeat_x)
    {
        size.width = 1;
    }
    if (repeat_y)
    {
        size.height = 1;
    }

    Image img(size, pixel);
    return std::make_shared<Texture>(std::move(img), repeat_x, repeat_y);
}

std::shared_ptr<ITexture> MakeCheckerTexture(Size size, char pixel1, char pixel2,
    bool repeat_x, bool repeat_y)
{
    Image img(size);
    for (size_t i = 0; i < size.height; ++i)
    {
        for (size_t j = 0; j < size.width; ++j)
        {
            img[i][j] = (i + j) % 2 ? pixel2 : pixel1;
        }
    }
    return std::make_shared<Texture>(std::move(img), repeat_x, repeat_y);
}
