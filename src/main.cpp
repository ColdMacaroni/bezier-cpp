#include <cctype>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <point.hpp>

namespace raylib
{
    #include <raylib.h>
}

namespace std
{
    #include <unistd.h>
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


#define LERP(a, b, t) (a + t * (b - a))
Point point_lerp(Point pt1, Point pt2, double t)
{
    return Point(LERP(pt1.x, pt2.x, t), LERP(pt1.y, pt2.y, t));
}
#undef LERP


raylib::Vector2 pt_to_v(Point pt)
{
    raylib::Vector2 v;
    v.x = pt.x;
    v.y = pt.y;

    return v;
}


void fit_points(std::vector<Point> &pts, int padding = 20)
{
    /* Makes the points bigger so they fit on the screen better */
    // First get the maximum distance
    if (pts.size() <= 1)
        return ;

    // Get max for x and y
    double max_x = pts[0].x, max_y = pts[0].y;
    for (size_t i = 0; i < pts.size(); i++)
    {
        if (pts[i].x > max_x)
            max_x = pts[i].x;
        if (pts[i].y > max_y)
            max_y = pts[i].y;
    }

    // If both are 0 just exit
    if (!(max_x || max_y))
        return ;

    double factor;
    // Height is bigger
    if (max_y > max_x)
        factor = (W_HEIGHT - padding) / max_y;

    // Width is bigger
    else
        factor = (W_WIDTH - padding) / max_x;

    // Expand em
    for (size_t i = 0; i < pts.size(); i++)
    {
        pts[i] *= factor;
        pts[i] += padding/2;
    }
}


class Bezier
{
    std::vector<Point> points;
    int inc;

    Point calculate(std::vector<Point> pts, double t)
    {
        if (pts.size() == 1)
            return pts[0];

        raylib::DrawCircle(pts[0].x, pts[0].y, 3, raylib::BLUE);
        std::vector<Point> new_pts;
        for (size_t i = 1; i < pts.size(); i++)
        {
            new_pts.push_back(point_lerp(pts[i-1], pts[i], t));

            if (t < double(1))
            {
                raylib::DrawLineEx(pt_to_v(pts[i-1]), pt_to_v(pts[i]), 2,
                                   raylib::ColorAlpha(
                                   raylib::ColorFromHSV(inc * pts.size(), 0.9, 0.7),
                                       0.7
                                ));
                raylib::DrawCircle(pts[i].x, pts[i].y, 3, raylib::BLUE);
            }
        }

        return calculate(new_pts, t);
    }

    public:
    Bezier(std::vector<Point> pts)
    {
        points = pts;
        inc = 360 / pts.size();
    }

    Point get_point(double t)
    {
        // I hate floating point numbers.
        // (double)1 - 1 gives like 2e-23
        if (t < 0 || (t - 1) == ((double)1 - 1))
            throw std::invalid_argument("t must be between 0 and 1");
        return calculate(points, t);
    }

    auto get_points(void)
    {
        return points;
    }

};

int main(int argc, char** argv)
{
    std::vector<Point> points;
    std::string input;

    // Get points until EOF, separated by newline
    while (std::getline(std::cin, input))
        points.push_back(
            Point(string_to_pair(input))
        );

    fit_points(points);

    // Show stuff!
    for (long unsigned i = 0; i < points.size(); i++)
    {
        points[i] = tf_pt(points[i]);
    }

    Bezier bezier = Bezier(points);


    raylib::InitWindow(W_WIDTH, W_HEIGHT, "Bezier Curve");
    raylib::SetTargetFPS(30);

    const float thickness = 2.5;

    double t = 0;
    std::vector<Point> curve;

    while (!raylib::WindowShouldClose())
    {
        raylib::BeginDrawing();
            raylib::ClearBackground(raylib::WHITE);

            for (Point pt : bezier.get_points())
                raylib::DrawCircle(pt.x, pt.y, thickness*2, (raylib::Color){0, 0, 0, 128});

            curve.push_back(bezier.get_point(t));

            if (curve.size() > 1)
                for (size_t i = 1; i < curve.size(); i++)
                    raylib::DrawLineEx(pt_to_v(curve[i-1]), pt_to_v(curve[i]), thickness, raylib::BLUE);

            //raylib::DrawLineEx(pt_to_v(points[0]), pt_to_v(points[1]), thickness, raylib::BLACK);

        raylib::EndDrawing();

        if (t > 1)
        {
            std::sleep(1);
            curve.clear();
            t = 0;
        }
        else
            t += 0.01;
    }

    raylib::CloseWindow();
    return 0;
}
