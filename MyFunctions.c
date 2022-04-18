#include<stdio.h>
#include<dirent.h>

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
void fibonacci(int n)
{
	int i;
	int n1 = 0, n2 = 1, next = n1+n2;
	//fgets (*n, sizeof n, stdin);
	if(n<0)
	{
		printf("Invalid input\n");
	}
	else
	{
		printf("The first %d values: %d, %d, ",n , n1, n2);
		for (i = 2; i < n; i++)
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

void list()//Refernce from HomeWork-2
{
	struct dirent *dirent;
	DIR *rootDir = opendir(".");
	if(rootDir == NULL)
	{
		printf("Unable to open Directory");
		return;
	}
	while((dirent = readdir(rootDir)) != NULL)
	{
		printf("%s\n", dirent->d_name);
	}
	closedir(rootDir);
	return;


}