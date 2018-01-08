
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//stack used for operation
char stack[30][30];
int stackindex[30];
int top;
void push(char c[30],int index){
	strcpy(stack[++top],c);
  stackindex[top]=index;
}
int pop(){
	if(top==-1){
		return -1;
	}
	else{
		return top--;
	}
}

int checkforsym(char a[30], char s){
  int i=0;
  for(i=0;i < strlen(a); ++i){
    if(a[i] == s)
      return 1;
  }
  return 0;
}

int checkTerminal(char c[30]){
	if(strlen(c)==1){
		if(islower(c[0])){
			return 1;
		}
		else if((c[0] =='*') || (c[0] =='+') || (c[0] =='-') || (c[0] =='/') ||
		                        (c[0] =='(') || (c[0] ==')') || (c[0] =='~') ){
      //~ for epsilon or empty nd assuming ~ will come alone only
			return 1;
		}
		else{
			return 0;
		}
	}
	else if(strcmp(c,"id") == 0){
		return 1;
	}
	return 0;
}

int main(){

	char productions[30][30],first[30][30],ffirst[30][30],follow[30][30],ffollow[30][30];
	int numProductions;
  char A,a[10],B,b[10];
  char stackelement[30];
  int aindex,bindex,posB;
  char *pos;

	int i,j,k,l,m,n;
	int topV;
	char temp[10], temp2[3];

    printf("Enter num of productions :");
    scanf("%d",&numProductions);
    printf("\nEnter the productions (use ~ for empty ) :\n ");
    for(i=0; i < numProductions; ++i){
    	scanf("%s", productions[i]);
    }

    for(i=0; i < numProductions; ++i){
    	top = -1;
    	m=0;
    	for(j=3; j < strlen(productions[i]); ++j){
    		if(productions[i][j] == '|'){
    			push(temp,0);
    			m=0;
    		}
    		else{
    			temp[m++] = productions[i][j];
    		}

    	}
    	strcat(temp, "\0");
    	push(temp,0);

    	first[i][0]='\0';

    	while(top > -1){
           topV = pop();
           if(checkTerminal(stack[topV])){ //if its a terminal just add it to first
                strcat(first[i],stack[topV]);
                strcat(first[i],",");

           }
           else if((stack[topV][0]=='i') && (stack[topV][1]=='d')){
           	strcat(first[i],"id");
           	strcat(first[i],",");
           }
           else{
              temp2[0] = stack[topV][0];
              temp2[1] = '\0';
              if(checkTerminal(temp2)){
                  strcat(first[i],temp2);
                  strcat(first[i],",");

              }
              else{
              	//if non terminal first in production
              	for(n=0; n < numProductions; ++n ){
                  if(productions[n][0] != temp2[0]){
                    continue;
                  }
              		m=0;
    				    for(j=3; j < strlen(productions[n]); ++j){
    				      if(productions[n][j] == '|'){
    					     push(temp,0);
    					    m=0;
    				      }
    				      else{
    				    	 temp[m++] = productions[n][j];
    				      }

    			     }
    			     strcat(temp, "\0");
    			     push(temp,0);
               break;
              }
            }
           }
    	}

    }

   /* for(i=0 ; i < numProductions; ++i){
      printf("%c\t{%s\b}\n",productions[i][0],first[i]);
    }*/

    //to eliminate duplicate terms
    for(i=0; i< numProductions; ++i){
      strcat(first[i],"\0");
      strcat(ffirst[i],"\0");
      ffirst[i][0] = first[i][0];
      m=1;
      for(j=1; j < strlen(first[i]); ++j){
        if(first[i][j] == ',' && ffirst[i][m-1] != ','){
          ffirst[i][m++] = first[i][j];
        }
        else{
          if(checkforsym(ffirst[i],first[i][j])==0){
            ffirst[i][m++] = first[i][j];
          }
        }
      }
      ffirst[i][m]='\0';
    }

     for(i=0 ; i < numProductions; ++i){
      printf("%c\t %s\b \n",productions[i][0],ffirst[i]);
    }

    // NOW TO FIND FOLLLOW , FIRST in ffirst
    for(i=0;i<30;++i){
      follow[i][0]='\0';
    }

    follow[0][0] = '$';
    follow[0][1] = ',';
    follow[0][2] = '\0';
    top = -1;
    for(i=0 ; i < numProductions; ++i){
      //push all production components to stack
      m=0;
      temp[0]='\0';
      for(j=3; j < strlen(productions[i]); ++j){
        if(productions[i][j] == '|'){
          temp[m]='\0';
          push(temp,i);
          m=0;
        }
        else{
          temp[m++] = productions[i][j];
        }
      }
      temp[m]='\0';
      push(temp,i);
    }

   /*for(i=0 ; i <= top; ++i){
      printf("%s\t %d \n",stack[i], stackindex[i] );
    }*/

    for(i=0;i < numProductions ; ++i){
       a[0]='\0';
       b[0]='\0';
       B = productions[i][0];
      for(j=0; j <= top; ++j){
        strcpy(stackelement,stack[j]);
        pos = strchr(stackelement,B);//returns position of first occurance of the character
        if(pos){
          posB = pos - stackelement;
        }
        else{
          posB=-1;
        }


      if(posB > -1){
          strncpy(a,stackelement,posB);
          a[posB]='\0';
          for(m=posB+1; m < strlen(stackelement) ;++m){
             b[m-posB-1] = stackelement[m];
             b[m-posB]='\0';
          }
          strcat(b,"\0");

        //printf("%s\t%c\t%s\n",a,B,b );
        //aBb  found and appliying rule 2
        if(strlen(b)>0){
            //find first of b and append to follow of B
            if(checkTerminal(b)==1){
             if(b[0]=='i' && b[1] == 'd'){
               strcat(follow[i],"id");
             }
             else{
              follow[i][strlen(follow[i])] = b[0];
             }
             strcat(follow[i],",");
            }
            else if(islower(b[0])){
              follow[i][strlen(follow[i])] = b[0];
              strcat(follow[i],",");
            }
            else{
              //find index of nonterminal from production
              for(k=0; k< numProductions; ++k){
                if(productions[k][0] == b[0]){
                   strcat(follow[i],ffirst[k]);
                   //aBb found and rule 3 has to be applied
                   if(checkforsym(ffirst[k],'~')){
                    //append follow(A) to follow(B)
                    if(i != stackindex[j])
                       strcat(follow[i],follow[stackindex[j]]);

                   }
                }


              }

            }
            //rule 2 applied


          }
        else{//apply rule 3

            //printf("%d\t", stackindex[j]);
            //printf("%s\t", follow[i]);
            //printf("%s\n", follow[stackindex[j]]);
            strcat(follow[stackindex[j]],"\0");
            k = stackindex[j];
            if(i != stackindex[j])
               strcat(follow[i],follow[k]);

          }
        }
       }
    }

    for(i=0; i< numProductions; ++i){
      strcat(follow[i],"\0");
      strcat(ffollow[i],"\0");


      m=0;
      for(j=0; j < strlen(follow[i]); ++j){

        if(follow[i][j] == '~'){
          continue;
        }

        if(follow[i][j] == ',' && ffollow[i][m-1] != ','){
          ffollow[i][m++] = follow[i][j];
        }
        else{
          if((checkforsym(ffollow[i],follow[i][j])==0)){
            ffollow[i][m++] = follow[i][j];
          }
        }
      }
      ffollow[i][m]='\0';
    }

    printf("Follow\n");

    for(i=0; i<numProductions; ++i){
      printf("%c\t%s\n", productions[i][0],ffollow[i]);
    }


	return 0;
}
