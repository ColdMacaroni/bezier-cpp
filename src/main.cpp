#include <iostream>
#include <vector>
#include <string>
#include <cctype>

#include <point.hpp>

namespace raylib
{
    #include <raylib.h>
}

#define W_WIDTH 640
#define W_HEIGHT 640

typedef point::Point<double> Point;

auto
string_to_pair(std::string str)
{
    double x{};
    double y{};
    double *cur = &x;

    size_t off = 0;

    for (size_t i = 0; i < str.size(); i++)
        if (std::isdigit(str[i]))
        {
            // Convert to num
            *cur = std::stod(str.substr(i, str.size()), &off);

            // Skip the whole converted num
            i += off;

            // now eval the next num
            cur = &y;
        }

    return std::make_pair(x, y);
}

Point tl_to_c(Point pt)
{
    pt.x += W_WIDTH / 2;

    pt.y *= -1;
    pt.y += W_HEIGHT / 2;

    return pt;
}

raylib::Vector2 pt_to_v(Point pt)
{
    raylib::Vector2 v;
    v.x = pt.x;
    v.y = pt.y;
    return v;
}

int main( int argc, char** argv)
{
    std::vector<Point> points;
    std::string input;

    // Get points until EOF, separated by newline
    while (std::getline(std::cin, input))
        points.push_back(Point(string_to_pair(input)));

    // Show stuff!
    for (long unsigned i = 0; i < points.size(); i++)
        std::cout << points[i].to_string() << '\n';

    raylib::InitWindow(W_WIDTH, W_HEIGHT, "Bezier Curve");
    raylib::SetTargetFPS(60);

    const float thickness = 2.5;

    while (!raylib::WindowShouldClose())
    {
        raylib::BeginDrawing();
            raylib::ClearBackground(raylib::WHITE);
            raylib::Vector2 v = {4, 5};
            DrawLineEx((raylib::Vector2){0, 0}, (raylib::Vector2){10, 20}, thickness, raylib::BLACK);

        raylib::EndDrawing();
    }

    raylib::CloseWindow();
    return 0;
}
