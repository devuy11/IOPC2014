#include<stdio.h>
typedef long long int ll;
int main()
{
	int test,curr,prev;
	ll state[2][2],mod,q,r,a,b;
	scanf("%d",&test);
	while(test--){
		curr=1;
		scanf("%lld %lld",&a,&b);
		mod=b%2;
		if(a==0){
			printf("Even\n");
			continue;
		}
		else if(a==1 && b==1){
			printf("Odd\n");
			continue;
		}
		state[0][0]=0;
		state[0][1]=1;		//remainder is 1
		state[1][0]=0;
		state[1][1]=0;
		for(ll i=2;i<=a;i++){
			prev=curr^1;
			q=(state[prev][1]*i)/b;	
			r=(state[prev][1]*i)%b;
			q%=2;
			state[curr][0]=(state[prev][0]*i+q)%2;
			state[curr][1]=r;
			curr=curr^1;
		}
		prev=curr^1;
		if(state[prev][0]==0)	printf("Even\n");
		else	printf("Odd\n");
	}
}
