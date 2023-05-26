/**
 * @file    main.h
 * @author  Mindou (minsu5875@naver.com)
 * @brief   external & user define library / etc. function package header
 * @version 0.1
 * @date    2023-05-08
 * 
 * @copyright Copyright (c) 2023 Minsu Bak
 * 
 */

#ifndef MAIN_H
#define MAIN_H

// external library & user define library
#include "FCFS.h"
#include "SJF.h"
#include "HRN.h"
#include "NPP.h"
#include "PP.h"
#include "RR.h"
#include "SRT.h"

/**
 * @brief main.h variable info
 *  
 *  type        name        pointer     info
 *  char        message     y           message with error info
 *  
 */

#define TARGET_FPS          60                              // target fps
#define SCREEN_W            1024                            // screen size: width
#define SCREEN_H            768                             // screen size: height
#define BTN_W               100                             // button size: width
#define BTN_H               62                              // button size: height

bool FILE_NOT_FOUND       = false;                          // file find flag
int  btnColorTag[7];                                        // define color flag for each buttons

/**
 * @brief print error and exit
 * 
 * @param message print error info message
 */
void error(char * message) {
    
    fprintf(stderr, "%s\n", message);
    exit(1);
}

#endif