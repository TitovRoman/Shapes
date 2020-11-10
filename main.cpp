#include <iostream>
#include <memory>

#include "window.h"
#include "shape.h"
#include "texture.h"
#include "utilities.h"

void test_1()
{
    using namespace std;

    auto texture_plus = MakeSolidTexture({ 10, 10 }, '+');
    auto texture_minus = MakeSolidTexture({ 10, 10 }, '-');
    auto texture_checker = MakeCheckerTexture({ 10, 10 }, '1', '2');

    shared_ptr<Shape> square = make_shared<Square>(Point{ 2, 2 }, 3);
    square->SetTexture(texture_minus);
    shared_ptr<Shape> circle = make_shared<Circle>(Point{ 20, 5 }, 3);
    circle->SetTexture(texture_plus);

    shared_ptr<Shape> ellipse = make_shared<Ellipse>(Point{ 25, 10 }, Point{ 40, 3 }, 10);

    shared_ptr<Shape> triangle = make_shared<Triangle>(Point{ 10, 5 }, Point{ 0, 10 }, Point{ 20, 15 });
    triangle->SetTexture(texture_checker);

    shared_ptr<Shape> rectangle = make_shared<Rectangle>(Point{ 6, 2 }, Size{ 6, 3 });

    Window win;
    win.SetSize({ 45, 15 });
    win.Draw(square);
    win.Draw(triangle);
    win.Draw(circle);
    win.Draw(ellipse);
    win.Draw(rectangle);
    win.Print(std::cout);
}

void test_2()
{
    using namespace std;

    auto texture_clear = MakeSolidTexture({ 10, 10 }, ' ');
    auto texture_Xx = MakeCheckerTexture({ 10, 10 }, 'X', 'x');
    auto texture_plus = MakeSolidTexture({ 10, 10 }, '+');

    shared_ptr<Shape> circle = make_shared<Circle>(Point{ 10, 9 }, 7);
    circle->SetTexture(texture_Xx);
    shared_ptr<Shape> circle2 = make_shared<Circle>(Point{ 13, 9 }, 5);
    circle2->SetTexture(texture_plus);

    shared_ptr<Shape> circle3 = make_shared<Circle>(Point{ 35, 9 }, 7);
    circle3->SetTexture(texture_Xx);
    shared_ptr<Shape> circle4 = make_shared<Circle>(Point{ 32, 9 }, 5);
    circle4->SetTexture(texture_clear);

    Window win;
    win.SetSize({ 45, 19 });

    win.Draw(circle);
    win.Draw(circle2);
    win.Draw(circle3);
    win.Draw(circle4);

    win.Print(std::cout);
}

int main()
{
    test_1();
    test_2();
}

