#include<stdio.h>
#include<string.h>
char A[5003];
bool check(int a,int b,int c,int d)
{
	if(b>=c && d>a)	return true;
	if(d>=a && b>c)	return true;
	return false;
}
int satisfy (int a,int b,int c,int d,int e,int f,int m)
{
	int sum=0;
	for(int i=a;i<=b;i++)	if(A[i]=='a')	sum++;	
	for(int i=c;i<=d;i++)	if(A[i]=='a')	sum++;	
	for(int i=e;i<=f;i++)	if(A[i]=='a')	sum++;	
	if(sum>=m)	return 1;
	return 0;
}
int main()
{
	int m,ans=0,mod=1000000007,test;
	scanf("%d",&test);
	while(test--){
	ans=0;
	scanf("%s%d",A,&m);
	int len=strlen(A);
		
	for(int a=0;a<len;a++)
		for(int b=a;b<len;b++)
			for(int c=b+1;c<len;c++)
				for(int d=c;d<len;d++)
					for(int e=d+1;e<len;e++)
						for(int f=e;f<len;f++){
							if(check(a,b,c,d) && check(a,b,e,f) && check(c,d,e,f))	break;
							ans=(ans+satisfy(a,b,c,d,e,f,m))%mod;
						}
	printf("%d\n",ans);
	}
	return 0;
}
