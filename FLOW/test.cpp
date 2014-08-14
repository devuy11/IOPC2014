#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<algorithm>
using namespace std;
const int T=5;
const int N=100;
struct intervals{
	int s,e;
}A[101];		//as N<=100
int find(int s,int e)
{
	return s+(rand()%(e-s+1));
}
void gen(char file[],int par)
{
	int J,C,array[202],x,a,b,fix=1,vix=1,six=1;
	array[0]=0;
	FILE *fp=fopen(file,"w");	
	fprintf(fp,"%d\n",T);
	for(int i=0;i<T;i++){
		J=find(1,N);
		C=find(3,99997);
		fprintf(fp,"%d %d %d\n",N,J,C);
		for(int j=0;j<2*par;j++){
			//choose 2*par points
			array[j+1]=find(array[j]+100,array[j]+5000000);
			if(j%2==0)
			A[j/2].s=array[j+1];
			else
			A[j/2].e=array[j+1];
		}
		for(int j=par;j<100;j++){
			x=rand()%par;
			a=find(A[x].s+2,A[x].e-2);
			b=find(A[x].s+2,A[x].e-2);
			if(a==b){
				b=a+1;
			}
			else{
				if(a>b){
					swap(a,b);
				}
			}
                        A[j].s=a;
                        A[j].e=b;
		}
		random_shuffle(A,A+100);
		if(fix){		//larger than case
			fix--;
			for(int j=1;j<=N;j++){
				if(j==J){
					fprintf(fp,"%d %d %d %d\n",find(1,1000000),A[j-1].s,A[j-1].e,find(C+1,1000000));
				}
				else{
					fprintf(fp,"%d %d %d %d\n",find(1,1000000),A[j-1].s,A[j-1].e,find(1,1000000));
				}
			}
		}
		else if(vix){		//exactly equal case
			vix--;
			for(int j=1;j<=N;j++){
                                if(j==J){
                                        fprintf(fp,"%d %d %d %d\n",find(1,1000000),A[j-1].s,A[j-1].e,C);
                                }
                                else{
                                        fprintf(fp,"%d %d %d %d\n",find(1,1000000),A[j-1].s,A[j-1].e,find(1,1000000));
                                }
                        }
		}
		else if(six){
			six--;
			for(int j=1;j<=N;j++){
                        	fprintf(fp,"%d %d %d %d\n",find(1,1000000),A[j-1].s,A[j-1].e,find(1,2));
                        }
		}
		else{			//smaller than case
			for(int j=1;j<=N;j++){
                                if(j==J){
                                        fprintf(fp,"%d %d %d %d\n",find(1,1000000),A[j-1].s,A[j-1].e,find(1,C-1));
                                }
                                else{
                                        fprintf(fp,"%d %d %d %d\n",find(1,1000000),A[j-1].s,A[j-1].e,find(1,1000000));
                                }
                        }
		}
	}
	fclose(fp);
}
void same(char file[])
{
	int J,C,x,a,b,fix=1,vix=1,dec1=find(1,100),dec2=find(10000000,100000000),six=1;;
	FILE *fp=fopen(file,"w");	
	fprintf(fp,"%d\n",T);
	for(int i=0;i<T;i++){
		J=find(1,N);
		C=find(3,99997);
		fprintf(fp,"%d %d %d\n",N,J,C);
		for(int j=0;j<100;j++){
                        A[j].s=dec1;
                        A[j].e=dec2;
		}
		if(fix){		//larger than case
			fix--;
			for(int j=1;j<=N;j++){
				if(j==J){
					fprintf(fp,"%d %d %d %d\n",find(1,1000000),A[j-1].s,A[j-1].e,find(C+1,1000000));
				}
				else{
					fprintf(fp,"%d %d %d %d\n",find(1,1000000),A[j-1].s,A[j-1].e,find(1,1000000));
				}
			}
		}
		else if(vix){		//exactly equal case
			vix--;
			for(int j=1;j<=N;j++){
                                if(j==J){
                                        fprintf(fp,"%d %d %d %d\n",find(1,1000000),A[j-1].s,A[j-1].e,C);
                                }
                                else{
                                        fprintf(fp,"%d %d %d %d\n",find(1,1000000),A[j-1].s,A[j-1].e,find(1,1000000));
                                }
                        }
		}
		else if(six){
                        six--;
                        for(int j=1;j<=N;j++){
                                fprintf(fp,"%d %d %d %d\n",find(1,1000000),A[j-1].s,A[j-1].e,find(1,2));
                        }
                }
		else{			//smaller than case
			for(int j=1;j<=N;j++){
                                if(j==J){
                                        fprintf(fp,"%d %d %d %d\n",find(1,1000000),A[j-1].s,A[j-1].e,find(1,C-1));
                                }
                                else{
                                        fprintf(fp,"%d %d %d %d\n",find(1,1000000),A[j-1].s,A[j-1].e,find(1,1000000));
                                }
                        }
		}
	}
	fclose(fp);
}
int main()
{	
	char in_files[27][20]={"input/input00.txt" ,"input/input01.txt","input/input02.txt","input/input03.txt","input/input04.txt","input/input05.txt","input/input06.txt","input/input07.txt","input/input08.txt","input/input09.txt","input/input10.txt","input/input11.txt","input/input12.txt","input/input13.txt","input/input14.txt","input/input15.txt"};
	gen(in_files[0],100);
	gen(in_files[1],100);
	gen(in_files[2],100);
	gen(in_files[3],100);
	gen(in_files[4],100);
	gen(in_files[5],90);
	gen(in_files[6],80);
	gen(in_files[7],70);
	gen(in_files[8],60);
	gen(in_files[9],50);
	gen(in_files[10],30);
	gen(in_files[11],10);
	gen(in_files[12],1);
	same(in_files[13]);
	return 0;
}
