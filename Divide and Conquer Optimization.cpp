#include <bits/stdc++.h>
#include <vector>
#include<math.h>
#include<string.h>
using namespace std;
#define MAX 300002
#define MOD 998244353
#define GMAX 19
#define INF 20000000000000000
#define EPS 0.0000000001
#define FASTIO ios_base::sync_with_stdio(false);cin.tie(NULL)
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
vector<pair<int,long long> > Cat;
vector<int> d;
vector<long long> minimum_times,cats;
long long C(int i, int j)
{
    return (minimum_times[j]*Cat[j].first+Cat[j].second)-(minimum_times[j]*Cat[i].first+Cat[i].second);
}
vector<long long> dp_before, dp_cur;

// compute dp_cur[l], ... dp_cur[r] (inclusive)
void compute(int l, int r, int optl, int optr)
{
    if (l > r)
        return;
    int mid = (l + r) >> 1;
    pair<long long, int> best = {INF, -1};

    for (int k = optl; k <= min(mid, optr); k++) {
        best = min(best, {dp_before[k] + C(k, mid), k});
    }

    dp_cur[mid] = best.first;
    int opt = best.second;

    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
}
void update()
{
    for(int i=0;i<dp_before.size();i++)
    {
        dp_before[i]=dp_cur[i];
    }
}
int main()
{
    int n,m,q,i,j;
    scanf("%d %d %d",&n,&m,&q);
    d.push_back(0);
    for(i=1;i<n;i++)
    {
        int tt;
        scanf("%d",&tt);
        d.push_back(d[i-1]+tt);
    }
    for(i=0;i<m;i++)
    {
        int h,t;
        scanf("%d %d",&h,&t);
        h--;
        cats.push_back(t-d[h]);
    }
    d.clear();
    sort(cats.begin(),cats.end());
    pair<int,long long> p=make_pair(0,0);
    for(i=0;i<m;i++)
    {
        for(j=i;j<m&&cats[j]==cats[i];j++);
        p.first=j-i;
        minimum_times.push_back(cats[i]);
        p.second=-cats[i];
        p.second=p.second*p.first;
        Cat.push_back(p);
        i=j-1;
    }
    cats.clear();
    for(i=1;i<Cat.size();i++)
    {
        Cat[i].first=Cat[i].first+Cat[i-1].first;
        Cat[i].second=Cat[i].second+Cat[i-1].second;
    }
    n=Cat.size();
    for(i=0;i<n;i++)
    {
        dp_before.push_back(minimum_times[i]*Cat[i].first+Cat[i].second);
        dp_cur.push_back(minimum_times[i]*Cat[i].first+Cat[i].second);
    }
    for(i=1;i<q;i++)
    {
        compute(0,n-1,0,n-1);
        update();
    }
    long long ans=dp_cur[n-1];
    printf("%I64d",ans);
    return 0;
}
