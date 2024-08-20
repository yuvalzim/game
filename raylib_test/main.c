#include <stdio.h>
#include "include/raylib.h"

const int screenWidth = 800;
const int screenHeight = 450;

struct player
{
    int x, y;
    double verticalVelocity, verticalAcceleration;
    bool isRight;
    Texture2D image;
};

struct player initializePlayer(int playerStartY, Texture2D playerImage)
{
    struct player Player;
    Player.x = 0;
    Player.y = playerStartY;
    Player.image = playerImage;
    return Player;
}

int main(void)
{
    
    InitWindow(screenWidth, screenHeight, "Game");

    Texture2D backGroundImage = LoadTexture("bg.png");
    Texture2D playerImage = LoadTexture("WALK.png");


    const int playerStartY = screenHeight - playerImage.height/1.15;

    struct player Player = initializePlayer(playerStartY, playerImage);
    
    float frameWidth = (float)(playerImage.width / 8);
    int maxFrames = (int)(playerImage.width / (int)frameWidth);

    float timer = 0.0f;
    int frame = 0;

    float current_frame_width = frameWidth;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        timer += GetFrameTime();

        if (!Player.isRight && current_frame_width > 0){
            current_frame_width = -1 * frameWidth;
        }
        if (Player.isRight && current_frame_width < 0){
            current_frame_width = frameWidth;
        }

        if (IsKeyDown(KEY_D))
        {
            Player.isRight = true;
            Player.x += 3;   
        }
        if (IsKeyDown(KEY_A))
        {
            Player.isRight = false;
            Player.x -= 3;
        }
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_A))
        {
            if (timer >= 0.2f){
                timer = 0.0f;
                frame += 1;
            }
            frame = frame % maxFrames;
        }
        else{
            frame = 0;
        }

        if (IsKeyPressed(KEY_SPACE))
        {
            Player.verticalVelocity = -7.5;
            Player.verticalAcceleration = 0.25;
        }
        
        

        Player.y += (int)Player.verticalVelocity;
        Player.verticalVelocity += Player.verticalAcceleration;

        if (Player.y >= playerStartY){
            Player.y = playerStartY;
            Player.verticalVelocity = 0;
            Player.verticalAcceleration = 0;
        }

        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTexture(backGroundImage, 0, 0, WHITE);

            DrawTextureRec(
                playerImage,
                (Rectangle){frameWidth * frame, 0, current_frame_width, (float)playerImage.height},
                (Vector2){Player.x, Player.y},
                RAYWHITE);

        EndDrawing();
        
    }

    
    CloseWindow();        // Close window and OpenGL context

    return 0;
}