/*
	Assignment No. : 1
	Title : Insertion Sort
	Name : Supraja Narra
	Date : 02/01/2015 2:48AM
*/

	//Header Files
#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

int main()
{
	int data[MAX];
	int n=0,i=0,j=0,key=0;

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

		//Insertion Sort on the data
	i=1;
	while(i<n)
	{
		key=data[i];
		j=i-1;
		while(j>=0 && data[j]>key)
		{
			data[j+1]=data[j];
			j=j-1;
		}
		data[j+1]=key;
		i=i+1;
	}

		//displaying the sorted data
	printf("\n");
	for(i=0;i<n;i++)
	{
		printf("%d\n",data[i]);
	}

		//successful termination of program
	return 0;
}
