#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
#define INF (1<<30)
#define Max_N 100
#define Nodes 2*Max_N + 4
#define Edges 8*Max_N + 2 + 2*Max_N*Max_N 
int nodes,edges,to[Edges],fin[Edges],next[Edges],cop[Nodes],dist[Nodes],cap[Edges],flow[Edges],Q[Nodes],answer;

int src,snk,S,T,rooms;

int N,M;
void addedge(int u,int v,int c)
{
	to[edges]=v;
	next[edges]=fin[u];
	fin[u]=edges;
	cap[edges]=c;
	flow[edges]=0;
	edges++;
}
bool bfs()
{
	for(int i=0;i<nodes;i++)	dist[i]=-1;
	int st=0,end=1,u,v;
	Q[0]=src;
	dist[src]=0;
	while(st<end){
		u=Q[st];
		st++;
		for(int i=fin[u];i!=-1;i=next[i]){
			v=to[i];
			if(flow[i]<cap[i] && dist[v]==-1){
				dist[v]=dist[u]+1;
				Q[end]=v;
				end++;
			}
		}
	}
	return dist[snk]!=-1;
}
int dfs(int u,int fl)
{
	int val,v;
	if(u==snk)	return fl;
	for(int &e=cop[u];e!=-1;e=next[e]){
		v=to[e];
		if(flow[e]<cap[e] && dist[v]==dist[u]+1){	
			val=dfs(v,min(fl,cap[e]-flow[e]));
			if(val>0){
				flow[e]+=val;
				flow[e^1]-=val;
				return val;
			}
		}
	}
	return 0;
}
int Network()
{
	int ans=0,x;
	while(bfs()){
		for(int i=0;i<nodes;i++)	cop[i]=fin[i];
		while(true){
			x=dfs(src,INF);
			if(x==0)	break;
			else	ans+=x;
		}
	}
	return ans;
}
void graph()
{
	rooms=0;
	edges=0;
	int A[100],B[100],C[100],clean[100][100];
	scanf("%d%d",&N,&M);
	nodes=2*N+4;
	for(int i=0;i<nodes;i++)	fin[i]=-1;
	for(int i=0;i<N;i++){
		scanf("%d%d%d",&A[i],&B[i],&C[i]);
		if(C[i]%M==0)   C[i]=C[i]/M;
		else    C[i]=C[i]/M + 1;
		rooms+=C[i];
	}
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			scanf("%d",&clean[i][j]);
		}
	}
	src=0;
	snk=2*N+3;
	S=N+1;
	T=S+1;
	for(int i=0;i<N;i++){
		addedge(src,i+1,C[i]);
		addedge(i+1,src,0);
	
		addedge(i+1,S,INF);
		addedge(S,i+1,0);
		
		addedge(T,T+i+1,INF);
		addedge(T+i+1,T,0);
	
		addedge(T+i+1,snk,C[i]);
		addedge(snk,T+i+1,0);
	}
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if(B[i]+clean[i][j]<A[j]){
				addedge(i+1,T+j+1,INF);
				addedge(T+j+1,i+1,0);
			}
		}
	}
	addedge(S,T,0);
	addedge(T,S,0);
}
void binary_search(int low,int high)
{
	if(low>high)	return ;
	int mid=(low+high)/2;
	memset(flow,0,sizeof(int)*(edges));	
	cap[edges-2]=mid;
	int val=Network();
	if(val==rooms){
		answer=mid;
		return binary_search(low,mid-1);
	}
	else
		return binary_search(mid+1,high);
}
int main()
{
	int T;
	scanf("%d",&T);
	for(int tes=1;tes<=T;tes++){
		graph();
		answer=0;
		binary_search(1,rooms);
		printf("Case %d: %d\n",tes,answer);
	}
	return 0;
}
