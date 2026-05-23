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
int num_particals =0;
//the grid with the color of each cell
int grid[grid_height][grid_width];
Color grid_color[grid_height][grid_width];

typedef enum {
    EMPTY = -1,
    SAND = 1,
    STONE = 2,
    WATER = 3,
    LAVA = 4
} material;

typedef struct {
    int x, y;
    unsigned int type;
    Color color;
} Particle;

Particle p[grid_height*grid_width];
char particals[][10]={"sand","stone","water","lava"};



void move_particle(Particle *p, int nx, int ny){
    int temp = grid[p->y][p->x]; 
    grid[p->y][p->x] = -1;
    p->x = nx;
    p->y = ny;
    grid[ny][nx] = temp;
}

void clear(int grid[grid_height][grid_width], Color grid_color[grid_height][grid_width], int *num){
    *num=0;
    for(int i =0; i<grid_height;i++){
        for(int j=0; j<grid_width; j++){
            grid_color[i][j]=BLACK;
            grid[i][j]=-1;
        }
    }
    
}

void swap(int ox, int oy, int nx, int ny){
    int temp = grid[ox][oy];
    grid[ox][oy]=grid[nx][ny];
    grid[nx][ny]=temp;
}

int clamp(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

Color randomcolor(int r, int g, int b, int range) {
    int max=255,min=0;
    Color color ={
        GetRandomValue(clamp(r-range, min, max),
                       clamp(r+range, min, max)),
        GetRandomValue(clamp(g-range, min, max),
                       clamp(g+range, min, max)),
        GetRandomValue(clamp(b-range, min, max),
                       clamp(b+range, min, max)),
        255};
    return color;
}

void drawparticals(){
    for(int i=0; i<num_particals;i++){
        Particle par = p[i];
        DrawRectangle(par.x*cell_size,par.y*cell_size,cell_size,cell_size,par.color);
    }
}

void update_sand(int grid[grid_height][grid_width],Particle *par){
    if(par->y >= grid_height - 1)
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

void update_water(int grid[grid_height][grid_width], int i, int j){
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

void update_lava(int grid[grid_height][grid_width], int i, int j){
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
        clear(grid,grid_color,&num_particals);
    }
}

void grid_coordinates(int *gx, int *gy){
    Vector2 mouse = GetMousePosition();
    *gx = mouse.x / cell_size;
    *gy = mouse.y / cell_size;
}

Particle create_particle(int x, int y,int material_type, Color color){
    Particle p;
    p.x = x;
    p.y = y;
    p.color = color;
    p.type = material_type;
    return p;
}

int main(void){
    for(int i = 0; i < grid_height; i++){
        for(int j = 0; j < grid_width; j++){
            grid[i][j] = -1;
        }
    }
    int material_type = 1;
    InitWindow(screenWidth, screenHeight, "sim");
    SetTargetFPS(FPS);
    
    int v[4][4]={{64,64,64,range},{255,207,92,range},{35,137,218,range},{240,37*GetRandomValue(0,6),15, range+5}};
 
    while(!WindowShouldClose()){
        checkmaterial(&material_type);
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            int gx,gy;
            grid_coordinates(&gx,&gy);

            //placing only when the cell is empty
            if(grid[gy][gx] == -1){
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
                update_sand(grid, wow);
            }
        }
    
        BeginDrawing();
            ClearBackground(BLACK);
            drawparticals();
            DrawText(TextFormat("number of particals: %i",num_particals), 5, 25, 20, LIGHTGRAY);
            DrawText(TextFormat("current partical: %s", particals[material_type-1]), 5, 50, 20, LIGHTGRAY);
            DrawFPS(5, 5);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}