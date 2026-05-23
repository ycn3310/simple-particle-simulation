#include "raylib.h"
#include "helper.h"

Color randomcolor(int r, int g, int b, int range) {
    int max=255,min=0;
    Color color ={
        GetRandomValue(clamp(r-range, min, max),
                       clamp(r+range, min, max)),
        GetRandomValue(clamp(g-range, min, max),
                       clamp(g+range, min, max)),
        GetRandomValue(clamp(b-range, min, max),
                       clamp(b+range, min, max)),
        255};
    return color;
}

void drawparticals(int num_particals){
    for(int i=0; i<num_particals;i++){
        Particle par = particles[i];
        DrawRectangle(par.x*cell_size,par.y*cell_size,cell_size,cell_size,par.color);
    }
}