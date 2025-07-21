#include <raylib.h>

enum GameState { TITLE_SCREEN, GAME_SCREEN, DIFFICULTY1, DIFFICULTY2, DIFFICULTY3 };
GameState currentState = TITLE_SCREEN;

int main()
{
    const int screenWidth = 1024;
    const int screenHeight = 768;
    InitWindow(screenWidth, screenHeight, "Test");

    Rectangle startButton = { screenWidth/2 - 150, screenHeight/2 - 50, 300, 100 };
    Rectangle difficulty1 = { screenWidth/2 - 150, screenHeight/2 - 50, 300, 100 };
    Rectangle difficulty2 = { screenWidth/2 - 150, screenHeight/2 + 100, 300, 100 };
    Rectangle difficulty3 = { screenWidth/2 - 150, screenHeight/2 + 250, 300, 100 };
    
    Color buttonColor = GREEN;
    Color Difficultybutton1 = GREEN;
    Color Difficultybutton2 = YELLOW;
    Color Difficultybutton3 = RED;

    SetTargetFPS(60);

    while (!WindowShouldClose()) 
    {
        Vector2 mouseCoordinates = GetMousePosition();
        
        if (currentState == TITLE_SCREEN and IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mouseCoordinates, startButton)) 
            {
                currentState = GAME_SCREEN;
            }
        }
        else if (currentState == GAME_SCREEN and IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mouseCoordinates, difficulty1))
            {
                currentState = DIFFICULTY1;
            }
            else if (CheckCollisionPointRec(mouseCoordinates, difficulty2))
            {
                currentState = DIFFICULTY2;
            }
            else if (CheckCollisionPointRec(mouseCoordinates, difficulty3))
            {
                currentState = DIFFICULTY3;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (currentState == TITLE_SCREEN)
        {
            DrawText("The Guessing Game", screenWidth/2 - MeasureText("The Guessing Game", 40)/2, 100, 40, BLACK);
            DrawRectangleRec(startButton, buttonColor);
            DrawText("Start", startButton.x + startButton.width/2 - MeasureText("Start", 30)/2, startButton.y + startButton.height/2 - 15, 30, BLACK);
                
        }
        else if (currentState == GAME_SCREEN)
        {
            DrawText("You have to guess a number from the difficulty range", 100, 100, 30, DARKGRAY);
            DrawText("and get it correct in three attempts.", 150, 150, 30, DARKGRAY);
            
            DrawRectangleRec(difficulty1, Difficultybutton1);
            DrawText("1 to 10", difficulty1.x + difficulty1.width/2 - MeasureText("1 to 10", 30)/2, difficulty1.y + difficulty1.height/2 - 15, 30, BLACK);
                    
            
            DrawRectangleRec(difficulty2, Difficultybutton2);
            DrawText("20 to 50", difficulty2.x + difficulty2.width/2 - MeasureText("20 to 50", 30)/2, difficulty2.y + difficulty2.height/2 - 15, 30, BLACK);
                    
            
            DrawRectangleRec(difficulty3, Difficultybutton3);
            DrawText("30 to 100", difficulty3.x + difficulty3.width/2 - MeasureText("30 to 100", 30)/2, difficulty3.y + difficulty3.height/2 - 15, 30, BLACK);
                  
        }
        else if (currentState == DIFFICULTY1)
        {
            DrawText("Difficulty 1 Selected (1-10)", 250, 100, 30, BLACK);
        }
        else if (currentState == DIFFICULTY2)
        {
            DrawText("Difficulty 2 Selected (20-50)", 250, 100, 30, BLACK);
        }
        else if (currentState == DIFFICULTY3)
        {
            DrawText("Difficulty 3 Selected (30-100)", 250, 100, 30, BLACK);
        }
            
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
