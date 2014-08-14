#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
using namespace std;
int A[200001],M[100001],St[100001],S,N,Q;
int increasing(int x,int y)
{
	
	int maxi=M[x];
	St[x]=M[x];
	//printf("%d ",M[x]);
	for(int i=x+1;i<=y;i++){
	//	printf("%d ",M[i]);
		if(St[i-1]>0)	St[i]=St[i-1]+M[i];
		else	St[i]=M[i];
		maxi=max(St[i],maxi);
	}
	return maxi;
}
int main()
{
	for(int i=0;i<100001;i++)	M[i]=0;
	int x,y,X,v,ans;
	char c;
	scanf("%d%d%d",&S,&N,&Q);
	for(int i=1;i<=S;i++){
		scanf("%d",&v);
		A[i]=v;
	}
	for(int i=S+1;i<=2*N;i++)		A[i]=A[i-S];
	for(int counter=0;counter<Q;counter++){
		scanf(" %c",&c);
		if(c=='U'){
			scanf("%d%d%d",&x,&y,&X);
			X=X%S;
			if(X==0)	X=S;
			for(int i=x;i<=y;i++)	M[i]=A[X+i-x];
		}
		else{
			scanf("%d%d",&x,&y);
			ans=increasing(x,y);
			printf("%d\n",ans);
		}
	}
	return 0;
}
