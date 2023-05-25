/**
 * @file    main.c
 * @author  Mindou (minsu5875@naver.com)
 * @brief   Operating System-Term Project: CPU_Scheduler Simulator
 * @version 0.1
 * @date    (first date: 2023-04-26)
 * 
 * @copyright Copyright (c) 2023 Minsu Bak
 * 
 */

// standard library
#include <stdio.h>
#include <stdlib.h>

// external library & user define library
#include "main.h"
#include "process.h"
#include "raylib.h"
#include "main.h"

/**
 * @brief main.c variable info
 *  
 *  type        name        pointer     info
 *  FILE        fp          y           file pointer for file I/O and management
 *  Process     p           y           structure for process data storage
 *  int         i           n           multipurpose utilization variable
 *  int         count       n           save process count
 *  int         quantum     n           save simulator environment variable basic value
 *  int         total       n           save scheduler total burst time
 *  
 */

#define TARGET_FPS          60                               // target fps
#define SCREEN_WIDTH        1024                             // screen size: width
#define SCREEN_HEIGHT       768                              // screen size: height
#define BACKGROUND_COLOR    ((Color) { 255, 255, 255, 255 }) // screen background basic color
#define BUTTON_CORLOR       ((Color) {  30,  30,  30, 255 }) // button background basic color

bool FILE_NOT_FOUND       = false;

const Vector2 btnPos[] = {                         // define button display position
    {.x = 30, .y =                       40},
    {.x = 30, .y = SCREEN_HEIGHT * 0.1 + 40},
    {.x = 30, .y = SCREEN_HEIGHT * 0.2 + 40},
    {.x = 30, .y = SCREEN_HEIGHT * 0.3 + 40},
    {.x = 30, .y = SCREEN_HEIGHT * 0.4 + 40},
    {.x = 30, .y = SCREEN_HEIGHT * 0.5 + 40},
    {.x = 30, .y = SCREEN_HEIGHT * 0.6 + 40}
};

const char* algorithm[] = {
    "FCFS",
    "SJF",
    "HRN",
    "NPP",
    "PP",
    "RR",
    "SRT"
};

int main(void) {    

    // search and load "data.txt" files with process data

    FILE *fp = fopen("data.txt", "r");
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
        &p[i].prioity
        );
        p[i].remain = p[i].burst;
        p[i].timeout = p[i].arrival;
        p[i].waiting = 0;
        p[i].execute = 0;
        total += p[i].burst;
    }

    // get time quantum

    int quantum;
    fscanf(fp, "%d", &quantum);
/* 
    // First Come First Served
    FCFS(p, count, total);

    // Shortest Job First
    SJF(p, count, total);

    // Highest Responese Ratio Next
    HRN(p, count, total);

    // Non-Preemption Prioity
    NPP(p, count, total);
    
    // Preemption Prioity
    PP(p, count, total);

    // Round-Robin
    RR(p, count, total, quantum);

    // Shortest Remaining Time
    SRT(p, count, total); */

    // default config settings
    //SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "CPU Scheduling Simulator with raylib");
    SetTargetFPS(TARGET_FPS);

    // loading and creating texture image from `res` folder
    // WARN: be sure to call `InitWindows()` before creating a texture image 

    Texture2D logo_6pm_256x256      = LoadTexture("res/images/6pm-logo_256x256.png");
    Texture2D logo_raylib_128x128   = LoadTexture("res/images/raylib-logo_128x128.png");
    Texture2D card_image            = LoadTexture("res/images/cards_70x10.png");
    
    // define a rectangle that represents the boundary of the screen

    const Rectangle bounds = { .width = SCREEN_WIDTH, .height = SCREEN_HEIGHT };
    const Rectangle button = { .width = 100, .height = 62 };

    // define position for drawing logo

    const Vector2 logo_6pm_position = { 
        0.8f * (SCREEN_WIDTH - logo_6pm_256x256.width),
        1.07f * (SCREEN_HEIGHT - logo_6pm_256x256.height)
    };

    const Vector2 logo_raylib_position = {
        0.95f * (SCREEN_WIDTH - logo_raylib_128x128.width),
        0.95f * (SCREEN_HEIGHT - logo_raylib_128x128.height)
    };

    if(FILE_NOT_FOUND == true) {    // if program can't find the file
        while (!WindowShouldClose()) {  // repeat until the user closes the window or presses the `ESC` key

            // initalizing frame buffer for drawing
            BeginDrawing();
            
            // fill frame buffer to black
            ClearBackground(BLACK);
            
            // draw dark black of rectangle on the screen 
            DrawRectangleRec(bounds, BACKGROUND_COLOR);
            
            // draw text on the screen
            DrawText(
                "File not Found!\nPlease check your folder!",\
                SCREEN_WIDTH * 0.1,\
                SCREEN_HEIGHT * 0.4,\
                40.0f, BLACK);

            // draw screen using doulbe buffer method, ready to next frame buffer
            EndDrawing();
        }
    } else {    // if program find the file
        while (!WindowShouldClose()) { // repeat until the user closes the window or presses the `ESC` key

            // initalizing frame buffer for drawing
            BeginDrawing();
            
            // fill frame buffer to black
            ClearBackground(BLACK);

            // draw dark black of rectangle on the screen 
            DrawRectangleRec(bounds, BACKGROUND_COLOR);

            // draw button on the screen
            for(int i = 0; i < 7; i++) {
                DrawRectangle(btnPos[i].x, btnPos[i].y, button.width, button.height, BUTTON_CORLOR);
                DrawText( algorithm[i], btnPos[i].x + 10, btnPos[i].y + 15, 30.0f, WHITE);
            }

            // draw the texture at the specified position on the screen
            DrawTextureV(   logo_6pm_256x256,    logo_6pm_position, WHITE);
            DrawTextureV(logo_raylib_128x128, logo_raylib_position, WHITE);

            // display fps at set poisition
            DrawFPS(8, 8);

            // draw screen using doulbe buffer method, ready to next frame buffer
            EndDrawing();
        }
    }


    // memory allocate disable
    UnloadTexture(logo_6pm_256x256);
    UnloadTexture(logo_raylib_128x128);
    UnloadTexture(card_image);
    CloseWindow();
    free(p);
    fclose(fp);

    return 0;
}