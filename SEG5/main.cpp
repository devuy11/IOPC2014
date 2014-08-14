#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<assert.h>
using namespace std;
typedef long long int ll;
ll INF = (ll)(1<<21) *(ll)(1<<21);
int power[27];
struct node{
	ll best_sum,sum,best_pre,best_suf;
	int t,s,e;
	node(ll a=-INF,ll b=-INF,ll c=-INF,ll d=-INF,int f=0,int g=0,int h=0){
		sum=a;
		best_pre=b;
		best_suf=c;
		best_sum=d;
		t=f;
		s=g;
		e=h;
	}
	bool operator == (const node & x) const {
		if(sum==x.sum && best_sum==x.best_sum && best_pre==x.best_pre && best_suf==x.best_suf)	return true;
		return false;
	}
}core[1<<18],smart[1001][1001];
int S,N,Q,counter,clev;	//S numbers and N size seg tree

int obtain(int x)
{
	int lev=0;
	int y=x;
	while(x!=0){
		x>>=1;
		lev++;
	}
	if(power[lev-1]!=y)	lev++;
	return lev;
}

/************************smart calculations*********************/
node merge(node A,node B)
{
        if(A==node())   return B;
        if(B==node())   return A;
        return node (  A.sum+B.sum , max(A.best_pre,A.sum+B.best_pre) , max(B.best_suf,B.sum+A.best_suf) , max(A.best_sum, ( max(B.best_sum,A.best_suf+B.best_pre) ) ) ,counter );
}
void be_smart()
{
	for(int i=0;i<S;i++)
		for(int j=i+1;j<S;j++)
			smart[i][j]=merge(smart[i][j-1],smart[j][j]);
}
node powmod(node A,int b)
{
	if(b==0)	return node(0,0,0,0);
	node ans=node();
	while(b){
		if(b&1){
			ans=merge(ans,A);
			b--;
		}
		else{
			A=merge(A,A);
			b>>=1;
		}
	}
	return ans;
}
node base_query(int s,int e)
{
	int x=(s%S)-1,y=(e%S)-1;
	if(x<0)	x+=S;
	if(y<0)	y+=S;
	if(e-s+1<=S){
		if(y>=x)	return smart[x][y];
		else	return merge(smart[x][S-1],smart[0][y]);
	}
	else{
		return merge(merge(smart[x][S-1],powmod(smart[0][S-1],(e-s-y+x-S)/S)),smart[0][y]);
	}
}
/************************smart calculations*********************/
/********************************MAIN Segment Tree********************************/
void core_update(int b,int e,int i,int j,int nod,int X)
{
	if(i>e || b>j)	return;
	if(b>=i && j>=e){
		//get the node value from the basic segment tree and update the time.
		node A=base_query(X,X+e-b);
		core[nod]=A;
		core[nod].t=counter;
		core[nod].s=X;
		core[nod].e=X+e-b;
		return;
	}
	int v=(nod<<1),mid;
	if(core[nod].t>core[v].t && core[nod].t>core[v+1].t ){		//Update the halves

		mid=core[nod].s+((core[nod].e-core[nod].s+1)>>1)-1;

		node A=base_query(core[nod].s,mid);
		core[v]=A;
		core[v].t=counter;
		core[v].s=core[nod].s;
		core[v].e=mid;

		A=base_query(mid+1,core[nod].e);
		core[v+1]=A;
		core[v+1].t=counter;
		core[v+1].s=mid+1;
		core[v+1].e=core[nod].e;

	}
	if(i<b)	mid= (X+ ((b+e)>>1)-b +1 );
	else if(i<= ((b+e)>>1))	mid = (X+ ((b+e)>>1) - i+1);
	else	mid=X;
	core_update(b,((b+e)>>1),i,j,v,X);
	core_update(((b+e)>>1)+1,e,i,j,v+1,mid);
	core[nod]=merge(core[(nod<<1)],core[(nod<<1)+1]);
}
node core_query(int b,int e,int i,int j,int nod)
{
	if(i>e || b>j)  return node();
	if(b>=i && j>=e){
		return core[nod];
	}
	int v=(nod<<1),mid;
	if(core[nod].t>core[v].t && core[nod].t>core[v+1].t ){          //Update the halves

		mid=core[nod].s+((core[nod].e-core[nod].s+1)>>1)-1;

		node A=base_query(core[nod].s,mid);
		core[v]=A;
		core[v].t=counter;
		core[v].s=core[nod].s;
		core[v].e=mid;

		A=base_query(mid+1,core[nod].e);
		core[v+1]=A;
		core[v+1].t=counter;
		core[v+1].s=mid+1;
		core[v+1].e=core[nod].e;

	}
	node A=core_query(b,((b+e)>>1),i,j,v);
	node B=core_query(((b+e)>>1)+1,e,i,j,v+1);
	return merge(A,B);
}
/********************************MAIN Segment Tree********************************/
void constant()
{
	power[0]=1;
	for(int i=1;i<=24;i++)	power[i]=power[i-1]<<1;	
}
int main()
{
	memset(core,0,sizeof(core));
	ll ans;
	constant();
	int x,y,X,v;
	char c;
	counter=100;
	scanf("%d%d%d",&S,&N,&Q);
	assert(S<=1000);
	assert(N<=100000);
	assert(Q<=100000);
	clev=obtain(N);
	for(int i=0;i<S;i++){
		scanf("%d",&v);
		smart[i][i]=node(v,v,v,v);
	}
	int use=(1000/S)*S;
	for(int i=S;i<use;i++)	smart[i][i]=smart[i-S][i-S];
	S=use;
	be_smart();
	for(;counter<Q+100;counter++){
		scanf(" %c",&c);
		assert(c=='U' || c=='Q');
		if(c=='U'){
			scanf("%d%d%d",&x,&y,&X);
			assert(x<=y);
			assert(y<=N);
			assert(x>=1 && X<=1000000000);
			X=X%S;
			if(X==0)	X=S;
			core_update(1,power[clev-1],x,y,1,X);
		}
		else{
			scanf("%d%d",&x,&y);
			assert(x<=y);
			assert(y<=N);
			assert(x>=1);
			//node an=core_query(1,power[clev-1],x,y,1);
			ans=core_query(1,power[clev-1],x,y,1).best_sum;
			printf("%lld\n",ans);
		}
	}
	return 0;
}
