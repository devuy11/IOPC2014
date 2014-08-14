#include<stdio.h>
#include<string.h>
#include<stdlib.h>
using namespace std;
typedef long long int ll;
const int mod = 1000000007;
int ncr[2000001],sweets,inv_ncr[2000001];
int input[1009][2002];
int use[1002],x,answer[2002],copy[2002],bine[2002];
long long int inverse(long long int a,long long int b)	 //b>a
{
	long long int Remainder,p0=(long long int)0,p1=(long long int)1,pcurr=(long long int)1,q,m=b;
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
void constant()
{	
	ncr[0]=inv_ncr[0]=1;
	for(int i=1;i<=2000000;i++){
		ncr[i]=((ll)ncr[i-1]*(ll)i)%mod;
		inv_ncr[i]=inverse(ncr[i],mod);
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
	for(int i=0;i<n;i++){
		scanf("%d",&x);
		if(x>0)
		use[x+1]++;
	}
	sweets=2000;
	memset(input,0,sizeof(input));
	for(int i=2;i<=101;i++){
		p=use[i];
		if(p>0)
			for(int j=0;j<=sweets;j+=i){
				s=j/i;
				input[i][j]= compute(p,s);
				if(s&1)
					input[i][j]=mod-input[i][j];

			}
	}
	memset(answer,0,sizeof(answer));
	answer[0]=1;
	for(int i=2;i<=101;i++){
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
	printf("%d\n",prt);
}
int main()
{
	int test;
	constant();
	scanf("%d",&test);
	while(test--)	solve();
	return 0;
}
