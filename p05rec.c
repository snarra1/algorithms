/*
	Assignment No. : 05 (Memoized)
	Title : Optimal Binary Search Trees
	Name : Supraja Narra
	Email id : snarra1@binghamton.edu
	Date : 03/09/15, 9:50 PM
*/

	//Header files
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

	//Global variable declarations
int n=0;

	//Function declarations
int** matrixalloc();
int findmintree(int,int,int**,int*);
int min(int,int);
void printmatrix(int**,int*);
int sum(int i, int j,int array[i]);
void memfree(int**,int*);


	//main function definition
int main()
{
	int i=0,x=0;
	int *array;
	scanf("%d",&n);
	array=malloc(n*sizeof(int));
	int** matrix=matrixalloc();
	for(i=0;i<n;i++)
	{
		scanf("%d",&array[i]);
	}

	x=findmintree(0,n-1,matrix,array);

	printmatrix(matrix,array);

	printf("\n\n %d",x);
	memfree(matrix,array);
	printf("\n\n");
	return 0;
}

int findmintree(int i, int j,int**matrix, int* array)
{
	if(matrix[i][j]==-1)
	{
		if(i==j)
		{
			matrix[i][i] = array[i];
		}
		else if(j>i)
		{
			int r=0,fsum=0,cost=0,minimum=INT_MAX; 
			fsum=sum(i,j,array);
			for(r=i;r<j;r++)
			{
				cost=findmintree(i,r-1,matrix,array)+findmintree(r+1,j,matrix,array);
			}
			printmatrix(matrix,array);
			minimum=min(minimum,cost);
			matrix[i][j]=fsum+minimum;
		}
		else
		{
			matrix[i][j] = 0;
		}
	}
	return matrix[i][j];
}

void memfree(int** matrix,int* array)
{
	int i=0;
	while(i<n)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	free(array);
}

void printmatrix(int** matrix,int* array)
{
	int i=0,j=0;
	printf("\nArray : \n");
	for(i=0;i<n;i++)
	{
		printf(" %d",array[i]);
	}
	printf("\n\nMatrix : ");
	for(i=0;i<n;i++)
	{
		printf("\n");
		for(j=0;j<n;j++)
		{
			printf("  %d ", matrix[i][j]);
		}
	}
}

int min(int a, int b)
{
	return (a<=b?a:b);
}

int sum(int i, int j,int array[i])
{
	int r=0,fsum=0;
	for(r=i;r<=j;r++)
	{
		fsum+=array[r];
	}
	return fsum;
}

int** matrixalloc()
{
	int i=0,j=0;
	int** matrix=malloc(n*sizeof(int*));
	for(i=0;i<n;i++)
	{
		matrix[i]=malloc(n*sizeof(int));
		for(j=0;j<n;j++)
		{
			matrix[i][j]=-1;
		}
	}
	return matrix;
}
