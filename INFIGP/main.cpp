#include<stdio.h>
#include<assert.h>
typedef long long int ll;
int pow[33];
void print_yes()
{
	printf("YES\n");
}
void print_no()
{
	printf("NO\n");
}
ll gcd(ll a,ll b)
{
	if(b==0)	return a;
	return gcd(b,a%b);
}
void solve()
{
	int p,q,g,last=0,sec_last=0,b;
	ll m;
	scanf("%d%d",&p,&q);
	assert(p>=1 && p<=1000000000);
	assert(q>=1 && q<=1000000000);
	g=gcd(p,q);
	p=p/g;
	q=q/g;
	m=p;
	b=q;
	if(p==q && p==1){
		print_yes();
		return ;
	}
	while((b%2)==0){
		b/=2;
		last++;
	}
	if(b>1){
		print_no();
		return;
	}
	if(p==1){
		print_yes();
		return;
	}
	p=p-1;
	g=gcd(p,q);
	p=p/g;
	q=q/g;
	b=q;
	while((b%2)==0){
		b/=2;
		sec_last++;
	}
	ll cr=pow[last-sec_last],inc=1;
	//printf("%d %d %lld\n",last,sec_last,cr);
	int st=0;
	while(m>0){
		m=m-inc;
		inc=inc*cr;
	}
	if(m==0)	print_yes();
	else	print_no();
}
void solveinfi(int p, int q)
{
	ll z;
	int /*p,q,*/s=-1,ts,tx,g;
	//scanf("%d%d",&p,&q);
	assert(p>=1 && p<=1000000000);
	assert(q>=1 && q<=1000000000);
	g=gcd(p,q);
	p=p/g;
	q=q/g;
	z=q;
	while((z%2)==0){
		z/=2;
	}
	for(int i=1;i<31;i++)	
		if(z==pow[i]-1){
			s=i;
			break;
		}
	if(s==-1){
		print_no();
		return ;
	}
	ts=pow[s];
	q=q/z;
	z=(ll)ts*(ll)q;
	if(z%p==0){
		p/=gcd(z,p);
		for(int i=0;i<=30;i++)	if(p==pow[i]){
			print_yes();
			return;
		}
	}
	else{
		print_no();
		return;
	}
}
int main()
{
	pow[0]=1;
	for(int i=1;i<=30;i++)	pow[i]=pow[i-1]<<1;
	int test;
	scanf("%d",&test);
	assert(test<=50000);
	int p,q;
	//while(test--){
	while(scanf("%d%d",&p,&q)!=EOF){
		test--;
		assert(p>=1 && p<=1000000000);
		assert(q>=1 && q<=1000000000);
		solveinfi(p,q);
	}
	assert(test==0);
	return 0;
}

