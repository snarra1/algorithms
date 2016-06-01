/*
	Assignment No. : 2
	Title : Quick Sort
	Name : Supraja Narra
	Date : 02/11/2015 7:25 PM
*/

	//Header Files
#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

void quicksort(int*,int,int);
int hoare(int*, int, int);

int main()
{
	int n=0,i=0;
	int data[MAX];

		//Accept the size of array to be sorted
	scanf("%d",&n);

	if(n<0 || n>100000)
	{
		printf("\n Invalid value of n...\n\t\t 0<n<100000\n");
		exit(1);
	}

		//Accept the data to be sorted
	for(i=0;i<n;i++)
	{
		scanf("%d",&data[i]);
	}
		//Quick Sort on the data
	quicksort(data,0,n-1);

		//displaying the sorted data
	printf("\n");
	for(i=0;i<n;i++)
	{
		printf("%d\n",data[i]);
	}
		//successful termination of program
	return 0;
}

int hoare(int* data, int p, int r)
{
	int i=0,j=0,pivot=0,index=0,temp=0;
	pivot=data[p];
	i=p-1;		//initialising the i and j
	j=r+1;
	index=p+rand() % (r-p+1);	//randomly selecting the pivot element
	temp=data[index];
	data[index]=data[p];
	data[p]=temp;
	while(1)
	{
		do		//looping till values to be swapped are found
		{
			j=j-1;
		}while(data[j]>pivot);

		do
		{
			i=i+1;
		}while(data[i]<pivot);

		if(i<j)
		{
			temp=data[i];
			data[i]=data[j];
			data[j]=temp;
		}
		else		//returning the pivot element
		{
			return j;
		}
	}
}

void quicksort(int* data, int p, int r)
{
	int q=0;
	if(r>p)
	{
		q=hoare(data,p,r);
		quicksort(data,p,q);
		quicksort(data,q+1,r);
	}
}

