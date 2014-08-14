#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
#include <math.h>
using namespace std;
#define MaxN 51
#define MaxM 130
#define chutiyap 0
#define MaxR 144
#define AFTER 48
#define db 0
typedef double R;

int N,M,Q,F,addo,distinct=0,total,minwala;
R Fuck;
int T[MaxN][MaxN],counter;
int Res[MaxN][MaxN],maxmax;
int visited[MaxN],mapping[MaxN];
int pre_graph[MaxN][MaxN];
int new_graph[AFTER*MaxM+MaxN][AFTER*MaxM+MaxN];
int degree[AFTER*MaxM+MaxN];

int gcd(int a,int b)
{
	if(b==0)	return a;
	return gcd(b,a%b);
}

/*---------------------------------------------------------------*/
R vc[AFTER*MaxM+MaxN][AFTER*MaxM+MaxN],l[AFTER*MaxM+MaxN],m[AFTER*MaxM+MaxN][AFTER*MaxM+MaxN],m2[AFTER*MaxM+MaxN][AFTER*MaxM+MaxN];

void print(int n)
{
        printf("Eigen Values are\n");
        for(int i=0;i<n;i++)    printf("%.6lf ",l[i]);
        printf("\n");
}
void twst_m2(int n,R c,R &t,R s,int i,int j)
{
	int k=n; 
	while(k--)
	{
		t = c*m2[i][k]+s*m2[j][k];
		m2[j][k] = -s*m2[i][k]+c*m2[j][k]; 
		m2[i][k] = t;
	}
}
void twst_vc(int n,R c,R &t,R s,int i,int j)
{
	int k=n; 
	while(k--)
	{
		t = c*vc[i][k]+s*vc[j][k];
		vc[j][k] = -s*vc[i][k]+c*vc[j][k]; 
		vc[i][k] = t;
	}
}
void eigen(int n)
{
	{
		int i=n; 
		while(i--) 
		{
			int j=n; 
			while(j--) 
			{
				m2[i][j] = m[i][j]; 
				vc[i][j] = i==j;
			}
		}
	}
	while(1)
	{
		R mod = 0; int i=0, j=0;
		{
			int k=n; 
			while(k--)
			{
				int m=n; 
				while((--m)>k)
				{
					R q = fabs(m2[k][m]);
					if(q > mod) 
					{
						mod=q; i=k; j=m;
					}
				}
			}
		}
		if(mod < 0.00000000001) break;
		if(db) printf("mii=%e, mjj=%e\n", m2[i][i], m2[j][j]);
		R th = 0.5*atan(2*m2[i][j]/(m2[i][i] - m2[j][j]));
		if(db) printf("th=%e, i=%d, j=%d\n", th, i, j);
		{
			R c = cos(th), s = sin(th);
			int k;
			R t;
			{
				k=n; 
				while(k--)
				{
					t = c*m2[k][i] + s*m2[k][j];
					m2[k][j] = -s*m2[k][i] + c*m2[k][j]; m2[k][i]=t;
				}
			}
			twst_m2(n,c,t,s,i,j); twst_vc(n,c,t,s,i,j);
		}
	}
	{
		int j=n; 
		while(j--) 
			l[j] = m2[j][j];
	}
}
/*---------------------------------------------------------------*/

void dfs(int root)
{
	visited[root]=1;
	for(int i=0;i<MaxN;i++){
		if(pre_graph[root][i]==1 && visited[i]==0){
			dfs(i);
		}
	}
}


void DO_IT()
{
	Fuck=0;
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if(visited[i] && visited[j])
				Fuck = Fuck + ((double)T[i][j] *(double)Res[i][j]);
		}
	}
	Fuck=Fuck/(double)maxmax;
	if(chutiyap)	printf("Fuck %lf\n",Fuck);
}

void create_it_man()
{
	total=addo+distinct;
	if(chutiyap)	printf("%d %d %d ---- TOTAL ADDO DISTINCT\n",total,addo,distinct);
	counter=distinct;
	int curr;
	int u,v,rv;
	memset(degree,0,sizeof(degree));
	for(int i=0;i<N;i++){
		for(int j=0;j<i;j++){
			if(visited[i] && visited[j]  && Res[i][j]>0){	//both are in the same componenti
				u=mapping[i];	
				v=mapping[j];
				if(chutiyap)	printf("%d %d is u and v\n",u,v);
				rv=maxmax/Res[i][j];
				rv--;
				for(int i=1;i<rv;i++){
					new_graph[counter+i][counter+i-1]=1,new_graph[counter+i-1][counter+i]=1;
					degree[counter+i]++;
					degree[counter+i-1]++;
				}
				degree[u]++;degree[v]++;
				if(rv==0){
					new_graph[u][v]=new_graph[v][u]=1;
				}
				else{	
					new_graph[u][counter]=new_graph[counter][u]=1;
					new_graph[v][counter+rv-1]=new_graph[counter+rv-1][v]=1;
					if(chutiyap)	printf("%d is counter\n",counter);
					degree[counter]++;
					degree[counter+rv-1]++;
				}
				counter=counter+rv;
			}
		}
	}
	if(chutiyap)	printf("%d is  counter outside\n",counter);
	for(int i=0;i<counter;i++){
		for(int j=0;j<counter;j++){
			if(chutiyap)	printf("%d ",new_graph[i][j]);
			if(i==j){
				m[i][j]=degree[i];
			}
			else if(new_graph[i][j]==1){
				m[i][j]=-1;
			}
			else{
				m[i][j]=0;
			}
		}
		if(chutiyap)	printf("\n");
	}
	if(chutiyap)
	for(int i=0;i<counter;i++){
		for(int j=0;j<counter;j++)	printf("%.1lf ",m[i][j]);
		printf("\n");
	}
	eigen(counter);
	if(chutiyap)	print(counter);
	minwala=0;
	for(int i=1;i<counter;i++){
		if(l[i]<l[minwala])	minwala=i;
	}
}
void ANSWER_KARO_BE(int i,int j)
{
	R answer=0;
	for(int k=0;k<counter;k++){
		if(k==minwala)	continue;
		answer=answer+ (((vc[k][i]-vc[k][j])*(vc[k][i]-vc[k][j]))/l[k]);
	}
	answer=answer*Fuck;
	printf("%.4lf\n",answer);
}
bool solve()
{
	addo=0;
	distinct=0;
	int u,v,r,tuv,tvu;
	scanf("%d%d%d",&N,&M,&Q);
	if(N==0 && M==0 && Q==0)	return false;
	memset(pre_graph,0,sizeof(pre_graph));
	memset(Res,0,sizeof(Res));
	maxmax=0;
	for(int i=0;i<M;i++){
		scanf("%d%d%d%d%d",&u,&v,&r,&tuv,&tvu);
		if(maxmax==0)	maxmax=r;
		else	maxmax=maxmax*r/gcd(maxmax,r);
		u--;
		v--;
		pre_graph[u][v]=pre_graph[v][u]=1;
		T[u][v]=tuv;
		T[v][u]=tvu;
		Res[u][v]=Res[v][u]=r;
		addo=addo+r-1;
	}
	memset(visited,0,sizeof(visited));
	dfs(0);
	for(int i=0;i<MaxN;i++){
		mapping[i]=distinct;
		if(visited[i])	distinct++;
	}
	memset(new_graph,0,sizeof(new_graph));
	DO_IT();		//calculating the constant F.
	create_it_man();	//creating a new graph
	for(int i=0;i<Q;i++){
		scanf("%d",&F);
		if(F==1){
			printf("0.0000\n");
			continue;
		}
		F--;
		if(!visited[F]){
			printf("INFINITE\n");
			continue;
		}
		ANSWER_KARO_BE(0,mapping[F]);
	}
	return true;
}
int main()
{
	bool check=true;
	//scanf("%d",&test);
	while(check){
		check=solve();
	}
	return 0;
}
