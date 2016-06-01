/*
	Assignment No : 04
	Title : Check cashing (Dynamic Programming)
	Name : Narra Supraja
	Email id : snarra1@binghamton.edu
	Date : 2/24/2015 8:24 PM
*/

	//Header files
#include <stdio.h>
#include <stdlib.h>

	//Global variables
int n, debit;

	//Function declarations
int getval(int**,int,int);
void setval(int**,int,int,int);
int** allocmatrix();
void checkcash(int**,int*);
int max(int,int);
void printarrayval(int**,int*);
void memfree(int**,int*);

	//main function definition
int main()
{
	int** matrix, *cheques;
	int i=0;
	scanf("%d",&debit);	//holds total debit amount
	scanf("%d",&n);		//stores total no of cheques
	cheques=malloc(sizeof(int)*(n+1));	//holds pointer to cheques amounts
	cheques[0]=0;	//cheque #0
	for(i=1;i<=n;i++)		//scans the cheque amounts
	{
		scanf("%d",&cheques[i]);
	}

	matrix=allocmatrix();		//allocates memory to matrix

	checkcash(matrix,cheques);	//checkcash function called to evaluate the cheque numbers deposited

//	printarrayval(matrix,cheques);	//prints matrix and cheque values

	printf("\n");
	memfree(matrix,cheques);	//frees the memory allocated to pointers

	return 0;	//successfully terminates main function
}

	//checkcash function definition
void checkcash(int** matrix, int* cheques)
{
	int i=0,j=0,k=0,x=0,flag=0;
	int sum=0;
	int* printarray=malloc(sizeof(int)*debit);
	matrix[0][0]=0;
	for(i=1;i<=n;i++)
	{
		matrix[i][0]=matrix[0][0];	//initializes to '0'
		for(j=0;j<=debit;j++)
		{
			if(matrix[i-1][j]!=-1)
			{
				setval(matrix,i,j,0);	//sets value to 0 if previous is 1
			}
				//matrix[i][j]=matrix[i-1][j];
			if(j==cheques[i])		//sets value to 1 if cheque is cashed
			{
				setval(matrix,i,j,max(matrix[i][j],1));
			}
		}
	}
	for(x=n;x>0;x--)
	{
	 i=x;
	 sum=0;
	 k=1;
	 while(i>=1)		//starts the search from last check till the 1st one
	 {
		j=debit;
		while(j>=1)	//starts from the max deposit amount 
		{
			if(getval(matrix,i,j)==1)
			{
				sum=sum+j;		//calculates the total sum
				if(sum==debit)		//checks if sum equals debit amount
				{
					printarray[k]=i;	//inserts value into printarray
					k++;
					flag=1;			//breaks the loop if answer is found
					break;
				}
				if(sum<debit)		//continues the loop if sum is less than debited amount
				{
					printarray[k]=i;
					k++;
				}
				else if(sum>debit)	//does not add current value if sum exceeds the debit value
				{
					sum=sum-j;
				}
				j--;
			}			//continues the search for value 1 in matrix
			else if(getval(matrix,i,j)==-1 || getval(matrix,i,j)==0)
			{
				j--;
			}
		}
		i--;
		if(flag==1)		//breaks the loop if cheques deposited are found
		{
			break;
		}
	 }
	 k--;
	 if(flag==1)		//breaks the loop if flag is raised
	 {
		break;
	 }

	}
	if(sum==debit)		//if debit amount found then prints the cheque numbers
	{
		for(i=k;i>0;i--)
		{
			if(printarray[i]!=0)
				printf("\n%d",printarray[i]);
		}
	}
	else		//else prints the message
	{
		printf("\n Not Possible\n");
	}
	free(printarray);
}

	//Defining printarrayval function
void printarrayval(int** matrix,int* cheques)
{
	int i=0,j=0;
	printf("\nMatrix :");
	i=0;
	while(i<=n)	//prints the values in the matrix
	{
		printf("\n");
		j=0;
		while(j<=debit)
		{
			printf("  %d ",getval(matrix,i,j));	//gets value at ith row and jth colum
			j++;
		}
		i++;
	}
	printf("\n\nCheques : ");
	i=1;
	while(i<=n)
	{
		printf("$%d ",cheques[i]);	//prints cheque amounts
		i++;
	}
	printf("\n");
}

	//memfree function definition
void memfree(int** matrix,int* cheques)
{
	int i=0;
	while(i<=n)
	{
		free(matrix[i]);	//releases the memory allocated to 2D matrix
		i++;
	}
	free(cheques);	//frees the cheques array
	free(matrix);	//deletes the memory allocated to matrix pointer
}

	//allocates memory to matrix
int** allocmatrix()
{
	int i=0,j=0;
	int** mat=malloc(sizeof(int*)*(n+1));	//stores pointer to matrix of amounts and cheque numbers
	for(i=0;i<=n;i++)
	{
		mat[i]=malloc(sizeof(int)*(debit+1));
		for(j=0;j<=debit;j++)
		{
			setval(mat,i,j,-1);	//sets initial values in matrix to -1
		}
	}
	return mat;
}

	//max function returns the maximum value
int max(int x, int y)
{
		//returns the maximum value
	if(x>y)
		return x;
	else
		return y;
}

	//getval function defination
int getval(int** matrix,int i,int j)
{
	return matrix[i][j];	//returns matrix value
}

	//Defining setval function
void setval(int** matrix,int i,int j,int val)
{
	matrix[i][j]=val;	//sets matrix to a value
}
