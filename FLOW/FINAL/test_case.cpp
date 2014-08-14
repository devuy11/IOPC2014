#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<algorithm>
#include<string.h>
using namespace std;
#define ds 1
#define de 10000
#define ts 1
#define te 1000000000
const int T=5;

int MAT[101][101];
struct graph{
	int st[10001],end[10001],M,Di[10001];
}A;
struct SE{
	int s[101],e[101],x[101],p[101];
}SE;
int find(int s,int e)
{
	assert(s<=e);
	return s+(rand()%(e-s+1));
}
struct intervals{
	int s,e;
}A1[101];		//as N<=100
void geng(int N,char file[],int par,int z)
{
	int J,C,array[202],x,a,b,fix=1,vix=1,six=1;
	array[0]=0;
	FILE *fp=fopen(file,"w");	
	fprintf(fp,"%d\n",T);
	for(int i=0;i<T;i++){
		J=find(1,N);
		C=find(3,99997);
		fprintf(fp,"%d %d %d %d %d\n",N,N*(N-1),J,C,z);	//V=0
		for(int j=0;j<2*par;j++){
			//choose 2*par points
			array[j+1]=find(array[j]+100,array[j]+5000000);
			if(j%2==0)
				A1[j/2].s=array[j+1];
			else
				A1[j/2].e=array[j+1];
		}
		for(int j=par;j<100;j++){
			x=rand()%par;
			a=find(A1[x].s+2,A1[x].e-2);
			b=find(A1[x].s+2,A1[x].e-2);
			if(a==b){
				b=a+1;
			}
			else{
				if(a>b){
					swap(a,b);
				}
			}
			A1[j].s=a;
			A1[j].e=b;
		}
		random_shuffle(A1,A1+100);
		if(fix){		//larger than case
			fix--;
			for(int j=1;j<=N;j++){
				if(j==J){
					fprintf(fp,"%d %d %d %d\n",find(1,1000000),A1[j-1].s,A1[j-1].e,find(C+1,1000000));
				}
				else{
					fprintf(fp,"%d %d %d %d\n",find(1,1000000),A1[j-1].s,A1[j-1].e,find(1,1000000));
				}
			}
		}
		else if(vix){		//exactly equal case
			vix--;
			for(int j=1;j<=N;j++){
				if(j==J){
					fprintf(fp,"%d %d %d %d\n",find(1,1000000),A1[j-1].s,A1[j-1].e,C);
				}
				else{
					fprintf(fp,"%d %d %d %d\n",find(1,1000000),A1[j-1].s,A1[j-1].e,find(1,1000000));
				}
			}
		}
		else if(six){
			six--;
			for(int j=1;j<=N;j++){
				fprintf(fp,"%d %d %d %d\n",find(1,1000000),A1[j-1].s,A1[j-1].e,find(1,2));
			}
		}
		else{			//smaller than case
			for(int j=1;j<=N;j++){
				if(j==J){
					fprintf(fp,"%d %d %d %d\n",find(1,1000000),A1[j-1].s,A1[j-1].e,find(1,C-1));
				}
				else{
					fprintf(fp,"%d %d %d %d\n",find(1,1000000),A1[j-1].s,A1[j-1].e,find(1,1000000));
				}
			}
		}
		for(int i1=1;i1<=N;i1++){
			for(int j1=1;j1<=N;j1++){
				if(i1==j1)        continue;
				fprintf(fp,"%d %d %d\n",i1,j1,find(1,1000));
			}
		}
	}
	fclose(fp);
}
void same(int N,char file[])
{
	int J,C,x,a,b,fix=1,vix=1,dec1=find(1,100),dec2=find(10000000,100000000),six=1;;
	FILE *fp=fopen(file,"w");	
	fprintf(fp,"%d\n",T);
	for(int i=0;i<T;i++){
		J=find(1,N);
		C=find(3,99997);
		fprintf(fp,"%d %d %d %d 0\n",N,N*(N-1),J,C);	//V=0
		for(int j=0;j<100;j++){
			A1[j].s=dec1;
			A1[j].e=dec2;
		}
		if(fix){		//larger than case
			fix--;
			for(int j=1;j<=N;j++){
				if(j==J){
					fprintf(fp,"%d %d %d %d\n",find(1,1000000),A1[j-1].s,A1[j-1].e,find(C+1,1000000));
				}
				else{
					fprintf(fp,"%d %d %d %d\n",find(1,1000000),A1[j-1].s,A1[j-1].e,find(1,1000000));
				}
			}
		}
		else if(vix){		//exactly equal case
			vix--;
			for(int j=1;j<=N;j++){
				if(j==J){
					fprintf(fp,"%d %d %d %d\n",find(1,1000000),A1[j-1].s,A1[j-1].e,C);
				}
				else{
					fprintf(fp,"%d %d %d %d\n",find(1,1000000),A1[j-1].s,A1[j-1].e,find(1,1000000));
				}
			}
		}
		else if(six){
			six--;
			for(int j=1;j<=N;j++){
				fprintf(fp,"%d %d %d %d\n",find(1,1000000),A1[j-1].s,A1[j-1].e,find(1,2));
			}
		}
		else{			//smaller than case
			for(int j=1;j<=N;j++){
				if(j==J){
					fprintf(fp,"%d %d %d %d\n",find(1,1000000),A1[j-1].s,A1[j-1].e,find(1,C-1));
				}
				else{
					fprintf(fp,"%d %d %d %d\n",find(1,1000000),A1[j-1].s,A1[j-1].e,find(1,1000000));
				}
			}
		}
		for(int i1=1;i1<=N;i1++){
                        for(int j1=1;j1<=N;j1++){
                                if(i1==j1)        continue;
                                fprintf(fp,"%d %d %d\n",i1,j1,find(1,10));
                        }
                }
	}
	fclose(fp);
}
void print(char file[],int N,int J,int C,int V)
{
	FILE *fp=fopen(file,"a");
	fprintf(fp,"%d %d %d %d %d\n",N,A.M,J,C,V);
	for(int i=0;i<N;i++){
		fprintf(fp,"%d %d %d %d\n",SE.x[i],SE.s[i],SE.e[i],SE.p[i]);
	}
	for(int i=0;i<A.M;i++){
		fprintf(fp,"%d %d %d\n",A.st[i],A.end[i],A.Di[i]);
	}
	fclose(fp);
}
void G0(int N,int M)		//N,M randomly generated
{
	int x,y;
	memset(MAT,0,sizeof(MAT));
	A.M=M;
	for(int i=0;i<M;i++){
		while(1){
			x=find(1,N);
			y=find(1,N);
			while(x==y){
				x=find(1,N);
				y=find(1,N);
			}
			if(MAT[x][y]==0){
				MAT[x][y]=1;
				A.st[i]=x;
				A.end[i]=y;
				A.Di[i]=find(ds,de);
				break;
			}
		}
	}
}
void G1(int N,int chain)		//tree with chain length chain
{
	int M=2*(N-1);
	int c=0,z=0;
	A.M=M;
	for(int i=1;i<chain;i++){
		A.st[c]=i;
		A.end[c]=i+1;
		A.Di[c]=find(ds,de);
		c++;
		A.st[c]=i+1;
		A.end[c]=i;
		A.Di[c]=A.Di[c-1];
		c++;
	}
	for(int i=chain;i<N;i++){
		z=(rand()%i)+1;
		A.st[c]=i+1;
		A.end[c]=z;
		A.Di[c]=find(ds,de);
		c++;

		A.st[c]=z;
		A.end[c]=i+1;
		A.Di[c]=A.Di[c-1];
		c++;
	}	
	assert(c==M);
}
void G2(int N)	//cycle of N vertices
{
	int M=N,c=0;
	for(int i=1;i<=N;i++){
		A.st[c]=i;
		A.end[c]=(i)%N+1;
		A.Di[c]=find(ds,de);
		c++;
		A.st[c]=A.end[c-1];
		A.end[c]=A.st[c-1];
		A.Di[c]=A.Di[c-1];
		c++;	
	}
	A.M=2*N;
}

void G3(int N)	//complete graph
{
	int c=0;
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			A.st[c]=i;
			A.end[c]=j;
			A.Di[c]=find(ds,de);
			c++;
		}
	}
	A.M=N*N;
	assert(c==N*N);
}

void G4(int x,int y)
{
	int M=2*x+2*(y-1)+2,c=0,N=x+y;
	/*************x nodes cycle******************/
	for(int i=1;i<=x;i++){
		A.st[c]=i;
		A.end[c]=(i)%x+1;
		A.Di[c]=find(ds,de);
		c++;
		A.st[c]=A.end[c-1];
		A.end[c]=A.st[c-1];
		A.Di[c]=A.Di[c-1];
		c++;
	}
	/*************x nodes cycle******************/


	/************y nodes tree*******************/	//st line
	for(int j=x+1;j<N;j++){
		A.st[c]=j;
		A.end[c]=j+1;
		A.Di[c]=find(ds,de);
		c++;

		A.st[c]=j+1;
		A.end[c]=j;
		A.Di[c]=A.Di[c-1];
		c++;	
	}
	/************y nodes tree*******************/
	A.st[c]=find(1,x);
	A.end[c]=find(x+1,N);
	A.Di[c]=find(ds,de);
	c++;

	A.st[c]=A.end[c-1];
	A.end[c]=A.st[c-1];
	A.Di[c]=find(ds,de);
	c++;

	A.M=c;
	assert(c==M);
}
void G5(int N)		//st chain
{
	int c=0;
	A.M=2*(N-1);
	for(int j=1;j<N;j++){
		A.st[c]=j;
		A.end[c]=j+1;
		A.Di[c]=find(ds,de);
		c++;

		A.st[c]=j+1;
		A.end[c]=j;
		A.Di[c]=A.Di[c-1];
		c++;
	}
	assert(c==A.M);
}
void G6(int N,int t)		//1 node t nodes 4 cycles
{
	int c=0,M=8*t+8;
	assert(4*t+1 <= N);
	A.M=M;
	for(int i=1;i<=t;i++){
		A.st[c]=i;
		A.end[c]=(i)%t+1;
		A.Di[c]=find(ds,de);
		c++;
		A.st[c]=A.end[c-1];
		A.end[c]=A.st[c-1];
		A.Di[c]=A.Di[c-1];
		c++;
	}
	for(int i=t+1;i<=2*t;i++){
		A.st[c]=i;
		A.end[c]=(i)%t + t+1;
		A.Di[c]=find(ds,de);
		c++;
		A.st[c]=A.end[c-1];
		A.end[c]=A.st[c-1];
		A.Di[c]=A.Di[c-1];
		c++;
	}
	for(int i=2*t+1;i<=3*t;i++){
		A.st[c]=i;
		A.end[c]=(i)%t + 2*t+1;
		A.Di[c]=find(ds,de);
		c++;
		A.st[c]=A.end[c-1];
		A.end[c]=A.st[c-1];
		A.Di[c]=A.Di[c-1];
		c++;
	}
	for(int i=3*t+1;i<=4*t;i++){
		A.st[c]=i;
		A.end[c]=(i)%t + 3*t+1;
		A.Di[c]=find(ds,de);
		c++;
		A.st[c]=A.end[c-1];
		A.end[c]=A.st[c-1];
		A.Di[c]=A.Di[c-1];
		c++;
	}
	//8 edges Now
	A.st[c]=N;
	A.end[c]=find(1,t);
	A.Di[c]=find(ds,de);
	c++;

	A.st[c]=A.end[c-1];
	A.end[c]=A.st[c-1];
	A.Di[c]=A.Di[c-1];
	c++;


	A.st[c]=N;
	A.end[c]=find(1+t,2*t);
	A.Di[c]=find(ds,de);
	c++;

	A.st[c]=A.end[c-1];
	A.end[c]=A.st[c-1];
	A.Di[c]=A.Di[c-1];
	c++;


	A.st[c]=N;
	A.end[c]=find(1+2*t,3*t);
	A.Di[c]=find(ds,de);
	c++;

	A.st[c]=A.end[c-1];
	A.end[c]=A.st[c-1];
	A.Di[c]=A.Di[c-1];
	c++;



	A.st[c]=N;
	A.end[c]=find(1+3*t,4*t);
	A.Di[c]=find(ds,de);
	c++;

	A.st[c]=A.end[c-1];
	A.end[c]=A.st[c-1];
	A.Di[c]=A.Di[c-1];
	c++;
}
void G7(int N,int t)	//5 cycle
{
	assert(5*t<=N);
	int c=0,M=10*t+5;
	for(int i=1;i<=t;i++){
		A.st[c]=i;
		A.end[c]=(i)%t+1;
		A.Di[c]=find(ds,de);
		c++;
		A.st[c]=A.end[c-1];
		A.end[c]=A.st[c-1];
		A.Di[c]=A.Di[c-1];
		c++;
	}
	A.st[c]=1;
	A.end[c]=t/2;
	A.Di[c]=find(ds,de);
	c++;
	A.st[c]=A.end[c-1];
	A.end[c]=A.st[c-1];
	A.Di[c]=A.Di[c-1];
	c++;
	for(int i=t+1;i<=2*t;i++){
		A.st[c]=i;
		A.end[c]=(i)%t + t+1;
		A.Di[c]=find(ds,de);
		c++;
		A.st[c]=A.end[c-1];
		A.end[c]=A.st[c-1];
		A.Di[c]=A.Di[c-1];
		c++;
	}
	A.st[c]=t+1;
	A.end[c]=t+t/2;
	A.Di[c]=find(ds,de);
	c++;
	A.st[c]=A.end[c-1];
	A.end[c]=A.st[c-1];
	A.Di[c]=A.Di[c-1];
	c++;
	for(int i=2*t+1;i<=3*t;i++){
		A.st[c]=i;
		A.end[c]=(i)%t + 2*t+1;
		A.Di[c]=find(ds,de);
		c++;
		A.st[c]=A.end[c-1];
		A.end[c]=A.st[c-1];
		A.Di[c]=A.Di[c-1];
		c++;
	}
	A.st[c]=2*t+1;
	A.end[c]=2*t+t/2;
	A.Di[c]=find(ds,de);
	c++;
	A.st[c]=A.end[c-1];
	A.end[c]=A.st[c-1];
	A.Di[c]=A.Di[c-1];
	c++;
	for(int i=3*t+1;i<=4*t;i++){
		A.st[c]=i;
		A.end[c]=(i)%t + 3*t+1;
		A.Di[c]=find(ds,de);
		c++;
		A.st[c]=A.end[c-1];
		A.end[c]=A.st[c-1];
		A.Di[c]=A.Di[c-1];
		c++;
	}
	A.st[c]=3*t+1;
	A.end[c]=3*t+t/2;
	A.Di[c]=find(ds,de);
	c++;
	A.st[c]=A.end[c-1];
	A.end[c]=A.st[c-1];
	A.Di[c]=A.Di[c-1];
	c++;
	for(int i=4*t+1;i<=5*t;i++){
		A.st[c]=i;
		A.end[c]=(i)%t + 4*t+1;
		A.Di[c]=find(ds,de);
		c++;
		A.st[c]=A.end[c-1];
		A.end[c]=A.st[c-1];
		A.Di[c]=A.Di[c-1];
		c++;
	}
	A.st[c]=4*t+1;
	A.end[c]=4*t+t/2;
	A.Di[c]=find(ds,de);
	c++;
	A.st[c]=A.end[c-1];
	A.end[c]=A.st[c-1];
	A.Di[c]=A.Di[c-1];
	c++;
}
void rSE(int N,int ss,int ee,int P,int J)
{
	int c=0,x,y,profit;
	for(int i=0;i<N;i++){
		x=find(ss,ee);
		y=find(ss,ee);
		while(x==y){
			x=find(ss,ee);
			y=find(ss,ee);
		}
		if(x>y)	swap(x,y);
		SE.s[c]=x;
		SE.e[c]=y;
		if(c==J-1){
			profit=P;
		}
		else	profit=find(1,1000000);
		SE.p[c]=profit;
		SE.x[c]=find(1,1000000);
		c++;
	}
}
void Algo1(int N,int P,int J)
{
	int c=0;
	int profit;
	for(int i=ts;i<=te;i+=10000000){
		SE.s[c]=find(i,i+10000000-10);
		SE.e[c]=find(SE.s[c],i+10000000-1);
		if(c==J-1){
			profit=P;
		}
		else    profit=find(1,1000000);
		SE.p[c]=profit;
		SE.x[c]=find(1,1000000);
		c++;
	}
}
void Algo2(int N,int P,int J)
{
	int x=find(ts,(ts+te)/2);
	int y=find((ts+te)/2 + 2, te);
	int profit;
	for(int i=0;i<N;i++){
		SE.s[i]=x;
		SE.e[i]=y;
		if(i==J-1){
			profit=P;
		}
		else    profit=find(1,1000000);
		SE.p[i]=profit;
		SE.x[i]=find(1,1000000);
	}
}
void Algo3(int N,int p,int P,int J)
{
	int Array[101],range=te/p,c=1,z,x,y;
	int profit;
	for(int i=1;i<=te;i+=range){
		Array[c]=i;
		Array[c+1]=i+range-1;
		c+=2;
	}
	c=0;
	for(int i=1;i<=N;i++){
		z=find(1,p);
		//printf("z=%d p=%d %d %d--kata\n",z,p,Array[2*z-1],Array[2*z]);
		assert(Array[2*z-1]<=Array[2*z]-100);
		x=find(Array[2*z-1],Array[2*z]-100);
		y=find(x,Array[2*z]);
		SE.s[c]=x;
		SE.e[c]=y;
		if(c==J-1){
			profit=P;
		}
		else    profit=find(1,1000000);
		SE.p[c]=profit;
		SE.x[c]=find(1,1000000);
		c++;
	}
}
void Algo4(int N,int P,int J)
{
	int Array[102],profit;
	for(int i=1;i<=101;i++){
		Array[i]=i*10;
	}
	for(int i=0;i<N;i++){
		SE.s[i]=Array[i+1];
		SE.e[i]=Array[i+2];
		SE.x[i]=find(1,1000000);
		if(i==J-1)	profit=P;
		else	profit=find(1,100000);	
		SE.p[i]=profit;
	}
}
void gen(char file[],int p,int c,int r,int algo)
{	
	int N=100,C,J,M,V,x,y;
	FILE *fp=fopen(file,"w");
	fprintf(fp,"%d\n",T);
	fclose(fp);
	if(r){
		M=find(1,400);
		//printf("%d is M\n",M);
		G0(N,M);
		assert(M==A.M);
		C=find(100,100000);
		J=find(1,N);
		if(p>c)		rSE(N,ts,te,find(C+1,1000000),J);
		else if(p<c)	rSE(N,ts,te,find(1,C-1),J);
		else		rSE(N,ts,te,C,J);
		V=find(1,10);
		print(file,N,J,C,V);
		assert(M==A.M);


		G1(N,find(1,N/2));
		C=find(100,100000);
		J=find(1,N);
		if(p>c)         rSE(N,ts,te,find(C+1,1000000),J);
		else if(p<c)    rSE(N,ts,te,find(1,C-1),J);
		else            rSE(N,ts,te,C,J);
		V=find(1,10);
		print(file,N,J,C,V);


		G2(N);
		C=find(100,100000);
		J=find(1,N);
		if(p>c)         rSE(N,ts,te,find(C+1,1000000),J);
		else if(p<c)    rSE(N,ts,te,find(1,C-1),J);
		else            rSE(N,ts,te,C,J);
		V=find(1,10);
		print(file,N,J,C,V);


		G3(N);
		C=find(100,100000);
		J=find(1,N);
		if(p>c)         rSE(N,ts,te,find(C+1,1000000),J);
		else if(p<c)    rSE(N,ts,te,find(1,C-1),J);
		else            rSE(N,ts,te,C,J);
		V=find(1,10);
		print(file,N,J,C,V);


		x=find(2,N/2);
		y=N-x;
		G4(x,y);
		C=find(100,100000);
		J=find(1,N);
		if(p>c)         rSE(N,ts,te,find(C+1,1000000),J);
		else if(p<c)    rSE(N,ts,te,find(1,C-1),J);
		else            rSE(N,ts,te,C,J);
		V=find(1,10);
		print(file,N,J,C,V);		

	}
	else{
		M=find(1,400);
		G0(N,M);
		C=find(100,100000);
		J=find(1,N);
		if(algo==0)	rSE(N,1,10000,find(1,C-1),J);
		V=find(1,10);
		print(file,N,J,C,V);


		G1(N,find(1,N/2));
		C=find(100,100000);
		J=find(1,N);
		if(algo==1)	Algo1(N,find(1,C-1),J);
		V=find(1,10);
		print(file,N,J,C,V);


		G2(N);
		C=find(100,100000);
		J=find(1,N);
		if(algo==2)	Algo2(N,find(1,C-1),J);
		V=find(1,10);
		print(file,N,J,C,V);


		G3(N);
		C=find(100,100000);
		J=find(1,N);
		if(algo==3)	Algo3(N,find(10,50),find(1,C-1),J);
		V=find(1,10);
		print(file,N,J,C,V);


		x=find(2,N/2);
		y=N-x;
		G4(x,y);
		C=find(100,100000);
		J=find(1,N);
		if(algo==4)	Algo4(N,find(1,C-1),J);
		V=find(1,10);
		print(file,N,J,C,V);
	}	
}
void cgen(char file[],int p,int c,int r,int algo)
{	
	int N=100,C,J,M,V,x,y;
	FILE *fp=fopen(file,"w");
	fprintf(fp,"%d\n",T);
	fclose(fp);
	if(r){
		G5(N);
		C=find(100,100000);
		J=find(1,N);
		if(p>c)		rSE(N,ts,te,find(C+1,1000000),J);
		else if(p<c)	rSE(N,ts,te,find(1,C-1),J);
		else		rSE(N,ts,te,C,J);
		V=find(1,10);
		print(file,N,J,C,V);

		N=97;
		G6(N,24);
		C=find(100,100000);
		J=find(1,N);
		if(p>c)         rSE(N,ts,te,find(C+1,1000000),J);
		else if(p<c)    rSE(N,ts,te,find(1,C-1),J);
		else            rSE(N,ts,te,C,J);
		V=find(1,10);
		print(file,N,J,C,V);
		N=100;

		G7(N,N/5);
		C=find(100,100000);
		J=find(1,N);
		if(p>c)         rSE(N,ts,te,find(C+1,1000000),J);
		else if(p<c)    rSE(N,ts,te,find(1,C-1),J);
		else            rSE(N,ts,te,C,J);
		V=find(1,10);
		print(file,N,J,C,V);


		x=find(2,N/2);
		y=N-x;
		G4(x,y);
		C=find(100,100000);
		J=find(1,N);
		if(p>c)         rSE(N,ts,te,find(C+1,1000000),J);
		else if(p<c)    rSE(N,ts,te,find(1,C-1),J);
		else            rSE(N,ts,te,C,J);
		V=find(1,10);
		print(file,N,J,C,V);


		x=find(2,N/2);
		y=N-x;
		G4(x,y);
		C=find(100,100000);
		J=find(1,N);
		if(p>c)         rSE(N,ts,te,find(C+1,1000000),J);
		else if(p<c)    rSE(N,ts,te,find(1,C-1),J);
		else            rSE(N,ts,te,C,J);
		V=find(1,10);
		print(file,N,J,C,V);		

	}
	else{
		G5(N);
		C=find(100,100000);
		J=find(1,N);
		if(algo==0)	rSE(N,1,10000,find(1,C-1),J);
		V=find(1,10);
		print(file,N,J,C,V);

		N=97;
		G6(N,24);
		C=find(100,100000);
		J=find(1,N);
		if(algo==1)	Algo1(N,find(1,C-1),J);
		V=find(1,10);
		print(file,N,J,C,V);
		N=100;

		G7(N,N/5);
		C=find(100,100000);
		J=find(1,N);
		if(algo==2)	Algo2(N,find(1,C-1),J);
		V=find(1,10);
		print(file,N,J,C,V);


		x=find(2,N/2);
		y=N-x;
		G4(x,y);
		C=find(100,100000);
		J=find(1,N);
		if(algo==3)	Algo3(N,find(10,50),find(1,C-1),J);
		V=find(1,10);
		print(file,N,J,C,V);


		x=find(2,N/2);
		y=N-x;
		G4(x,y);
		C=find(100,100000);
		J=find(1,N);
		if(algo==4)	Algo4(N,find(1,C-1),J);
		V=find(1,10);
		print(file,N,J,C,V);
	}	
}


int main()
{	
	char in_files[39][20]={"input/input00.txt" ,"input/input01.txt","input/input02.txt","input/input03.txt","input/input04.txt","input/input05.txt","input/input06.txt","input/input07.txt","input/input08.txt","input/input09.txt","input/input10.txt","input/input11.txt","input/input12.txt","input/input13.txt","input/input14.txt","input/input15.txt","input/input16.txt","input/input17.txt","input/input18.txt","input/input19.txt","input/input20.txt","input/input21.txt","input/input22.txt","input/input23.txt","input/input24.txt","input/input25.txt","input/input26.txt","input/input27.txt","input/input28.txt","input/input29.txt","input/input30.txt","input/input31.txt","input/input32.txt","input/input33.txt","input/input34.txt"};
	gen(in_files[0],10,5,1,0);	//pj>c,1 for si,e1 random,0 for algo 0 if not random
	gen(in_files[1],5,10,1,0);	
	gen(in_files[2],5,5,1,0);	
	gen(in_files[3],5,10,0,0);	
	gen(in_files[4],5,10,0,1);	
	gen(in_files[5],5,10,0,2);	
	gen(in_files[6],5,10,0,3);
	gen(in_files[7],5,10,0,4);

	cgen(in_files[8],10,5,1,0);	//pj>c,1 for si,e1 random,0 for algo 0 if not random
	cgen(in_files[9],5,10,1,0);	//pj>c,1 for si,e1 random,0 for algo 0 if not random
	cgen(in_files[10],5,5,1,0);	//pj>c,1 for si,e1 random,0 for algo 0 if not random
	cgen(in_files[11],5,10,1,0);	//pj>c,1 for si,e1 random,0 for algo 0 if not random
	cgen(in_files[12],5,10,1,1);	//pj>c,1 for si,e1 random,0 for algo 0 if not random
	cgen(in_files[13],5,10,1,2);	//pj>c,1 for si,e1 random,0 for algo 0 if not random
	cgen(in_files[14],5,10,1,3);	//pj>c,1 for si,e1 random,0 for algo 0 if not random
	cgen(in_files[15],5,10,1,4);	//pj>c,1 for si,e1 random,0 for algo 0 if not random

	geng(100,in_files[16],100,0);
	geng(100,in_files[17],100,1);
	geng(100,in_files[18],90,0);
	same(100,in_files[19]);

	//gen(in_files[0],10,5,1,0);


	return 0;
}
