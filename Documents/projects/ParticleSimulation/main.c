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
char particals[][10]={"sand","water","stone","lava"};

int main(void){
    for(int i = 0; i < grid_height; i++){
        for(int j = 0; j < grid_width; j++){
            grid[i][j] = EMPTY;
        }
    }
    int material_type = SAND;
    InitWindow(screenWidth, screenHeight, "sim");
    SetTargetFPS(FPS);
    
    int v[4][4]={{255,207,92,range},//sand
                {35,137,218,range},//water
                {64,64,64,range},//stone
                {240,37*GetRandomValue(0,6),15, range+5}//lava 
    };
    
    while(!WindowShouldClose()){
        checkmaterial(&material_type,&num_particals);
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            int gx,gy;
            grid_coordinates(&gx,&gy);

            //placing only when the cell is empty
            if(grid[gy][gx] == EMPTY){
                grid[gy][gx]=num_particals;
                p[num_particals++] = create_particle(gx,gy,material_type,randomcolor(v[material_type][0],
                                                                                     v[material_type][1],
                                                                                     v[material_type][2],
                                                                                     v[material_type][3]));
      
            }
        
        }
        for(int i=0;i<num_particals;i++){
            Particle *wow = &p[i];
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
            DrawText(TextFormat("current partical: %s", particals[material_type-1]), 5, 50, 20, LIGHTGRAY);
            DrawFPS(5, 5);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}