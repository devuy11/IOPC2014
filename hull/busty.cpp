#include <bits/stdc++.h>

using namespace std;

vector < pair < long long, long long > > Hull, pts;
long long n;

long long CrossProduct (pair < long long, long long > p, pair < long long, long long > q)
{
	return (p.first * q.second - p.second * q.first);
}

bool Check (pair < long long, long long > p, pair < long long, long long > q, pair < long long, long long > r)
{
	pair < long long, long long > a = make_pair (q.first - p.first, q.second - p.second);
	pair < long long, long long > b = make_pair (r.first - p.first, r.second - p.second);
	return CrossProduct (b, a) > 0;
}

void ConvexHull ()
{
	Hull.clear ();
	sort (pts.begin (), pts.end ());
	Hull.resize (2 * n);
	long long sz = 0;
	for (long long i = 0; i < n; i++)
	{
		while (sz >= 2 && !Check (Hull[sz - 1], Hull[sz - 2], pts[i]))
			sz--;
		Hull[sz++] = pts[i];
	}

	for (long long i = n - 2, temp = sz + 1; i >= 0; i--)
	{
		while (sz >= temp && !Check (Hull[sz - 1], Hull[sz - 2], pts[i]))
			sz--;
		Hull[sz++] = pts[i];
	}
	if (sz >= 1)
		Hull.resize (sz - 1);
}

int main ()
{
	long long T, x, y;
	scanf ("%lld", &T);
	while (T--)
	{
		scanf ("%lld", &n);
		if (n == 1)
		{
			printf ("0\n");
			continue;
		}
		else if (n == 2)
		{
			printf ("1\n");
			continue;
		}

		pts.clear ();
		for (long long i = 0; i < n; i++)
		{
			scanf ("%lld %lld", &x, &y);
			pts.push_back (make_pair (x, y));
		}
		ConvexHull ();
		long long sz = Hull.size ();
		long long res = 3 * n - sz - 3;
		printf ("%lld\n", res);
	}
	return 0;
}

