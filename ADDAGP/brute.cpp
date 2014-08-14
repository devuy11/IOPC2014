#include<stdio.h>
#include<string.h>
#include<iostream>
#include<algorithm>
#include<stdlib.h>
#include<set>
#include<map>
#include<bitset>
#include<vector>
using namespace std;
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
typedef long long int ll;
const int mod = 100711433;

vector<int> myvector[100001];
int N,parent[100001],depth[100001],Q,U,A,B,r;
int store[100001];
ll ans[100001],powmod[100001];


/***************DFS REQUIRED FOR THE PROBLEM*****************************************/
void dfs_pre(int root)
{
	for(vector<int>::iterator it=myvector[root].begin();it!=myvector[root].end();it++){
		if(parent[root]==*it)	continue;
		parent[*it]=root;
		depth[*it]=depth[root]+1;
		dfs_pre(*it);
	}
}
/***************DFS REQUIRED FOR THE PROBLEM*****************************************/

/*********************************FOR FINDING LCA***********************************/
int Root[100001][18];
void init()
{
	store[0]=0;store[1]=0;store[2]=1;
	int cmp=4;
	FOR(i,3,100000){
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

/***************************MAIN FUNCTION TO SOLVE THE PROBLEM*********************/
void solve()
{
	ll a,d,step,val;
	int anc,x,y;
	scanf("%d%d",&N,&r);

	FOR(i,1,N-1){
		scanf("%d%d",&x,&y);
		myvector[x].push_back(y);
		myvector[y].push_back(x);
	}
	parent[1]=1;
	depth[1]=0;
	dfs_pre(1);
	process(N);
	powmod[0]=1;
	FOR(i,1,100000)	powmod[i]=(powmod[i-1]*(ll)r)%mod;
	scanf("%d%d",&U,&Q);
	memset(ans,0,sizeof(ans));
	while(U--){
		scanf("%lld%d%d",&a,&A,&B);
		d=1;
		anc=lca(A,B);
		step=1;
		while(A!=anc){
			ans[A]=(ans[A]+((step*a)%mod)*((d*powmod[step])%mod))%mod;
			A=parent[A];
			step++;
		}
		vector<int> rachit;
		while(B!=anc){
			rachit.push_back(B);
			B=parent[B];
		}
		rachit.push_back(anc);
		reverse(rachit.begin(),rachit.end());
		for(vector<int>::iterator it=rachit.begin();it!=rachit.end();it++){
			ans[*it]=(ans[*it]+((step*a)%mod)*((d*powmod[step])%mod))%mod;
			step++;	
		}
	}
	while(Q--){	
		scanf("%d%d",&A,&B);
		anc=lca(A,B);
		val=0;
		while(A!=anc){
                        val=(val+ans[A])%mod;
                        A=parent[A];
                }
                while(B!=anc){
			val=(val+ans[B])%mod;
                        B=parent[B];
                }
		val=(val+ans[anc])%mod;
		printf("%lld\n",val);
	}
}
/***************************MAIN FUNCTION TO SOLVE THE PROBLEM*********************/

int main()
{
	init();
	solve();
	return 0;
}
