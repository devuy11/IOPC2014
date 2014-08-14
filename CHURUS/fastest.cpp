#include<stdio.h>
#include<string.h>
#include<stdlib.h>
using namespace std;
typedef long long int ll;
const int mod = 1000000007;
int ncr[1002002],sweets,inv_ncr[1002002];
int input[1002][2002];
int use[1002],x,answer[2002],copy[2002],bine[2002];
void constant()
{	
	memset(inv_ncr,0,sizeof(inv_ncr));
	ncr[0]=inv_ncr[0]=1;
	inv_ncr[0] = inv_ncr[1] = 1;
	for(int i = 2; i <= 1002000; i++)
    		inv_ncr[i] = (-(ll)(mod/i) * (ll)inv_ncr[mod % i]) % mod + mod;

	for(int i=1;i<=1002000;i++){
		ncr[i]=((ll)ncr[i-1]*(ll)i)%mod;
		inv_ncr[i]=((ll)inv_ncr[i]*(ll)inv_ncr[i-1])%mod;
	}
}
int compute(int n,int r)
{
	if(n<r)	return 0;
	if(r==0 || n==r)	return 1;
	return ( (ll) ( ((ll)ncr[n]*(ll)inv_ncr[r])%mod ) * (ll)inv_ncr[n-r] )%mod;
}
void multiply(int mul)
{
	for(int i=0;i<=sweets;i++)	copy[i]=answer[i];
	memset(answer,0,sizeof(answer));
	for(int i=0;i<=sweets;i+=mul){		//copy
		for(int j=0;j<=sweets-i;j++){	//input[mul]
			answer[i+j]=((ll)answer[i+j]+(ll)copy[j]*(ll)input[mul][i])%mod;
		}
	}
}
void print(int Array[])
{
	for(int i=0;i<20;i++)	printf("%d ",Array[i]);
	printf("\n");
}
void solve()
{
	int p,s,prt=0,req,n,Q;
	scanf("%d",&n);
	memset(use,0,sizeof(use));
	x=1;
	for(int i=0;i<n;i++){
		scanf("%d",&x);
		if(x>0)
		use[x+1]++;
	}
	sweets=2000;
	memset(answer,0,sizeof(answer));
	answer[0]=1;
	for(int i=2;i<=1001;i++){
		p=use[i];
		if(p>0)
			for(int j=0;j<=sweets;j+=i){
				s=j/i;
				input[i][j]= compute(p,s);
				if(s&1)
					input[i][j]=mod-input[i][j];

			}
	}
	for(int i=2;i<=1001;i++){
		if(use[i]){
			multiply(i);
		}
	}
	for(int i=0;i<2001;i++)	
		bine[i]=compute(n+i-1,i);
	memset(copy,0,sizeof(copy));
	for(int i=0;i<=2000;i++){
		for(int j=0;j<=2000-i;j++){
			copy[i+j]=((ll)copy[i+j]+(ll)answer[i]*(ll)bine[j])%mod;
		}
	}
	scanf("%d",&Q);
	while(Q--){
		scanf("%d",&x);
		printf("%d\n",copy[x]);
	}
}
int main()
{
	int test;
	constant();
	//return 0;
	test=1;
	while(test--)	solve();
	return 0;
}
