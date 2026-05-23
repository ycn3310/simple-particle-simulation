#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "raylib.h"
#include "particles.h"
#include "updates.h"
#include "grid.h"
#include "render.h"
#include "helper.h"

#define FPS 180

const int range = 10;
int num_particals =0;
char particles_name[][10]={"sand","water","stone","lava"};
int gx,gy;
int material_type = SAND;

int main(void){
    InitWindow(screenWidth, screenHeight, "ParticleSim");
    SetTargetFPS(FPS);

    int color_palette[][4]={{255,207,92,range},//sand
                {35,137,218,range},//water
                {64,64,64,range},//stone
                {240,37*GetRandomValue(1,6),15, range+5}//lava 
    };

    for(int i = 0; i < grid_height; i++){
        for(int j = 0; j < grid_width; j++){
            grid[i][j] = EMPTY;
        }
    }
    
    while(!WindowShouldClose()){
        checkmaterial(&material_type,&num_particals);

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
            grid_coordinates(&gx,&gy);
            if(gx >= 0 && gx < grid_width && gy >= 0 && gy < grid_height){
            //placing only when the cell is empty
                if(grid[gy][gx] == EMPTY){
                    grid[gy][gx]=num_particals;
                    particles[num_particals++] = create_particle(gx,gy,material_type,randomcolor(color_palette[material_type][0]
                                                                                                ,color_palette[material_type][1]
                                                                                                ,color_palette[material_type][2]
                                                                                                ,color_palette[material_type][3]));
                }
            }
        }

        for(int i=0;i<num_particals;i++){
            Particle *wow = &particles[i];
            if(wow->type == SAND){
                update_sand(wow);
            }
            else if(wow->type == WATER){
                update_water(wow);
            }
            else if(wow->type == LAVA){
                update_lava(wow);
            }
        }
    
        BeginDrawing();
            ClearBackground(BLACK);
            drawparticals(num_particals);
            DrawText(TextFormat("number of particals: %i",num_particals), 5, 25, 20, LIGHTGRAY);
            DrawText(TextFormat("current partical: %s", particles_name[material_type]), 5, 50, 20, LIGHTGRAY);
            DrawFPS(5, 5);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}