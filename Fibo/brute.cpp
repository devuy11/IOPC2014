#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
#include<stack>
#include<queue>
#include<map>
#include<set>
using namespace std;
typedef long long int ll;
int comb[1001][1001],n,r,m;
void pre(int mod)
{
	for(int i=0;i<=n;i++)	comb[i][i]=comb[i][0]=1;
	for(int i=2;i<=n;i++)
		for(int j=1;j<i;j++)
			comb[i][j]=(comb[i-1][j-1]+comb[i-1][j])%mod;
}
int cal_period(int mod)
{
	if(mod==1)	return 1;
	int s=0,e=1,p=0;
	do{
		s=(s+e)%mod;
		swap(s,e);
		p++;
	}while(!(s==0 && e==1));
	return p;
}
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
void solve()
{
	scanf("%d%d%d",&n,&r,&m);
	int p=cal_period(m);
	pre(p);
	int z=comb[n][r];
	z++;
	printf("%d\n",fibo(z,m));
}
int main()
{
	int test;
	scanf("%d",&test);
	while(test--){
		solve();
	}
	return 0;
}
