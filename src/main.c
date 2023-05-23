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
 *  Process     o           y           structure for process data storage(original)
 *  Process     t           y           structure for process data storage(target)
 *  int         i           n           multipurpose utilization variable
 *  int         count       n           save process count
 *  int         quantum     n           save simulator environment variable basic value
 *  int         total       n           save scheduler total burst time
 *  
 */

#define TARGET_FPS         60                           // target fps
#define SCREEN_WIDTH       1024                         // screen size: width
#define SCREEN_HEIGHT      768                          // screen size: height
#define BACKGROUND_COLOR   ((Color) { 26, 26, 26, 255 })// screen background basic color

int main(void) {    

    // search and load "data.txt" files with process data

    FILE *fp = fopen("data.txt", "r");
    if(fp == NULL) error("file not found");
    else printf("file found!\n\n");

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

    // default initalize settings
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "ToyProject");
    SetTargetFPS(TARGET_FPS);

    // 6PM 로고 파일로 텍스처를 생성한다.
    // 텍스처를 생성하기 전에 반드시 `InitWindow()`를 호출해야 함을 기억하자!
    Texture2D texture = LoadTexture("res/images/6pm-logo_512x512.png");
    
    // 게임 화면의 경계를 나타내는 직사각형을 정의한다.
    const Rectangle bounds = { .width = SCREEN_WIDTH, .height = SCREEN_HEIGHT };

    // 6PM 로고를 그릴 위치를 정의한다.
    const Vector2 position = { 
        0.5f * (SCREEN_WIDTH - texture.width),
        0.5f * (SCREEN_HEIGHT - texture.height)
    };

    // 사용자가 창을 닫거나, `ESC` 키를 누르기 전까지 반복한다.
    while (!WindowShouldClose()) {
        // 게임 화면을 그리기 위해 프레임 버퍼를 초기화한다.
        BeginDrawing();
        
        // 프레임 버퍼를 검은색으로 채운다.
        ClearBackground(BLACK);

        // 게임 화면에 어두운 회색 색상의 직사각형을 그린다.
        DrawRectangleRec(bounds, BACKGROUND_COLOR);

        // 게임 화면의 가운데에 6PM 로고를 그린다.
        DrawTextureV(texture, position, WHITE);

        // 게임 화면에 현재 FPS를 표시한다.
        DrawFPS(8, 8);

        // 더블 버퍼링 기법을 사용하여 게임 화면을 그리고,
        // 다음 프레임 버퍼를 준비한다.
        EndDrawing();
    }

    // memory allocate disable
    UnloadTexture(texture);
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
    SRT(p, count, total);
*/