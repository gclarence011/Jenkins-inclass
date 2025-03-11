#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
void signal_handler(int sig){
	(void)sig; // Sig is not being use
	exit(5);
}

int main ()
{
	pid_t pid;

	// Fork a child process
	pid = fork();

        // If Error occurred
	if (pid < 0) {
		fprintf(stderr, "Fork Failed");
		exit(1);
	}

	// Child Process
	if (pid == 0) {
		// Set up SIGINT and make sure it works
		if(signal(SIGINT, signal_handler) == SIG_ERR) {
			fprintf(stderr,"Error while installing a signal handler\n");
			exit(1);
		}
		// Print child pid
		fprintf(stdout,"%d\n", getpid());

		// Pause child process until signal recieve
		pause();
	}
	// Parent Process
	else {
		// Wait for the child process to finish
		int status;
		if (waitpid(pid, &status, 0) == -1) {
			fprintf(stderr, "Error while waiting for child process\n");
			exit(1);
		}

		// Print the Child ID and exit status
		fprintf(stdout, "childpid=%d,exitstatus=%d\n", getpid(), WEXITSTATUS(status));
	}

	return 0;
}

