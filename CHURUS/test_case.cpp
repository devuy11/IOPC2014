#include<stdio.h>
#include<algorithm>
#include<stdlib.h>
using namespace std;
int find(int s,int e)
{
        return s+(rand()%(e-s+1));
}
void gen(char file[],int N,int A,int Q)
{
	FILE *fp = fopen(file,"w");
	fprintf(fp,"%d\n",N);
	while(N--)	fprintf(fp,"%d\n",find(1,A));
	fprintf(fp,"%d\n",Q);
	while(Q--){
		fprintf(fp,"%d\n",find(1,2000));
	}
	fclose(fp);
}
void sep_gen(char file[],int N,int st,int end,int Q)
{
	FILE *fp = fopen(file,"w");
        fprintf(fp,"%d\n",N);
	for(int i=0;i<N;i++)	fprintf(fp,"%d\n",find(st,end));
	fprintf(fp,"%d\n",Q);
	while(Q--)	fprintf(fp,"%d\n",find(1,2000));
	fclose(fp);
}
void chain(char file[],int N,int Q)
{
	FILE *fp = fopen(file,"w");
        fprintf(fp,"%d\n",N);
	int x=1;
	for(int i=0;i<N;i++){
		fprintf(fp,"%d\n",x);
		x=(x)%1000 + 1;
	}
	fprintf(fp,"%d\n",Q);
	x=1;
	for(int i=0;i<Q;i++){   
                fprintf(fp,"%d\n",x);
                x=(x)%2000 + 1;
        }
	fclose(fp);
}
int main()
{
	char in_files[27][20]={"input/input00.txt" ,"input/input01.txt","input/input02.txt","input/input03.txt","input/input04.txt","input/input05.txt","input/input06.txt","input/input07.txt","input/input08.txt","input/input09.txt","input/input10.txt","input/input11.txt","input/input12.txt","input/input13.txt","input/input14.txt","input/input15.txt"};
	sep_gen(in_files[0],100,999,1000,100);		//only 1 number from 999 to 1000,with Q=10000
	sep_gen(in_files[1],100,1,1,100);
	chain(in_files[2],1000,100);
	gen(in_files[3],1000,1000,100);	
	gen(in_files[4],1000,1000,100);	
	gen(in_files[5],1000,1000,100);	
	gen(in_files[6],1000,1000,100);
	return 0;
}
