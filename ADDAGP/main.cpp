#include<stdio.h>
#include<string.h>
#include<iostream>
#include<algorithm>
#include<stdlib.h>
#include<set>
#include<map>
#include<bitset>
#include<vector>
#include<assert.h>
using namespace std;
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
typedef long long int ll;
const int mod = 100711433;

vector<int> myvector[100001];
struct node{
	ll sum,start;
}Frwd_Tree[100001],Bkwd_Tree[100001];
int N,parent[100001],depth[100001],Q,U,A,B,r,invr,powmod[100001];
ll sum[100001];
int store[100001];

/************SMALL FUNCTIONS REQUIRED***********/
ll inverse(ll a,ll b)
{
	ll Remainder,p0=0,p1=1,pcurr=1,q,m=b;
	while(a!=0){
		Remainder=b%a;
		q=b/a;
		if(Remainder!=0){
			pcurr=p0-(p1*q)%m;
			if(pcurr<0)
				pcurr+=m;
			p0=p1;
			p1=pcurr;
		}
		b=a;
		a=Remainder;
	}
	return pcurr;	
}
ll multiply(ll a,ll b)
{
        return (a*b)%mod;
}
/************SMALL FUNCTIONS REQUIRED***********/


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
void dfs_cal(int root)          //stores the value of each node in sum[]
{
	for(vector<int>::iterator it=myvector[root].begin();it!=myvector[root].end();it++){
		if(parent[root]==*it)   continue;
		dfs_cal(*it);
		Frwd_Tree[root].sum=(Frwd_Tree[root].sum+(Frwd_Tree[*it].sum+Frwd_Tree[*it].start)*(ll)r)%mod;
		Frwd_Tree[root].start=(Frwd_Tree[root].start+Frwd_Tree[*it].start*(ll)r)%mod;
		Bkwd_Tree[root].sum=(Bkwd_Tree[root].sum+Bkwd_Tree[*it].sum*(ll)invr-Bkwd_Tree[*it].start*(ll)invr)%mod;
		Bkwd_Tree[root].start=(Bkwd_Tree[root].start+Bkwd_Tree[*it].start*(ll)invr)%mod;
	}
	sum[root]=(ll)(Frwd_Tree[root].sum+Bkwd_Tree[root].sum)%mod;
}
void dfs_sum(int root)          //finds the cumm sum from root
{
	for(vector<int>::iterator it=myvector[root].begin();it!=myvector[root].end();it++){
		if(parent[root]==*it)   continue;
		sum[*it]=(sum[*it]+sum[root])%mod;
		dfs_sum(*it);
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
	ll mul,ans,a,d,gul;
	int Z,anc,x,y;
	scanf("%d%d",&N,&r);
	assert(N<=100000);
	assert(r<=1000000000 && r>=2);
	invr=inverse(r,mod);
	FOR(i,1,N-1){
		scanf("%d%d",&x,&y);
		assert(x>=1 && x<=N);
		assert(y>=1 && y<=N);
		myvector[x].push_back(y);
		myvector[y].push_back(x);
	}
	parent[1]=1;
	depth[1]=0;
	dfs_pre(1);
	process(N);

	powmod[0]=1;
	FOR(i,1,N)	powmod[i]=((ll)powmod[i-1]*(ll)r)%mod;
	scanf("%d%d",&U,&Q);
	assert(U<=100000);
	assert(Q<=100000);
	while(U--){
		scanf("%lld%d%d",&a,&A,&B);
		d=1;
		assert(a<=1000000000 && A<=N && B<=N && A>=1 && B>=1);
		anc=lca(A,B);
		//Update for Node A
		mul=multiply((a*(ll)d)%mod,r);
		Frwd_Tree[A].sum=(Frwd_Tree[A].sum + mul)%mod;
		Frwd_Tree[A].start=(Frwd_Tree[A].start + mul)%mod;
		//BackWard Update
		gul=multiply(a,(d*(ll)powmod[(depth[A]-2*depth[anc]+depth[B]+1)])%mod);
		mul=(gul*(ll)(depth[A]-2*depth[anc]+depth[B]+1))%mod;
		Bkwd_Tree[B].sum=(Bkwd_Tree[B].sum + mul)%mod;
		Bkwd_Tree[B].start=(Bkwd_Tree[B].start + gul)%mod;
		//Forward Update for Parent Anc
		if(anc!=1){
			Z=parent[anc];
			gul=multiply(a,(d*(ll)powmod[(depth[A]-depth[anc]+2)])%mod);
			mul=(gul*(ll)(depth[A]-depth[anc]+2))%mod;
			Frwd_Tree[Z].sum=(Frwd_Tree[Z].sum -mul)%mod;
			Frwd_Tree[Z].start=(Frwd_Tree[Z].start -gul)%mod;
		}
		//Backward Update for Anc
		gul=multiply(a,(d*(ll)powmod[(depth[A]-depth[anc]+1)])%mod);
		mul=(gul*(ll)(depth[A]-depth[anc]+1))%mod;
		Bkwd_Tree[anc].sum=(Bkwd_Tree[anc].sum - mul)%mod;
		Bkwd_Tree[anc].start=(Bkwd_Tree[anc].start - gul)%mod;
	}
	dfs_cal(1);
	dfs_sum(1);
	while(Q--){	
		scanf("%d%d",&x,&y);
		assert(x<=N && y<=N && x>=1 && y>=1);
		anc=lca(x,y);
		if(anc!=1)	ans=(sum[x]+sum[y]-sum[anc]-sum[parent[anc]])%mod;
		else	ans=(sum[x]+sum[y]-sum[anc])%mod;
		if(ans<0)	printf("%lld\n",ans+mod);
		else	printf("%lld\n",ans);
	}
}
/***************************MAIN FUNCTION TO SOLVE THE PROBLEM*********************/

int main()
{
	init();
	solve();
	return 0;
}
