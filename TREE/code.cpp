/*Cost of a path from a to b is defined as (val(a))^(val(parent(a)))^(val(parent(parent(a))))^.....^(val(b)) Modulo M
  Given Q Queries ::
   a b :: Compute the cost of the path from node a to node b
  Constraints::
  M<=100
  Q<=10000
 */
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<utility>
#include<assert.h>
using namespace std;
typedef long long int ll;
int Edit[1025];
int head[1025][1025],cycle[1025][1025];
int max_L[1025];
int max_p,steps;
int glob[100002];
int gcd(int x,int y)
{
	if(y==0){
		return x;
	}
	return gcd(y,x%y);
}
//check if a^b is less than n or not, if a^b is greater than n return -1 otherwise return the **exact value**

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
//Returns the value of a^b mod m
ll binpow(ll a,ll b,ll mod)
{
	assert(mod!=0);
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

void constant(ll a,ll mod)
{
	if(cycle[mod][a]!=-1)	return;
	memset(Edit,0,mod*sizeof(int));
	int len=1,x,y,c;
	ll v=1;
	while(1){
		v=(v*a)%mod;
		if(Edit[v]!=0){
			x=Edit[v]-1;
			y=len-Edit[v];
			break;
		}
		else{
			steps++;
			Edit[v]=len;
			len++;
		}
	}
	cycle[mod][a]=y;
	head[mod][a]=x;
	ll z=x;
	for(int i=0;i<y;i++){
		steps++;
		cycle[mod][v]=y/gcd(y,z+1);
		head[mod][v]=0;
		z++;
		v=(v*a)%mod;
	}
}
void preprocess()
{
	steps=0;
	memset(cycle,-1,sizeof(cycle));
	max_p=0;
	int v,per,s,maxii=0;
	for(int m=1;m<=1024;m++){
		for(int i=0;i<m;i++){
			v=i;
			constant(v,m);
		}
	}
}
int fun(int x,int v,int h,int p,int p1)
{
	//printf("%d %d %d %d %d\n",x,v,h,p,p1);
	assert(p!=0);
	int r=(p+v-h%p)%p,pow;
	if(r==0)	pow=h+p;
	else	pow=h+r;
	return binpow(x,pow,p1);
}
pair<int,int> find_it(int a,int mod)
{
	int EDIT[100001];
	memset(EDIT,0,sizeof(EDIT));
	int len=1,x,y,c;
	ll v=1;
	//Finding x
	while(1){
		v=(v*a)%mod;
		if(EDIT[v]!=0){
			x=EDIT[v]-1;
			y=len-EDIT[v];
			break;
		}
		else{
			EDIT[v]=len;
			len++;
		}
	}
	return make_pair(y,x);
}
int powe(int arr[],int upto,int threshold,int M)
{
	int ans=1,over=1;
	if(threshold){
		for(;upto>=0;upto--){
			over=check(arr[upto],ans,2*M);
			if(over<0)	break;
			ans=over;
		}
		upto++;
		arr[upto]=ans;
	}
	int period[10],start[10],z=M,modulo[10];
	for(int i=0;i<=upto;i++){
		if(z>1000){
			pair<int,int> p=find_it(arr[i],z);
			period[i]=p.first;
                        start[i]=p.second;
                        modulo[i]=z;
                        arr[i]=(arr[i]%z);
                        z=period[i];
		}
		else{
			period[i]=cycle[z][arr[i]%z];
			start[i]=head[z][arr[i]%z];
			modulo[i]=z;
			arr[i]=(arr[i]%z);
			z=period[i];
		}
		if(period[i]==1 &&  start[i]==0){
			upto=i;
			break;
		}
	}
	//for(int i=0;i<=upto;i++)	printf("%d ",arr[i]);
	//printf("\n");
	int st=upto-1;
	//printf("%d is st\n",st);
	for(;st>=0;st--)
		arr[st]=fun(arr[st],arr[st+1],start[st],period[st],modulo[st]);
	return arr[0];
}
int main()
{
	preprocess();
	int test,lev,arr[55],x,M,khacra,y,n;
	scanf("%d",&n);	
	for(int i=1;i<=n;i++)	scanf("%d",&glob[i]);	
	scanf("%d",&test);
	while(test--){
		scanf("%d%d%d",&x,&y,&M);
		assert(x<=y);
		for(int i=0;i<=(y-x);i++){
			if(i<50)
			arr[i]=glob[i+x];
			else	break;
		}
		if(y-x+1>50)	 printf("%d\n",powe(arr,50,1,M));
		else	 printf("%d\n",powe(arr,y-x,1,M));
	}
	return 0;
}
