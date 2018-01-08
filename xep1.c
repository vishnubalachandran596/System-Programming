#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char symtab[150][20];
int sym[150];
char symh[150][5];
char ltab[150][20];
int li[150];
char lih[150][5];
char op[150][20];
char val[150][20];
char source[200][100];
int i1=0,i2=0;
int n;
void hadd(char a[],char b[])
	{
		int b1=0,c1=0,t1,p1,i,j,flag;
		for(i=0;i<4;i++)
			{if(a[i]>='A')
				t1=a[i]-'A'+10;
			else
				t1=a[i]-'0';
			if(b[i]>='A')
				p1=b[i]-'A'+10;
			else
				p1=b[i]-'0';
		b1=b1*16+t1;
		c1=c1*16+p1;}
		b1=b1+c1;
		for(j=3,flag=b1;j>=0;j--)
			{
					a[j]=flag%16;
				if((flag%16)<10)
					a[j]=a[j]+48;
				else
					a[j]=a[j]+55;
					flag=flag/16;
			}
		a[4]='\0';
	}
void pass1()
	{
		FILE *fp;
		int lcc;
		int flag,i,j,p,q;
		FILE *fp1,*fp2,*fp3;
		fp=fopen("xep1.txt","r");
		fp1=fopen("intermediate-xe.txt","w");
		fp2=fopen("symtab-xe.txt","w");
		fp3=fopen("litab-xe.txt","w");
		for(i=0;fgets(source[i],100,fp);i++)
			{
			}
		n=i-1;
		for(i=0,p=0;i<n;i++)
			{
				while(source[i][0]=='.')
					i++;
				for(j=0,q=0,flag=1;source[i][j]!='\0';j++,q++)
					{
						if(source[i][j]==' ' && flag==2)
							{
								op[i][q]='\0';
								q=0;
								flag++;j++;
							}
						if(source[i][j]==' ' && flag==1)
							{
								symtab[i][q]='\0';
								sym[i]=p;
								q=0;
								flag++;j++;
							}
						if(flag==1)
						symtab[i][q]=source[i][j];
						if(flag==2)
						op[i][q]=source[i][j];
						if(flag==3)
						val[i][q]=source[i][j];
						if(source[i][j]==' ' && flag==3)
							break;
					}
						val[i][strlen(val[i])-1]='\0';
						if(val[i][0]=='=')
							{strcpy(ltab[i1],val[i]);i1++;}
						if(!strcmp(op[i],"LTORG"))
						   {	while(i1>i2)
								{
									li[i2]=p;
									p=p+strlen(ltab[i2]);
									i2++;
								}
							p=p-3;
						   }
						if(!strcmp(op[i],"BYTE"))
						{
							lcc=strlen(val[i]);

							lcc=lcc-3;
							if(val[i][0]=='X')
							if(lcc%2)
							lcc=(lcc/2)+1;
							else
							lcc=lcc/2;
							p=p+lcc-3;
						}
					if(!strcmp(op[i],"RESW"))
						{
							lcc=atoi(val[i]);
							lcc=3*lcc;
							p=p+lcc-3;
						}
					if(!strcmp(op[i],"RESB"))
						{
							lcc=atoi(val[i]);
							p=p+lcc-3;
						}
						if(op[i][0]=='+')
						p=p+4;
						else
						if(op[i][strlen(op[i])-1]=='R')
						p=p+2;
						else
						p=p+3;
			}
				while(i1>i2)
					{
						li[i2]=p;
						p=p+strlen(ltab[i2]);
						i2++;
					}
				for(i=0;i<n;i++)
					sym[i]=sym[i]-3;
				for(i=0;i<i2;i++)
					li[i]=li[i]-3;
					sym[0]=sym[0]+3;
		for(i=0;i<n;i++)
			{
			   for(j=3,flag=sym[i];j>=0;j--)
				{
					symh[i][j]=flag%16;
					if((flag%16)<10)
						symh[i][j]=symh[i][j]+48;
					else
						symh[i][j]=symh[i][j]+55;
					flag=flag/16;
				}
			   symh[i][4]='\0';
			}
		for(i=0;i<i2;i++)
			{
			   for(j=3,flag=li[i];j>=0;j--)
				{
					lih[i][j]=flag%16;
					if((flag%16)<10)
						lih[i][j]=lih[i][j]+48;
					else
						lih[i][j]=lih[i][j]+55;
					flag=flag/16;
				}
			   lih[i][4]='\0';
			}
		for(i=0;i<n;i++)
			hadd(symh[i],val[0]);
		for(i=0;i<i2;i++)
			hadd(lih[i],val[0]);
		for(i=0;i<n;i++)
			{
			    if(strlen(symtab[i])>0)
				{
                			fputs(symtab[i],fp2);
                			fputs(" ",fp2);
                			fputs(symh[i],fp2);
                			fputs("\n",fp2);
				}
			}
		printf("\n\nSYMBOL TABLE generated\n");
		for(i=0;i<i1;i++)
			{
				ltab[i][strlen(ltab[i])-1]='\0';
                		fputs(ltab[i],fp3);
                		fputs(" ",fp3);
                		fputs(lih[i],fp3);
                		fputs("\n",fp3);
			}
		printf("\n\nLITERAL TABLE generated\n");
		for(i=0;i<n;i++)
			{
					fputs(symh[i],fp1);
					fputs(" ",fp1);
					fputs(op[i],fp1);
                			fputs(" ",fp1);
					if(strlen(val[i])>0)
                			fputs(val[i],fp1);
                			fputs("\n",fp1);
			}
		printf("\n\nINTERMEDIATE FILE generated\n");

	}

void main()
	{

		int o;
		pass1();
	}

