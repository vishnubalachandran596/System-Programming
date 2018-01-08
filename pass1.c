//SANDEEP S
//6050
//PASS ONE OF SIC ASSEMBLER

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char line[25];
int lc;
int s,num,f=0,f1,l,i,n=0,k;
char lab[10],op[10],val[10],g[3];
char a[23][7]={"STA","LDA","STX","JMP","STL","JSUB","JEQ","J","LDL","RSUB","COMP","RESW","RESB","WORD","BYTE","TD","RD","LDX","TIX","JLT","STCH","LDCH","WD"};
char b[20][10],prgname[20];
void readline(void) 
  {	
			
	char buffer[10],wordA[10],wordB[10],wordC[10];
	int i,j = 0;
 	lab[0]=op[0]=val[0]=wordA[0]=wordB[0]=wordC[0]='\0';
       for(i=0;line[i]!='\0';i++) {
  		if(line[i]!=' ')
  			buffer[j++]=line[i];
  		else {
  			buffer[j]='\0';
  			strcpy(wordC,wordB);
  			strcpy(wordB,wordA);
  			strcpy(wordA,buffer);
  			j=0;
  			 }
  	}
  	buffer[j-1]='\0';
  	strcpy(wordC,wordB);
  	strcpy(wordB,wordA);
  	strcpy(wordA,buffer);
  	strcpy(lab,wordC);
  	strcpy(op,wordB);
  	strcpy(val,wordA);
  }
void main()
 {
  FILE *fp1,*fp2,*fp3;
 fp1=fopen("INPUT1.DAT","r");
 fp2=fopen("SYMTAB.DAT","w");
 fp3=fopen("INTER.DAT","w");
 fgets(line,20,fp1); 
 while(line[0]=='.')
     fgets(line,20,fp1);
 readline();
 if(strcmp(op,"START")==0)
   {
    lc=atoi(val);
    fprintf(fp3,"%x %s %x\n",lc,op,lc);
    fgets(line,20,fp1);
    while(line[0] == '.') 
        fgets(line,20,fp1);
  }
 strcpy(prgname,lab);
 s=lc; 
 while(strcmp(op,"END")!=0)
  {
    for(i=0;i<23;i++)
     {
      if(strcmp(op,a[i])==0)
        {
         f1=0;
         break;
        }
     f1=1;
    }
  if(strcmp(lab,"\0")!=0)
    {
      for(i=0;i<n;i++)
        {
          if(strcmp(lab,b[i])==0)
             {
              f=1;
              break;
             }
          f=0;
       }
    if(f==0)
     {
       fprintf(fp2,"%s %x\n",lab,lc);
       strcpy(b[n++],lab);
     }
   }
 
 fprintf(fp3,"%x %s %s\n",lc,op,val);
 

 if(f==1)
    fprintf(fp3,"SYMBOL ALREADY DEFINED\n");
 if(f1==1)
    fprintf(fp3,"WRONG OPCODE\n");
 num=atoi(val);
 if(strcmp(op,"RESW")==0)
    lc=lc+(num*3);
 else if(strcmp(op,"RESB")==0)
    lc=lc+num;
 else if(strcmp(op,"BYTE")==0)
   {
 
   }
 else if(strcmp(op,"WORD")==0)
   lc=lc+3;
 else
   lc=lc+3;
   printf("\n%x",lc);
 fgets(line,20,fp1); 
 while(line[0] == '.') 
	fgets(line,20,fp1);
 readline();
 }
 fprintf(fp3,"%x %s %s\n",lc,op,val);
 l=lc-s;
 fprintf(fp3,"PROGRAMLENGTH %x\n",l);
 fprintf(fp3,"PROGRAMNAME %s",prgname);
}

INPUT

COPY START 4096
FIRST STL RETADR
CLOOP JSUB RDREC
     LDA LENGTH
    COMP ZERO
    JEQ EDFIL
    JSUB WRREC
 J CLOOP
EDFIL LDA EOF
 STA BUFFER
 LDA THREE
 STA LENGTH
 JSUB WRREC
 LDL RETADR
 RSUB 
.next subroutine
EOF BYTE C'EOF'
THREE WORD 3
ZERO WORD 0
RETADR RESW 1
LENGTH RESB 1
BUFFER RESB 4096
RDREC LDX ZERO
 LDA ZERO
RLOOP TD INPUT
 JEQ RLOOP
 RD INPUT
 COMP ZERO
 JEQ EXIT
 TIX MAXLEN
 JLT RLOOP
EXIT STX LENGTH
 RSUB 
.nextsubroutine
INPUT BYTE X'F1'
MAXLEN WORD 4096
WRREC LDX ZERO
WLOOP TD OUTPUT
 JEQ WLOOP
 LDCH BUFFER
 WD OUTPUT
 TIX LENGTH
 JLT WLOOP
 TIX LENGTH
 RSUB 
OUTPUT BYTE X'05'
 END FIRST
 
OUTPUT

Symbol Table

FIRST 1000
CLOOP 1003
EDFIL 1015
EOF 102a
THREE 102d
ZERO 1030
RETADR 1033
LENGTH 1036
BUFFER 1037
RDREC 2037
RLOOP 203d
EXIT 2052
INPUT 2058
MAXLEN 2059
WRREC 205c
WLOOP 205f
OUTPUT 2077

 Intermediate File
 
1000 START 1000
1000 STL RETADR
1003 JSUB RDREC
1006 LDA LENGTH
1009 COMP ZERO
100c JEQ EDFIL
100f JSUB WRREC
1012 J CLOOP
1015 LDA EOF
1018 STA BUFFER
101b LDA THREE
101e STA LENGTH
1021 JSUB WRREC
1024 LDL RETADR
1027 RSUB 
102a BYTE C'EOF'
102d WORD 3
1030 WORD 0
1033 RESW 1
1036 RESB 1
1037 RESB 4096
2037 LDX ZERO
203a LDA ZERO
203d TD INPUT
2040 JEQ RLOOP
2043 RD INPUT
2046 COMP ZERO
2049 JEQ EXIT
204c TIX MAXLEN
204f JLT RLOOP
2052 STX LENGTH
2055 RSUB 
2058 BYTE X'F1'
2059 WORD 4096
205c LDX ZERO
205f TD OUTPUT
2062 JEQ WLOOP
2065 LDCH BUFFER
2068 WD OUTPUT
206b TIX LENGTH
206e JLT WLOOP
2071 TIX LENGTH
2074 RSUB 
2077 BYTE X'05'
2078 END FIRST
PROGRAMLENGTH 1078
PROGRAMNAME COPY

 */


