#include<iostream>
#include<vector>
#include<cmath>
#include"geometry.h"
#include<algorithm>

void print_vector(std::vector<int> list){
    for(auto i:list)std::cout<<i<<" ";
    std::cout<<std::endl;
}

void bresenham(Point2d a,Point2d b,std::vector<Point2d>& line) {

    int x0=round(a.x);
    int x1=round(b.x);
    int y0=round(a.y);
    int y1=round(b.y);
    int dx =std::abs(x1 - x0);
    int dy =std::abs(y1 - y0);
    int sx =(x0 < x1) ? 1 : -1;  // direction in x
    int sy =(y0 < y1) ? 1 : -1;  // direction in y
    int err=dx - dy;
    while (true) {
        line.push_back({(float)x0,(float)y0});
        if (x0==x1 && y0==y1) break;
        float e2 = 2 * err;
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

bool custom_comparator(Point2d a,Point2d b){
    if(a.y==b.y)return (a.x<=b.x);
    else return a.y<b.y;
}

void fill_triangle_area(Triangle &triangle){
    std::sort(triangle.perimeter.begin(),triangle.perimeter.end(),custom_comparator);
    int i=0;
    while(true){
        if(i>triangle.perimeter.size()-2)break;
        if(triangle.perimeter[i].y==triangle.perimeter[i+1].y){
            int j=triangle.perimeter[i].x;
            while(j<triangle.perimeter[i+1].x){
                triangle.area.push_back({(float)j,triangle.perimeter[i].y});
                j++;
            }        
                i++;
        }
        else i++;
    }
}


Point2d project(Point3d p, float fov, int screenW, int screenH){
    Point2d p1;
    p1.x=(p.x/p.z)*fov+screenW/2;
    p1.y=(p.y/p.z)*fov+screenH/2;
    return p1;
};

void Point3d::rotate(float alpha,float beta,float gamma,Point3d pivot){
    float x1=x-pivot.x;
    float y1=y-pivot.y;
    float z1=z-pivot.z;
    float x2=x1*(cos(alpha)*cos(beta)) + y1*(cos(alpha)*sin(beta)*sin(gamma) - sin(alpha)*cos(gamma)) + z1*(cos(alpha)*sin(beta)*cos(gamma) + sin(alpha)*sin(gamma));
    float y2=x1*(sin(alpha)*cos(beta)) + y1*(sin(alpha)*sin(beta)*sin(gamma) + cos(alpha)*cos(gamma)) + z1*(sin(alpha)*sin(beta)*cos(gamma) - cos(alpha)*sin(gamma));
    float z2=x1*(-sin(beta)) + y1*(cos(beta)*sin(gamma)) + z1*(cos(beta)*cos(gamma));
    x=x2+pivot.x;
    y=y2+pivot.y;
    z=z2+pivot.z;
}


void Object3d::rotate(float alpha,float beta,float gamma,Point3d pivot){
    for(auto& i:vertices){
        i.rotate(alpha,beta,gamma,pivot);
    }    
}    


Object2d FlattenObject(const Object3d& cube){
    Object2d projected_cube;
    for(auto& i:cube.vertices){
        projected_cube.vertices.push_back(project(i,1000,800,600));
    }
    return projected_cube;
}