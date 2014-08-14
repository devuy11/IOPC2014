#include <bits/stdc++.h>

using namespace std;

#define BUF 4096
char ibuf[BUF];
int ipt = BUF;
const int N = (int)(1e5 + 5);

template <class T>
T readInteger()
{
	while (ipt < BUF && ibuf[ipt] < '0')
		ipt++;
	if (ipt == BUF)
	{
    	fread (ibuf, 1, BUF, stdin);
    	ipt = 0;
    	while (ipt < BUF && ibuf[ipt] < '0')
    		ipt++;
	}
	T n = 0;
	while (ipt < BUF && ibuf[ipt] >= '0')
		n = (n*10) + (ibuf[ipt++] - '0');
	if (ipt == BUF)
	{
    	fread (ibuf, 1, BUF, stdin);
    	ipt = 0;
    	while (ipt < BUF && ibuf[ipt] >= '0')
    		n = (n*10) + (ibuf[ipt++] - '0');
	}
	return n;
}

typedef int coord_t;
typedef long long coord2_t;
 
struct Point
{
	coord_t x, y;
	bool operator <(const Point &p) const
	{
		return x < p.x || (x == p.x && y < p.y);
	}
};

vector < Point > P, H;
 
coord2_t cross(const Point &O, const Point &A, const Point &B)
{
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}
 
int ConvexHull(int n)
{
	int k = 0;
 
	sort (P.begin(), P.end());
 	
 	H.resize (2 * n);
	for (int i = 0; i < n; i++)
	{
		while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0)
			k--;
		H[k++] = P[i];
	}
 
	for (int i = n-2, t = k+1; i >= 0; i--)
	{
		while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0)
			k--;
		H[k++] = P[i];
	}
	return k - 1; 
}

int main ()
{
	long long T, n, x, y;
	T = readInteger < long long > ();
	while (T--)
	{
		n = readInteger < long long > ();
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

		Point Temp;
		P.clear ();
		for (long long i = 0; i < n; i++)
		{
			Temp.x = readInteger < long long > ();
			Temp.y = readInteger < long long > ();
			P.push_back (Temp);
		}
		int sz = ConvexHull (n);
		int res = 3 * n - sz - 3;
		printf ("%d\n", res);
	}
	return 0;
}