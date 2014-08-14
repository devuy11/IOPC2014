// Gauss-Jordan elimination with full pivoting.
//
// Uses:
//   (1) solving systems of linear equations (AX=B)
//   (2) inverting matrices (AX=I)
//   (3) computing determinants of square matrices
//
// Running time: O(n^3)
//
// INPUT:    a[][] = an nxn matrix
//           b[][] = an nxm matrix
//
// OUTPUT:   X      = an nxm matrix (stored in b[][])
//           A^{-1} = an nxn matrix (stored in a[][])
//           returns determinant of a[][]

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <cstring>

using namespace std;

const double EPS = 1e-10;

typedef vector<int> VI;
typedef double T;
typedef vector<T> VT;
typedef vector<VT> VVT;

vector <int> adj[50];
bool visited[50];

void dfs(int u) {
	visited[u] = true;
	for(int i = 0; i < adj[u].size(); i ++) {
		if(!visited[adj[u][i]])
			dfs(adj[u][i]);
	}
}

T GaussJordan(VVT &a, VVT &b) {
  const int n = a.size();
  const int m = b[0].size();
  VI irow(n), icol(n), ipiv(n);
  T det = 1;

  for (int i = 0; i < n; i++) {
    int pj = -1, pk = -1;
    for (int j = 0; j < n; j++) if (!ipiv[j])
      for (int k = 0; k < n; k++) if (!ipiv[k])
	if (pj == -1 || fabs(a[j][k]) > fabs(a[pj][pk])) { pj = j; pk = k; }
    ipiv[pk]++;
    swap(a[pj], a[pk]);
    swap(b[pj], b[pk]);
    if (pj != pk) det *= -1;
    irow[i] = pj;
    icol[i] = pk;

    T c = 1.0 / a[pk][pk];
    det *= a[pk][pk];
    a[pk][pk] = 1.0;
    for (int p = 0; p < n; p++) a[pk][p] *= c;
    for (int p = 0; p < m; p++) b[pk][p] *= c;
    for (int p = 0; p < n; p++) if (p != pk) {
      c = a[p][pk];
      a[p][pk] = 0;
      for (int q = 0; q < n; q++) a[p][q] -= a[pk][q] * c;
      for (int q = 0; q < m; q++) b[p][q] -= b[pk][q] * c;      
    }
  }

  for (int p = n-1; p >= 0; p--) if (irow[p] != icol[p]) {
    for (int k = 0; k < n; k++) swap(a[k][irow[p]], a[k][icol[p]]);
  }

  return det;
}

double A[50][50];
double B[50][1];
int rate[50][50], tim[50][50];

int main() {
	int n, m, q;
	int cntr = 0;
	scanf(" %d %d %d", &n, &m, &q);
	while(n != 0) {
		cntr ++;
		printf("Case #%d:\n", cntr);
		memset(tim, 0, sizeof(tim));
		memset(rate, 0, sizeof(rate));
		memset(visited, 0, sizeof(visited));
		for(int i = 0; i < 50; i ++)
			adj[i].clear();
		for(int i = 0; i < 50; i ++) {
			for(int j = 0; j < 50; j ++)
				A[i][j] = B[i][j] = 0.0;
		}
		for(int i = 0; i < m; i ++) {
			int u, v, r, tuv, tvu;
			scanf(" %d %d %d %d %d", &u, &v, &r, &tuv, &tvu);
			u --;
			v --;
			rate[u][v] = r;
			rate[v][u] = r;
			tim[u][v] = tuv;
			tim[v][u] = tvu;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		dfs(0);
		for(int i = 0; i < n; i ++) {
			int sumrat = 0;	
			for(int k = 0; k < n; k ++)
				sumrat += rate[i][k];
			if(sumrat == 0)
				sumrat = 1;
			for(int j = 0; j < n; j ++) {
				A[i][j] = -1.0 * ((double) rate[i][j]) / ((double) sumrat);
				if(j == i)
					A[i][j] = 1.0;
				B[i][0] -= A[i][j] * tim[i][j];
			}
		}
		/*for(int i = 0; i < n; i ++) {
			for(int j = 0; j < n; j ++) {
				printf("%lf ", A[i][j]);
			}
			printf(": %lf\n", B[i][0]);
		}*/
		for(int i = 0; i < q; i ++) {
		
			VVT a(n), b(n);
			for (int i = 0; i < n; i++) {
				a[i] = VT(A[i], A[i] + n);
				b[i] = VT(B[i], B[i] + 1);
			}
			int k;
			scanf(" %d", &k);
			k --;
			if(!visited[k]) {
				printf("INFINITE\n");
				continue;
			}
			for(int i = 0; i < n; i ++) {
				a[k][i] = 0;
			}
			a[k][k] = 1.0;
			b[k][0] = 0.0;
			GaussJordan(a, b);
			double v1 = b[0][0];
			for(int i = 0; i < n; i++) {
				a[i] = VT(A[i], A[i] + n);
				b[i] = VT(B[i], B[i] + 1);
			}
			for(int i = 0; i < n; i ++) {
				a[0][i] = 0;
			}
			a[0][0] = 1.0;
			b[0][0] = 0.0;
			GaussJordan(a, b);
			double v2 = b[k][0];
			printf("%.4lf\n", v1 + v2);
		}
		scanf(" %d %d %d", &n, &m, &q);
	}
	return 0;
}
