/*
Algo :: Segment Trees
Definitely to be Passed
Time WOrst Case :: 0.8 sec
*/
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
#include<vector>
#include<set>
#include<utility>
#include<bitset>
#include<map>
#include<assert.h>
using namespace std;
typedef long long int ll;
const int mod=1e9+7;
#define FOR(i,a,b)	for(int i=(a);i<=(b);i++)
struct node{
	ll Z[4];
	ll sum;
	int s,e;
}seg[1<<18],upd;
ll ans;
int N,Q,power[24],level;
ll D[3],X[3],store[3][(1<<18)+1];


void constant()
{
	power[0]=1;
	FOR(i,1,23)	power[i]=power[i-1]<<1;
	store[0][0]=store[1][0]=store[2][0]=0;
	FOR(i,1,(1<<18)){
		store[0][i]=(store[0][i-1]+i)%mod;
		store[1][i]=(store[1][i-1]+(ll)i*(ll)i)%mod;
		store[2][i]=(store[2][i-1]+(ll)i*(ll)i*(ll)i)%mod;
	}
}
void obtain(int x)
{
	level=0;
	int y=x;
	while(x!=0){
		level++;
		x>>=1;
	}
	if(power[level-1]!=y)	level++;
}
void cal()
{
	FOR(i,1,2){
		D[i]=D[i-1]*D[0];
		X[i]=(X[i-1]*X[0])%mod;
	}
	upd.Z[0]=(  -X[2]*D[2] + X[1]*D[1] - X[0]*D[0]  )%mod;
	upd.Z[1]=(  (ll)3*X[1]*D[2] - (ll)2*X[0]*D[1]  + D[0] )%mod;
	upd.Z[2]=(  D[1] - (ll)3*X[0]*D[2] ) %mod;
	upd.Z[3]= D[2];
	//printf("%lld %lld %lld %lld\n",upd.Z[0],upd.Z[1],upd.Z[2],upd.Z[3]);
	upd.sum=0;
	upd.s=upd.e=0;
}
ll ret(int s,int e)
{
	return (upd.Z[0]*(ll)(e-s+1) + upd.Z[1]*(store[0][e]-store[0][s-1]) + upd.Z[2] *( store[1][e]-store[1][s-1]) + upd.Z[3]*(store[2][e]-store[2][s-1]) )%mod;	
}
ll find(int s,int e,node x)
{
	//printf("%d is s and %d is e\n",s,e);
        ll val=(x.Z[0]*(ll)(e-s+1) + x.Z[1]*(store[0][e]-store[0][s-1]) + x.Z[2] *( store[1][e]-store[1][s-1]) + x.Z[3]*(store[2][e]-store[2][s-1]) )%mod;
	//printf("%d is s and %d is e\n",s,e);
	return val;
}
void update(int b,int e,int i,int j,int node)		// (1,power[level-1],i,j,node)
{
	if(e<i || b>j)	return ;
	if(b>=i && e<=j){
		//printf("%d %d\n",b,e);
		int z=node;
		seg[z].Z[0]=(seg[z].Z[0]+upd.Z[0])%mod;
		seg[z].Z[1]=(seg[z].Z[1]+upd.Z[1])%mod;
		seg[z].Z[2]=(seg[z].Z[2]+upd.Z[2])%mod;
		seg[z].Z[3]=(seg[z].Z[3]+upd.Z[3])%mod;
		seg[z].sum=(seg[z].sum+ ret(b,e))%mod;
		while(z!=1){
			//printf("%d is z\n",z);
			z>>=1;
			seg[z].sum=(find(seg[z].s,seg[z].e,seg[z])+seg[(z<<1)].sum+seg[(z<<1)+1].sum)%mod;	
			//printf("%d is z\n",z);
			//printf("%d %lld\n",z,seg[z].sum);
			//printf("%d %lld %lld %lld %lld %lld\n",z,seg[z].Z[0],seg[z].Z[1],seg[z].Z[2],seg[z].Z[3],seg[z].sum);
		}
		return ;
	}
	update(b,((b+e)>>1),i,j,(node<<1));
	update(((b+e)>>1)+1,e,i,j,(node<<1)+1);
}
/*ll find(int s,int e,node x)
{
	return (x.Z[0]*(ll)(e-s+1) + x.Z[1]*(store[0][e]-store[0][s-1]) + x.Z[2] *( store[1][e]-store[1][s-1]) + x.Z[3]*(store[2][e]-store[2][s-1]) )%mod;
}*/
void query(int b,int e,int i,int j,int node)
{
	if(e<i || b>j)	return ;
	if(b>=i && e<=j){
		ans= (ans+seg[node].sum)%mod;
		//printf("Loop0 %d %d %lld\n",b,e,ans);
		return;
	}
	if(e>j && b>i){
		ans= (ans+find(b,j,seg[node]) )%mod;	
		//printf("Loop1 %d %d %lld\n",b,e,ans);
	}
	else if(i>b && j>e){
		ans= (ans+find(i,e,seg[node]) )%mod;	
		//printf("Loop2 %d %d %lld\n",b,e,ans);
	}
	else{
		ans= (ans+find(i,j,seg[node]) )%mod;	
		//printf("Loop3 %d %d %lld\n",b,e,ans);
	}
	query(b,((b+e)>>1),i,j,(node<<1));
	query(((b+e)>>1)+1,e,i,j,(node<<1)+1);
}
void init(int b,int e,int node)
{
	if(b==e){
		seg[node].s=seg[node].e=b;
		return ;
	}
	init(b,((b+e)>>1),(node<<1));
	init(((b+e)>>1)+1,e,((node<<1)+1));
	seg[node].s=b;
	seg[node].e=e;
}
void solve()
{	
	int x,y,d;
	char c;
	scanf("%d",&N);
	assert(N<=100000);
	obtain(N);
	//memset(seg,0,sizeof(node)*power[level]);
	init(1,power[level-1],1);
	scanf("%d",&Q);
	assert(Q<=100000);
	while(Q--){
		scanf(" %c",&c);
		assert(c=='U' || c=='Q');
		if(c=='U'){
			scanf("%d%d%d",&x,&y,&d);
			assert(x<=N && y<=N && d<=100 && x>=1 && y>=1 && x<=y);
			D[0]=d;
			X[0]=x;
			cal();
			update(1,power[level-1],x,y,1);
		}
		else{
			scanf("%d%d",&x,&y);
			assert(x<=N && y<=N && x>=1 && y>=1 && x<=y);
			ans=0;
			query(1,power[level-1],x,y,1);
			if(ans<0)	ans+=mod;
			printf("%lld\n",ans);
		}
	}
}
int main()
{
	constant();
	solve();
	return 0;
}
