#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#include "writer_parent_main.h"
#include "shared_stuff.h"
#include "writer_constants.h"

#define BUFFER_CHAR_COUNT 32


int run_and_wait_for_children(int cycle_count, int children_count) {
    int fork_result;
    int i;
    char arg[32];
    for (i = 0; i < children_count; i++)
    {
        fork_result = fork();
        if (fork_result == -1) {
            printf("fork() failed. errno=%d", errno);
            return -1; // ERROR
        }
        else if (fork_result == 0) { // child
            DBG_PRINTF("child %d\n", i);
            sprintf(arg, "%d", cycle_count/children_count);
            if( execl(WRITER_MAIN_PATH, WRITER_MAIN_PATH, arg, NULL) == -1 ) {
                printf("execl(%s) failed. errno=%d", WRITER_MAIN_PATH, errno);
            }
        }
        else { // parent
            DBG_PRINTF("parent %d\n", i);
        }
    }
    
    while(children_count--) { // wait for all children to terminate
        wait(NULL); // wait for one child
    }
    return 0;
}

/* 
 * The writer program receives the number of cycles as the first argument.
 * Usage: writer [TOTAL_WRITER_CYCLE_COUNT=5120]
 */

int main() {
    int ret;
    struct timeval tvstart;     /* data de inicio */
    struct timeval tvend;       /* data de fim */
    struct timeval tvduration;  /* diferenca entre as duas datas */
    unsigned int duration_us;   /* diferenca entre as datas em microssegundos */
    
    time_t curtime;             /* tempo em formato time_t para conversao de formatos */
    char buffer[BUFFER_CHAR_COUNT]; /* para escrever a data em formato legivel */
    
    gettimeofday(&tvstart, NULL);   /* ler a data actual */
    /* converter e imprimir a data */
    curtime = tvstart.tv_sec;
    strftime(buffer, BUFFER_CHAR_COUNT, "%m-%d-%Y  %T.", localtime(&curtime));
    printf("inicio: %s%ld\n", buffer, (long int)tvstart.tv_usec);
    
    ret = run_and_wait_for_children(TOTAL_WRITER_CYCLE_COUNT, CHILDREN_COUNT);
    if (ret < 0) // error
        return ret;
    
    gettimeofday(&tvend, NULL); /* ler a data actual */
    
    /* converter e imprimir a data */
    curtime = tvend.tv_sec;
    strftime(buffer, BUFFER_CHAR_COUNT, "%m-%d-%Y  %T.", localtime(&curtime));
    printf("fim: %s%ld\n", buffer, (long int)tvend.tv_usec);
    
    /* calcular e imprimir a diferenca de datas */
    tvduration.tv_sec = tvend.tv_sec - tvstart.tv_sec;
    tvduration.tv_usec = tvend.tv_usec - tvstart.tv_usec;
    duration_us = tvduration.tv_sec * 1000000 + tvduration.tv_usec;
    printf("duracao: %.4f segundos\n", ((float)duration_us)/1000000.0f);
    
    
    return ret;
}
