/**
 * @file    process.h
 * @author  Mindou (minsu5875@naver.com)
 * @brief   CPU scheduler simulator process header
 * @version 0.1
 * @date    (frist date: 2023-05-03, last date: 2023-05-28)
 * 
 * @copyright Copyright (c) 2023 Minsu Bak
 * 
 */
#ifndef PROCESS_H
#define PROCESS_H

// standard libaray
#include <stdbool.h>

// external library & user define library
#include "raylib.h"
#include "queue.h"
#include "main.h"

/**
 * @brief process.h variable info
 *  
 *  type        name        pointer info
 *  #define     CHECK       n       debug flag for process status
 *  Rectangle   card_bound  n       card size
 *  int         processID   n       process no.
 *  int         arrival     n       process arrival time
 *  int         burst       n       process burst time(equal remain, but not using calulate)
 *  int         remain      n       process task remain time(equal burst, but using calculate)
 *  int         priority     n       process priority
 *  int         waiting     n       record process waiting time
 *  int         timeout     n       record process time-out time
 *  int         execute     n       record process execute time
 *  Process     p           y       pointer for process structure (result array)
 *  Process     g           y       pointer for process structure (gannt chart array)
 *  Texture2D   texture     n       card image
 *  int         t           n       total busrt time
 *  int         n           n       total process count
 * 
 */

#define CHECK   false

// card size
const Rectangle card_bound = {
    .x = 60, .y = 0, .width = 10, .y = 16
};

/**
 * @brief structure for process
 * 
 */
typedef struct Process{

    int processID;  // process no.
    int arrival;    // process arrival time
    int burst;      // process burst time(equal remain, but not using calculate)
    int remain;     // process task remain time(equal burst, but using calculate)
    int priority;   // process priority
    int waiting;    // record process waiting time
    int timeout;    // record process time-out time
    int execute;    // record process execute time

} Process;

/**
 * @brief draw gantt chart and result
 * 
 * @param p         pointer for process structure (result array)
 * @param g         pointer for process structure (gannt chart array)
 * @param texture   card image
 * @param t         total busrt time
 * @param n         total process count
 */
void draw_everything(Process *p, Process *g, Texture2D texture, int t, int n) {

    for(int i = 0; i < t; i++) {
        
        // draw textrue, texture size, draw position, reference point, rotation, color
        DrawTexturePro(
        texture,\
        card_bound,\
        (Rectangle) {SCREEN_W * 0.1 + 103 + (i * 12), 80, 10, 16},\
        (Vector2) { 0, 0 },\
        0,\
        colorTag[g[i].processID + 2]);

        // draw text, x position, y position, font size, text color
        DrawText(TextFormat("%d", g[i].processID), SCREEN_W * 0.1 + 103 + (i * 12), 80, 10, WHITE);
    }

    // draw text, x position, y position, font size, text color
    DrawText("index\t\t\t\tPID\t\t\t\tarrival\t\t\t\tburst\t\t\t\tprioity\t\t\t\twaitng\t\t\tturnaround\n", SCREEN_W * 0.2, SCREEN_H * 0.2, 20, GREEN);
    
    for(int i = 0; i < n; i++) {

        // draw text, x position, y position, font size, text color
        DrawText(TextFormat("%d", i),                            SCREEN_W * 0.2,       SCREEN_H * 0.2 + (i * 20) + 30, 20, GREEN);
        DrawText(TextFormat("%d", p[i].processID),               SCREEN_W * 0.2 + 100, SCREEN_H * 0.2 + (i * 20) + 30, 20, GREEN);
        DrawText(TextFormat("%d", p[i].arrival),                 SCREEN_W * 0.2 + 185, SCREEN_H * 0.2 + (i * 20) + 30, 20, GREEN);
        DrawText(TextFormat("%d", p[i].burst),                   SCREEN_W * 0.2 + 302, SCREEN_H * 0.2 + (i * 20) + 30, 20, GREEN);
        DrawText(TextFormat("%d", p[i].priority),                SCREEN_W * 0.2 + 408, SCREEN_H * 0.2 + (i * 20) + 30, 20, GREEN);
        DrawText(TextFormat("%d", p[i].waiting),                 SCREEN_W * 0.2 + 522, SCREEN_H * 0.2 + (i * 20) + 30, 20, GREEN);
        DrawText(TextFormat("%d",(p[i].execute + p[i].waiting)), SCREEN_W * 0.2 + 620, SCREEN_H * 0.2 + (i * 20) + 30, 20, GREEN);
    }
}

#endif