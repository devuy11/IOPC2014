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

using namespace std;

typedef long long INT;
typedef pair<int, int> pii;
#define NN 5100

vector<int> adj[NN], radj[NN];
int id[NN], num[NN], vst[NN], flag=0;
int tmp[NN];

bool cmp(int u, int v) {
	return id[u]<id[v];
}

void Add(int u, int v) {
	if (id[u]<id[v]) {
		adj[u].push_back(v);
		radj[v].push_back(u);
		return;
	}
	
	int j, fr, to, i, d, x, w, n;
	pii pu;
		
	flag++; fr=id[v]; to=id[u];
	queue<int> q=queue<int>();
	q.push(v); n=0; vst[v]=flag;
	while(!q.empty()) {
		w=q.front(); q.pop();
		tmp[n++]=w; 
		for (i=0, d=adj[w].size(); i<d; i++) {
			x=adj[w][i];
			if (id[x]>id[u]) continue;
			if (vst[x]!=flag) {
				vst[x]=flag;
				q.push(x);
			}
		}
	}
	j=fr;
	for (i=fr; i<=to; i++) {
		if (vst[num[i]]==flag) {
			continue;
		} else {
			num[j++]=num[i];
			id[num[j-1]]=j-1;
		}
	}
	sort(tmp, tmp+n, cmp);
	for (i=0; i<n; i++) {
		num[j++]=tmp[i];
		id[tmp[i]]=j-1;
	}
	adj[u].push_back(v);
	radj[v].push_back(u);
}

int main() {
	
	int T, N, ok, i, u, v;
	char str[100];
	
	for (scanf("%d", &T); T--; ) {
		scanf("%d", &N); ok=0;
		for (i=0; i<N; i++) {
			id[i]=num[i]=i;
			adj[i].clear(); radj[i].clear();
		}
		while(1) {
			scanf("%s", str);
			if (!strcmp(str, "END")) break;
			scanf("%d%d", &u, &v); u--; v--;
			if (str[0]=='U') {
				if (ok) swap(u, v);
				Add(u, v);
			} else {
				if (id[u]<id[v]) puts("YES");
				else {
					puts("NO");
					ok=1-ok;
				}
			}
		}
	}
	
	return 0;
}


