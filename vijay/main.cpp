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
typedef pair<int, int> pii;

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


bool tpowgeq(ll base, int pwr, ll what)	{
	assert(pwr>0);
	ll ans=1;
	for(int i=0;i<pwr;i++)	{
		if(ans>=what)	return true;
		ans*=base;
	}
	return ans>=what;
}

int main(void)	{
	int test=1;
	while(1)	{
		int n,k;
		scanf("%d %d",&n,&k);
		if(n==0 && k==0)	break;
		assert(k>=2 && k<=1000000);
                assert(n>1 && n<=1000000000);
		printf("Case #%d: ",test++);
		assert(k>1);
		assert(n>1);
		if(k==2)	{
			int a,b;
			scanf("%d %d",&a,&b);
			assert(a>0 && b>0);
			assert((a+b)==n);
			int mmin=MIN(a,b),mmax=MAX(a,b);
			if(mmin==1)	{
				printf("%d\n",mmax);
			}
			else	{
				int ans=(int)ceil(pow((long double)mmax,1.0/(long double)mmin));
//				assert(powgeq(ans,mmin,mmax));
//				assert(!powgeq(ans-1,mmin,mmax));
				printf("%d\n",MIN(ans,4));	
			}
		}
		else	{
			int mmax=-1,sum=0,a;
			for(int i=0;i<k;i++)	{
				scanf("%d",&a);
				sum+=a;
				mmax=MAX(mmax,a);
			}
			assert(sum==n);
			int s=sum-mmax;
			int t=mmax;
			if(t==1)	printf("1\n");
			else	if(t>=2 && s>t)	printf("2\n");
			else	{
				int ans=(int)ceil(pow((double)t,1.0/(double)s));
//				assert(powgeq(ans,s,t));
//				assert(!powgeq(ans-1,s,t));
				printf("%d\n",MIN(3,ans));
			}
		}
	}
	assert(test<=101);

	return 0;
}
