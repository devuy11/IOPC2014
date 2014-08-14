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
#include<assert.h>
using namespace std;
#define st 1
#define end 1000000000
struct query{
	int array[1001];
	int k;
	int sum;
}A[1001];
int power4[15];
int power3[15];
int find(int s,int e)
{
	return s+(rand()%(e-s+1));
}
void constant()
{
	power4[0]=1;
	power3[0]=1;
	for(int i=1;i<=14;i++)	power4[i]=power4[i-1]*4;
	for(int i=1;i<=14;i++)	power3[i]=power3[i-1]*3;
}
void gen(char file[][20])
{
	for(int i=1;i<=8;i++){
		FILE *fp=fopen(file[i-1],"w");
		for(int j=1;j<=100;j++){
			fprintf(fp,"%d %d\n",A[(i-1)*100+j].sum,A[(i-1)*100+j].k);
			fprintf(fp,"%d",A[(i-1)*100+j].array[1]);
			for(int k=2;k<=A[(i-1)*100+j].k;k++){
				fprintf(fp," %d",A[(i-1)*100+j].array[k]);
			}
			if(A[(i-1)*100+j].sum==0){
				printf("%d is k \n",A[(i-1)*100+j].k);
			}
			assert(A[(i-1)*100+j].sum<=1000000000);
			assert(A[(i-1)*100+j].sum>=0);
			fprintf(fp,"\n");
		}
		fprintf(fp,"0 0\n");
		fclose(fp);
	}
}
void fun()
{
	int c=1,t;
	for(int i=0;i<50;i++){
		A[c].k=2;
		A[c].array[1]=1;
		A[c].array[2]=find(1,1000);
		c++;
	}
	for(int s=1;s<=14;s++){
		for(int j=1;j<=8;j++){
			t=find(power4[s]+1,end-100);
			A[c].k=2;
			A[c].array[1]=t;
			A[c].array[2]=s;
			c++;
		}
	}
	for(int s=1;s<=14;s++){
		for(int j=1;j<=20;j++){
			A[c].k=2;
			A[c].array[1]=find(1,power4[s]-1);
			A[c].array[2]=s;
			c++;
		}
	}
	int range,sum;
	for(int i=1;i<=100;i++){
		sum=0;
		A[c].k=find(3,1000);
		A[c].array[1]=find(10000000,100000000);
		for(int i=2;i<A[c].k;i++){
			A[c].array[i]=find(1,10000);
			sum+=A[c].array[i];
		}
		A[c].array[A[c].k]=find(1,A[c].array[1]-sum);
		c++;
	}

	for(int i=1;i<=10;i++){
		sum=0;
		A[c].k=find(3,1000);
		A[c].array[1]=find(10000000,100000000);
		for(int i=2;i<A[c].k;i++){
			A[c].array[i]=find(1,10000);
			sum+=A[c].array[i];
		}
		A[c].array[A[c].k]=A[c].array[1]-sum;
		c++;
	}
	for(int i=2;i<=14;i++){
		for(int kl=1;kl<=5;kl++){
			A[c].k=i+1;
			for(int j=1;j<A[c].k;j++)	A[c].array[j]=1;
			//Q=i
			A[c].array[A[c].k]=find(1,power3[i]-1);
			c++;
		}
	}

	for(int i=2;i<=14;i++){
		for(int kl=1;kl<=5;kl++){
			A[c].k=i+1;
			for(int j=1;j<A[c].k;j++)    A[c].array[j]=1;
			//Q=i
			A[c].array[A[c].k]=power3[i];
			c++;
		}
	}

	for(int i=2;i<=14;i++){
		for(int kl=1;kl<=5;kl++){
			A[c].k=i+1;
			for(int j=1;j<A[c].k;j++)    A[c].array[j]=1;
			//Q=i
			A[c].array[A[c].k]=find(power3[i]+1,end-100);
			c++;
		}
	}
	for(int i=1;i<=53;i++){
		A[c].k=find(1,1000);
		//if(A[c].k==
		for(int j=1;j<=A[c].k;j++)	A[c].array[j]=find(1,100);
		c++;
	}
	for(int i=1;i<=800;i++){
		sum=0;
		for(int j=1;j<=A[i].k;j++){
			sum+=A[i].array[j];
		}
		A[i].sum=sum;
	}
	random_shuffle(A+1,A+801);
	assert(c==801);
}
int main()
{
	char in_files[27][20]={"input/input00.txt" ,"input/input01.txt","input/input02.txt","input/input03.txt","input/input04.txt","input/input05.txt","input/input06.txt","input/input07.txt","input/input08.txt","input/input09.txt","input/input10.txt","input/input11.txt","input/input12.txt","input/input13.txt","input/input14.txt","input/input15.txt"};
	constant();
	fun();
	gen(in_files);
	return 0;
}
