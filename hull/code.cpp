#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

struct pt {
 LL x, y;

 pt () {
 
 }

 pt (LL _x, LL _y) {
 	x = _x;
	y = _y;
 }
};

bool cmp (pt a, pt b) {
 return a.x <b.x || a.x == b.x && a.y <b.y;
}

bool cw (pt a, pt b, pt c) {
 return a.x * (b.y-c.y) + b.x * (c.y-a.y) + c.x * (a.y-b.y) <0;
}

bool ccw (pt a, pt b, pt c) {
 return a.x * (b.y-c.y) + b.x * (c.y-a.y) + c.x * (a.y-b.y)> 0;
}

void convex_hull (vector <pt> & a) {
 if (a.size () == 1) return;
 sort (a.begin (), a.end (), & cmp);
 pt p1 = a [0], p2 = a.back ();
 vector <pt> up, down;
 up.push_back (p1);
 down.push_back (p1);
 for (size_t i = 1; i <a.size (); ++ i) {
	 if (i == a.size () -1 || cw (p1, a [i], p2)) {
		 while (up.size () >= 2 &&! cw (up [up.size () -2], up [up.size () -1], a [i]))
			 up.pop_back ();
		 up.push_back (a [i]);
	 }
	 if (i == a.size () -1 || ccw (p1, a [i], p2)) {
		 while (down.size () >= 2 &&! ccw (down [down.size () -2], down [down.size () -1], a [i]))
			 down.pop_back ();
		 down.push_back (a [i]);
	 }
 }
 a.clear ();
 for (size_t i = 0; i <up.size (); ++ i)
	 a.push_back (up [i]);
 for (size_t i = down.size () -2; i> 0; -- i)
	 a.push_back (down [i]);
} 

const int INF = (int) 1e9;

int main() {
	int T;
	cin >> T;
	int sum = 0;
	
	while (T--) {
		int n;
		vector <pt> a;
		cin >> n;
		assert (n >= 1 && n <= 100000);
		sum += n;
		for (int i = 0; i < n; i++) {
			int x = 0, y = 0;
			scanf ("%d %d", &x, &y);
			assert (x >= -INF && x <= INF);
			assert (y >= -INF && y <= INF);
			a.push_back (pt (x, y));
		}
		
		convex_hull (a);
	
		if (n == 1) {
			cout << 0 << endl;
			continue;
		}

		int hull = a.size();
		//cout << n << " hull size  " << hull << endl;
		int ans = 3 * n - 3 - hull;
		cout << ans << endl;
	}	
	cerr << "Sum " << sum << endl;
	assert (sum <= 200000);

	return 0;
}
