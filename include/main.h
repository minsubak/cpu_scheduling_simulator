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
#include "NPP.h"
/*
#include "PP.h"
#include "RR.h"
#include "SRT.h"
#include "HRN.h"
*/

/**
 * @brief main.h variable info
 *  
 *  type        name        pointer     info
 *  char        message     y           message with error info
 *  
 */


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