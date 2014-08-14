/*

                       o                            | |    
_|_       __,   _  _       __   ,_    __,   __, _|_ | |    
 |  |  |_/  |  / |/ |  |  /    /  |  /  |  /  |  |  |/ \
 |_/ \/  \_/|_/  |  |_/|_/\___/   |_/\_/|_/\_/|_/|_/|   |_/

*/

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
#include<cassert>

using namespace std;

typedef long long int ll;
typedef unsigned long long int ull;
typedef vector<int> vi;
typedef pair<int, ll> pi;

#define mfor(i,e)	for(int i = 0; i < e; i++)
#define mford(i,s,e)	for(int i = s; i > e; i--)
//#define FORE(i,s,e)	for(typeof(s) i = s; i != e; ++i)
#define mfori(i,s,e)	for(int i = s; i < e; i++)
#define in(x)		(x = getc(stdin))
#define MP			make_pair
#define out(x)		putc(x, stdout)
#define pb			push_back

template <class _T> _T MAX(_T a, _T b){ return a > b ? a : b; }
template <class _T> _T MIN(_T a, _T b){ return a < b ? a : b; }
template <class _T> _T GCD(_T a, _T b){ return b ? GCD(b, a % b) : a; }

#define SET(p) memset(p, -1, sizeof(p))
#define CLR(p) memset(p, 0, sizeof(p))
#define i64 long long

const int INF = 0x7fffffff;
const int MAXN = 205, MAXE = 60000;

int src, snk, nNode, nEdge;
int Q[MAXN], fin[MAXN], pro[MAXN], dist[MAXN];
int flow[MAXE], cap[MAXE], next[MAXE], to[MAXE];
ll s[MAXN],e[MAXN],x[MAXN],p[MAXN],backup;
int clean[105][105];
ll pixi,c;


inline void init(ll _src, ll _snk, ll _n) {
    src = _src, snk = _snk, nNode = _n, nEdge = 0;
    SET(fin);
}

inline void add(ll u, ll v, ll c) {
    to[nEdge] = v, cap[nEdge] = c, flow[nEdge] = 0, next[nEdge] = fin[u], fin[u] = nEdge++;
    to[nEdge] = u, cap[nEdge] = 0, flow[nEdge] = 0, next[nEdge] = fin[v], fin[v] = nEdge++;
}

void initdist(int n)	{
	const int INF=1000000000;
	for(int i=1;i<=n;i++)	{
		for(int j=1;j<=n;j++)	{
			clean[i][j]=INF;
		}
	}
	for(int i=1;i<=n;i++)	clean[i][i]=0;
}

void initflow()	{
	for(int i=0;i<nEdge;i++)	flow[i]=0;
}

bool bfs() {
    int st, en, i, u, v;
    SET(dist);
    dist[src] = st = en = 0;
    Q[en++] = src;
    while(st < en) {
        u = Q[st++];
        for(i=fin[u]; i>=0; i=next[i]) {
            v = to[i];
            if(flow[i] < cap[i] && dist[v]==-1) {
                dist[v] = dist[u]+1;
                Q[en++] = v;
            }
        }
    }
    return dist[snk]!=-1;
}

int dfs(int u, int fl) {
    if(u==snk) return fl;
    for(int &e=pro[u], v, df; e>=0; e=next[e]) {
        v = to[e];
        if(flow[e] < cap[e] && dist[v]==dist[u]+1) {
            df = dfs(v, min(cap[e]-flow[e], fl));
            if(df>0) {
                flow[e] += df;
                flow[e^1] -= df;
                return df;
            }
        }
    }
    return 0;
}

ll dinitz() {
    ll ret = 0;
    int df;
    while(bfs()) {
        for(int i=1; i<=nNode; i++) pro[i] = fin[i];
        while(true) {
            df = dfs(src, INF);
            if(df) ret += (i64)df;
            else break;
        }
    }
    return ret;
}


bool jafteri(int i, int j)	{
	if((e[i]+clean[i][j])<=s[j])	return true;
	return false;
}

int bsearchc(int C, int low, int high, int without)	{
	 backup=-100000;	
	while(high>=low)	{
//		printf("C1=%d C2=%d high=%d low=%d without=%d\n",C1,C2,high,low,without);
		int mid=(low+high)/2;
		cap[C]=mid;
		initflow();
		int Amid=dinitz();
//		printf("amif=%d\n",Amid);		
		if(low==high)	{
			if(Amid==without)	return low;
			else	return backup;
		}
		if(Amid<without)	{
			low=mid+1;
		}
		else if(Amid>without)	{
			assert(0);
		}
		else if(Amid==without)	{
			backup=mid;
			high=mid-1;
		}
	}
	
	//high<low	
	if(backup>-1)	return backup;
	assert(0);	
}

ll ans(ll xj, int Cx1, int Cx2, int sigma, int C)	{
	//cx1, cx2 are 2 diff edges
//-------------------------------------------
	cap[Cx1]=xj;
	cap[Cx2]=xj;
	cap[C]=INF;
	initflow();
	int without=dinitz();

	int C_opt=bsearchc(C,0,sigma,without);

	//now calculate prof
	ll prof=pixi;
	prof+=((ll)xj*(ll)p[1]);
	prof-=((ll)C_opt*(ll)c);
	return prof;
}


pi bsearchx(int C, int sigma, int low, int high, int Cx1, int Cx2)	{
	        if (low == high)	return make_pair(low,ans(low,Cx1,Cx2,sigma,C));
	
        ll alow=ans(low,Cx1,Cx2,sigma,C),ahigh=ans(high,Cx1,Cx2,sigma,C);


   if ((high == low + 1) && alow > ahigh)	return make_pair(low,alow);

   if ((high == low + 1) && alow <= ahigh)	return make_pair(high,ahigh);

   int mid = (low + high)/2;   /*low + (high - low)/2;*/
        ll amid=ans(mid,Cx1,Cx2,sigma,C);

   if ( amid > ans(mid+1,Cx1,Cx2,sigma,C) && amid > ans(mid-1,Cx1,Cx2,sigma,C))	   return make_pair(mid,amid);

   if (amid > ans(mid + 1,Cx1,Cx2,sigma,C) && amid < ans(mid - 1,Cx1,Cx2,sigma,C))	   return bsearchx(C,sigma,low, mid-1,Cx1,Cx2);
   else // when arr[mid] is greater than arr[mid-1] and smaller than arr[mid+1]
     return bsearchx(C,sigma,mid+1, high,Cx1,Cx2);
}

void swap(int a, int b)	{
	ll ax=x[a],as=s[a],ae=e[a],ap=p[a];
	x[a]=x[b],s[a]=s[b],e[a]=e[b],p[a]=p[b];
	x[b]=ax,s[b]=as,e[b]=ae,p[b]=ap;
}

void readgraph(int n, int m, int v,int j)	{
	for(int i=0;i<m;i++)	{
		int p,q;
		scanf("%d %d",&p,&q);
		if(p==1)	p=j;
		else if(p==j)	p=1;
		if(q==1)	q=j;
		else if(q==j)	q=1;
		scanf("%d",&clean[p][q]);
		clean[p][q]*=v;
	}
	
	for(int k=1;k<=n;k++)	{
		for(int i=1;i<=n;i++)	{
			for(int j=1;j<=n;j++)	{
				clean[i][j]=MIN(clean[i][j],(clean[i][k]+clean[k][j]));
			}
		}
		//for(int i=1;i<=n;i++)	for(int j=1;j<=n;j++)	printf("%d\n",clean[i][j]);
	}
}

void solve() {
	int n,j,m,v,sigma=0;
	scanf("%d %d %d %lld %d",&n,&m,&j,&c,&v);

	initdist(n);
	
	int s1=n+n+1,t1=n+n+2,s2=n+n+3,t2=n+n+4; 
	const int INF=1000000000;
	init(s1,t2,n+n+4);

	pixi=0;

	for(int k=1;k<=n;k++)   {
                scanf("%lld %lld %lld %lld",&x[k],&s[k],&e[k],&p[k]);
	}
	swap(1,j);

	readgraph(n,m,v,j);


//	scanf("%d %d %d %d",&x[1],&s[1],&e[1],&p[1]);
	for(int k=2;k<=n;k++)	{
		add(s1,k,x[k]);
		add(n+k,t2,x[k]);
		add(k,t1,INF);
		add(s2,n+k,INF);
		sigma+=x[k];
		pixi+=((ll)x[k]*(ll)p[k]);
	}
	for(int i=2;i<=n;i++)	{
		for(int j=2;j<=n;j++)	{
			if(jafteri(i,j))	add(i,n+j,INF);
		}
	}

	//now C1,C2=c1_back
	int C=nEdge;
	add(t1,s2,sigma);
	ll without=dinitz();
	ll C_opt = bsearchc(C,0,sigma,without);
	//printf("without=%d\n",without);

	if(p[1]>=c)	{
		//use all rooms
		add(s1,1,x[1]);
		add(n+1,t2,x[1]);
		add(1,t1,INF);
		add(s2,n+1,INF);
		sigma+=x[1];
		for(int j=2;j<=n;j++)	if(jafteri(1,j))	add(1,n+j,INF);
		for(int i=2;i<=n;i++)	if(jafteri(i,1))	add(i,n+1,INF);

                cap[C]=sigma;
                initflow();
                without=dinitz();

	//	for(int i=0;i<nEdge;i+=2)	{
	//		printf("%d: %d->%d cap=%d flow=%d\n",i,to[i+1],to[i],cap[i],flow[i]);
	//		 printf("%d: %d->%d cap=%d flow=%d\n",i,to[i],to[i+1],cap[i+1],flow[i+1]);
	//	}
	//	printf("wit=%d\n",without);
		C_opt=bsearchc(C,0,sigma,without);
		ll prof=pixi;
		prof+=(x[1]*p[1]);
		prof-=(C_opt*c);
		printf("%lld %lld\n",x[1],prof);

	}
	else	{
		int Cx1=nEdge;
		add(s1,1,0);
		int Cx2=nEdge;
		add(n+1,t2,0);
		add(1,t1,INF);
		add(s2,n+1,INF);
		for(int j=2;j<=n;j++)   if(jafteri(1,j))        add(1,n+j,INF);
                for(int i=2;i<=n;i++)   if(jafteri(i,1))        add(i,n+1,INF);

		sigma+=x[1];
		//:(
		pi fxj;
		fxj=bsearchx(C,sigma,0,x[1],Cx1,Cx2);

		printf("%d %lld\n",fxj.first,fxj.second);

	}


}

int main()	{
	int test;
	scanf("%d",&test);
	for(int t=0;t<test;t++)	{
		solve();

	}
}

