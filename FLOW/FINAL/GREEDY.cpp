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
typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
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
const int maxn=105;
ll n,j,c,x[maxn],s[maxn],e[maxn],p[maxn];
ll cost,ret;
int clean[105][105];

void initdist(int n)	{
	const int INF=800000000;
	for(int i=0;i<=n;i++)	for(int j=0;j<=n;j++)	clean[i][j]=INF;
	for(int i=0;i<=n;i++)	clean[i][i]=0;
}



class mycomp_start    {
        public:
                bool operator()(ll &a, ll &b)     {
			return s[a]>s[b];
                }
};

class mycomp_end    {
        public:
                bool operator()(ll &a, ll &b)     {
			return e[a]>e[b];
                }
};



void init()	{
	cost=0;
	ret=0;
}

void swap(ll j)	{
//	printf("%d %d %d %d\n",x[0],s[0],e[0],p[0]);
	ll xj=x[j];
	ll sj=s[j];
	ll ej=e[j];
	ll pj=p[j];
        x[j]=x[0];
	s[j]=s[0];
	e[j]=e[0];
	p[j]=p[0];
        x[0]=xj;
	s[0]=sj;
	e[0]=ej;
	p[0]=pj;
//	printf("%d %d %d %d\n",x[0],s[0],e[0],p[0]);
}

ll ans(ll x0)	{
	ll frooms=0,urooms=0;
	ll x00=x[0];
	x[0]=x0;
	std::priority_queue<ll, vector<ll>, mycomp_end> sched;
	std::priority_queue<ll, vector<ll>, mycomp_start> unsched;

	assert(sched.size()==0 && unsched.size()==0);
	for(ll i=0;i<n;i++)	unsched.push(i);
	while(!unsched.empty())	{
		ll utop=unsched.top();
		ll us=s[utop];
		
		while(sched.size() && ((e[sched.top()]+clean[sched.top()][utop])<=us))	{
			ll j=sched.top();
			sched.pop();
			frooms+=x[j];
			urooms-=x[j];
//			printf("removed %lld by %lld\n",j,utop);
//			printf("becoz utop=%lld s[utop]=%lld > %lld\n",utop,s[utop],e[j]);
		}

		ll up=x[utop];
		if(up<=frooms)	{
			frooms-=up;
			urooms+=up;
		}
		else	{
			urooms+=up;
			frooms=0;
		}
//		printf("added %lld\n",utop);
		unsched.pop();
		sched.push(utop);
	}
	x[0]=x00;
//	printf("ret=%lld p0=%lld frooms=%lld urooms=%lld\n",ret,p[0],frooms,urooms);
	return ret+(x0*p[0])-((frooms+urooms)*c);
}	

pl fun(ll low, ll high)	{
	if (low == high)
     return make_pair(low,ans(low));
	ll alow=ans(low),ahigh=ans(high);
 
	
   if ((high == low + 1) && alow > ahigh)
      return make_pair(low,alow);
 
   if ((high == low + 1) && alow <= ahigh)
      return make_pair(high,ahigh);
 
   ll mid = (low + high)/2;   /*low + (high - low)/2;*/
	ll amid=ans(mid);
 
   if ( amid > ans(mid+1) && amid > ans(mid-1))
      return make_pair(mid,amid);
 
   if (amid > ans(mid + 1) && amid < ans(mid - 1))
     return fun(low, mid-1);
   else // when arr[mid] is greater than arr[mid-1] and smaller than arr[mid+1]
     return fun(mid + 1, high);

}
/*
pl brute(ll low, ll high)	{
	ll prof=-1e16;
	ll n=-1;
	for(ll i=low;i<=high;i++)	{
		ll sol=ans(i);
		if(sol>prof)	{
			prof=sol;
			n=i;		
		}
	}
	return make_pair(n,prof);
}
*/

void readgraph(int n, int m, int v,int j)       {
        for(int i=0;i<m;i++)    {
                int p,q;
                scanf("%d %d",&p,&q);
		p--;
		q--;
                if(p==0)        p=j;
                else if(p==j)   p=0;
                if(q==0)        q=j;
                else if(q==j)   q=0;
                scanf("%d",&clean[p][q]);
                clean[p][q]*=v;
        }
        for(int k=0;k<n;k++)   {
                for(int i=0;i<n;i++)   {
                        for(int j=0;j<n;j++)   {
                                clean[i][j]=MIN(clean[i][j],(clean[i][k]+clean[k][j]));
                        }
                }
                //for(int i=1;i<=n;i++) for(int j=1;j<=n;j++)   printf("%d\n",clean[i][j]);
        }
}

int main(void)	{
	int test;
	scanf("%d",&test);
	for(int t=0;t<test;t++)	{
		int m,v;
		init();
		scanf("%lld %d %lld %lld %d",&n,&m,&j,&c,&v);
		j--;
		for(int i=0;i<n;i++)	scanf("%lld %lld %lld %lld",&x[i],&s[i],&e[i],&p[i]);
		swap(j);
		readgraph(n,m,v,j);
		for(int i=1;i<n;i++)	{
			ret+=x[i]*p[i];
		}
		pl sol=fun(0,x[0]);
		printf("%lld %lld\n",sol.first,sol.second);
	}
	return 0;
}
