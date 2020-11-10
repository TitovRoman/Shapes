#pragma once

#include <algorithm>

#include "shape.h"


void Shape::Draw(Image& img) const
{
    Size img_size = img.GetSize();

    double start_width = std::max<double>(0, position_bbox_.x);
    double finish_width = std::min<double>(img_size.width
        , position_bbox_.x + size_bbox_.width);
    double start_height = std::max<double>(0, position_bbox_.y);
    double finish_height = std::min<double>(img_size.height
        , position_bbox_.y + size_bbox_.height);

    Point p;
    for (p.x = start_width; p.x < finish_width; ++p.x)
    {
        for (p.y = start_height; p.y < finish_height; ++p.y)
        {
            if (Check(p))
            {
                char pixel = '.';
                if (texture_)
                {
                    texture_->SetPixel(pixel, p);
                }
                img[p.y][p.x] = pixel;
            }
        }
    }
}



Circle::Circle(Point center, double radius) : center_(center)
, radius_(radius)
{
    Validation(radius);
    UpdateBoundingBox();
}

bool Circle::Check(Point point) const
{
    return GetDistance(point, center_) <= radius_ + 0.2;
}

void Circle::SetRadius(double radius)
{
    Validation(radius);
    radius_ = radius;
    UpdateBoundingBox();
}

double Circle::GetRadius() const
{
    return radius_;
}

void Circle::SetPointCenter(Point center)
{
    center_ = center;
    UpdateBoundingBox();
}

Point Circle::GetPointCenter() const
{
    return center_;
}

void Circle::UpdateBoundingBox() {
    SetPosition({ center_.x - radius_, center_.y - radius_ });
    SetSize({ radius_ * 2 + 1, radius_ * 2 + 1 });
}

void Circle::Validation(double radius) const
{
    if (radius < 0)
    {
        throw std::invalid_argument("Circle radius < 0");
    }
}


void Ellipse::Validation(Point f_1, Point f_2, double semi_major) const
{
    if (GetDistance(f_1, f_2) >= semi_major * 2)
    {
        throw std::invalid_argument("Ellipse: F_1*F_2 >= 2 * radius");
    }
}

Ellipse::Ellipse(Point focus_1, Point focus_2, double radius)
    : focus_1_(focus_1)
    , focus_2_(focus_2)
    , semi_major_(radius)
{
    Validation(focus_1, focus_2, radius);
    UpdateBoundingBox();
}

bool Ellipse::Check(Point point) const
{
    auto distance1 = GetDistance(point, focus_1_);
    auto distance2 = GetDistance(point, focus_2_);
    return (distance1 + distance2) <= semi_major_ * 2;
}

void Ellipse::SetRadius(double radius)
{
    Validation(focus_1_, focus_2_, radius);
    semi_major_ = radius;
    UpdateBoundingBox();
}

double Ellipse::GetRadius() const
{
    return semi_major_;
}

void Ellipse::SetFocus_1(Point center)
{
    Validation(center, focus_2_, semi_major_);
    focus_1_ = center;
    UpdateBoundingBox();
}

Point Ellipse::GetFocus_1() const
{
    return focus_1_;
}

void Ellipse::SetFocus_2(Point center) {
    Validation(focus_1_, center, semi_major_);
    focus_2_ = center;
    UpdateBoundingBox();
}

Point Ellipse::GetFocus_2() const
{
    return focus_2_;
}

void Ellipse::UpdateBoundingBox()
{
    double left_top_x = std::min(focus_1_.x, focus_2_.x) - semi_major_;
    double left_top_y = std::min(focus_1_.y, focus_2_.y) - semi_major_;
    double right_bottom_x = std::max(focus_1_.x, focus_2_.x) + semi_major_;
    double right_bottom_y = std::max(focus_1_.y, focus_2_.y) + semi_major_;

    SetPosition({ left_top_x, left_top_y });
    SetSize({ right_bottom_x - left_top_x + 1,
             right_bottom_y - left_top_y + 1 });
}


void Square::Validation(double side) const
{
    if (side < 0) {
        throw std::invalid_argument("Square: side < 0");
    }
}

Square::Square(Point point, double side) : point_(point), side_length_(side)
{
    Validation(side);
    UpdateBoundingBox();
}

bool Square::Check(Point) const
{
    return true;
}

void Square::UpdateBoundingBox()
{
    SetPosition(point_);
    SetSize({ side_length_, side_length_ });
}

void Square::SetSizeSquare(double side)
{
    Validation(side);
    side_length_ = side;
    UpdateBoundingBox();
}

Size Square::GetSizeSquare() const {
    return { side_length_, side_length_ };
}

void Square::SetPoint(Point p)
{
    point_ = p;
    UpdateBoundingBox();
}
Point Square::GetPoint() const
{
    return point_;
}

Rectangle::Rectangle(Point point, Size size) : point_(point), size_(size)
{
    UpdateBoundingBox();
}

bool Rectangle::Check(Point) const
{
    return true;
}

void Rectangle::UpdateBoundingBox()
{
    SetPosition(point_);
    SetSize(size_);
}

void Rectangle::SetSizeRect(Size size)
{
    size_ = size;
    UpdateBoundingBox();
}
Size Rectangle::GetSizeRect() const {
    return size_;
}

void Rectangle::SetPoint(Point p)
{
    point_ = p;
    UpdateBoundingBox();
}
Point Rectangle::GetPoint() const
{
    return point_;
}

Triangle::Triangle(Point p1, Point p2, Point p3) : points({ p1, p2, p3 })
{
    Validation();
    UpdateVectors();
    UpdateBoundingBox();
}

bool Triangle::Check(Point p) const
{
    Point vec_p = GetVector(p);
    double m = (vec_p.x * vec_p2_p1_.y - vec_p2_p1_.x * vec_p.y)
        / (vec_p3_p1_.x * vec_p2_p1_.y - vec_p2_p1_.x * vec_p3_p1_.y);
    if (m >= 0 && m <= 1)
    {
        double n = (vec_p.x - m * vec_p3_p1_.x) / vec_p2_p1_.x;
        if (n >= 0 && (m + n) <= 1)
        {
            return true;
        }
    }
    return false;
}

void Triangle::Validation() const
{
    Validation(points[0], points[1], points[2]);
}

void Triangle::Validation(Point p1, Point p2, Point p3) const
{
    if (!((p3.y - p1.y) * (p2.x - p1.x) - (p3.x - p1.x) * (p2.y - p1.y)))
    {
        throw std::invalid_argument("Triangle: Three points on one line");
    }
}

void Triangle::UpdateVectors()
{
    vec_p2_p1_ = GetVector(points[1]);
    vec_p3_p1_ = GetVector(points[2]);
    if (vec_p2_p1_.x == 0.0)
    {
        std::swap(vec_p2_p1_, vec_p3_p1_);
    }
}

void Triangle::SetPoint(Point p, size_t ind)
{
    if (ind > 2)
    {
        throw std::invalid_argument("SetPointTriangle: ind > 2");
    }
    Point old_value = points[ind];
    points[ind] = p;
    try
    {
        Validation();
    }
    catch (std::invalid_argument)
    {
        points[ind] = old_value;
        throw;
    }
}

Point Triangle::GetPoint(size_t ind)
{
    if (ind > 2)
    {
        throw std::invalid_argument("SetPointTriangle: ind > 2");
    }
    return points[ind];
}

Point Triangle::GetVector(Point p) const
{
    return { p.x - points[0].x, p.y - points[0].y };
}

void Triangle::UpdateBoundingBox()
{
    auto [left_top_x, right_bottom_x] = std::minmax_element(
        points.begin(),
        points.end(),
        [](const Point& lhs, const Point& rhs) {return lhs.x < rhs.x; });
    auto [left_top_y, right_bottom_y] = std::minmax_element(
        points.begin(),
        points.end(),
        [](const Point& lhs, const Point& rhs) {return lhs.y < rhs.y; });

    SetPosition({ left_top_x->x, left_top_y->y });
    SetSize({ right_bottom_x->x - left_top_x->x + 1,
             right_bottom_y->y - left_top_y->y + 1 });
}


