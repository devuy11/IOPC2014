#include<stdio.h>
#include<string.h>
#include<algorithm>
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
}base[1<<19],core[1<<18],smart[1001][1001];
int S,N,Q,counter,blev,clev;	//S numbers and N size seg tree

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
/*********************************Base Segment Tree*******************************/
void base_init(int b,int e,int nod)
{
	if(b==e){
		if(b>2*N+1) base[nod]=node();
		return;
	}
	int v=nod<<1;
	base_init(b,((b+e)>>1),v);
	base_init(((b+e)>>1)+1,e,v+1);
	base[nod].sum=base[v].sum+base[v+1].sum;
	base[nod].best_pre=max(base[v].best_pre,base[v].sum+base[v+1].best_pre);
	base[nod].best_suf=max(base[v].best_suf+base[v+1].sum,base[v+1].best_suf);
	base[nod].best_sum=max(base[v].best_sum,max(base[v+1].best_sum,base[v].best_suf+base[v+1].best_pre));
}
node base_query(int b,int e,int i,int j,int nod)
{
	//printf("%d %d %d %d %d\n",b,e,i,j,nod);
	if(b>j || i>e)        return node();
	if(b>=i && j>=e)        return base[nod];
	int v=(nod<<1);
	node A = base_query(b,((b+e)>>1),i,j,v);
	node B = base_query(((b+e)>>1)+1,e,i,j,v+1);
	if(A==node())	return B;
	if(B==node())	return A;
	return node (  A.sum+B.sum , max(A.best_pre,A.sum+B.best_pre) , max(B.best_suf,B.sum+A.best_suf) , max(A.best_sum, max(B.best_sum,A.best_suf+B.best_pre) )   );
}
/*********************************BASIC Segment Tree*******************************/

void print(int p,int s)
{
	int cmp=0;
	for(int i=1;i<s;i++){
		if(power[cmp]==i){
			printf("\n");
			cmp++;
		}
		if(p==0)
			printf("(%lld,%lld,%lld,%lld) ",base[i].sum,base[i].best_pre,base[i].best_suf,base[i].best_sum);
		else
			printf("(%lld,%lld,%lld,%lld,%d,%d) ",core[i].sum,core[i].best_pre,core[i].best_suf,core[i].best_sum,core[i].s,core[i].e);
	}
	printf("\n");
}
/********************************MAIN Segment Tree********************************/
node merge(node A,node B)
{
	if(A==node())	return B;
	if(B==node())	return A;
	return node (  A.sum+B.sum , max(A.best_pre,A.sum+B.best_pre) , max(B.best_suf,B.sum+A.best_suf) , max(A.best_sum, ( max(B.best_sum,A.best_suf+B.best_pre) ) ) ,counter );
}
void core_update(int b,int e,int i,int j,int nod,int X)
{
	if(i>e || b>j)	return;
	if(b>=i && j>=e){
		//get the node value from the basic segment tree and update the time.
		node A=base_query(1,power[blev-1],X,X+e-b,1);
		core[nod]=A;
		core[nod].t=counter;
		core[nod].s=X;
		core[nod].e=X+e-b;
		//Going Upwards
		return;
	}
	int v=(nod<<1),mid;
	if(core[nod].t>core[v].t && core[nod].t>core[v+1].t ){		//Update the halves

		mid=core[nod].s+((core[nod].e-core[nod].s+1)>>1)-1;

		node A=base_query(1,power[blev-1],core[nod].s,mid,1);
		core[v]=A;
		core[v].t=counter;
		core[v].s=core[nod].s;
		core[v].e=mid;

		A=base_query(1,power[blev-1],mid+1,core[nod].e,1);
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

		node A=base_query(1,power[blev-1],core[nod].s,mid,1);
		core[v]=A;
		core[v].t=counter;
		core[v].s=core[nod].s;
		core[v].e=mid;

		A=base_query(1,power[blev-1],mid+1,core[nod].e,1);
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
	clev=obtain(N);
	blev=obtain(2*N+1);
	for(int i=0;i<S;i++){
		scanf("%d",&v);
		base[power[blev-1]+i]=node(v,v,v,v);
	}
	for(int i=S;i<=2*N;i++){
		base[power[blev-1]+i]=base[power[blev-1]+i-S];
	}
	base_init(1,power[blev-1],1);
	for(;counter<Q+100;counter++){
		scanf(" %c",&c);
		if(c=='U'){
			scanf("%d%d%d",&x,&y,&X);
			X=X%S;
			if(X==0)	X=S;
			core_update(1,power[clev-1],x,y,1,X);
		}
		else{
			scanf("%d%d",&x,&y);
			//node an=core_query(1,power[clev-1],x,y,1);
			ans=core_query(1,power[clev-1],x,y,1).best_sum;
			printf("%lld\n",ans);
		}
	}
	return 0;
}
