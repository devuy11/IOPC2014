#include<stdio.h>
#include<algorithm>
#include<stdlib.h>
#include<assert.h>
using namespace std;
char use[100001];
int find(int s,int e)
{
        return s+(rand()%(e-s+1));
}
void strRan(int s)
{
	for(int i=0;i<s;i++)	use[i]='B';
	use[s]='\0';
}
void gen(char file[],int s,int e,int n,int T)
{
	int a,b,x;
        FILE *fp = fopen(file,"w");
	fprintf(fp,"%d\n",T);
	for(int i=0;i<T;i++){
		strRan(n);
		a=find(s,e);
		b=find(1,a);
		while(a--){
			while(1){
				x=find(1,n);
				if(use[x]=='B'){
					use[x]='A';
					break;
				}	
			}
		}
		fprintf(fp,"%s\n%d\n",use,b);
	}
        fclose(fp);
}
void all(char file[],int n,int T)
{
	int z,count,sum=0;
	FILE *fp = fopen(file,"w");
	fprintf(fp,"%d\n",T);
	for(int i=1;i<(1<<n);i++){
		count=0;
		z=i;
		while(z!=0){
			if(z&1)	count++;
			z>>=1;
		}
		for(int j=1;j<=count;j++){
			strRan(n);
			for(int k=0;k<15;k++){
				if((i&(1<<k))!=0)	use[k]='A';
			}
			sum++;
			fprintf(fp,"%s\n%d\n",use,j);
		}
	}
	assert(sum==T);
	fclose(fp);	
}
void random(char file[],int n,int T)
{
	int count=0,op;
	FILE *fp = fopen(file,"w");
	fprintf(fp,"%d\n",T);
	for(int i=0;i<T;i++){
		count=0;
		strRan(100);
		op=find(1,100);
		while(op--){
			use[find(0,99)]='A';
		}
		for(int i=0;i<100;i++)	if(use[i]=='A')	count++;
		fprintf(fp,"%s\n%d\n",use,find(1,count));
	}
        fclose(fp);
}
int main()
{
	char in_files[27][20]={"input/input00.txt" ,"input/input01.txt","input/input02.txt","input/input03.txt","input/input04.txt","input/input05.txt","input/input06.txt","input/input07.txt","input/input08.txt","input/input09.txt","input/input10.txt","input/input11.txt","input/input12.txt","input/input13.txt","input/input14.txt","input/input15.txt"};
	all(in_files[0],13,4096*13);		//all test cases for n=10
	gen(in_files[1],25,75,100,10000);
	gen(in_files[2],250,750,1000,1000);
	gen(in_files[3],2500,7500,10000,100);
	gen(in_files[4],25000,75000,100000,10);
	random(in_files[5],100,1000);
	gen(in_files[6],5,15,20,50000);
	gen(in_files[7],2,4,5,200000);
	return 0;
}
