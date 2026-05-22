#include "particles.h"
#include "grid.h"
#include "raylib.h"

void move_particle(Particle *p, int nx, int ny){
    int temp = grid[p->y][p->x]; 
    grid[p->y][p->x] = -1;
    p->x = nx;
    p->y = ny;
    grid[ny][nx] = temp;
}

Particle create_particle(int x, int y,int material_type, Color color){
    Particle p;
    p.x = x;
    p.y = y;
    p.color = color;
    p.type = material_type;
    return p;
}