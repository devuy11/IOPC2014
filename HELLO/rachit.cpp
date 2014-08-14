#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef double R;
#define db 0
R vc[1001][1001],l[1001],m[1001][1001],m2[1001][1001];
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
void print(int n)
{
	printf("Eigen Values are\n");
	for(int i=0;i<n;i++)	printf("%.6lf ",l[i]);
	printf("\n");
}
int main(){
	int n,x;
	scanf("%d",&n);
	for(int j=0;j<n;j++)
		for(int k=0;k<n;k++){
			scanf("%d",&x);
			m[j][k]=x;
		}
	eigen(n);
	print(n);

	return 0;
}
