
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
void leading(char);
void trailing(char);
int r=0,i,k,j,n,cn,nn=0,m=0,ln=0,nr=0,tt=0;
char str[30][30],l[20][20],t[20][20],ch[10],chr[10],ck[20],a[30][30][30];
int check(char c)
{
int flag=0;
	for(k=0;k<nn;k++)
	{
		if(ch[k]==c)
		{
			flag=1;
			break;
		}
	}
	if(flag==1)
	return 1;
	else return 0;
}

int checkr(char c)
{
	int flag=0;
	for(k=0;k<nr;k++)
	{
		if(chr[k]==c)
		{
			flag=1;
			break;
		}
	}
	if(flag==1)
		return 1;
	else return 0;
}

int search(char c)
{
	int flag=0;
	for(k=0;k<tt;k++)
	{
		if(ck[k]==c)
		{
			flag=1;
			break;
		}
	}
	if(flag==1)
		return 1;
	else return 0;
}

int main()
{
	int p;
//clrscr();
	printf("\nNumber of productions:");
	scanf("%d",&n);
	printf("\nEnter productions:\n");
	for(i=0;i<n;i++)
		scanf("%s",str[i]);
	for(i=0;i<n;i++)
	{
		cn=check(str[i][0]);
		if(cn==0)
		{
			ch[nn++]=str[i][0];
			r=0;
			leading(str[i][0]);
			printf("\nLeading(%c):{",str[i][0]);
			for(p=0;p<r-1;p++)
			{
				printf("%c ",l[i][p]);
			}
			printf("%c}",l[i][r-1]);
		}
	}
	printf("\n");
	for(i=0;i<n;i++)
	{
		cn=checkr(str[i][0]);
		if(cn==0)
		{
			chr[nr++]=str[i][0];
			m=0;
			trailing(str[i][0]);
			printf("\nTrailing(%c):{",str[i][0]);
			for(p=0;p<m-1;p++)
			{
				printf("%c ",t[i][p]);
			}
			printf("%c}",t[i][m-1]);
		}
	}
	for(i=0;i<n;i++)
	{
		for(j=3;j<strlen(str[i]);j++)
		{
			if(!isupper(str[i][j]))
			{
				cn=search(str[i][j]);
				{
					if(cn==0)
					{
						ck[tt++]=str[i][j];
					}
				}
			}
		}
	}
	printf("\n");
	for(i=1;i<=tt;i++)
	{
		a[i][0][0]=ck[i-1];
	}
	a[tt+1][0][0]='$';
	for(j=1;j<=tt;j++)
	{
		a[0][j][0]=ck[j-1];
	}
	a[0][tt+1][0]='$';
	for(i=0;i<n;i++)
	{
		for(j=3;j<strlen(str[i]);j++)
		{
			if(!isupper(str[i][j]) && !isupper(str[i][j+1]))
			{
				for(k=1;k<=tt;k++)
				{
					for(p=1;p<=tt;p++)
					{
						if(a[k][0][0]==str[i][j] && 
						a[0][p][0]==str[i][j+1])
						{
							a[k][p][0]='=';
							break;
						}
					}
				}
			}
			if(!isupper(str[i][j]) && !isupper(str[i][j+2]))
			{
				for(k=1;k<=tt;k++)
				{
					for(p=1;p<=tt;p++)
					{
						if(a[k][0][0]==str[i][j] && 
							a[0][p][0]==str[i][j+2])
						{
							a[k][p][0]='=';
							break;
						}
					}
				}
			}
			if(!isupper(str[i][j]) && isupper(str[i][j+1]))
			{
				r=0;
				leading(str[i][j+1]);
				for(m=0;m<r;m++)
				{
					for(k=1;k<=tt;k++)
					{
						for(p=1;p<=tt;p++)
						{
							if(a[k][0][0]==str[i][j] && 
							a[0][p][0]==l[i][m])
							{
								a[k][p][0]='<';
							}
						}
					}
				}
			}
			if(isupper(str[i][j]) && !isupper(str[i][j+1]))
			{
				m=0;
				trailing(str[i][j]);
				for(r=0;r<m;r++)
				{
					for(k=1;k<=tt;k++)
					{
						for(p=1;p<=tt;p++)
						{
							if(a[k][0][0]==t[i][r] && 
							a[0][p][0]==str[i][j+1])
							{
								a[k][p][0]='>';
							}
						}
					}
				}
			}
		}
	}
	r=0;
	leading(str[0][0]);
	for(m=0;m<r;m++)
	{
		for(k=1;k<=tt;k++)
		{
			if(a[k][0][0]==l[i][m])
			{
				a[tt+1][k][0]='<';
			}
		}
	}
	m=0;
	trailing(str[0][0]);
	for(r=0;r<m;r++)
	{
		for(k=1;k<=tt;k++)
		{
			if(a[k][0][0]==t[i][r])
			{
				a[k][tt+1][0]='>';
			}
		}
	}
	for(i=0;i<=tt+1;i++)
	{
		for(j=0;j<=tt+1;j++)
		{
			printf("%c\t",a[i][j][0]);
		}
		printf("\n");
	}
// getch();
	return 0;
}

void leading(char c)
{
	for(k=0;k<n;k++)
	{
		if(str[k][0]==c)
		{
			if(!isupper(str[k][3]))
			{
				l[i][r++]=str[k][3];
			}
			if(isupper(str[k][3]) && !isupper(str[k][4]))
			{
				l[i][r++]=str[k][4];
			}
			if(isupper(str[k][3]) && str[k][3]!=c)
				leading(str[k][3]);
		}
	}
	return;
}

void trailing(char c)
{
	for(k=0;k<n;k++)
	{
		ln=strlen(str[k])-1;
		if(str[k][0]==c)
		{
			if(!isupper(str[k][ln]))
			{
				t[i][m++]=str[k][ln];
			}
			if(isupper(str[k][ln]) && !isupper(str[k][ln-1]))
			{
				t[i][m++]=str[k][ln-1];
			}
			if(isupper(str[k][ln]) && str[k][ln]!=c)
				trailing(str[k][ln]);
		}
	}
	return;
}
/*
OUTPUT

Number of productions:6

Enter productions:
E->E+T
E->T
T->T*F
T->F
F->(E)
F->i

Leading(E):{+  *  ( i}
Leading(T):{*  ( i}
Leading(F):{( i}

Trailing(E):{+ * ) i}
Trailing(T):{* ) i}
Trailing(F):{) i}
	+	*	(	)	i	$	
+	>	<	<	>	<	>	
*	>	>	<	>	<	>	
(	<	<	<	=	<		
)	>	>		>		>	
i	>	>		>		>	
$	<	<	<		<		

*/
