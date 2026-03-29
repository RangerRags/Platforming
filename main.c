#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
int main(void) {
    InitWindow(800, 800, "Platform Game");
    int x=200, y=400;
    int ground=765;
    bool onGround = false;
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
        // 1. reset each frame
        onGround = false;
        ground = 765;

        // 2. input
        if (IsKeyDown(KEY_D)) x += 10;
        if (IsKeyDown(KEY_A)) x -= 10;

        // 3. apply gravity
        if (!onGround) yV += 1;

        // 4. move
        y += yV;

        // 5. platform collision
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (platforms[i][j] == 1) {
                    // top collision
                    if (x+20 >= j*80 && x-20 <= j*80+80 && y+20 >= i*80 && y < i*80) {
                        ground = i*80;
                        y = i*80 - 21;
                        yV = 0;
                        onGround = true;
                    }
                    // side collision (left side of tile)
                    if (x+20 >= j*80 && x < j*80 && y+20 >= i*80 && y-20 <= i*80+80) {
                        x = j*80 - 21;
                    }
                }
            }
        }

        // 6. floor collision
        if (y >= ground) {
            y = ground - 1;
            yV = 0;
            onGround = true;
        }

        // 7. jump (after onGround is known)
        if (IsKeyPressed(KEY_W) && onGround) {
            yV = -15;
        }

        // 8. draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircle(x, y, 20, BLACK);
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (platforms[i][j] == 1) {
                    DrawRectangle(j*80, i*80, 80, 80, BLACK);
                }
            }
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}