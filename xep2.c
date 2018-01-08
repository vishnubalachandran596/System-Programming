#include<stdio.h>
#include"string.h"
#include<stdlib.h>
char optab[23][5]={"WD","RD","TD","RSUB","LDCH","COMP","JSUB","J","LDA","STA","LDX","STX","LDB","STB","ADD","SUB","MUL","DIV","JLT","JGT","JEQ","TIX","LDL"};
char opcode[23][2]={"00","04","08","10","14","18","20","24","28","30","34","38","40","44","48","50","54","58","60","64","68","70","74"};
char symtab[150][20];
char symh[150][5];
char litab[150][20];
char lih[150][5];
char lc[150][5];
char op[150][20];
char val[150][20];
char obj[200][25];
char source1[200][100];
char source2[200][100];
char source3[200][100];
char mod[100][100];int modi=1;
int k=0,l=0,m=0,k1=0,l1=0;
int n,n1,n2,pp;
char opp[2];
char reg[7]="AXLBSTF";
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
		b1=b1-c1;
		if(b1>=0)
		for(j=3,flag=b1;j>=0;j--)
			{
					a[j]=flag%16;
				if((flag%16)<10)
					a[j]=a[j]+48;
				else
					a[j]=a[j]+55;
					flag=flag/16;
			}
		else{
            b1=-b1;
            for(j=3,flag=b1;j>=0;j--)
			{
					a[j]=flag%16;
				if((flag%16)<10)
					a[j]=a[j]+48;
				else
					a[j]=a[j]+55;
					flag=flag/16;
			}
			for(j=0;j<4;j++)
			switch(a[j])
                    {
                        case '0': a[j]='F';break;
                        case '1': a[j]='E';break;
                        case '2': a[j]='D';break;
                        case '3': a[j]='C';break;
                        case '4': a[j]='B';break;
                        case '5': a[j]='A';break;
                        case '6': a[j]='9';break;
                        case '7': a[j]='8';break;
                        case '8': a[j]='7';break;
                        case '9': a[j]='6';break;
                        case 'A': a[j]='5';break;
                        case 'B': a[j]='4';break;
                        case 'C': a[j]='3';break;
                        case 'D': a[j]='2';break;
                        case 'E': a[j]='1';break;
                        case 'F': a[j]='0';break;
                    }
		}

		a[4]='\0';
	}
int srs(char a[])
	{int i;
	 char ab[25];
		for(i=0;i<k;i++){
			strcpy(ab,symtab[i]);
			if(strcmp(ab,a)==0)
			   return(i);
	}
		return(-1);
	}

int srl(char a[])
	{int i;
	 char ab[25];
		for(i=0;i<k;i++){
			strcpy(ab,litab[i]);
			if(strcmp(ab,a)==0)
			   return(i);
	}
		return(-1);
	}

int srop(char a[])
	{int i;
		for(i=0;i<23;i++)
			{
			 if(!strcmp(optab[i],a))
			   {
				strcpy(opp,opcode[i]);
				return(1);
			   }
			}
		return(0);
	}
int srr(char a)
	{int i;
		for(i=0;i<7;i++)
			{
			 if(reg[i]==a)
			   return(i);
			}
		return(-1);
	}
void fn1()
	{
		int flag,i,j,p,q;
		FILE *fp1,*fp2,*fp3;
		fp1=fopen("intermediate-xe.txt","r");
		fp2=fopen("symtab-xe.txt","r");
		fp3=fopen("litab-xe.txt","r");
		for(i=0;fgets(source1[i],100,fp1);i++);

		n=i;
		for(i=0;fgets(source2[i],100,fp2);i++);

		n1=i;
		for(i=0;fgets(source3[i],100,fp3);i++);

		n2=i;

		for(i=0;i<n;i++)
			{
				for(j=0,q=0,flag=1;source1[i][j]!='\0';j++,q++)
					{
						if(source1[i][j]==' ' && flag==2)
							{
								q=0;
								flag++;j++;
							}
						if(source1[i][j]==' ' && flag==1)
							{
								q=0;
								flag++;j++;
							}
						if(flag==1)
						lc[k1][q]=source1[i][j];
						if(flag==2)
						op[l][q]=source1[i][j];
						if(flag==3)
						val[m][q]=source1[i][j];
					}
						val[m][q-1]='\0';
						if(val[m][q-2]=='\n'||val[m][q-2]=='\r')
							val[m][q-2]='\0';
						m++;l++;k1++;
			}
		for(i=0;i<n1;i++)
			{
				for(j=0,q=0,flag=1;source2[i][j]!='\0';j++,q++)
					{
						if(source2[i][j]==' ' && flag==1)
							{
								q=0;
								flag++;j++;
							}
						if(flag==1)
						symtab[k][q]=source2[i][j];
						if(flag==2)
						symh[k][q]=source2[i][j];
					}
				symh[k][q-1]='\0';
				k++;
			}
		for(i=0;i<n2;i++)
			{
				for(j=0,q=0,flag=1;source3[i][j]!='\0';j++,q++)
					{
						if(source3[i][j]==' ' && flag==1)
							{
								q=0;
								flag++;j++;
							}
						if(flag==1)
						litab[l1][q]=source3[i][j];
						if(flag==2)
						lih[l1][q]=source3[i][j];
					}
				lih[l1][q-1]='\0';
				l1++;
			}
	}

void pass2()
	{
		fn1();
		char temp[100];
		int pppr;
		int j,i,t=0,z,i1,b;
		char xc[6];
		char tp[4];pp=1;
        t++;                obj[t][0]='T';i=0;
							obj[t][1]='^';
							obj[t][2]='0';
							obj[t][3]='0';
							obj[t][4]=lc[i][0];
							obj[t][5]=lc[i][1];
							obj[t][6]=lc[i][2];
							obj[t][7]=lc[i][3];
							obj[t][8]='^';
							n=10*3;
                        				if((n%16)<10)
								obj[t][10]=n%16+48;
                        				else
     									obj[t][10]=n%16+55;
                        				if(((n/16)%16)<10)
								  obj[t][9]=(n/16)%16+48;
                        				else
       							  obj[t][9]=(n/16)%16+55;

		obj[t][11]='^'; z=t;
		for(i=1,t=2;i<l;i++,t++)
			{
					if(t%10==0)
						{
							obj[t][0]='T';
							obj[t][1]='^';
							obj[t][2]='0';
							obj[t][3]='0';
							obj[t][4]=lc[i][0];
							obj[t][5]=lc[i][1];
							obj[t][6]=lc[i][2];
							obj[t][7]=lc[i][3];
							obj[t][8]='^';
							n=(t-pp)*3;
                        				if((n%16)<10)
								obj[pp][10]=n%16+48;
                        				else
  								obj[pp][10]=n%16+55;
                        				if(((n/16)%16)<10)
								obj[pp][9]=(n/16)%16+48;
                        				else
      							  obj[pp][9]=(n/16)%16+55;
							pp=t;
							t++;
						}
					if(!strcmp(op[i],"END"))
					{
						n=(t-pp)*3;
                        				if((n%16)<10)
								obj[pp][10]=n%16+48;
                        				else
  								obj[pp][10]=n%16+55;
                        				if(((n/16)%16)<10)
								obj[pp][9]=(n/16)%16+48;
                        				else
      							  obj[pp][9]=(n/16)%16+55;
							pp=t;
						obj[t][0]='E';
						obj[t][1]='0';
						obj[t][2]='0';
						obj[t][3]=lc[0][0];
						obj[t][4]=lc[0][1];
						obj[t][5]=lc[0][2];
						obj[t][6]=lc[0][3];
					}
				if(op[i][0]!='+')
                    		{if(op[i][strlen(op[i])-1]=='R')
						{

							strncpy(tp,op[i],strlen(op[i])-1);
							for(pppr=0;pppr<(strlen(op[i])-1);pppr++)
								tp[pppr]=op[i][pppr];
							tp[pppr]='\0';
							if(srop(tp))
								{
									obj[t][0]=opp[0];
									obj[t][1]=opp[1]+1;
								}
							obj[t][2]=srr(val[i][0])+48;
							obj[t][3]=srr(val[i][2])+48;
							obj[t][4]='\0';
							printf("%s",obj[t]);
						}
				else{
					b=srs(val[i]);
					if(b<0)
					    b=srl(val[i]);
					strcpy(temp,symh[b]);
					hadd(temp,lc[i]);
					obj[t][2]='2';
					obj[t][3]=temp[1];
					obj[t][4]=temp[2];
					obj[t][5]=temp[3];
					if(srop(op[i]))
					 {
						obj[t][0]=opp[0];
						obj[t][1]=opp[1];
					 }
					if(val[i][0]=='#')
					 {
						obj[t][1]=obj[t][1]+1;
						obj[t][2]=val[i][1];
						obj[t][3]=val[i][2];
						obj[t][4]=val[i][3];
						obj[t][5]=val[i][4];
					 }
					else{

					if(val[i][0]=='@')
					 {
						obj[t][1]=obj[t][1]+2;
						if(obj[t][1]>'9')
							obj[t][1]='A';
						for(i1=1;i1<strlen(val[i]);i1++)
							tp[i1-1]=val[i][i1];
						tp[i1-1]='\0';
						b=srs(tp);
					if(b<0)
					    b=srl(tp);
					strcpy(temp,symh[b]);
					hadd(temp,lc[i]);
					obj[t][2]='2';
					obj[t][3]=temp[1];
					obj[t][4]=temp[2];
					obj[t][5]=temp[3];

					 }

					else
					 {
						obj[t][1]=obj[t][1]+3;
						if(obj[t][1]>'9')
							obj[t][1]='B';
					 }
					}

					if(val[i][strlen(val[i])-1]=='X')
					 {
						obj[t][2]=obj[t][2]+8;
						if(obj[t][1]>'9')
							obj[t][2]=obj[t][2]+7;
						for(i1=0;i1<(strlen(val[i])-2);i1++)
							tp[i1]=val[i][i1];
						tp[i1]='\0';
						b=srs(tp);
					if(b<0)
					    b=srl(tp);
					strcpy(temp,symh[b]);
					hadd(temp,lc[i]);
					obj[t][3]=temp[1];
					obj[t][4]=temp[2];
					obj[t][5]=temp[3];
					 }
if(!strcmp(op[i],"RESW")||!strcmp(op[i],"RESB"))
{obj[t][0]='T';
							obj[t][1]='^';
							obj[t][2]='0';
							obj[t][3]='0';
							obj[t][4]=lc[i][0];
							obj[t][5]=lc[i][1];
							obj[t][6]=lc[i][2];
							obj[t][7]=lc[i][3];
							obj[t][8]='^';
							n=(t-pp)*3;
                        				if((n%16)<10)
								obj[pp][10]=n%16+48;
                        				else
  								obj[pp][10]=n%16+55;
                        				if(((n/16)%16)<10)
								obj[pp][9]=(n/16)%16+48;
                        				else
      							  obj[pp][9]=(n/16)%16+55;
							pp=t;
							t++;
}

					if(!strcmp(op[i],"WORD"))
						sprintf(obj[t],"%06d",atoi(val[i]));
					if(!strcmp(op[i],"BYTE"))
						strcpy(obj[t],val[i]);
				}
					}
				    else
					{
					   mod[modi][0]=lc[i][0];
					   mod[modi][1]=lc[i][1];
					   mod[modi][2]=lc[i][2];
					   mod[modi][3]=lc[i][3];
					   mod[modi][4]='\0';
					   modi++;
					for(i1=0;i1<(strlen(op[i])-1);i1++)
						op[i][i1]=op[i][i1+1];
					op[i][i1]='\0';
					b=srs(val[i]);
					if(b<0)
					    b=srl(val[i]);
					obj[t][2]='1';
					obj[t][3]='0';
					obj[t][4]=symh[b][0];
					obj[t][5]=symh[b][1];
					obj[t][6]=symh[b][2];
					obj[t][7]=symh[b][3];

					if(srop(op[i]))
					 {
						obj[t][0]=opp[0];
						obj[t][1]=opp[1];
					 }
					if(val[i][0]=='#')
					 {
						obj[t][1]=obj[t][1]+1;
						obj[t][2]='1';
						obj[t][3]='0';
						obj[t][4]=val[i][1];
						obj[t][5]=val[i][2];
						obj[t][6]=val[i][3];
						obj[t][7]=val[i][4];
					 }
					else{
					if(val[i][0]=='@')
					 {
						obj[t][1]=obj[t][1]+2;
						if(obj[t][1]>'9')
							obj[t][1]='A';
						for(i1=1;i1<strlen(val[i]);i1++)
							tp[i1-1]=val[i][i1];
						tp[i1-1]='\0';
						b=srs(tp);
					if(b<0)
					    b=srl(tp);
					obj[t][2]='1';
					obj[t][3]='0';
					obj[t][4]=symh[b][0];
					obj[t][5]=symh[b][1];
					obj[t][6]=symh[b][2];
					obj[t][7]=symh[b][3];

					 }

					else
					 {
						obj[t][1]=obj[t][1]+3;
						if(obj[t][1]>'9')
							obj[t][1]='B';
					 }
					}

					if(val[i][strlen(val[i])-1]=='X')
					 {
						obj[t][2]=obj[t][2]+8;
						if(obj[t][1]>'9')
							obj[t][2]=obj[t][2]+7;
						for(i1=0;i1<(strlen(val[i])-2);i1++)
							tp[i1]=val[i][i1];
						tp[i1]='\0';
						b=srs(tp);
					if(b<0)
					    b=srl(tp);
					obj[t][2]='1';
					obj[t][3]='0';
					obj[t][4]=symh[b][0];
					obj[t][5]=symh[b][1];
					obj[t][6]=symh[b][2];
					obj[t][7]=symh[b][3];
					 }

					}
				}

        obj[0][0]='H';
        FILE *fp4;
        symtab[0][6]='\0';
        fp4=fopen("output.txt","w");
            char appp[2][100];
    strcpy(appp[0],lih[0]);
    strcpy(appp[1],lih[0]);
    hadd(appp[1],appp[0]);
    	fputs("H^",fp4);
	fputs(symtab[0],fp4);
	fputs("^",fp4);
	fputs(lc[0],fp4);
	fputs("^",fp4);
	fputs("2080",fp4);
	fputs("\n",fp4);
	for(i=1;i<t-1;i++)
            {
                fputs(obj[i],fp4);
		if(i>1&&obj[i+1][0]!='T'&&obj[i+1][0]!='E'&&i<t-1&&strlen(obj[i+1]))
		fputs("^",fp4);
		if(obj[i+1][0]=='T'||obj[i+1][0]=='E')
                fputs("\n",fp4);
            }
 for(i=1;i<modi;i++)
            {
		fputs("M^",fp4);
		fputs(mod[i],fp4);
		fputs("^05\n",fp4);
	    }	
	fputs("E^",fp4);
	fputs(lc[0],fp4);
	fputs("\n",fp4);
       
	printf("\nOBJECT FILE generated\n");
	}

void main()
	{

		int o,i;
		for(i=0;i<3;i++)
		optab[i][2]='\0';
		strcpy(optab[3],"RSUB");
		strcpy(optab[4],"COMP");
		strcpy(optab[5],"LDCH");
		strcpy(optab[6],"JSUB");
		strcpy(optab[7],"J");
		for(i=8;i<23;i++)
			optab[i][3]='\0';
		pass2();
	}

