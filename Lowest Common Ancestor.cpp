#include<bits/stdc++.h>
#include<vector>
#include<math.h>
#include<string.h>
using namespace std;
#define MOD 1000000007
#define MAX 100005
#define PMAX 55
#define PRECISION 0.000001
#define INF 2000000000
#define FASTIO ios_base::sync_with_stdio(false);cin.tie(NULL)
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
pair<int,int> cal[MAX*2];
vector<pair<int,long long> > Graph[MAX];
int positions[MAX];
int depths[MAX];
int parents[MAX];
vector<pair<int,int> > arr,SparseTable[MAX*2];
void dfsLCA(int node,int depth=0,int parent=-1)
{
    positions[node]=arr.size();
    depths[node]=depth;
    arr.push_back(make_pair(depth,node));
    int i;
    for(i=0; i<Graph[node].size(); i++)
    {
        if(Graph[node][i].first==parent) continue;
        dfsLCA(Graph[node][i].first,depth+1,node);
        arr.push_back(make_pair(depth,node));
    }
}
void initialize()
{
    int i,j;
    cal[1].second=1;
    for(i=1,j=1<<i; j<MAX*2; i++,j=1<<i)
    {
        cal[j].first=1;
        cal[j].second=j;
    }
    for(i=2; i<MAX*2; i++)
    {
        cal[i].first=cal[i].first+cal[i-1].first;
        if(cal[i].second==0) cal[i].second=cal[i-1].second;
    }
}
void build()
{
    int i,j,m,n=arr.size();
    for(i=0,j=0; i<n; i++)
    {
        SparseTable[i].push_back(arr[i]);
        //printf("(%d,%d) ",SparseTable[i][j].first,SparseTable[i][j].second);
    }
    //printf("\n");
    for(j=0,m=1<<j; m<n; j++,m=1<<j)
    {
        for(i=0; i+m<n; i++)
        {
            SparseTable[i].push_back(min(SparseTable[i][j],SparseTable[i+m][SparseTable[i+m].size()-1]));
            //printf("(%d,%d) ",SparseTable[i][j+1].first,SparseTable[i][j+1].second);
        }
        //printf("\n");
    }
}
void Clear()
{
    int i,n=arr.size();
    arr.clear();
    for(i=0; i<n; i++)
    {
        SparseTable[i].clear();
    }
}
pair<int,int> query(int l,int r)
{
    int difference=(r-l+1);
    //printf("(%d,%d,%d)\n",difference,cal[difference].first,cal[difference].second);
    return min(SparseTable[l][cal[difference].first],SparseTable[r-cal[difference].second+1][cal[difference].first]);
}
pair<int,int> lca(int a,int b)
{
    int l=positions[a],r=positions[b];
    if(l>r) swap(l,r);
    //printf("(%d,%d)\n",l,r);
    pair<int,int> ans=query(l,r);
    return ans;
}
int p[MAX];
int main()
{
    initialize();
    int t,T=1;
    //scanf("%d",&T);
    for(t=0; t<T; t++)
    {
        int n,i,j,m,a,b;
        scanf("%d",&n);
        for(i=0; i<n; i++)
        {
            scanf("%d",&m);
            for(j=0; j<m; j++)
            {
                scanf("%d",&a);
                p[a]=i;
                Graph[i].push_back(make_pair(a,1));
                Graph[a].push_back(make_pair(i,1));
            }
        }
        i=0;
        //printf("root=%d\n",i);
        dfsLCA(i);
        build();
        scanf("%d",&m);
        pair<int,int> l;
        //printf("Case %d:\n",t+1);
        for(i=0;i<m;i++)
        {
            scanf("%d %d",&a,&b);
            l=lca(a,b);
            printf("%d\n",l.second);
        }
        for(i=0;i<n;i++)
        {
            Graph[i].clear();
        }
        Clear();
    }
    return 0;
}
