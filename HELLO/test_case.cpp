#include<stdio.h>
#include<algorithm>
#include<stdlib.h>
#include<string.h>
using namespace std;
#define ts 1
#define te 100
int R[]={4,12,6,3,16,18};
int mul[51][51];
int find(int s,int e)
{
        return s+(rand()%(e-s+1));
}
void gen(char file[],int S,int N,int Q,int s1,int e1,int s2,int e2)
{
	FILE *fp = fopen(file,"w");
	fclose(fp);
}
void random(char file[],int n,int e)
{
	int x,y;
	FILE *fp = fopen(file,"a");
	memset(mul,0,sizeof(mul));
	fprintf(fp,"%d %d %d\n",n,e,n);
	while(e--){
		while(1){
			x=find(1,n);
			y=find(1,n);
			while(x==y){
				x=find(1,n);
				y=find(1,n);
			}
			if(mul[x][y]!=1){
				mul[x][y]=mul[y][x]=1;
				fprintf(fp,"%d %d %d %d %d\n",x,y,R[find(0,5)],find(ts,te),find(ts,te));
				break;
			}
		}
	}
	for(int i=1;i<=n;i++)	fprintf(fp,"%d\n",i);
	fprintf(fp,"0 0 0\n");
	fclose(fp);
}
void comp(char file[],int s,int e,int n)
{
	FILE *fp = fopen(file,"w");
	int edges=(n*(n-1))>>1;
	for(int i=s;i<=e;i++){
		fprintf(fp,"%d %d %d\n",n,edges,n);
		//edges lines
		for(int j=1;j<=n;j++){
			for(int k=1;k<j;k++){
				fprintf(fp,"%d %d %d %d %d\n",j,k,R[i],find(ts,te),find(ts,te));
			}
		}
		//Q lines
		for(int j=1;j<=n;j++)	fprintf(fp,"%d\n",j);
	}
	fclose(fp);
	random(file,8,20);
}
void comp1(char file[],int s,int e,int n)
{
        FILE *fp = fopen(file,"w");
        int edges=(n*(n-1))>>1;
        for(int i=s;i<=e;i++){
                fprintf(fp,"%d %d %d\n",n,edges,n);
                //edges lines
                for(int j=1;j<=n;j++){
                        for(int k=1;k<j;k++){
                                fprintf(fp,"%d %d 3 %d %d\n",j,k,find(ts,te),find(ts,te));
                        }
                }
                //Q lines
                for(int j=1;j<=n;j++)   fprintf(fp,"%d\n",j);
        }
        fclose(fp);
        random(file,8,20);
}
void equal(char file[],int s,int e,int r,int Ar[],int upto)
{
	int edges,x,y;
	FILE *fp = fopen(file,"w");
	for(int i=0;i<=upto;i++){
		memset(mul,0,sizeof(mul));
		edges=r*(e-s+1);
		fprintf(fp,"%d %d %d\n",Ar[i],edges,Ar[i]);
		//edges lines
		for(int j=s;j<=e;j++){
			for(int k=1;k<=r;k++){
				while(1){
					x=find(1,Ar[i]);
					y=find(1,Ar[i]);
					while(x==y){
						x=find(1,Ar[i]);
						y=find(1,Ar[i]);
					}
					if(mul[x][y]!=1){
						fprintf(fp,"%d %d %d %d %d\n",x,y,R[j],find(1,ts),find(1,te));
						mul[x][y]=mul[y][x]=1;
						break;
					}
				}
			}
		}
		//Ar[i] queries
		for(int j=1;j<=Ar[i];j++)	fprintf(fp,"%d\n",j);
	}
	fprintf(fp,"0 0 0\n");
	fclose(fp);
}
void dis(char file[],int n,int m1)
{
	FILE *fp = fopen(file,"a");
	int edges=(n*(n-1))>>1,node=n+m1;
	fprintf(fp,"%d %d %d\n",node,edges+9,n+m1);
	//edges lines
	for(int j=1;j<=n;j++){
		for(int k=1;k<j;k++){
			fprintf(fp,"%d %d %d %d %d\n",j,k,R[find(0,5)],find(ts,te),find(ts,te));
		}
	}
	fprintf(fp,"15 17 %d %d %d\n",R[find(0,5)],find(ts,te),find(ts,te));
	fprintf(fp,"15 16 %d %d %d\n",R[find(0,5)],find(ts,te),find(ts,te));
	fprintf(fp,"15 18 %d %d %d\n",R[find(0,5)],find(ts,te),find(ts,te));
	fprintf(fp,"15 20 %d %d %d\n",R[find(0,5)],find(ts,te),find(ts,te));
	fprintf(fp,"15 50 %d %d %d\n",R[find(0,5)],find(ts,te),find(ts,te));
	fprintf(fp,"15 26 %d %d %d\n",R[find(0,5)],find(ts,te),find(ts,te));
	fprintf(fp,"15 48 %d %d %d\n",R[find(0,5)],find(ts,te),find(ts,te));
	fprintf(fp,"42 46 %d %d %d\n",R[find(0,5)],find(ts,te),find(ts,te));
	fprintf(fp,"31 35 %d %d %d\n",R[find(0,5)],find(ts,te),find(ts,te));
	for(int i=1;i<=node;i++)	fprintf(fp,"%d\n",i);
	fprintf(fp,"0 0 0\n");
	fclose(fp);
}
int main()
{
	char in_files[27][20]={"input/input00.txt" ,"input/input01.txt","input/input02.txt","input/input03.txt","input/input04.txt","input/input05.txt","input/input06.txt","input/input07.txt","input/input08.txt","input/input09.txt","input/input10.txt","input/input11.txt","input/input12.txt","input/input13.txt","input/input14.txt","input/input15.txt"};
	int A[]={50};		//equal dis
	int B[]={25,25};	//equal dis
	int C[]={40,10};
	comp(in_files[0],0,2,14);
	comp(in_files[1],3,5,14);
	equal(in_files[2],0,5,16,A,0);
	equal(in_files[3],0,5,16,B,1);
	dis(in_files[4],14,36);
	equal(in_files[5],4,5,50,A,0);
	equal(in_files[6],3,5,33,B,1);
	comp1(in_files[7],0,2,14);
	return 0;
}
