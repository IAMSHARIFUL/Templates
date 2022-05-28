#include<bits/stdc++.h>
#include<math.h>
#include<vector>
using namespace std;
#define MAX 100005
#define MOD 1000000007
vector<int> *pvec[MAX];
vector<int> Graph[MAX];
int subtree[MAX];
int color[MAX];
int color_counter[MAX];
pair<long long int,int> Info[MAX];
int Subtree(int node,int parent=-1)
{
    subtree[node]=1;
    int i;
    for(i=0; i<Graph[node].size(); i++)
    {
        if(Graph[node][i]==parent) continue;
        subtree[node]=subtree[node]+Subtree(Graph[node][i],node);
    }
    return subtree[node];
}
pair<long long int,int> dfs(int node,int parent=-1,bool keep=false)
{
    int i,j,k,child,hchild=-1;
    for(i=0; i<Graph[node].size(); i++)
    {
        if(Graph[node][i]==parent) continue;
        if(hchild==-1||subtree[hchild]<subtree[Graph[node][i]])
        {
            hchild=Graph[node][i];
        }
    }
    for(i=0; i<Graph[node].size(); i++)
    {
        if(Graph[node][i]==parent||Graph[node][i]==hchild) continue;
        dfs(Graph[node][i],node,false);
    }
    if(hchild!=-1)
    {
        Info[node]=dfs(hchild,node,true);
        pvec[node]=pvec[hchild];
    }
    else
    {
        pvec[node]=new vector<int> ();
    }
    pvec[node]->push_back(node);
    color_counter[color[node]]++;
    if(color_counter[color[node]]>Info[node].second)
    {
        Info[node].second=color_counter[color[node]];
        Info[node].first=color[node];
    }
    else if(color_counter[color[node]]==Info[node].second)
    {
        Info[node].first=Info[node].first+color[node];
    }
    for(i=0; i<Graph[node].size(); i++)
    {
        if(Graph[node][i]==parent||Graph[node][i]==hchild) continue;
        child=Graph[node][i];
        for(j=0; j<(*pvec[child]).size(); j++)
        {
            k=(*pvec[child])[j];
            pvec[node]->push_back(k);
            color_counter[color[k]]++;
            if(color_counter[color[k]]>Info[node].second)
            {
                Info[node].second=color_counter[color[k]];
                Info[node].first=color[k];
            }
            else if(color_counter[color[k]]==Info[node].second)
            {
                Info[node].first=Info[node].first+color[k];
            }
        }
    }
    if(!keep)
    {
        for(j=0; j<(*pvec[node]).size(); j++)
        {
            k=(*pvec[node])[j];
            color_counter[color[k]]--;
        }
    }
    return Info[node];
}
int main()
{
    int n,u,v,i;
    scanf("%d",&n);
    for(i=1; i<=n; i++)
    {
        scanf("%d",&color[i]);
    }
    for(i=1; i<n; i++)
    {
        scanf("%d %d",&u,&v);
        Graph[u].push_back(v);
        Graph[v].push_back(u);
    }
    Subtree(1);
    dfs(1);
    for(i=1; i<=n; i++)
    {
        printf("%I64d ",Info[i].first);
    }
    return 0;
}
