#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"

int main(void) {
    InitWindow(800, 800, "Platform Game");
    int x = 200, y = 400;
    int ground = 765;
    bool onGround = false;
    int currentLevel = 1;
    int yV = 0;
    SetTargetFPS(60);

    int platforms[10][10] = {
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

    int platforms2[10][10] = {
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
    };

    while (!WindowShouldClose()) {
        // 1. reset each frame
        onGround = false;
        ground = 765;

        // 2. select active level
        int (*activeMaze)[10] = (currentLevel == 1) ? platforms : platforms2;

        // 3. input
        if (IsKeyDown(KEY_D)) x += 10;
        if (IsKeyDown(KEY_A)) x -= 10;

        // 4. apply gravity
        if (!onGround) yV += 1;

        // 5. move
        y += yV;

        // 6. platform collision (overlap-based)
        for (int row = 0; row < 10; row++) {
            for (int col = 0; col < 10; col++) {
                if (activeMaze[row][col] == 1) {
                    int wallX = col * 80;
                    int wallY = row * 80;

                    if (x + 20 > wallX && x - 20 < wallX + 80 &&
                        y + 20 > wallY && y - 20 < wallY + 80) {

                        int overlapLeft   = (x + 20) - wallX;
                        int overlapRight  = (wallX + 80) - (x - 20);
                        int overlapTop    = (y + 20) - wallY;
                        int overlapBottom = (wallY + 80) - (y - 20);

                        int minOverlap = overlapLeft;
                        if (overlapRight  < minOverlap) minOverlap = overlapRight;
                        if (overlapTop    < minOverlap) minOverlap = overlapTop;
                        if (overlapBottom < minOverlap) minOverlap = overlapBottom;

                        if (minOverlap == overlapLeft) {
                            x = wallX - 20;
                        } else if (minOverlap == overlapRight) {
                            x = wallX + 80 + 20;
                        } else if (minOverlap == overlapTop) {
                            y = wallY - 20;
                            yV = 0;
                            onGround = true;
                        } else {
                            y = wallY + 80 + 20;
                            yV = 0;
                        }
                    }
                }
            }
        }

        // 7. floor collision
        if (y >= ground) {
            y = ground - 1;
            yV = 0;
            onGround = true;
        }

        // 8. screen boundaries
        if (x >= 780) x = 779;
        if (x <= 20)  x = 21;

        // 9. jump
        if (IsKeyPressed(KEY_W) && onGround) {
            yV = -15;
        }

        // 10. level transition
        if (currentLevel == 1 && x >= 779) {
            currentLevel = 2;
            x = 21;
            y = 400;
        }

        // 11. draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircle(x, y, 20, BLACK);
        DrawText(TextFormat("Level: %d  x:%d y:%d", currentLevel, x, y), 10, 10, 20, GREEN);
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (activeMaze[i][j] == 1) {
                    DrawRectangle(j*80, i*80, 80, 80, BLACK);
                }
            }
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}