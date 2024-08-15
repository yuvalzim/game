#include "include/raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    
    

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    Texture2D playerImage = LoadTexture("WALK.png");

    float frameWidth = (float)(playerImage.width / 8);
    int maxFrames = (int)(playerImage.width / (int)frameWidth);

    int playerX = 0;
    int playerY = screenHeight - playerImage.height;

    float timer = 0.0f;
    int frame = 0;

    bool isRight = true;
    float current_frame_width = frameWidth;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();

            ClearBackground(WHITE);
            timer += GetFrameTime();

            if (!isRight && current_frame_width > 0){
                current_frame_width = -1 * frameWidth;
            }
            if (isRight && current_frame_width < 0){
                current_frame_width = frameWidth;
            }

            DrawTextureRec(
                playerImage,
                (Rectangle){frameWidth * frame, 0, current_frame_width, (float)playerImage.height},
                (Vector2){playerX, playerY},
                RAYWHITE);

            if (IsKeyDown(KEY_W))
            {
                playerY -= 2;
            }
            if (IsKeyDown(KEY_S))
            {
                playerY += 2;
            }
            if (IsKeyDown(KEY_D))
            {
                isRight = true;
                playerX += 2;
                
            }
            if (IsKeyDown(KEY_A))
            {
                isRight = false;
                playerX -= 2;
            }
            if (IsKeyDown(KEY_D) || IsKeyDown(KEY_A))
            {
                if (timer >= 0.2f){
                    timer = 0.0f;
                    frame += 1;
                }
                frame = frame % maxFrames;
            }
        EndDrawing();
        
    }

    
    CloseWindow();        // Close window and OpenGL context

    return 0;
}