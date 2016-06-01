/*
	Title : Heap Sort Algorithm
	Assignment No. : 3
	Name : Supraja Narra
	Date : 2/19/15 2:19
	snarra@binghamton.edu
*/

	//Header files
#include <stdio.h>
#include <stdlib.h>

#define MAX 100000
int length;
	//Function declarations
void heapsort(int* array, int n);
void buildheap(int* array, int n);
void maxheapify(int* array, int i);

	//main function definition
int main()
{
	int* array;
	int i=0, n=0;
	scanf("%d",&n);
	array=(int*)malloc(sizeof(int)*n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&array[i]);
	}
	length=n-1;
	heapsort(array,n);	//calling heapsort function
	for(i=0;i<n;i++)
	{
		printf("\n%d",array[i]);
	}
	printf("\n");
	free(array);
	return 0;
}

	//heapsort function definition
void heapsort(int* array,int n)
{
	int i=0, temp=0;
	buildheap(array,n);
	i=n-1;
	while(i>0)
	{			//swapping the 1st and last value
		temp=array[0];
		array[0]=array[i];
		array[i]=temp;
		i--;
		length--;
		maxheapify(array,0);
	}
}

	//defining buildheap function
void buildheap(int * array, int n)
{
	int  i=length/2;
	while(i>=0)
	{
		maxheapify(array,i);
		i--;
	}
}

	//Function definition for heapify function
void maxheapify(int* array, int i)
{
	int left=0, right=0,largest=0,temp=0;
	left=2*i+1;
	right=2*i+2;
	largest=i;
				//finds the largest values among the 3
	if(left<=length && array[left]>array[largest])
	{
		largest=left;
	}
	if(right<=length && array[right]>array[largest])
	{
		largest=right;
	}
	if(largest!=i)
	{
				//swapping values if found larger than parent
		temp=array[i];
		array[i]=array[largest];
		array[largest]=temp;
		maxheapify(array,largest);		//heapify the othes nodes
	}
	//printf("\n%d", largest);
}
