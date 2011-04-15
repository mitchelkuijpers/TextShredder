#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int conf;
int numberOfLines;

int pass;
int failed;
int skipped;

#define kBufferSizes 1024

#define kAllConfig 1
#define kResultConfig 2
#define kFailedConfig 3


int main(int argc, char *argv[]);
void readLines(char *testProgram);
void parentFileReaderWithPipes(pid_t pid, int *outputPipe, int *inputPipe);
int shouldWriteLineStartingWithCharacter(char c);
void executeChildProcess(char *program, char **arguments, int *outputPipe, int *inputPipe);
#endif