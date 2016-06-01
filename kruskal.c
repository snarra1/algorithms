/*
	Assignment No. : 07
	Name : Supraja Narra
	Title : Kruskal's MST
	Date : 04/16/2015 7:41 PM

*/
	//header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

	//strores no. of vertices and edges
int nV=0,nE=0;

	//structure Edge stores the vertices connected and its length
struct Edge{
	int u;
	int v;
	int len;
};

	//function declarations
int compare_edge(const void* a,const void * b);
void make_set(int* djs, int i);
void link(int* djs, int i, int j);
int find_set(int* djs, int i);
void kruskal(struct Edge *edge);

	//main function definition Supraja
int main()
{
	int i=0,j=0;
	struct Edge *edge;
	scanf("%d",&nV);
	scanf("%d",&nE);
	edge = malloc(nE*(sizeof(struct Edge)));
	for(i=0;i<nE;i++)
	{
		scanf("%d",&edge[i].u);
		scanf("%d",&edge[i].v);
		scanf("%d",&edge[i].len);
	}
	kruskal(edge);	//kruskal function called
	free(edge);
}

	//kruskal function definition - supraja
void kruskal(struct Edge* edge)
{
	int i=0,j=0,cost=0;
	int *djs = malloc(nV*(sizeof(int)));
		//stores the final edges selected
	struct Edge *finale = malloc(nV*(sizeof(struct Edge)));
		//sorts the edges quick sort
	qsort(edge,nE,sizeof(struct Edge),compare_edge);
	for(i=0;i<nV;i++)
	{
		make_set(djs,i);
	}
	i=0;
	j=0;
	while(1)
	{
		if(j<nV-1)
		{
			struct Edge sedge=edge[i++];
			int x=find_set(djs,sedge.u); //find their parent
			int y=find_set(djs,sedge.v);
			if(x!=y)	//if cycle is not formed then include it
			{
				finale[j]=sedge;
				link(djs,x,y);
				j++;
			}
		}
		else
		{
			break;
		}
	}
	for(i=0;i<j;i++)
	{
		printf("\n %d  %d  %d",finale[i].u,finale[i].v,finale[i].len);
		cost=cost+finale[i].len;
	}
	printf("\nTotal Cost : %d\n\n",cost);
	free(finale);
	free(djs);
}

	//find_set function
int find_set(int* djs, int i)
{
	if(djs[i]!=i)
	{
		djs[i]=find_set(djs,djs[i]);
	}
	return djs[i];
}

	//function definition for link ( merges the sets)
void link(int* djs, int i, int j)
{
	int x=find_set(djs,i);
	int y=find_set(djs,j);
	if(djs[x] < djs[y])
	{
		djs[y]=x;
	}
	else
	{
		djs[x]=y;
	}
}

	//make_set function
void make_set(int* djs, int i)
{
	djs[i] = i;
}

	//compare function to be provided in qsort
int compare_edge(const void* a, const void* b)
{
	struct Edge* a1 = (struct Edge*)a;
	struct Edge* b1 = (struct Edge*)b;
	return a1->len > b1->len;
}
