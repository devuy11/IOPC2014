//Heavy Light Decomposition
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<iostream>
#include<string.h>
#include<vector>
#include<set>
#include<map>
#include<utility>
#include<bitset>
#include<queue>
#include<stack>
using namespace std;

typedef long long int ll;
#define INF 1000000000

//Variables required for HL tree
int which[100001],size_sub[100001],parent[100001],depth[100001],seg_size,mapping[100001],counter,skip[100001],N,root,visit[100001],level;
bool hlson[100001];
vector<int> myvector[100001];

int power[25];
void constant()
{
	power[0]=1;
	for(int i=1;i<=25;i++)	power[i]=power[i-1]<<1;
}
int obtain(int x)
{
	int l=0,y=x;
	while(x!=0){
		l++;
		x>>=1;
	}
	if(power[l-1]!=y)	l++;
	return l;
}
struct node{
	ll sum,dsum;
	node(ll a=0,ll b=0){
		sum=a;dsum=b;
	}
	node operator + (const node &x)const{
		return node(x.sum+sum,x.dsum+dsum);
	}
}HL[1<<18],freq[100002];

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


/*********************************HL Tree Coding Begins***************************/
void dfs_pre(int root)
{
	which[root]=-1;
	skip[root]=root;	//only purpose is to init it!
	size_sub[root]=1;
	for(vector<int>::iterator it=myvector[root].begin();it!=myvector[root].end();it++){
		if(parent[root]==*it)	continue;
		parent[*it]=root;
		depth[*it]=depth[root]+1;
		dfs_pre(*it);
		size_sub[root]+=size_sub[*it];
	}
	for(vector<int>::iterator it=myvector[root].begin();it!=myvector[root].end();it++){
		if(parent[root]==*it)   continue;
		if(size_sub[*it]>size_sub[root]/2){
			hlson[*it]=true;
			which[root]=*it;
		}
		else{
			hlson[*it]=false;
		}
	}
}
void dfs_cal(int root)
{
	//printf("%d us root\n",root);
	int z;
	for(vector<int>::iterator it=myvector[root].begin();it!=myvector[root].end();it++){
		if(parent[root]==*it)	continue;
		if(hlson[*it]){		//heavy node detected
			//printf("%d is Heavy\n",*it);
			skip[*it]=skip[root];
			if(skip[root]==root){
				z=*it;
				//construction of segment tree begins
				while(z!=-1){
					mapping[z]=seg_size;
					seg_size++;
					z=which[z];
				}
			}
		}
		dfs_cal(*it);
	}
}
void seg_Update(int l)
{
	int v;
	while(l!=0){
		v=(l<<1);
		HL[l]=HL[v]+HL[v+1];
		l>>=1;
	}
}
node seg_Query(int l,int r,int i,int j,int nod)
{
	int v,mid;
	if(j<l || i>r)	return node();
	if(l>=i && j>=r){
		return HL[nod];
	}
	v=nod<<1;
	mid=(l+r)>>1;
	return seg_Query(l,mid,i,j,v)+seg_Query(mid+1,r,i,j,v+1);
}
node HL_Update(int x,node v)
{
	int ind;
	if(hlson[x]){		//Heavy Part
		ind=mapping[x]+power[level-1];
		HL[ind]=HL[ind]+v;
		seg_Update(ind>>1);
	}
}
node HL_Query(int i,int j)		//from i to j --> j is the ancestor
{
	node r;
	int end,st;
	while(i!=j){
		if(hlson[i]){
			end=skip[i];
			st=i;
			i=end;
			end=which[i];
			if(depth[end]<=depth[j]){
				r=r+seg_Query(1,power[level-1],mapping[j]+1,mapping[st]+1,1);
				return r;
			}
			else{		//carry on
				r=r+seg_Query(1,power[level-1],mapping[end]+1,mapping[st]+1,1);
			}
		}
		else{
			r=r+freq[i];
			i=parent[i];
			//printf("%d is i %d is j\n",i,j);
		}
	}
	return r+freq[j];
}
/*********************************HL Tree Coding Ends***************************/
void print()
{
	for(int i=1;i<=N;i++)
		if(hlson[i])	printf("H ");
		else	printf("L ");
	printf("\n");
	for(int i=1;i<=N;i++)
		printf("%d ",which[i]);
	printf("\n");
        for(int i=1;i<=N;i++)
                printf("%d ",skip[i]);
	printf("%d is seg_size\n",seg_size);
}
void solve()
{
	char c;
	int x,y,anc,Q;
	ll s,b;
	memset(freq,0,sizeof(freq));
	scanf("%d%d%d",&N,&Q,&root);
	for(int i=1;i<N;i++){
		scanf("%d%d",&x,&y);
		myvector[x].push_back(y);
		myvector[y].push_back(x);
	}
	seg_size=0;
	parent[root]=root;
	depth[root]=0;
	dfs_pre(root);			//find heavy edges, parent, depth,which[]
	process(N);
	dfs_cal(root);			//construct segment tree;
	level=obtain(seg_size);
	//print();
	//printf("%d is the level obtained\n",level);
	for(int i=0;i<Q;i++){
		scanf(" %c",&c);
		if(c=='U'){
			scanf("%d%lld",&x,&s);
			b=(ll)depth[x]*s;
			HL_Update(x,node(s,b));
			int cmp=0,co=0;
			/*for(int i=1;i<=16;i++){
				printf("%lld ",HL[i].sum);
				co++;
				if(co==power[cmp]){
					printf("\n");
					co=0;
					cmp++;
				}
			}*/
			freq[x].sum+=s;
			freq[x].dsum+=b;
		}
		else{
			scanf("%d%d",&x,&y);
			anc=lca(x,y);
			node A=HL_Query(x,anc);
			node B=freq[anc];
			node C=HL_Query(y,anc);
			printf("%lld\n",A.dsum-B.dsum+C.dsum);
		}
	}
}
int main()
{
	constant();
	init();
	solve();
	return 0;
}
