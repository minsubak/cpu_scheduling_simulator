/**
 * @file    main.c
 * @author  Mindou (minsu5875@naver.com)
 * @brief   Operating System-Term Project: CPU_Scheduler Simulator
 * @version beta 0.1.2
 * @date    (first date: 2023-04-26, last date: 2023-05-31)
 * 
 * @copyright Copyright (c) 2023 Minsu Bak
 * 
 */

// external library & user define library
#include "FCFS.h"
#include "SJF.h"
#include "HRN.h"
#include "NPP.h"
#include "PP.h"
#include "RR.h"
#include "SRT.h"
#include "main.h"
#include "process.h"
#include "raylib.h"

/**
 * @brief main.c variable info
 *  
 *  type        name        pointer     info
 *  Process     gantt       y           pointer to get gantt chart from function
 *  Process     p           y           pointer for process structure
 *  int         total       n           int variable for total burst time of tasks
 *  Image       temp        n           temporary variable for loading images
 *  Texture2D   logo6pm     n           6pm logo image
 *  Texture2D   logoRay     n           laylib logo image
 *  Texture2D   cardImg     n           card image
 *  Vector2     mousePoint  n           realtime mouse position (default .x = 0.0f, .y = 0.0f)
 * 
 */

Process *gantt; // pointer to get gantt chart from function

int main(void) {    

    // dynamic memory allocation

    Process *p = malloc(sizeof(Process) * P_COUNT); // process structure pointer to be used by the simulator

    // load process data to the process structure

    int total = 0; // int variable for total burst time of tasks
    for(int i = 0; i < P_COUNT; i++) {
            
        p[i].processID = pInfo[i][0];
        p[i].arrival   = pInfo[i][1];
        p[i].burst     = pInfo[i][2];
        p[i].priority  = pInfo[i][3];
        p[i].remain    = p[i].burst;
        p[i].timeout   = p[i].arrival;
        p[i].waiting   = 0;
        p[i].execute   = 0;
        total         += p[i].burst;
    }

    // memory allocate to gantt array
    gantt = malloc(sizeof(Process) * total);

    // default config settings
    InitWindow(SCREEN_W, SCREEN_H, "CPU Scheduling Simulator with raylib");
    SetTargetFPS(TARGET_FPS);

    Image temp; // temporary variable for loading images

    // load image from `image.h`, and load textrue from image
    // WARN: be sure to call `InitWindows()` before creating a texture image

    temp = LoadImageFromMemory(".png", logo_6pm, LOGO_6PM_LEN);
    Texture2D logo6pm = LoadTextureFromImage(temp); // 6pm logo texture

    temp = LoadImageFromMemory(".png", logo_ray, LOGO_RAY_LEN);
    Texture2D logoRay = LoadTextureFromImage(temp); // raylib logo texture

    temp = LoadImageFromMemory(".png", card_img, CARD_IMG_LEN);
    Texture2D cardImg = LoadTextureFromImage(temp); // card texture

    // unloadimage temporary variable
    UnloadImage(temp);

    // define position for default mouse position
    
    Vector2 mousePoint = { .x = 0.0f, .y = 0.0f }; // realtime mouse position

    // repeat until the user closes the window or presses the `ESC` key
    while (!WindowShouldClose()) {

        // mouse activate sensing
        mousePoint = GetMousePosition();

        // check mouse state
        for (int i = 0; i < 7; i++) {

            // if the mouse point position approaches the button position
            if (CheckCollisionPointRec(mousePoint, (Rectangle){30, 768 * (0.1 * i) + 40, BTN_W, BTN_H})) {

                // if mouse left button is pressed
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    
                    // initalize button click flags
                    for(int i = 0; i < 7; i++)
                        btnClickFlag[i] = 0;

                    // change the flag corresponding to the clicked button
                    btnClickFlag[i] = 1;      
                }
            }
        }

        // initalizing frame buffer for drawing
        BeginDrawing();
        
            // fill frame buffer to black
            ClearBackground((Color){ 0, 0, 0, 255});
            // draw button on the screen
            for(int i = 0; i < 7; i++) {
                DrawRectangleRec(
                    (Rectangle){30, 768 * (0.1 * i) + 40, BTN_W, BTN_H},
                    colorTag[btnClickFlag[i]]
                );
                DrawText(
                    name[i], 
                    40, 
                    768 * (0.1 * i) + 55, 
                    30.0f, 
                    (Color){ 238, 58, 23, 255}
                );
            }

            // draw gantt chart
            for(int i = 0; i < 7; i++) {

                // if the flag corresponding to the `i` variable is 1
                if(btnClickFlag[i] == 1) {

                    // enforce algorithms that fit `i` variable
                    switch(i) {
                    case 0:
                        // First Come First Served
                        FCFS(p, P_COUNT, total, cardImg);
                        break;
                        
                    case 1:
                        // Shortest Job First
                        SJF(p, P_COUNT, total, cardImg);
                        break;
                        
                    case 2:
                        // Highest Responese Ratio Next
                        HRN(p, P_COUNT, total, cardImg);
                        break;
                        
                    case 3:
                        // Non-Preemption Prioity
                        NPP(p, P_COUNT, total, cardImg);
                        break;
                        
                    case 4:
                        // Preemption Prioity
                        PP(p, P_COUNT, total, cardImg);
                        break;
                        
                    case 5:
                        // Round-Robin
                        RR(p, P_COUNT, total, QAUNTUM, cardImg);
                        break;
                        
                    case 6:
                        // Shortest Remaining Time
                        SRT(p, P_COUNT, total, cardImg);
                        break;
                        
                    default:
                        // if system can't get `i` answer
                        TraceLog(LOG_WARNING, "unknown variable `i`");
                        break;
                    }
                }
            }

            DrawTexturePro(
                logo6pm,    
                (Rectangle){.x = 0, .y = 0, .width = 256, .height = 256}, 
                logo_position[0], 
                (Vector2){ 0, 0 }, 
                0, 
                WHITE
            );
            DrawTexturePro(
                logoRay, 
                (Rectangle){.x = 0, .y = 0, .width = 256, .height = 256}, 
                logo_position[1], 
                (Vector2){ 0, 0 }, 
                0, 
                WHITE
            );

            // display fps at set poisition
            DrawFPS(8, 8);

        // draw screen using doulbe buffer method, ready to next frame buffer
        EndDrawing();
    }

    // memory allocate disable
    UnloadTexture(logo6pm);
    UnloadTexture(logoRay);
    UnloadTexture(cardImg);

    CloseWindow();

    free(p);

    return 0;
}