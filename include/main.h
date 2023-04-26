#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include "FCFS.h"
#include "SJF.h"
#include "PP.h"
#include "NPP.h"
#include "RR.h"
#include "SRT.h"
#include "HRN.h"

void error(char * message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

#endif