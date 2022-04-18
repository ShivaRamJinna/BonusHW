#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>


#define cmd_len 256
#define no_of_args 16
#define fSize 16

char InputString[cmd_len];//Input String
char *arguments[no_of_args];
int Array_length;
pid_t pid;

void ProcessInput(char *str, char** PostParsing)  
{
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
}//Challanges : Postparshing[1] is not being cleared after every iteration
//Fibonacci not working 



void hello()
{
	printf("Hello World!\n");
}

void Help()
{
	printf("***************************\n");
	printf("List of Commands Supported:\n"
		   "***************************\n"
		   "list – list all the files in the current directory.\n"
		   "cd <directory> – change the current directory to the <directory>.\n"
		   "help – display the internal commands and a short description on how to use them\n"
		   "quit – quit the shell program.\n"
		   "history - display all the previous command entered into the shell program.\n");
	printf("***************************\n");
}

void fibonacci()
{
	//Implement if argv == 1 -> Fibonacci no args
	//Else if argv == 2 -> Fibonacci with args 
	int n, i;
	n = 0;
	int n1 = 0, n2 = 1, next = n1+n2;
	printf("How many elements you want to display:\t");
	scanf("%d", &n);
	if(n<0)
	{
		printf("Invalid input\n");
	}
	else
	{
		printf("The first %d values: %d, %d, ",n , n1, n2);
		for (i = 3; i <= n; i++)
		{
		    printf("%d, ", next);
		    n1 = n2;
		    n2 = next;
		    next = n1 + n2;
  		}
  		printf("\n");
	}
	//return;

}

void fibonacci_Args(int n){    
    static int n1=0,n2=1,next; 
      
    if(n>0){    
         next = n1 + n2;    
         n1 = n2;    
         n2 = next;    
         printf("%d, ",next);    
         fibonacci_Args(n-1);    
    }    
}  


int Built_inCommands(char** PostParsing)
{
	if(strcmp("quit", PostParsing[0]) == 0)
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
	else if(strcmp("cd", PostParsing[0]) == 0)
	{
		chdir(PostParsing[1]);
		return 0;
	}

	//PENDING
	else if(strcmp("fibonacci", PostParsing[0]) == 0)
	{
		if(PostParsing[1] > 0)
		{
			int d1=0, d2=1;
			//printf("inside Args");
			int key = atoi(PostParsing[1]);
			printf("%d ,%d, ", d1, d2);
			fibonacci_Args(key);
			printf("\n");
		}
		else
		{
			fibonacci();
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

void logHistory(char* str, FILE* fp, char* fileName)
{
	fp = fopen(fileName, "a");
    if (fp == NULL)
    {
        printf("\nUnable to open file.\n");
    }
    fputs(str, fp);
    fputs("\n",fp);
    fclose(fp);
}
void ViewLog(FILE* fp,char* fileName)
{
	char ch;
	fp = fopen(fileName, "r");
	do {
        ch = fgetc(fp);
        printf("%c", ch);
    } while (ch != EOF);

}
int main(int argc, char const *argv[])
{	
	char logFile[] = "uab_sh.log";
	remove(logFile);
	FILE* filePtr;
	//filePtr = fopen(logFile, "a");

	while(1)
	{
		memset(arguments, 0, no_of_args);
		ProcessInput(InputString, arguments);
		logHistory(InputString, filePtr, logFile);
		int is_builtInCmd = 0;
		is_builtInCmd = Built_inCommands(arguments);
		if(strcmp("history", arguments[0]) == 0)
		{
			ViewLog(filePtr, logFile);
		}
		else if(is_builtInCmd == 1)
		{
			//printf("Hello From Fork\n");
			Fork_Exec(arguments);
		}
	}
	return 0;
}
