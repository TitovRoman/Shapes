#pragma once

#include <memory>
#include <array>

#include "utilities.h"
#include "texture.h"


class IDraw
{
public:
    virtual void Draw(Image&) const = 0;

    virtual ~IDraw() = default;
};


class Shape : public IDraw
{
protected:
    Point position_bbox_;
    Size size_bbox_;
    std::shared_ptr<ITexture> texture_;

    virtual void SetPosition(Point point) {
        position_bbox_ = point;
    }

    virtual void SetSize(Size s) {
        size_bbox_ = s;
    }

    virtual void UpdateBoundingBox() = 0;

    virtual bool Check(Point) const = 0;

public:
    virtual std::shared_ptr<Shape> Clone() const = 0;

    virtual Point GetPosition() const
    {
        return position_bbox_;
    }

    virtual Size GetSize() const
    {
        return size_bbox_;
    }

    virtual void SetTexture(std::shared_ptr<ITexture> texture)
    {
        texture_ = texture;
    }

    virtual std::shared_ptr<ITexture> GetTexture() const
    {
        return texture_;
    }

    void Draw(Image& img) const override;
};

class Circle : public Shape
{
public:
    Circle(Point center, double radius);

    bool Check(Point point) const override;

    void SetRadius(double radius);
    double GetRadius() const;

    void SetPointCenter(Point center);
    Point GetPointCenter() const;

    std::shared_ptr<Shape> Clone() const override;

private:
    Point center_;
    double radius_;

    void UpdateBoundingBox() override;

    void Validation(double radius) const;
};

class Ellipse : public Shape
{
public:
    Ellipse(Point focus_1, Point focus_2, double radius);

    bool Check(Point point) const override;

    void SetRadius(double radius);
    double GetRadius() const;

    void SetFocus_1(Point center);
    Point GetFocus_1() const;

    void SetFocus_2(Point center);
    Point GetFocus_2() const;

    std::shared_ptr<Shape> Clone() const override;

private:
    Point focus_1_;
    Point focus_2_;
    double semi_major_;

    void UpdateBoundingBox() override;
    void Validation(Point f_1, Point f_2, double semi_major) const;
};

class Square : public Shape
{
public:
    Square(Point point, double side);

    bool Check(Point) const override;

    void SetSizeSquare(double size);
    Size GetSizeSquare() const;

    void SetPoint(Point p);
    Point GetPoint() const;

    std::shared_ptr<Shape> Clone() const override;

private:
    Point point_;
    double side_length_;

    void UpdateBoundingBox() override;
    void Validation(double side) const;
};

class Rectangle : public Shape
{
public:
    Rectangle(Point point, Size size);

    bool Check(Point) const override;

    void SetSizeRect(Size size);
    Size GetSizeRect() const;

    void SetPoint(Point p);
    Point GetPoint() const;

    std::shared_ptr<Shape> Clone() const override;

private:
    Point point_;
    Size size_;

    void UpdateBoundingBox() override;
};

class Triangle : public Shape
{
public:
    Triangle(Point p1, Point p2, Point p3);

    void SetPoint(Point p, size_t ind);
    Point GetPoint(size_t ind);

    bool Check(Point p) const override;

    std::shared_ptr<Shape> Clone() const override;
private:
    std::array<Point, 3> points;
    Point vec_p2_p1_, vec_p3_p1_;

    void Validation(Point p1, Point p2, Point p3) const;
    void Validation() const;
    void UpdateVectors();

    Point GetVector(Point p) const;

    void UpdateBoundingBox() override;
};
