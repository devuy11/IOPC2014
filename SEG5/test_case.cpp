#include<stdio.h>
#include<algorithm>
#include<stdlib.h>
using namespace std;
int find(int s,int e)
{
        return s+(rand()%(e-s+1));
}
void gen(char file[],int S,int N,int Q,int s1,int e1,int s2,int e2)
{
	int a,b;
	FILE *fp = fopen(file,"w");
	fprintf(fp,"%d %d %d\n",S,N,Q);
	for(int i=0;i<S;i++){
		if(rand()%2)
			fprintf(fp,"%d ",(rand()%1000)+1);
		else
			fprintf(fp,"%d ",-((rand()%1000)+1));
	}
	fprintf(fp,"\n");
	for(int i=0;i<Q;i++){
		a=find(s1,e1);
		b=find(s2,e2);
		if(a>b)	swap(a,b);
		if(rand()%2){
			fprintf(fp,"U %d %d %d\n",a,b,(rand()%1000000000)+1);
		}
		else{
			fprintf(fp,"Q %d %d\n",a,b);
		}
	}
	fclose(fp);
}
int main()
{
	char in_files[27][20]={"input/input00.txt" ,"input/input01.txt","input/input02.txt","input/input03.txt","input/input04.txt","input/input05.txt","input/input06.txt","input/input07.txt","input/input08.txt","input/input09.txt","input/input10.txt","input/input11.txt","input/input12.txt","input/input13.txt","input/input14.txt","input/input15.txt"};
	gen(in_files[0],10,100000,100000,10000,50000,50000,100000);	
	gen(in_files[1],100,100000,100000,1,100000/2,100000/2,100000);	
	gen(in_files[2],1000,100000,100000,1,100000/2,100000/2,100000);	
	gen(in_files[3],1000,100000,100000,10000,50000,50000,100000);	
	gen(in_files[4],99,100000,100000,100,50000,50000,100000);	
	gen(in_files[5],1000,100000,100000,100,50000,50000,100000);	
	return 0;
}
