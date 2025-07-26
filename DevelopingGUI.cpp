#include <raylib.h>
#include <cstring>
#include <string>

enum GameState { TITLE_SCREEN, GAME_SCREEN, DIFFICULTY1, DIFFICULTY2, DIFFICULTY3 };
GameState currentState = TITLE_SCREEN;

int main()
{
    const int screenWidth = 1024;
    const int screenHeight = 768;
    
    InitWindow(screenWidth, screenHeight, "Test");

    Rectangle inputBox = { screenWidth/2 - 100, 300, 200, 50 };
    Rectangle startButton = { screenWidth/2 - 150, screenHeight/2 - 50, 300, 100 };
    Rectangle difficulty1 = { screenWidth/2 - 150, screenHeight/2 - 50, 300, 100 };
    Rectangle difficulty2 = { screenWidth/2 - 150, screenHeight/2 + 100, 300, 100 };
    Rectangle difficulty3 = { screenWidth/2 - 150, screenHeight/2 + 250, 300, 100 };
    
    Color buttonColor = GREEN;
    Color Difficultybutton1 = GREEN;
    Color Difficultybutton2 = YELLOW;
    Color Difficultybutton3 = RED;
    Color boxColor = LIGHTGRAY;
    
    char input_text[32] = "\0";
    bool text_allowed = false;
    
    SetTargetFPS(60);

    while (!WindowShouldClose()) 
    {
        Vector2 mouseCoordinates = GetMousePosition();
        
        // Handle mouse clicks
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (currentState == TITLE_SCREEN)
            {
                if (CheckCollisionPointRec(mouseCoordinates, startButton)) 
                {
                    currentState = GAME_SCREEN;
                }
            }
            else if (currentState == GAME_SCREEN)
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
            
            // NEW: Proper input box collision check
            if (currentState == DIFFICULTY1 or currentState == DIFFICULTY2 or currentState == DIFFICULTY3)
            {
                text_allowed = CheckCollisionPointRec(mouseCoordinates, inputBox);
            }
        }

        if ((currentState == DIFFICULTY1 or currentState == DIFFICULTY2 or currentState == DIFFICULTY3) and text_allowed)
        {
            int key_pressed = GetCharPressed();
            while (key_pressed > 0)
            {
                if ((key_pressed >= '0' and key_pressed <= '9') or key_pressed == KEY_BACKSPACE)
                {
                    if (key_pressed == KEY_BACKSPACE)
                    {
                        int length = strlen(input_text);
                        if (length > 0) 
                        {
                            input_text[length-1] = '\0';
                        }
                    }
                    else if (strlen(input_text) < 4)
                    {
                        int length = strlen(input_text);
                        input_text[length] = (char)key_pressed;
                        input_text[length+1] = '\0';
                    }
                }
                key_pressed = GetCharPressed();
            }

            if (IsKeyPressed(KEY_ENTER) and strlen(input_text) > 0)
            {
                input_text[0] = '\0';
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
        
        if (currentState == DIFFICULTY1 or currentState == DIFFICULTY2 or currentState == DIFFICULTY3)
        {
            DrawText("Enter your guess (press enter key):",screenWidth/2 - MeasureText("Enter your guess (press enter key):",20)/2,250,20,BLACK);
            DrawRectangleRec(inputBox, boxColor);
            DrawRectangleLinesEx(inputBox, 2, DARKGRAY);
            DrawText(input_text, inputBox.x + 10, inputBox.y + 15, 30, BLACK);
        }    
            
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
