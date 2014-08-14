#include<stdio.h>
#include<string.h>
#include<stdlib.h>
using namespace std;
typedef long long int ll;
char A[5009];
ll dp[2][5001][2][3];
const int mod=1000000007;
int main()
{
	int N,M,len,flag=0,prev;
	scanf("%d%s",&M,A);
	len=strlen(A);
	N=len;
	memset(dp,0,sizeof(dp));
	//Base Case
	for(int i=0;i<N;i++){
		prev=flag^1; 
		for(int j=0;j<=i+1;j++){	//If I Loose the Segment Under Cons.
			dp[flag][j][1][0]=dp[flag][j][1][1]=dp[flag][j][1][2]=0;
			dp[flag][j][0][0]=dp[prev][j][0][0]+dp[prev][j][1][0];
			dp[flag][j][0][1]=dp[prev][j][0][1]+dp[prev][j][1][1];
			dp[flag][j][0][2]=dp[prev][j][0][2]+dp[prev][j][1][2];
		}
		//Initing with a Segment
		if(A[i]=='a'){
			for(int j=0;j<=i;j++){
				dp[flag][j+1][1][1]=dp[prev][j][0][0]+dp[prev][j][1][0];
				dp[flag][j+1][1][2]=dp[prev][j][0][1]+dp[prev][j][1][1];
			}
			dp[flag][1][1][0]=1;//a=1,cont=1,seg=1
		}
		else{
			for(int j=0;j<=i;j++){
				dp[flag][j][1][1]=dp[prev][j][0][0]+dp[prev][j][1][0];
				dp[flag][j][1][2]=dp[prev][j][0][1]+dp[prev][j][1][1];
			}
			dp[flag][0][1][0]=1;//a=0,cont=1,seg=1
		}
		for(int j=0;j<=i+1;j++){	//If I continue with the current.
			if(A[i]=='a'){
				dp[flag][j+1][1][0]+=dp[prev][j][1][0];
				dp[flag][j+1][1][1]+=dp[prev][j][1][1];
				dp[flag][j+1][1][2]+=dp[prev][j][1][2];
			}
			else{
				dp[flag][j][1][0]+=dp[prev][j][1][0];
				dp[flag][j][1][1]+=dp[prev][j][1][1];
				dp[flag][j][1][2]+=dp[prev][j][1][2];
			}
		}
		for(int j=0;j<=i+1;j++){
			dp[flag][j][0][0]%=mod;
			dp[flag][j][0][1]%=mod;
			dp[flag][j][0][2]%=mod;

			dp[flag][j][1][0]%=mod;
			dp[flag][j][1][1]%=mod;
			dp[flag][j][1][2]%=mod;
		}
		flag=flag^1;
	}
	int ans=0;
	flag=flag^1;
	for(int i=M;i<=N;i++){
		ans=(ans+dp[flag][i][0][2])%mod;
		ans=(ans+dp[flag][i][1][2])%mod;
	}
	printf("%d\n",ans);
	//printf("%lld %lld %lld\n",dp[flag][1][1][0]+dp[flag][1][0][0],dp[flag][1][1][1]+dp[flag][1][0][1],dp[flag][1][0][2]+dp[flag][1][1][2]);
	return 0;
}
