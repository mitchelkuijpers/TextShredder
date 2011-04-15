/*
 * Program to parse QTestLib application output.
 * Program can be made by a make file.
 * Input should be: './testparser [executable] <option>
 *
 * exexutable: the testexecutable created by qt.
 * option: can be '-r', '-f' or '-a'. r is for only results. f is for only failures. a is for all results.
 * Author: Mats Stijlaart.
 * Date: Does it really mather?
 */

#include "testparser.h"

int main(int argc, char *argv[]) {
	
	//Check arguments
	if(argc < 3) {
		printf("Supply a enough arguments\n");
		exit(1); 
	}
	
	if (strcmp(argv[2],"-r") == 0) {
		conf = kResultConfig;
	} else if(strcmp(argv[2], "-f") == 0) {
		conf = kFailedConfig;
	} else if(strcmp(argv[2], "-a") == 0) {
		conf = kAllConfig;
	} else {
		printf("Second argument is incorrect, should be: -r(esults), -f(ail) or -a(ll) \n");
		exit(2);
	}
	
	readLines(argv[1]);
	return 0;
}

void readLines(char *testProgram) {
	int mainToChildPipe[2];
	int childToMainPipe[2];
	pipe(mainToChildPipe);
	pipe(childToMainPipe);
	
	int status;
	
	pid_t pid = fork();
	if ( pid == -1 ) {
		printf("Could not fork\n");
		exit(1);
	} else if ( pid == 0 ) {
		/* Close unnecessary pipe ends.*/
		close(mainToChildPipe[1]);  
		close(childToMainPipe[0]);
		
		/* Execute child process with correct pipes */
		char *arguments[2];
		arguments[0] = testProgram;
		arguments[1] = NULL;
		executeChildProcess(testProgram, arguments, &childToMainPipe[1], &mainToChildPipe[0]);
		
		/*Close the rest of the pipes. */
		close(mainToChildPipe[0]);
		close(childToMainPipe[1]);
		
		exit(0);
	} else if ( pid > 0 ) {
		close(mainToChildPipe[0]);
		close(childToMainPipe[1]);
		parentFileReaderWithPipes(pid, &mainToChildPipe[1], &childToMainPipe[0]);
		
		while(wait(&status) != pid)
			;
	}
}

void parentFileReaderWithPipes(pid_t pid, int *outputPipe, int *inputPipe) {
	char buffer[kBufferSizes] = {0};
	int reading = 1;
	int i;
	usleep(1000);
	int printLine = 1;
	int beginOfLine = 1;
	
	while(reading) {
		int readResult = read(*inputPipe, buffer, kBufferSizes-1);
		if (readResult == 0) {
			reading = 0;
		} 
		if (readResult > 0) {
			
			buffer[readResult] = '\0';
			for (i = 0; i < readResult; i++ ) {
				if (beginOfLine) {
					if (1) {
						printLine = shouldWriteLineStartingWithCharacter(buffer[i]);
					} 
					if (printLine)
						printf("%c", buffer[i]);

					beginOfLine = 0;
					
					if (buffer[i] == '\n')
						beginOfLine = 1;
				} else {
					if (printLine) {
						printf("%c", buffer[i]);
					}
					if (buffer[i] == '\n')
						beginOfLine = 1;
				}
			}		
		}
	}
	printf("\nTest result is:\n\tPASSED:  %d\n\tFAILED:  %d\n\tSKIPPED: %d\n", pass, failed, skipped);
}

void executeChildProcess(char *program, char **arguments, int *outputPipe, int *inputPipe) {
	dup2(*outputPipe, 1); /* Redirect the stdout to write to the parent. */
	dup2(*inputPipe, 0); /* Redirect the stdin to the input pipe that will be filled by the parent */
	execvp(program, arguments);//execute the program with the arguments
	printf("Could not execute program\n");
}

int shouldWriteLineStartingWithCharacter(char c) {
	if (c == '*') {
		return 0;
	} else if (c == 'P') {
		pass++;
		if (kAllConfig == conf)
			return 1;
		return 0;
	} else if (c == 'F') {
		failed++;
		if (kAllConfig == conf || kFailedConfig == conf)
			return 1;
		return 0;
	} else if (c == 'S') {
		skipped++;
		failed++;
		if (kAllConfig == conf)
			return 1;
		return 0;
	} else if (c == ' ') {
		if (kAllConfig == conf || kFailedConfig == conf)
			return 1;
		return 0;
	} 
	return 0;
}
