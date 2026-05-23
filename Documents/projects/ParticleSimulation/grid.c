#define screenWidth 1290
#define screenHeight 720

#define cell_size 10
#define grid_height (screenHeight/cell_size)
#define grid_width (screenWidth/cell_size)

#include "particles.h"

int grid[grid_height][grid_width];
Particle particles[grid_height*grid_width];