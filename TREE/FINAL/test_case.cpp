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
void gen(char file[],int c,int N,int Q,int mini,int M)
{
	int U=5;
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
	fprintf(fp,"%d",find(2,1000000000));
	FOR(i,2,N)	fprintf(fp," %d",find(2,100000000));
	fprintf(fp,"\n");
	FOR(i,1,Q){
		if(U>0){
			if(rand()%2){
				if(A[p].steps<mini){
					fprintf(fp,"Q %d %d %d\n",A[1].s,A[1].e,find(1,M));
					p=2;
				}
				else{
					fprintf(fp,"Q %d %d %d\n",A[p].s,A[p].e,find(1,M));
					p++;
				}
				if(p==counter)  p=1;
			}
			else{
				U--;
				fprintf(fp,"U %d %d\n",find(2,N),find(2,1000000000));
			}
		}
		else{
			if(A[p].steps<mini){
				fprintf(fp,"Q %d %d %d\n",A[1].s,A[1].e,find(1,M));
				p=2;
			}
			else{
				fprintf(fp,"Q %d %d %d\n",A[p].s,A[p].e,find(1,M));
				p++;
			}
			if(p==counter)  p=1;
		}
	}
	fclose(fp);
}
void st_chain(char file[],int N,int Q,int M)
{
	int x,y,U=5;
	FILE *fp=fopen(file,"w");
	fprintf(fp,"%d %d\n",N,Q);
	FOR(i,1,N-1)	fprintf(fp,"%d %d\n",i,i+1);
	fprintf(fp,"%d",find(2,1000000000));
        FOR(i,2,N)      fprintf(fp," %d",find(2,100000000));
        fprintf(fp,"\n");
	FOR(i,1,Q){
		if(U>0){
			if(rand()%2){	
				U--;
				fprintf(fp,"U %d %d\n",find(1,N),find(2,10000));
			}
			else{
				x=find(1,N);
				y=find(1,N);
				fprintf(fp,"Q %d %d %d\n",x,y,find(1,M));
			}
		}
		else{
			x=find(1,N);
			y=find(1,N);
			fprintf(fp,"Q %d %d %d\n",x,y,find(1,M));
		}
	}
	fclose(fp);
}
void st_chain1(char file[],int N,int Q,int M)
{
        int x,y,U=5,A[15];
	A[0]=1;
	for(int i=1;i<15;i++)	A[i]=A[i-1]<<1;
        FILE *fp=fopen(file,"w");
        fprintf(fp,"%d %d\n",N,Q);
        FOR(i,1,N-1)    fprintf(fp,"%d %d\n",i,i+1);
        fprintf(fp,"%d",A[(rand()%14)+1]);
        FOR(i,2,N)      fprintf(fp," %d",A[(rand()%14)+1]);
        fprintf(fp,"\n");
        FOR(i,1,Q){
                if(U>0){
                        if(rand()%2){
                                U--;
                                fprintf(fp,"U %d %d\n",find(1,N),find(2,10000));
                        }
                        else{
                                x=find(1,N);
                                y=find(1,N);
                                fprintf(fp,"Q %d %d %d\n",x,y,find(1,M));
                        }
                }
                else{
                        x=find(1,N-4);
                        y=find(x,x+2);
                        fprintf(fp,"Q %d %d %d\n",x,y,M);
                }
        }
        fclose(fp);
}
void dhinwa_graph(char file[],int chain,int N,int Q,int M)
{
	int U=5;
	FILE *fp=fopen(file,"w");
	fprintf(fp,"%d %d\n",N,Q);
	for(int i=1;i<chain;i++)	fprintf(fp,"%d %d\n",i,i+1);
	for(int i=chain;i<N;i++){
		fprintf(fp,"%d %d\n",i+1,(rand()%i)+1);
	}
	fprintf(fp,"%d",find(2,1000000000));
        FOR(i,2,N)      fprintf(fp," %d",find(2,100000000));
        fprintf(fp,"\n");
	int flag=0;
	for(int i=0;i<Q;i++){
		if(U>0){
			if(rand()%2){
				U--;
				fprintf(fp,"U %d %d\n",find(1,chain),find(2,1000));
			}
			else
				fprintf(fp,"Q %d %d %d\n",find(1,1000),find(chain-1000,chain),find(2,1000));
		}
		else{
			fprintf(fp,"Q %d %d %d\n",find(1,1000),find(chain-1000,chain),find(2,1000));
		}
	}
	fclose(fp);
}
int main()
{	
	char in_files[27][20]={"input/input00.txt" ,"input/input01.txt","input/input02.txt","input/input03.txt","input/input04.txt","input/input05.txt","input/input06.txt","input/input07.txt","input/input08.txt","input/input09.txt","input/input10.txt","input/input11.txt","input/input12.txt","input/input13.txt","input/input14.txt","input/input15.txt"};
	//gen(in_files[0],2,20,10000,2,1000);
	gen(in_files[0],100,100000,100000,100,100000);			//c,N,Q,mini,M
	gen(in_files[1],500,100000,100000,1000,100000);
	dhinwa_graph(in_files[2],1e4,1e5,100000,100000);		//chain,N,Q,M
	dhinwa_graph(in_files[3],1e4,1e5,100000,100000);
	dhinwa_graph(in_files[4],1e4,1e5,100000,100000);
	st_chain(in_files[5],100000,100000,100000);			//N,Q-->Random.
	st_chain1(in_files[6],100000,100000,65536);
	return 0;
}
