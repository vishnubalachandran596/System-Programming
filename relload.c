#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void main()
{
	FILE *fp1,*fp2;
	fp1=fopen("input.txt","r+");
	fp2=fopen("output.txt","w+");
	char line[100],objcode[20],loc[10],exp[20];
	int locctr=0,i=0,j=0,k=0,length=0,locctra=0,l,q=0,locct;
	fscanf(fp1,"%s",line);
	strcat(line,"\0");
	printf("Enter Address to load Object Code:");
	scanf("%x",&locctra);
	printf("%x\n",locctra);
	l=locctra;
		strcpy(line,"\0");
		fscanf(fp1,"%s",line);
		
		strcat(line,"\0");
	while(!feof(fp1))
	{
	
	 k=10;
	 
	 while(line[k]!='\0')   
		{   	
		   
		    j=0;
		    strcpy(objcode,"\0");
			while((line[k]!='^')&&(line[k]!='\0'))
			{
				objcode[j]=line[k];
				k++;
				j++;
			}
			
		   strcat(objcode,"\0");
		   
		   q=0;
		   
		   if((objcode[0]>'0')||(objcode[1]>'0'))
		   { 
		   	for(j=2;objcode[j]!='\0';j++)
		   		{
		   		  exp[q]=objcode[j];
					 q++;	
				}
				exp[q]='\0';
				locct=(int)strtol(exp, NULL, 16);
				locct=locct+l;
				fprintf(fp2,"%04x\t%c%c%x\n",locctra,objcode[0],objcode[1],locct);
				
		   }
		   else
		   {
		   
		   fprintf(fp2,"%04x\t%s\n",locctra,objcode);
		   fflush(fp2);
	       }
		   locctra=locctra+3;
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
	     
		strcat(line,"\0");
		i=2;	
		j=0;
	   while(line[i]!='^')
	  {
	  	loc[j]=line[i];
		i++;
		j++;	  
	  }
	  	strcat(loc,"\0");
	  	locctr=(int)strtol(loc, NULL, 16);
		locctra=l+(locctr-1000);  	
	}
	fclose(fp1);
	fclose(fp2);
}
