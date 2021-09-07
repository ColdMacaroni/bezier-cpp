#include <iostream>
#include <point.hpp>

typedef point::Point<double> Point;

int main( int argc, char** argv)
{


    return 0;
}

auto
str_xy(std::string &str)
{
    /* https://old.reddit.com/r/learncpp/comments/pinj4p/someone_told_me_my_code_looks_like_c_am_i_taking/hbrb8vs/ */
    auto const comma = str.find(',');
    return std::make_pair( strtod(str.c_str(),nullptr), strtod(str.c_str()+comma+1,nullptr));
}
