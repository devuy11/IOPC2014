#include<stdio.h>
#include<string.h>
#define Max_M 1000
#define Level 50
typedef long long int ll;
inline int max(int a,int b)
{
	if(a>b)	return a;
	else	return b;
}
int input[Level],testing;
int sieve_par=319;
int prime[320] , array[320],counter=0;
struct A
{
	int x,p;
	A(int a=0,int b=0){
		x=a;p=b;
	}
}factor[6][100001];
int DP[Level][100001];
int used[Level][100001];
int size[100001];
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
ll binpow(ll a,ll b,ll mod)
{
	ll ans=1;
	while(b)
		if(b&1){
			ans=(ans*a)%mod;
			b--;

		}
		else{	
			a=(a*a)%mod;
			b>>=1;
		}
	return ans%mod;
}
ll CRT(ll mod[],ll rem[],int t)			//t is the number of pairs of rem and mod
{
    ll ans = rem[0],m = mod[0];
  
    for(int i = 1;i < t;++i)
	{
        ll a = inverse(m,mod[i]);
        ll b = inverse(mod[i],m);
        ans = (ans * b * mod[i] + rem[i] * a * m) % (m * mod[i]);
        m *= mod[i];
    }   
    return ans;
}
void sieve()
{
	for(int i=1;i<sieve_par;i++)
		array[i]=1;
	array[0]=0;
	int j;
	for(int i=2;i<=sieve_par;i++)
	{
		if(array[i-1]==1)
		{
			prime[counter]=i;
			for(j=i*i;j<=sieve_par;j+=i)
				array[j-1]=0;
			counter++;
		}
	}
}
void constant()
{
	memset(used,0,sizeof(used));
	int remaining[100001],x,y;
	for(int i=0;i<100001;i++)	remaining[i]=i,size[i]=0;
	for(int i=0;i<counter;i++){
		for(int j=prime[i];j<100001;j=j+prime[i]){
			x=1;
			while(remaining[j]%prime[i]==0){
				remaining[j]/=prime[i];
				x=x*prime[i];
			}
			factor[size[j]][j]=A(x,prime[i]);
			size[j]++;
		}
	}
	for(int i=0;i<100001;i++){
		if(remaining[i]!=1){
			factor[size[i]][i]=A(remaining[i],remaining[i]);
			size[i]++;
		}
	}
}
int check(ll a,ll b,ll n)
{
	ll ans=1;
	while(b)
		if(b&1){
			ans=ans*a;
			if(ans>n)	return -1;
			b--;
		}
		else{
			a=a*a;
			if(a>n)		return -1;
			b>>=1;	
		}
	return ans;
}
int set_tol(int x,int M)
{
	int ans=1,over;
	for(;x>=0;x--){
		over=check(input[x],ans,2*M);
		if(over<0)	break;
		ans=over;
	}
	x++;
	input[x]=ans;
	return x;
}
int fun(int st,int end,int mod)
{
	if(st==end)	return input[st]%mod;
	if(input[st]%mod==0)	return 0;
	if(used[Level][mod]==testing){
		return DP[Level][mod];
	}
	int s=size[mod];
	ll modi[6],rem[6];
	for(int i=0;i<s;i++){
		modi[i]=factor[i][mod].x;
		if(input[st]%factor[i][mod].p==0)	rem[i]=0;
		else	rem[i]=binpow(input[st],fun(st+1,end,factor[i][mod].x-factor[i][mod].x/factor[i][mod].p),factor[i][mod].x);
	}
	int ans=CRT(modi,rem,s);
	used[st][mod]=testing;
	DP[st][mod]=ans;
	return ans;
}
void find_max_level()
{
	int tp[100001],s,maxi=-1;
	tp[1]=1;
	int ans,a,b,g;
	for(int i=2;i<=100000;i++){
		ans=-1;
		s=size[i];
		for(int j=0;j<s;j++){
			g=0;
			a=factor[j][i].x;
			b=factor[j][i].p;
			while(a%b==0){
				g++;
				a/=b;
			}
			ans=max(ans,g+tp[b-1]);
		}
		tp[i]=ans;
		maxi=max(ans,maxi);
	}
	//printf("%d is maxi\n",maxi);	
	for(int i=0;i<=100000;i++)	if(tp[i]>=15)	printf("%d ",i);
	printf("\n");
}
int main()
{
	testing=100;
	sieve();
	constant();
	find_max_level();
	int test,x,m;
	scanf("%d",&test);
	while(test--){
		testing++;
		scanf("%d%d",&x,&m);
		for(int i=0;i<x;i++)	scanf("%d",&input[i]);
		x=set_tol(x-1,m);
		printf("%d\n",fun(0,x,m));		
	}
	return 0;
}
