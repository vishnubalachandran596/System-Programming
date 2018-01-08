#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void main()
{
	FILE *fp1,*fp2;
	fp1=fopen("input.txt","r+");
	fp2=fopen("output.txt","w+");
	char line[100],objcode[20],loc[10];
	int locctr=0,i=0,j=0,k=0,length=0;
	fscanf(fp1,"%s",line);
	strcat(line,"\0");
	if(line[0]=='H')
	{ i=2;
	  while(line[i]!='^')
	  {
		i++;	  
	  }
	  i=i+1;
	  j=0;
	   while(line[i]!='^')
	  {
	  	loc[j]=line[i];
	  	printf("%c\n",line[i]);
		i++;
		j++;	  
	  }
	  	strcat(loc,"\0");
	  	locctr=(int)strtol(loc, NULL, 16);	
	  	printf("%x\n",locctr);
	}
		strcpy(line,"\0");
		fscanf(fp1,"%s",line);
		strcat(line,"\0");
	while(!feof(fp1))
	{
		printf("%x",k);
	 k=10;
	 
	 while(line[k]!='\0')   
		{   	printf("%x",k);
		    j=0;
		    strcpy(objcode,"\0");
			while((line[k]!='^')&&(line[k]!='\0'))
			{
				objcode[j]=line[k];
				k++;
				j++;
			}
			
		   strcat(objcode,"\0");
		   printf("%s\n\n",objcode);
		   fprintf(fp2,"%04x\t%s\n",locctr,objcode);
		   fflush(fp2);
		   locctr=locctr+3;
		   if(line[k]=='\0')
			 {
			  break;
			 }
		   k=k+1;
		}
		
	    strcpy(line,"\0");
	
		fscanf(fp1,"%s",line);
	     length=strlen(line);
	     line[length]='\0';
	     printf("%s",line);
		strcat(line,"\0");
		i=2;	
		j=0;
	   while(line[i]!='^')
	  {
	  	loc[j]=line[i];
		i++;
		j++;	  
	  }
	  	strcat(loc,"N");
	  	locctr=(int)strtol(loc, NULL, 16);	
	}
	
}
