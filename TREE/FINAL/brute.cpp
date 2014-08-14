#include<stdio.h>
#include<iostream>
#include<string.h>
#include<vector>
#include<assert.h>
using namespace std;
int N,Q,value[100001],depth[100001],parent[100001],store[100001],trash[100001];

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
/********************************POWER TOWER LIGHT BRUTE CODE**********************/
typedef long long int ll;
int Edit[1025];
int head[1025][1025],cycle[1025][1025];
int max_L[1025];
int max_p,steps;
int gcd(int x,int y)
{
	if(y==0){
		return x;
	}
	return gcd(y,x%y);
}
//check if a^b is less than n or not, if a^b is greater than n return -1 otherwise return the **exact value**

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
//Returns the value of a^b mod m
ll binpow(ll a,ll b,ll mod)
{
	assert(mod!=0);
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

void constant(ll a,ll mod)
{
	if(cycle[mod][a]!=-1)	return;
	memset(Edit,0,mod*sizeof(int));
	int len=1,x,y,c;
	ll v=1;
	while(1){
		v=(v*a)%mod;
		if(Edit[v]!=0){
			x=Edit[v]-1;
			y=len-Edit[v];
			break;
		}
		else{
			steps++;
			Edit[v]=len;
			len++;
		}
	}
	cycle[mod][a]=y;
	head[mod][a]=x;
	ll z=x;
	for(int i=0;i<y;i++){
		steps++;
		cycle[mod][v]=y/gcd(y,z+1);
		head[mod][v]=0;
		z++;
		v=(v*a)%mod;
	}
}
void preprocess()
{
	steps=0;
	memset(cycle,-1,sizeof(cycle));
	max_p=0;
	int v,per,s,maxii=0;
	for(int m=1;m<=1024;m++){
		for(int i=0;i<m;i++){
			v=i;
			constant(v,m);
		}
	}
}
int fun(int x,int v,int h,int p,int p1)
{
	assert(p!=0);
	int r=(p+v-h%p)%p,pow;
	if(r==0)	pow=h+p;
	else	pow=h+r;
	return binpow(x,pow,p1);
}
pair<int,int> find_it(int a,int mod)
{
	int EDIT[100001];
	memset(EDIT,0,sizeof(EDIT));
	int len=1,x,y,c;
	ll v=1;
	//Finding x
	while(1){
		v=(v*a)%mod;
		if(EDIT[v]!=0){
			x=EDIT[v]-1;
			y=len-EDIT[v];
			break;
		}
		else{
			EDIT[v]=len;
			len++;
		}
	}
	return make_pair(y,x);
}
int powe(int arr[],int upto,int threshold,int M)
{
	int ans=1,over=1;
	if(threshold){
		for(;upto>=0;upto--){
			over=check(arr[upto],ans,2*M);
			if(over<0)	break;
			ans=over;
		}
		upto++;
		arr[upto]=ans;
	}
	int period[10],start[10],z=M,modulo[10];
	for(int i=0;i<=upto;i++){
		if(z>1000){
			pair<int,int> p=find_it(arr[i],z);
			period[i]=p.first;
                        start[i]=p.second;
                        modulo[i]=z;
                        arr[i]=(arr[i]%z);
                        z=period[i];
		}
		else{
			period[i]=cycle[z][arr[i]%z];
			start[i]=head[z][arr[i]%z];
			modulo[i]=z;
			arr[i]=(arr[i]%z);
			z=period[i];
		}
		if(period[i]==1 &&  start[i]==0){
			upto=i;
			break;
		}
	}
	//for(int i=0;i<=upto;i++)	printf("%d ",arr[i]);
	//printf("\n");
	int st=upto-1;
	//printf("%d is st\n",st);
	for(;st>=0;st--)
		arr[st]=fun(arr[st],arr[st+1],start[st],period[st],modulo[st]);
	return arr[0];
}

/********************************POWER TOWER LIGHT BRUTE CODE*********************/
int main()
{
	preprocess();
	init();
	int x,y,a,b,anc,upto,arr[50],total,p,st,M;
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
		}
		else{
			scanf("%d",&M);
			upto=0;
			st=0;
			anc=lca(a,b);
			while(a!=anc){
				arr[upto]=value[a];
				upto++;
				if(upto==50)	break;
				a=parent[a];
			}
			if(upto<50){
				arr[upto]=value[a];
				upto++;
			}
			if(upto<50){
				while(b!=anc){
					trash[st]=value[b];
					b=parent[b];
					st++;
				}
			}
			st--;
			while(upto<50 && st>=0){
				arr[upto]=trash[st];
				st--;	
				upto++;
			}
			printf("%d\n",powe(arr,upto-1,1,M));
		}
	}
	return 0;
}
