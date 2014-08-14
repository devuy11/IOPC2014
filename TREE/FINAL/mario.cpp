#include<stdio.h>
#include<iostream>
#include<string.h>
#include<vector>
#include<assert.h>
using namespace std;
int N,Q,value[100001],depth[100001],parent[100001],store[100001];

vector<int> myvector[100001];
void dfs(int root)
{
	for(vector<int>::iterator it=myvector[root].begin();it!=myvector[root].end();it++){
		if(parent[root]==*it)	continue;
		parent[*it]=root;
		depth[*it]=depth[root]+1;
		dfs(*it);
	}
}

/*********************************FOR FINDING LCA***********************************/
int Root[100001][18];
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

int find(int q,int p)		//node q se upper jao aur jiska level p aaye return karo
{
	//	assert(depth[q]>=p);
	if(depth[q]==p)	return q;
	int steps=store[depth[q]];

	for(int i=steps;i>=0;i--)
		if(depth[q]-(1<<i) >= p)
			q=Root[q][i];
	return q;
}
/*****************Power Tower********************************/
#define Level 20
typedef long long int ll;
int input[Level+1];
int sieve_par=319;
int prime[320] , array[320],counter=0;
struct A
{
	int x,p;
	A(int a=0,int b=0){
		x=a;p=b;
	}
}factor[6][100001];
int size[100001];
ll inverse(ll a,ll b)					//b>a
{
	ll Remainder,p0=0,p1=1,pcurr=1,q,m=b;
	while(a!=0)
	{
		Remainder=b%a;
		q=b/a;
		if(Remainder!=0)
		{
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
ll binpow(ll a,ll b,ll mod)
{
	ll ans=1;
	while(b)
		if(b&1){
			ans=(ans*a)%mod;
			b--;

		}
		else{	
			a=(a*a)%mod;
			b>>=1;
		}
	return ans%mod;
}
ll CRT(ll mod[],ll rem[],int t)			//t is the number of pairs of rem and mod
{
	ll ans = rem[0],m = mod[0];

	for(int i = 1;i < t;++i)
	{
		ll a = inverse(m,mod[i]);
		ll b = inverse(mod[i],m);
		ans = (ans * b * mod[i] + rem[i] * a * m) % (m * mod[i]);
		m *= mod[i];
	}   
	return ans;
}
void sieve()
{
	for(int i=1;i<sieve_par;i++)
		array[i]=1;
	array[0]=0;
	int j;
	for(int i=2;i<=sieve_par;i++)
	{
		if(array[i-1]==1)
		{
			prime[counter]=i;
			for(j=i*i;j<=sieve_par;j+=i)
				array[j-1]=0;
			counter++;
		}
	}
}
void constant()
{
	int remaining[100001],x,y;
	for(int i=0;i<100001;i++)	remaining[i]=i,size[i]=0;
	for(int i=0;i<counter;i++){
		for(int j=prime[i];j<100001;j=j+prime[i]){
			x=1;
			while(remaining[j]%prime[i]==0){
				remaining[j]/=prime[i];
				x=x*prime[i];
			}
			factor[size[j]][j]=A(x,prime[i]);
			size[j]++;
		}
	}
	for(int i=0;i<100001;i++){
		if(remaining[i]!=1){
			factor[size[i]][i]=A(remaining[i],remaining[i]);
			size[i]++;
		}
	}
}
int check(ll a,ll b,ll n)
{
	ll ans=1;
	while(b)
		if(b&1){
			ans=ans*a;
			if(ans>n)	return -1;
			b--;
		}
		else{
			a=a*a;
			if(a>n)		return -1;
			b>>=1;	
		}
	return ans;
}
int set_tol(int x,int M)
{
	int ans=1,over;
	for(;x>=0;x--){
		over=check(input[x],ans,2*M);
		if(over<0)	break;
		ans=over;
	}
	x++;
	input[x]=ans;
	return x;
}
int fun(int st,int end,int mod)
{
	int x;
	if(st==end)	return input[st]%mod;
	if(input[st]%mod==0)	return 0;
	int s=size[mod];
	ll modi[6],rem[6];
	for(int i=0;i<s;i++){
		modi[i]=factor[i][mod].x;
		if(input[st]%factor[i][mod].p==0){
			x=0;
			if(st+1==end){
				x=input[st];
				while(x%factor[i][mod].p==0){
					x=x/factor[i][mod].p;
				}
				x=input[st]/x;
				x=check(x,input[end],modi[i]);
				if(x!=-1){
					rem[i]=binpow(input[st],fun(st+1,end,factor[i][mod].x-factor[i][mod].x/factor[i][mod].p),factor[i][mod].x);
				}
				else    rem[i]=0;
			}
			else    rem[i]=0;
		}
		else	rem[i]=binpow(input[st],fun(st+1,end,factor[i][mod].x-factor[i][mod].x/factor[i][mod].p),factor[i][mod].x);
	}
	int ans=CRT(modi,rem,s);
	return ans;
}
/*******************************Power Tree*******************************/
int main()
{
	int m;
	sieve();
	constant();
	init();
	int x,y,a,b,anc,upto,total,p,z;
	char x1;
	scanf("%d%d",&N,&Q);
	for(int i=1;i<N;i++){
		scanf("%d%d",&x,&y);
		myvector[x].push_back(y);
		myvector[y].push_back(x);
	}
	for(int i=1;i<=N;i++)	scanf("%d",&value[i]);
	depth[1]=0;		//depth of root is 0
	parent[1]=1;
	dfs(1);
	process(N);
	for(int i=0;i<Q;i++){
		scanf(" %c%d%d",&x1,&a,&b);
		if(x1=='U'){
			value[a]=b;
			assert(a>=1 && a<=N);
		}
		else{
			assert(a>=1 && a<=N);
			assert(b>=1 && b<=N);
			scanf("%d",&m);
			upto=0;
			anc=lca(a,b);
			total=depth[b]-2*depth[anc]+depth[a]+1;
			if(total>20){
				if(depth[a]-depth[anc]>=19){
					while(upto<20){
						input[upto]=value[a];
						a=parent[a];
						upto++;
					}
				}
				else{
					z=a;
					while(a!=anc){
						input[upto]=value[a];
						a=parent[a];
						upto++;
					}
					p=find(b,depth[anc]+20-(depth[z]-depth[anc]+1));
					for(int j=19;j>=upto;j--){
						input[j]=value[p];
						p=parent[p];
					}
					upto=20;
				}
			}
			else{
				while(a!=anc){
					input[upto]=value[a];
					a=parent[a];
					upto++;
				}
				for(int j=total-1;j>=upto;j--){
					input[j]=value[b];
					b=parent[b];
				}
				upto=total;
			}
			x=upto;
			x=set_tol(x-1,m);
			printf("%d\n",fun(0,x,m));
		}
	}
	return 0;
}

