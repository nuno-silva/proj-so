#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "writer.h"

#define BUFFER_CHAR_COUNT 32


int run_and_wait_for_children() {
    int fork_result;
    int i;
    for (i = 0; i < CHILDREN; i++)
    {
        fork_result = fork();
        if (fork_result == -1) {
            return -1; // ERROR
        }
        else if (fork_result == 0) { // child
            printf("child %d\n", i);
            execl(WRITER_MAIN_PATH, WRITER_MAIN_PATH, NULL);
        }
        else { // parent
            printf("parent %d\n", i);
        }
    }
    
    wait(); // wait for all childs to terminate
    return 0;
}

int main (int argc, char *argv[]) {
    int ret;
    struct timeval tvstart;     /* data de inicio */
    struct timeval tvend;       /* data de fim */
    struct timeval tvduration;  /* diferenca entre as duas datas */
    unsigned int duration_us;   /* diferenca entre as datas em microssegundos */
    
    time_t curtime;     /* tempo em formato time_t para conversao de formatos */
    char buffer[BUFFER_CHAR_COUNT];/* para escrever a data em formato legivel */
    
    gettimeofday(&tvstart, NULL); /* ler a data actual */
    /* converter e imprimir a data */
    curtime = tvstart.tv_sec;
    strftime(buffer, BUFFER_CHAR_COUNT, "%m-%d-%Y  %T.", localtime(&curtime));
    printf("inicio: %s%ld\n", buffer, tvstart.tv_usec);
    
    ret = run_and_wait_for_children();
    if(ret < 0) // error
        return ret;
    
    gettimeofday(&tvend, NULL); /* ler a data actual */
    
    /* converter e imprimir a data */
    curtime = tvend.tv_sec;
    strftime(buffer, BUFFER_CHAR_COUNT, "%m-%d-%Y  %T.", localtime(&curtime));
    printf("fim: %s%ld\n", buffer, tvend.tv_usec);
    
    /* calcular e imprimir a diferenca de datas */
    tvduration.tv_sec = tvend.tv_sec - tvstart.tv_sec;
    tvduration.tv_usec = tvend.tv_usec - tvstart.tv_usec;
    duration_us = tvduration.tv_sec * 1000000 + tvduration.tv_usec;
    printf("duracao: %.4f segundos\n", ((float)duration_us)/1000000.0f);
    
    
    return ret;
}
