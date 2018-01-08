#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

char header[13][20]={"stdio.h","conio.h","iostream.h","stdlib.h","ctype.h","iomanip.h","string.h","alloc.h","math.h"};
char keyword[32][20]={"int","float","char","double","if","then","else","include","continue","while","do","for","switch","break","void","main","printf","scanf","FILE","fopen","fclose","fgets","fprintf","isdigit","isspace","isspace","isalpha","isalnum","strcpy","strcat","strlen"};
char oprtr[32][3]={"+","-","*","/","++","--","+=","-=","*=","/=","%","%=","<",">","<=",">=","==","||","&&","=","!=","&","|","^","!"};
char delmtr[20]={',',';','(',')','{','}','#','[',']','.','_'};

int cnt=0;
char entry[40][20];

int lookup(char s[]){
	int j=0,m=0;
	for (j=0;j<cnt;j++){
		if (strcmp(entry[j],s)==0){
			m=j+1;
			break;
		}
	}
	return m;	
}

int searchop(char s[]){
	int i,flg=0;
	for (i=0;i<32;i++){
		if (strcmp(s,oprtr[i])==0){
			flg=i+1;
		}	
	}
	return flg;
}

int dsearch(char l){
	int i,flg=0;
	for (i=0;i<11;i++){
		if (delmtr[i]==l){
			flg=i+1;
		}
	}
	return flg;
}

void main(){
	char s[50],line[100],hdr[20];
	int size=80,i,flag,k,j,lc=1,op,flg;
	float c;
	printf("\nTOKENS\n");
	FILE *fp,*fp1;
	fp=fopen("inputlex.txt","r");
	fp1=fopen("outputlex.txt","w");
	while(fgets(line,size,fp)){
		i=0;
		printf("%s:\n",line);
		while(i<strlen(line)){
			if(line[i]=='\n'){
				lc++;
				i++;
			}
			else if(line[i]=='\"'){
			
				printf("Line : %d\t<Literal,",lc);
				fprintf(fp1,"Line : %d\t<Literal,",lc);
				while(line[i+1]!='\"'){
					printf("%c",line[i+1]);
					fprintf(fp1,"%c",line[i+1]);
					i++;
				}
				
				printf(">\n");
				fprintf(fp1,">\n");
				i+=2;
			}
				else if (isspace(line[i])){
				i++;
			}
			else if (isdigit(line[i])){
				c=0;
				do{
					c=c*10+(line[i]-48);
					i++;
				}while(isdigit(line[i]));
				if (line[i]=='.'){
					i++;
					j=10;
					while (isdigit(line[i])){
						c=c+(float)(line[i]-48)/j;
						j*=10;
						i++;
					}
				}
				printf("Line : %d\t<num,%.1f>\n",lc,c);
				fprintf(fp1,"Line : %d\t<dnum,%.1f>\n",lc,c);
			}
			else if (isalpha(line[i])){
				k=0;
				while (isalnum(line[i]) || line[i]=='_'){
					s[k]=line[i];
					k++;i++;
				}
				s[k]='\0';
				flag=0;
				for (j=0;j<30;j++){
					if (strcmp(s,keyword[j])==0){
						flag=1;
						break;
					}
				}
				if (flag==1){
					printf("Line : %d\t<keyword,%d>\n",lc,j+1);
				fprintf(fp1,"Line : %d\t<keyword,%d>\n",lc,j+1);
				if(strcmp(s,"include")==0){
					printf("Line : %d\t<delimiter,0>\n",lc);
					fprintf(fp1,"Line : %d\t<delimiter,0>\n",lc);
					i++;
					printf("Line : %d\t<header,",lc);
					fprintf(fp1,"Line : %d\t<header,",lc);
					j=0;
					while(line[i]!='>'){
						hdr[j++]=line[i];
						i++;
					}
					hdr[j]='\0';
					for(j=0;j<9;j++){
						if(strcmp(hdr,header[j])==0)
							break;
					}
					printf("%d>\n",j+1);
					fprintf(fp1,"%d>\n",j+1);
					printf("Line : %d\t<delimiter,-1>\n",lc);
					fprintf(fp1,"Line : %d\t<delimiter,-1>\n",lc);
					i++;
				}
			}
			else{
				j=lookup(s);
				if(j==0){
					strcpy(entry[cnt],s);
					cnt++;
					j=cnt;
				}
				printf("Line : %d\t<id,%d>\n",lc,j);
				fprintf(fp1,"Line : %d\t<id,-1>\n",lc);			
			}
		}
		else{
			if (line[i]=='\''){
				printf("Line : %d\t<delimiter,-2>\n",lc);
				fprintf(fp1,"Line : %d\t<delimiter,-2>\n",lc);
				i++;			
			}
			else{
				flg=dsearch(line[i]);
				if (flg>0){
					printf("Line : %d\t<delimiter,%d>\n",lc,flg);
					fprintf(fp1,"Line : %d\t<delimiter,%d>\n",lc,flg);
					i++;
				}
				else{
					s[0]=line[i];
					i++;
					s[1]='\0';
					flg=searchop(s);
					op=flg;
					if(flg==0){
						printf("Invalid\t%d\n",lc);
						fprintf(fp1,"Invalid\t%d\n",lc);
						i++;
					}
					else{
						s[1]=line[i];
						s[2]='\0';
						flg=searchop(s);
						if (flg>0){
							i++;
							op=flg;
						}
						else{
							s[1]='\0';
						}
						printf("Line : %d\t<operator,%d>\n",lc,op);
					    fprintf(fp1,"Line : %d\t<operator,%d>\n",lc,op);
					}
				}			
			}
			
			}
		} 
	}
	fclose(fp);
	printf("\nNo: of Lines %d\n",lc-1);
	fprintf(fp1,"\nNo: of Lines %d\n",lc-1
	);
	fclose(fp1);				
}						

