#include "grid.h"
#include "raylib.h"

int clamp(int value, int min, int max);
void swap(int ox, int oy, int nx, int ny);
void clear(int *number_particles);
void checkmaterial(int *material_type, int *num_particals);
void grid_coordinates(int *gx, int *gy);