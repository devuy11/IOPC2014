#include <bits/stdc++.h>

using namespace std;

long long Mult (long long a, long long b, long long c)
{
	if(b > a)
		return Mult(b, a, c);
	long long ans = 0, temp = a % c;
	while (b)
	{
		if (b & 1LL)
			ans = (ans + temp) % c;
		temp = (temp << 1) % c;
		b >>= 1;
	}
	return ans;
}

int main ()
{
	int T;
	long long n, b;
	scanf ("%d", &T);
	while (T--)
	{
		scanf ("%lld %lld", &n, &b);
		
		if (n <= 1 && b == 1)
		{
			printf ("Odd\n");
			continue;
		}

		long long res1 = 1LL, res2 = 1LL;
		for (int i = 2; i <= n; i++)
		{
			res1 = Mult (res1, i, b << 1);
			res2 = Mult (res2, i, b);
		}
		if (res1 == res2)
			printf ("Even\n");
		else
			printf ("Odd\n");
	}
	return 0;
}
