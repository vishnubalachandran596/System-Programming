using namespace std;
#include<iostream>
#include<stdio.h>
#include<stdlib.h>

int f=0,r=0,y=0,q[20],output[20];
int nfa[15][5][5],m,n,fin[5];
int final,dfa_size=0,dfa_st_name=65;
char trans[10][5];

struct dfa{
int state[10],flag,len;
char name;
}d[10];

void input()
{
int i,j,k;
char symb[5];
cout<<"\nenter the no of states: ";
cin>>n;
cout<<"enter no of symbols:";
cin>>m;
cout<<"enter the symbols:";
for(i=0;i<m;i++)
{
cin>>symb[i];
if(i!=0)
trans[0][i+1]=symb[i];
}
for(i=0;i<n;i++)
{
cout<<"for state "<<i<<": \n\n";
for(j=0;j<m;j++)
{
cout<<"enter the no of state for symbol "<<symb[j]<<":";
cin>>r;
if(r>0)
{
cout<<"enter the states: ";
}
for(k=0;k<r;k++)
{
cin>>nfa[i][j][k];
}
nfa[i][j][k]=-1;
}
}
//printf("enter the no of final states: \n");
cout<<"enter no of final states";
cin>>final;
cout<<"enter the final state: ";
for(k=0;k<final;k++)
{
cin>>fin[k];
}
}

void pop(int x)
{
int found=0,j,z;
for(j=0;nfa[x][0][j]!=-1;j++)
{
found=0;
for(z=0;z<r;z++)
if(q[z]==nfa[x][0][j])
found=1;
if(found==0)
q[r++]=nfa[x][0][j];
}
if(f<r)
{
output[y++]=q[f];
pop(q[f++]);
}
}

void pop_symb(int x,int symb)
{
int found=0,j,z;
for(j=0;nfa[x][symb][j]!=-1;j++)
{
found=0;
for(z=0;z<r;z++)
if(q[z]==nfa[x][symb][j])
found=1;
if(found==0)
q[r++]=nfa[x][symb][j];
}
}

void sort()
{
int i,j,temp;
for(i=0;i<y;i++)
for(j=0;j<y-i-1;j++)
if(output[j]>output[j+1])
{
temp=output[j+1];
output[j+1]=output[j];
output[j]=temp;
}
}

char search()
{
 int i,l=0;
 char found='-';
for(i=0;i<dfa_size;i++)
{
found='-';
if(d[i].len==y)
{
 while(d[i].state[l]==output[l]&&l<y)
l++;
if(l==y)
{
found=d[i].name;
break;
}
}
}
return found;
}

int main()
{
int i,j,l;
char found;
system("clear");
input();
y=f=r=0;
q[r++]=0;
pop(0);
sort();
trans[1][0]='>';
for(i=0;i<y;i++)
 d[dfa_size].state[i]=output[i];
d[dfa_size].len=y;
d[dfa_size].flag=0;
d[dfa_size].name=dfa_st_name;
trans[++dfa_size][1]=dfa_st_name++;
for(i=0;i<dfa_size;i++)
{
 if(d[i].flag==0)
 {
  d[i].flag=1;
 for(j=1;j<m;j++)
 {
  y=f=r=0;
 for(l=0;l<d[i].len;l++)
 {
  pop_symb(d[i].state[l],j);
 }
if(f<r)
 pop(q[f]);
sort();
found=search();
if(found=='-'&&y>0)
{
d[dfa_size].len=y;
for(int k=0;k<y;k++)
d[dfa_size].state[k]=output[k];
d[dfa_size].flag=0;
d[dfa_size].name=dfa_st_name;
trans[++dfa_size][1]=dfa_st_name;
trans[i+1][j+1]=dfa_st_name++;
}
else if(y<=0)
       trans[i+1][j+1]='-';
   else
       trans[i+1][j+1]=found;
 }
}
for(int p=0;p<final;p++)
{
for(int q=0;q<dfa_size;q++)
{
for(l=0;l<d[i].state[l];l++)
{
if(fin[p]==d[q].state[l])
trans[q+1][0]='*';
}
}
}
}
printf("\nThe corresponding dfa\n");
for(i=0;i<=dfa_size;i++)
{ //cout<<"\n"<<n;
 for(j=0;j<m+1;j++)
{

//printf("hello");
printf("\t%c",trans[i][j]);
}
printf("\n\n");
}
printf("\n");
for(i=0;i<dfa_size;i++)
{
 printf("%c:[",d[i].name);
for(j=0;j<d[i].len;j++)
{
printf("%d",d[i].state[j]);
}
printf("]\n");
}
return 0;
}
