/*
	@author: Praveen Dhinwa
	Expected output: AC
*/
#include<bits/stdc++.h>

using namespace std;

string s;
const int N = 1e5;
int sum[N];
int m;

int getValue (int L, int R) {
	if (L == 0) return sum[R];
	return sum[R] - sum[L - 1];
}

// AC with normal IO
// TLE with memset
int solve1 () {
	//memset (sum, 0, sizeof (sum));
	for (int i = 0; i < s.size(); i++) sum[i] = 0;
	
	sum[0] = (s[0] == 'A');
	for (int i = 1; i < s.size(); i++) {
		if (s[i] == 'A') sum[i] = sum[i - 1] + 1;
		else sum[i] = sum[i - 1];
	}
	int ans = 0;
	for (int i = 0; i <= s.size() - m; i++) {
		int cnt = getValue (i, i + m - 1);
		ans = max (ans, cnt);
	}
	return m - ans;
}

// TLE
int solve2 () {
	int ans = 0;
	for (int i = 0; i < s.size(); i++) {
		int sz = 0, cnt = 0;
		for (int j = i; j < i + m; j++) {
			sz ++;
			if (s[j] == 'A') cnt ++;
		}
		if (sz == m) {
			ans = max (ans, cnt);
		}
	}
	return m - ans;
}

// randomized, fails means test cases are not weak
int solveFraud () {
	memset (sum, 0, sizeof (sum));
	sum[0] = (s[0] == 'A');
	for (int i = 1; i < s.size(); i++) {
		if (s[i] == 'A') sum[i] = sum[i - 1] + 1;
		else sum[i] = sum[i - 1];
	}
	
	vector <int> a;
	for (int i = 0; i <= (int) s.size() - m; i++) a.push_back (i);
	random_shuffle (a.begin(), a.end());
	
	int ans = 0;
	for (int i = 0; i < min (10000, (int)a.size()); i++) {
		int id = a[i];
		int cnt = getValue (id, id + m - 1);
		ans = max (ans, cnt);
	}
	
	return m - ans;
}

int main() {
	srand (time (NULL));
//	ios_base:: sync_with_stdio (false);

	int T = 1;
	cin >> T;
	int sum = 0;
	while (T--) {
		cin >> s;
		cin >> m;
		assert (s.size() >= 1 && s.size() <= 100000);
		for (int i = 0; i < s.size(); i++) assert (s[i] >= 'A' && s[i] <= 'Z');
		int cnt = 0; 
		for (int i = 0; i < s.size(); i++) if (s[i] == 'A') cnt ++;
		assert (cnt >= m);

		int ans1 = solve1 ();
		/*
		if (s.size() <= 10000) {
			int ans2 = solve2 ();
			assert (ans1 == ans2);
		}
		*/
		cout << ans1 << endl;
		
		sum += s.size();
	}
	
	assert (sum >= 0 && sum <= 1000000);
	return 0;
}
