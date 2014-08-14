/*
Algo :: Brute Force
Definitely TLE
Time WOrst Case :: 68 sec
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
using namespace std;
typedef long long int ll;
const int mod=1e9+7;
#define FOR(i,a,b)	for(int i=(a);i<=(b);i++)
ll array[100001];
ll ret(ll t,ll d)
{
	return ( t*d + t*t*d*d + ((t*t*t)%mod)*d*d*d )%mod;
}
void solve()
{	
	int x,y,d,N,Q;
	ll sum;
	char c;
	scanf("%d",&N);
	scanf("%d",&Q);
	while(Q--){
		scanf(" %c",&c);
		if(c=='U'){
			scanf("%d%d%d",&x,&y,&d);
			FOR(i,x,y){
				array[i]=(array[i]+ret(i-x,d))%mod;
			}
		}
		else{
			sum=0;
			scanf("%d%d",&x,&y);
			FOR(i,x,y)	sum+=array[i];
			printf("%lld\n",sum%mod);
		}
	}
}
int main()
{
	solve();
	return 0;
}
