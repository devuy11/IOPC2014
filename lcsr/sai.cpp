#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		string s;
		cin>>s;
		int k,L;
		cin>>k>>L;
		int ans=0;
		int count=0;
		char ch;
		ch = s[0];
		count=0;
		priority_queue<int> pq;
		ch = s[0];
		count=0;
		int i;
		//cout<<s<<endl;
		for(i=0; i<s.length(); ++i)
		{
			if(ch!=s[i])
			{
				pq.push(count);
				//cout<<i<<" "<<count<<" "<<ch<<endl;
				ch = s[i];
				count=0;
			}
			count++;
		}
		//cout<<i<<" "<<count<<" "<<ch<<endl;
		pq.push(count);

		int l = pq.size();
		/*for(i=0;i<l;++i)
		{
			cout<<pq.top()<<" ";
			pq.pop();
		}*/
		count=0;
		ch = s[0];
		for(i=0; i<s.length(); ++i)
		{
			if(ch!=s[i])
			{
				ch = s[i];
				count=1;
				ans++;
			}
			else if(count != k)
			{
				count++;
				ans++;
			}
			if(ans>=L)
				break;
		}
		int ans1=ans;
		int ans2=ans;
		bool flag=false;
		if(ans2<L)
		{
			int max;
			while(!pq.empty())
			{
				int temp = ans2;
				max = pq.top();
				pq.pop();

				if(max>=2*k && L>=(k+temp))
				{
					ans2+=k;
					ans1+=1+k;
					pq.push(max-k);
					pq.push(k);
				}
				if(max>k && max<2*k && L>=(k+temp))
				{
					ans2+=max-k;
					ans1+=1+max-k;
					pq.push(max-k);
					pq.push(k);
				}
				if(max>=2*k && L<(k+temp))
				{
					ans2=L;
					ans1+=1+L-ans2;
					//pq.push(max-k);
				}
				if(max>k && max<2*k && L<(k+temp))
				{
					if(L <= max-k+temp)
					{
						ans2=L;
						ans1+= 1+ L-temp;
					}
					else
					{
						ans2+=(max-k);
						ans1+= 1+(max-k);
						pq.push(max-k);
						pq.push(k);
					}
				}
				if(max<=k && ans2!=L)
                {
                    flag=true;
                    break;
                }
			}
		}
		if(!flag)
            printf("%d\n", ans1);
        else
            printf("0\n");
	}
	return 0;
}

