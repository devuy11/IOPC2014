/**
 * Validates that the input contains the only token token.
 * This token can contain only lowercase latin letters a-z. The length should be between 1 and 100, inclusive.
 * Also validates that file ends with EOLN and EOF.
 */

#include"../testlib-0.8.5/testlib.h"
#include <bits/stdc++.h>
//#include "testlib.h"

using namespace std;

const int INF = (int) 1e9;

int main()
{
    registerValidation();

    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();
	
	int sum = 0;

	while (T--)
	{
		int n = inf.readInt(1, 100000, "n");
		inf.readEoln();
		
		sum += n;

		for (int i = 0; i < n; i++)
		{
			int x = inf.readInt(-INF, INF, "x");
			inf.readSpace();
			int y = inf.readInt(-INF, INF, "y");
			inf.readEoln();
		}
	}

	assert (sum >= 1 && sum <= 200000);

    inf.readEof();

    return 0;
}

