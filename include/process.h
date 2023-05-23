/**
 * @file    process.h
 * @author  Mindou (minsu5875@naver.com)
 * @brief   CPU scheduler simulator process header
 * @version 0.1
 * @date    2023-05-03
 * 
 * @copyright Copyright (c) 2023 Minsu Bak
 * 
 */
#ifndef PROCESS_H
#define PROCESS_H

// standard libaray
#include <stdbool.h>

// external library & user define library
#include "queue.h"

/**
 * @brief process.h variable info
 *  
 *  type        name        pointer  info
 *  #define     CHECK       n        debug flag for process status
 *  Process     p           y        pointer for process structure
 *  int         processID   n        process no.
 *  int         arrival     n        process arrival time
 *  int         burst       n        process burst time(equal remain, but not using calulate)
 *  int         remain      n        process task remain time(equal burst, but using calculate)
 *  int         prioity     n        process prioity
 *  int         waiting     n        record process waiting time
 *  int         timeout     n        record process time-out time
 *  int         execute     n        record process execute time
 *  int         index       n        index for result array
 *  char        name        y        algorithm name 
 * 
 */

#define CHECK   false

/**
 * @brief structure for process
 * 
 */
typedef struct Process{

    int processID;  // process no.
    int arrival;    // process arrival time
    int burst;      // process burst time(equal remain, but not using calculate)
    int remain;     // process task remain time(equal burst, but using calculate)
    int prioity;    // process prioity
    int waiting;    // record process waiting time
    int timeout;    // record process time-out time
    int execute;    // record process execute time

} Process;

/**
 * @brief       print for gantt chart data
 * 
 * @param p     pointer for process structure
 * @param index index for result array
 * @param count count of processes
 * @param name  algorithm name
 */
void print_result(Process *p, int index, int count, char* name) {

    printf("\n\n%s\n", name);
    printf("index\tPID\tarrival\tburst\tprioity\twaitng\tturnaround\n");
    for(int i = 0; i < index ;i++)
        printf("%d\tP%d\t%d\t%d\t%d\t%d\t%d\n", 
        i,\
        p[i].processID,\
        p[i].arrival,\
        p[i].burst,\
        p[i].prioity,\
        p[i].waiting,\
        (p[i].execute + p[i].waiting)
        );
}

#endif