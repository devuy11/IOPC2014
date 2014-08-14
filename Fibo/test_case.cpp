#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<stack>
#include<queue>
#include<map>
#include<set>
#include<bitset>
#include<iostream>
#include<utility>
using namespace std;
struct node
{
	int n,r,m;
	node(int a=0,int b=0,int c=0){
		n=a;
		r=b;
		m=c;
	}
}A[100001];

int gcd(int a,int b)
{
	if(b==0)	return a;
	return gcd(b,a%b);
}
int find(int s,int e)
{
	return s+(rand()%(e-s+1));
}
void gen(int ns,int ne,int rs,int re,int ms,int me,int &n,int &r,int &m)
{
	while(1){
		n=find(ns,ne);
		r=find(rs,re);
		if(n<r)	swap(n,r);
		m=find(ms,me);
		if(gcd(n,m)==1 && gcd(r,m)==1)	return ;
	}
}
void generate(char file[],int ns,int ne,int rs,int re,int ms,int me)
{
	int n,r,m,sum=0,t=0;
	FILE *fp=fopen(file,"w");
	gen(ns,ne,rs,re,ms,me,n,r,m);
	sum+=n;
	while(sum<=100000){
		A[t]=node(n,r,m);
		t++;
		gen(ns,ne,rs,re,ms,me,n,r,m);
		sum+=n;
	}
	fprintf(fp,"%d\n",t);
	for(int i=0;i<t;i++){
		fprintf(fp,"%d %d %d\n",A[i].n,A[i].r,A[i].m);
	}
	fclose(fp);
}
int main()
{
	char in_files[27][20]={"input/input00.txt" ,"input/input01.txt","input/input02.txt","input/input03.txt","input/input04.txt","input/input05.txt","input/input06.txt","input/input07.txt","input/input08.txt","input/input09.txt","input/input10.txt","input/input11.txt","input/input12.txt","input/input13.txt","input/input14.txt","input/input15.txt","input/input16.txt","input/input17.txt","input/input18.txt","input/input19.txt","input/input19.txt"};
	for(int i=0;i<6;i++)	generate(in_files[i],1,1000,1,1000,1,1000);
	for(int i=6;i<12;i++)	generate(in_files[i],1,1000,1,1000,1001,10000000);
	for(int i=12;i<16;i++)	generate(in_files[i],1001,10000,1,10000,1,10000000);
	for(int i=16;i<17;i++)	generate(in_files[i],40001,50000,1,50000,1,10000000);		
	for(int i=17;i<18;i++)	generate(in_files[i],100000,100000,1,100000,1,10000000);		
	for(int i=18;i<19;i++)	generate(in_files[i],100000,100000,1,100000,1,10000000);
	for(int i=19;i<20;i++)	generate(in_files[i],100,1000,100,1000,9765625,9765625);	
	return 0;
}
