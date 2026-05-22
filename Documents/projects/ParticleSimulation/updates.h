#ifndef UPDATES_H
#define UPDATES_H
#endif

#include "particles.h"

#define screenWidth 1290
#define screenHeight 720

#define cell_size 10
#define grid_height (screenHeight/cell_size)
#define grid_width (screenWidth/cell_size)

void update_sand(Particle *par);
void update_water(Particle *par);
void update_lava(Particle *par);
