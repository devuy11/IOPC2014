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

long long int power(long long int a,long long int b)
{
    if(b==0)
        return 1;
    if(b==1)
        return a;
    long long int temp=power(a,b/2);
    if(temp > 1000000 || temp==-1)
        return -1;
    if(b%2==0)
        return temp*temp;
    else
        return temp*temp*a;
}

long long int extra;

long long int divpower(long long int a,long long int b,long long int l,long long int r)
{
    if(l>r)
        return -1;
    long long int mid=(l+r)/2;
    long long int temp=power(mid,b);
    if(temp == a)
        return mid;
    if(temp<0 || temp>a)
    {
        extra=mid;
        return divpower(a,b,l,mid-1);
    }
    else if(temp<a && temp>=0)
    {
//        extra = mid;
        return divpower(a,b,mid+1,r);
    }
}


int main(void)	{

    long long int n,k,i,j,t,s,a[100005],test=1;
    scanf("%lld %lld",&n,&k);
    while(n!=0 || k!=0)
    {
        for(i=0;i<k;i++)
            scanf("%lld",&a[i]);
        
        printf("Case #%lld: ",test);
        test++;
        if(k==2 && a[0]==1)
        {
            printf("%lld\n",a[1]);
            //return 0;
        }
        else if(k==2 && a[1]==1)
        {
            printf("%lld\n",a[0]);
            //return 0;
        }
        else if(k==2)
        {
            long long int max=MAX(a[0],a[1]);
            long long int min=MIN(a[0],a[1]);
            extra=0;
            j=divpower(max,min,1,max+1);
            if(j==-1)
                j=extra;
            if(j>4)
                j=4;
            printf("%lld\n",j);
            //return 0;
        }
        else if(k>=3)
        {
            t=0;
            for(i=0;i<k;i++)
            {
                if(t<=a[i])
                    t=a[i];
                s=s+a[i];
            }
            s=s-t;
            if(t==1)
                printf("1\n");
            else if(t>=2 && s>t)
                printf("2\n");
            else if(s<=t)
            {
                extra=0;
                int temp=divpower(t,s,1,t+1);
                if(temp==-1)
                    temp=extra;
                if(temp>3)
                    temp=3;
                printf("%d\n",temp);
            }
            //return 0;
            
        }
        scanf("%lld %lld",&n,&k); 
    }
    
    return 0;
}

