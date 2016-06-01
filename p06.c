/*
	Assignment No. : 06
	Title : Ferry Loading
	Name : Narra Supraja
	Email id : snarra1@binghamton.edu
	Date : 03/16/2015 2:30 AM
*/

#include <stdio.h>
#include <stdlib.h>

int fn=0,cn=0,leftf=0,rightf=0,maxcars=0;
int **ferry, *carlen, *side;

int** allocmatrix();
int ferryloading();
int max(int a,int b);
void printmatrix();
void deallocmatrix();

int main()
{
	int i=0;
	scanf("\n%d",&fn);
	scanf("\n%d",&cn);
	carlen=malloc((cn+1)*sizeof(int));
	side=malloc((cn+1)*sizeof(int));
	for(i=1;i<=cn;i++)
	{
		scanf("%d",&carlen[i]);
		side[i]=-1;
	}
	ferry=allocmatrix();
	maxcars=ferryloading();
	printmatrix();
	printf("\n%d",maxcars);
	for(i=1;i<=maxcars;i++)
	{
		if(side[i]==1)
			printf("\nL");
		else if(side[i]==0)
			printf("\nR");
	}
	deallocmatrix();
	printf("\n");
	free(carlen);
	free(side);
	return 0;
}

int ferryloading()
{
	int i=0,j=0;
	ferry[0][0]=0;
	leftf=0;
	rightf=0;
	for(i=1;i<=cn;i++)
	{
		ferry[i][0]=0;
		if(leftf+carlen[i]<=fn)
		{
			leftf+=carlen[i];
			ferry[i][leftf]=1;
		}
		else if(carlen[i]+rightf<=fn)
		{
			rightf+=carlen[i];
			ferry[i][rightf]=0;
		}
		else
		{
			break;
		}	
	}
	leftf=fn;
	rightf=fn;
	for(i=1;i<=cn;i++)
	{
		for(j=1;j<=fn;j++)
		{
			if(ferry[i][j]==1)
			{
				leftf-=carlen[i];
				maxcars++;
				side[maxcars]=1;	
			}
			else if(ferry[i][j]==0)
			{
				rightf-=carlen[i];
				maxcars++;
				side[maxcars]=0;			
			}
		}
	}
	return maxcars;
}

void printmatrix()
{
	int i=0,j=0;
	printf("\n Ferry Matrix : \n");
	for(i=0;i<=cn;i++)
	{
		printf("\n");
		for(j=0;j<=fn;j++)
		{
			printf(" %d",ferry[i][j]);
		}
	}
	printf("\n\n Car lengths : \n");
	for(i=1;i<=cn;i++)
	{
		printf(" %d",carlen[i]);
	}
	printf("\n");
}

int max(int a,int b)
{
	return (a>=b?a:b);
}

void deallocmatrix()
{
	int i=0;
	for(i=0;i<=cn;i++)
	{
		free(ferry[i]);
	}
	free(ferry);
}

int** allocmatrix()
{
	int i=0,j=0;
	int** ferry=malloc((cn+1)* sizeof(int*));
	for(i=0;i<=cn;i++)
	{
		ferry[i]=malloc((fn+1)* sizeof(int));
		for(j=0;j<=fn;j++)
		{
			ferry[i][j]=-1;
		}
	}
	return ferry;
}
