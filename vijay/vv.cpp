#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<math.h>
#include<queue>
#include<vector>
#include<stack>
#include<set>
using namespace std;

#define FOR(i,n)  for(i=0;i<n;i++)

#define pi(n)   printf("%d\n",n);

#define pl(n)	printf("%lld",n);

#define ps(c)   printf("%s\n",c);

#define si(n)   scanf("%d",&n);

#define sl(n)	scanf("%lld",&n);

#define ss(n)   scanf("%s",n);

#define sf(n)   scanf("%lf",&n);

#define sc(n)   scanf(" %c",&n);

#define inf 1000000007

#define pb(a)	push_back(a)

#define FORi(i,a,n) for(i=a;i<n;i++)

long long power(long long a,long long b)
{
	if(b==0)
		return 1;
	else if(b==1)
		return a;
	else
	{
		long long ans;
		ans=power(a,b/2);
		if(b%2==1)
		{
			return (ans*ans*a);
		}
		else
			return ans*ans;
	}
}
int main()
{
	long long *nu=new long long[1000010];
	long long n,nm,i,j=1,k,a,b,c,m,rem;
	cin>>n>>k;
	while((n!=0)||(k!=0))
	{
	//	ps("Hi")
		nm=0;
	//	pl(k)
		FOR(i,k)
		{
			sl(nu[i])
			if(nm<nu[i])
				nm=nu[i];
		}
		rem=n-nm;
		m=2;
		if(nm>1)
		{
			while(1)
			{
				a=power(m,rem);
				if(a>=nm)
					break;
				m++;
			}
		}
		else
			m=1;
		printf("Case #%lld: %lld\n",j,m);
		j++;
		cin>>n>>k;
	//	ps("Hello")
	}
	return 0;
}
