/*

                       o                            | |    
_|_       __,   _  _       __   ,_    __,   __, _|_ | |    
 |  |  |_/  |  / |/ |  |  /    /  |  /  |  /  |  |  |/ \
 |_/ \/  \_/|_/  |  |_/|_/\___/   |_/\_/|_/\_/|_/|_/|   |_/

*/

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
#include<cassert>

using namespace std;

typedef long long int ll;
typedef unsigned long long int ull;
typedef vector<int> vi;
typedef pair<int, int> pii;

#define mfor(i,e)	for(int i = 0; i < e; i++)
#define mford(i,s,e)	for(int i = s; i > e; i--)
//#define FORE(i,s,e)	for(typeof(s) i = s; i != e; ++i)
#define mfori(i,s,e)	for(int i = s; i < e; i++)
#define in(x)		(x = getc(stdin))
#define MP			make_pair
#define out(x)		putc(x, stdout)
#define pb			push_back

template <class _T> _T MAX(_T a, _T b){ return a > b ? a : b; }
template <class _T> _T MIN(_T a, _T b){ return a < b ? a : b; }
template <class _T> _T GCD(_T a, _T b){ return b ? GCD(b, a % b) : a; }


const int maxn=55;
const int maxm=105;
const int maxnew=355;
int q,n,m,bkp_t[maxn][maxn],bkp_c[maxn][maxn],c[maxn][maxn],t[maxn][maxn],r[maxn][maxn],mymap[maxn];
vi adj[maxnew];
int maze[maxnew][maxnew],degree[maxnew];
long double F,eigen_vec[maxnew][maxnew],eigen_val[maxnew];
int mat_tree_num[maxnew],map_ind;
int laplace[maxnew][maxnew];

void init()	{
	memset(bkp_t,0,sizeof(bkp_t));
	memset(bkp_c,0,sizeof(bkp_c));
	memset(c,0,sizeof(c));
	memset(t,0,sizeof(t));
	memset(r,0,sizeof(r));
	memset(maze,0,sizeof(maze));
	memset(mat_tree_num,0,sizeof(mat_tree_num));
	memset(degree,0,sizeof(degree));
	for(int i=0;i<55;i++)	mymap[i]=-1;
	for(int i=0;i<55;i++)	adj[i].clear();
	F=0;
	map_ind=0;


}

bool readmat()	{
	scanf("%d %d %d",&n,&m,&q);
	if(n==0)	{
		assert(m==0 && q==0);
		return false;
	}
	int u,v,r,tuv,tvu;	
	for(int i=0;i<m;i++)	{
		scanf("%d %d %d %d %d",&u,&v,&r,&tuv,&tvu);
		u--;
		v--;
		adj[u].pb(v);
		adj[v].pb(u);
		bkp_c[u][v]=r;
		bkp_c[v][u]=r;
		bkp_t[u][v]=tuv;
		bkp_t[v][u]=tvu;
	}
	return true;
}

void mat_dfs(int node, int treenum)	{
	if(mat_tree_num[node])	return;
	mat_tree_num[node]=treenum;
	for(vi::iterator it=adj[node].begin();it!=adj[node].end();it++)	{
		if(!mat_tree_num[*it])	mat_dfs(*it,treenum);
	}
}

bool get_eff_graph()	{
	int tree_count=1;
	for(int i=0;i<n;i++)	{
		if(mat_tree_num[i]) continue;
		mat_dfs(i,tree_count);
		tree_count++;
	}
//mat_tree_num of 0 is ALWAYS 1

	for(int i=0;i<n;i++)	{
		adj[i].clear();
		if(mat_tree_num[i]!=1) continue;
		mymap[map_ind++]=i;
	}

	m=0;
	for(int i=0;i<map_ind;i++)	{
		for(int j=0;j<map_ind;j++)	{
			c[i][j]=bkp_c[mymap[i]][mymap[j]];
			if(c[i][j])	{
				r[i][j]=c[i][j];
		//		printf("%d\n",c[i][j]);
	//			assert(12%c[i][j]==0);
			}
			t[i][j]=bkp_t[mymap[i]][mymap[j]];
			if(c[i][j]) {
//				adj[i].pb(j);		//to be inserted while re constructing the graph
				m++;		
			}
	//		printf("c[%d][%d]=%d\n",i,j,c[i][j]);
		}
	}
	m=m/2;
	n=map_ind;
//	printf("n=%d m=%d\n",n,m);
	return true;
}

void find_F()	{
	F=0.0;
	for(int i=0;i<n;i++)	{
		for(int j=0;j<n;j++)	{
			if(i==j) assert(t[i][j]==0);
//			printf("%d ",t[i][j]);
			F+=(t[i][j]*c[i][j]);
		}
	}
//	printf("\n");
	F=F/12.0;
	//printf("%Lf\n",F);
}

void solve_chandra()	{
	//readmat();
	bool poss=get_eff_graph();
	//if(!poss)	return false;			//1 and n not in same comp / unreachable
	find_F();
	//return true;
}

void add_edge(int i, int j)	{
//	adj[i].pb(j);
//	adj[j].pb(i);
	maze[i][j]=1;
	maze[j][i]=1;
	degree[i]++;
	degree[j]++;
	assert(i!=j);
}

void reconstruct_graph()	{
	int fake_node=n,fake_inserted=0;
	for(int i=0;i<n;i++)	{
		for(int j=i+1;j<n;j++)	{
			if(!r[i][j]) continue;
			if(r[i][j]==12)	{		//r=1
				add_edge(i,j);
				continue;
			}
			if(r[i][j]==6)	{		//r=2
				add_edge(i,fake_node);
				add_edge(fake_node,j);
				fake_node++;
				fake_inserted++;
				continue;
			}
			if(r[i][j]==4)	{		//r=3
				int f1=fake_node,f2=fake_node+1;
				add_edge(i,f1);
				add_edge(f1,f2);
				add_edge(f2,j);
				fake_node+=2;
				fake_inserted+=2;
				continue;
			}
			if(r[i][j]==3)	{		//r=4
				int f1=fake_node,f2=fake_node+1,f3=fake_node+2;
				add_edge(i,f1);
				add_edge(f1,f2);
				add_edge(f2,f3);
				add_edge(f3,j);
				fake_node+=3;
				fake_inserted+=3;
				continue;
			}
			if(r[i][j]==16)	{		//r=3/4
				int f1=fake_node,f2=fake_node+1;
				add_edge(i,j);
				add_edge(i,f1);
				add_edge(f1,f2);
				add_edge(f2,j);
				fake_node+=2;
				fake_inserted+=2;
				continue;
			}
			if(r[i][j]==18)	{
				int f1=fake_node;
				add_edge(i,j);
				add_edge(i,f1);
				add_edge(f1,j);
				fake_node+=1;
				fake_inserted+=1;
				continue;
			}
//			printf("r[%d][%d]=%d\n",i,j,r[i][j]);
			assert(0);
		}
	}
	n=n+fake_inserted;
	m=m+(fake_inserted*2);
}

void dump_graph()	{
	for(int i=0;i<n;i++)	{
		printf("%d: ",i);
		for(int j=0;j<n;j++)	if(maze[i][j])	printf("%d ",j);
		printf("\n");
	}
}

void dump_laplace()	{
	for(int i=0;i<n;i++)	{
		for(int j=0;j<n;j++)	{
			printf("%d ",laplace[i][j]);
		}
		printf("\n");
	}
}


void construct_laplace()	{
	for(int i=0;i<n;i++)	{
		for(int j=0;j<n;j++)	{
			if(i==j)	laplace[i][j]=degree[i];
			else	{
				if(maze[i][j])	laplace[i][j]=-1;
				else laplace[i][j]=0;
			}
		}
	}
}

void r8mat_identity(int n, long double a[])	{
	int k=0;
	for(int i=0;i<n;i++)	{
		for(int j=0;j<n;j++)	{
			if(i==j)	a[k]=1.0;
			else	a[k]=0.0;
			k++;
		}
	}
}

void r8mat_diag_get_vector ( int n, long double a[], long double v[] )	{
	int i;
	for ( i = 0; i < n; i++ )	  {
	    v[i] = a[i+i*n];
  	}
}

void jacobi_eigenvalue ( int n, long double a[], int it_max, long double v[], 
  long double d[], int &it_num, int &rot_num )
{
long double *bw;
  long double c;
  long double g;
  long double gapq;
  long double h;
  int i;
  int j;
  int k;
  int l;
  int m;
  int p;
  int q;
  long double s;
  long double t;
  long double tau;
  long double term;
  long double termp;
  long double termq;
  long double theta;
  long double thresh;
  long double w;
  long double *zw;

  r8mat_identity ( n, v );
  r8mat_diag_get_vector ( n, a, d );

  bw = new long double[n];
  zw = new long double[n];

  for ( i = 0; i < n; i++ )	{
	  bw[i] = d[i];
	  zw[i] = 0.0;
  }
  it_num = 0;
  rot_num = 0;

  while ( it_num < it_max )	{
	  it_num = it_num + 1;
	  //
	  //  The convergence threshold is based on the size of the elements in
	  //  the strict upper triangle of the matrix.
	  //
	  thresh = 0.0;
	  for ( j = 0; j < n; j++ )	{
		  for ( i = 0; i < j; i++ )
		  {
			  thresh = thresh + a[i+j*n] * a[i+j*n];
		  }
	  }

	  thresh = sqrt ( thresh ) / ( double ) ( 4 * n );

	  if ( thresh == 0.0 )	break;

	  for ( p = 0; p < n; p++ )	{
		  for ( q = p + 1; q < n; q++ )	 {
			  gapq = 10.0 * fabs ( a[p+q*n] );
			  termp = gapq + fabs ( d[p] );
			  termq = gapq + fabs ( d[q] );
			  //
			  //  Annihilate tiny offdiagonal elements.
			  //
			  if ( 4 < it_num &&
					  termp == fabs ( d[p] ) &&
					  termq == fabs ( d[q] ) )
			  {
				  a[p+q*n] = 0.0;
			  }
			  //
			  //  Otherwise, apply a rotation.
			  //
			  else if ( thresh <= fabs ( a[p+q*n] ) )	{
			          h = d[q] - d[p];
			          term = fabs ( h ) + gapq;

			          if ( term == fabs ( h ) )	{
			            t = a[p+q*n] / h;
			          }
			          else	{
			            theta = 0.5 * h / a[p+q*n];
			            t = 1.0 / ( fabs ( theta ) + sqrt ( 1.0 + theta * theta ) );
			            if ( theta < 0.0 )	{
			              t = - t;
			            }
	          		}
			          c = 1.0 / sqrt ( 1.0 + t * t );
			          s = t * c;
			          tau = s / ( 1.0 + c );
			          h = t * a[p+q*n];
//
//  Accumulate corrections to diagonal elements.
//
			          zw[p] = zw[p] - h;                 
			          zw[q] = zw[q] + h;
			          d[p] = d[p] - h;
			          d[q] = d[q] + h;

			          a[p+q*n] = 0.0;
//
//  Rotate, using information from the upper triangle of A only.
//
		          for ( j = 0; j < p; j++ )	{
		            g = a[j+p*n];
		            h = a[j+q*n];
		            a[j+p*n] = g - s * ( h + g * tau );
		            a[j+q*n] = h + s * ( g - h * tau );
		          }

		          for ( j = p + 1; j < q; j++ )	{
		            g = a[p+j*n];
		            h = a[j+q*n];
		            a[p+j*n] = g - s * ( h + g * tau );
		            a[j+q*n] = h + s * ( g - h * tau );
		          }

		          for ( j = q + 1; j < n; j++ )	{
		            g = a[p+j*n];
		            h = a[q+j*n];
		            a[p+j*n] = g - s * ( h + g * tau );
		            a[q+j*n] = h + s * ( g - h * tau );
		          }
//
//  Accumulate information in the eigenvector matrix.
//
	          for ( j = 0; j < n; j++ )	{
	            g = v[j+p*n];
        	    h = v[j+q*n];
	            v[j+p*n] = g - s * ( h + g * tau );
        	    v[j+q*n] = h + s * ( g - h * tau );
	          }
        	  rot_num = rot_num + 1;
	        }
      	}
    }

    for ( i = 0; i < n; i++ )	{
      bw[i] = bw[i] + zw[i];
      d[i] = bw[i];
      zw[i] = 0.0;
    }
  }
//
//  Restore upper triangle of input matrix.
//
  for ( j = 0; j < n; j++ )	{
    for ( i = 0; i < j; i++ )	{
      a[i+j*n] = a[j+i*n];
    }
  }
//
//  Ascending sort the eigenvalues and eigenvectors.
//
  for ( k = 0; k < n - 1; k++ )	{
    m = k;
    for ( l = k + 1; l < n; l++ )	{
      if ( d[l] < d[m] )	{
        m = l;
      }
    }

    if ( m != k )	{
      t    = d[m];
      d[m] = d[k];
      d[k] = t;
      for ( i = 0; i < n; i++ )	{
        w        = v[i+m*n];
        v[i+m*n] = v[i+k*n];
        v[i+k*n] = w;
      }
    }
  }

  delete [] bw;
  delete [] zw;

  return;
}

void dump_eval(long double d[])	{
	printf("eigen values: ");
	for(int i=0;i<n;i++)	printf("%Lf ",d[i]);
	printf("\n------\n");
}

void dump_evec(long double v[], long double d[])	{
	for(int i=0;i<n;i++)	{
//		printf("%LF : ", d[i]);
		eigen_val[i]=d[i];
		for(int j=0;j<n;j++)	{
//			printf("%Lf ",v[(i*n)+j]);
			eigen_vec[i][j]=v[(i*n)+j];
		}
//		printf("\n");
	}
//	printf("\n------\n");
}

void solve_eigen()	{
	long double a[n*n],v[n*n],d[n];
	int it_max=1000,it_num,rot_num;
	int k=0;
	for(int i=0;i<n;i++)	{
		for(int j=0;j<n;j++)	{	
			a[k]=laplace[i][j];
			k++;
		}
	}
	jacobi_eigenvalue(n,a,it_max,v,d,it_num,rot_num);
//	printf("it_num=%d\n",it_num);
//	printf("rot_num=%d\n",rot_num);
	assert(it_num < (it_max-10));
	//assert(rot_num < (it_max-10));
	//assert(it_num + rot_num < (it_max-10));
//	dump_eval(d);
	dump_evec(v,d);
}

long double Ruv(int u, int v)	{
	long double ans=0;
	for(int k=1;k<n;k++)	{
		assert(fabs(eigen_val[k])>0.00001);
		//printf("%Lf\n",eigen_vec[k][u]-eigen_vec[k][v]);
		ans=ans+(((eigen_vec[k][u]-eigen_vec[k][v])*(eigen_vec[k][u]-eigen_vec[k][v]))/eigen_val[k]);
	}	
	return ans;
}

void solve_queries()	{
	for(int Q=0;Q<q;Q++)	{
		int alice;
		scanf("%d",&alice);
		alice--;			//if alice=bob, formula will take care :), (hopefully! :P)
		if(mat_tree_num[alice]!=1)	{		//mat_tree_num[bob]=1
			printf("INFINITE\n");
			continue;
		}
		else	{
			assert(mymap[0]==0);
			int z;
			for(z=0;z<map_ind;z++)	{
				if(mymap[z]==alice)	break;
			}
			assert(z!=map_ind);
			assert(mymap[z]==alice);
			printf("%.4Lf\n",F*Ruv(0,z));
//			printf("F=%Lf Res=%Lf\n",F,Ruv(mymap[0],mymap[alice]));
			//printf("Laplace sir will take care :D\n");
		
		}
	}
}

int main(void)	{
	int test=1;
	while(1)	{
		init();
		if(!readmat())	break;
		printf("Case #%d:\n",test++);
		solve_chandra();
		reconstruct_graph();
		construct_laplace();
		solve_eigen();
		//dump_laplace();
		solve_queries();
	}


	return 0;
}
