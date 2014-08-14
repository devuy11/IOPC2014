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
int find(int s,int e)
{
	return s+(rand()%(e-s+1));
}
void gen(char file[],int N,int Q,int ds,int de,int up,int q,int r)
{
	FILE *fp=fopen(file,"w");
	int x,y,d,flag=0;
	fprintf(fp,"%d %d\n",N,Q);
	while(Q--){
		x=rand()%N;
		y=rand()%N;
		x++;
		y++;
		if(x>y)	swap(x,y);
		d=find(ds,de);
		if(r){
			if(rand()%2)
				fprintf(fp,"U %d %d %d\n",x,y,d);
			else
				fprintf(fp,"Q %d %d\n",x,y);
		}
		else if(up){
			fprintf(fp,"U %d %d %d\n",x,y,d);
		}
		else if(q){
			fprintf(fp,"Q %d %d\n",x,y);
		}
		else{
			if(flag)		
				fprintf(fp,"U %d %d %d\n",x,y,d);
			else	
				fprintf(fp,"Q %d %d\n",x,y);
			flag=flag^1;
		}
	}
	fclose(fp);
}
int main()
{
	char in_files[27][20]={"input/input00.txt" ,"input/input01.txt","input/input02.txt","input/input03.txt","input/input04.txt","input/input05.txt","input/input06.txt","input/input07.txt","input/input08.txt","input/input09.txt","input/input10.txt","input/input11.txt","input/input12.txt","input/input13.txt","input/input14.txt","input/input15.txt"};
	gen(in_files[0],1e5,1e5,1,1e2,0,0,1);		//random
	gen(in_files[1],1e5,1e5,1,1e2,1,0,0);		//only update
	gen(in_files[2],1e5,1e5,1,1e2,0,1,0);		//only query
	gen(in_files[3],1e5,1e5,1,1e2,0,0,0);		//alternate update and query
	gen(in_files[4],1e5,1e5,90,99,0,0,0);		//alternate update and query
	gen(in_files[5],1e5,1e5,1e2,1e2,0,0,0);		//alternate update and query
	return 0;
}
