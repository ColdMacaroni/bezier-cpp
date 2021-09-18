#include <iostream>
#include <vector>
#include <string>
#include <cctype>

// #include <GL/freeglut.h>
#include <raylib.h>

#include <point.hpp>

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

/*
void init()
{
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(SIZE, SIZE);
    glutInitWindowPosition(200, 50);
    glutCreateWindow("Bezier");
}

void display()
{
    /*
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0,0.4,0.2);
    glPointSize(3.0);

    glBegin(GL_LINES);
    glVertex2d(180, 15);
    glVertex2d(10, 145);

    glFlush();
    */
    /*
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 0.0);

    glColor3f(0, 0, 0);
    glPointSize(50.0);

    glBegin(GL_LINES);
    glVertex2i(0, 0);
    glVertex2i(SIZE, SIZE);
    glEnd();
    glFlush();
}

/*https://stackoverflow.com/a/22374339*/
/*
void resize(int width, int height) {
    glutReshapeWindow(SIZE, SIZE);
}

/**/

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

    InitWindow(SIZE, SIZE, "Bezier Curve");

    /*
    glutInit(&argc,argv);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutMainLoop();
*/
    return 0;
}
