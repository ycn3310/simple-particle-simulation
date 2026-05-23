#include "raylib.h"
#include "math.h"
#include <string.h>
#include <stdio.h>

#define screenWidth 540
#define screenHeight 960

#define gravity 1000

typedef struct {
    float x , y;
    float size;
    float mass;
    float velocity_x, velocity_y;
    Color color;
} planet;

planet make_planet(float x, float y, float vx, float vy, float mass,float size, Color color){
    planet p;
    p.x = x;
    p.y = y;
    p.velocity_x = vx;
    p.velocity_y = vy;
    p.mass = mass;
    p.size = size;
    p.color = color;

    return p;
}

int main(void)
{   
    planet planet1, planet2;
    float distance;
    float force;
    float dt;
    int FPS = 60;
    float dx, dy;


    planet1 = make_planet(screenWidth/2, screenHeight/2, 0, 0, 100000, 200, WHITE);
    planet2 = make_planet(screenWidth/2, screenHeight/2 + 200 , 0, sqrt(gravity * planet1.mass/200), 30, 10,WHITE);

    dt = 1.0f / FPS;
    
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(FPS);     
    
    while (!WindowShouldClose())    
    {   
        dx = planet2.x - planet1.x;
        dy = planet2.y - planet1.y;

        distance = sqrt( (dx)*(dx) + (dy)*(dy) );
        if (distance < 1.0) distance = 1.0;
        force = gravity * (planet1.mass * planet2.mass)/(distance*distance);

        planet1.velocity_x += (force * dx / distance) / planet1.mass * dt;
        planet1.velocity_y += (force * dy / distance) / planet1.mass * dt;

        planet2.velocity_x -= (force * dx / distance) / planet2.mass * dt;
        planet2.velocity_y -= (force * dy / distance) / planet2.mass * dt;

        planet1.x += planet1.velocity_x * dt;
        planet1.y += planet1.velocity_y * dt;
        planet2.x += planet2.velocity_x * dt;
        planet2.y += planet2.velocity_y * dt;

        float velocity1 = sqrt(planet1.velocity_x*planet1.velocity_x + planet1.velocity_y*planet1.velocity_y);
        float velocity2 = sqrt(planet2.velocity_x*planet2.velocity_x + planet2.velocity_y*planet2.velocity_y);

        char display_distance[1028], display_velocity1 [1028], display_velocity2 [1028];
        float rounded = distance * 10;

        sprintf(display_distance, "distance: %.1f", floor(rounded)/10);
        sprintf(display_velocity1, "speed: %.2f", velocity1);
        sprintf(display_velocity2, "speed: %.2f", velocity2);

        BeginDrawing();

            ClearBackground(BLACK);

            DrawCircle(planet1.x, planet1.y, planet1.size, planet1.color);
            DrawCircle(planet2.x, planet2.y, planet2.size, planet2.color);
            DrawText(display_distance, 10, 10, 20,RAYWHITE);
            DrawText(display_velocity1, planet1.x + 85, planet1.y - 85, 20, RAYWHITE);
            DrawText(display_velocity2, planet2.x + 55, planet2.y - 55, 20, RAYWHITE);
            

        EndDrawing();
       
    }
    CloseWindow();        

    return 0;
}