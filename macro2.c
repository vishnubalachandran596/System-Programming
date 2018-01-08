#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
void reverse(char str[], int length)
{
	char temp;
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        temp=*(str+start);
	 *(str+start)=*(str+end);
	*(str+end)=temp;
        start++;
        end--;
    }
}
char mne[20],opnd[20],la[20];
// Implementation of itoa()
char* itoa(int num, char* str, int base)
{
    int i = 0;
    int isNegative = 0;
 
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 
    // In standard itoa(), negative numbers are handled only with 
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = 1;
        num = -num;
    }
 
    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
 
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
 
    str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    reverse(str, i);
 
    return str;
}
void freads(FILE *fp)
{
char str[30],WOR[3][12],*pch;
int count,l,len[4];
count=0;
fgets(str,28,fp);
pch = strtok (str," \t\n");
  		while (pch != NULL)
  	{	l=strlen(pch);
		len[count]=l;
  	 	//printf ("%s\n",pch);
		//pch[l]='\0';
		strcpy(WOR[count],pch);
		WOR[count][l]='\0';
		count++;
		pch = strtok (NULL, "  \n");
 	 }
 	 strcpy(la,"");strcpy(mne,"");strcpy(opnd,"");
 	 switch(count)
 	 {
 	 	case 1: strcpy(la,"-");strcpy(mne,WOR[0]);strcpy(opnd,"-");break;
 	 	case 2: strcpy(la,"-");strcpy(mne,WOR[0]);strcpy(opnd,WOR[1]);break;
 	 	case 3:strcpy(la,WOR[0]);strcpy(mne,WOR[1]);strcpy(opnd,WOR[2]);break;
 	 }
 	 printf("%s%s%s",la,mne,opnd);
}
void main()
{
FILE *f1,*f2,*f3,*f4,*f5;
int len,i,pos=1;
char arg[20],name[20],mne1[20],opnd1[20],pos1[10],pos2[10];

f1=fopen("macin.txt","r");
f2=fopen("namtab.txt","w+");
f3=fopen("deftab.txt","w+");
f4=fopen("argtab.txt","w+");
f5=fopen("op.txt","w+");
fscanf(f1,"%s%s%s",la,mne,opnd);
printf("%s%s%s",la,mne,opnd);
while(strcmp(mne,"END")!=0)
{
printf("inloop");
if(strcmp(mne,"MACRO")==0)
{
fprintf(f2,"%s\n",la);
fseek(f2,SEEK_SET,0);
fprintf(f3,"%s\t%s\n",la,opnd);
//fscanf(f1,"%s%s%s",la,mne,opnd);
freads(f1);
while(strcmp(mne,"MEND")!=0)
{
if(opnd[0]=='&')
{
itoa(pos,pos1,5);
//snprintf(pos1, sizeof(pos1), "%d",pos);
strcpy(pos2,"?");
strcpy(opnd,strcat(pos2,pos1));
pos=pos+1;
}
fprintf(f3,"%s\t%s\n",mne,opnd);
//fscanf(f1,"%s%s%s",la,mne,opnd);
freads(f1);
}
fprintf(f3,"%s",mne);
}
else
{
fscanf(f2,"%s",name);
if(strcmp(mne,name)==0)
{
len=strlen(opnd);
for(i=0;i<len;i++)
{
if(opnd[i]!=',')
fprintf(f4,"%c",opnd[i]);
else
fprintf(f4,"\n");
}
fseek(f3,SEEK_SET,0);
fseek(f4,SEEK_SET,0);
fscanf(f3,"%s%s",mne1,opnd1);
fprintf(f5,".\t%s\t%s\n",mne1,opnd);
fscanf(f3,"%s%s",mne1,opnd1);
while(strcmp(mne1,"MEND")!=0)
{
printf("\n%s",opnd1);
if((opnd1[0]=='?'))
{
fscanf(f4,"%s",arg);
fprintf(f5,"\t%s\t%s\n",mne1,arg);
}
else
fprintf(f5,"\t%s\t%s\n",mne1,opnd1);
fscanf(f3,"%s%s",mne1,opnd1);
}fseek(f4,SEEK_SET,0);fprintf(f4,"\n");
}
else
{
if(la[0]!='-'&&opnd[0]!='-')
fprintf(f5,"%s\t%s\t%s\n",la,mne,opnd);
else if(la[0]!='-')
fprintf(f5,"%s\t%s\t\n",la,mne);
else if(opnd[0]!='-')
fprintf(f5,"\t%s\t%s\n",mne,opnd);
else
fprintf(f5,"\t%s\n",mne);
}
}
//fscanf(f1,"%s%s%s",la,mne,opnd);
freads(f1);
}
if(la[0]!='-'&&opnd[0]!='-')
fprintf(f5,"%s\t%s\t%s\n",la,mne,opnd);
else if(la[0]!='-')
fprintf(f5,"%s\t%s\t\n",la,mne);
else if(opnd[0]!='-')
fprintf(f5,"\t%s\t%s\n",mne,opnd);
else
fprintf(f5,"\t%s\n",mne);
fclose(f1);
fclose(f2);
fclose(f3);
fclose(f4);
fclose(f5);
printf("files to be viewed \n");
printf("1. argtab.txt\n");
printf("2. namtab.txt\n");
printf("3. deftab.txt\n");
printf("4. op.txt\n");

}
