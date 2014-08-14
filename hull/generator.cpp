#include"../testlib-0.8.5/testlib.h"
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rep(i,n) for(int (i)=0;(i)<(int)(n);(i)++)
#define rep1(i,a,b) for(int (i)=(a);(i)<=(int)(b);(i)++)
#define fore(c,itr) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)

void print(vector<int>a){ rep(i,a.size()) {cout<<a[i]; if(i+1!=a.size())cout<<" ";} cout<<endl;}

int main(int argc, char* argv[]) {
    //registerGen(argc, argv);
    //int T=0;
    //rep(tc,1) writeTest1(T++);
   	 char in_files[27][20]={"input/input00.txt" ,"input/input01.txt","input/input02.txt","input/input03.txt","input/input04.txt","input/input05.txt","input/input06.txt","input/input07.txt","input/input08.txt","input/input09.txt","input/input10.txt","input/input11.txt","input/input12.txt","input/input13.txt","input/input14.txt","input/input15.txt"};
   	
   	int sum = 0, file = 14, n = 0, T = 0;
	FILE *fp;
	fp = fopen(in_files[file], "w");
	/*
	n = 30000;
	fprintf (fp, "%d\n", n);

	for (int i = 0; i < 30000; i++) {
		fprintf (fp, "%d %d\n", i, i * i);
	}
	
	n = 60000;

	fprintf (fp, "%d\n", n);
	for (int i = -30000; i < 30000; i++) {
		fprintf (fp, "%d %d\n", i, i * i);
	}

	n = 50000;

	fprintf (fp, "%d\n", n);
	for (int i = -25000; i < 25000; i++) {
		fprintf (fp, "%d %d\n", i, i * i + 15);
	}
	*/



	fclose (fp);	
	return 0;
}
