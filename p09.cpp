/*
	Assignment No. : 09
	Title : Boolean Satisfiability (3-CNF)
	Name : Supraja Narra
	email id : snarra1@binghamton.edu
	Date : 05/10/2015 3:40AM

*/
	//Header files
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#define MAX 1000

using namespace std;

	//Variable declarations
int nVar,nClauses;
int input[MAX][MAX];
bool gotsolution=false,flag=0;

	//Function Declarations
void backTrackCompute(int depth, vector<int> v);
int getabs(int i);

	//Main function
int main()
{
	int i=0,j=0;
	scanf("%d",&nVar);
	scanf("%d",&nClauses);
	for(i=0;i<nClauses;i++)
	{
		for(j=0;j<3;j++)
		{
			scanf("%d",&input[i][j]);
		}
	}
	vector<int> v;
	backTrackCompute(0,v);
	if(!gotsolution)
		cout<<"Not Satisfiable"<<std::endl;
	return 0;
}
	//computes and prints the output, and returns if solution is found
void backTrackCompute(int depth,vector<int> v)
{
	int j=0,k=0;
	unsigned int i;
	if(flag==1)
	{
		return;
	}
	if(depth==nVar)
	{
		int clauseeval=0, allclausesseval=1, temp, temp2;
		for(j=0;j<nClauses;j++)
		{
			clauseeval=0;
			for(k=0;k<3;k++)
			{
				temp=input[j][k];
				temp2=v[getabs(temp)-1];
				if(temp<0)
				{
					if(temp2==1)
						temp2=0;
					else
						temp2=1;
				}
				clauseeval|=temp2;
			}
			allclausesseval&=clauseeval;
		}
		if(allclausesseval)
		{
			flag=1;
			for(i=0;i<v.size();i++)
			{
				cout<<v[i]<<std::endl;
			}
			gotsolution=true;
		}
		return;
	}
	vector<int> v1;
	vector<int> v2;
	for(i=0;i<v.size();i++)
	{
		v1.push_back(v[i]);
		v2.push_back(v[i]);
	}
	v1.push_back(1);
	backTrackCompute(depth+1,v1);
	v2.push_back(0);
	backTrackCompute(depth+1,v2);
}
	//returns absolute value
int getabs(int i)
{
	return((i<0)?(-1*i):i);
}