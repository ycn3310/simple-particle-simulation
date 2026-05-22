#ifndef PARTICLES_H
#define PARTICLES_H

#include "raylib.h"
#include "particles.h"

typedef enum {
    EMPTY = -1,
    SAND,
    WATER,
    STONE,
    LAVA
} MaterialType;

typedef struct {
    int x, y;
    MaterialType type;
    Color color;
} Particle;

void move_particle(Particle *p, int nx, int ny);
Particle create_particle(int x, int y,int material_type, Color color);

#endif