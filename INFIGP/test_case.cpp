#include<stdio.h>
#include<algorithm>
#include<stdlib.h>
#include<assert.h>
using namespace std;
int find(int s,int e)
{
        return s+(rand()%(e-s+1));
}
int pow[30];
void constant()
{
	pow[0]=1;
	for(int i=1;i<=29;i++)	pow[i]=pow[i-1]<<1;
}
void all(char file[],int s,int e,int T)
{
	FILE *fp = fopen(file,"w");
	fprintf(fp,"%d\n",T);
	for(int i=1;i<=s;i++){
		for(int j=1;j<=e;j++){
			fprintf(fp,"%d %d\n",i,j);
		}
	}
	fclose(fp);
}
void randomly(char file[],int T)
{
        FILE *fp = fopen(file,"w");
	fprintf(fp,"%d\n",T);
	for(int i=0;i<T;i++){
		fprintf(fp,"%d %d\n",find(101,1000000000),find(101,1000000000));
	}
        fclose(fp);
}
void pow2_all(char file[],int start,int T)
{
	int st,sum=0;
        FILE *fp = fopen(file,"w");
	fprintf(fp,"%d\n",T);
	for(int i=1;i<=start;i++){
		st=pow[i];	
		sum+=st;
		for(int j=1;j<=st;j++)	fprintf(fp,"%d %d\n",j,st);
	}
	assert(sum==T);
        fclose(fp);
}
void pow2_notall(char file[],int st,int end,int T)
{
        FILE *fp = fopen(file,"w");
	fprintf(fp,"%d\n",T);
	int rep=T/(end-st+1),term,sum=0;
	for(int i=st;i<=end;i++){
		term=pow[i];
		for(int j=0;j<rep;j++)	fprintf(fp,"%d %d\n",find(1,1000000000),term);
		sum+=rep;
	}
	assert(sum==T);
        fclose(fp);
}
int main()
{
	constant();
	char in_files[27][20]={"input/input00.txt" ,"input/input01.txt","input/input02.txt","input/input03.txt","input/input04.txt","input/input05.txt","input/input06.txt","input/input07.txt","input/input08.txt","input/input09.txt","input/input10.txt","input/input11.txt","input/input12.txt","input/input13.txt","input/input14.txt","input/input15.txt"};
	all(in_files[0],100,100,10000);
	randomly(in_files[1],10000);
	pow2_all(in_files[2],14,pow[15]-2);
	pow2_notall(in_files[3],15,18,50000);
	pow2_notall(in_files[4],19,22,50000);
	pow2_notall(in_files[5],23,26,50000);
	pow2_notall(in_files[6],27,28,50000);
	pow2_notall(in_files[7],29,29,50000);
	return 0;
}
