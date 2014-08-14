/*
Logic

Let the minimum area required excluding the good J be A1
Let the minimum area required including all good J be A2

Claim :: Area Purchased will be A1 if P[J] < C 
Proof :: let the Area be A3 at which max profit occurs. It is trivail that A3 > A1 . Now If we are able to put more than A3-A1 extra packets then it may be the solution.But this is not possible because then the solution A1 is not optimal.(As 2 jobs cannot be scheduled at the same time in the same place)
let a be the parcels which will be adjusted in A1
Hence it follows that A2= A1+X[J]-a
let devu be the profit in taking the A2 area
and let rachit be the profit in taking A1 area
devu=rachit + X[J]*P[J] - C*(A2-A1)  // profit - loss
substituting we get
devu = rachit + X[J]*P[J] - C*(X[J]-a)
devu - rachit - X[J]*P[J] + C*X[J] = a*C
a = (devu -rachit -X[J]*P[J] + C*X[J]) / C
Answer will be (rachit + a*P[J])

If P[J] > C then it is obvious to take all the gifts.
Print Total Parcel of J Delivered and Total Profit Obtained.
If P[J] >= C , then deliver all the Parcels :)
*/
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<string.h>
#include<assert.h>
using namespace std;
#define INF (1<<30)		//summation of Number of parcels will be less than INF
#define Max_N 100		//Maximum N given is 100
#define Nodes 2*Max_N + 4	//Maximum Nodes will be 1+N+1+1+N+1
#define Edges 8*Max_N + 2 + 2*Max_N*Max_N 	//Maximum Edges :: 2*(MaxN + MaxN + MaxN + MaxN + 1 + MaxN*MaxN)
typedef long long int ll;
int nodes,edges,to[Edges],fin[Nodes],next[Edges],cop[Nodes],dist[Nodes],cap[Edges],flow[Edges],Q[Nodes],answer;

int src,snk,S,T,parcels,M,V;

int N,J,C,ind1,ind2;
int X[100],A[100],B[100],P[100],clean[101][101];

ll sum;
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
	parcels=0;			//parcels denote the total order of all goods
	edges=0;
	sum=0;
	scanf("%d%d%d%d%d",&N,&M,&J,&C,&V);		//N is the variety of goods, C is the cost per area
	assert(N<=100);
	assert(J<=N && J>=1);
	assert(C<=100000 && C>=1);
	assert(M<=N*N);
	J--;
	nodes=2*N+4;
	for(int i=0;i<nodes;i++)	fin[i]=-1;
	for(int i=0;i<N;i++){
		scanf("%d%d%d%d",&X[i],&A[i],&B[i],&P[i]);	//X orders, A st time, B end time, P amount for each parcel
		assert(X[i]<=1000000 && X[i]>=1);
		assert(A[i]>=1 && A[i]<B[i]);
		assert(B[i]<=1000000000);
		assert(P[i]<=1000000 && P[i]>=1);
		parcels+=X[i];
		sum+=(ll)X[i]*(ll)P[i];
	}
	src=0;
	snk=2*N+3;
	S=N+1;
	T=S+1;
	for(int i=0;i<N;i++){
		if(i==J)	ind1=edges;	//storing the indices where Good J is used
		addedge(src,i+1,X[i]);
		addedge(i+1,src,0);
	
		addedge(i+1,S,INF);
		addedge(S,i+1,0);
		
		addedge(T,T+i+1,INF);
		addedge(T+i+1,T,0);
	
		if(i==J)	ind2=edges;
		addedge(T+i+1,snk,X[i]);
		addedge(snk,T+i+1,0);
	}
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if(B[i]<A[j]){
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
	if(val==parcels){
		answer=mid;
		return binary_search(low,mid-1);
	}
	else
		return binary_search(mid+1,high);
}
int main()
{
	int T,area1,area2,a;
	ll rachit,devu,val;
	scanf("%d",&T);
	assert(T<=5);
	for(int tes=1;tes<=T;tes++){
		graph();		//Taking the graph
		if(P[J]>=C){
			answer=0;
                        binary_search(1,parcels);
			devu=sum-(ll)C*(ll)answer;
			printf("%d %lld\n",X[J],devu);
		}
		else{
			answer=0;
			binary_search(1,parcels);
			area1=answer;

			answer=0;
			cap[ind1]=cap[ind2]=0;
			parcels-=X[J];
			binary_search(1,parcels);
			area2=answer;

			rachit=sum-(ll)X[J]*(ll)P[J]-(ll)C*(ll)area2;

			devu=sum-(ll)C*(ll)area1;

			val=devu-rachit+(ll)C*(ll)X[J]-(ll)X[J]*(ll)P[J];
			assert(val%C==0);
			a=(ll)val/(ll)C;
			printf("%d %lld\n",a,rachit+(ll)a*(ll)P[J]);
		}
	}
	return 0;
}
