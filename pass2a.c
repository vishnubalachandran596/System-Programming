//SANDEEP S
//6050
//PASS TWO OF SIC ASSEMBLER

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
int locctr,ad,address,temp=0,st;
int txt[20];
int s,num,l,i=0,j,n,c=0,nii,len,ni=1,li=0,n2=1,g=0,flag=1;
char pr[20]="COPY";
char lab[20],op[20],oper[20],code[20],line[30];
char opc[23][7]={"STA","LDA","STX","JMP","STL","JSUB","JEQ","J","LDL","RSUB","COMP","RESW","RESB","WORD","BYTE","TD","RD","LDX","TIX","JLT","STCH","LDCH","WD"};
char opc1[23][4]={"01","02","03","04","05","06","07","08","09","10","11","12","13","14","15","16","17","18","19","20","21","22","23"};
char sym[18][10];
int symadd[18];
int hex2dec(char hexadecimal[20]) {  
    long long decimalNumber=0;
    char hexDigits[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8',
      '9', 'a', 'b', 'c', 'd', 'e', 'f'};
  
    int i, j, power=0, digit;   

    for(i=strlen(hexadecimal)-1; i >= 0; i--) {
      
        for(j=0; j<16; j++){
            if(hexadecimal[i] == hexDigits[j])
             {
                decimalNumber += j*pow(16, power);
             }
        }
        power++;
    }  

    return decimalNumber;  
}
void readline(void) 
  {	
			
	char buffer[10],wordA[10],wordB[10],wordC[10],wordD[10];
	int i,j = 0;
 	lab[0]=op[0]=oper[0]=wordA[0]=wordB[0]=wordC[0]=wordD[0]='\0';
      
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
  		ad=hex2dec(wordC);
		
			strcpy(op,wordB);
			strcpy(oper,wordA);
  		}
void main()
{
txt[0]=1;

FILE *fp1,*fp2,*fp3;
fp1=fopen("INTER.DAT","r");
fp2=fopen("SYMTAB.DAT","r");
fp3=fopen("OUTPUT.DAT","w");
fgets(line,40,fp1);
readline();
while(strcmp(op,"END")!=0)
   {nii=ni;
       if(nii-txt[c]==10&&(txt[c]-txt[c-1])!=0||strcmp(op,"RESW")==0&&strcmp(op,"RESB")!=0)
        {
          if(strcmp(op,"RESW")==0)
             txt[++c]=ni-1;
     else txt[++c]=ni;
        }
       
    if(strcmp(op,"RESW")!=0&&strcmp(op,"RESB")!=0)
     {
      ni++; }
    fgets(line,40,fp1);
    readline();if(strcmp(op,"END")==0){txt[++c]=ni-1;}
   }
ni--;
fscanf(fp1,"%s %x",oper,&len);
fclose(fp1);
while(!feof(fp2))
  {
   fscanf(fp2,"%s %x\n",sym[i],&symadd[i]);
   
   i++;
  }
n=i;

fp1=fopen("INTER.DAT","r");
fgets(line,40,fp1);
readline();
if(strcmp(op,"START")==0)
   {
	locctr=ad;
      
	fprintf(fp3,"H^%s^%x^%x\n",pr,locctr,len);
	fprintf(fp3,"T^%x^%x",locctr,((txt[1]-txt[0])*3));
	fgets(line,40,fp1);
        readline();
   }
s=locctr;
while(strcmp(op,"END")!=0)
  {   flag=1;
	if(strcmp(op,"RESW")!=0&&strcmp(op,"RESB")!=0)
	{  
             n2++; 
             
                for(i=0;i<c;i++)
                    { 
                      if(txt[i]==n2){
                            
                        flag=0;break;}
                      else flag=1;
                    } 
		
              if(strcmp(op,"BYTE")==0)
		{
			for(i=2,j=0;i<strlen(oper)-1;i++)
			{
			code[j]=oper[i];
			j++;
			}
		        code[j]='\0';
		        
                       if(strcmp(code,"EOF")==0)
                        {printf("\n%s\n",code);
                          fprintf(fp3,"^454f46");
                        }
                       else
		         fprintf(fp3,"^%s",code);
		       if(flag==0)
                        { 
                         g++;if(g==3||g==4)fprintf(fp3,"\nT^%x^%x",ad,((txt[g+1]-txt[g])*3)-2);
                     else  fprintf(fp3,"\nT^%x^%x",ad,(txt[g+1]-txt[g])*3);
                        }
		}
		else
		{ 
			for(i=0;i<23;i++)
			{
				if(strcmp(op,opc[i])==0)
				{ 
				strcpy(code,opc1[i]);
				break;
				}
			}
			for(i=0;i<n;i++)
			{  
				if(strcmp(oper,sym[i])==0&&strcmp(oper," ")!=0)
				{
                               
				address=symadd[i];
				break;
				}
				else
				{address=atoi(oper); 
}
			}
               
		 if(flag==0)
                   {  
                     g++;
                    
                         if(strcmp(op,"WORD")==0)
                           fprintf(fp3,"^%06x",address);
                    
                         else if(strcmp(op,"RSUB")==0)
                             {
                               fprintf(fp3,"^4c0000");
                             }
                         else 
                           { 
                            fprintf(fp3,"^%s%x",code,address);   
                            }
                                     if(g==3||g==4)fprintf(fp3,"\nT^%x^%x",ad,((txt[g+1]-txt[g])*3)-2);
                     else  fprintf(fp3,"\nT^%x^%x",ad,(txt[g+1]-txt[g])*3);
                     
                     
                     }
                
                   else{
                       if(strcmp(op,"WORD")==0)
                           fprintf(fp3,"^%06x",address);
                    else if(strcmp(op,"RSUB")==0)
                             {
                               fprintf(fp3,"^4c0000");
                             }
                    else
                        fprintf(fp3,"^%s%x",code,address);  
                    }             
              }
         }
  fgets(line,20,fp1);
  readline();
 }
 fprintf(fp3,"\nE^00%x",s);
}

/*
INPUT

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

Object Program

H^COPY^1000^1078
T^1000^1e^051033^062037^021036^111030^071015^06205c^081003^02102a^011037^02102d
T^101b^15^011036^06205c^091033^4c0000^454f46^000003^000000
T^1030^1e^181030^021030^162058^07203d^172058^111030^072052^192059^20203d^031036
T^2052^1c^4c0000^F1^001000^181030^162077^07205f^221037^232077^191036^20205f
T^206e^7^191036^4c0000^05
E^001000

*/

