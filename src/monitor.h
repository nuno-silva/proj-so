#ifndef __MONITOR_H__
    #define __MONITOR_H__
    
    #define WRITER_PATH "./writer_parallel"
    #define READER_PATH "./reader_parallel"
    
    #define INPUT_BUFFER_SIZE 512
    
    #define EXIT_COMMAND    "sair"
    #define SIGUSR1_COMMAND "il"
    #define SIGUSR2_COMMAND "ie"
    
    #define LINE_FEED		"\n"
    #define LINE_FEED_LEN	(1)
    
    int run_proccess(char* prog_path, int* stdin_pipe_fd);
    
    void exit_monitor();
    
    int process_command(char* command);

#endif