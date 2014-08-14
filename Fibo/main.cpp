#include<stdio.h>
#include<bitset>
#include<iostream>
#include<string.h>
#include<algorithm>
#include<stdlib.h>
#include<stack>
#include<map>
using namespace std;
#define Max 12322
#define lmt 111
typedef long long int ll;

/**********************USED FOR CAL PERIOD OF FIB() % M***************/
int prime[(Max)>>1],counter,fact[20],mul[20];
bitset<(Max>>1)> mybits;
void sieve()
{
        prime[0]=2;
        counter=1;
        for(int i=3;i<lmt;i+=2)
                if(!mybits[i>>1])
                        for(int j=i*i,k=i<<1;j<Max;j+=k)
                                mybits.set(j>>1,1);
        for(int i=3;i<Max;i+=2)
                if(!mybits[i>>1]){
                        prime[counter]=i;
                        counter++;
                }
}
int factorise(int x)
{
        int tot=0,y;
        for(int i=0;i<counter;i++){
                if(x<prime[i])  break;
                if(x%prime[i]==0){
                        fact[tot]=prime[i];
                        x/=prime[i];
                        y=x;
                        while(x%prime[i]==0){
                                x/=prime[i];
                        }
                        mul[tot]=y/x;
                        tot++;
                }
        }
        if(x>1){
                fact[tot]=x;
                mul[tot]=1;
                tot++;
        }
        return tot;
}
ll gcd(ll a,ll  b){
        if(b==0)        return a;
        return gcd(b,a%b);
}
ll lcm(ll a,ll b)
{
        return a*b/gcd(a,b);
}
int cal_period(int mod)
{
	int upto=factorise(mod);
	int ans=1;
	for(int j=0;j<upto;j++){
		if(fact[j]%5==0)        mul[j]*=20;
		if(fact[j]%5==1 || fact[j]%5==4)        mul[j]*=(fact[j]-1);
		if(fact[j]%5==2 || fact[j]%5==3)        mul[j]*=(2*fact[j]+2);
		ans=lcm(ans,mul[j]);
	}
	return ans;
}
/**************USED IN CALCULATING PERIOD OF FIB() % M **************/



/*************USED IN CALCULATING nCr % p *************************/
ll fast_comb[10][100001];
int count_comb[10][100001];
ll rem[20],modulo[20];		//FOR CRT
int powmod(int a,int b,int m)
{
	int ans=1;
	while(b)
		if(b&1){
			ans=((ll)ans*(ll)a)%m;
			b--;	
		}
		else{
			a=( (ll)a* (ll)a )%m;
			b>>=1;
		}
	return ans%m;
}
ll inverse(ll a,ll b)	//a inverse % b
{
	ll Remainder,p0=0,p1=1,pcurr=1,q,m=b;
	while(a!=0){
		Remainder=b%a;
		q=b/a;
		if(Remainder!=0){
			pcurr=p0-(p1*q)%m;
			if(pcurr<0)	pcurr+=m;
			p0=p1;
			p1=pcurr;
		}
		b=a;
		a=Remainder;
	}
	return pcurr;
}
ll CRT(int t)
{
	ll ans=rem[0],m=modulo[0],a,b,c;
	for(int i=1;i<t;i++){
		a=inverse(m,modulo[i]);
		b=inverse(modulo[i],m);
		c=m*modulo[i];
		ans=( ((ans*b)%c)*modulo[i]  +  ((rem[i]*a)%c)*m ) % c;
		m=m*modulo[i];
	}
	return ans;
}
int cal_ncr(int n,int r,int m)
{
	//printf("%d is cal_ncr m\n",m);
	int upto=factorise(m),s;
	for(int i=0;i<upto;i++)	mul[i]*=fact[i];
	for(int i=0;i<upto;i++){
		for(int j=1;j<=n;j++){
			count_comb[i][j]=count_comb[i][j-1];
			s=j;
			while(s%fact[i]==0){
				count_comb[i][j]++;
				s/=fact[i];
			}
			fast_comb[i][j]=((ll)fast_comb[i][j-1]*(ll)s)%mul[i];
		}
	}
	//printf("%d n %d r %d m\n",n,r,m);
	for(int i=0;i<upto;i++){
		modulo[i]=mul[i];
		//printf("%lld ",modulo[i]);
		rem[i]=(((fast_comb[i][n]*inverse(fast_comb[i][r],modulo[i]))%modulo[i])*(inverse(fast_comb[i][n-r],modulo[i]))) %modulo[i] ;
		//printf("%lld  ",rem[i]);
		rem[i]=(rem[i]*(ll)powmod(fact[i],count_comb[i][n]-count_comb[i][r]-count_comb[i][n-r],modulo[i]))%modulo[i];
		//printf("%lld\n",rem[i]);
	}
	return CRT(upto);	
}
/*************USED IN CALCULATING nCr % p *************************/


/************CALCULATING FIBONACCI(z) %m *************************/
ll ans[2][2]={{1,0},{0,1}};
ll A[2][2]={{1,1},{1,0}};
void mat_same(int mod)	//A*A
{
	ll reply[2][2]={{0,0},{0,0}};
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			for(int k=0;k<2;k++){
				reply[i][j]=(reply[i][j]+A[i][k]*A[k][j])%mod;
			}
		}
	}
	memcpy(A,reply,sizeof(reply));
}
void mat_diff(int mod)
{
	ll reply[2][2]={{0,0},{0,0}};
        for(int i=0;i<2;i++){
                for(int j=0;j<2;j++){
                        for(int k=0;k<2;k++){
                                reply[i][j]=(reply[i][j]+ans[i][k]*A[k][j])%mod;
                        }
                }
        }
        memcpy(ans,reply,sizeof(reply));
}
void mat_mult(int a,int mod)
{
	A[0][0]=1;
	A[0][1]=1;
	A[1][0]=1;
	A[1][1]=0;
	ans[0][0]=1;
	ans[0][1]=0;
	ans[1][0]=0;
	ans[1][1]=1;
	while(a)
		if(a&1){
			mat_diff(mod);
			a--;
		}
		else{
			mat_same(mod);
			a>>=1;
		}
}
int fibo(int x,int mod)		//Fibo(x)%mod
{
	mat_mult(x,mod);
	return ans[1][1];
}
/************CALCULATING FIBONACCI(z) %m *************************/

void solve()
{
	int n,m,r,z;
	scanf("%d%d%d",&n,&r,&m);
	int p=cal_period(m);
	//printf("%d is p\n",p);
	z=cal_ncr(n,r,p);
	//printf("%d is z\n",z);
	z++;
	printf("%d\n",fibo(z,m));
}
int main()
{
	for(int i=0;i<10;i++)   fast_comb[i][0]=1,count_comb[i][0]=0;
	sieve();
	int test;
	scanf("%d",&test);
	while(test--){
		solve();
	}
	return 0;
}
