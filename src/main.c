/**
 * @file    main.c
 * @author  Mindou (minsu5875@naver.com)
 * @brief   Operating System-Term Project: CPU_Scheduler Simulator
 * @version beta 0.1.1
 * @date    (first date: 2023-04-26, last date: 2023-05-28)
 * 
 * @copyright Copyright (c) 2023 Minsu Bak
 * 
 */

// standard library
#include <stdio.h>
#include <stdlib.h>

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
 *  FILE        fp          y           pointer for file I/O
 *  int         count       n           int variable for process count
 *  Process     p           y           pointer for process structure
 *  int         total       n           int variable for total burst time of tasks
 *  int         quantum     n           int variable for time quantum
 *  Texture2D   logo_6pm    n           6pm logo image
 *  Texture2D   logo_raylib n           laylib logo image
 *  Texture2D   card_image  n           card image
 *  Vector2     mousePoint  n           return mouse position (default .x = 0.0f, .y = 0.0f)
 * 
 */

Process *gantt; // pointer to get gantt chart from function

int main(void) {    

    // search and load `data.txt` files with process data

    FILE *fp = fopen("res/txt/data.txt", "r");
    if(fp == NULL) {
        TraceLog(LOG_WARNING, "file not found!");
        FILE_NOT_FOUND = true;
    } else TraceLog(LOG_INFO, "file found!");

    // read process count and allocate memory

    int count = 0;
    fscanf(fp, "%d\n", &count);
    Process *p = malloc(sizeof(Process)*count);

    // read and save process data

    int total = 0;
    for(int i = 0; i < count; i++) {
        fscanf(fp, "%d %d %d %d\n",\
        &p[i].processID,\
        &p[i].arrival,\
        &p[i].burst,\
        &p[i].priority
        );
        p[i].remain = p[i].burst;
        p[i].timeout = p[i].arrival;
        p[i].waiting = 0;
        p[i].execute = 0;
        total += p[i].burst;
    }

    // memory allocate to gantt array
    gantt = malloc(sizeof(Process) * total);

    // get time quantum

    int quantum;
    fscanf(fp, "%d", &quantum);

    // default config settings
    InitWindow(SCREEN_W, SCREEN_H, "CPU Scheduling Simulator with raylib");
    SetTargetFPS(TARGET_FPS);

    // loading and creating texture image from `res` folder
    // WARN: be sure to call `InitWindows()` before creating a texture image

    Texture2D logo_6pm    = LoadTexture("res/images/6pm-logo_256x256.png");
    Texture2D logo_raylib = LoadTexture("res/images/raylib-logo_256x256.png");
    Texture2D card_image  = LoadTexture("res/images/cards_70x10.png");

    // define position for default mouse position
    
    Vector2 mousePoint = { .x = 0.0f, .y = 0.0f };

    // if program can't find the file
    if(FILE_NOT_FOUND == true) {

    // repeat until the user closes the window or presses the `ESC` key
        while (!WindowShouldClose()) {  

            // initalizing frame buffer for drawing
            BeginDrawing();
            
                // fill frame buffer to black
                ClearBackground(WHITE);
                
                // draw text on the screen
                DrawText(
                    "File not Found!\nPlease check your folder and restart!",\
                    SCREEN_W * 0.1,\
                    SCREEN_H * 0.4,\
                    40.0f, BLACK
                );

            // draw screen using doulbe buffer method, ready to next frame buffer
            EndDrawing();
        }
    } 

    // if program find the file
    else {

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
                            FCFS(p, count, total, card_image);
                            break;
                            
                        case 1:
                            // Shortest Job First
                            SJF(p, count, total, card_image);
                            break;
                            
                        case 2:
                            // Highest Responese Ratio Next
                            HRN(p, count, total, card_image);
                            break;
                            
                        case 3:
                            // Non-Preemption Prioity
                            NPP(p, count, total, card_image);
                            break;
                            
                        case 4:
                            // Preemption Prioity
                            PP(p, count, total, card_image);
                            break;
                            
                        case 5:
                            // Round-Robin
                            RR(p, count, total, quantum, card_image);
                            break;
                            
                        case 6:
                            // Shortest Remaining Time
                            SRT(p, count, total, card_image);
                            break;
                            
                        default:
                            // if system can't get `i` answer
                            TraceLog(LOG_WARNING, "unknown variable `i`");
                            break;
                        }
                    }
                }

                DrawTexturePro(
                    logo_6pm,    
                    (Rectangle){.x = 0, .y = 0, .width = 256, .height = 256}, 
                    logo_position[0], 
                    (Vector2){ 0, 0 }, 
                    0, 
                    WHITE
                );
                DrawTexturePro(
                    logo_raylib, 
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
    }

    // memory allocate disable
    UnloadTexture(logo_6pm);
    UnloadTexture(logo_raylib);
    UnloadTexture(card_image);
    CloseWindow();
    free(p);
    fclose(fp);

    return 0;
}