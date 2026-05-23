#include "grid.h"
#include "particles.h"
#include "raylib.h"

int clamp(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

void swap(Particle *a, Particle *b){
    int ax = a->x;
    int ay = a->y;

    a->x = b->x;
    a->y = b->y;

    b->x = ax;
    b->y = ay;

    grid[a->y][a->x] = a - particles;
    grid[b->y][b->x] = b - particles;

}

void clear(int *number_particles){
    for(int i=0; i<*number_particles; i++){
        grid[particles[i].y][particles[i].x]=EMPTY; 
    }
    *number_particles = 0;
}

void checkmaterial(int *material_type, int *number_particles){
    if(IsKeyPressed(KEY_S)){
        *material_type = SAND;
    }
    if(IsKeyPressed(KEY_W)){
        *material_type = WATER;
    }
    if(IsKeyPressed(KEY_T)){
        *material_type = STONE;
    }
    if(IsKeyPressed(KEY_L)){
        *material_type = LAVA;
    }
    if(IsKeyPressed(KEY_C)){
        clear(number_particles);
    }
}

void grid_coordinates(int *gx, int *gy){
    Vector2 mouse = GetMousePosition();
    *gx = mouse.x / cell_size;
    *gy = mouse.y / cell_size;
}