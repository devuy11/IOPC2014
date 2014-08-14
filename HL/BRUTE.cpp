#include<stdio.h>
#include<vector>
#include<stdlib.h>
#include<string.h>
using namespace std;
typedef long long int ll;
vector<int> myvector[100001];
ll tree[100001];
int parent[100001],depth[100001];
/*********************************FOR FINDING LCA***********************************/
int Root[100001][18],store[100001];
void init()
{
	store[0]=0;store[1]=0;store[2]=1;
	int cmp=4;
	for(int i=3;i<=100000;i++){
		if(cmp>i)       store[i]=store[i-1];
		else{
			store[i]=store[i-1]+1;
			cmp<<=1;
		}
	}
}
void process(int N)
{
	memset(Root,-1,sizeof(Root));
	for(int i=1;i<=N;i++)	Root[i][0]=parent[i];
	for(int i=1;(1<<i)<=N;i++)
		for(int j=1;j<=N;j++)
			if(Root[j][i-1]!=-1)
				Root[j][i]=Root[Root[j][i-1]][i-1];
}
int lca(int p,int q)
{
	int temp;
	if(depth[p]>depth[q])	swap(p,q);
	int steps=store[depth[q]];
	for(int i=steps;i>=0;i--)
		if(depth[q]-(1<<i) >= depth[p])
			q=Root[q][i];
	if(p==q)	return p;
	for(int i=steps;i>=0;i--){
		if(Root[p][i]!=Root[q][i])
			p=Root[p][i],q=Root[q][i];
	}
	return parent[p];
}
/*********************************FOR FINDING LCA***********************************/
void dfs(int root)
{
	for(vector<int>::iterator it=myvector[root].begin();it!=myvector[root].end();it++){
		if(parent[root]==*it)	continue;
		parent[*it]=root;
		depth[*it]=depth[root]+1;
		dfs(*it);
	}
}

int main()
{
	char ab;
	int N,root,x,y,Q,anc;
	ll sum=0;
	scanf("%d%d%d",&N,&Q,&root);
	init();
	for(int i=1;i<N;i++){
		scanf("%d%d",&x,&y);
		myvector[x].push_back(y);
		myvector[y].push_back(x);
	}
	parent[root]=root;
	depth[root]=0;
	dfs(root);
	process(N);
	for(int i=0;i<Q;i++){
		scanf(" %c",&ab);
		if(ab=='U'){
			scanf("%d%d",&x,&y);
			tree[x]=tree[x]+depth[x]*y;
		}
		else{
			scanf("%d%d",&x,&y);
			anc=lca(x,y);
			sum=0;
			while(x!=anc){
				sum+=tree[x];
				x=parent[x];
			}
			while(y!=anc){
				sum+=tree[y];
				y=parent[y];
			}
			sum+=tree[anc];
			printf("%lld\n",sum);
		}
	}
}
