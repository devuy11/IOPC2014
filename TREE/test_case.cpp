#include<stdio.h>
#include<algorithm>
#include<stdlib.h>
using namespace std;
int find(int s,int e)
{
        return s+(rand()%(e-s+1));
}
/*void gen(char file[],int S,int N,int Q,int s1,int e1,int s2,int e2)
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
}*/
/*void gen(char file[],int T,int M,int h)		//Test case, Modulo <= M , len--> lenght of the sequence, C -->
{
	FILE *fp = fopen(file,"w");
	fprintf(fp,"%d\n",T);
	for(int i=0;i<T;i++){
		fprintf(fp,"%d %d\n",h,(rand()%M)+1);
		for(int j=0;j<h;j++)	fprintf(fp,"%d ",(rand()%1000000000+1));
		fprintf(fp,"\n");
	}
	fclose(fp);
}*/
void gen(char file[],int N,int T,int M)         //Test case, Modulo <= M , len--> lenght of the sequence, C -->
{
        FILE *fp = fopen(file,"w");
	fprintf(fp,"%d\n",N);
	fprintf(fp,"%d",find(1,1000000000));
	for(int i=2;i<=N;i++){
		fprintf(fp," %d",find(1,1000000000));
	}
	fprintf(fp,"\n");
        fprintf(fp,"%d\n",T);
        for(int i=0;i<T;i++){
                fprintf(fp,"%d %d %d\n",find(1,N/2),find((N/2)+1,N),(rand()%M)+1);
        }
        fclose(fp);
}
void worst(char file[],int N,int T)
{
	int M=0;
	int array[]={16384,32768,40961,49152,49157,65536,65537,81920,81922,98304};
	FILE *fp = fopen(file,"w");
        fprintf(fp,"%d\n",N);
        fprintf(fp,"%d",find(1,1000000000));
        for(int i=2;i<=N;i++){
                fprintf(fp," %d",find(1,1000000000));
        }
        fprintf(fp,"\n");
        fprintf(fp,"%d\n",T);
        for(int i=0;i<T;i++){
                fprintf(fp,"%d %d %d\n",find(1,N/2),find((N/2)+1,N),array[M]);
		M++;
		M%=10;
        }
        fclose(fp);
}
int main()
{
	char in_files[27][20]={"input/input00.txt" ,"input/input01.txt","input/input02.txt","input/input03.txt","input/input04.txt","input/input05.txt","input/input06.txt","input/input07.txt","input/input08.txt","input/input09.txt","input/input10.txt","input/input11.txt","input/input12.txt","input/input13.txt","input/input14.txt","input/input15.txt","input/input16.txt"};
	/*gen(in_files[0],10,100000,100000,10000,50000,50000,100000);	
	gen(in_files[1],100,100000,100000,1,100000/2,100000/2,100000);	
	gen(in_files[2],1000,100000,100000,1,100000/2,100000/2,100000);	
	gen(in_files[3],1000,100000,100000,10000,50000,50000,100000);	
	gen(in_files[4],99,100000,100000,100,50000,50000,100000);	
	gen(in_files[5],1000,100000,100000,100,50000,50000,100000);*/
	gen(in_files[0],100000,100000,100000);
	gen(in_files[1],100000,100000,100000);
	gen(in_files[2],100000,100000,100000);
	gen(in_files[3],100000,100000,100000);
	gen(in_files[4],100000,100000,100000);
	gen(in_files[5],100000,100000,100000);
	gen(in_files[6],100000,100000,100000);
	gen(in_files[7],100000,100000,100000);
	gen(in_files[8],100000,100000,100000);
	gen(in_files[9],100000,100000,10000);
	gen(in_files[10],100000,100000,6);
	gen(in_files[11],100000,100000,5);
	gen(in_files[12],100000,100000,4);
	gen(in_files[13],100000,100000,3);
	gen(in_files[14],100000,100000,2);
	gen(in_files[15],100000,100000,1);
	worst(in_files[16],100000,100000);
	return 0;
}
