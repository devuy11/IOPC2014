/*
Algo :: DP
Acc
Time :: 1.3 sec
*/
#include<stdio.h>
#include<assert.h>
typedef long long int ll;
ll q,r;
void powmod(ll R,ll a,ll b)
{
	ll q1=0,r1=0;
	while(a)
		if(a&1){
			a--;
			r1=r1+R;
			if(r1>=b){
				r1=r1-b;
				q1=q1+1;
			}
		}
		else{
			a>>=1;
			R=R+R;
			if(R >= b){
				R=R-b;
				q1=q1+a;
			}
		}
	q=q1;
	r=r1;
}
int main()
{
	int test,curr,prev;
	ll state[2][2],mod,a,b;
	ll z=1e9;
	z=(ll)z*(ll)z;
	scanf("%d",&test);
	assert(test<=100);
	while(test--){
		curr=1;
		scanf("%lld %lld",&a,&b);
		assert(a<=100000 && b<=z);
		mod=b%2;
		if((a==1 && b==1) || (a==0 && b==1) ){
			printf("Odd\n");
			continue;
		}
		state[0][0]=0;
		state[0][1]=1;		//remainder is 1
		state[1][0]=0;
		state[1][1]=0;
		for(ll i=2;i<=a;i++){
			prev=curr^1;
			powmod(state[prev][1],i,b);
			state[curr][0]=(state[prev][0]*i+q)&1;
			state[curr][1]=r;
			curr=curr^1;
		}
		prev=curr^1;
		if(state[prev][0]==0)	printf("Even\n");
		else	printf("Odd\n");
	}
}
