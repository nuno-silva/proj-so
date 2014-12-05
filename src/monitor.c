#include "monitor.h"
#include "shared_stuff.h"

#include <unistd.h>
#include <signal.h> /* needs -D_POSIX_C_SOURCE if using -ansi */

static pid_t writer_pid = NULL;
static pid_t reader_pid = NULL;

pid_t run_writer(char* prog_path, int* pipefd) {
	int fork_res;
	fork_res = fork();

	if (fork_res == 0) {
		/* child */
		if (pipefd != NULL) {
			close(STDIN_FILENO); /* close the normal stdin */
			dup2(*pipefd[1], STDIN_FILENO);
		}
			execl(prog_path, NULL);

	}
	else if (fork_res == -1) {
		/* error */
		DBG_PRINT("fork() error\n");
	}
	else { 
		/* parent */
		return fork_res;
	}
}

void exit_monitor(pid_t writer_pid, pid_t reader_pid) {
	if (writer_pid == NULL || reader_pid == NULL) {
		/* something went wrong here... */
		DBG_PRINT("invalid children pid's\n");
		exit(-1);
	}
	close(pipefd[1]);
	close(pipefd[0]);
	kill(reader_pid, SIGSTP);
	
	if (wait(writer_pid) == -1) { 
		DBG_PRINT("failed waiting on writer_pid\n");
		exit(-1);
	}
	
	if (wait(reader_pid)== -1){
		 DBG_PRINT("failed waiting on reader_pid\n");
		 exit(-1);
	}
	return 0;
}

int main(void) {
	int pipefd[2];
	int read_res;
	int index;
	char* in_buffer[BUFFER_SIZE];
	char* aux_buffer[AUX_BUFFER_SIZE];

	if (pipe(pipefd) == -1)
		DBG_PRINT("Error while creating the pipe\n");

	writer_pid = run_proccess((char*)READER_PATH, &pipefd, );
	
	reader_pid = run_proccess((char*)READER_PATH, NULL);
	
	/* TODO: associate pipe */
	close(STDOUT_FILENO); /* close the normal stdout */
	dup2(*pipefd[0], STDOUT_FILENO);
}

void process_command(char* command) {

	if (!strcmp(command, EXIT_COMMAND)) {
		exit_monitor(writer_pid, reader_pid);
	}

	else if (!strcmp(command, SIGUSR1_COMMAND)) {
		/* TODO: call appropriare fuction */
	}

	else if (!strcmp(command, SIGUSR2_COMMAND)) {
		/* TODO: call appropriare fuction */
	}

	else {
		/* TODO: send filename to reder */
	}


}




void process_input(fd, buff, buff_size) {
	int i;

	for (i = 0; i < input_size; i++) {

		if (in_buff[i] == ' ') {
			// TODO: proccess aux_buffer
			aux_buffer[i] = '\0';
			process_command();
			aux_buffer[0] = '\0'; /* clear aux buffer */
		}
		aux_buff[i] = in_buffer[i];
	}
}

/*
SO-12.txt SO-13.txt sair
*/

/*
int main (void) {
	int writer_pid;
	int reader_pipe_fd;

	writer_pid = run_writer();
	// TODO: test for errors 

	reader_pipe_fd = run_reader();
	/* TODO: test for errors 

	for( ;; ) {
		//TODO: read command 
		// TODO: process command and call corresponding function  

		if (line == "sair") {
			close READER:
				end processing of the current file;
				close pipe;
			send SIGSTP to writer:
				end processing of the current file;
				// this ends the writer

		wait(writer);
		wait(reader);

		end myself;
		}

		if (line == il)
				send SIGUSR1 to writer;

		if(line == ie)
			send SIGUSR2 to writer;
	}

}
*/)