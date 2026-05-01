#include<iostream>
#include<vector>
struct Point {
    int x, y;
};


void bresenham(int x0, int y0, int x1, int y1,std::vector<Point>& line);
