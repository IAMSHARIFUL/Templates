#include <bits/stdc++.h>
#include<vector>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define MAX 400000
#define BEGIN 1
#define DEFAULT_VALUE 0
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> new_data_set;
new_data_set s[MAX];
vector<pair<int,int> > Queries;
vector<int> values;
set<int> S;
int main()
{
    int n,i,j,q;
    scanf("%d %d",&n,&q);
    int a[n];
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
        S.insert(a[i]);
    }
    pair<int,int> p;
    for(i=0;i<q;i++)
    {
        scanf("%d %d",&p.second,&p.first);
        //p.second--;
        S.insert(p.first);
        Queries.push_back(p);
    }
    while(!S.empty())
    {
        j=*(S.begin());
        values.push_back(j);
        S.erase(j);
    }
    for(i=0;i<n;i++)
    {
        j=upper_bound(values.begin(),values.end(),a[i])-values.begin();
        s[j].insert(i);
    }
    for(i=0;i<q;i++)
    {
        j=upper_bound(values.begin(),values.end(),a[Queries[i].second])-values.begin();
        s[j].erase(Queries[i].second);
        j=upper_bound(values.begin(),values.end(),Queries[i].first)-values.begin();
        s[j].insert(Queries[i].second);
        a[Queries[i].second]=Queries[i].first;
        printf("%d\n",s[j].order_of_key(Queries[i].second));
    }
    return 0;
}
