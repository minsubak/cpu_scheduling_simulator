/**
 * @file    main.h
 * @author  Mindou (minsu5875@naver.com)
 * @brief   external & user define library & etc. function/variable package header
 * @version 0.1
 * @date    (first date: 2023-05-08, last date: 2023-05-23)
 * 
 * @copyright Copyright (c) 2023 Minsu Bak
 * 
 */

#ifndef MAIN_H
#define MAIN_H

// standarad library
#include <stdbool.h>

// external library & user define library
#include "raylib.h"
#include "image.h"

/**
 * @brief main.h variable info
 *  
 *  type        name            pointer     info
 *  #define     TARGET_FPS      n           target fps
 *  #define     SCREEN_W        n           screen size for width
 *  #define     SCREEN_H        n           screen size for height
 *  #define     BTN_W           n           button size for width
 *  #define     BTN_H           n           button size for height
 *  int         btnClickFlag    y           define click flag for each buttons
 * 
 */

#define TARGET_FPS          60      // target fps
#define SCREEN_W            1024    // screen size: width
#define SCREEN_H            600     // screen size: height
#define BTN_W               100     // button size: width
#define BTN_H               62      // button size: height
#define QAUNTUM             2       // default time quantum
#define P_COUNT             5       // default process count
#define P_PARAM             4       // default process parameters count

int btnClickFlag[7];                // define click flag for each buttons

// process default data to be used by the simulator
int pInfo[P_COUNT][P_PARAM] = {
    {0, 0, 10, 3}, // process 0, arrival 0, burst 10, priority 3
    {1, 1, 28, 2}, // process 1, arrival 1, burst 28, priority 2
    {2, 2,  6, 4}, // process 2, arrival 2, burst  6, priority 4
    {3, 3,  4, 1}, // process 3, arrival 3, burst  4, priority 1
    {4, 4, 14, 2}  // process 4, arrival 4, burst 14, priority 2
};

// button color flag
const Color colorTag[] = {

    {  26,  26,  26, 255}, // dark gray
    {  50,  50,  50, 255}, // white
    { 230,  41,  55, 255}, // red
    { 255, 161,   0, 255}, // orange
    { 253, 249,   0, 255}, // yellow
    {   0, 228,  48, 255}, // green
    {   0, 121, 241, 255}  // blue
};

// logo position
const Rectangle logo_position[] = { 
    {.x = SCREEN_W * 0.70f, .y = SCREEN_H * 0.8f, .width = 128, .height = 128},
    {.x = SCREEN_W * 0.83f, .y = SCREEN_H * 0.8f, .width = 96 , .height = 96 }
};

// script array
const char* name[] = {
    "FCFS", "SJF", "HRN", "NPP", "PP", "RR", "SRT",       // 0 ~  6: algorithm
    " P\n(0)", " P\n(1)", " P\n(2)", " P\n(3)", " P\n(4)" // 7 ~ 11: info
};

#endif