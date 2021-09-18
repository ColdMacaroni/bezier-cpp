#include <iostream>
#include <vector>
#include <string>
#include <cctype>

#include <GL/freeglut.h>

#include <point.hpp>

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

/* glut */
void init()
{
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);	//Line C
	glutInitWindowSize(640,480);
    glutInitWindowPosition(1000,200);
    glutCreateWindow("Bezier");
}

void display()
{
    glClearColor(1.0,1.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	// gluOrtho2D(0.0,100.0,0,100.0);
	glFlush();
}

/**/

int main( int argc, char** argv)
{
    std::vector<Point> points;
    std::string input = "";

    // Get points until EOF, separated by newline
    while (std::getline(std::cin, input))
        points.push_back(Point(string_to_pair(input)));

    for (long unsigned i = 0; i < points.size(); i++)
        std::cout << points[i].to_string() << '\n';

    glutInit(&argc,argv);			//Line A
        init();					//Line B
        glutDisplayFunc(display);
        glutMainLoop();

    return 0;
}
