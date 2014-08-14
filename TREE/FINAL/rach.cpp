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
typedef vector<ll> vi;
typedef pair<ll, ll> pi;
typedef vector<ll> prime_vi;
typedef pair<ll,ll> mod_vi;
typedef pair<prime_vi,mod_vi> crt_arg;
typedef vector<crt_arg> crt_arg_vi;

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
const int maxn=100005;
ull sieve_par=maxn;
ull primes[maxn] , array[maxn],counter,prime_factorization[20];

void sieve()
{
	for(int i=1;i<sieve_par;i++)
		array[i]=1;
	array[0]=0;
	ull j;
	for(ull i=2;i<=sieve_par;i++)
	{
		if(array[i-1]==1)
		{
			primes[counter]=i;
			for(j=i*i;j<=sieve_par;j+=i)
				array[j-1]=0;
			counter++;
		}
	}
}

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

ll CRT(vi mod, vi rem)			//t is the number of pairs of rem and mod
{
	int t=mod.size();
    ll ans = rem[0],m = mod[0];
//	printf("CRT: size=%d\n",t);
//	for(int i=0;i<t;i++)	{
//		printf("rem=%lld mof=%lld\n",rem[i],mod[i]);
//	}
    for(int i = 1;i < t;++i)
	{
        ll a = inverse(m,mod[i]);
        ll b = inverse(mod[i],m);
        ans = (ans * b * mod[i] + rem[i] * a * m) % (m * mod[i]);
        m *= mod[i];
    }   
    return ans;
}

int pow_without_mod(int a, int b)	{
	int ans=1;
	for(int i=0;i<b;i++)	ans=ans*a;
	return ans;
}

ll powmod(ll a, ll pwr, ll mod)	{
	if(pwr==0)	return 1;
	ll ans=powmod(a,pwr>>1,mod);
	ans=(ans*ans)%mod;
	if(pwr&1)	ans=(ans*a)%mod;
	return ans;
}

int check(int t, vi tower, int pwr)	{		//return -1 if t*(\\tower\\) >=pwr

	if(t*tower[0]>=pwr)	return -1;

	for(int i=tower.size()-2;i>=0;i--)	{
		ll a=tower[i];
		ll n=tower[i+1];

		ll x=1;
		for(int j=0;j<n;j++)	{
			x=x*a;
			if(x>=pwr)	return -1;
		}		
		tower[i]=x;
	}
	if(t*tower[0]>=pwr)	return -1;
	return t*tower[0];
} 


ll cal(vi tower, ll mod)	{

	if(mod==1)	return 0;
	if(tower.size()==1)	return tower[0]%mod;
	if(!(tower[0]%mod))	return 0;

	int fac_count[counter+10],fac_count_count=0;
	int fac_last=-1;
	memset(fac_count,0,sizeof(fac_count));
	ll mod_bkp=mod;
	for(int i=0;i<counter && mod>1;i++)	{
		if(!(mod%primes[i]))	{
			fac_count_count++;
			fac_last=i;		//last factor is primes[i]
		}
		while(!(mod%primes[i]))	{
			fac_count[i]++;
			mod/=primes[i];
		}

	}
	mod=mod_bkp;

	//printf("mod=%lld fac_c_c=%d\n",mod,fac_count_count);

	if(fac_count_count==1)	{
		int prm=primes[fac_last];
		int pwr=fac_count[fac_last];
		int newmod=prm-1;

		if(!(tower[0]%prm))	{		//tower 0 is div by prime
			ll k=tower[0];
			int t=0;
			while(!(k%prm))	{
				k=k/prm;
				t++;
			}
			
			vi newtower;
			newtower.pb(k);
			//for(int i=1;i<tower.size();i++)	newtower.pb(tower[i]);
			for(vi::iterator it=tower.begin()+1;it!=tower.end();it++)	newtower.pb(*it);
			ll v1=cal(newtower,mod);
			
			newtower.erase(newtower.begin());
			//newtower.clear();
			//for(int i=1;i<tower.size();i++) newtower.pb(tower[i]);
			ll v2=check(t,newtower,pwr);		//check if t*(\\newtower\\) >= pwr if it is, it is 0, else, actual value
			if(v2!=-1)	{
				v2=pow_without_mod(prm,v2);
			}
			else	v2=0;
			return (v1*v2)%mod;

		}
		else	{
			if(pwr>1)	newmod=mod-(mod/prm);
			vi newtower;
			for(vi::iterator it=tower.begin()+1;it!=tower.end();it++)       newtower.pb(*it);
			//for(int i=1;i<tower.size();i++)	newtower.pb(tower[i]);
			ll newpow=cal(newtower,newmod);
			return powmod(tower[0],newpow,mod);

		}
	}
	else	{
		int crt_param=0;
		vi crt_mod,crt_rem;
		for(int i=0;i<counter;i++)	{
			if(fac_count[i])	{
				int new_pwr=pow_without_mod(primes[i],fac_count[i]);
				//printf("new prw=%d\n",new_pwr);
				ll new_ans=cal(tower,new_pwr);
				crt_rem.pb(new_ans);
				crt_mod.pb(new_pwr);
					
			}
		}
		return CRT(crt_mod,crt_rem);
	}
}


int n,m,q,a,b,parent[maxn],st[maxn],finish[maxn],tt,val[maxn];
bool tvis[maxn];
vector<int> tv[maxn];

void dfs(int node, int pa)	{
	if(tvis[node])	return;
	st[node]=tt++;
	parent[node]=pa;
	tvis[node]=true;
	for(int i=0;i<tv[node].size();i++)	dfs(tv[node][i],node);
	finish[node]=tt++;
}

void readt()	{
	scanf("%d %d",&n,&q);
	for(int i=1;i<n;i++)	{
		scanf("%d %d",&a,&b);
		tv[a].pb(b);
		tv[b].pb(a);
	}
	for(int i=1;i<=n;i++)	scanf("%d",&val[i]);
	dfs(1,0);
}

vi caltower(int a, int b)	{

	vi towa,towb;

	while(!(st[a]<=st[b] && finish[a]>=finish[b]))	{
		towa.pb(val[a]);
		a=parent[a];
		if(towa.size()>20) return towa;
	}
	towa.pb(val[a]);

	while(a!=b)	{
		int i;
		for(i=0;i<tv[a].size();i++)	{
			int v=tv[a][i];
			if((st[v]<=st[b]) && (finish[v]>=finish[b]) && (v!=parent[a]))	break;	
		}
		a=tv[a][i];
		towa.pb(val[a]);
		if(a==b)	return towa;
		if(towa.size()>20)	return towa;
	}

	return towa;

}

int main(void)	{
	sieve();
	readt();

	for(int Q=0;Q<q;Q++)	{
		char c;
		int a,b;
		scanf(" %c %d %d",&c,&a,&b);
//		printf("%c %d %d\n",c,a,b);	
		if(c=='U')	val[a]=b;
		else	{
			int mod;
			scanf("%d",&mod);
			vi tow=caltower(a,b);
			//for(int i=0;i<tow.size();i++)	printf("-%lld ",tow[i]);
			//printf("\n");
			printf("%lld\n",cal(caltower(a,b),mod));

		}

	}

/*	int arr[maxn];
	int n,test;
	scanf("%d",&n);
	for(int i=0;i<n;i++)	{
		scanf("%d",&arr[i]);
	}
	scanf("%d",&test);
	for(int t=0;t<test;t++)	{
		int x,y,mod;
		vi tower;
		int cnt=0;
		scanf("%d %d %d",&x,&y,&mod);
		for(int i=x-1;i<y-1 && cnt<30;i++)	{
			tower.pb(arr[i]);
			cnt++;
		}
		printf("%lld\n",cal(tower,mod));
	}
*/	
	return 0;
}
