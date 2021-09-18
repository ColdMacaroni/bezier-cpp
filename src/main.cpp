#include <iostream>
#include <vector>
#include <string>
#include <cctype>

#include <point.hpp>

namespace raylib
{
    #include <raylib.h>
}

#define SIZE 640

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

    raylib::InitWindow(SIZE, SIZE, "Bezier Curve");

    /*
    glutInit(&argc,argv);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutMainLoop();
*/
    return 0;
}
