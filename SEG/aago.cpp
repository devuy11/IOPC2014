#include <algorithm>
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <ctype.h>
#include <cmath>
#include <ctime>
#include <queue>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <bitset>
#include <iostream>

using namespace std;

typedef long long INT;
typedef pair<int, int> pii;

#define MOD 1000000007
#define NN 100100

struct NODE {
	int st, en;
	INT cof[5];	
} node[NN*3];

INT c[10];

void Make(int u, int st, int en) {
	node[u].st=st; node[u].en=en;
	int j, mid;
	for (j=0; j<5; j++) node[u].cof[j]=0;
	if (st==en) return;
	mid=(st+en)/2;
	Make(u*2, st, mid);
	Make(u*2+1, mid+1, en);
}

void PushDown(int u) {
	int i, l, r;
	l=u*2; r=u*2+1;
	for (i=0; i<5; i++) {
		node[l].cof[i]+=node[u].cof[i];
		node[r].cof[i]+=node[u].cof[i];
		node[u].cof[i]=0;
	}
}

void Update(int u, int st, int en) {
	if (node[u].st>en) return;
	if (node[u].en<st) return;
	if (node[u].st>=st && node[u].en<=en) {
		for (int i=0; i<5; i++) {
			node[u].cof[i]+=c[i];
			node[u].cof[i]%=MOD;
		}
		return;
	}
	PushDown(u);
	Update(u*2, st, en);
	Update(u*2+1, st, en);
}

INT power(INT a, INT b) {
	if (b==0) return 1;
	INT ret=power(a, b/2);
	ret=ret*ret%MOD;
	if (b&1) ret=ret*a%MOD;
	return ret;
}

INT Calc(int u, int st, int en) {
	if (node[u].st>en) return 0;
	if (node[u].en<st) return 0;
	if (node[u].st==node[u].en) {
		INT res=0;
		for (int i=0; i<5; i++) {
			res=res+power(st, i)*node[u].cof[i];
			res%=MOD;
		}
		return res;
	}
	PushDown(u);
	return Calc(u*2, st, en)+Calc(u*2+1, st, en);
}

int main() {
	
	int d, x, y, i, j, ii, N, T;
	char ch;
	INT res;
	
	INT C[10][10];
	
	for (i=0; i<10; i++) C[i][i]=C[i][0]=1;
	for (i=2; i<10; i++) for (j=1; j<i; j++) C[i][j]=C[i-1][j]+C[i-1][j-1];
	
	scanf("%d%d", &N, &T);
	
	Make(1, 0, N+1);
	
	for (ii=0; ii<T; ii++) {
		scanf(" %c ", &ch);
		if (ch=='Q') {
			scanf("%d%d", &x, &y);
			res=Calc(1, y, y)-Calc(1, x-1, x-1);
			res=(res%MOD+MOD)%MOD;
			res=res*power(12, MOD-2)%MOD;
			cout << res << endl;
		} else {
			scanf("%d%d%d", &x, &y, &d);
			c[0]=0;
			c[1]=(2*d*d+6*d); 
			c[2]=6*d*d+6*d+3*d*d*d;
			c[3]=6*d*d*d+4*d*d;
			c[4]=3*d*d*d;
			for (i=1; i<=4; i++) {
				for (j=0; j<i; j++) {
					if ((i+j)&1) {
						c[j]-=C[i][j]*c[i]%MOD*power(x, i-j)%MOD;
						c[j]=(c[j]%MOD+MOD)%MOD;
					} else {
						c[j]+=C[i][j]*c[i]%MOD*power(x, i-j)%MOD;
						c[j]%=MOD;
					}
				}
			}
			Update(1, x, y);
		}
	}
		

	return 0;
}



