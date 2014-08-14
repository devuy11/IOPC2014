#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <vector>
#include <map>
#include <set>

using namespace std;

#define SIZE(A) (int((A).size()))
#define pb(A) push_back(A)
#define mp(A,B) make_pair(A,B)

const int MAXN = 200000;

int n;
pair<int,int> a[MAXN], b[MAXN];

bool cmp(const pair<int,int> i, const pair<int,int> j) {
	return i.first*1LL*j.second - i.second*1LL*j.first > 0;
}

int main() {
	int t;
	cin >> t;
	for (; t--;) {
		scanf("%d", &n);
		int p = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d%d", &a[i].first, &a[i].second);
			if (a[i].first < a[p].first) {
				p = i;
			}
		}

		if (n == 1) {
			puts("0");
			continue;
		}
		
		swap(a[0], a[p]);
		for (int i = n-1; i >= 0; i--) {
			a[i].first -= a[0].first;
			a[i].second -= a[0].second;
		}
		sort(a+1, a+n, cmp);

		b[0] = a[0]; b[1] = a[1]; b[2] = a[2];
		int m = min(2, n-1);
		for (int i = 3; i < n; i++) {
			while ((a[i].first-b[m].first)*1LL*(b[m].second-b[m-1].second)-(a[i].second-b[m].second)*1LL*(b[m].first-b[m-1].first) > 0) {
				m--;
			}
			b[++m] = a[i];
		}

		printf("%d\n", (n-1)*3-m-1);
	}

    return 0;
}


