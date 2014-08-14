#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<string.h>
#include<assert.h>
using namespace std;
#define INF (1000000000)
#define Left 50
#define Nodes 2*Left + 2
#define Edges 2*(Left+Left+Left*Left)
#define hagga 0
typedef long long int ll;
int nodes,edges,to[Edges],fin[Edges],next[Edges],cop[Nodes],dist[Nodes],cap[Edges],flow[Edges],Q[Nodes];
int rowsum[51],colsum[51],sum,osum;
int answer[51][51];
int edge_num[51][51],Lefty[51],Righty[51];
int src,snk,N,M;

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
void init_flow()
{
	for(int i=0;i<edges;i++)	flow[i]=0;
}
bool try_zero(int i,int j)
{
	cap[edge_num[i][j]]=0;
	int val=Network();
	if(val==sum)	return true;
	if(hagga)	printf("zero %d is val\n",val);
	return false;
}
bool try_one(int i,int j)
{
	cap[edge_num[i][j]]=0;
	cap[Lefty[i]]--;
	cap[Righty[j]]--;
	int val=Network();
	if(hagga)	printf("one %d is val\n",val);
	if(val+1==sum){
		sum--;
		return true;
	}
	return false;
}
void verify(int a)
{
	for(int i=1;i<=M;i++){
		if(cap[Righty[i]]==N-a+1){
			for(int j=a;j<=N;j++){	//answer[i,j]=1
				answer[j][i]=1;
				cap[edge_num[j][i]]=0;
				cap[Righty[i]]--;
				cap[Lefty[j]]--;
				sum--;
			}
		}
		else if(cap[Righty[i]]==0){
			for(int j=a;j<=N;j++){  //answer[i,j]=1
				answer[j][i]=1;
				cap[edge_num[j][i]]=0;
			}	
		}
	}
}
void solve()
{
	bool check;
	int x;
	sum=osum=0;
	scanf("%d%d",&N,&M);
	edges=0;
	src=0;
	snk=N+M+1;
	nodes=snk+1;
	for(int i=0;i<nodes;i++)	fin[i]=-1;

	for(int i=1;i<=N;i++){
		scanf("%d",&x);
		sum+=x;
		Lefty[i]=edges;
		addedge(src,i,x);
		addedge(i,src,0);
	}

	for(int i=1;i<=M;i++){
		scanf("%d",&x);
		osum+=x;
		Righty[i]=edges;
		addedge(i+N,snk,x);
		addedge(snk,i+N,0);
	}
	/*for(int i=1;i<=N;i++){
		if(cap[Lefty[i]]==M){
			for(int j=1;j<=M;j++){
				answer[i][j]=1;
				cap[edge_num[i][j]]=0;
				cap[Righty[j]]--;
			}
			cap[Lefty[i]]=0;
			sum-=M;
		}
		else if(cap[Lefty[i]]==0){
			for(int j=1;j<=M;j++){
				cap[edge_num[i][j]]=0;
				answer[i][j]=0;
			}
		}
	}*/
	if(sum!=osum){
		printf("-1\n");
		return ;
	}
	for(int i=1;i<=N;i++){
		for(int j=1;j<=M;j++){
			edge_num[i][j]=edges;
			addedge(i,j+N,1);
			addedge(j+N,i,0);
		}
	}
	memset(answer,-1,sizeof(answer));
	for(int i=1;i<=N;i++){
		for(int j=1;j<=M;j++){
			if(answer[i][j]!=-1)	continue;
			init_flow();
			check=try_zero(i,j);
			if(!check){
				init_flow();
				check=try_one(i,j);
				answer[i][j]=1;
			}
			else{
				answer[i][j]=0;
			}
			if(!check){
				printf("-1\n");
				return ;
			}
		}
	}
	for(int i=1;i<=N;i++){
		for(int j=1;j<=M;j++){
			printf("%d",answer[i][j]);
		}
		printf("\n");
	}
}
int main()
{
	int test;
	scanf("%d",&test);
	//assert(test<=20);
	for(int i=1;i<=test;i++){
		printf("TestCase #:%d\n",i);
		solve();
	}
	return 0;
}
