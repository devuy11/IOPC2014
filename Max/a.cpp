#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cassert>

using namespace std;

int row[51], col[51];
int mat[51][51];
bool used[51][51];
int n, m;

void __sort(vector <pair <int, int> > &a) {
	/*printf("Orig:\n");
	for(int i = 0; i < a.size(); i ++) {
		printf("%d ", a[i].first);
	}
	printf("\n");*/
	if(a.size() == 0)
		return;
	vector <pair <int, int> > p, q;
	for(int i = 0; i < a.size() - 1; i ++) {
		p.push_back(a[i]);
		if(a[i].first > a[i + 1].first)
			break;
	}
	for(int i = p.size(); i < a.size(); i ++)
		q.push_back(a[i]);
	/*printf("P:\n");
	for(int i = 0; i < p.size(); i ++)
		printf("%d ", p[i].first);
	printf("\n");
	printf("Q: \n");
	for(int i = 0; i < q.size(); i ++)
		printf("%d ", q[i].first);
	printf("\n");*/
	int l = 0, r = 0, t = 0;
	while(l < p.size() && r < q.size()) {
		if(p[l].first < q[r].first) {
			a[t ++] = p[l];
			l ++;
		}
		else {
			a[t ++] = q[r];
			r ++;
		}
	}
	while(l < p.size()) {
		a[t ++] = p[l ++];
	}
	while(r < q.size()) {
		a[t ++] = q[r ++];
	}
}

bool equality(vector <pair <int, int> > a, vector <pair <int, int> > b) {
	if(a.size() != b.size())
		return false;
	for(int i = 0; i < a.size(); i ++) {
		if(a[i].first != b[i].first)
			return false;
	}
	return true;
}

bool check(int x, int y, bool inc) {
	vector <pair <int, int> > tempr, tempc, bla;
	//printf("%d %d\n", x, y);
	x = x + (y + 1) / m;
	y = (y + 1) % m;
	for(int i = x; i < n; i ++)
		tempr.push_back(make_pair(row[i], i));
	for(int j = 0; j < m; j ++)
		tempc.push_back(make_pair(col[j], j));
	sort(tempc.begin(), tempc.end());
	int start;
	if(y == 0) {
		start = 0;
	}
	else {
		int val = tempr[0].first;
		for(int i = tempc.size() - 1; i >= 0; i --) {
			if(val == 0)
				break;
			if(!used[tempr[0].second][tempc[i].second]) {
				val --;
				tempc[i].first --;
			}
		}
		start = 1;
	}
	bla = tempc;
	sort(tempc.begin(), tempc.end());
	//assert(equality(bla, tempc));
	for(int i = start; i < tempr.size(); i ++) {
		int val = tempr[i].first;
		//printf("Val: %d\n", val);
		for(int j = tempc.size() - 1; j >= 0; j --) {
			if(val == 0)
				break;
			tempc[j].first --;
			val --;
		}
		__sort(tempc);
	}
	for(int i = 0; i < m; i ++)
		if(tempc[i].first != 0)
			return false;
	//printf("True\n");
	return true;
}

int main() {
	int T;
	scanf( "%d", &T);
	for(int t = 0; t < T; t ++) {
		scanf(" %d %d", &n, &m);
		for(int i = 0; i < n; i ++) {
			scanf(" %d", row + i);
		}
		for(int i = 0; i < m; i ++) {
			scanf(" %d", col + i);
		}
		memset(used, false, sizeof(used));
		printf("TestCase #:%d\n", t + 1);
		if(!check(0, -1, false)) {
			printf("-1\n");
		}
		else {
			for(int i = 0; i < n; i ++) {
				for(int j = 0; j < m; j ++) {
					used[i][j] = true;
					mat[i][j] = 0;
					if(!check(i, j, true)) {
						mat[i][j] = 1;
						row[i] --;
						col[j] --;
					}
					printf("%d", mat[i][j]);
				}
				printf("\n");
			}
		}
	}
	return 0;
}
