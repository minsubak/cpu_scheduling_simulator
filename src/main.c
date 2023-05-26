/**
 * @file    main.c
 * @author  Mindou (minsu5875@naver.com)
 * @brief   Operating System-Term Project: CPU_Scheduler Simulator
 * @version 0.1
 * @date    (first date: 2023-04-26, last date: 2023-05-)
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

const Color colorTag[] = {                                      // button color flag
    {  30,  30,  30, 255}, //  dark gray
    { 150, 150, 150, 255}, // light gray
    { 230,  41,  55, 255}, // red
    { 255, 151,   0, 255}, // orange
    { 253, 249,   0, 255}, // yellow
    {   0, 228,  48, 255}, // green
    {   0, 121, 241, 255}, // blue
};

const Rectangle btnSize = { .width = BTN_W, .height = BTN_H };  // button size

const Rectangle btnPos[] = {                                    // define button display position
    { .x = 30, .y =                  40, .width = BTN_W, .height = BTN_H },
    { .x = 30, .y = SCREEN_H * 0.1 + 40, .width = BTN_W, .height = BTN_H },
    { .x = 30, .y = SCREEN_H * 0.2 + 40, .width = BTN_W, .height = BTN_H },
    { .x = 30, .y = SCREEN_H * 0.3 + 40, .width = BTN_W, .height = BTN_H },
    { .x = 30, .y = SCREEN_H * 0.4 + 40, .width = BTN_W, .height = BTN_H },
    { .x = 30, .y = SCREEN_H * 0.5 + 40, .width = BTN_W, .height = BTN_H },
    { .x = 30, .y = SCREEN_H * 0.6 + 40, .width = BTN_W, .height = BTN_H }
};

const Rectangle card = {
    .x = 60, .y = 0, .width = 10, .y = 16
};

const Rectangle gantt = {
    .x = SCREEN_W * 0.5, .y = SCREEN_H * 0.5, .width = 10 * 3, .height = 16 * 3
};

const Rectangle info[] = {
    {.x =                   35, .y = SCREEN_H * 0.9, .width = 10 * 3, .height = 16 * 3},
    {.x = SCREEN_W * 0.05 + 35, .y = SCREEN_H * 0.9, .width = 10 * 3, .height = 16 * 3},
    {.x = SCREEN_W * 0.1  + 35, .y = SCREEN_H * 0.9, .width = 10 * 3, .height = 16 * 3},
    {.x = SCREEN_W * 0.15 + 35, .y = SCREEN_H * 0.9, .width = 10 * 3, .height = 16 * 3},
    {.x = SCREEN_W * 0.2  + 35, .y = SCREEN_H * 0.9, .width = 10 * 3, .height = 16 * 3}
};

const Rectangle logo = {
    .x = 0, .y = 0, .width = 256, .height = 256
};

const char* name[] = {                                     // define script for  name
    "FCFS", "SJF", "HRN", "NPP", "PP", "RR", "SRT",        // 0 ~  6: algorithm
    " P\n(1)", " P\n(2)", " P\n(3)", " P\n(4)", " P\n(5)"  // 7 ~ 11: info
};

int main(void) {    

    // search and load `data.txt` files with process data

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

    // default config settings
    InitWindow(SCREEN_W, SCREEN_H, "CPU Scheduling Simulator with raylib");
    SetTargetFPS(TARGET_FPS);

    // loading and creating texture image from `res` folder
    // WARN: be sure to call `InitWindows()` before creating a texture image

    Texture2D logo_6pm      = LoadTexture("res/images/6pm-logo_256x256.png");
    Texture2D logo_raylib   = LoadTexture("res/images/raylib-logo_256x256.png");
    Texture2D card_image    = LoadTexture("res/images/cards_70x10.png");

    // define position for drawing logo

    const Rectangle logo_position[] = { 
        {.x = 0.84f * (SCREEN_W - 128), .y = 0.99f * (SCREEN_H - 128), .width = 128, .height = 128},
        {.x = 0.99f * (SCREEN_W - 128), .y = 0.99f * (SCREEN_H - 128), .width = 128, .height = 128}
    };
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
                    40.0f, BLACK);

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
                if (CheckCollisionPointRec(mousePoint, btnPos[i])) {
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        btnColorTag[i] = 1;
                    }
                    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btnColorTag[i] = 0;
                }
                else btnColorTag[i] = 0;
            }

            // initalizing frame buffer for drawing
            BeginDrawing();
            
                // fill frame buffer to black
                ClearBackground(WHITE);

                // draw button on the screen
                for(int i = 0; i < 7; i++) {
                    DrawRectangleRec( btnPos[i], colorTag[btnColorTag[i]] );
                    DrawText( name[i], btnPos[i].x + 10, btnPos[i].y + 15, 30.0f, WHITE );
                }

                // draw gantt chart
/*                 for(int i = 0; i < total; i++) {
                    DrawTexturePro(  );
                } */
                //DrawTexturePro( card_image, card, gantt, (Vector2) { 0, 0 }, 0 ,RED );

                // draw scheduler calculate result


                // draw the texture at the `position` on the screen
                 
                DrawTexturePro( logo_6pm, logo, logo_position[0], (Vector2){ 0, 0 }, 0, WHITE );
                DrawTexturePro( logo_raylib, logo, logo_position[1], (Vector2){ 0, 0 }, 0, WHITE );
                DrawText( "Process by Color", info[1].x * 0.72, info[1].y * 0.95, 20.0f, BLACK);
                for(int i = 0; i < count; i++) {
                    DrawTexturePro( card_image, card, info[i], (Vector2) { 0, 0 }, 0 , colorTag[i + 2] );
                    DrawText( name[i + 7], info[i].x + 2, info[i].y, 20.0f, BLACK );
                }

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