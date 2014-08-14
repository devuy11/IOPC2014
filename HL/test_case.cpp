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
void gen(char file[],int c,int N,int Q,int mini,int R)
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
	fprintf(fp,"%d %d %d\n",N,Q,R);
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
	FOR(i,1,Q){
		if(rand()%2){
			if(A[p].steps<mini){
				fprintf(fp,"Q %d %d\n",A[1].s,A[1].e);
				p=2;
			}
			else{
				fprintf(fp,"Q %d %d\n",A[p].s,A[p].e);
				p++;
			}
			if(p==counter)  p=1;
		}
		else{
			if(rand()%2)
				fprintf(fp,"U %d %d\n",(rand()%N)+1,rand()%1000);
			else
				fprintf(fp,"U %d %d\n",(rand()%N)+1,-(rand()%1000));
		}
	}
	fclose(fp);
}
void st_chain(char file[],int N,int Q,int root)
{
	int x,y;
	FILE *fp=fopen(file,"w");
	fprintf(fp,"%d %d %d\n",N,Q,root);
	FOR(i,1,N-1)	fprintf(fp,"%d %d\n",i,i+1);
	FOR(i,1,Q){
		if(rand()%2){
			if(rand()%2)
				fprintf(fp,"U %d %d\n",find(1,N),rand()%1000);
			else
				fprintf(fp,"U %d %d\n",find(1,N),-(rand()%1000));
		}
		else{
			x=find(1,N);
			y=find(1,N);
			fprintf(fp,"Q %d %d\n",x,y);
		}
	}
	fclose(fp);
}
void dhinwa_graph(char file[],int chain,int N,int Q,int root,int up,int qu)
{
	FILE *fp=fopen(file,"w");
	fprintf(fp,"%d %d %d\n",N,Q,root);
	for(int i=1;i<chain;i++)	fprintf(fp,"%d %d\n",i,i+1);
	for(int i=chain;i<N;i++){
		fprintf(fp,"%d %d\n",i+1,(rand()%i)+1);
	}
	int flag=0;
	for(int i=0;i<Q;i++){
		if(up){
			fprintf(fp,"U %d %d\n",find(1,chain),rand()%1000);
		}
		else if(qu){
			fprintf(fp,"Q %d %d\n",find(1,10),find(chain-10,chain));
		}
		else{
			flag=flag^1;
			if(flag){
				if(rand()%2)
					fprintf(fp,"U %d %d\n",find(1,chain),rand()%1000);
				else
					fprintf(fp,"U %d %d\n",find(1,chain),-(rand()%1000));
			}
			else{
				fprintf(fp,"Q %d %d\n",find(1,1000),find(chain-1000,chain));
			}
		}
	}
	fclose(fp);
}
int main()
{	
	char in_files[27][20]={"input/input00.txt" ,"input/input01.txt","input/input02.txt","input/input03.txt","input/input04.txt","input/input05.txt","input/input06.txt","input/input07.txt","input/input08.txt","input/input09.txt","input/input10.txt","input/input11.txt","input/input12.txt","input/input13.txt","input/input14.txt","input/input15.txt"};
	gen(in_files[0],100,1e5,1e5,1000,27);
	gen(in_files[1],500,1e5,1e5,1000,2392);
	dhinwa_graph(in_files[2],1e4,1e5,1e5,23,1,0);		//chain,N,Q,root,Only Updates,Only Queries
	dhinwa_graph(in_files[3],1e4,1e5,1e5,54,0,1);
	dhinwa_graph(in_files[4],1e4,1e5,1e5,98,0,0);		//Alternate Queries
	st_chain(in_files[5],1e5,1e5,50000);			//N,Q-->Random.
	return 0;
}
