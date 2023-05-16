/**
 * @file    FCFS.h
 * @author  Mindou (minsu5875@naver.com)
 * @brief   = CPU schedule simulator
 *          = non preemeption method - FCFS(first come first served)
 *          - assign to CPU in order of arrival in the ready queue
 *          - once executed, wait until the next order is over
 *          - all processes have the same prioity
 * @version 0.1
 * @date    (first date: 2023-05-03, last date: 2023-05-15)
 * 
 * @copyright Copyright (c) 2023 Minsu Bak
 * 
 */

#ifndef FCFS_H
#define FCFS_H

// external library & user define library
#include "queue.h"
#include "process.h"
#include "compare.h"

/**
 * @brief FCFS.h variable info
 *  
 *  type        name             pointer     info
 *  Process     result           y           CPU scheduling result storage structure, reference from "process.h"
 *  Process     p                y           structure for process data storage
 *  Process     temp             y           pointer of process structure temporary variable
 *  QueueType   ready            n           queue structure for queue(for ready queue)
 *  QueueType   pre              n           queue structure for queue(for previous queue)
 *  int         total_turnaround n           the sum of turnaround
 *  int         total_waiting    n           the sum of waiting
 *  int         total_response   n           the sum of response
 *  int         result_index     n           index for result array
 *  int         n                n           save process count
 *  int         i                n           multipurpose utilization variable
 *  int         time             n           flow of time in the scheduler
 *  int         terminate        n           Number of process terminated
 *  
 */

extern Process result[MAX];

/**
 * @brief   First Come First Served
 * 
 * @param p pointer for process structure
 * @param n process count
 */
void FCFS(Process *p, int n) {
    
    // create variable, queue and etc

    int total_turnaround = 0;   
    int total_waiting    = 0;
    int total_response   = 0;
    int result_index     = 0;
    Process *temp     = NULL;
    QueueType ready, pre;

    // initalize queue
    init_queue(&ready);
    init_queue(&pre);

    // insert process to queue
    for(int i = 0; i < n; i++)
        enqueue(&pre, p[i]);

    // sort by arrival
    sort(&pre, compare_for_arrival);
    
    // running FCFS scheduling

    int time = 0; // flow of time in the scheduler
    int terminate = 0; // number of process terminated
    while(terminate < n) {
        
        // insert prcoess into the ready queue in order of arrive
        if(!is_empty_q(&pre)) {
            if(peek(&pre).arrival == time) {
                enqueue(&ready, *dequeue(&pre));
                if(CHECK) // debug
                    printf("arrival:\tt: %2d, p: %2d\n", time, ready.queue->processID);
            }
        }

        // dispatch new PCB: if the previous task terminated
        if(peek(&ready).arrival <= time && temp == NULL) {
            temp = dequeue(&ready);
            temp->waiting  = time - temp->arrival;
            total_waiting += temp->waiting;
            temp->execute  = 0;
            if(CHECK) // debug
                printf("dispatch:\tt: %2d, p: %2d, w: %2d\n", time, temp->processID, temp->waiting);
        }

        time++;

        // scheduler task progress
        if(temp != NULL) {
            temp->remain--;
            temp->execute++;

            // terminate present PCB
            if(temp->remain == 0) {
                if(CHECK) // debug
                    printf("terminate:\tt: %2d, p: %2d\n", time, temp->processID);
                total_turnaround      += temp->execute + temp->waiting;
                total_response        += temp->waiting;
                result[result_index++] = *temp;
                temp = NULL;
                terminate++;
            }
        }
    }

    // test
    print_result(
        result,\
        result_index,\
        n,\
        total_turnaround,\
        total_waiting,\
        total_response,\
        "FCFS"
    );
}

#endif