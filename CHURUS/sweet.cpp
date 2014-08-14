#include <iostream>
#include <cstdio>
using namespace std;
int main(){
	long long q,n,i,j,k,count[1002],mod=1000000007;
	cin>>n;
	for(i=0;i<1002;i++)count[i]=0;
	for(i=0;i<n;i++){
		scanf("%lld",&j);
		count[j+1]++;
	}
	long long arr[2001],ans[2001],mid[2001],sum;
	for(i=0;i<2001;i++)ans[i]=0;
	ans[0]=1;
	for(i=1;i<1002;i++){
		for(j=0;j<2001;j++)arr[j]=mid[j]=0;
		arr[0]=1;
		for(j=0;j<count[i];j++){
			sum=0;
			for(k=0;k<2001;k++){
				sum=(sum+arr[k])%mod;
				if(k>=i)sum=(sum+mod-arr[k-i])%mod;
				mid[k]=sum;
			}		
			for(k=0;k<2001&&mid[k]>0;k++)arr[k]=mid[k];
		}
		for(j=0;j<2001;j++)mid[j]=0;
		for(j=0;j<2001&&ans[j]>0;j++){
			for(k=0;(j+k)<2001&&arr[k]>0;k++){
				mid[j+k]=(mid[j+k]+arr[k]*ans[j])%mod;
			}
		}
		for(j=0;j<2001&&mid[j]>0;j++)ans[j]=mid[j];
	}
	cin>>q;
	for(i=0;i<q;i++){
		scanf("%lld",&j);
		printf("%lld\n",ans[j]);
	}
	return 0;
}