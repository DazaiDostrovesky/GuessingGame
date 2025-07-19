#include <raylib.h>

enum GameState { TITLE_SCREEN, GAME_SCREEN };
GameState currentState = TITLE_SCREEN;

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Test");

    Rectangle startButton = { screenWidth/2 - 150, screenHeight/2 - 50, 300, 100 };
    Color buttonColor = GREEN;

    SetTargetFPS(60);

    while (!WindowShouldClose()) 
    {
        if (currentState == TITLE_SCREEN and IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mouseCoordinates = GetMousePosition();
            if (CheckCollisionPointRec(mouseCoordinates, startButton)) 
            {
                currentState = GAME_SCREEN;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (currentState == TITLE_SCREEN)
        {
            DrawText("The Guessing Game", screenWidth/2 - MeasureText("The Guessing Game", 40)/2, 100, 40, BLACK);
            DrawRectangleRec(startButton, buttonColor);
            DrawText("Start", 
                    startButton.x + startButton.width/2 - MeasureText("Start", 30)/2,
                    startButton.y + startButton.height/2 - 15,
                    30, BLACK);
        }
        else if (currentState == GAME_SCREEN)
        {
            DrawText("This project is still in development", 150, 300, 30, DARKGRAY);
        }
            
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
