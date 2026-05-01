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
    Point a={500,400};
    Point b={200,200};
    Point c={600,500};
    std::vector<Point> line;
    bresenham(a.x,a.y,b.x,b.y,line);
    bresenham(c.x,c.y,b.x,b.y,line);
    bresenham(c.x,c.y,a.x,a.y,line);

    while (running) {
        SDL_Event event;
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer,200,200,200,255);
        //SDL_RenderDrawPoint(renderer,(int)x%100+100,200);
        for(const auto& i:line){
            SDL_RenderDrawPoint(renderer,i.x,i.y);
        }
        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
    }

    // 4. Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}