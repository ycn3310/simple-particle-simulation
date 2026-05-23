#ifndef GRID_H
#define GRID_H
#endif

#include "particles.h"

#define screenWidth 1290
#define screenHeight 720

#define cell_size 10
#define grid_height (screenHeight/cell_size)
#define grid_width (screenWidth/cell_size)

extern int grid[grid_height][grid_width];
extern Particle particles[grid_height*grid_width];