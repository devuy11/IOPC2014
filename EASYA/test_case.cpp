#include<stdio.h>
#include<algorithm>
#include<stdlib.h>
using namespace std;
typedef long long int ll;
int find(int s,int e)
{
        return s+(rand()%(e-s+1));
}
void random(char file[],int as,int ae,int bs,int be)
{
	FILE *fp=fopen(file,"w");
	fprintf(fp,"100\n");
	for(int i=0;i<100;i++){
		fprintf(fp,"%d %lld\n",find(as,ae),(ll)find(bs,be)*(ll)find(bs,be));
	}
	fclose(fp);
}
int prime[]={2,15485863,982450673,982450687,982450697,982450741,982450753,982450769,982450787,982450801,982450829,982450849,982450871,982450913,982450921,982450943,982450967,982450981,982450999,982451023,982451081,982451087,982451111,982451123,982451159,982451161,982451179,982451191,982451219,982451227,982451231,982451243,982451321,982451333,982451359,982451383,982451419,982451429,982451443,982451467,982451479,982451497,982451501,982451549,982451567,982451579,982451581,982451609,982451629,982451653};
void over_flow(char file[])
{
	FILE *fp=fopen(file,"w");
        fprintf(fp,"100\n");
        for(int i=0;i<50;i++){
                fprintf(fp,"%d %lld\n",find(1e4,1e5),(ll)prime[i]*(ll)prime[i]);
                fprintf(fp,"%d %lld\n",find(1e4,1e5),(ll)prime[i]*(ll)prime[(i+1)%50]);
        }
        fclose(fp);
}
void tricky(char file[])
{
	FILE *fp=fopen(file,"w");
        fprintf(fp,"100\n");
	for(int i=0;i<=9;i++){
		for(int j=1;j<=10;j++){
			fprintf(fp,"%d %d\n",i,j);
		}
	}
	fclose(fp);
}
void strong_prime(char file[],ll v)
{
	FILE *fp=fopen(file,"w");
        fprintf(fp,"100\n");
	for(int i=1;i<=100;i++){
		fprintf(fp,"%d %lld\n",(rand()%100000)+1,v);
	}
        fclose(fp);
}
int main()
{
	char in_files[27][20]={"input/input00.txt" ,"input/input01.txt","input/input02.txt","input/input03.txt","input/input04.txt","input/input05.txt","input/input06.txt","input/input07.txt","input/input08.txt","input/input09.txt","input/input10.txt","input/input11.txt","input/input12.txt","input/input13.txt","input/input14.txt","input/input15.txt"};
	random(in_files[0],1e4,1e5,1e8*5,1e9);
	random(in_files[1],1e4,1e5,1e8*5,1e9);
	random(in_files[2],1,1e2,1,1e2);
	over_flow(in_files[3]);
	tricky(in_files[4]);		//manually type coded
	strong_prime(in_files[5],1693182318746371L);
	return 0;
}
