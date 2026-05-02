#pragma once
#include<iostream>
#include<vector>
struct Point2d {
    float x, y;
};
struct Point3d {
    float x, y, z;
    void rotate(float alpha,float beta,float gamma,Point3d pivot);
};
struct Triangle{
    std::vector<Point2d> vertices;
    std::vector<Point2d> perimeter;
    std::vector<Point2d> area;
};
struct Object2d{
    std::vector<Point2d> vertices;
    std::vector<Point2d> edges;
    std::vector<Point2d> area;
    std::vector<std::pair<int,int>> edgepairs;

};
struct Object3d{
    std::vector<Point3d> vertices;
    std::vector<Point3d> edges;
    std::vector<Point3d> volume;
    std::vector<std::pair<int,int>> edgepairs;
    void rotate(float alpha,float beta,float gamma,Point3d pivot);    
};
Point2d project(Point3d p, float fov, int screenW, int screenH);

void bresenham(Point2d a,Point2d b,std::vector<Point2d>& line);
void fill_triangle_area(Triangle& triangle);
bool custom_comparator(Point2d a,Point2d b);
Object2d FlattenObject(const Object3d& cube);
