//gcc -o uab_sh uab_sh.c Myfunctions.c History.c   
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include"MyFunctions.h"//All the built in commands
#include"History.h"//Functions related to logs


#define cmd_len 256
#define no_of_args 16
#define fSize 16
#define pathLen 101


char InputString[cmd_len];//Input String
char *arguments[no_of_args];
int Array_length;
pid_t pid;

void ProcessInput(char *str, char** PostParsing)  
{

	memset(arguments, 0, no_of_args);
	//Takes Input from "uab_sh >"and assigns it to Char Args
	printf("uab_sh> ");
	char *temp;
	int currentLength;
	fgets(str, cmd_len, stdin);
	str[strcspn(str, "\n")] = 0;
	//split input string into Tokens and storing them in char array
	currentLength = 0;
	temp = strtok(str," ");
    while (temp != NULL)
    {
        PostParsing[currentLength] = temp;
        currentLength++;
        temp = strtok (NULL, " ");
    }
}
//Challanges : Postparshing[1] is not being cleared after every iteration
//Fibonacci not working 
int Built_inCommands(char** PostParsing)
{
	if(strcmp("", PostParsing[0]) == 0)
	{
		//continue;
		return 0;
	}
	else if(strcmp("quit", PostParsing[0]) == 0)
	{
		exit(0);
	}
	else if(strcmp("hello", PostParsing[0]) == 0)
	{
		hello();
		return 0;
	}
	else if(strcmp("help", PostParsing[0]) == 0)
	{
		Help();
		return 0;
	}
	else if(strcmp("list", PostParsing[0]) == 0)
	{
		list();
		return 0;
	}
	else if(strcmp("cd", PostParsing[0]) == 0)
	{
		if(PostParsing[1] > 0)
		{
			chdir(PostParsing[1]);
		}
		else
		{
			chdir("..");
		}
		return 0;
	}
	//PENDING
	else if(strcmp("fibonacci", PostParsing[0]) == 0)
	{
		/*
		if(PostParsing[1] > 0)
		{
			int d1=0, d2=1;
			//printf("inside Args");
			int key = atoi(PostParsing[1]);
			printf("%d ,%d, ", d1, d2);
			fibonacci_Args(key);
			printf("\n");
			//return 0;
		}
		else
		{
			fibonacci();
			//return 0;
		}
		*/
		if(PostParsing[1] > 0)
		{
			int key = atoi(PostParsing[1]);
			fibonacci(key);
		}
		else
		{
			printf("How many elements you want to display: ");
			int n;
			scanf("%d", &n);
			fibonacci(n);
		}
		return 0;
	}

	return 1;
}

void Fork_Exec(char** PostParsing)
{
	// Forking a child
	pid = fork();

	if (pid == -1)
	{
		printf("\nfork Failed to create a child process.");
		return;
	}
	else if (pid == 0)
	{
		execvp(PostParsing[0], PostParsing);
		return;
	}
 	else
 	{
		wait(NULL);
		return;
	}
}
int main(int argc, char const *argv[])
{
	char logFile[] = "uab_sh.log";
	remove(logFile);
	char path[pathLen];
	getcwd(path, pathLen);//getting Current directry
	strcat(path, "/");
	strcat(path, logFile);

	FILE* filePtr;
	while(1)
	{
		ProcessInput(InputString, arguments);//Start Terminal and Parse input
		logHistory(arguments, filePtr, path);//Log all the commands
		int is_builtInCmd = 0;
		is_builtInCmd = Built_inCommands(arguments);//Executing built in commands
		if(strcmp("history", arguments[0]) == 0)
		{
			ViewLog(filePtr, logFile);
		}
		if(is_builtInCmd == 1)//If Built_inCommands returns 1, Execute System Commands
		{
			//printf("Hello From Fork\n");
			Fork_Exec(arguments);
		}
	}
	return 0;
}