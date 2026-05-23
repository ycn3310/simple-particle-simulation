#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "raylib.h"

#define screenWidth 1290
#define screenHeight 720
#define FPS 180


#define cell_size 10
#define grid_height (screenHeight/cell_size)
#define grid_width (screenWidth/cell_size)
#define gravity 10

int range = 10;
int num_sand =0;
//the grid with the color of each cell
unsigned int grid[grid_height][grid_width] = {0};
Color grid_color[grid_height][grid_width];

typedef struct {
    int x, y;
    unsigned int type;
    Color color;
    bool active;
} Particle;

Particle p[grid_height*grid_width];
char particals[][10]={"sand","stone","water","lava"};

void clear(unsigned int grid[grid_height][grid_width], Color grid_color[grid_height][grid_width], int *num){
    *num=0;
    for(int i =0; i<grid_height;i++){
        for(int j=0; j<grid_width; j++){
            grid_color[i][j]=BLACK;
            grid[i][j]=0;
        }
    }
    
}

int clamp(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

Color randomcolor(int r, int g, int b, int range) {
    int max=255,min=0;
    Color color ={
        GetRandomValue(clamp(r+range, min, max),
                       clamp(r-range, min, max)),
        GetRandomValue(clamp(g+range, min, max),
                       clamp(g-range, min, max)),
        GetRandomValue(clamp(b+range, min, max),
                       clamp(b-range, min, max)),
        255};
    return color;
}

void drawparticals(unsigned int grid[grid_height][grid_width], Color grid_color[grid_height][grid_width]){
    for(int i =0; i<grid_height; i++){
        for(int j=0; j<grid_width; j++){
            if(grid[i][j]==1){
                DrawRectangle(j*cell_size, i*cell_size, cell_size, cell_size, grid_color[i][j]);
            } else if(grid[i][j]==2){
                DrawRectangle(j*cell_size, i*cell_size, cell_size, cell_size, grid_color[i][j]);
            } else if(grid[i][j]==3){
                DrawRectangle(j*cell_size, i*cell_size, cell_size, cell_size, BLUE);
            } else if(grid[i][j]==4){
                DrawRectangle(j*cell_size, i*cell_size, cell_size, cell_size, grid_color[i][j]);
            } 
        }
    }
}

void checksand(unsigned int grid[grid_height][grid_width],Color grid_color[grid_height][grid_width], int i, int j){
    //check down
    if(grid[i+1][j]==0){
        grid[i][j]=0;
        grid[i+1][j]=1;

        grid_color[i+1][j]=grid_color[i][j];
        grid_color[i][j]=BLACK;
        
    }
    //check down right
    else if (j <grid_width-1 && grid[i+1][j+1]==0 && rand()%2){
        grid[i][j]=0;
        grid[i+1][j+1]=1;

        grid_color[i+1][j+1]=grid_color[i][j];
        grid_color[i][j]=BLACK;
    }
    //check down left
    else if (j>0 && grid[i+1][j-1]==0  ){
        grid[i][j]=0;
        grid[i+1][j-1]=1;

        grid_color[i+1][j-1]=grid_color[i][j];
        grid_color[i][j]=BLACK;
    }

    //if down is water
    else if(grid[i+1][j]==3){
        grid[i][j]=3;
        grid[i+1][j]=1;

        Color temp = grid_color[i+1][j];
        grid_color[i+1][j]=grid_color[i][j];
        grid_color[i][j]=temp;
        
    }
}

void checkwater(unsigned int grid[grid_height][grid_width], int i, int j){
     //check down
    if(grid[i+1][j]==0){
        grid[i][j]=0;
        grid[i+1][j]=3;
    }
    //check down right
    else if (j <grid_width-1 && grid[i+1][j+1]==0 && rand()%2){
        grid[i][j]=0;
        grid[i+1][j+1]=3;
    }
    //check down left
    else if (j>0 && grid[i+1][j-1]==0){
        grid[i][j]=0;
        grid[i+1][j-1]=3;
    }
    //check left
    else if (j>0 && grid[i][j-1]==0 && rand()%2){
        grid[i][j]=0;
        grid[i][j-1]=3;
    }
    //check right
    else if (j>0 && grid[i][j+1]==0){
        grid[i][j]=0;
        grid[i][j+1]=3;
    }
}

void checklava(unsigned int grid[grid_height][grid_width], int i, int j){
     //check down
    if(grid[i+1][j]==0){
        grid[i][j]=0;
        grid[i+1][j]=4;

        grid_color[i+1][j]=grid_color[i][j];
        grid_color[i][j]=BLACK;
    }
    //check down right
    else if (j <grid_width-1 && grid[i+1][j+1]==0 && rand()%2){
        grid[i][j]=0;
        grid[i+1][j+1]=4;

        grid_color[i+1][j+1]=grid_color[i][j];
        grid_color[i][j]=BLACK;
    }
    //check down left
    else if (j>0 && grid[i+1][j-1]==0){
        grid[i][j]=0;
        grid[i+1][j-1]=4;

        grid_color[i+1][j-1]=grid_color[i][j];
        grid_color[i][j]=BLACK;
    }
    //check left
    else if (j>0 && grid[i][j-1]==0 && rand()%2){
        grid[i][j]=0;
        grid[i][j-1]=4;

        grid_color[i][j-1]=grid_color[i][j];
        grid_color[i][j]=BLACK;
    }
    //check right
    else if (j>0 && grid[i][j+1]==0){
        grid[i][j]=0;
        grid[i][j+1]=4;

        grid_color[i][j+1]=grid_color[i][j];
        grid_color[i][j]=BLACK;
    }

    else if(grid[i+1][j]==3){
        grid[i][j]=2;
        grid[i+1][j]=2;
        
        grid_color[i+1][j]=randomcolor(64,64,64,range);;
        grid_color[i][j]=randomcolor(64,64,64,range);;
        
    }

    else if(grid[i-1][j]==3){
        grid[i][j]=2;
        grid[i-1][j]=2;
        
        grid_color[i-1][j]=randomcolor(64,64,64,range);;
        grid_color[i][j]=randomcolor(64,64,64,range);;
        
    }
}

void checkmaterial(int *material_type){
    if(IsKeyPressed(KEY_O)){
        *material_type = 1;
    }
    if(IsKeyPressed(KEY_P)){
        *material_type = 2;
    }
    if(IsKeyPressed(KEY_I)){
        *material_type = 3;
    }
    if(IsKeyPressed(KEY_L)){
        *material_type = 4;
    }
    if(IsKeyPressed(KEY_C)){
        clear(grid,grid_color,&num_sand);
    }
}

void grid_coordinates(int *gx, int *gy){
    Vector2 mouse = GetMousePosition();
    *gx = mouse.x / cell_size;
    *gy = mouse.y / cell_size;
}

Particle create_particle(int x, int y,unsigned int material_type, Color color){
    Particle p;
    p.x = x;
    p.y = y;
    p.color = color;
    p.type = material_type;
    p.active = true;
    return p;
}
int main(void){
    
    int material_type = 1;

    //initializing the window and the fps
    InitWindow(screenWidth, screenHeight, "sim");
    SetTargetFPS(FPS);

    //game loop
    while(!WindowShouldClose()){
        checkmaterial(&material_type);
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            int gx,gy;
            grid_coordinates(&gx,&gy);

            //placing only when the cell is empty
            if(grid[gy][gx] == 0){
                grid[gy][gx]=material_type;
                if(material_type == 1){
                    grid_color[gy][gx] = randomcolor(255,207,92,range);
                } else if(material_type ==2){
                    grid_color[gy][gx] = randomcolor(64,64,64,range);
                } else if (material_type == 4){
                    grid_color[gy][gx] = randomcolor(240,37*GetRandomValue(0,6),15, range+5);
                }
                
                num_sand++;
            }
        
        }

        //checking each cell
        for(int i =grid_height-2; i>=0; i--){
            for(int j=0; j<grid_width; j++){
                if(grid[i][j]==1){
                    checksand(grid,grid_color, i, j);
                } 
                if(grid[i][j]==3){
                   checkwater(grid, i, j);
                }
                if(grid[i][j]==4){
                    checklava(grid, i, j);
                }
            }
            
        }

        BeginDrawing();
            ClearBackground(BLACK);
            drawparticals(grid, grid_color);
            DrawText(TextFormat("number of particals: %i",num_sand), 5, 25, 20, LIGHTGRAY);
            DrawText(TextFormat("current partical: %s", particals[material_type-1]), 5, 50, 20, LIGHTGRAY);
            DrawFPS(5, 5);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}