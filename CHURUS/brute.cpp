#include<stdio.h>
#include<string.h>
#include<stdlib.h>
using namespace std;
typedef long long int ll;
const int mod = 1000000007;
ll answer[2002],copy[2002];
int use[1002];
void multiply(int deg)
{
	copy[0]=answer[0];
	for(int i=1;i<2001;i++)	copy[i]=(copy[i-1]+answer[i])%mod;
	for(int i=1;i<2001;i++)	
		if(i>deg)	answer[i]=(copy[i]-copy[i-deg-1]+mod)%mod;
		else	answer[i]=copy[i];
}
void print()
{
	for(int i=0;i<=20;i++)	printf("%lld ",answer[i]);
	printf("\n");
}
void solve()
{
	int p,s,prt=0,req,n,Q,x;
	scanf("%d",&n);
	answer[0]=1;
	for(int i=0;i<n;i++){
		scanf("%d",&x);
		multiply(x);
	}
	scanf("%d",&Q);
	while(Q--){
		scanf("%d",&x);
		printf("%lld\n",answer[x]);
	}
}
int main()
{
	int test;
	test=1;
	while(test--)	solve();
	return 0;
}
