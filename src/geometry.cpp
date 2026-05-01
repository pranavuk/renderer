#include<iostream>
#include<vector>
#include<cmath>
#include"geometry.h"

void bresenham(int x0, int y0, int x1, int y1,std::vector<Point>& line) {
    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;  // direction in x
    int sy = (y0 < y1) ? 1 : -1;  // direction in y
    int err = dx - dy;
    while (true) {
        line.push_back({x0, y0});
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;   
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
    return;
}