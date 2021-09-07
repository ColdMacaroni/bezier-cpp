#ifndef POINT_STRUCT_H
#define POINT_STRUCT_H 1
#include <string>
namespace point
{
    template<class c_T>
    struct Point
    {
        c_T x, y;

        Point(c_T _x, c_T _y)
        {
            this->x = _x;
            this->y = _y;
        };

        std::string to_string(void)
        {
            /* (x, y) */
            std::string output = "(";

            output.append(std::to_string(this->x));
            output.append(", ");
            output.append(std::to_string(this->y));
            output.append(")");

            return output;
        };

        /* -- Operators -- */
        /* Math */
        Point<c_T> operator+(c_T other)
        {
            return Point<c_T>(this->x + other, this->y + other);
        };

        Point<c_T> operator-(c_T other)
        {
            return Point<c_T>(this->x + other, this->y + other);
        };

        Point<c_T> operator*(c_T other)
        {
            return Point<c_T>(this->x * other, this->y * other);
        };

        Point<c_T> operator/(c_T other)
        {
            return Point<c_T>(this->x / other, this->y / other);
        };

        /* Comparison */
        bool operator==(const Point other)
        {
            return (other.x == this->x && other.y == this->y);
        };

        bool operator>(const Point other)
        {
            return (other.x > this->x && other.y > this->y);
        };

        bool operator<(const Point other)
        {
            return (other.x < this->x && other.y < this->y);
        };

        bool operator>=(const Point other)
        {
            return (other.x >= this->x && other.y >= this->y);
        };

        bool operator<=(const Point other)
        {
            return (other.x <= this->x && other.y <= this->y);
        };
    };
}
#endif
