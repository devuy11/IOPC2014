#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<algorithm>
using namespace std;
#define FOR(i,a,b)	for(int i=(a);i<=(b);i++)
struct node{
	int s,e,steps;
	bool operator < (const node x) const{
		if(steps < x.steps)	return false;
		return true;
	}
}A[1000001];
int in[100001],pivot[1001][2],diff[1001];
int find(int s,int e)
{
	return s+(rand()%(e-s+1));
}
void gen(char file[],int c,int N,int U,int Q,int mini,int R)
{
	FILE *fp = fopen(file,"w");
	int counter=1,p,where;
	int ch=(N/c);
	FOR(i,1,N)	in[i]=i;
	random_shuffle(in+1,in+N+1);
	FOR(i,1,ch){
		pivot[i][0]=find((i-1)*c+1,i*c)-(i-1)*c;
		pivot[i][1]=find((i-1)*c+1,i*c)-(i-1)*c;
		if(pivot[i][0]>pivot[i][1])	swap(pivot[i][0],pivot[i][1]);
		diff[i]=pivot[i][1]-pivot[i][0];
	}
	diff[0]=0;
	FOR(i,1,ch)	diff[i]=diff[i-1]+diff[i];
	FOR(i,1,ch){
		FOR(j,i,ch){
			A[counter].s=in[(i-1)*c+1];
			A[counter].e=in[j*c];
			A[counter].steps=(j-i) + pivot[i][1]-1+c-pivot[j][0] + diff[j-1]-diff[i];
			counter++;
		}
	}
	sort(A+1,A+counter);
	fprintf(fp,"%d %d\n",N,Q);
	p=c-1;
	where=1;
	FOR(i,1,ch){
		while(p--){
			fprintf(fp,"%d %d\n",in[where],in[where+1]);
			where++;
		}
		p=c-1;
		where++;
	}
	//assert(where==N);
	FOR(i,1,ch-1)	fprintf(fp,"%d %d\n",in[ (i-1)*c +  pivot[i][1] ],in[ (i)*c + pivot[i+1][0] ]);
	for(int i=0;i<N;i++)	fprintf(fp,"%d ",find(2,1000000000));
	fprintf(fp,"\n");
	FOR(i,1,Q){
		if(rand()%2){
			fprintf(fp,"U %d %d\n",find(1,N),find(2,1000000000));
		}
		else{
			fprintf(fp,"Q %d %d\n",find(1,N),find(1,N));
		}
	}
	fclose(fp);
}
void st_chain(char file[],int R)
{
	int U=1e5,Q=1e5,N=1e5;
	FILE *fp=fopen(file,"w");
	fprintf(fp,"%d %d\n",N,R);
	FOR(i,1,N-1)	fprintf(fp,"%d %d\n",i,i+1);
	fprintf(fp,"%d %d\n",U,Q);
	FOR(i,1,U)	fprintf(fp,"%d %d %d 100000\n",(rand()%1000000000)+1,(rand()%1000000000)+1,i);
	FOR(i,1,Q)	fprintf(fp,"1 %d\n",i);
}
int main()
{	
	char in_files[27][20]={"input/input00.txt" ,"input/input01.txt","input/input02.txt","input/input03.txt","input/input04.txt","input/input05.txt","input/input06.txt","input/input07.txt","input/input08.txt","input/input09.txt","input/input10.txt","input/input11.txt","input/input12.txt","input/input13.txt","input/input14.txt","input/input15.txt"};
        gen(in_files[0],10,1e4,1e5,1e5,1000,73456);

        gen(in_files[1],100,1e5,1e5,1e5,1000,25837);

        gen(in_files[2],1000,1e5,1e5,1e5,1000,999999999);

        gen(in_files[3],5000,1e5,1e5,1e5,1000,347259123);

        gen(in_files[4],1e4,1e5,1e5,1e5,1000,887364758);

	return 0;
}
