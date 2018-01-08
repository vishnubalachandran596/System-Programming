
#include<stdio.h>
#include<string.h>
#include<ctype.h>
  
char input[10];
int i,error;
void E();
void T();
void Eplus();
void Tplus();
void F();  
       void  main()
          {
		i=0;
		error=0;
                printf("Grammar is\n");
                printf("E->E+T/T\nT->T*F/F\nF->(E)/a\n");
                printf("Enter Expression   :  "); 
                gets(input);
                E();
                if(strlen(input)==i&&error==0)
                        printf("\nValid String\n");
                else printf("\nInvalid String\n");
          }
          
          
  
void E()
{
     T();
     Eplus();
}
void Eplus()
{
     if(input[i]=='+')
     {
     i++;
     T();
     Eplus();
     }
     }
void T()
{
     F();
     Tplus();
}
void Tplus()
{
     if(input[i]=='*')
     {
                      i++;
                      F();
                      Tplus();
                      }
                      }
     void F()
     {
          if(input[i]=='a') i++;
          	  
         else if(input[i]=='(')
          {
          i++;
          E();
          if(input[i]==')')
          i++;

          else error=1; 
            }
         
          else error=1;
          }
           
