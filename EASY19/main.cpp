#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
using namespace std;
char str[100007];
int As[100007];
int Cp[100007];
int m,maxa;
void solve()
{
	maxa=0;
	scanf("%s%d",str,&m);
	int len=strlen(str);
	for(int i=0;i<=len;i++)	As[i]=0;
	//init step
	for(int i=1;i<=len;i++){
		if(str[i-1]=='A')	As[i]=1+As[i-1];
		else	As[i]=As[i-1];
	}
	for(int i=0;i<m;i++)	Cp[i]=As[i];
	for(int i=m;i<=len;i++)	Cp[i]=As[i]-As[i-m];
	for(int i=0;i<=len;i++){
		maxa=max(maxa,Cp[i]);
	}
	printf("%d\n",m-maxa);
	return ;
}
int main()
{
	int test;	
	scanf("%d",&test);
	while(test--)	solve();
	return 0;
}
