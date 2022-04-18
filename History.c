#include<stdio.h>
#include<unistd.h>
#include<string.h>

void logHistory(char** PostParsing, FILE* fp, char* fileName)
{
	fp = fopen(fileName, "a");
    if (fp == NULL)
    {
        printf("\nUnable to open file.\n");
    }
    if(PostParsing[1] > 0)
	{
		fputs(PostParsing[0], fp);
		fputs(" ", fp);
    	fputs(PostParsing[1], fp);
	}
    else
    {
    	fputs(PostParsing[0], fp);
    }
    fputs("\n",fp);
    fclose(fp);
}
void ViewLog(FILE* fp,char* fileName)
{
	char ch;
	fp = fopen(fileName, "r");
	while ((ch = fgetc(fp)) != EOF)
	{
        putchar(ch);
	}
    fclose(fp);
}