/*
	Assignment No. : 08
	Name : Supraja Narra
	Title : Dijkstra's Algorithm
	Date : 04/27/2015 3:41 PM
	Referred geeksforgeeks dijkstra's algo set 7
*/
	//Header Files
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define DEBUG 1

int nV,nE;

struct Node
{
	int v;
	int len;
	struct Node* next;
};

struct List
{
	struct Node* head;
};

struct Graph
{
	int nV;
	struct List* garray;
};

struct heapnode
{
	int v;
	int dist;
};

struct heap
{
	int size;	//no. of nodes present
	int capacity;	//heapsize
	int* pos;	//position of heap required for decreaseKey
	struct heapnode** harray;
};

	//Function declarations
void swap(struct heapnode** x,struct heapnode** y)
{
	struct heapnode* temp=*x;
	*y=*x;
	*x=temp;
}
int isheapempty(struct heap* h)
{
    return h->size == 0;
}
int parentofi(int i)
{
	return (i-1)/2;
}
int leftofi(int i)
{
	return (2*i)+1;
}
int rightofi(int i)
{
	return (2*i)+2;
}
struct Graph* creategraph(int nV);
struct Node* newnode(int v,int len);
void addEdge(struct Graph* G,int u,int v,int len);
void printgraph(struct Graph* G);
struct heapnode* newheapnode(int v,int dist);
struct heap* createminheap(int capacity);
void minheapify(struct heap* h,int i);
void exchange(struct heap* h,int i, int small);
struct heapnode* extractmin(struct heap* h);
void decreasekey(struct heap* h, int v,int dist);
void dijkstra(struct Graph* graph, int u);
void freegraph(struct Graph* G);
void freeheap(struct heap* h);

int main()
{
	int i=0,u=0,v=0,len=0;
	scanf("%d",&nV);
	scanf("%d",&nE);
	struct Graph* G=creategraph(nV);
	for(i=0;i<nE;i++)
	{
		scanf("%d %d %d",&u,&v,&len);
		addEdge(G,u,v,len);
	}
//	printgraph(G);
	dijkstra(G,0);
	freegraph(G);
	return 0;
}

void freeheap(struct heap* h)
{
	int i=0;
	for(i=0;i<nV;i++)
	{
		free(h->pos);
		free(h->harray);
	}
	free(h);
}

void freegraph(struct Graph* G)
{
	int i=0;
	for(i=0;i< G->nV;i++)
	{
		struct Node* n = G->garray[i].head;
		struct Node* prev = n;
		while(n!=NULL)
		{
			n=n->next;
			free(prev);
		}
	}
	free(G->garray);
	free(G);
}

void dijkstra(struct Graph* G, int u)
{
//	if(DEBUG){printf("\nDijkstra");}
	int i=0,j=0,max=-99;
	int V=G->nV;
	int distance[V];
	struct heap* h;
//	if(DEBUG){printf("\nCallingcreateminheap");}
	h=createminheap(V);
//	if(DEBUG){printf("\nCreatedminheap");}
	for(i=0;i<V;i++)
	{
		distance[i]=INT_MAX;
		h->harray[i]=newheapnode(i,distance[i]);
		h->pos[i]=i;
	}
//	if(DEBUG){printf("\ncreatedheapnodes");}
	h->harray[u]=newheapnode(u,distance[u]);
	h->pos[u]=u;
	distance[u]=0;
	decreasekey(h,u,distance[u]);
//	if(DEBUG){printf("\n1stdecreasekey");}
	h->size=V;
	while(!isheapempty(h))
	{
		struct heapnode* hnode=extractmin(h);
		int start=hnode->v;
		struct Node* n=G->garray[start].head;
//		if(DEBUG){printf("\nextractedmin");}
		while(n!=NULL)
		{
			int end=n->v;
			if(h->pos[end]< h->size && distance[start]!=INT_MAX && n->len+distance[start] < distance[end])
			{
				distance[end]=distance[start]+n->len;
				decreasekey(h,end,distance[end]);
			}
			n=n->next;
		}
//		if(DEBUG){printf("\nalldecreasekeys");}	
	}
	max=distance[0];
	j=0;
	for(i=1;i<V;i++)
	{
		if(distance[i]>max)
		{
			max=distance[i];
			j=i;
		}
	}
	printf("\nMax distance %d from Vertex %d\n",max,j);
	freeheap(h);
}

void decreasekey(struct heap* h, int v,int dist)
{
	int i=h->pos[v];
	int parent=parentofi(i);
	h->harray[i]->dist=dist;
	while(i && h->harray[i]->dist < h->harray[parent]->dist);
	{
		h->pos[h->harray[i]->v]=parent;
		h->pos[h->harray[parent]->v]=i;
		//swap(&h->harray[i],&h->harray[parent]);
		struct heapnode* temp=h->harray[i];
		h->harray[i]=h->harray[parent];
		h->harray[parent]=temp;
		i=parent;
	}
	return;
}

struct heapnode* extractmin(struct heap* h)
{
	if(h->size==0)	//heap is empty	
	{
		return NULL;
	}
	struct heapnode* root = h->harray[0];
	struct heapnode* last = h->harray[h->size - 1];
	h->harray[0]=last;
	h->pos[root->v]=h->size-1;
	h->pos[last->v]=0;
	h->size--;
	minheapify(h,0);
//	if(DEBUG){printf("\ninextractmin");}
	return root;
}

void exchange(struct heap* h,int i, int j)
{
	struct heapnode* jnode=h->harray[j];
	struct heapnode* inode=h->harray[i];
		//swap positions and nodes
	h->pos[jnode->v]=i;
	h->pos[inode->v]=j;
		//swap(&h->harray[j],&h->harray[i]);
	struct heapnode* temp=h->harray[j];
	h->harray[j]=h->harray[i];
	h->harray[i]=temp;
}

void minheapify(struct heap* h,int i)
{
	int small=i;
	int left=leftofi(i);
	int right=rightofi(i);
	if((left< h->size) && (h->harray[left]->dist < h->harray[small]->dist))
	{
		small=left;
	}
	if((right< h->size) && (h->harray[right]->dist < h->harray[small]->dist))
	{
		small=right;
	}
	if(small!=i)
	{
			//exchange the nodes
		exchange(h,i,small);
		minheapify(h,small);
	}
}

struct heap* createminheap(int capacity)
{
	struct heap* h=malloc(sizeof(struct heap));
	h->pos=malloc(capacity*sizeof(int));
	h->size=0;
	h->capacity=capacity;
	h->harray=malloc(capacity*sizeof(struct heapnode*));
//	if(DEBUG){printf("\ncreateminheap");}
	return h;
}

struct heapnode* newheapnode(int v,int dist)
{
	struct heapnode* hnode=malloc(sizeof(struct heapnode));
	hnode->v=v;
	hnode->dist=dist;
//	if(DEBUG){printf("\nnewheapnode");}
	return hnode;
}

void printgraph(struct Graph* G)
{
	int i=0;
	for(i=0;i<G->nV;i++)
	{
		struct Node* n = G->garray[i].head;
		printf("Vertex %d",i);
		while(n!=NULL)
		{
			printf("->%d(%d)",n->v,n->len);
			n=n->next;
		}
		printf("\n");
	}
}

void addEdge(struct Graph* G,int u,int v,int len)
{		//adds edge on both sides u->v and v->u
	struct Node* N;
	N=newnode(v,len);
	N->next=G->garray[u].head;
	G->garray[u].head=N;
	N=newnode(u,len);
	N->next=G->garray[v].head;
	G->garray[v].head=N;
}

struct Graph* creategraph(int nV)
{
	int i=0;
	struct Graph* G=malloc(sizeof(struct Graph));
	G->nV=nV;
	G->garray=malloc(nV* sizeof(struct List));
	for(i=0;i<nV;++i)
	{
		G->garray[i].head=NULL;
	}
	return G;
}

struct Node* newnode(int v,int len)
{
	struct Node* N=malloc(sizeof(struct Node));
	N->v=v;
	N->len=len;
	N->next=NULL;
	return N;
}