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

void fibonacci_Args(int n)
{    
    static int n1=0,n2=1,next;   
    if(n>0){    
         next = n1 + n2;    
         n1 = n2;    
         n2 = next;    
         printf("%d, ",next);    
         fibonacci_Args(n-1);    
    }    
}