#include "stdlib.h"
#include "updates.h"
#include "particles.h"
#include "grid.h"
#include "render.h"
#include "helper.h"
#include "raylib.h"

void update_sand(Particle *par){
    if(par->y >= grid_height-1)
        return;
    //check down
    if(grid[par->y+1][par->x]== EMPTY){
        move_particle(par,par->x,par->y+1);
    }
    //check down right
    else if (par->x +1 < grid_width && grid[par->y+1][par->x+1]== EMPTY && rand()%2){
        move_particle(par,par->x+1,par->y+1);
    }
    //check down left
    else if (par->x-1 >= 0 && grid[par->y+1][par->x-1] == EMPTY){
        move_particle(par,par->x-1,par->y+1);
    }

    //if down is water
    else if( p[grid[par->y+1][par->x]].type == WATER ){
        swap(par->x,par->y,par->x,par->y+1);
    }
}

void update_water(Particle *par){
    
     //check down
    if(par->y + 1 < grid_height && grid[par->y+1][par->x] == EMPTY){
        move_particle(par, par->x, par->y + 1);
    }
    //check down right
    else if (par->x+1 < grid_width && par->y+1 <grid_height && grid[par->y+1][par->x+1] == EMPTY && rand()%2){
        move_particle(par,par->x+1,par->y+1);
    }
    //check down left
    else if (par->x-1>= 0 && par->y+1<grid_height && grid[par->y+1][par->x-1]==EMPTY){
        move_particle(par,par->x-1,par->y+1);
    }
    //check left
    else if (par->x-1>= 0 && grid[par->y][par->x-1]==EMPTY && rand()%2){
        move_particle(par,par->x-1,par->y);
    }
    //check right
    else if (par->x+1 < grid_width && grid[par->y][par->x+1]==EMPTY){
        move_particle(par,par->x+1,par->y);
    }
}

void update_lava(Particle *par){
    int range = 10;
  
     //check down
    if(par->y+1<grid_height && grid[par->y+1][par->x] == EMPTY){
        move_particle(par, par->x, par->y + 1);
    }
    //check down right
    else if (par->x+1 < grid_width && par->y+1 <grid_height && grid[par->y+1][par->x+1] == EMPTY && rand()%2){
        move_particle(par,par->x+1,par->y+1);
    }
    //check down left
    else if (par->x-1>= 0 && par->y+1<grid_height && grid[par->y+1][par->x-1]==EMPTY){
        move_particle(par,par->x-1,par->y+1);
    }
    //check left
    else if (par->x-1>= 0 && grid[par->y][par->x-1]==EMPTY && rand()%2){
        move_particle(par,par->x-1,par->y);
    }
    //check right
    else if (par->x+1 < grid_width && grid[par->y][par->x+1]==EMPTY){
        move_particle(par,par->x+1,par->y);
    }
    //check down for water

    else if(grid[par->y+1][par->x] != EMPTY && par->y+1<grid_height && p[grid[par->y+1][par->x]].type==WATER){
        p[grid[par->y+1][par->x]].type = STONE;
        p[grid[par->y][par->x]].type = STONE;
        p[grid[par->y+1][par->x]].color = randomcolor(64,64,64,range);
        p[grid[par->y][par->x]].color = randomcolor(64,64,64,range);
    }
    //check up for water
    else if(grid[par->y-1][par->x] != EMPTY && par->y-1>=0 && p[grid[par->y-1][par->x]].type==WATER){
        p[grid[par->y-1][par->x]].type = STONE;
        p[grid[par->y][par->x]].type = STONE;
        p[grid[par->y-1][par->x]].color = randomcolor(64,64,64,range);
        p[grid[par->y][par->x]].color = randomcolor(64,64,64,range);
    }
}