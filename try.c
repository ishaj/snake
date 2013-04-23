#include<stdio.h>
#include<stdlib.h>
FILE *fp;
int main()
{
	int temp,opcode,line,vis,c=0,j=0,i,x=12;
	char ch=1,ar[10],ar1[10];
	fp = fopen("disp2.txt","r+");
		while(score!=0)
		{
		ar[c++]=((score%10)+48);
		x=x/10;
		}
		for(ai=c-1;ai>=0;ai--)
		ar1[j++]=ar[ai];
		ar1[j]='\0';
		printf("%s",ar1);
	fclose(fp);
	return 0;
}

