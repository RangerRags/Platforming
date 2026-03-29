#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
int main(void) {
    InitWindow(800, 800, "Platform Game");
    int x=200, y=400;
    int ground=765;
    int yV=0;
    SetTargetFPS(60);
    int platforms[10][10]={
        {0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,1},
{0,0,0,0,0,0,0,0,1,1},
{0,0,0,0,0,0,0,1,1,1},
{0,0,0,0,0,0,1,1,1,1},
{0,0,0,0,0,1,1,1,1,1},
{0,0,0,0,1,1,1,1,1,1},
    };


    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_D)) {
            x+=10;
        }
        if (IsKeyDown(KEY_A)) {
            x-=10;
        }
        if (IsKeyPressed(KEY_W)) {
            if (y>ground-25) {
             yV=-15;
            }

        }
        if (y < ground) {
            yV += 1;
        }
        if (y>=ground) {
            y=764;
        }

        for (int i=0;i<10;i++) {
            for (int j=0;j<10;j++) {
                if (platforms[i][j]==1) {
                 //   DrawRectangle(i*80,j*80,80,80,BLACK);
                   // if (x>=i*80-20) {
                     //   x=i*80-21;
                   // }
                    if (x>=i*80-20&&x<=i*80+60&&y>=j*80-20) {
                        ground=j*80-20;
                        y=j*80-21;
                    }
                }
            }
        }
        y+=yV;
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircle(x,y,20,BLACK);
        for (int i=0;i<10;i++) {
            for (int j=0;j<10;j++) {
                if (platforms[i][j]==1) {
                    DrawRectangle(i*80,j*80,80,80,BLACK);
                }
            }
        }
        EndDrawing();
    }


    return 0;
}