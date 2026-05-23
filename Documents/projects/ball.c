#include "raylib.h"
#include <math.h>
#include <stdio.h>

#define screen_width 1600
#define screen_height 900
#define FPS 120
#define gravity 6.647/100

typedef struct {
    float x , y, z;
    float size;
    float mass;
    float velocity_x, velocity_y, velocity_z;
    Color color;
} planet;

planet make_planet(float x, float y,float z, float vx, float vy,float vz, float mass,float size, Color color){
    planet p;
    p.x = x;
    p.y = y;
    p.z = z;
    p.velocity_x = vx;
    p.velocity_y = vy;
    p.velocity_z = vz;
    p.mass = mass;
    p.size = size;
    p.color = color;

    return p;
}

float distance;
float force;
float dt;
float dx, dy, dz;
float Fx, Fy, Fz;
const int num_pln = 200;


int main(void){
    planet planets[num_pln];
    //initializing the camera
    Camera3D camera = {0};
    camera.position = (Vector3){ 100.0f, 5.0f, 7.0f }; // where you are
    camera.target   = (Vector3){ 0.0f, 0.0f, 0.0f }; // looking at origin
    camera.up       = (Vector3){ 0.0f, 1.0f, 0.0f }; // up direction
    camera.fovy     = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    //initializing the window and the music
    InitWindow(screen_width, screen_height, "render ball");
    InitAudioDevice(); 
    DisableCursor();
    SetTargetFPS(FPS);
    Music music = LoadMusicStream("C:\\Users\\chbe9 chbe9\\Music\\Cosmic City - Space Music For Cosmic Drift.mp3");
    PlayMusicStream(music);
    
    //setting up the planets


    for(int i = 0; i<num_pln; i++){
        float x,y,z;
        do{ 
            x = GetRandomValue(-50, 50)/1.0f;
            y = GetRandomValue(-50, 50)/1.0f;
            z = GetRandomValue(-50, 50)/1.0f;
        } while(sqrt(x*x +y*y + z*z)>50.0f);
        Color c = {
            GetRandomValue(10,255),
            GetRandomValue(10,255),
            GetRandomValue(10,255),
            255
        };
        planets[i]=make_planet(x, y, z, 0, 0, 0, 10, 0.5, c);
    }
    
    while(!WindowShouldClose()){
        UpdateMusicStream(music);
        SetMusicVolume(music, 0.5f); 

        dt = 2.0f/FPS;

        //calculating force
        for(int i =0; i<num_pln; i++){
            for(int j = i +1; j<num_pln; j++){
                if(i==j) continue;
                dx = planets[j].x - planets[i].x;
                dy = planets[j].y - planets[i].y;
                dz = planets[j].z - planets[i].z;

                distance = sqrt(dx*dx + dy*dy + dz*dz);
                if (distance < 1.0) distance = 5.0;

                Fx = gravity * planets[i].mass * planets[j].mass * dx / (distance*distance*distance);
                Fy = gravity * planets[i].mass * planets[j].mass * dy / (distance*distance*distance);
                Fz = gravity * planets[i].mass * planets[j].mass * dz / (distance*distance*distance);

                if (CheckCollisionSpheres(
                    (Vector3){planets[i].x, planets[i].y, planets[i].z}, planets[i].size,
                    (Vector3){planets[j].x, planets[j].y, planets[j].z}, planets[j].size))
                {
                    Vector3 n = {
                        planets[i].x - planets[j].x,
                        planets[i].y - planets[j].y,
                        planets[i].z - planets[j].z
                    };
                    Vector3 v_rel = {
                        planets[i].velocity_x - planets[j].velocity_x,
                        planets[i].velocity_y - planets[j].velocity_y,
                        planets[i].velocity_z - planets[j].velocity_z
                    };
                    float dist = sqrt(n.x*n.x + n.y*n.y + n.z*n.z);
                    // normalize
                    n.x /= dist;
                    n.y /= dist;
                    n.z /= dist;
                    float velAlongNormal = v_rel.x*n.x + v_rel.y*n.y + v_rel.z*n.z;
                    if (velAlongNormal > 0) break;
                    float e = 0.1f; // elasticity (1 = perfect bounce, 0 = no bounce)

                    float h = -(1 + e) * velAlongNormal;
                    h /= (1/planets[i].mass + 1/planets[j].mass);
                    Vector3 impulse = {
                        h * n.x,
                        h * n.y,
                        h * n.z
                    };

                    planets[i].velocity_x += impulse.x / planets[i].mass;
                    planets[i].velocity_y += impulse.y / planets[i].mass;
                    planets[i].velocity_z += impulse.z / planets[i].mass;

                    planets[j].velocity_x -= impulse.x / planets[j].mass;
                    planets[j].velocity_y -= impulse.y / planets[j].mass;
                    planets[j].velocity_z -= impulse.z / planets[j].mass;

                    float overlap = (planets[i].size + planets[j].size) - dist;

                    if (overlap > 0) {
                        float correction = overlap / 2.0f;

                        planets[i].x += n.x * correction;
                        planets[i].y += n.y * correction;
                        planets[i].z += n.z * correction;

                        planets[j].x -= n.x * correction;
                        planets[j].y -= n.y * correction;
                        planets[j].z -= n.z * correction;
                    }
                }

                planets[i].velocity_x += Fx  / planets[i].mass * dt;
                planets[i].velocity_y += Fy  / planets[i].mass * dt;
                planets[i].velocity_z += Fz  / planets[i].mass * dt;

                planets[j].velocity_x -= Fx  / planets[j].mass * dt;
                planets[j].velocity_y -= Fy  / planets[j].mass * dt;
                planets[j].velocity_z -= Fz  / planets[j].mass * dt;
            }
        }

        //updating the position
        for(int i =0; i<num_pln; i++){
            planets[i].x += planets[i].velocity_x * dt;
            planets[i].y += planets[i].velocity_y * dt;
            planets[i].z += planets[i].velocity_z * dt;
        }
        

        UpdateCamera(&camera, CAMERA_FREE);
        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode3D(camera);
                for(int i =0; i<num_pln; i++){
                    DrawSphere((Vector3){planets[i].x, planets[i].y, planets[i].z}, planets[i].size, planets[i].color);
                }
                
                DrawGrid(100, 2.0f);
            EndMode3D();
            DrawFPS(20,20);
        EndDrawing();
    }
    
    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}