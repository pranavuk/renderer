#include<iostream>
#include <SDL2/SDL.h>
#include<vector>
#include<cmath>
#include"geometry.h"
int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    // 2. Create a window — fill in the blanks
    SDL_Window* window = SDL_CreateWindow("renderer",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,0);
    SDL_Renderer* renderer= SDL_CreateRenderer(window,-1,0);
    
    bool running = true;
    Point2d a = {400, 100};
    Point2d b = {100, 500};
    Point2d c = {700, 500};
    Object3d cube;
    cube.vertices = {
    {-1,-1, 14}, { 1,-1, 14}, { 1, 1, 14}, {-1, 1, 14},
    {-1,-1, 16}, { 1,-1, 16}, { 1, 1, 16}, {-1, 1, 16}
    };
    cube.edgepairs.push_back({0,1});
    cube.edgepairs.push_back({1,2});
    cube.edgepairs.push_back({2,3});
    cube.edgepairs.push_back({3,0});
    cube.edgepairs.push_back({4,5});
    cube.edgepairs.push_back({5,6});
    cube.edgepairs.push_back({6,7});
    cube.edgepairs.push_back({7,4});
    cube.edgepairs.push_back({0,4});
    cube.edgepairs.push_back({1,5});
    cube.edgepairs.push_back({2,6});
    cube.edgepairs.push_back({3,7});

    int xrf=0;
    while (running) {
        xrf++;
        if(xrf==100){
            xrf=0;
            cube.rotate(0,0.1,0,{0,0,10});
        }
        SDL_Event event;
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer,200,0,0,255);
        Object2d projected_cube=FlattenObject(cube);
        std::vector<Point2d> mesh;
        for(const auto& i:projected_cube.vertices){
            SDL_RenderDrawPoint(renderer,i.x,i.y);
        }
        for(const auto& i:cube.edgepairs){
            bresenham(projected_cube.vertices[i.first],projected_cube.vertices[i.second],mesh);
        }
        for(const auto& i:mesh){
            SDL_RenderDrawPoint(renderer,i.x,i.y);
        }
        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        //SDL_Delay(16);  // ~60 FPS
    }

    // 4. Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}