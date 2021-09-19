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
        if (std::isdigit(str[i]) || str[i] == '-')
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

Point tf_pt(Point pt)
{
    //pt.x += W_WIDTH / 2;

    //pt.y = (W_HEIGHT / 2) - pt.y;
    pt.y = W_HEIGHT - pt.y;

    return pt;
}

raylib::Vector2 pt_to_v(Point pt)
{
    raylib::Vector2 v;
    v.x = pt.x;
    v.y = pt.y;

    return v;
}

void fit_points(std::vector<Point> &pts, int padding = 10)
{
    /* Makes the points bigger so they fit on the screen better */
    // First get the maximum distance
    if (pts.size() <= 1)
        return ;

    // Get min and max for both x and y to calculate biggest distance
    double min_x, max_x;
    min_x = max_x = pts[0].x;

    double min_y, max_y;
    min_y = max_y = pts[0].y;

    for (unsigned int i = 0; i < pts.size(); i++)
    {
        if (pts[i].x < min_x)
        {
            min_x = pts[i].x;
        }
        else if (pts[i].x > max_x)
        {
            max_x = pts[i].x;
        }

        if (pts[i].y < min_y)
        {
            min_y = pts[i].y;
        }
        else if (pts[i].y > max_y)
        {
            max_y = pts[i].y;
        }
    }
    std::cout << "max, min" << max_x << min_x << "\n";
    double dist_x = max_x - min_x;
    double dist_y = max_y - min_y;

    std::cout << dist_x << "\n";
    std::cout << dist_y << "\n";

    // If the W_* are not equal weird stuff will happen but on mine they'll be a square so /shrug
    double factor;
    if (dist_x >= dist_y)
    {
        factor = ((W_WIDTH - padding)/1)/dist_x;
    }
    else
    {
        factor = ((W_HEIGHT - padding)/1)/dist_y;
    }

    for (unsigned int i = 0; i < pts.size(); i++)
    {
        std::cout << pts[i].x * factor << "\n";
        pts[i] *= factor;
        pts[i] += padding / 4;
    }

}

int main( int argc, char** argv)
{
    std::vector<Point> points;
    std::string input;

    // Get points until EOF, separated by newline
    while (std::getline(std::cin, input))
        points.push_back(
            Point(string_to_pair(input))
        );

    //fit_points(points);

    // Show stuff!
    for (long unsigned i = 0; i < points.size(); i++)
    {
        points[i] = tf_pt(points[i]);
        std::cout << points[i].to_string() << '\n';
    }

    raylib::InitWindow(W_WIDTH, W_HEIGHT, "Bezier Curve");
    raylib::SetTargetFPS(60);

    const float thickness = 2.5;

    while (!raylib::WindowShouldClose())
    {
        raylib::BeginDrawing();
            raylib::ClearBackground(raylib::WHITE);

            raylib::DrawLineEx(pt_to_v(points[0]), pt_to_v(points[1]), thickness, raylib::BLACK);

        raylib::EndDrawing();
    }

    raylib::CloseWindow();
    return 0;
}
