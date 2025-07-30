#include <iostream>
#include <raylib.h>
#include <string>
#include <cstring>

enum GameState { TITLE_SCREEN,GAME_SCREEN, DIFFICULTY1, DIFFICULTY2, DIFFICULTY3, PLAYING, RESULT};
GameState currentState = TITLE_SCREEN;

int RandomNumber(int min, int max) {
    return GetRandomValue(min,max);
}

int main()
{
    const int screenWidth = 1368;
    const int screenHeight = 768;

    InitWindow(screenWidth, screenHeight, "Test");
    InitAudioDevice();

    Sound buttonClick = LoadSound("button-click.mp3");
    Sound keyboardClick = LoadSound("keyboardclick.mp3");
    Sound rightAnswer=LoadSound("correct.mp3");
    Sound wrongAnswer=LoadSound("wrong.mp3");

    int secret_integer;
    int attempts_remaining;
    int guess;
    bool game_won;  // Changed from game_lost
    int min_value;
    int max_value;
    char input_text[32] = "\0";
    bool text_allowed=false;

    Rectangle startButton = { screenWidth/2 - 150, screenHeight/2 - 50, 300, 100 };
    Rectangle difficulty1 = { screenWidth/2 - 150, screenHeight/2 - 150, 300, 100 };
    Rectangle difficulty2 = { screenWidth/2 - 150, screenHeight/2, 300, 100 };
    Rectangle difficulty3 = { screenWidth/2 - 150, screenHeight/2 + 150, 300, 100 };
    Rectangle inputBox = { screenWidth/2 - 150, screenHeight/2 -50, 300, 100 };
    Color buttonColor = GREEN;
    Color Difficultybutton1 = GREEN;
    Color Difficultybutton2 = YELLOW;
    Color Difficultybutton3 = RED;
    Color boxColor = LIGHTGRAY;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        Vector2 mouseCoordinates = GetMousePosition();

        if (currentState == TITLE_SCREEN and IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mouseCoordinates, startButton)) 
            {
                PlaySound(buttonClick);
                currentState = GAME_SCREEN;
            }
        }
        else if (currentState == GAME_SCREEN and IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        { 
            if (CheckCollisionPointRec(mouseCoordinates, difficulty1))
            {
                PlaySound(buttonClick);
                currentState = DIFFICULTY1;
                min_value=1; 
                max_value=10;
                secret_integer=RandomNumber(min_value,max_value);
                attempts_remaining=3;
                game_won=false;
            }
            else if (CheckCollisionPointRec(mouseCoordinates, difficulty2))
            {
                PlaySound(buttonClick);
                currentState = DIFFICULTY2;
                min_value=10; 
                max_value=30;
                secret_integer=RandomNumber(min_value,max_value);
                attempts_remaining=3;
                game_won=false;
            }
            else if (CheckCollisionPointRec(mouseCoordinates,difficulty3))
            {
                PlaySound(buttonClick);
                currentState = DIFFICULTY3;
                min_value=30; 
                max_value=100;
                secret_integer=RandomNumber(min_value,max_value);
                attempts_remaining=3;
                game_won=false;
            }
        }
        
        if ((currentState == DIFFICULTY1 or currentState == DIFFICULTY2 or currentState == DIFFICULTY3) and game_won == false and attempts_remaining>0) 
        {
            inputBox = { screenWidth/2 - 100, 300, 200, 50 };

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                text_allowed = CheckCollisionPointRec(mouseCoordinates, inputBox);
                
                if (text_allowed == true) {
                    PlaySound(buttonClick);
                }
            }

            if (text_allowed == true) {
                int key_pressed = GetCharPressed();
                if (key_pressed > 0) { 
                    PlaySound(keyboardClick);
                }
                while (key_pressed > 0) {
                    if ((key_pressed >= '0' and key_pressed <= '9') or key_pressed == KEY_BACKSPACE) {
                        if (key_pressed == KEY_BACKSPACE) {
                            int length = strlen(input_text);
                            if (length>0) {
                                input_text[length-1]='\0';
                            }
                        }
                        else if (strlen(input_text)<3) {
                            int length=strlen(input_text);
                            input_text[length] = (char)key_pressed;
                            input_text[length+1]='\0';
                        }
                    }
                    key_pressed=GetCharPressed();
                }

                if (IsKeyPressed(KEY_ENTER) and strlen(input_text)>0) {
                    guess=atoi(input_text);
                    attempts_remaining=attempts_remaining-1;
                    PlaySound(buttonClick);

                    if (guess == secret_integer) {
                        PlaySound(rightAnswer);
                        game_won = true;
                        currentState=RESULT;
                    }
                    else if (attempts_remaining == 0) {
                        PlaySound(wrongAnswer);
                        currentState=RESULT;
                    }
                    
                    strcpy(input_text, "\0");
                }
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
                DrawText("You have to guess a number from the difficulty range and get it correct in three attempts. ", 30, 100, 29, DARKGRAY);

                DrawRectangleRec(difficulty1,Difficultybutton1);
                DrawText("1 to 10", difficulty1.x +difficulty1.width/2 - MeasureText("1 to 10",30)/2, difficulty1.y+difficulty1.height/2 - 15,30,BLACK);

                DrawRectangleRec(difficulty2, Difficultybutton2);
                DrawText("10 to 30", difficulty2.x + difficulty2.width/2 - MeasureText("10 to 30",30)/2, difficulty2.y+difficulty2.height/2 - 15,30,BLACK);

                DrawRectangleRec(difficulty3, Difficultybutton3);
                DrawText("30 to 100", difficulty3.x + difficulty3.width/2 - MeasureText("30 to 100",30)/2, difficulty3.y + difficulty3.height/2 -15,30,BLACK);
            }
            else if (currentState == DIFFICULTY1 or currentState == DIFFICULTY2 or currentState == DIFFICULTY3)
            {
                DrawText("Enter your guess (press enter key):",screenWidth/2 - MeasureText("Enter your guess (press enter key):",20)/2,250,20,BLACK);
                DrawRectangleRec(inputBox, boxColor);
                if (text_allowed == true) {
                    DrawRectangleLinesEx(inputBox, 2, DARKGRAY);
                }
                DrawText(input_text, inputBox.x + 10, inputBox.y + 15, 30,BLACK);
                DrawText(TextFormat("Attempts left : %d", attempts_remaining),50,50,20,BLACK);
            }
            else if (currentState == RESULT)
            {
                if (game_won == true)
                {
                    DrawText("YOU WIN!",screenWidth/2 - MeasureText("YOU WIN!",50)/2,250,50,BLACK);
                }
                else
                {
                    DrawText("YOU LOSE!",screenWidth/2 - MeasureText("YOU LOSE!",50)/2,250,50,BLACK);
                }
            }
        EndDrawing();
    }

    UnloadSound(buttonClick);
    UnloadSound(keyboardClick);
    UnloadSound(rightAnswer);
    UnloadSound(wrongAnswer);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
